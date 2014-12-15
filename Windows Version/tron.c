/*
 * tron.c
 *
 *  Created on: Oct 14, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

//Function to draw the tron-like landscape I desire
void tron (double xx, double yy, double zz)
{
	//glScaled(dx,dy,dz);
	//Save transformation otherwise translated pushes objects into places we don't want them to be
	glPushMatrix();

	glTranslated(xx,yy,zz);
	glLineWidth(2.5);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glVertex3f(0.0, 40.0, 1000.0);
	glVertex3f(0.0, 40.0, -1000.0);

	glEnd();
	glPopMatrix();
	glDisable(GL_LINE_SMOOTH);
}

//Function to draw the tron-like landscape I desire
void tron2 (double xx, double yy, double zz)
{
	 //Save transformation otherwise translated pushes objects into places we don't want them to be
	 glPushMatrix();

	 glTranslated(xx,yy,zz);
	 glLineWidth(2.5);

	 glEnable(GL_LINE_SMOOTH);
	 glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
	 glColor3f(0.0, 0.0, 1.0);

	 glBegin(GL_LINES);

	 glVertex3f(0.0, 1000.0, 40.0);
	 glVertex3f(0.0, -1000.0, 40.0);

	 glEnd();
	 glPopMatrix();
}
//Function to draw the tron-like landscape I desire
void tron3 (double xx, double yy, double zz)
{
	 //Save transformation otherwise translated pushes objects into places we don't want them to be
	 glPushMatrix();

	 glTranslated(xx,yy,zz);
	 glLineWidth(2.5);

	 glEnable(GL_LINE_SMOOTH);
	 glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
	 glColor3f(0.0, 0.0, 1.0);

	 glBegin(GL_LINES);

	 glVertex3f(1000.0, 20.0, 0.0);
	 glVertex3f(-1000.0, 20.0, 0.0);

	 glEnd();
	 glPopMatrix();
}
