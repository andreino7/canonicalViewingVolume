//
//  parser.cpp
//  Homework 02
//
//  Created by Andrea Rottigni on 18/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#include "parser.hpp"

Database::Database(std::string filepath) {
    parse(filepath);
    updateZmin();
}

void Database::updateZmin() {
    zmin = -(-prp[2]+F)/(-prp[2]+B);
}

std::list<std::string> Database::split(std::string original, std::string separator) {
    int firstIndex, secondIndex;
    std::list<std::string> result;
    firstIndex = 0;
    secondIndex = 0;
    while (secondIndex != std::string::npos) {
        secondIndex = int(original.find(separator));
        std::string tmp = original.substr(firstIndex, secondIndex);
        original = original.substr(secondIndex+1);
        result.push_back(tmp);
    }
    return result;
}

std::list<std::string> Database::readFileIntoLine(std::string filename) {
    std::string line;
    std::list<std::string> result;
    std::ifstream f (filename);
    //push every line of the file in a list of strings
    if (f.is_open()) {
        while ( std::getline (f,line) ) {
            result.push_back(line);
        }
        f.close();
    }
    return result;
}

Vec Database::create3DVector(std::list<std::string> words) {
    double coordinates[3];
    for (int i = 0; i < 3; i++) {
        coordinates[i] = std::stod(words.front());
        words.pop_front();
    }
    return Vec::initializedVec(coordinates, 3).toHomogeneous();
}

std::vector<Vec> Database::computeCoordinates(std::vector<double> coordinates) {
    std::vector<Vec> vertices;
    for (int i = 0; i < coordinates.size()-2; i=i+3) {
        double coord[] = {coordinates[i], coordinates[i+1], coordinates[i+2]};
        vertices.push_back(Vec::initializedVec(coord, 3).toHomogeneous());
    }
    return vertices;
}

std::vector<Vec> Database::computeCuboid(std::vector<double> elements) {
    double xmax = (elements[0]*2+elements[3])/2;
    double xmin = xmax - elements[3];
    double ymax = (elements[1]*2+elements[4])/2;
    double ymin = ymax - elements[4];
    double zmax = (elements[2]*2+elements[3])/2;
    double zmin = zmax - elements[3];
    std::vector<double> coord = {
        xmin, ymin, zmin,
        xmax, ymin, zmin,
        xmax, ymin, zmax,
        xmin, ymin, zmax,
        xmin, ymax, zmin,
        xmax, ymax, zmin,
        xmax, ymax, zmax,
        xmin, ymax, zmax
    };
    return computeCoordinates(coord);
}

std::vector<Vec> Database::computeCylinder(std::vector<double> elements) {
    double xcenter = elements[0];
    double ycenter = elements[1];
    double zcenter = elements[2];
    double radius = elements[3];
    double height = elements[4];
    std::vector<double> coordinates;
    for(int i=0; i<20; i++) {
        double angle = i * (2.0*M_PI/20);
        coordinates.push_back(cos(angle)*radius+xcenter);
        coordinates.push_back(ycenter);
        coordinates.push_back(sin(angle)*radius+zcenter);
        coordinates.push_back(cos(angle)*radius+xcenter);
        coordinates.push_back(ycenter+height);
        coordinates.push_back(sin(angle)*radius+zcenter);
    }
    return computeCoordinates(coordinates);
}

std::vector<Vec> Database::computeDoorPoints(std::vector<double> elements) {
    double xcenter = elements[12];
    double ycenter = elements[13];
    double zcenter = elements[14];
    double radius = elements[15];
    std::vector<double> coordinates;
    for (int i = 0; i < 12; i++) {
        coordinates.push_back(elements[i]);
    }
    for(int i=0; i<40; i++) {
        double angle = i * (2.0*M_PI/20);
        coordinates.push_back(xcenter);
        coordinates.push_back(sin(angle)*radius+ycenter);
        coordinates.push_back(cos(angle)*radius+zcenter);
    }
    return computeCoordinates(coordinates);
}

std::vector<double> Database::readPoints(std::list<std::string> words, int numberOfPoints) {
    std::vector<double> result = *new std::vector<double>(numberOfPoints);
    for (int i = 0; i < numberOfPoints; i++) {
        result[i] = std::stod(words.front());
        words.pop_front();
    }
    return result;
}

void Database::parse (std::string filename) {
    std::list<std::string> fileLines = readFileIntoLine(filename);
    //iterate over each line of the file
    for (std::list<std::string>::iterator it=fileLines.begin(); it != fileLines.end(); it++) {
        //split each line in words
        std::list<std::string> words = split((*it), " ");
        std::string firstWord = words.front();
        words.pop_front();
        //exploit the structure of the file to parse it.
        if (firstWord == "vrp") {
            vrp = create3DVector(words);
        } else if (firstWord == "vpn") {
            vpn = create3DVector(words);
        } else if (firstWord == "vup") {
            vup = create3DVector(words);
        } else if (firstWord == "prp") {
            prp = create3DVector(words);
        } else if (firstWord == "window") {
            umin = std::stoi(words.front());
            words.pop_front();
            vmin = std::stoi(words.front());
            words.pop_front();
            umax = std::stoi(words.front());
            words.pop_front();
            vmax = std::stoi(words.front());
            words.pop_front();
        } else if (firstWord == "F") {
            F = std::stoi(words.front());
        } else if (firstWord == "B") {
            B = std::stoi(words.front());
        } else if (firstWord == "room") {
            //put in the map the vertices of the house. Use the function readpoints to transform strings in double
            house["room"] = computeCoordinates(readPoints(words, 24));
        } else if (firstWord == "door") {
            house[firstWord] = computeDoorPoints(readPoints(words, 16));
        } else if (firstWord == "windowRoom") {
            house[firstWord] = computeCoordinates(readPoints(words, 24));
        } else if (firstWord == "tableCuboid") {
            house["table"] = computeCuboid(readPoints(words, 5));
        } else if (firstWord == "chandelier") {
            house["chandlier"] = computeCoordinates(readPoints(words, 18));
        } else if (firstWord == "tableCylinder") {
        house["tableCylinder"] = computeCylinder(readPoints(words, 5));
    }
    }
}

//I use this approsimation function to handle floating point imprecision
double approssimate(double value, double nearerInteger) {
    if (fabs(value - nearerInteger) < 0.001) {
        return nearerInteger;
    }
    return value;
}


void Database::transform(Matrix transformation) {
    //iterates over each element of the map
    for (std::map<std::string,std::vector<Vec>>::iterator it=house.begin(); it!=house.end(); ++it) {
        //the vector of vertices is given by the attribute second.
        std::vector<Vec> vertices = it->second;
        //transform each vertex applying the matrix
        for (int i = 0; i < vertices.size(); i++) {
            vertices[i] = transformation*vertices[i];
            for (int j = 0; j < vertices[i].getSize(); j++) {
                vertices[i][j] = approssimate(vertices[i][j], round(vertices[i][j]));
            }
        }
        //assign to the key pointed by the iterator the updated vertices
        house[it->first] = vertices;
    }
}




House Database::createHouse() {
    House result = *new House();
    result.addCube(house["room"]);
    result.addDoor(house["door"]);
    result.addWindow(house["windowRoom"]);
    result.addCube(house["table"]);
    result.addChandlier(house["chandlier"]);
    result.addCylinder(house["tableCylinder"]);
    return result;
}