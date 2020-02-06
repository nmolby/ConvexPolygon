//
//  ConvexPolygonRenderer.hpp
//  ComputerGraphics
//
//  Created by David M. Reed on 1/28/20.
//  Copyright © 2020 David M Reed. All rights reserved.
//

#ifndef ConvexPolygonRenderer_hpp
#define ConvexPolygonRenderer_hpp

#include "ConvexPolygon.hpp"
#include "graphics.hpp"


class ConvexPolygonRenderer: public Renderer {
public:
    /// Renderer subclass for reading and rendering Rectangles
    /// @param window GLFW window
    /// @param filename filename containing Rectangle data
    ConvexPolygonRenderer(std::string windowTitle, int width, int height, std::string filename);

    virtual ~ConvexPolygonRenderer() noexcept {}


    
private:
    std::vector<ConvexPolygon> _polygons;
    
    
};

#endif /* ConvexPolygonRenderer_hpp */
