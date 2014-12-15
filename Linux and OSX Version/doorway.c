/*
 * doorway.c
 *
 *  Created on: Oct 19, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

void doorway(double x, double y, double z,
                double dx, double dy, double dz,
                  double rx, double ry, double rz, double angle, int i)
{
	//Set specular color to white
	float white[] = {1,1,1,1};
	float black[] = {0,0,0,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

	//*****Set physics for this body
	//Here we use dMassSetBox
	//set DENSITY to be very high to prevent it from being moved from balls
	dMatrix3 R;
	dBodySetPosition(doorway_body[i], x, y, z);
	//The last value of dRFromAxisAndAngle takes RADIANS, not degrees
	dRFromAxisAndAngle(R, rx, ry, rz, angle);//Set the rotation matrix for this side
	dBodySetRotation(doorway_body[i], R);//Rotate the body in space (invisible) using the previously calc'd rotation matrix

	//Setting these velocities prevents the object from moving: i.e. sets them to 'push back' on any collisions
	dBodySetLinearVel(doorway_body[i], tempVect.x, tempVect.y, tempVect.z);
	dBodySetAngularVel (doorway_body[i], 0, 0, 0);//Force a linear angle, if this is not set then some default turns on and causes a curve

	//Turn off colliding object force effects on this geom so that it is stationary (less density = greater effect on objects colliding into this one)
	dBodyDisable(doorway_body[i]);
	//******End of Physics for this body

	//Save transformation s.t. each pyramid draws individually, rotates individually etc.
	glPushMatrix();

	//Do this instead of calling glTranslate and glRotate to get proper physics
	const dReal* rot;
	const dReal* pos;
	rot = dBodyGetRotation(doorway_body[i]);
	pos = dBodyGetPosition(doorway_body[i]);
	GLfloat matrix[16];

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

	//Scale as normal
	//glTranslated(x,y,z);
	glScaled(dx,dy,dz);//These val's determined by size 1,2,3 param's
	//glRotated(angle,rx,ry,rz);

	//Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glColor3f(1,1,1);
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//Bind texture BEFORE glBegin
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//Draw platform
    glBegin(GL_QUADS);
    glColor3f(1,1,1);//White for now
    //Draw bottom
    glNormal3f(0.0,-1.0,0.0);//Set normal for lighting
    glTexCoord2f(0.0,0.0); glVertex3f(+2.0,0.0,+1.0);
    glTexCoord2f(1.0,0.0); glVertex3f(-2.0,0.0,+1.0);
    glTexCoord2f(1.0,1.0); glVertex3f(-2.0,0.0,-1.0);
    glTexCoord2f(0.0,1.0); glVertex3f(+2.0,0.0,-1.0);
    //Draw top counterclockwise
	glNormal3f(0.0,1.0,0.0);//Set normal for lighting
	glTexCoord2f(0.0,0.0); glVertex3f(+1.75,+0.25,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.75,+0.25,-1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.75,+0.25,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+1.75,+0.25,+1.0);
    glEnd();

    //Bind texture BEFORE glBegin
    glBindTexture(GL_TEXTURE_2D, texture[2]);
	//Draw Sides
    glBegin(GL_QUADS);
	//Front counter clockwise
	glNormal3f(0.0,0.0,1.0);
	glColor3f(1,0,0);//Red for now
	glTexCoord2f(0.0,0.0); glVertex3f(-2.0,0.0,+1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+2.0,0.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+1.75,+0.25,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.75,+0.25,+1.0);

	//Back
	glNormal3f(0.0,0.0,-1.0);
	glColor3f(1,0,0);//Red for now
	glTexCoord2f(0.0,0.0); glVertex3f(-1.75,+0.25,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+1.75,+0.25,-1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+2.0,0.0,-1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-2.0,0.0,-1.0);

	//Right
	glNormal3f(0.707107,0.707107,0.0);
	glColor3f(1,0,0);//Red for now
	glTexCoord2f(0.0,0.0); glVertex3f(+1.75,+0.25,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(+1.75,+0.25,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(+2.0,0.0,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(+2.0,0.0,-1.0);

	//Left
	glNormal3f(-0.707107,0.707107,0.0);
	glColor3f(1,0,0);//Red for now
	glTexCoord2f(0.0,0.0); glVertex3f(-2.0,0.0,-1.0);
	glTexCoord2f(1.0,0.0); glVertex3f(-2.0,0.0,+1.0);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.75,+0.25,+1.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.75,+0.25,-1.0);
	glEnd();
	//Return to old matrix
	glPopMatrix();
	//Disable textures so that entire project not enabled
	glDisable(GL_TEXTURE_2D);
}

//All rotations are in RADIANS not degrees
void animateDoor(int value)
{
	//******************Doorway 1******************
	//Blow it up
    if (zpos < 5)
    {
		if (yplace < 0.75)
		{
			yplace += 0.25;
		}
			if (yplacetb <= 1.5)
			{
				yplacetb += 0.1;
			}
				if (xplace <= 1.5)
				{
					xplace += 0.1;
				}
					if (size < 0.5)
					{
						size += 0.05;
					}
						if (rotate < 3.1415926536)//< 180 deg.
						{
							rotate += 0.3490658504;//add 20 deg.
						}
    }
    //Shrink it back
    if (zpos >= 5)
	{
		if (yplace > 0.0)
		{
			if (yplace - 0.1 > 0.0)
			{
				yplace -= 0.1;
			}
		}
			if (yplacetb > 0.0)
			{
				if (yplacetb - 0.1 > 0.0)
				{
					yplacetb -= 0.1;
				}
			}
				if (xplace > 0.0)
				{
					if (xplace - 0.1 > 0.0)
					{
					    xplace -= 0.1;
					}
				}
					if (size > 0.1)
					{
						if (size - 0.05 >= 0.1)
						{
						     size -= 0.05;
						}
					}
						if (rotate > 0.0)//> 0 deg.
						{
							if (rotate - 0.3490658504 >= 0.0)//rotate - 20 deg.
							{
							     rotate -= 0.3490658504;//subtract 20 deg.
							}
						}
	    }
		//******************Doorway 2******************
		//Blow it up
		if ( zpos < 10)
		{
			if (yplace2 < 0.75)
			{
				yplace2 += 0.25;
			}
				if (yplacetb2 <= 1.5)
				{
					yplacetb2 += 0.1;
				}
					if (xplace2 <= 1.5)
					{
						xplace2 += 0.1;
					}
						if (size2 < 0.5)
						{
							size2 += 0.05;
						}
							if (rotate2 < 3.1415926536)//< 180 deg.
							{
								rotate2 += 0.3490658504;//add 20 deg.
							}
		}
		//Shrink it back
		if (zpos >= 10)
		{
			if (yplace2 > 0.0)
			{
				if (yplace2 - 0.1 > 0.0)
				{
					yplace2 -= 0.1;
				}
			}
				if (yplacetb2 > 0.0)
				{
					if (yplacetb2 - 0.1 > 0.0)
					{
						yplacetb2 -= 0.1;
					}
				}
					if (xplace2 > 0.0)
					{
						if (xplace2 - 0.1 > 0.0)
						{
							xplace2 -= 0.1;
						}
					}
						if (size2 > 0.1)
						{
							if (size2 - 0.05 >= 0.1)
							{
								 size2 -= 0.05;
							}
						}
							if (rotate2 > 0.0)
							{
								if (rotate2 - 0.3490658504 >= 0.0)//0.3490658504 = 20 deg.
								{
									 rotate2 -= 0.3490658504;
								}
							}
	}
	//******************Doorway 3******************
	//Blow it up
	if ( zpos < 15)
	{
		if (yplace3 < 0.75)
		{
			yplace3 += 0.25;
		}
			if (yplacetb3 <= 1.5)
			{
				yplacetb3 += 0.1;
			}
				if (xplace3 <= 1.5)
				{
					xplace3 += 0.1;
				}
					if (size3 < 0.5)
					{
						size3 += 0.05;
					}
						if (rotate3 < 3.1415926536)//PI = 180 deg.
						{
							rotate3 += 0.3490658504;//0.3490658504 = 20 deg.
						}
	}
	//Shrink it back
	if (zpos >= 15)
	{
		if (yplace3 > 0.0)
		{
			if (yplace3 - 0.1 > 0.0)
			{
				yplace3 -= 0.1;
			}
		}
			if (yplacetb3 > 0.0)
			{
				if (yplacetb3 - 0.1 > 0.0)
				{
					yplacetb3 -= 0.1;
				}
			}
				if (xplace3 > 0.0)
				{
					if (xplace3 - 0.1 > 0.0)
					{
						xplace3 -= 0.1;
					}
				}
					if (size3 > 0.1)
					{
						if (size3 - 0.05 >= 0.1)
						{
							 size3 -= 0.05;
						}
					}
						if (rotate3 > 0.0)
						{
							if (rotate3 - 0.3490658504 >= 0.0)
							{
								 rotate3 -= 0.3490658504;
							}
						}
	}
    //Request display update
    glutPostRedisplay();
    //Try creating an animation
    glutTimerFunc(30, animateDoor, 1);
}

