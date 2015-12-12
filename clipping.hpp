//
//  clipping.hpp
//  Homework 02
//
//  Created by Andrea Rottigni on 17/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#ifndef clipping_hpp
#define clipping_hpp

#include <stdio.h>
#include "matrixLibrary.hpp"

#endif /* clipping_hpp */
/** 
    type usedo to compute the outcodes of the cohen-sutherland algorithm
 */
typedef unsigned int outcode;
/**
    Enum that associates each possible position of one points with bitcodes
 */
enum {ABOVE = 0x1, BELOW = 0x2, RIGHT = 0x4, LEFT = 0x8, BEHIND = 0x10, INFRONT = 0x20};

/**
    Implementation of the Cohen-Sutherland algorithm, adjusted to handle 3D.
    @param firstPoint the first endpoint of the line
    @param secondPoint the second endpoint of the line
    @param zmin the distance of the front clipping plane
 */
bool clip3D(Vec &firstPoint, Vec &secondPoint, double zmin);