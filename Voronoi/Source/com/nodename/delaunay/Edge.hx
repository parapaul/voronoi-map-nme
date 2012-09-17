package com.nodename.delaunay;

//import as3.PointCore;
//import as3.Rectangle;
import nme.geom.Rectangle;
import nme.geom.Point;
import nme.display.BitmapData;
import nme.display.Sprite;
import nme.display.Graphics;
import nme.display.LineScaleMode;
import nme.display.CapsStyle;
//import as3.TypeDefs;
import com.nodename.geom.LineSegment;

//using as3.BitmapDataCore;
//using as3.RectangleCore;

class Edge {

	private static var _pool:Array<Edge> = new Array<Edge>();
	
	/**
	 * This is the only way to create a new Edge 
	 * @param site0
	 * @param site1
	 * @return 
	 * 
	 */
	public static function createBisectingEdge(site0:Site, site1:Site):Edge
	{
		var dx:Float, dy:Float, absdx:Float, absdy:Float;
		var a:Float, b:Float, c:Float;
	
		dx = site1.x - site0.x;
		dy = site1.y - site0.y;
		absdx = dx > 0 ? dx : -dx;
		absdy = dy > 0 ? dy : -dy;
		c = site0.x * dx + site0.y * dy + (dx * dx + dy * dy) * 0.5;
		if (absdx > absdy)
		{
			a = 1.0; b = dy/dx; c /= dx;
		}
		else
		{
			b = 1.0; a = dx/dy; c /= dy;
		}
		
		var edge:Edge = Edge.create();
	
		edge.leftSite = site0;
		edge.rightSite = site1;
		site0.addEdge(edge);
		site1.addEdge(edge);
		
		edge.leftVertex = null;
		edge.rightVertex = null;
		
		edge.a = a; edge.b = b; edge.c = c;
		//Lib.trace("createBisectingEdge: a ", edge.a, "b", edge.b, "c", edge.c);
		
		return edge;
	}
	
	private static function create():Edge
	{
		var edge:Edge;
		if (_pool.length > 0)
		{
			edge = _pool.pop();
			edge.init();
		}
		else
		{
			edge = new Edge();
		}
		return edge;
	}
	
	private static var LINESPRITE:Sprite = new Sprite();
	private static var GRAPHICS:Graphics = LINESPRITE.graphics;
	
	public var delaunayLineBmp(getDelaunayLineBmp, never):BitmapData;
	private var _delaunayLineBmp:BitmapData;
	private function getDelaunayLineBmp():BitmapData
	{
		if (_delaunayLineBmp == null)
		{
			_delaunayLineBmp = makeDelaunayLineBmp();
		}
		return _delaunayLineBmp;
	}
	
	// making this available to Voronoi; running out of memory in AIR so I cannot cache the bmp
	public function makeDelaunayLineBmp():BitmapData
	{
		//throw "unimplemented";
		
		var p0:Point = leftSite.coord;
		var p1:Point = rightSite.coord;
		
		var w:Int = Std.int(Math.ceil(Math.max(p0.x, p1.x)));
		if (w < 1)
		{
			w = 1;
		}
		var h:Int = Std.int(Math.ceil(Math.max(p0.y, p1.y)));
		if (h < 1)
		{
			h = 1;
		}
		var bmp:BitmapData = new BitmapData(w, h, true, 0);
		//var bmp:BitmapData = new BitmapData();

		GRAPHICS.clear();
		// clear() resets line style back to undefined!
		GRAPHICS.lineStyle(0, 0, 1.0, false, LineScaleMode.NONE, CapsStyle.NONE);
		GRAPHICS.moveTo(p0.x, p0.y);
		GRAPHICS.lineTo(p1.x, p1.y);
		
		//bmp.drawLine(p0, p1);
		
		bmp.draw(LINESPRITE);
		return bmp;
	}
	
	public function delaunayLine():LineSegment
	{
		// draw a line connecting the input Sites for which the edge is a bisector:
		return new LineSegment(leftSite.coord, rightSite.coord);
	}

	public function voronoiEdge():LineSegment
	{
	  if (!visible) return new LineSegment(null, null);
	  return new LineSegment(clippedEnds.get(LR.LEFT.toString()),
							 clippedEnds.get(LR.RIGHT.toString()));
	}

	private static var _nedges:Int = 0;
	
	public static var DELETED:Edge = new Edge();

	// the equation of the edge: ax + by = c
	public var a:Float;
	public var b:Float;
	public var c:Float;

	// the two Voronoi vertices that the edge connects
	//		(if one of them is null, the edge extends to infinity)
	public var leftVertex(default, null):Vertex;
	public var rightVertex(default, null):Vertex;
	public function vertex(leftRight:LR):Vertex
	{
		return (leftRight == LR.LEFT) ? leftVertex : rightVertex;
	}

	public function setVertex(leftRight:LR, v:Vertex):Void
	{
		if (leftRight == LR.LEFT)
		{
			leftVertex = v;
		}
		else
		{
			rightVertex = v;
		}
	}
	
	public function isPartOfConvexHull():Bool
	{
		return (leftVertex == null || rightVertex == null);
	}

	public function sitesDistance():Float
	{
		return Point.distance(leftSite.coord, rightSite.coord);
	}
	
	public static function compareSitesDistances_MAX(edge0:Edge, edge1:Edge):Int
	{
		var length0:Float = edge0.sitesDistance();
		var length1:Float = edge1.sitesDistance();
		if (length0 < length1)
		{
			return 1;
		}
		if (length0 > length1)
		{
			return -1;
		}
		return 0;
	}

	public static function compareSitesDistances(edge0:Edge, edge1:Edge):Int
	{
		return - compareSitesDistances_MAX(edge0, edge1);
	}
	
	// Once clipVertices() is called, this Hash will hold two Points
	// representing the clipped coordinates of the left and right ends...
	//private var _clippedVertices:Hash;
	public var clippedEnds(default, null):Hash<Point>;
	// unless the entire Edge is outside the bounds.
	// In that case visible will be false:
	public var visible(getVisible, never):Bool;
	private inline function getVisible():Bool
	{
		return clippedEnds != null;
	}

	// the two input Sites for which this Edge is a bisector:
	//private var _sites:Hash<Site>;
	// the two input Sites for which this Edge is a bisector:               
	public var leftSite : Site;
	public var rightSite : Site;
	
	public function site(leftRight:LR):Site
	{
		return (leftRight == LR.LEFT) ? leftSite : rightSite;
	}

	private var _edgeIndex:Int;
	
	public function dispose():Void
	{
		if (_delaunayLineBmp != null)
		{
			_delaunayLineBmp.dispose();
			_delaunayLineBmp = null;
		}
		leftVertex = null;
		rightVertex = null;
		if (clippedEnds != null)
		{
			clippedEnds.set(LR.LEFT.toString(), null);
			clippedEnds.set(LR.RIGHT.toString(), null);
			clippedEnds = null;
		}

		leftSite = null;
		rightSite = null;
		
		_pool.push(this);
	}

	private function new()
	{
		_edgeIndex = _nedges++;
		init();
	}
	
	private function init():Void
	{	
		leftSite = null;
		rightSite = null;
	}
	
	public function toString():String
	{
		return "Edge " + _edgeIndex + "; sites " + leftSite + ", " + rightSite
				+ "; endVertices " + (leftVertex != null ? Std.string(leftVertex.vertexIndex) : "null") + ", "
				 + (rightVertex != null ? Std.string(rightVertex.vertexIndex) : "null") + "::";
	}

	/**
	 * Set _clippedVertices to contain the two ends of the portion of the Voronoi edge that is visible
	 * within the bounds.  If no part of the Edge falls within the bounds, leave _clippedVertices null. 
	 * @param bounds
	 * 
	 */
	public function clipVertices(bounds:Rectangle):Void
	{
		var xmin:Float = bounds.x;
		var ymin:Float = bounds.y;
		var xmax:Float = bounds.right;
		var ymax:Float = bounds.bottom;
		
		var vertex0:Vertex, vertex1:Vertex;
		var x0:Float, x1:Float, y0:Float, y1:Float;
		
		if (a == 1.0 && b >= 0.0)
		{
			vertex0 = rightVertex;
			vertex1 = leftVertex;
		}
		else 
		{
			vertex0 = leftVertex;
			vertex1 = rightVertex;
		}
	
		if (a == 1.0)
		{
			y0 = ymin;
			if (vertex0 != null && vertex0.y > ymin)
			{
				 y0 = vertex0.y;
			}
			if (y0 > ymax)
			{
				return;
			}
			x0 = c - b * y0;
			
			y1 = ymax;
			if (vertex1 != null && vertex1.y < ymax)
			{
				y1 = vertex1.y;
			}
			if (y1 < ymin)
			{
				return;
			}
			x1 = c - b * y1;
			
			if ((x0 > xmax && x1 > xmax) || (x0 < xmin && x1 < xmin))
			{
				return;
			}
			
			if (x0 > xmax)
			{
				x0 = xmax; y0 = (c - x0)/b;
			}
			else if (x0 < xmin)
			{
				x0 = xmin; y0 = (c - x0)/b;
			}
			
			if (x1 > xmax)
			{
				x1 = xmax; y1 = (c - x1)/b;
			}
			else if (x1 < xmin)
			{
				x1 = xmin; y1 = (c - x1)/b;
			}
		}
		else
		{
			x0 = xmin;
			if (vertex0 != null && vertex0.x > xmin)
			{
				x0 = vertex0.x;
			}
			if (x0 > xmax)
			{
				return;
			}
			y0 = c - a * x0;
			
			x1 = xmax;
			if (vertex1 != null && vertex1.x < xmax)
			{
				x1 = vertex1.x;
			}
			if (x1 < xmin)
			{
				return;
			}
			y1 = c - a * x1;
			
			if ((y0 > ymax && y1 > ymax) || (y0 < ymin && y1 < ymin))
			{
				return;
			}
			
			if (y0 > ymax)
			{
				y0 = ymax; x0 = (c - y0)/a;
			}
			else if (y0 < ymin)
			{
				y0 = ymin; x0 = (c - y0)/a;
			}
			
			if (y1 > ymax)
			{
				y1 = ymax; x1 = (c - y1)/a;
			}
			else if (y1 < ymin)
			{
				y1 = ymin; x1 = (c - y1)/a;
			}
		}

		clippedEnds = new Hash<Point>();
		if (vertex0 == leftVertex)
		{
			clippedEnds.set(LR.LEFT.toString(), new Point(x0, y0));
			clippedEnds.set(LR.RIGHT.toString(), new Point(x1, y1));
		}
		else
		{
			clippedEnds.set(LR.RIGHT.toString(), new Point(x0, y0));
			clippedEnds.set(LR.LEFT.toString(), new Point(x1, y1));
		}
	}
	
}