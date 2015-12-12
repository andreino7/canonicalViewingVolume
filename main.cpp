//
//  main.cpp
//  Homework 02
//
//  Created by Andrea Rottigni on 09/10/15.
//  Copyright © 2015 Andrea Rottigni. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define WINDOWIDTH 800;
#define WINDOHEIGHT 800;

#include <iostream>
#include <math.h>
#include "parser.hpp"

#include <iostream>
using namespace std;

//Initialization of the slide
int state = 0;
#define NAME "ANDREA"

Database db = *new Database("../database/database.txt");
House house;

//function that applies a series of matrix in order to show the house on the screen
void prepareHouse() {
    //initialize a new house
    house = db.createHouse();
    //obtain the Nper matrix
    Matrix transformation = Matrix::normalizePerspectiveTransformationMatrix3D(db.vrp.toCartesian(), db.vpn.toCartesian(), db.vup.toCartesian(), db.prp.toCartesian(), db.F, db.B, db.umin, db.umax, db.vmin, db.vmax);
    //applying Nper matrix to clip against tha canonical viewing volume
    house.transform(transformation);
    //clip the house against the canonical viewing volume
    house.clip(db.zmin);
    //obtain the projection matrix
    transformation = Matrix::perspectiveProjectionMatrix3D(-1);
    //project the house
    house.transform(transformation);
    //obtain the matrix to map the 3D coordinates to 2D screen coordinates
    transformation = Matrix::viewPortMapping3D(-1, -1, -1, 1, 1, 1, 0, 0, 800, 800);
    //apply the 2D transformation
    house.transform2D(transformation);
}

//function to obtain a rotation matrix for making the house rotate with respects to his center
Matrix prepareRotation(Matrix rotationMatrix) {
    //create a translation matrix to translate the center to the origin
    Matrix translation = Matrix::translationMatrix3D(-20, -20, 20);
    //create a translation matrix to translate the center back
    Matrix translation2 = Matrix::translationMatrix3D(20, 20, -20);
    //multiply the rotation matrix with the first translation
    Matrix result = rotationMatrix*translation;
    //and finally multiply with the second translation
    return translation2*result;
}

//Function to update vpn, vup and vrp using the array of double passed as parameters
void updateViewVectors(double *c, double *v, double *z) {
    Vec vrp = Vec::initializedVec(c, 3).toHomogeneous();
    Vec vpn = Vec::initializedVec(v, 3).toHomogeneous();
    Vec vup = Vec::initializedVec(z, 3).toHomogeneous();
    db.vrp = vrp;
    db.vpn = vpn;
    db.vup = vup;
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:       //ESCAPE key
            exit(0);
            break;
        case 'r': //rotation around y axis key
        {
            //compute the transformation matrix
            Matrix rotation = Matrix::yRotationMatrix3D(M_PI/48);
            //transform the world calling prepare translation to rotate with respect to the center of the house
            db.transform(prepareRotation(rotation));
            break;
        }
        case 't':      //change view
        {
            state = (state+1)%4;
            switch (state) {
                case 0:
                {
                    //change the values of vpn vup and vrp
                    double c[] = {20,20,20};
                    double v[] = {0,0,1};
                    double z[] = {0,1,0};
                    updateViewVectors(c,v,z);
                    break;
                }
                case 1:
                {
                    double c[] = {60,20,-20};
                    double v[] = {1,0,0};
                    double z[] = {0,1,0};
                    updateViewVectors(c,v,z);
                    break;
                }
                case 2:
                {
                    double c[] = {20,60,-20};
                    double v[] = {0,1,0};
                    double z[] = {0,0,1};
                    updateViewVectors(c,v,z);
                    break;
                }
                    break;
                case 3:
                {
                    //change the values of vpn vup and vrp and also apply a rotation to obtain a certain angle
                    double c[] = {20,5,15};
                    double v[] = {0,0,1};
                    double z[] = {0,1,0};
                    updateViewVectors(c,v,z);
                    Matrix rotation = Matrix::xRotationMatrix3D(M_PI/6);
                    db.vpn = rotation*db.vpn;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case 'i': { //zoom in
            db.prp[2] = db.prp[2]+1;
            db.updateZmin();
            break;
        }
        case 'o': { //zoom out
            if (db.prp[2] > 0) {
                db.prp[2] = db.prp[2]-1;
                db.updateZmin();
            }
            break;
        }
        case 'a': //arbitrary rotation
        {
            Matrix rotation = Matrix::zRotationMatrix3D(M_PI/48);
            db.transform(prepareRotation(rotation));
            break;
        }
    }
    //prepare the house to be shown.
    prepareHouse();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    glPointSize(1.0);
    //calls the drawing function of the house
    house.draw();
    glutSwapBuffers();
}

void reshape (int w, int h) {
    /* set the viewport */
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);  // lower-left corner
    
    /* Matrix for projection transformation */
    glMatrixMode (GL_PROJECTION);
    
    /* replaces the current matrix with the identity matrix */
    glLoadIdentity ();
    
    /* Define a 2d orthographic projection matrix */
    gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);  // left, right, bottom, top
}

/*******************************************************************/


int main(int argc, char** argv) {
    //call the method to load the database and create the runtime objects
    prepareHouse();
    /* deal with any GLUT command Line options */
    glutInit(&argc, argv);
    
    /* create an output window */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(800, 800);
    
    /* set the name of the window and try to create it */
    glutCreateWindow("CS 425 - HOMEWORK 02");
    
    /* specify clear values for the color buffers */
    glClearColor (1.0, 1.0, 1.0, 1.0);
    
    /* Receive keyboard inputs */
    glutKeyboardFunc (Keyboard);
    
    /* assign the display function */
    glutDisplayFunc(display);
    
    /* assign the idle function */
    glutIdleFunc(display);
    
    /* sets the reshape callback for the current window */
    glutReshapeFunc(reshape);
    
    /* enters the GLUT event processing loop */
    glutMainLoop();
    
    
    
    
    return (EXIT_SUCCESS);
}
