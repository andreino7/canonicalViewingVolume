//
//  scene.cpp
//  Homework 02
//
//  Created by Andrea Rottigni on 18/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#include "scene.hpp"

Line::Line() {
    
}

Line::Line(Vec firstPoint, Vec secondPoint) {
    this->firstPoint = firstPoint;
    this->secondPoint = secondPoint;
}

Vec Line::getFirstPoint() {
    return firstPoint;
}

Vec Line::getSecondPoint() {
    return secondPoint;
}

void Line::clipLine(double zmin) {
    //set the state of the line to the state returned by the clipping procedure
    accepted = clip3D(firstPoint, secondPoint, zmin);
}

void Line::setPoints(Vec firstPoint, Vec secondPoint) {
    this->firstPoint = firstPoint;
    this->secondPoint = secondPoint;
}


void Line::setPoints2D(Vec firstPoint, Vec secondPoint) {
        this->firstPoint = firstPoint;
        this->secondPoint = secondPoint;
}

void Line::drawLine() {
    if (accepted) {
        plotLine(firstPoint, secondPoint);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
Shape::Shape(std::vector<Vec> vertices) {
    this->vertices = vertices;
}


std::vector<Line> Shape::getEdges() {
    return edges;
}

std::vector<Vec> Shape::getVertices() {
    return vertices;
}

void Shape::clipShape(double zmin) {
    for (int i = 0; i < edges.size(); i++) {
        edges[i].clipLine(zmin);
    }
}

void Shape::transformShape(Matrix transformation) {
    //for each line multiply each line endpoint with the transformation matrix and update the endpoints.
    for (int i = 0; i < edges.size(); i++) {
        Vec firstPoint = edges[i].getFirstPoint();
        Vec secondPoint = edges[i].getSecondPoint();
        firstPoint = transformation*firstPoint;
        secondPoint = transformation*secondPoint;
        edges[i].setPoints(firstPoint, secondPoint);
    }
}

void Shape::transformShape2D(Matrix transformation) {
    //for each line multiply each line endpoint transformed into 2D coordinate with the transformation matrix and update the endpoints.
    for (int i = 0; i < edges.size(); i++) {
        Vec firstPoint = edges[i].getFirstPoint().toCartesian().from3Dto2D().toHomogeneous();
        Vec secondPoint = edges[i].getSecondPoint().toCartesian().from3Dto2D().toHomogeneous();
        firstPoint = transformation*firstPoint;
        secondPoint = transformation*secondPoint;
        edges[i].setPoints(firstPoint, secondPoint);
    }
}

void Shape::draw() {
    for (int i = 0; i < edges.size(); i++) {
        edges[i].drawLine();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

Cylinder::Cylinder(std::vector<Vec> vertices) : Shape(vertices) {
    generateEdges();
}

void Cylinder::generateEdges() {
    edges = *new std::vector<Line>(60);
    //generate each line that composes the cylinder exploiting how they are stored in the the vertices vector.
    for (int i = 0; i < 20; i++) {
        edges[i] = *new Line(vertices[i*2], vertices[i*2+1]);
        edges[i+20] = *new Line(vertices[i], vertices[i+2]);
        edges[i+40] = *new Line(vertices[(i+20)%40], vertices[(i+22)%40]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

Cube::Cube(std::vector<Vec> vertices) : Shape(vertices) {
    generateEdges();
}

void Cube::generateEdges() {
    edges = *new std::vector<Line>(numberOfEdges);
    //generate each line that composes the cube exploiting how they are stored in the the vertices vector.
    for (int i = 0; i < 4; i++) {
        edges[i] = *new Line(vertices[i], vertices[(i+1)%4]);
        edges[i+4] = *new Line(vertices[i+4], vertices[((i+1)%4)+4]);
        edges[i+8] =  *new Line(vertices[i], vertices[(i+4)]);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
Window::Window(std::vector<Vec> vertices) : Rectangle(vertices) {
    generateEdges();
}

void Window::generateEdges() {
        //generate each line that composes the window exploiting how they are stored in the the vertices vector. Most of the work is accomplished by the super class
    for (int i = 4; i < 7; i=i+2) {
        edges.push_back(*new Line(vertices[i], vertices[i+1]));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
Door::Door(std::vector<Vec> vertices) : Rectangle(vertices) {
    generateEdges();
}

void Door::generateEdges() {
        //generate each line that composes the door exploiting how they are stored in the the vertices vector. Most of the work is accomplished by the superclass
    for (int i = 0; i < 40; i++) {
        edges.push_back(*new Line(vertices[i+4], vertices[(i+1)%40 + 4]));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
Rectangle::Rectangle(std::vector<Vec> vertices) : Shape(vertices) {
    generateEdges();
}


void Rectangle::generateEdges() {
    edges = *new std::vector<Line>(4);
    //generate each line that composes the rectangle exploiting how they are stored in the the vertices vector.
    for (int i = 0; i < 4; i++) {
        edges[i] = *new Line(vertices[i], vertices[(i+1)%4]);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
Chandlier::Chandlier(std::vector<Vec> vertices) : Shape(vertices) {
    generateEdges();
}

void Chandlier::generateEdges() {
    edges = *new std::vector<Line>(9);
    //generate each line that composes the chandlier exploiting how they are stored in the the vertices vector.
    for (int i = 0; i < 4; i++) {
        edges[i] = *new Line(vertices[i], vertices[(i+1)%4]);
        edges[i+4] = *new Line(vertices[vertices.size()-1], vertices[i]);
    }
    edges[8] = *new Line(vertices[vertices.size()-1], vertices[vertices.size()-2]);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void House::addCube(std::vector<Vec> coordinates) {
    Cube *c = new Cube(coordinates);
    shapes.push_back(c);
}

void House::addChandlier(std::vector<Vec> coordinates) {
    Chandlier *c = new Chandlier(coordinates);
    shapes.push_back(c);
}

void House::addCylinder(std::vector<Vec> coordinates) {
    Cylinder *c = new Cylinder(coordinates);
    shapes.push_back(c);
}

void House::addWindow(std::vector<Vec> coordinates) {
    Window *w = new Window(coordinates);
    shapes.push_back(w);
}

void House::addDoor(std::vector<Vec> coordinates) {
    Door *d = new Door(coordinates);
    shapes.push_back(d);
}

void House::draw() {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
}

void House::clip(double zmin) {
    //for each shape call the clip function
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->clipShape(zmin);
    }
}

void House::transform(Matrix transformation) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->transformShape(transformation);
    }
}

void House::transform2D(Matrix transformation) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->transformShape2D(transformation);
    }
}

