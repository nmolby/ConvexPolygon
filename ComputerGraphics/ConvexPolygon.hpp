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
    /**
     Creates a ConvexPolygon
     @param points The points that the convex polygon contains
     @param color The color that the convex polygon will be drawn with
     @param scaleX The x scale of the polygon
     @param scaleY The y scale of the polygon
     @param translateX The x translate of the polygon
     @param translateY The y translate of the polygon
     @param rotateDeg The rotation, in degrees, of the polygon
     */
    ConvexPolygon(const std::vector<Point3D> &points = std::vector<Point3D>(), const Color &color = Color(0, 0, 0), const float scaleX = 1, const float scaleY = 1, const float translateX = 0, const float translateY = 0, const float rotateDeg = 0);
    
    /**
     Sets the instance variables of a ConvexPolygon
     @param points The points that the convex polygon contains
     @param color The color that the convex polygon will be drawn with
     @param scaleX The x scale of the polygon
     @param scaleY The y scale of the polygon
     @param translateX The x translate of the polygon
     @param translateY The y translate of the polygon
     @param rotateDeg The rotation, in degrees, of the polygon
     @return None
     */
    void set(const std::vector<Point3D> &points, const Color &color = Color(0, 0, 0), const float scaleX = 1, const float scaleY = 1, const float translateX = 0, const float translateY = 0, const float rotateDeg = 0);
    
    /**
     Renders the ConvexPolygon in the renderer
     @param renderer The renderer to render the convex polygon in
     */
    void render(Renderer *renderer);

    /**
     Returns the center point of the ConvexPolygon
     @return The center point of the ConvexPolygon
     */
    Point3D centerPoint() const;
private:
    /**
     Gets the points of the polygon after applying scale, translate, and rotation.
     @return The vector of the altered points
     */
    std::vector<Point3D> getAlteredPoints();
    
    size_t _vertexCount;
    float _scaleX, _scaleY, _translateX, _translateY, _rotateDeg;
    Color _color;
    std::vector<Point3D> _points;

};

/**
 Reads an istream into a Polygon
 @param is The istream to read from
 @param polygon The polygon to read into
 @return The same istream that was read from
 */
std::istream& operator>>(std::istream &is, ConvexPolygon &polygon);


#endif /* ConvexPolygon_hpp */
