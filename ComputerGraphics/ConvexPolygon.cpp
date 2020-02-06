//
//  ConvexPolygon.cpp
//  ComputerGraphics
//
//  Created by Nathan Molby on 2/6/20.
//  Copyright © 2020 Nathan Molby All rights reserved.
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
    std::vector<Point3D> pointsToDraw;
    float minY = newPoints[0].y, maxY = newPoints[0].y;
    
    for(Point3D point: newPoints){
        if(point.y > maxY)
            maxY = point.y;
        if(point.y < minY)
            minY = point.y;
    }
    
    std::cout << minY << std::endl << maxY;
    

    
    for(int y = std::ceil(minY); y <= std::floor(maxY); y++){
        bool x1Init = false;
        int x1, x2;
        float t, x;
        
        for(int i = 0; i < newPoints.size() - 1; i++){
            //if the current y is between the next point and this point but not equal to BOTH of them
            if(((newPoints[i].y <= y && y <= newPoints[i + 1].y) ||
                (newPoints[i].y >= y && y >= newPoints[i + 1].y)) &&
               !(newPoints[i].y == y && y == newPoints[i + 1].y)){
                t = (y - newPoints[i].y) / (newPoints[i + 1].y - newPoints[i].y);
                
                x = (newPoints[i + 1].x - newPoints[i].x) * t + newPoints[i].x;
                
                if(!x1Init){
                    x1 = x;
                    x1Init = true;
                } else{
                    x2 = x;
                }
            }
        }
        
        //if the current y is between the first point and last point but not equal to BOTH of them
        if(((newPoints[0].y <= y && y <= newPoints[newPoints.size() - 1].y) ||
            (newPoints[0].y >= y && y >= newPoints[newPoints.size() - 1].y)) &&
           !(newPoints[0].y == y && y == newPoints[newPoints.size() - 1].y))
        {
            t = (y - newPoints[0].y) / (newPoints[newPoints.size() - 1].y - newPoints[0].y);
            
            x = (newPoints[newPoints.size() - 1].x - newPoints[0].x) * t + newPoints[0].x;
            
            if(!x1Init){
                x1 = x;
                x1Init = true;
            } else{
                x2 = x;
            }
        }
        
        int minX = x1 < x2 ? x1 : x2;
        int maxX = x1 > x2 ? x1 : x2;
        
        for(int x = minX; x <= maxX; x++){
            pointsToDraw.push_back(Point3D(x, y));
        }
        
    }
    
    renderer->addPoints(pointsToDraw, _color);
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
