/*
 * project.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Russ Mehring
 */
#include "5229_Project.h"

//Create a function called Project() to be called any time we need the perspective to change
//Will handle the function call to either glOrth or gluPerspective
void Project(double ar,double dim)
{
   //Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //Orthogonal projection
   if (view == 1)
   {
        glOrtho(-ar*dim,+ar*dim, -dim,+dim, -50,+50);
   }
       //Perspective view
       if (view == 0)
       {
            gluPerspective(55,ar,dim/4, 1000.0);
       }
   //Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}


