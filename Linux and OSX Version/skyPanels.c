/*
 * skyPanels.c
 *
 *  Created on: Nov 19, 2014
 *      Author: Russ Mehring
 */


#include "5229_Project.h"

void skyPanel(double x, double y, double z,
                double dx, double dy, double dz,
                  double rx, double ry, double rz, double angle, int i)
{
	//Capture calculated normals

	//Set specular color to white
	float white[] = {1,1,1,1};
	float black[] = {0,0,0,1};
	GLfloat matrix[16];//Physics
	const dReal* rot3;//physics
	const dReal* pos3;//physics

	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

	//Save the transformation
	glPushMatrix();
	//*****Set the physics for this body
	dMatrix3 R;
	dBodySetPosition(skyPanel_body[i], x, y, z);
	//The last value of dRFromAxisAndAngle takes RADIANS, not degrees
	dRFromAxisAndAngle(R, rx, ry, rz, angle);//Set the rotation matrix for this side
	dBodySetRotation(skyPanel_body[i], R);//Rotate the body in space (invisible) using the previously calc'd rotation matrix

	//Setting these velocities prevents the object from moving: i.e. sets them to 'push back' on any collisions
	dBodySetLinearVel(skyPanel_body[i], tempVect.x, tempVect.y, tempVect.z);
	dBodySetAngularVel (skyPanel_body[i], 0, 0, 0);//Force a linear angle, if this is not set then some default turns on and causes a curve
	//*****End of physics for this body

	// Do this instead of calling glTranslate and glRotate to get proper physics
	rot3 = dBodyGetRotation(skyPanel_body[i]);
	pos3 = dBodyGetPosition(skyPanel_body[i]);

	matrix[0] = rot3[0];
	matrix[1] = rot3[4];
	matrix[2] = rot3[8];
	matrix[3] = 0;
	matrix[4] = rot3[1];
	matrix[5] = rot3[5];
	matrix[6] = rot3[9];
	matrix[7] = 0;
	matrix[8] = rot3[2];
	matrix[9] = rot3[6];
	matrix[10] = rot3[10];
	matrix[11] = 0;
	matrix[12] = pos3[0] - 1;//x position, adjusted due to an (ode?) inaccuracy
	matrix[13] = pos3[1] -3.5;//y position, adjusted due to an (ode?) inaccuracy
	matrix[14] = pos3[2];//z position
	matrix[15] = 1;
	glMultMatrixf(matrix);

    glScaled(dx, dy, dz);

	//Now draw the object as normal with OpenGl
	//Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);

	//Change colors when hit
	if (!(dBodyIsEnabled(skyPanel_body[i])))
	{
	     glColor3f(1,1,1);
	}

		if (dBodyIsEnabled(skyPanel_body[i]))
		{
			glColor3f(1.0,1.0,0.0);//Yellow for now
		}
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[11]);

	//Draw skyPanel
	glBegin(GL_QUADS);
	glNormal3f(0.0,-1.0,0.0);

	//Draw back (bottom half)
	glNormal3f(0.0,0.0,-1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.0,0.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.0,0.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.5,0.5,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.5,0.5,+1.0);
	//Draw back (top half)
	glNormal3f(0.0,0.0,-1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.5,0.5,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.5,0.5,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.0,1.0,+1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.0,1.0,+1.0);

	//Draw front (bottom half)
	glNormal3f(0.0,0.0,1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.5,+0.5,+1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.5,+0.5,+1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.0,+0.0,+1.5);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.0,+0.0,+1.5);
    //Draw front (top half)
	glNormal3f(0.0,0.0,1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.0,+1.0,+1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.0,+1.0,+1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.5,+0.5,+1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.5,+0.5,+1.5);

	//Draw Sides
	glBindTexture(GL_TEXTURE_2D,texture[11]);
	//Change colors when hit
	if (!(dBodyIsEnabled(skyPanel_body[i])))
	{
		 glColor3f(1,0,0);//Red
	}

		if (dBodyIsEnabled(skyPanel_body[i]))
		{
			glColor3f(0.0,1.0,0.0);//Green for now
		}
	//Left (bottom half
	glNormal3f(-0.707107,-0.707107,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.0,0.0,+1.0);
	glTexCoord2f(0.5,0.0); glVertex3f(-1.0,0.0,+1.5);
	glTexCoord2f(0.5,0.5); glVertex3f(-1.5,+0.5,+1.5);
	glTexCoord2f(0.0,0.5); glVertex3f(-1.5,+0.5,+1.0);
	//Left(Top half)
	glNormal3f(-0.707107,-0.707107,0.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,+0.5,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.5,+0.5,+1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.0,+1.0,+1.5);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.0,+1.0,+1.0);

	//Bottom
	glNormal3f(0.0,-1.0,0.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.0,+0.0,+1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.0,+0.0,+1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.0,+0.0,+1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.0,+0.0,+1.0);

	//Right (bottom half
	glNormal3f(0.707107,0.707107,0.0);
	glTexCoord2f(0.0,0.5); glVertex3f(+1.5,+0.5,+1.0);
	glTexCoord2f(0.5,0.5); glVertex3f(+1.5,+0.5,+1.5);
	glTexCoord2f(0.5,0.0); glVertex3f(+1.0,0.0,+1.5);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.0,0.0,+1.0);
	//Right(Top half)
	glNormal3f(0.707107, 0.707107,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.0,+1.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+1.0,+1.0,+1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(+1.5,+0.5,+1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.5,+0.5,+1.0);

	//Top
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.0,+1.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.0,+1.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.0,+1.0,+1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.0,+1.0,+1.5);

	glEnd();
	//Return to old matrix
	glPopMatrix();
	//Disable textures so that entire project not texture enabled
	glDisable(GL_TEXTURE_2D);

}

