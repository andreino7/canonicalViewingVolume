//
//  clipping.cpp
//  Homework 02
//
//  Created by Andrea Rottigni on 17/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#include "clipping.hpp"

//function that given the coordinates of a point and of the fron clipping plane it combute the outcodes. It simply checks all the condition (taken from the book) and assigns the appropriate outcode
outcode computOutcode(double x, double y, double z, double zmin) {
    outcode code = 0;
    if (y > -z) {
        //a bitwise or is used to compute the outcode.
        code |= ABOVE;
    } else {
        if (y < z) {
            code |= BELOW;
        }
    }
    if (x > -z) {
        code |= RIGHT;
    } else {
        if (x < z) {
            code |= LEFT;
        }
    }
    if (z < -1) {
        code |= BEHIND;
    } else {
        if (z > zmin) {
            code |= INFRONT;
        }
    }
    return code;
}

//function that computes the intersection point given one point of the line and the parameter t
double computeIntersectionCoordinate(double p0, double p1, double t) {
    double result;
    //apply the formula taken from basic geometry.
    result = p0 + t*(p1-p0);
    return result;
}

bool clip3D(Vec &firstPoint, Vec &secondPoint, double zmin) {
    //converts the two points in cartesian coordinates to apply cohen-sutherland
    firstPoint = firstPoint.toCartesian();
    secondPoint = secondPoint.toCartesian();
    double x0 = firstPoint[0], y0 = firstPoint[1], z0 = firstPoint[2], x1 = secondPoint[0], y1 = secondPoint[1], z1 = secondPoint[2];
    //compute the outcodes of the two endpoints
    outcode outcode0 = computOutcode(x0, y0, z0, zmin);
    outcode outcode1 = computOutcode(x1, y1, z1, zmin);
    outcode outcodeOut;
    //initialize accept and done to false. accept symbolizes if the line should be drawn or not.
    bool accept = false;
    bool done = false;
    do {
        //checks if the line can be trivially accepted: bitwise or must be 0
        if (!(outcode0|outcode1)) {
            accept = true;
            done = true;
        //checks if the line can be trivially rejected: bitwise and must be != 0
        } else if (outcode0 & outcode1) {
            done = true;
        } else {
            double x, y, z, t;
            //if we are here at least one outcode must be different from 0. Assign that outcode to outcode out.
            outcodeOut = outcode0 ? outcode0 : outcode1;
            //performs a bitwise and with all possible situations (ABOVE, BELOW etc) and when the result of the and is true, compute the intersection of the line.
            if (outcodeOut & ABOVE) {
                t = (-y0-z0)/(y1-y0+z1-z0);
                x = computeIntersectionCoordinate(x0, x1, t);
                y = computeIntersectionCoordinate(y0, y1, t);
                z = -y;
            } else if (outcodeOut & BELOW) {
                t = (z0-y0) / (y1-y0-z1+z0);
                x = computeIntersectionCoordinate(x0, x1, t);
                y = computeIntersectionCoordinate(y0, y1, t);
                z = y;
            } else if (outcodeOut & RIGHT) {
                t = (-x0-z0)/(x1-x0+z1-z0);
                x = computeIntersectionCoordinate(x0, x1, t);
                y = computeIntersectionCoordinate(y0, y1, t);
                z = -x;
            } else if (outcodeOut & LEFT) {
                t = (z0-x0) / (x1-x0-z1+z0);
                x = computeIntersectionCoordinate(x0, x1, t);
                y = computeIntersectionCoordinate(y0, y1, t);
                z = x;
            } else if (outcodeOut & BEHIND) {
                z = -1;
                t = (z-z0)/(z1-z0);
                x = computeIntersectionCoordinate(x0, x1, t);
                y = computeIntersectionCoordinate(y0, y1, t);
            } else {
                z = zmin;
                t = (z-z0)/(z1-z0);
                x = computeIntersectionCoordinate(x0, x1, t);
                y = computeIntersectionCoordinate(y0, y1, t);
            }
            //assign the new coordinates to the point with the outcode equals to outcode out
            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                z0 = z;
                outcode0 = computOutcode(x0, y0, z0, zmin);
            } else {
                x1 = x;
                y1 = y;
                z1 = z;
                outcode1 = computOutcode(x1, y1, z1, zmin);
            }
        }
    } while (done == false); //repeat until the variable done is equal to false
    //checks if the line can be accepted
    if (accept) {
        //if true updates the endpoints
        double coordinates0[] = {x0, y0, z0};
        double coordinates1[] = {x1, y1, z1};
        firstPoint = Vec::initializedVec(coordinates0, 3);
        secondPoint = Vec::initializedVec(coordinates1, 3);
    }
    //transforms back points into homogeneous coordinate
    firstPoint = firstPoint.toHomogeneous();
    secondPoint = secondPoint.toHomogeneous();
    //return the state of the line
    return accept;
}