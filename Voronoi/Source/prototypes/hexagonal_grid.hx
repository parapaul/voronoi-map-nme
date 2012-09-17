// Make a map out of a hexagonal grid
// Author:amitp@cs.stanford.edu
// License:MIT

package;

  import flash.geom.*;
  import nme.display.*;
  import flash.events.*;
  
  class hexagonal_grid extends Sprite {
public function hexagonal_grid(){
  stage.scaleMode='noScale';
  stage.align='TL';

  go();

  stage.addEventListener(MouseEvent.CLICK, function(e:MouseEvent):Void { go();});
}

public function go():Void {
  graphics.clear();
  graphics.beginFill(0x999999);
  graphics.drawRect(-1000, -1000, 2000, 2000);
  graphics.endFill();

  var edges:Array<Dynamic>=[];
  
  function valid1(i:Int, j:Int):Bool {
	return(i>=0)&&(i<11)
	  &&(j>=0)&&(j<11)
	  &&(i + j>=5)&&(i + j<16);
  }

  function valid(i:Int, j:Int):Bool {
	var p:Point=coordinateToPoint(i, j).subtract(new Point(300, 250));
	var angle:Float=Math.atan2(p.y, p.x);
	var r1:Float=200 + 50*Math.sin(5*angle);
	var r2:Float=200 + 100*Math.sin(5*angle + 0.5);
	return p.length<r1 ||(p.length>=30+r1 && p.length<r2);
  }
  
  function maybeAddEdge(i1:Int, j1:Int, i2:Int, j2:Int):Void {
	if(valid(i2, j2)){
	  edges.push({i1:i1, j1:j1, i2:i2, j2:j2});
	}
  }

  for(var i:Int=-5;i<15;i++){
	for(var j:Int=-5;j<15;j++){
	  var p:Point=coordinateToPoint(i, j);
	  if(valid(i, j)){
		graphics.beginFill(0xff0000);
		graphics.drawCircle(p.x, p.y, 4);
		graphics.endFill();
		maybeAddEdge(i, j, i+1, j);
		maybeAddEdge(i, j, i, j+1);
		maybeAddEdge(i, j, i+1, j-1);
	  }
	}
  }

  function drawNoisyLine(p:Point, q:Point):Void {
	var pv:Vector3D=new Vector3D(p.x, p.y);
	var qv:Vector3D=new Vector3D(q.x, q.y);
	var p2q:Vector3D=qv.subtract(pv);
	var perp:Vector3D=new Vector3D(0.4*p2q.y, -0.4*p2q.x);
	var pq:Vector3D=new Vector3D(0.5*(p.x+q.x), 0.5*(p.y+q.y));
	noisy_line.drawLine(graphics, pv, pq.add(perp), qv, pq.subtract(perp));
  }
  
  for(var edge:Dynamic in edges){
	  drawNoisyLine(coordinateToPoint(edge.i1, edge.j1),
					coordinateToPoint(edge.i2, edge.j2));
	}
}

public static function coordinateToPoint(i:Int, j:Int):Point {
  return new Point(20 + 50*i + 25*j + 3.7*(i % 3)+ 2.5*(j % 4), 10 + 50*j + 3.7*(j % 3)+ 2.5*(i % 4));
}
  }