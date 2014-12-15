/*
 * sphere.c
 *
 *  Created on: Nov 9, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

/*
 *  Draw vertex in polar coordinates with normal
 */
void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);//Bind the texture to each column in the sphere's drawing
   glVertex3d(x,y,z);
}

//Experiment to test gravitational pull on this object
//r = radius of all spheres
//This function uses prof. Schreuder's sphere function which I took and added physics to
void sphere(double r) {
	int th2,ph2;
	int inc = 10;//Ball increment
    float yellow[] = {1.0,1.0,0.0,1.0};
    float Emission[]  = {0.0,0.0,0.01*emission,1.0};
    const dReal* rot;
    const dReal* pos;
    const dReal* rot2;
	const dReal* pos2;
    GLfloat matrix[16];
    GLfloat matrix2[16];//for ball 2, just to prevent any conflicting data with other balls
/*  //This is a relic: Moved to 5229_Project.c --thought that made more sense than to call it in the Sphere function, also this is the same as our simLoop function
    dSpaceCollide (spacePhy,0,&nearCallback);
	dWorldQuickStep (world,0.05);
	dJointGroupEmpty (contactgroup);
*/
	//dSpaceCollide(spacePhy,0,&nearCallback);//Inserts all objects into a space that checks which objects are potentially intersecting
	//dWorldQuickStep (world,0.1);//Steps the world, updates where objects are after each frame etc.

    glPushMatrix();
    //Turn on textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//Allow modulation for this texture
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[10]);

	// Do this instead of calling glTranslate and glRotate to get proper physics, balls that spin etc.
	rot = dBodyGetRotation(ball_body);
	pos = dBodyGetPosition(ball_body);

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

	//Multiply against the current matrix to get proper location of ball
	glMultMatrixf(matrix);
	//Scale as normal
    glScaled(r, r, r);
	//White ball
	glColor3f(1,1,0);
	glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
	glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

	//  Bands of latitude
	for (ph2 =- 90; ph2 < 90; ph2 += inc)
    {
		glBegin(GL_QUAD_STRIP);
		for (th2 = 0; th2 <= 360; th2 += 2*inc)
		{
			//This function sets the normal for the sphere
			Vertex(th2,ph2);//Call vertex function above
			Vertex(th2, ph2 + inc);
		}
		glEnd();
	}

	glPopMatrix();
	//Turn off textures
	glDisable(GL_TEXTURE_2D);

	//If space is pressed throw a new ball in, position set in keyControl.c
	if (draw == 1)
	{
		glPushMatrix();
		//Turn on textures
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//Allow modulation for this texture
		//Bind texture at this array position to the object
		glBindTexture(GL_TEXTURE_2D, texture[10]);

		// Do this instead of calling glTranslate and glRotate to get proper physics, balls that spin etc.
		rot2 = dBodyGetRotation(ball_body2);
		pos2 = dBodyGetPosition(ball_body2);

		matrix2[0] = rot2[0];
		matrix2[1] = rot2[4];
		matrix2[2] = rot2[8];
		matrix2[3] = 0;
		matrix2[4] = rot2[1];
		matrix2[5] = rot2[5];
		matrix2[6] = rot2[9];
		matrix2[7] = 0;
		matrix2[8] = rot2[2];
		matrix2[9] = rot2[6];
		matrix2[10] = rot2[10];
		matrix2[11] = 0;
		matrix2[12] = pos2[0];
		matrix2[13] = pos2[1];
		matrix2[14] = pos2[2];
		matrix2[15] = 1;
		glMultMatrixf(matrix2);

		//Scale as normal
		glScaled(r, r, r);
		//Cyan ball
	    glColor3f(0,1,1);
	    glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
	    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
	    glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
	    //  Bands of latitude
	    for (ph2 =- 90; ph2 < 90; ph2 += inc)
	    {
		    glBegin(GL_QUAD_STRIP);
		    for (th2 = 0; th2 <= 360; th2 += 2 * inc)
		    {
		    	//This function sets the normal for the sphere
		    	Vertex(th2, ph2);//Call vertex function above
		    	Vertex(th2, ph2 + inc);
		    }
		    glEnd();
	    }
		glPopMatrix();
		//Turn off textures
		glDisable(GL_TEXTURE_2D);
	}

	//Ball 3
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//Allow modulation for this texture
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[10]);

	// Do this instead of calling glTranslate and glRotate to get proper physics, balls that spin etc.
	rot = dBodyGetRotation(ball_body3);
	pos = dBodyGetPosition(ball_body3);

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
	//Multipply against cur. matrix to get proper ball location, spin etc.
	glMultMatrixf(matrix);
	//Scale as normal
	glScaled(r, r, r);
	//White ball
	glColor3f(1,0,1);
	glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
	glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
	//  Bands of latitude
	for (ph2 =- 90; ph2 < 90; ph2 += inc)
    {
		glBegin(GL_QUAD_STRIP);
		for (th2 = 0; th2 <= 360; th2 += 2*inc)
		{
			//This function sets the normal for the sphere
			Vertex(th2, ph2);//Call vertex function above
			Vertex(th2, ph2 + inc);
		}
		glEnd();
	}
	glPopMatrix();
	//Turn off textures
	glDisable(GL_TEXTURE_2D);
}

//This funciton draws all spheres that are located inside boxes
void boxSpheres(double r, int i) {
	int th2,ph2;
	int inc = 10;//Ball increment
	float yellow[] = {1.0,1.0,0.0,1.0};
	float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	const dReal* rot;
	const dReal* pos;
	GLfloat matrix[16];

	//Add balls inside of exploding box
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//Allow modulation for this texture
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[10]);

	// Do this instead of calling glTranslate and glRotate to get proper physics, balls that spin etc.
	rot = dBodyGetRotation(balls_body[i]);
	pos = dBodyGetPosition(balls_body[i]);

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
	//Multiply against cur. matrix to get proper ball location, spin etc.
	glMultMatrixf(matrix);
	//Scale as normal
	glScaled(r, r, r);
	//White ball
	glColor3f(ballx - (i*.05),bally+(i*.05),ballz-+(i*.05));//Mess with the colors
	//Reset colors
	if(ballx < 0)
	{
		ballx = 1;
	}
		if(bally > 1)
		{
			bally = 0;
		}
			if(ballz < 0)
			{
				ballz = 1;
			}
	glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
	glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
	//  Bands of latitude
	for (ph2 =- 90; ph2 < 90; ph2 += inc)
	{
		glBegin(GL_QUAD_STRIP);
		for (th2 = 0; th2 <= 360; th2 += 2*inc)
		{
			//This function sets the normal for the sphere
			Vertex(th2, ph2);//Call vertex function above
			Vertex(th2, ph2 + inc);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}
//LightningSphere
void lightningSphere()
{
    int th2,ph2;
    int inc = 10;//Ball increment
    float yellow[] = {1.0,1.0,0.0,1.0};
    float Emission[]  = {0.0,0.0,0.01*emission,1.0};
    //  Save transformation
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//Allow modulation for this texture
    //Bind texture at this array position to the object
    glBindTexture(GL_TEXTURE_2D, texture[19]);
    //  Offset, scale and rotate
    glTranslated(0,5,-10);//Placed inside pyramid
    glRotated(rh ,0, 1 ,0);//Rotates with pyramid
    glScaled(1,1,1);
    //  White ball
    glColor3f(1,1,1);
    glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
    //  Bands of latitude
    for (ph2=-90;ph2<90;ph2+=inc)
    {
 	   glBegin(GL_QUAD_STRIP);
	   for (th2=0;th2<=360;th2+=2*inc)
	   {
		  Vertex(th2,ph2);
		  Vertex(th2,ph2+inc);
	   }
	   glEnd();
    }
    //  Undo transformations
    glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
