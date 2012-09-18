// Make a map out of a voronoi graph
// Author:amitp@cs.stanford.edu
// License:MIT

package;

import graph.Center;
import graph.Corner;
import graph.Edge;
import nme.Lib;
import nme.ObjectHash;
import nme.geom.Point;
import nme.geom.Rectangle;
import com.nodename.geom.LineSegment;
import com.nodename.delaunay.Voronoi;
import de.polygonal.math.PM_PRNG;
#if !flash
import co.janicek.core.math.PerlinNoise;
import co.janicek.core.array.Array2dCore;
#end

class Map {
    static public var NUM_POINTS:Int=NUM_ROWS*NUM_COLUMNS;
    //static public var NUM_ROWS:Int = 120;
    //static public var NUM_COLUMNS:Int = 150;
    static public var NUM_ROWS:Int = 40;
    static public var NUM_COLUMNS:Int = 50;
    //static public var NUM_POINTS:Int=20;
    static public var LAKE_THRESHOLD:Float=0.3;// 0 to 1, fraction of water corners for water polygon
    static public var NUM_LLOYD_ITERATIONS:Int=2;

    // Passed in by the caller:
    public var SIZE:Size;

    // Island shape is controlled by the islandRandom seed and the
    // type of island, passed in when we set the island shape. The
    // islandShape function uses both of them to determine whether any
    // point should be water or land.
    //public var islandShape:Function;
    public var islandShape:Point -> Bool;

    // Island details are controlled by this random generator. The
    // initial map upon loading is always deterministic, but
    // subsequent maps reset this random number generator with a
    // random seed.
    public var mapRandom:PM_PRNG;

    // These store the graph data
    public var points:Array<Point>;// Only useful during map construction
    public var centers:Array<Center>;
    public var corners:Array<Corner>;
    public var edges:Array<Edge>;

    public function new(size:Size){
        mapRandom=new PM_PRNG();
        SIZE=size;
        reset();
    }

    // Random parameters governing the overall shape of the island
    public function newIsland(type:String, seed:Int, variant:Int):Void {
        //islandShape=IslandShape['make'+type](seed);
        switch(type)
        {
            case 'Perlin':
                islandShape=IslandShape.makePerlin(seed);
            case 'Square':
                islandShape=IslandShape.makeSquare(seed);
            case 'Blob':
                islandShape=IslandShape.makeBlob(seed);
            case 'Radial':
                islandShape=IslandShape.makeRadial(seed);
            default:
                islandShape=IslandShape.makePerlin(seed);
        }
        mapRandom.seed=variant;
    }


    public function reset():Void {
        var p:Center, q:Corner, edge:Edge;

        // Break cycles so the garbage collector will release data.
        if(points != null){
            points.splice(0, points.length);
        }
        if(edges != null){
            for(edge in edges){
                edge.d0=edge.d1=null;
                edge.v0=edge.v1=null;
            }
            edges.splice(0, edges.length);
        }
        if(centers != null){
            for(p in centers){
                p.neighbors.splice(0, p.neighbors.length);
                p.corners.splice(0, p.corners.length);
                p.borders.splice(0, p.borders.length);
            }
            centers.splice(0, centers.length);
        }
        if(corners != null){
            for(q in corners){
                q.adjacent.splice(0, q.adjacent.length);
                q.touches.splice(0, q.touches.length);
                q.protrudes.splice(0, q.protrudes.length);
                q.downslope=null;
                q.watershed=null;
            }
            corners.splice(0, corners.length);
        }

        // Clear the previous graph data.
        if(points == null)points=new Array<Point>();
        if(edges == null)edges=new Array<Edge>();
        if(centers == null)centers=new Array<Center>();
        if(corners == null)corners=new Array<Corner>();

        //System.gc();
    }


    public function go(first:Int, last:Int):Void {
        var stages:Array<Dynamic>=[];

        function timeIt(name:String, fn:Void -> Void):Void {
            //var t:Float=getTimer();
            fn();
        }

        // Generate the initial random set of points
        stages.push
            (["Place points...",
             function():Void {
             reset();
             Lib.trace('generating random points');
             points=generateRandomPoints();
             }]);

        stages.push
            (["Improve points...",
             function():Void {
             Lib.trace('improving points');
             improveRandomPoints(points);
             }]);


        // Create a graph structure from the Voronoi edge list. The
        // methods in the Voronoi object are somewhat inconvenient for
        // my needs, so I transform that data Into the data I actually
        // need:edges connected to the Delaunay triangles and the
        // Voronoi polygons, a reverse map from those four points back
        // to the edge, a map from these four points to the points
        // they connect to(both along the edge and crosswise).
        stages.push
            (["Build graph...",
             function():Void {
             Lib.trace('building graph');
             var voronoi:Voronoi=new Voronoi(points, null, new Rectangle(0, 0, SIZE.width, SIZE.height));
             buildGraph(points, voronoi);
             improveCorners();
             voronoi.dispose();
             voronoi=null;
             points=null;
             }]);

        stages.push
            (["Assign elevations...",
             function():Void {
             Lib.trace('assigning elevations');
             // Determine the elevations and water at Voronoi corners.
             assignCornerElevations();

             // Determine polygon and corner type:ocean, coast, land.
             assignOceanCoastAndLand();

             // Rescale elevations so that the highest is 1.0, and they're
             // distributed well. We want lower elevations to be more common
             // than higher elevations, in proportions approximately matching
             // concentric rings. That is, the lowest elevation is the
             // largest ring around the island, and therefore should more
             // land area than the highest elevation, which is the very
             // center of a perfectly circular island.
             redistributeElevations(landCorners(corners));

             // Assign elevations to non-land corners
             for(q in corners)
             {
                 if(q.ocean || q.coast)
                 {
                     q.elevation=0.0;
                 }
             }

             // Polygon elevations are the average of their corners
             assignPolygonElevations();
             }]);


        stages.push
            (["Assign moisture...",
             function():Void {
             Lib.trace('assigning moisture');
             // Determine downslope paths.
             calculateDownslopes();

             // Determine watersheds:for every corner, where does it flow
             // out Into the ocean? 
             calculateWatersheds();

             // Create rivers.
             createRivers();

             // Determine moisture at corners, starting at rivers
             // and lakes, but not oceans. Then redistribute
             // moisture to cover the entire range evenly from 0.0
             // to 1.0. Then assign polygon moisture as the average
             // of the corner moisture.
             assignCornerMoisture();
             redistributeMoisture(landCorners(corners));
             assignPolygonMoisture();
             }]);

        stages.push
            (["Decorate map...",
             function():Void {
             Lib.trace('decorating map');
             assignBiomes();
             }]);

        for(i in first...last){
            timeIt(stages[i][0], stages[i][1]);
        }
    }


    // Generate random points and assign them to be on the island or
    // in the water. Some water points are inland lakes;others are
    // ocean. We'll determine ocean later by looking at what's
    // connected to ocean.
    public function generateRandomPoints():Array<Point>{
        var p:Point, i:Int, points:Array<Point>=new Array<Point>();
        var h_step:Int = Math.ceil(SIZE.width/NUM_COLUMNS);
        var v_step:Int = Math.ceil(SIZE.height/NUM_ROWS);
        var odd:Bool = true;
        for(i in 0...NUM_COLUMNS)
        {
            for(j in 0...NUM_ROWS)
            {
                odd = !odd;
                //for(i in 0...NUM_POINTS){
                p=new Point(mapRandom.nextDoubleRange(10, h_step) + h_step*i + (odd ? h_step/2 : 0),
                        mapRandom.nextDoubleRange(10, v_step) + v_step*j);
                points.push(p);
            }

            }
            return points;
        }


        // Improve the random set of points with Lloyd Relaxation.
        public function improveRandomPoints(points:Array<Point>):Void {
            return;
            // We'd really like to generate "blue noise". Algorithms:
            // 1. Poisson dart throwing:check each new point against all
            //	 existing points, and reject it if it's too close.
            // 2. Start with a hexagonal grid and randomly perturb points.
            // 3. Lloyd Relaxation:move each point to the centroid of the
            //	 generated Voronoi polygon, then generate Voronoi again.
            // 4. Use force-based layout algorithms to push points away.
            // 5. More at http://www.cs.virginia.edu/~gfx/pubs/antimony/
            // Option 3 is implemented here. If it's run for too many iterations,
            // it will turn Into a grid, but convergence is very slow, and we only
            // run it a few times.
            var i:Int, voronoi:Voronoi, region:Array<Point>, tmp_p:Point = new Point();
            for(i in 0...NUM_LLOYD_ITERATIONS){
                voronoi=new Voronoi(points, null, new Rectangle(0, 0, SIZE.width, SIZE.height));
                for(p in points){
                    //Lib.trace('original point ' + Std.string(p.x) + ' ' + Std.string(p.y));
                    region=voronoi.region(p);

                    if(region.length == 0)
                    {
                        //Lib.trace('region length is null');
                        continue;
                    }
                    p.x=0.0;
                    p.y=0.0;
                    for(q in region){
                        p.x +=q.x;
                        p.y +=q.y;
                    }
                    tmp_p.x = tmp_p.x / region.length;
                    tmp_p.y = tmp_p.x / region.length;
                    //Lib.trace('modified point ' + Std.string(tmp_p.x) + ' ' + Std.string(tmp_p.y));
                    region.splice(0, region.length);
                }
                voronoi.dispose();
            }
        }


        // Although Lloyd relaxation improves the uniformity of polygon
        // sizes, it doesn't help with the edge lengths. Short edges can
        // be bad for some games, and lead to weird artifacts on
        // rivers. We can easily lengthen short edges by moving the
        // corners, but **we lose the Voronoi property**.  The corners are
        // moved to the average of the polygon centers around them. Short
        // edges become longer. Long edges tend to become shorter. The
        // polygons tend to be more uniform after this step.
        public function improveCorners():Void {
            //var newCorners:Array<Point>=new Array<Point>(corners.length);
            var newCorners:Array<Point>=new Array<Point>();
            var q:Corner, r:Center, point:Point, i:Int, edge:Edge;

            // First we compute the average of the centers next to each corner.
            for(q in corners){
                if(q.border){
                    newCorners[q.index]=q.point;
                } else {
                    point=new Point(0.0, 0.0);
                    for(r in q.touches){
                        point.x +=r.point.x;
                        point.y +=r.point.y;
                    }
                    point.x /=q.touches.length;
                    point.y /=q.touches.length;
                    newCorners[q.index]=point;
                }
            }

            // Move the corners to the new locations.
            for(i in 0...corners.length){
                corners[i].point=newCorners[i];
            }

            // The edge midpoints were computed for the old corners and need
            // to be recomputed.
            for (edge in edges) {
                if (edge.v0 != null && edge.v1 != null) {
                    edge.midpoint = Point.interpolate(edge.v0.point, edge.v1.point, 0.5);
                }
            }
        }


        // Create an array of corners that are on land only, for use by
        // algorithms that work only on land.  We return an array instead
        // of a vector because the redistribution algorithms want to sort
        // this array using Array.sortOn.
        public function landCorners(corners:Array<Corner>):Array<Dynamic> {
            var q:Corner, locations:Array<Dynamic>=[];
            for(q in corners){
                if(!q.ocean && !q.coast){
                    locations.push(q);
                }
            }
            return locations;
        }


        // Build graph data structure in 'edges', 'centers', 'corners',
        // based on information in the Voronoi results:point.neighbors
        // will be a list of neighboring points of the same type(corner
        // or center);point.edges will be a list of edges that include
        // that point. Each edge connects to four points:the Voronoi edge
        // edge.{v0,v1} and its dual Delaunay triangle edge edge.{d0,d1}.
        // For boundary polygons, the Delaunay edge will have one null
        // point, and the Voronoi edge may be null.
        public function buildGraph(points:Array<Point>, voronoi:Voronoi):Void {
            var p:Center, q:Corner, point:Point, other:Point;
            var libedges:Array<com.nodename.delaunay.Edge>=voronoi.edges();
            var centerLookup:ObjectHash<Point, Center>=new ObjectHash<>();

            // Build Center objects for of the points, and a lookup map
            // to find those Center objects again as we build the graph
            for(point in points){
                p=new Center();
                p.index=centers.length;
                p.point=point;
                p.neighbors=new  Array<Center>();
                p.borders=new Array<Edge>();
                p.corners=new Array<Corner>();
                centers.push(p);
                centerLookup.set(point, p);
            }

            // Workaround for Voronoi lib bug:we need to call region()
            // before Edges or neighboringSites are available
            for(p in centers){
                voronoi.region(p.point);
            }

            // The Voronoi library generates multiple Point objects for
            // corners, and we need to canonicalize to one Corner object.
            // To make lookup fast, we keep an array of Points, bucketed by
            // x value, and then we only have to look at other Points in
            // nearby buckets. When we fail to find one, we'll create a new
            // Corner object.
            var _cornerMap:Array<Array<Corner>> = [];
            function makeCorner(point:Point):Corner {
                var q:Corner;

                if (point == null) return null;
                var bucket:Int;
                for (bucket in Std.int(point.x) - 1...Std.int(point.x) + 2) {
                    if (_cornerMap[bucket] != null) {
                        for (q in _cornerMap[bucket]) {
                            var dx:Float = point.x - q.point.x;
                            var dy:Float = point.y - q.point.y;
                            if (dx * dx + dy * dy < 1e-6) {
                                return q;
                            }
                        }
                    }
                }
                bucket = Std.int(point.x);
                if (_cornerMap[bucket] == null) _cornerMap[bucket] = [];
                q = new Corner();
                q.index = corners.length;
                corners.push(q);
                q.point = point;
                q.border = (point.x == 0 || point.x == SIZE.width
                        || point.y == 0 || point.y == SIZE.height);
                q.touches = new Array<Center>();
                q.protrudes = new Array<Edge>();
                q.adjacent = new Array<Corner>();
                _cornerMap[bucket].push(q);
                return q;
            }
            for(libedge in libedges){
                var dedge:LineSegment=libedge.delaunayLine();
                var vedge:LineSegment=libedge.voronoiEdge();

                // Fill the graph data. Make an Edge object corresponding to
                // the edge from the voronoi library.
                var edge:Edge=new Edge();
                edge.index=edges.length;
                edge.river=0;
                edges.push(edge);
                edge.midpoint = if(vedge.p0 != null && vedge.p1 != null) Point.interpolate(vedge.p0, vedge.p1, 0.5);

                // Edges point to corners. Edges point to centers. 
                edge.v0=makeCorner(vedge.p0);
                edge.v1=makeCorner(vedge.p1);
                edge.d0=centerLookup.get(dedge.p0);
                edge.d1=centerLookup.get(dedge.p1);

                // Centers point to edges. Corners point to edges.
                if(edge.d0 !=null){ edge.d0.borders.push(edge);}
                if(edge.d1 !=null){ edge.d1.borders.push(edge);}
                if(edge.v0 !=null){ edge.v0.protrudes.push(edge);}
                if(edge.v1 !=null){ edge.v1.protrudes.push(edge);}

                function addToCornerList(v:Array<Corner>, x:Corner):Void {
                    if(x !=null && Lambda.indexOf(v, x)<0){ v.push(x);}
                }
                function addToCenterList(v:Array<Center>, x:Center):Void {
                    if(x !=null && Lambda.indexOf(v, x)<0){ v.push(x);}
                }

                // Centers point to centers.
                if(edge.d0 !=null && edge.d1 !=null){
                    addToCenterList(edge.d0.neighbors, edge.d1);
                    addToCenterList(edge.d1.neighbors, edge.d0);
                }

                // Corners point to corners
                if(edge.v0 !=null && edge.v1 !=null){
                    addToCornerList(edge.v0.adjacent, edge.v1);
                    addToCornerList(edge.v1.adjacent, edge.v0);
                }

                // Centers point to corners
                if(edge.d0 !=null){
                    addToCornerList(edge.d0.corners, edge.v0);
                    addToCornerList(edge.d0.corners, edge.v1);
                }
                if(edge.d1 !=null){
                    addToCornerList(edge.d1.corners, edge.v0);
                    addToCornerList(edge.d1.corners, edge.v1);
                }

                // Corners point to centers
                if(edge.v0 !=null){
                    addToCenterList(edge.v0.touches, edge.d0);
                    addToCenterList(edge.v0.touches, edge.d1);
                }
                if(edge.v1 !=null){
                    addToCenterList(edge.v1.touches, edge.d0);
                    addToCenterList(edge.v1.touches, edge.d1);
                }
            }
        }


        // Determine elevations and water at Voronoi corners. By
        // construction, we have no local minima. This is important for
        // the downslope vectors later, which are used in the river
        // construction algorithm. Also by construction, inlets/bays
        // push low elevation areas inland, which means many rivers end
        // up flowing out through them. Also by construction, lakes
        // often end up on river paths because they don't raise the
        // elevation as much as other terrain does.
        public function assignCornerElevations():Void {
            var q:Corner, s:Corner;
            var queue:Array<Dynamic>=[];

            for(q in corners){
                q.water=!inside(q.point);
            }

            for(q in corners){
                // The edges of the map are elevation 0
                if(q.border){
                    q.elevation=0.0;
                    queue.push(q);
                } else {
                    q.elevation=Math.POSITIVE_INFINITY;
                }
            }
            // Traverse the graph and assign elevations to each point. As we
            // move away from the map border, increase the elevations. This
            // guarantees that rivers always have a way down to the coast by
            // going downhill(no local minima).
            while(queue.length>0){
                q=queue.shift();

                for(s in q.adjacent){
                    // Every step up is epsilon over water or 1 over land. The
                    // number doesn't matter because we'll rescale the
                    // elevations later.
                    var newElevation:Float=0.01 + q.elevation;
                    if(!q.water && !s.water){
                        newElevation +=1;
                    }
                    // If this point changed, we'll add it to the queue so
                    // that we can process its neighbors too.
                    if(newElevation<s.elevation){
                        s.elevation=newElevation;
                        queue.push(s);
                    }
                }
            }
        }


        // Change the overall distribution of elevations so that lower
        // elevations are more common than higher
        // elevations. Specifically, we want elevation X to have frequency
        //(1-X).  To do this we will sort the corners, then set each
        // corner to its desired elevation.
        public function redistributeElevations(locations:Array<Dynamic>):Void {
            // SCALE_FACTOR increases the mountain area. At 1.0 the maximum
            // elevation barely shows up on the map, so we set it to 1.1.
            var SCALE_FACTOR:Float=1.1;
            var i:Int, y:Float, x:Float;

            //locations.sortOn('elevation', Array.NUMERIC);
            locations.sort(function(c1, c2) {
                    if (c1.elevation > c2.elevation) return 1;
                    if (c1.elevation < c2.elevation) return -1;
                    if (c1.index > c2.index) return 1;
                    if (c1.index < c2.index) return -1;
                    return 0;
                    } );
            for(i in 0...locations.length){
                // Let y(x)be the total area that we want at elevation<=x.
                // We want the higher elevations to occur less than lower
                // ones, and set the area to be y(x)=1 -(1-x)^2.
                y=i/(locations.length-1);
                // Now we have to solve for x, given the known y.
                //  *  y=1 -(1-x)^2
                //  *  y=1 -(1 - 2x + x^2)
                //  *  y=2x - x^2
                //  *  x^2 - 2x + y=0
                // From this we can use the quadratic equation to get:
                x=Math.sqrt(SCALE_FACTOR)- Math.sqrt(SCALE_FACTOR*(1-y));
                if(x>1.0)x=1.0;// TODO:does this break downslopes?
                locations[i].elevation=x;
            }
        }


        // Change the overall distribution of moisture to be evenly distributed.
        public function redistributeMoisture(locations:Array<Dynamic>):Void {
            var i:Int;
            locations.sort(function(c1, c2) {
                    if (c1.moisture > c2.moisture) return 1;
                    if (c1.moisture < c2.moisture) return -1;
                    if (c1.index > c2.index) return 1;
                    if (c1.index < c2.index) return -1;
                    return 0;
                    } );
            for(i in 0...locations.length){
                locations[i].moisture=i/(locations.length-1);
            }
        }


        // Determine polygon and corner types:ocean, coast, land.
        public function assignOceanCoastAndLand():Void {
            // Compute polygon attributes 'ocean' and 'water' based on the
            // corner attributes. Count the water corners per
            // polygon. Oceans are all polygons connected to the edge of the
            // map. In the first pass, mark the edges of the map as ocean;
            // in the second pass, mark any water-containing polygon
            // connected an ocean as ocean.
            var queue:Array<Dynamic>=[];
            var p:Center = new Center(), q:Corner = new Corner(), r:Center = new Center(), numWater:Int = 0;

            for(p in centers){
                numWater=0;
                for(q in p.corners){
                    if(q.border){
                        p.border=true;
                        p.ocean=true;
                        q.water=true;
                        queue.push(p);
                    }
                    if(q.water){
                        numWater +=1;
                    }
                }
                p.water=(p.ocean || (numWater>=p.corners.length * LAKE_THRESHOLD));
            }
            while(queue.length>0){
                p=queue.shift();
                for(r in p.neighbors){
                    if(r.water && !r.ocean){
                        r.ocean=true;
                        queue.push(r);
                    }
                }
            }

            // Set the polygon attribute 'coast' based on its neighbors. If
            // it has at least one ocean and at least one land neighbor,
            // then this is a coastal polygon.
            for(p in centers){
                var numOcean:Int=0;
                var numLand:Int=0;
                for(r in p.neighbors){
                    numOcean += r.ocean ? 1 : 0;
                    numLand += !r.water ? 1 : 0;
                }
                p.coast=(numOcean>0)&&(numLand>0);
            }


            // Set the corner attributes based on the computed polygon
            // attributes. If all polygons connected to this corner are
            // ocean, then it's ocean;if all are land, then it's land;
            // otherwise it's coast.
            for(q in corners){
                var numOcean:Int=0;
                var numLand:Int=0;
                //Lib.trace('new corner');
                for(p in q.touches){
                    //Lib.trace(Std.string(r.ocean) + Std.string(!r.water));
                    numOcean += p.ocean ? 1 : 0;
                    numLand += !p.water ? 1 : 0;
                }
                //Lib.trace(Std.string(numOcean) + Std.string(numOcean) + 'endup');
                q.ocean=(numOcean==q.touches.length);
                q.coast=(numOcean>0)&&(numLand>0);
                q.water=q.border ||((numLand !=q.touches.length)&& !q.coast);
            }
        }


        // Polygon elevations are the average of the elevations of their corners.
        public function assignPolygonElevations():Void {
            var p:Center, q:Corner, sumElevation:Float;
            for(p in centers){
                sumElevation=0.0;
                for(q in p.corners){
                    sumElevation +=q.elevation;
                }
                p.elevation=sumElevation / p.corners.length;
            }
        }


        // Calculate downslope pointers.  At every point, we point to the
        // point downstream from it, or to itself.  This is used for
        // generating rivers and watersheds.
        public function calculateDownslopes():Void {
            var q:Corner, s:Corner, r:Corner;

            for(q in corners){
                r=q;
                for(s in q.adjacent){
                    if(s.elevation<=r.elevation){
                        r=s;
                    }
                }
                q.downslope=r;
            }
        }


        // Calculate the watershed of every land point. The watershed is
        // the last downstream land point in the downslope graph. TODO:
        // watersheds are currently calculated on corners, but it'd be
        // more useful to compute them on polygon centers so that every
        // polygon can be marked as being in one watershed.
        public function calculateWatersheds():Void {
            var q:Corner, r:Corner, i:Int, changed:Bool;

            // Initially the watershed pointer points downslope one step.	  
            for(q in corners){
                q.watershed=q;
                if(!q.ocean && !q.coast){
                    q.watershed=q.downslope;
                }
            }
            // Follow the downslope pointers to the coast. Limit to 100
            // iterations although most of the time with NUM_POINTS=2000 it
            // only takes 20 iterations because most points are not far from
            // a coast.  TODO:can run faster by looking at
            // p.watershed.watershed instead of p.downslope.watershed.
            for(i in 0...100){
                changed=false;
                for(q in corners){
                    if(!q.ocean && !q.coast && !q.watershed.coast){
                        r=q.downslope.watershed;
                        if(!r.ocean)q.watershed=r;
                        changed=true;
                    }
                }
                if(!changed)break;
            }
            // How big is each watershed?
            for(q in corners){
                r=q.watershed;
                r.watershed_size=1 + ((NullHelper.IsNull(r.watershed_size)) ? 0 : r.watershed_size);
            }
        }


        // Create rivers along edges. Pick a random corner point, then
        // move downslope. Mark the edges and corners as rivers.
        public function createRivers():Void {
            //riverChance = riverChance.coalesce(Std.int((SIZE.width + SIZE.height) / 4));
            //return;

            var i:Int, q:Corner, edge:Edge;

            for (i in 0...50) {
                q=corners[mapRandom.nextIntRange(0, corners.length-1)];
                //Lib.trace(q.ocean);
                //Lib.trace(q.elevation);
                if(NullHelper.IsNotNull(q))
                {
                    //if(NullHelper.IsNotNull(q.ocean) && NullHelper.IsNotNull(q.elevation))
                    //{  

                    if(q.ocean || q.water || q.elevation<0.3 || q.elevation>0.9)
                        continue;
                    // Bias rivers to go west:if(q.downslope.x>q.x)continue;
                    while(!q.coast){
                        if(q==q.downslope){
                            break;
                        }
                        edge=lookupEdgeFromCorner(q, q.downslope);
                        edge.river=edge.river + 1;
                        q.river=((NullHelper.IsNull(q.river)) ? 0 : q.river)+ 1;
                        q.downslope.river=((NullHelper.IsNull(q.downslope.river)) ? 0 : q.downslope.river)+ 1;// TODO:fix double count
                        q=q.downslope;
                    }
                    //}
                }
            }
        }


        // Calculate moisture. Freshwater sources spread moisture:rivers
        // and lakes(not oceans). Saltwater sources have moisture but do
        // not spread it(we set it at the end, after propagation).
        public function assignCornerMoisture():Void {
            var q:Corner, r:Corner, newMoisture:Float;
            var queue:Array<Dynamic>=[];
            // Fresh water
            for(q in corners){
                if((q.water || q.river>0)&& !q.ocean){
                    q.moisture=q.river>0? Math.min(3.0,(0.2 * q.river)):1.0;
                    queue.push(q);
                } else {
                    q.moisture=0.0;
                }
            }
            while(queue.length>0){
                q=queue.shift();

                for(r in q.adjacent){
                    newMoisture=q.moisture * 0.9;
                    if(newMoisture>r.moisture){
                        r.moisture=newMoisture;
                        queue.push(r);
                    }
                }
            }
            // Salt water
            for(q in corners){
                if(q.ocean || q.coast){
                    q.moisture=1.0;
                }
            }
        }


        // Polygon moisture is the average of the moisture at corners
        public function assignPolygonMoisture():Void {
            var p:Center, q:Corner, sumMoisture:Float;
            for(p in centers){
                sumMoisture=0.0;
                for(q in p.corners){
                    if(q.moisture>1.0)q.moisture=1.0;
                    sumMoisture +=q.moisture;
                }
                p.moisture=sumMoisture / p.corners.length;
            }
        }


        // Assign a biome type to each polygon. If it has
        // ocean/coast/water, then that's the biome;otherwise it depends
        // on low/high elevation and low/medium/high moisture. This is
        // roughly based on the Whittaker diagram but adapted to fit the
        // needs of the island map generator.
        static public function getBiome(p:Center):String {

            if(p.ocean){
                return 'OCEAN';
            } else if(p.water){
                if(p.elevation<0.1)return 'MARSH';
                if(p.elevation>0.8)return 'ICE';
                return 'LAKE';
            } else if(p.coast){
                return 'BEACH';
            } else if(p.elevation>0.8){
                if(p.moisture>0.50)return 'SNOW';
                else if(p.moisture>0.33)return 'TUNDRA';
                else if(p.moisture>0.16)return 'BARE';
                else return 'SCORCHED';
            } else if(p.elevation>0.6){
                if(p.moisture>0.66)return 'TAIGA';
                else if(p.moisture>0.33)return 'SHRUBLAND';
                else return 'TEMPERATE_DESERT';
            } else if(p.elevation>0.3){
                if(p.moisture>0.83)return 'TEMPERATE_RAIN_FOREST';
                else if(p.moisture>0.50)return 'TEMPERATE_DECIDUOUS_FOREST';
                else if(p.moisture>0.16)return 'GRASSLAND';
                else return 'TEMPERATE_DESERT';
            } else {
                if(p.moisture>0.66)return 'TROPICAL_RAIN_FOREST';
                else if(p.moisture>0.33)return 'TROPICAL_SEASONAL_FOREST';
                else if(p.moisture>0.16)return 'GRASSLAND';
                else return 'SUBTROPICAL_DESERT';
            }
        }

        public function assignBiomes():Void {
            var p:Center;
            for(p in centers){
                p.biome=getBiome(p);
            }
        }


        // Look up a Voronoi Edge object given two adjacent Voronoi
        // polygons, or two adjacent Voronoi corners
        public function lookupEdgeFromCenter(p:Center, r:Center):Edge {
            for(edge in p.borders){
                if(edge.d0==r || edge.d1==r)return edge;
            }
            return null;
        }

        public function lookupEdgeFromCorner(q:Corner, s:Corner):Edge {
            for(edge in q.protrudes){
                if(edge.v0==s || edge.v1==s)return edge;
            }
            return null;
        }


        // Determine whether a given point should be on the island or in the water.
        public function inside(p:Point):Bool {
            return islandShape(new Point(2*(p.x/SIZE.width - 0.5), 2*(p.y/SIZE.height - 0.5)));
        }
    }


    // Factory class to build the 'inside' function that tells us whether
    // a point should be on the island or in the water.
    import flash.geom.Point;
    import flash.display.BitmapData;
    import de.polygonal.math.PM_PRNG;
    class IslandShape {
        // This class has factory functions for generating islands of
        // different shapes. The factory returns a function that takes a
        // normalized point(x and y are -1 to +1)and returns true if the
        // point should be on the island, and false if it should be water
        //(lake or ocean).


        // The radial island radius is based on overlapping sine waves 
        static public var ISLAND_FACTOR:Float=1.07;// 1.0 means no small islands;2.0 leads to a lot
        static public function makeRadial(seed:Int):Point -> Bool {
            var islandRandom:PM_PRNG=new PM_PRNG();
            islandRandom.seed=seed;
            var bumps:Int=islandRandom.nextIntRange(1, 6);
            var startAngle:Float=islandRandom.nextDoubleRange(0, 2*Math.PI);
            var dipAngle:Float=islandRandom.nextDoubleRange(0, 2*Math.PI);
            var dipWidth:Float=islandRandom.nextDoubleRange(0.2, 0.7);

            function inside(q:Point):Bool {
                var angle:Float=Math.atan2(q.y, q.x);
                var length:Float=0.5 *(Math.max(Math.abs(q.x), Math.abs(q.y))+ q.length);

                var r1:Float=0.5 + 0.40*Math.sin(startAngle + bumps*angle + Math.cos((bumps+3)*angle));
                var r2:Float=0.7 - 0.20*Math.sin(startAngle + bumps*angle - Math.sin((bumps+2)*angle));
                if(Math.abs(angle - dipAngle)<dipWidth
                        || Math.abs(angle - dipAngle + 2*Math.PI)<dipWidth
                        || Math.abs(angle - dipAngle - 2*Math.PI)<dipWidth){
                    r1=r2=0.2;
                }
                return(length<r1 ||(length>r1*ISLAND_FACTOR && length<r2));
            }

            return inside;
        }


        // The Perlin-based island combines perlin noise with the radius
        static public function makePerlin(seed:Int):Point -> Bool {
            
            #if flash
            	var perlin:BitmapData=new BitmapData(256, 256);
            	perlin.perlinNoise(64, 64, 8, seed, false, true);
            #else
            	var perlin:Array<Array<Int>>;
            	perlin = PerlinNoise.makePerlinNoise(256, 256, 1.0, 1.0, 1.0, seed, 8);
            #end

            return function(q:Point):Bool {
            	#if flash
                var c:Float=(perlin.getPixel(Std.int((q.x+1)*128), Std.int((q.y+1)*128))& 0xff)/ 255.0;
                #else
                var c:Float=(Array2dCore.get(perlin, Std.int((q.x + 1) * 128), Std.int((q.y + 1) * 128)) & 0xff) / 255.0;
                #end
                return c>(0.3+0.3*q.length*q.length);
            };
        }


        // The square shape fills the entire space with land
        static public function makeSquare(seed:Int):Point -> Bool {
            return function(q:Point):Bool {
                return true;
            };
        }


        // The blob island is shaped like Amit's blob logo
        static public function makeBlob(seed:Int):Point -> Bool {
            return function(q:Point):Bool {
                var eye1:Bool=new Point(q.x-0.2, q.y/2+0.2).length<0.05;
                var eye2:Bool=new Point(q.x+0.2, q.y/2+0.2).length<0.05;
                var body:Bool=q.length<0.8 - 0.18*Math.sin(5*Math.atan2(q.y, q.x));
                return body && !eye1 && !eye2;
            };
        }
    }
