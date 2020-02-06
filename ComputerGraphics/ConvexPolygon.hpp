//
//  ConvexPolygon.hpp
//  ComputerGraphics
//
//  Created by Nathan Molby on 2/6/20.
//  Copyright © 2020 Nathan Molby All rights reserved.
//

#ifndef ConvexPolygon_hpp
#define ConvexPolygon_hpp

#include <iostream>

#include "graphics.hpp"

class ConvexPolygon {
public:
    ConvexPolygon(const std::vector<Point3D> &points = std::vector<Point3D>(), const Color &color = Color(0, 0, 0), const float scaleX = 1, const float scaleY = 1, const float translateX = 0, const float translateY = 0, const float rotateDeg = 0);
    
    void set(const std::vector<Point3D> &points, const Color &color = Color(0, 0, 0), const float scaleX = 1, const float scaleY = 1, const float translateX = 0, const float translateY = 0, const float rotateDeg = 0);
    
    void render(Renderer *renderer);
    
    /// returns center point of Polygon
    Point3D centerPoint() const;
private:
    
    std::vector<Point3D> getAlteredPoints();
    
    size_t _vertexCount;
    float _scaleX, _scaleY, _translateX, _translateY, _rotateDeg;
    Color _color;
    std::vector<Point3D> _points;

};

std::istream& operator>>(std::istream &is, ConvexPolygon &polygon);


#endif /* ConvexPolygon_hpp */
