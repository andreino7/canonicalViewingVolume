//
//  Illustrator.cpp
//  sampleapp
//
//  Created by Andrea Rottigni on 19/09/15.
//  Copyright (c) 2015 Andrea Rottigni. All rights reserved.
//

#include "Illustrator.hpp"


void plotLine(Vec firstPoint, Vec secondPoint) {
    glBegin(GL_LINES);
    glVertex2f(firstPoint[0], firstPoint[1]);
    glVertex2f(secondPoint[0], secondPoint[1]);
    glEnd();
}