/*
 * normal.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

//Calculate normals for pyramids
//To get values use: printf("x: %f, y: %f. z: %f\n", k.x,k.y,k.z);
//To call decl: static struct normal k; and use:
//k = normalP(0.0,+0.5,0.0,-0.5,0,+0.5,+0.5,0,+0.5);
//glNormal3f(k.x,k.y,k.z);
//Algorithm from http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Normals
//Additional resource: http://fullonsoftware.co.uk/snippets/content/Math_-_Calculating_Face_Normals.pdf
//***Note that points must be calculated in a counter-clockwise direction or normal calc is not correct
struct normal normalP(double p1x, double p1y, double p1z,
                              double p2x, double p2y, double p2z,
                               double p3x, double p3y, double p3z)
{
    //Declare struct variables (each now can hold 3 points)
    static struct normal a, b, n;
    double one;

    a.x = (p2x) - (p1x);
    a.y = (p2y) - (p1y);
    a.z = (p2z) - (p1z);

    b.x = (p3x) - (p1x);
    b.y = (p3y) - (p1y);
    b.z = (p3z) - (p1z);

    n.x = (a.y * b.z) - (a.z * b.y);
    n.y = (a.z * b.x) - (a.x * b.z);
    n.z = (a.x * b.y) - (a.y * b.x);

    // Normalize (divide by root of dot product)
    one = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
    n.x /= one;
    n.y /= one;
    n.z /= one;

    return n;
}


