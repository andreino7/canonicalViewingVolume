//
//  Illustrator.h
//  sampleapp
//
//  Created by Andrea Rottigni on 19/09/15.
//  Copyright (c) 2015 Andrea Rottigni. All rights reserved.
//

#ifndef __sampleapp__Illustrator__
#define __sampleapp__Illustrator__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>
#include "matrixLibrary.hpp"

#endif

/**
    Function that plots a point on the screen calling
    an open gl function
    @param x
    X coordinate of the point to be plotted
    @param y
    Y coordinate of the point to be plotted
 */
void plotLine(Vec firstPoint, Vec secondPoint);
