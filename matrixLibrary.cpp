//
//  Library.cpp
//  Homework 02
//
//  Created by Andrea Rottigni on 13/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#include "matrixLibrary.hpp"

double operator*(Vec &v1, Vec &v2) {
    //checks if the vectors have the same size
    if (v1.getSize() != v2.getSize()) {
        throw "nomber of columns of first matrix different from number of rows of second matrix";
    }
    double result = 0;
    //perform the scalar product of two vectors
    for (int i = 0; i < v1.getSize(); i++) {
        result += v1[i]*v2[i];
    }
    return result;
}

Vec operator*(Vec &v1, double &d) {
    Vec result = Vec::zeroesVec(v1.getSize());
    //multiply each element of the vector for d.
    for (int i = 0; i < result.getSize(); i++) {
        result[i] = v1[i]*d;
    }
    return result;
}

Vec operator* (double &d, Vec &v) {
    //call the * operator redifinied above
    return v*d;
}

Vec operator- (Vec &v1, Vec &v2) {
    //checks if the vectors have the same size
    if (v1.getSize() != v2.getSize()) {
        throw "nomber of columns of first matrix different from number of rows of second matrix";
    }
    Vec result = Vec::zeroesVec(v1.getSize());
    //subtract each pair of corresponding elements
    for (int i = 0; i < result.getSize(); i++) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}


double approssimate(double value) {
    if (fabs(value) < 0.001) {
        return 0;
    }
    return value;
}

Vec::Vec(int size) : coordinates(size) {
    this->size = size;
}

Vec::Vec() {
    
}

int Vec::getSize() {
    return size;
}

Vec Vec::initializedVec(double* elements, int size) {
    Vec v = *new Vec(size);
    //assigns each element of the array to the corresponding vec's element
    for (int i=0; i < size; i++) {
        v[i] = elements[i];
    }
    return v;
}

Vec Vec::zeroesVec(int size) {
    Vec v = *new Vec(size);
    //assigns zero to each element of the Vec
    for (int i = 0; i < size; i++) {
        v[i] = 0;
    }
    return v;
}

double& Vec::operator [] (int index) {
    return coordinates.at(index);
}

void Vec::print() {
    for (int i = 0; i < size; i++) {
        std::cout << (*this)[i];
        std::cout << "\n";
    }
}

double Vec::norm() {
    double sumOfSquare = 0;
    //sums the square of each element of the vector
    for (int i = 0; i < size; i++) {
        sumOfSquare += ((*this)[i])*((*this)[i]);
    }
    //returns the square root of the sum of the squares
    return sqrt(sumOfSquare);
}

Vec Vec::projectOntoPlanePerpendicularTo(Vec other) {
    //compute the numerator, denominator of the formula use to project a vector onto a plane.
    double numerator = (*this)*other;
    double denominator = other.norm()*other.norm();
    double division = numerator/denominator;
    //compute the factor of the formula use to project a vector onto a plane.
    Vec factor = division*other;
    //finaly subtract this vector with the factor to obtain the vector resulting from the projection
    return *this - factor;
}

bool Vec::compareVector(Vec other) {
    for (int i = 0; i < size; i++) {
        //To checks if two elements are euqals I use the absolute value of the difference to handle floating point imprecision
        if ( fabs((*this)[i] - other[i]) < 0.01) {
            return false;
        }
    }
    return true;
}

Vec Vec::normalizeVector() {
    double norm = this->norm();
    Vec normalized = *new Vec(size);
    //Divides each element of the vector using the norm
    for (int i = 0; i < size; i++) {
        normalized[i] = ((*this)[i]) / norm;
    }
    return normalized;
}

Vec Vec::crossProduct(Vec other) {
    if (size !=3 || other.size !=3) {
        throw "Illegal vector";
    }
    Vec result = *(new Vec(size));
    //compute each component of the croos product
    result[0] = (*this)[1]*other[2] - (*this)[2]*other[1];
    result[1] = (*this)[2]*other[0] - (*this)[0]*other[2];
    result[2] = (*this)[0]*other[1] - (*this)[1]*other[0];
    return result;
}

Vec Vec::toHomogeneous() {
    Vec result = zeroesVec(size+1);
    int i;
    //creates a new vector which is a copy of the original one plus one element equal to one.
    for (i = 0; i < size; i++) {
        result[i] = (*this)[i];
    }
    result[i] = 1;
    return result;
}

Vec Vec::toCartesian() {
    Vec result = zeroesVec(size-1);
    //creates a new vector which has one less element than the original one. The other elements are the result of the division of each element with the last one.
    for (int i = 0; i < size-1; i++) {
        result[i] = (*this)[i]/(*this)[size-1];
    }
    return result;
}

Vec Vec::from3Dto2D() {
    Vec result = *new Vec(2);
    //create a vectore simply by ignoring the z coordinate
    for (int i = 0; i < 2; i++) {
        result[i] = (*this)[i];
    }
    return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix(int nrows, int ncolumns) : mat(nrows) {
    this->nrows = nrows;
    this->ncolumns = ncolumns;
    for (int i = 0; i < nrows; i++) {
        (*this)[i] = Vec::zeroesVec(ncolumns);
    }
}

Vec& Matrix::operator [] (int index) {
    return mat.at(index);
}

Matrix Matrix::zeroesMatrix(int nrows, int ncolumns) {
    return *new Matrix(nrows, ncolumns);
}

Matrix Matrix::identityMatrix(int nrows, int ncolumns) {
    Matrix m = zeroesMatrix(nrows, ncolumns);
    //put all ones on the diagonal
    for (int i = 0; i < std::min(nrows, ncolumns); i++) {
        m[i][i] = 1;
    }
    return m;
}

Matrix Matrix::translationMatrix3D(double dx, double dy, double dz) {
    Matrix m = identityMatrix(SIZE3D, SIZE3D);
    int j = 3;
    //put in the last column the coefficients dx, dy, dz and 1
    for (int i = 0; i < SIZE3D; i++) {
        m[i][j] = i==0 ? dx : i == 1 ? dy : i == 2 ? dz : 1;
    }
    return m;
}

Matrix Matrix::scaleMatrix3D(double scaleFactor) {
    Matrix m = Matrix::scaleMatrix3D(scaleFactor, scaleFactor, scaleFactor);
    return m;
}

Matrix Matrix::scaleMatrix3D(double sx, double sy, double sz) {
    Matrix m = identityMatrix(SIZE3D, SIZE3D);
    //put on the diagonal the coefficients sx, sy, sz and 1
    for (int i = 0; i < SIZE3D; i++) {
        m[i][i] = i==0 ? sx : i == 1 ? sy : i == 2 ? sz : 1;
    }
    return m;
}

Matrix Matrix::xRotationMatrix3D(double theta) {
    //I use an approssimation of cos theta and sin theta to obtain 0 when needed.
    return Matrix::xRotationMatrix3D(approssimate(cos(theta)), approssimate(sin(theta)));
}

Matrix Matrix::xRotationMatrix3D(double cosTheta, double sinTheta) {
    Matrix m = identityMatrix(SIZE3D, SIZE3D);
    //put in the coorect position the coefficient cosTheta and sinTheta
    for (int i = 1; i < SIZE3D - 1; i++) {
        for (int j = 1; j < SIZE3D - 1 ; j++) {
            m[i][j] = i==j ? cosTheta : (i == 1 ? -sinTheta : sinTheta);
        }
    }
    return m;
}

Matrix Matrix::yRotationMatrix3D(double theta) {
    //I use an approssimation of cos theta and sin theta to obtain 0 when needed.
    return Matrix::yRotationMatrix3D(approssimate(cos(theta)), approssimate(sinf(theta)));
}

Matrix Matrix::yRotationMatrix3D(double cosTheta, double sinTheta) {
    Matrix m = identityMatrix(SIZE3D, SIZE3D);
    //put in the coorect position the coefficient cosTheta and sinTheta
    for (int i = 0; i < SIZE3D - 1; i += 2) {
        for (int j = 0; j < SIZE3D - 1 ; j += 2) {
            m[i][j] = i==j ? cosTheta : (i == 0 ? sinTheta : -sinTheta);
        }
    }
    return m;
}

Matrix Matrix::zRotationMatrix3D(double theta) {
    //I use an approssimation of cos theta and sin theta to obtain 0 when needed.
    return Matrix::zRotationMatrix3D(approssimate(cos(theta)), approssimate(sinf(theta)));
}

Matrix Matrix::zRotationMatrix3D(double cosTheta, double sinTheta) {
    Matrix m = identityMatrix(SIZE3D, SIZE3D);
    //put in the coorect position the coefficient cosTheta and sinTheta
    for (int i = 0; i < SIZE3D - 2; i++) {
        for (int j = 0; j < SIZE3D - 2 ; j++) {
            m[i][j] = i==j ? cosTheta : (i == 0 ? -sinTheta : sinTheta);
        }
    }
    return m;
}

Matrix Matrix::perspectiveProjectionMatrix3D(double d) {
    Matrix result = Matrix::identityMatrix(SIZE3D, SIZE3D);
    int row = 3;
    result[row][row] = 0;
    result[row][row-1] = d;
    return result;
}


void Matrix::print() {
    for (int i = 0; i < nrows ; i++) {
        for (int j = 0; j < ncolumns; j++) {
            std::cout << (*this)[i][j];
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

int Matrix::getNcolumns() {
    return ncolumns;
}

int Matrix::getNrows() {
    return nrows;
}

Matrix Matrix::XYshear3D(double shx, double shy) {
    Matrix result = identityMatrix(SIZE3D, SIZE3D);
    int column = 2;
    for (int i = 0; i < SIZE3D - 2; i++) {
        result[i][column] = i ? shy : shx;
    }
    return result;
}

Matrix Matrix::rotationMatrix3D(Vec vpn, Vec vup) {
    if (vpn.getSize() != SIZE3D-1 || vup.getSize() != SIZE3D-1) {
        throw "error";
    }
    Matrix result = identityMatrix(SIZE3D, SIZE3D);
    //compute the rotation matrix using the formula of the book, using cross products etc...
    Vec z = vpn.normalizeVector();
    Vec x = vup.crossProduct(z);
    x = x.normalizeVector();
    Vec y = z.crossProduct(x);
    for (int i = 0; i < SIZE3D-1; i++) {
        for (int j = 0; j < SIZE3D-1; j++) {
            if (i == 0) {
                result[i][j] = x[j];
            }
            if (i == 1) {
                result[i][j] = y[j];
            }
            if (i == 2) {
                result[i][j] = z[j];
            }
        }
    }
    return result;
}

Matrix operator*(Matrix &m1, Matrix &m2) {
    //checks if the matrix can be multiplied
    if (m1.getNcolumns() != m2.getNrows()) {
        throw "nomber of columns of first matrix different from number of rows of second matrix";
    }
    Matrix result = Matrix::zeroesMatrix(m1.getNrows(), m2.getNcolumns());
    //compute the matrix product
    for (int i = 0; i < result.getNrows(); i++) {
        for (int j = 0; j < result.getNcolumns(); j++) {
            float temp = 0;
            for (int k=0; k < m2.getNrows(); k++) {
                temp += (m1[i][k])*(m2[k][j]);
            }
            result[i][j] = temp;
        }
    }
    return result;
}


Matrix Matrix::normalizePerspectiveTransformationMatrix3D(Vec vrp, Vec vpn, Vec vup, Vec prp, int F, int B, int umin, int umax, int vmin, int vmax) {
    Vec u, v, n, dop, cw, vrp1, origin;
    double shx, shy, sx, sy, sz, cwu, cwv, cwn = 0, vrp1z;
    
    //define the the viewing reference coordinate system using vpn and vup
    n = vpn;
    v = vup.projectOntoPlanePerpendicularTo(vpn);
    u = v.crossProduct(n);
    
    //compute center of window
    cwu = (umax+umin)/2;
    cwv = (vmax+vmin)/2;
    double coord[] = {cwu, cwv, cwn};
    cw = Vec::initializedVec(coord, SIZE3D-1);

    //compute the parameters
    //direction of projection
    dop = cw - prp;
    vrp1z = -prp[2];
    //scale factor on x axis
    sx = (2*vrp1z) / ((umax - umin)*(vrp1z + B));
    //scale factor on y axis
    sy = (2*vrp1z) / ((vmax - vmin)*(vrp1z + B));
    //scale factor on z axis
    sz = -1/(vrp1z + B);
    //shear factor on x axis
    shx = - dop[0]/dop[2];
    //shear factor on y axis
    shy = - dop[1]/dop[2];
    
    //compute all the matrices necessary to obtain Nper
    Matrix firstTranslation = translationMatrix3D(-vrp[0], -vrp[1], -vrp[2]);
    Matrix rotation = rotationMatrix3D(vpn, vup);
    Matrix secondTranslation = translationMatrix3D(-prp[0], -prp[1], -prp[2]);
    Matrix shear = XYshear3D(shx, shy);
    Matrix scale = scaleMatrix3D(sx, sy, sz);
    
    //multiply all them togheter following the order specified in the book
    Matrix result = rotation*firstTranslation;
    result = secondTranslation*result;
    result = shear*result;
    result = scale*result;
    return result;
}

Matrix Matrix::viewPortMapping3D(double xmin, double ymin, double zmin, double xmax, double ymax, double zmax, double umin, double vmin, double vmax, double umax) {
    //compute the 2D viewport mapping transformation
    double dx = xmax - xmin;
    double dy = ymax - ymin;
    double du = umax - umin;
    double dv = vmax - vmin;
    Matrix result = Matrix::identityMatrix(3, 3);
    result[0][0] = du/dx;
    result[1][1] = dv/dy;
    result[0][2] = -xmin*(du/dx) + umin;
    result[1][2] = -ymin*(dv/dy) + vmin;
    return result;
}



Vec operator*(Matrix &m, Vec &v) {
    if (m.getNcolumns() != v.getSize()) {
        throw "nomber of columns of first matrix different from number of rows of second matrix";
    }
    Vec result = Vec::zeroesVec(v.getSize());
    for (int i = 0; i < result.getSize(); i++) {
        float temp = 0;
        for (int j = 0; j < result.getSize(); j++) {
            temp += m[i][j]*v[j];
        }
        result[i] = temp;
        
    }
    return result;
}

Matrix Matrix::parallelProjectionMatrix3D() {
    Matrix result = identityMatrix(SIZE3D, SIZE3D);
    result[2][2] = 0;
    return result;
}

