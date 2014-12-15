/*
 * box.c
 *
 *  Created on: Nov 15, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

//This box will sit in the sky somewhere and when hit will fall apart and smash into the ground
//It will be composed of large sides that we will specify here
void boxSide(double x, double y, double z,
                double dx, double dy, double dz,
                  double rx, double ry, double rz, double angle, int i)
{
	//Set specular color to white
	float white[] = {1,1,1,1};
	float black[] = {0,0,0,1};
	GLfloat matrix[16];//Physics
	dMatrix3 R;
	const dReal* rot;//physics
	const dReal* pos;//physics
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

	//*****Set the physics for this body
	//dBodySetPosition(boxSide_body[i], x, y, z);//MAYBE SET WITH if dBody is disabled? or increase it's fall rate based on getPosition, set position *2 or something
	//The last value of dRFromAxisAndAngle takes RADIANS, not degrees
	dRFromAxisAndAngle(R, rx, ry, rz, angle);//Set the rotation matrix for this side
	dBodySetRotation(boxSide_body[i], R);//Rotate the body in space (invisible) using the previously calc'd rotation matrix

	//Setting these velocities prevents the object from moving: i.e. sets them to 'push back' on any collisions
	dBodySetLinearVel(boxSide_body[i], tempVect.x, tempVect.y, tempVect.z);
	dBodySetAngularVel (boxSide_body[i], 0, 0, 0);//Force a linear angle, if this is not set then some default turns on and causes a curve

	if (i < 12)//Small sides
	{
	     //box1
		 if (i==0)//front
	     {
			 dBodySetForce(boxSide_body[i],0,0,500);
			// dBodySetTorque(boxSide_body[i],0,0,500);
	     }
			 if (i==1)//right
			 {
				 dBodySetForce(boxSide_body[i],500,0,0);
				//dBodySetTorque(boxSide_body[i],500,0,0);
			 }
				 if (i==2)//back
				 {
					 dBodySetForce(boxSide_body[i],0,0,-500);
					 //dBodySetTorque(boxSide_body[i],0,0,-500);
				 }
					 if (i==3)//left
					 {
						 dBodySetForce(boxSide_body[i],-500,0,0);
						 //dBodySetTorque(boxSide_body[i],-500,0,0);
					 }
		 //Box2
		 if (i==6)//front
		 {
			 dBodySetForce(boxSide_body[i],0,0,500);
			// dBodySetTorque(boxSide_body[i],0,0,500);
		 }
			 if (i==7)//right
			 {
				 dBodySetForce(boxSide_body[i],500,0,0);
				//dBodySetTorque(boxSide_body[i],500,0,0);
			 }
				 if (i==8)//back
				 {
					 dBodySetForce(boxSide_body[i],0,0,-500);
					 //dBodySetTorque(boxSide_body[i],0,0,-500);
				 }
					 if (i==9)//left
					 {
						 dBodySetForce(boxSide_body[i],-500,0,0);
						 //dBodySetTorque(boxSide_body[i],-500,0,0);
					 }
	}

		if (((i >= 4) && (i < 6)) || ((i >= 10) && (i < 12)))//Top/bottom
		{
			 dBodySetForce(boxSide_body[i],0,-2000,0);
			 //dBodySetTorque(boxSide_body[i],0,0,0);
		}
	//*****End of physics for this body

	//Save transformation s.t. the box draws w/o affecting the world, rotates individually etc.
	glPushMatrix();

	//Apply textures to this box
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//Allow modulation for this texture
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	// Do this instead of calling glTranslate and glRotate to get proper physics
	rot = dBodyGetRotation(boxSide_body[i]);
	pos = dBodyGetPosition(boxSide_body[i]);

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

	//glTranslated(x,y,z);
	//glRotated(angle,rx,ry,rz);
	//Scale after you effectively rotate and translate the objects (nice!)
	glScaled(dx,dy,dz);

	//Draw platform
	glBegin(GL_QUADS);
	//Box 1
	if (i < 6)
	{
	     glColor3f(1.0,0.0,1.0);//Purple
	}

		//Box 2
		if (i >= 6)
		{
		     glColor3f(1.0,0.0,0.0);//Red
		}
    //Draw the outside of the box:
	//Draw bottom
	glNormal3f(0.0,-1.0,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+4.0,0.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-4.0,0.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-4.0,0.0,-1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+4.0,0.0,-1.0);

	//Draw Right
	glNormal3f(1.0,0.0,0.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+4.0,0.0,-1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+4.0,+4.0,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+4.0,+4.0,+1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+4.0,0.0,+1.0);

	//Draw Top
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+4.0,+4.0,-1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-4.0,+4.0,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-4.0,+4.0,+1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(+4.0,+4.0,+1.0);

	//Draw Left
	glNormal3f(-1.0,0.0,0.0);
	glTexCoord2f(0.0,0.0); glVertex3f(-4.0,0.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-4.0,+4.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-4.0,+4.0,-1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-4.0,0.0,-1.0);

	//Draw sides
	//Draw Left large side
	glNormal3f(0.0,0.0,1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(-4.0,0.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+4.0,0.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+4.0,+4.0,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-4.0,+4.0,+1.0);

	//Draw Right large side
	glNormal3f(0.0,0.0,-1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-4.0,+4.0,-1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+4.0,+4.0,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+4.0,0.0,-1.0);
	glTexCoord2f(0.0,0.0); glVertex3f(-4.0,0.0,-1.0);

	glEnd();

	glPopMatrix();
	//Turn off textures
	glDisable(GL_TEXTURE_2D);
}
