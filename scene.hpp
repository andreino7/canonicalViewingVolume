//
//  scene.hpp
//  Homework 02
//
//  Created by Andrea Rottigni on 18/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#ifndef scene_hpp
#define scene_hpp

#include <stdio.h>
#include "clipping.hpp"
#include "matrixLibrary.hpp"
#include "Illustrator.hpp"

/**
    This is the class tha represents line. Each line is basically composed by two points.
 */
class Line {
private:
    /**
        The two endpoints of the line.
     */
    Vec firstPoint, secondPoint;
    /**
        The state of the line after clipping. True if the line should be drawn, false otherwise.
     */
    bool accepted;
public:
    /**
        Public default constructor to create a line. It simply returns a new instance.
     */
    Line();
    /**
        Public constructor to create a line given two endpoints. It returns a line composed by the two endpoints.
        @param firstPoint the first endpoint
        @param secondPoint the second endpoint
     */
    Line(Vec firstPoint, Vec secondPoint);
    /**
        Getter method that returns the first endpoint
     */
    Vec getFirstPoint();
    /**
        Getter method that returns the second endpoint
     */
    Vec getSecondPoint();
    /**
        Setter method that sets the endpoints
        @param firstPoint the first endpoint
        @param secondPoint the second endpoint
     */
    void setPoints(Vec firstPoint, Vec secondPoint);
    /**
        Setter method that sets the endpoints in a 2D format
        @param firstPoint the first endpoint
        @param secondPoint the second endpoint
     */
    void setPoints2D(Vec firstPoint, Vec secondPoint);
    /**
        Method used to clipe the line in 3D.
        @param zmin the z coordinate of the front clipping plane.
     */
    void clipLine(double zmin);
    /**
        Method used to draw the line
     */
    void drawLine();
};

/**
    The class shape it's the superclass of each figure that is present in the final scene. It's subclasses are: cube, rectangle, cylinder, chandlier
 */
class Shape {
protected:
    /**
        Vector that contains the vertices of the shape.
     */
    std::vector<Vec> vertices;
    /**
        Vector that contains the edges of the shape.
     */
    std::vector<Line> edges;
public:
    /**
        Public constructor which return a new instance of shape after having computed all the edges.
        @param vertices the vertices of the shape.
     */
    Shape(std::vector<Vec> vertices);
    /**
        Method used to clip the shape in 3D.
        @param zmin the z coordinate of the front clipping plane
     */
    void clipShape(double zmin);
    /**
        Getter method for the edges of the shape
     */
    std::vector<Line> getEdges();
    /**
        Getter method for the vertices of the shape
     */
    std::vector<Vec> getVertices();
    /**
        Method to transorm a shape by multiplying the matrix passed as parameter with each vertex.
     */
    void transformShape(Matrix transformation);
    /**
        Method to transorm a shape by multiplying the matrix passed as parameter with each vertex in a 2D space.
     */
    void transformShape2D(Matrix transformation);
    /**
        Method used to draw the shape.
     */
    void draw();
};

/**
    Class that represents rectangle. It's a subclass of Shape class. Its subclasses are Window and Door.
 */
class Rectangle: public Shape {
private:
    /**
        Private method to appropriately generate all the edges of the rectangle from the vertices.
     */
    void generateEdges();
public:
    /**
        Public constructor of class rectangle. It calls the constructor of the super class shape and then calls the generateEdges method to generate the edges of the rectangle.
     */
    Rectangle(std::vector<Vec> vertices);
};

/**
    Class that represents a window. It's a subclass of Rectangle class.
 */
class Window: public Rectangle {
private:
    /**
        Private method to appropriately generate all the edges of the window from the vertices.
     */
    void generateEdges();
public:
    /**
        Public constructor of class window. It calls the constructor of the super class rectangle and then calls the generateEdges method to generate the edges of the rectangle. It is a subclass of rectangle because it has to generate also the two horizontal line inside the window.
     */
    Window(std::vector<Vec> vertices);
};

/**
    Class that represents a door. It's a subclass of Rectangle class.
 */
class Door: public Rectangle {
private:
    /**
        Private method to appropriately generate all the edges of the door from the vertices.
     */
    void generateEdges();
public:
    /**
        Public constructor of class Door. It calls the constructor of the super class rectangle and then calls the generateEdges method to generate the edges of the rectangle. It is a subclass of rectangle because it has to generate also door knob.
     */
    Door(std::vector<Vec> vertices);
};

/**
    Class that represents a cube. It's a subclass of Shape class.
 */
class Cube : public Shape {
private:
    /**
        number of edges in a cube.
     */
    int numberOfEdges = 12;
    /**
        Private method to appropriately generate all the edges of the cube from the vertices.
     */
    void generateEdges();
public:
    /**
        Public constructor of class cube. It calls the constructor of the super class shape and then calls the generateEdges method to generate the edges of the cube.
     */
    Cube(std::vector<Vec> vertices);
};

/**
    Class that represents a cylinder. It's a subclass of Shape class.
 */
class Cylinder : public Shape {
private:
    /**
        Private method to appropriately generate all the edges of the cylinder from the vertices.
     */
    void generateEdges();
public:
    /**
        Public constructor of class Cylinder. It calls the constructor of the super class shape and then calls the generateEdges method to generate the edges of the cylinder.
     */
    Cylinder(std::vector<Vec> vertices);
};

/**
    Class that represents a chandlier. It's a subclass of Shape class.
 */
class Chandlier : public Shape {
private:
    /**
        Private method to appropriately generate all the edges of the chandlier from the vertices.
     */
    void generateEdges();
public:
    /**
        Public constructor of class chandlier. It calls the constructor of the super class shape and then calls the generateEdges method to generate the edges of the chandlier.
     */
    Chandlier(std::vector<Vec> vertices);
};


/**
    Class that represents the House. It contains a set of shapes that constitutes the house.
 */
class House {
private:
    /**
        Vector of that contains all the shapes of the house.
     */
    std::vector<Shape *> shapes;
public:
    /**
        Method to clip the house in 3D
     */
    void clip(double zmin);
    /**
        Method to apply the transformation matrix to all the shapes that constitutes the house.
     */
    void transform(Matrix transformation);
    /**
        Method to apply the transformation matrix to all the shapes that constitutes the house in 2D.
     */
    void transform2D(Matrix transformation);
    /**
        Method to add the door to the house.
     */
    void addDoor(std::vector<Vec> coordinates);
    /**
        Method to add the chandlier to the house.
     */
    void addChandlier(std::vector<Vec> coordinates);
    /**
        Method to add the table to the house.
     */
    void addCube(std::vector<Vec> coordinates);
    /**
        Method to add the window to the house.
     */
    void addWindow(std::vector<Vec> coordinates);
    /**
        Method to add the table's leg to the house.
     */
    void addCylinder(std::vector<Vec> coordinates);
    /**
        Method to draw house.
     */
    void draw();
};

#endif /* scene_hpp */
