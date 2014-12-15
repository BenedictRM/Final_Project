/*
 * reshape.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

/*
 * This function is called by GLUT when the window is resized
 */
void reshape(int width,int height)
{
    //  Calculate width to height ratio
   ar = (height>0) ? (double)width/height : 1;
   widthActual = width;
   heightActual = height;
   //Set viewport as entire window
   glViewport(0,0, width,height);
   //call glOrtho
   Project(ar, dim);
}
