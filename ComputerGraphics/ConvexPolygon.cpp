//
//  ConvexPolygon.cpp
//  ComputerGraphics
//
//  Created by David M. Reed on 1/28/20.
//  Copyright © 2020 David M Reed. All rights reserved.
//

#include "ConvexPolygon.hpp"


ConvexPolygon::ConvexPolygon(const std::vector<Point3D> &points, const Color &color, const float scaleX, const float scaleY, const float translateX, const float translateY, const float rotateDeg){
    set(points, color, scaleX, scaleY, translateX, translateY, rotateDeg);
}

void ConvexPolygon::set(const std::vector<Point3D> &points, const Color &color, const float scaleX, const float scaleY, const float translateX, const float translateY, const float rotateDeg){
    
    _points = points;
    _color = color;
    _scaleX = scaleX;
    _scaleY = scaleY;
    _translateX = translateX;
    _translateY = translateY;
    _rotateDeg = rotateDeg;
}

void ConvexPolygon::render(Renderer *renderer) {
    std::vector<Point3D> newPoints = getAlteredPoints();
    
    renderer->addPoints(newPoints, _color);
}

Point3D ConvexPolygon::centerPoint() const { 
    float totX = 0, totY = 0;
    
    for(int i = 0; i < _points.size(); i++){
        totX += _points[i].x;
        totY += _points[i].y;
    }
    
    return Point3D(totX / _points.size(), totY / _points.size());
}

std::vector<Point3D> ConvexPolygon::getAlteredPoints() {
    std::vector<Point3D> newPoints;
    
    //translates each point to be around the origin
    mat3 transtoOrig = mat3(1, 0, -1 * centerPoint().x,
                            0, 1, -1 * centerPoint().y,
                            0, 0, 1);
    
    //scales each point
    mat3 scale = mat3(_scaleX, 0, 0,
                      0, _scaleY, 0,
                      0, 0, 1);
    
    //rotates each point
    mat3 rot = mat3(cos(DegreesToRadians * _rotateDeg), -1*sin(DegreesToRadians * _rotateDeg), 0,
                    sin(DegreesToRadians * _rotateDeg), cos(DegreesToRadians * _rotateDeg), 0,
                    0, 0, 1);
    
    //translates the point from the user
    mat3 transFromUser = mat3(1, 0, _translateX,
                      0, 1, _translateY,
                      0, 0, 1);
    
    //translate the point back to its initial position
    mat3 transBack = mat3(1, 0, centerPoint().x,
                            0, 1, centerPoint().y,
                            0, 0, 1);
    
    //order of events:
    //translate to origin
    //scale & rotate
    //translate given
    //translate back to initial position
    mat3 finalTrans = transBack * transFromUser * rot * scale * transtoOrig;
    
    for(Point3D origPoint: _points ){
        vec3 initialPoint = vec3(origPoint.x, origPoint.y, 1);
        
        //applies all of the transformations to point
        vec3 finalPoint = finalTrans * initialPoint;
        
        //adds the transformed point to the list of points
        newPoints.push_back(Point3D(float(finalPoint[0]), float(finalPoint[1]), 0.0));
    }
    
    return newPoints;
}

std::istream& operator>>(std::istream &is, ConvexPolygon &myPolygon) {
    float r, g, b, xScale, yScale, xTranslate, yTranslate, rotateAmount;
    int vertexCount;
    
    is >> vertexCount;
    
    
    std::vector<Point3D> points;
    
    for(int i = 0; i < vertexCount; i++){
        float x, y;
        is >> x >> y;
        Point3D newPoint = Point3D(x, y);
        points.push_back(newPoint);
    }

    is >> r >> g >> b >> xScale >> yScale >> xTranslate >> yTranslate >> rotateAmount;
    Color color(r, g, b);
    
    myPolygon.set(points, color, xScale, yScale, xTranslate, yTranslate, rotateAmount);
    return is;
}
