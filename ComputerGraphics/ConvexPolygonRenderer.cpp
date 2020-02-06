//
//  ConvexPolygonRenderer.cpp
//  ComputerGraphics
//
//  Created by Nathan Molby on 2/6/20.
//  Copyright © 2020 Nathan Molby All rights reserved.
//


#include <fstream>
#include "ConvexPolygon.hpp"
#include "ConvexPolygonRenderer.hpp"


ConvexPolygonRenderer::ConvexPolygonRenderer(std::string windowTitle, int width, int height, std::string filename) : Renderer(windowTitle, width, height){
    
    std::ifstream infile(filename.c_str());
    ConvexPolygon polygon;
    
    // while not end of file read Rectangle objects from file stream
    while (infile >> polygon) {
        // render it
        polygon.render(this);
        // store it in case we want to use it in the future
        _polygons.push_back(polygon);
        
    }
    infile.close();
}


