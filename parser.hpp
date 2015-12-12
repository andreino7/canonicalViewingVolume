//
//  parser.hpp
//  Homework 02
//
//  Created by Andrea Rottigni on 18/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include "scene.hpp"
#include <fstream>
#include <list>
#include <map>
#endif /* parser_hpp */

/**
    This class represents the database of points that is loaded in memory when the program is first loaded. It parses a file containig the points to generate all the shapes. It also handle transformations that happens in the world coordinate system.
 */
class Database {
private:
    /**
        Function that returns a 3D vector from a list of strings.
        @param words a list containing a string representation of the vertices.
     */
    Vec create3DVector(std::list<std::string> words);
    /**
        Function that returns a list of string that corresponds to the line of the file.
        @param filename the path to the file.
     */
    std::list<std::string> readFileIntoLine(std::string filename);
    /**
        Function that returns a list of string that corresponds to the original splitted on the splitting character
        @param original the starting string
        @param separator the string on which separate the original string
     */
    std::list<std::string> split(std::string original, std::string separator);
    /**
        Function that creates a vector of Vec from a vector of double.
        @param coordinates a vector containing a sequence of numbers.
     */
    std::vector<Vec> computeCoordinates(std::vector<double> coordinates);
    /**
        Function that creates a vector of Vec for the cuboid element from a vector of double.
        @param elements a vector containing a sequence of numbers.
     */
    std::vector<Vec> computeCuboid(std::vector<double> elements);
    /**
        Function that creates a vector of Vec for the cylinder element from a vector of double.
        @param elements a vector containing a sequence of numbers.
     */
    std::vector<Vec> computeCylinder(std::vector<double> elements);
    /**
        Function that creates a vector of Vec for the door element from a vector of double.
        @param elements a vector containing a sequence of numbers.
     */
    std::vector<Vec> computeDoorPoints(std::vector<double> elements);
    /**
        Function that creates a vector of double from a list of strings, given the number of double that must be generated
        @param words the list of string
        @param numberOfPoints the number of double to generate
     */
    std::vector<double> readPoints(std::list<std::string> words, int numberOfPoints);
public:
    /**
        All the parameters that defines the VRC system
     */
    Vec vrp, vpn, vup, prp;
    double umin, umax, vmin, vmax, zmin;
    int F, B;
    /**
        A map between strings and vector of the. It associates it's object of the house to a set of vertices.
     */
    std::map<std::string, std::vector<Vec>> house;

    /**
        Constructor that returns an instance of the newly created dabase using the given filepath
        @param filepath the path to the file
     */
    Database(std::string filepath);
    /**
        Method to update the value of zmin, the front clipping plane.
     */
    void updateZmin();
    /**
        Method used to parse the file specified as parameter.
        @param filename the path to the file.
     */
    void parse (std::string filename);
    /**
        Method used to apply the transformation matrix to all the points in the db
        @param transformation the trasnformation to apply to the points.
     */
    void transform(Matrix transformation);
    /**
        Method used to creates the house, using the map instance variable.
     */
    House createHouse();
};
