/*
 * platform.c
 *
 *  Created on: Oct 20, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

void platform(double x, double y, double z,
                double dx, double dy, double dz,
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
	dBodySetPosition(platform_body[i], x, y, z);
	//The last value of dRFromAxisAndAngle takes RADIANS, not degrees
	dRFromAxisAndAngle(R, rx, ry, rz, angle);//Set the rotation matrix for this side
	dBodySetRotation(platform_body[i], R);//Rotate the body in space (invisible) using the previously calc'd rotation matrix

	//Setting these velocities prevents the object from moving: i.e. sets them to 'push back' on any collisions
	dBodySetLinearVel(platform_body[i], tempVect.x, tempVect.y, tempVect.z);
	dBodySetAngularVel (platform_body[i], 0, 0, 0);//Force a linear angle, if this is not set then some default turns on and causes a curve

	//Turn off colliding object force effects on this geom so that it is stationary (less density = greater effect on objects colliding into this one)
	dBodyDisable(platform_body[i]);
    //*****End of physics for this body

    //Draw the geom with opengl
	//Save transformation s.t. each platform draws individually, rotates individually etc.
	glPushMatrix();

	//Pre matrix mult solution:
	//Set the position of the object in space with physics attached:
	//const dReal *realP4 = dBodyGetPosition(platform_body[i]);
	//platform: this pointer tells us how the body is affected by gravity
	//glTranslatef(realP4[0], realP4[1], realP4[2]);

	//***This sets the platform positions with rotation pre-physics, scaling occurs as normal
	//glTranslated(x,y,z);
    //glRotated(angle,rx,ry,rz);

	// Do this instead of calling glTranslate and glRotate to get proper physics
	rot = dBodyGetRotation(platform_body[i]);
	pos = dBodyGetPosition(platform_body[i]);

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
	matrix[12] = pos[0];
	matrix[13] = pos[1];
	matrix[14] = pos[2];
	matrix[15] = 1;
	glMultMatrixf(matrix);

	//Scale after you effectively rotate and translate the objects (nice!)
	glScaled(dx,dy,dz);

	//Now draw the object as normal with OpenGl
	//Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glColor3f(1,1,1);
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[18]);

	//Draw platform
	glBegin(GL_QUADS);
	glNormal3f(0.0,-1.0,0.0);
	//Draw bottom
	glColor3f(0.5,0.5,0.5);//Grey for now
	glTexCoord2f(0.0,0.0); glVertex3f(+2.0,0.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-2.0,0.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-2.0,0.0,-1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+2.0,0.0,-1.0);
	//Draw top counterclockwise
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+1.75,+0.25,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.75,+0.25,-1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.75,+0.25,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.75,+0.25,+1.0);
	glEnd();

	//Draw Sides
	glBindTexture(GL_TEXTURE_2D,texture[2]);
	//Front counter clockwise
	glBegin(GL_QUADS);
	glNormal3f(0.0,0.0,1.0);
	glColor3f(0,1,1);//Green for now
	glTexCoord2f(0.0,0.0); glVertex3f(-2.0,0.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+2.0,0.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+1.75,+0.25,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.75,+0.25,+1.0);

	//Back
	glNormal3f(0.0,0.0,-1.0);
	glColor3f(0,1,1);//Green for now
	glTexCoord2f(0.0,0.0); glVertex3f(-1.75,+0.25,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+1.75,+0.25,-1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+2.0,0.0,-1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-2.0,0.0,-1.0);

	//Right
	glNormal3f(0.707107,0.707107,0.0);
	glColor3f(0,1,1);//Green for now
	glTexCoord2f(0.0,0.0); glVertex3f(+1.75,+0.25,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+1.75,+0.25,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+2.0,0.0,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+2.0,0.0,-1.0);

	//Left
	glNormal3f(-0.707107,0.707107,0.0);
	glColor3f(0,1,1);//Green
	glTexCoord2f(0.0,0.0); glVertex3f(-2.0,0.0,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-2.0,0.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.75,+0.25,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.75,+0.25,-1.0);

	glEnd();
	//Return to old matrix
	glPopMatrix();
	//Disable textures so that entire project not texture enabled
	glDisable(GL_TEXTURE_2D);
}
