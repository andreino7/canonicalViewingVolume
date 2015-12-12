//
//  Library.hpp
//  Homework 02
//
//  Created by Andrea Rottigni on 13/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#ifndef Library_hpp
#define Library_hpp
#define SIZE3D 4

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>


/**
    This is the class used to generate vectors and define operations on them.
 **/
class Vec {
private:
    /**
        The number of elements in the vector
     */
    int size;
    /**
        The elements of the vector
     */
    std::vector<double> coordinates;
    /**
        Private constructor to create a new vector.
        @param size the size of the vector.
     */
    Vec(int size);
public:
    /**
        Default public constructor to create a new vector.
     */
    Vec();
    /**
        Method to return the number of elements in the vector
     */
    int getSize();
    /**
        Static method to initialize a vector with all zeroes. It returns the newly created instance.
        @param size the size of the vector
     */
    static Vec zeroesVec(int size);
    /**
        Method to initialize a vector with the elements passed as parameters. It returns the newly 
        created instance.
        @param elements an array containing the elements
        @size the size of the vector
     */
    static Vec initializedVec(double *elements, int size);
    /**
        Method to compare two vectors. It returns true if the vectors are equivalent, false otherwise.
        @param other the other vector of the comparison.
     */
    bool compareVector (Vec other);
    /**
        Method used to print a vector.
     */
    void print();
    /**
        Method that returns the norm of the vector.
     */
    double norm();
    /**
        Method to scale a vector. It returns a new vector which is the result of the scaling.
        @param scale the scale factor.
     */
    Vec scaleVector (double scale);
    /**
        Method to normalize a vector. It returns a new vector which is the result of the normalization.
     */
    Vec normalizeVector();
    /**
        Method to perform a vectorial product between two vectors. It returns a new vector which is the result of the product.
        @param other the other vector of the product.
     */
    Vec crossProduct(Vec other);
    /**
        Method to homegenize a vector. It returns a new vector which is the result of the homogenization.
     */
    Vec toHomogeneous();
    /**
        Method to convert the vector in cartesian form. It returns a new vector which is the cartesian form of the original one.
     */
    Vec toCartesian();
    /**
        Method that returns the vector resulting from the projection of this vector on the plane perpendicular to the vector passed as parameter.
        @param other the vector perpendicular to the plane in which the vector should be projected
     */
    Vec projectOntoPlanePerpendicularTo(Vec other);
    /**
     Method to transform a 3D vector in a 2D vector. It returns a new vector corresponding to the transformation
     */
    Vec from3Dto2D();
    /**
        Redefinition of [] operator to access Vec elements.
     */
    double& operator [] (int index);
    /**
        Redefinition of * operator to handle Vec-Vec product.
     */
    friend double operator*(Vec &v1, Vec &v2);
    /**
        Redefinition of * operator to handle Vec-double product.
     */
    friend Vec operator*(Vec &v1, double &d);
    /**
        Redefinition of * operator to handle double-Vec product.
     */
    friend Vec operator* (double &d, Vec &v);
    /**
        Redefinition of - operator to handle Vec-Vec subtraction.
     */
    friend Vec operator- (Vec &v1, Vec &v2);
};

/**
    This is the class used to generate all the matrices needed for transforming the scene.
    In addition it offers some method to perform some operations such as product between matrices and
    product between matrix and vector.
 **/
class Matrix {
private:
    /**
        The matrix is stored as an a vector of Vec
     */
    std::vector<Vec> mat;
    /**
        number of rows
     */
    int nrows;
    /**
        number of columns
     */
    int ncolumns;
    /**
        private constructor to create a matrix
        @param nrows the number of rows
        @param ncolumns the number of columns
     */
    Matrix(int nrows, int ncolumns);
public:
    /**
        method that returns the number of rows
     */
    int getNrows();
    /**
        method that returns the number of colomns
     */
    int getNcolumns();
    /**
        static method to create a matrix filled with zeroes. It returns the newly created matrix.
        @param nrows the number of rows
        @param ncolumns the number of columns
     */
    static Matrix zeroesMatrix(int nrows, int ncolumns);
    /**
        static method to create an identity matrix. It returns the newly created matrix.
        @param nrows the number of rows
        @param ncolumns the number of columns
     */
    static Matrix identityMatrix(int nrows, int ncolumns);
    /**
        static method to create a translation matrix. It returns the newly created matrix.
        @param dx the translation on the x axis
        @param dy the translation on the y axis
        @param dz the translation on the z axis
     */
    static Matrix translationMatrix3D(double dx, double dy, double dz);
    /**
        static method to create a uniform scale matrix. It returns the newly created matrix.
        @param scaleFactor
     */
    static Matrix scaleMatrix3D(double scaleFactor);
    /**
        static method to create a scale matrix. It returns the newly created matrix.
        @param sx the scale factor on the x axis
        @param sy the scale factor on the y axis
        @param sz the scale factor on the z axis
     */
    static Matrix scaleMatrix3D(double sx, double sy, double sz);
    /**
        static method to create a x-rotation matrix. It returns the newly created matrix.
        @param theta the angle of rotation
     */
    static Matrix xRotationMatrix3D(double theta);
    /**
        static method to create a x-rotation matrix. It returns the newly created matrix.
        @param cosTheta the cosine of the angle of rotation
        @param sinTheta the sine of the angle of rotation
     */
    static Matrix xRotationMatrix3D(double cosTheta, double sinTheta);
    /**
        static method to create a y-rotation matrix. It returns the newly created matrix.
        @param theta the angle of rotation
     */
    static Matrix yRotationMatrix3D(double theta);
    /**
        static method to create a y-rotation matrix. It returns the newly created matrix.
        @param cosTheta the cosine of the angle of rotation
        @param sinTheta the sine of the angle of rotation
     */
    static Matrix yRotationMatrix3D(double cosTheta, double sinTheta);
    /**
        static method to create a z-rotation matrix. It returns the newly created matrix.
        @param theta the angle of rotation
     */
    static Matrix zRotationMatrix3D(double theta);
    /**
        static method to create a z-rotation matrix. It returns the newly created matrix.
        @param cosTheta the cosine of the angle of rotation
        @param sinTheta the sine of the angle of rotation
     */
    static Matrix zRotationMatrix3D(double cosTheta, double sinTheta);
    /**
        static method to create a rotation matrix given two vectors. It returns the newly created matrix.
        @param vpn the normal vector
        @param vup the vup vector
     */
    static Matrix rotationMatrix3D(Vec vpn, Vec up);
    /**
        static method to create a xy-shear matrix. It returns the newly created matrix.
        @param shx the shear on the x-axis
        @param shy the shear on the y-axis
     */
    static Matrix XYshear3D(double shx, double shy);
    /**
        static method to create a perspective projection matrix. It returns the newly created matrix.
        @param d the distance of the projection plane
     */
    static Matrix perspectiveProjectionMatrix3D(double d);
    /**
        static method to create a parallel projection matrix. It returns the newly created matrix.
     */
    static Matrix parallelProjectionMatrix3D();
    /**
        static method to create a Nper matrix. This matrix is necessary to transform the view volume in
        the canonical viewing volume. It returns the newly created matrix.
        @param vrp the viewing reference point
        @param vpn the viewing plane normale
        @param vup the vup vector
        @param prp projection reference point
        @param f the distance of the front clipping plane
        @param b the distance of the back clipping plane
        @param umin the minimum coordinate of the window in the u axis
        @param umax the maximum coordinate of the window in the u axis
        @param vmin the minimum coordinate of the window in the v axis
        @param vmax the maximum coordinate of the window in the v axis
     */
    static Matrix normalizePerspectiveTransformationMatrix3D(Vec vrp, Vec vpn, Vec vup, Vec prp, int f, int b, int umin, int umax, int vmin, int vmax);
    /**
        static method to create the matrix to map the 3D coordinate into 2D coordinate. 
        It returns the newly created matrix.
        @param xmin the minimum x coordinate
        @param ymin the minimum y coordinate
        @param zmin the minimum z coordinate
        @param xmax the maximum x coordinate
        @param ymax the minimum y coordinate
        @param zmax the minimum z coordinate
        @param umin the minimum screen coordinate on u axis
        @param vmin the minimum screen coordinate on v axis
        @param umax the maximum screen coordinate on u axis
        @param vmax the maximum screen coordinate on v axis
     */
    static Matrix viewPortMapping3D(double xmin, double ymin, double zmin, double xmax, double ymax, double zmax, double umin, double vmin, double vmax, double umax);
    /**
        Method to print a matrix.
     */
    void print();
    /**
        Redefinition of * operator to handle matrix-vector product.
     */
    friend Vec operator*(Matrix &m, Vec &v);
    /**
        Redefinition of * operator to handle matrix-matrix product.
     */
    friend Matrix operator*(Matrix &m1, Matrix &m2);
    /**
        Redefinition of [] operator to access matrix elements.
     */
    Vec& operator [] (int index);
};


#endif /* Library_hpp */
