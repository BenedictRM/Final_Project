/*
 * boxTargets.c
 *
 *  Created on: Dec 7, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

//dx,dy,dz -- set scale, rx,ry,rz--set rotation, angle--rotation angle, i is array position of box physics array
void boxes(double dx, double dy, double dz,
             double rx, double ry, double rz, double angle, int i)
{
	//Set specular color to white
	float white[] = {1,1,1,1};
	float black[] = {0,0,0,1};
	GLfloat matrix[16];//Physics
	const dReal* rot;//physics
	const dReal* pos;//physics

	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

	//*****Set the physics for this body
	dMatrix3 R;
	//dBodySetPosition(targetBox_body[i], x, y, z);
	//The last value of dRFromAxisAndAngle takes RADIANS, not degrees
	dRFromAxisAndAngle(R, rx, ry, rz, angle);//Set the rotation matrix for this side
	//dBodySetRotation(targetBox_body[i], R);//Rotate the body in space (invisible) using the previously calc'd rotation matrix

	//Setting these velocities prevents the object from moving: i.e. sets them to 'push back' on any collisions
	//dBodySetAngularVel (targetBox_body[i], 0, 1, 0);//Force a linear angle, if this is not set then some default turns on and causes a curve
	//*****End of physics for this body

	//Save transformation s.t. each platform draws individually, rotates individually etc.
	glPushMatrix();
	// Do this instead of calling glTranslate and glRotate to get proper physics
	rot = dBodyGetRotation(targetBox_body[i]);
	pos = dBodyGetPosition(targetBox_body[i]);

	matrix[0] = rot[0];
	matrix[1] = rot[4];
	matrix[2] = rot[8];
	matrix[3] = 0;
	matrix[4] = rot[1];
	matrix[5] = rot[5];
	matrix[6] = rot[9];
	matrix[7] = 0;
	matrix[8] = rot[2];
	matrix[9] = rot[6];
	matrix[10] = rot[10];
	matrix[11] = 0;
	matrix[12] = pos[0];//Xpos
	matrix[13] = pos[1] - 2;//Ypos with adjustment
	matrix[14] = pos[2];//Zpos
	matrix[15] = 1;
	glMultMatrixf(matrix);

	//Scale after you effectively rotate and translate the objects (nice!)
	glScaled(dx,dy,dz);

	//Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glColor3f(1,1,1);
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[21]);
	//Draw box
	glBegin(GL_QUADS);
	//Bottom
    glNormal3f(0.0,-1.0,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+2.0,0.0,+2.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-2.0,0.0,+2.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-2.0,0.0,-2.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+2.0,0.0,-2.0);
    //Top
	glNormal3f(0.0,+1.0,0.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+2.0,+4.0,-2.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-2.0,+4.0,-2.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-2.0,+4.0,+2.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+2.0,+4.0,+2.0);
	//Front
	glNormal3f(0.0,0.0,+1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(-2.0,0.0,+2.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+2.0,0.0,+2.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+2.0,+4.0,+2.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-2.0,+4.0,+2.0);
	//Back
	glNormal3f(0.0,0.0,-1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(-2.0,+4.0,-2.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+2.0,+4.0,-2.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+2.0,0.0,-2.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-2.0,0.0,-2.0);
	//Right
	glNormal3f(+1.0,0.0,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+2.0,+4.0,-2.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+2.0,+4.0,+2.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+2.0,0.0,+2.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+2.0,0.0,-2.0);
	//Left
	glNormal3f(-1.0,0.0,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(-2.0,0.0,-2.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-2.0,0.0,+2.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-2.0,+4.0,+2.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-2.0,+4.0,-2.0);

	glEnd();
	//Return to old matrix
	glPopMatrix();
	//Disable textures so that entire project not texture enabled
	glDisable(GL_TEXTURE_2D);
}
