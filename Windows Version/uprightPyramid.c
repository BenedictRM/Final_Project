/*
 * uprightPyramid.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

//Create a function(s) that calls objects to draw
//x, y and z are for the position of the pyriamid, dx,dy,dz are for scale size of pyramid
//****The physics for the pyramid are too complex to figure out (there is no 'triangle' box for me to use
//Therefore we'll just have one large box with mass that sits invisibly around the pyramid that grows with it when
//it is opened
void pyramids(double x, double y, double z,
                double dx, double dy, double dz)
{
    //Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //*****Set the physics for this body
	//Pyramid physics will not rotate
	dBodySetPosition(pyramid_body, 0.0, 5.0, -10.0);
	//The last value of dRFromAxisAndAngle takes RADIANS, not degrees
	//dRFromAxisAndAngle(R, 0, 1, 0, rh);//Set the rotation matrix for this side
	//dBodySetRotation(pyramid_body, R);//Rotate the body in space (invisible) using the previously calc'd rotation matrix

	//Setting these velocities prevents the object from moving: i.e. sets them to 'push back' on any collisions
	dBodySetLinearVel(pyramid_body, tempVect.x, tempVect.y, tempVect.z);
	dBodySetAngularVel (pyramid_body, 0, 0, 0);//Force a linear angle, if this is not set then some default turns on and causes a curve

	//Turn off colliding object force effects on this geom so that it is stationary (less density = greater effect on objects colliding into this one)
	dBodyDisable(pyramid_body);
	 //*****End of physics for this body

    //Save transformation s.t. each pyramid draws individually, rotates individually etc.
    glPushMatrix();

    //***Physics box just around the entire diamond rather than around each indiv. pyra.
    glScaled(dx,dy,dz);
    glTranslated(x,y,z);
    glRotated(rh,0,1,0);


    //Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glColor3f(1,1,1);
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[8]);

    //Return the transformation to main
    glBegin(GL_TRIANGLES);

    //Draw pyramid with center at origin, counterclockwise so face culling works and so normals calculate properly
    //Front
    //calculate the normal for this side with our normal function (deprecated to save computations)
    glNormal3f(0.0,+0.707107,+0.707107);
    glColor3f(red,0,0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.0,+0.5,0.0);//p1
    glColor3f(red,0,blue);
    glTexCoord2f(1.0,0.0); glVertex3f(-0.5,0,+0.5);//p2
    glColor3f(red,green,blue + 0.3);
    //0.5 here because we are making triangles
    glTexCoord2f(0.5,1.0); glVertex3f(+0.5,0,+0.5);//p3

    //Right
    glNormal3f(+0.707107,+0.707107,0.0);
    glColor3f(red,0,0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.0,+0.5,0.0);//Draw top to meet other triangle
    glColor3f(red,green,blue);
    glTexCoord2f(1.0,0.0); glVertex3f(+0.5,0.0,+0.5);//Meet at x coordinate
    glColor3f(0,0,0);
    glTexCoord2f(0.5,1.0); glVertex3f(+0.5,0,-0.5);

    //Left
    //calculate the normal for this side *this one is a little different to get couter-clock dir calc
    glNormal3f(-0.707107,+0.707107,0.0);
    glColor3f(red,0,0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.0,+0.5,0.0);//Draw top to meet other triangle
    glColor3f(0,0,blue);
    glTexCoord2f(1.0,0.0); glVertex3f(-0.5,0,-0.5);//straight back from x coord
    glColor3f(red,0,blue);
    glTexCoord2f(0.5,1.0); glVertex3f(-0.5,0,+0.5);//Meet at x coordinate

    //Back
    //calculate the normal for this side *this one is a little different to get couter-clock dir calc
    glNormal3f(0.0,+0.707107,-0.707107);
    glColor3f(red,0,0);//blue (top)
    glTexCoord2f(0.0,0.0); glVertex3f(0.0,+0.5,0.0);//Draw top to meet other triangle
    glColor3f(0,0,0);
    glTexCoord2f(1.0,0.0); glVertex3f(+0.5,0.0,-0.5);//Meet at x coordinate
    glColor3f(0,0,blue);//right
    glTexCoord2f(0.5,1.0); glVertex3f(-0.5,0.0,-0.5);//parallel to x axis
    glEnd();

    //Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
    //Bottom square (should be counter clockwise
    glNormal3f(0.0,-1.0,0.0);
    glColor3f(red + 0.1,0,0);
    glTexCoord2f(0.0,0.0); glVertex3f(+0.5,0.0,-0.5);//back right
    glTexCoord2f(1.0,0.0); glVertex3f(+0.5,0.0,+0.5);//right
    glTexCoord2f(1.0,1.0); glVertex3f(-0.5,0.0,+0.5);//left
    glTexCoord2f(0.0,1.0); glVertex3f(-0.5,0.0,-0.5);//back left

    glEnd();
    glPopMatrix();
    //Disable textures so that entire project not texture enabled
	glDisable(GL_TEXTURE_2D);
}
//Fill in front/back of pyramid
void triInvertfb(double x, double y, double z,
                    double dx, double dy, double dz)
{
    //Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    //Save transformation s.t. each pyramid draws individually, rotates individually etc.
    glPushMatrix();

    glScaled(dx,dy,dz);
    glTranslated(x,y,z);
    glRotated(rh,0,1,0);

    //Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glColor3f(1,1,1);
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[8]);

    //Return the transformation to main
    glBegin(GL_TRIANGLES);

    //Draw pyramid with center at origin
    //Front
    //Calc normal, going in counter clockwise fashion as necessary
    glNormal3f(0.0,+0.707107,+0.707107);
    glColor3f(red,0,0);
    glTexCoord2f(0.0,0.0); glVertex3f(+0.5,+0.5,0.0);
    glColor3f(red,0,0);
    glTexCoord2f(1.0,0.0); glVertex3f(-0.5,+0.5,0.0);
    glColor3f(red,0,blue);
    glTexCoord2f(0.5,1.0); glVertex3f(0.0,0.0,0.5);

    //Right
    //Calc normal, going in counter clockwise fashion as necessary
    glNormal3f(+0.707107,-0.707107,0.0);
    glColor3f(red,0,0);
    glTexCoord2f(0.0,0.0); glVertex3f(+0.5,+0.5,0.0);//Draw top to meet other triangle
    glTexCoord2f(1.0,0.0); glVertex3f(0.0,0.0,+0.5);//Meet at x coordinate
    glTexCoord2f(0.5,1.0); glVertex3f(0.0,0.0,-0.5);

    //Left
    //Calc normal, going in counter clockwise fashion as necessary
    glNormal3f(-0.707107,-0.707107,0.0);
    glColor3f(0,0,blue);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.5,+0.5,0.0);//Draw top to meet other triangle
    glTexCoord2f(1.0,0.0); glVertex3f(0.0,0.0,-0.5);
    glTexCoord2f(0.5,1.0); glVertex3f(0.0,0.0,+0.5);//Meet at x coordinate

    //Back
    //Calc normal, going in counter clockwise fashion as necessary
    glNormal3f(0.0,+0.707107,-0.707107);
    glColor3f(0,0,0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.5,+0.5,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(+0.5,+0.5,0.0);
    glColor3f(0,green,blue);
    glTexCoord2f(0.5,1.0); glVertex3f(0.0,0.0,-0.5);

    glEnd();
    glPopMatrix();
    //Disable textures so that entire project not texture enabled
	glDisable(GL_TEXTURE_2D);
}
//Fill in left/right sides of pyramid
void triInvertlr(double x, double y, double z, double dx, double dy, double dz)
{
    //Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //Save transformation s.t. each pyramid draws individually, rotates individually etc.
    glPushMatrix();

    glScaled(dx,dy,dz);//Control the scaling
    glTranslated(x,y,z);
    glRotated(rh,0,1,0);

    //Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glColor3f(1,1,1);
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[8]);

    //Return the transformation to main
    glBegin(GL_TRIANGLES);

    //Draw pyramid with center at origin
    //Front
    //Calc normal, going in counter clockwise fashion as necessary
    glNormal3f(-0.707107,-0.707107,0.0);
    glColor3f(0,0,blue);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.5,0.0,0.0);
    glColor3f(red,0.137255,0.419608);
    glTexCoord2f(1.0,0.0); glVertex3f(0.0,+0.5,+0.5);
    glColor3f(0,0,0);
    glTexCoord2f(0.5,1.0); glVertex3f(0.0,+0.5,-0.5);

    //Right
    //Calc normal, going in counter clockwise fashion as necessary
    glNormal3f(0.0,-0.707107,-0.707107);
    glColor3f(0,green,0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.5,0.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(0.0,+0.5,-0.5);//Draw top to meet other triangle
    glTexCoord2f(0.5,1.0); glVertex3f(+0.5,0.0,0.0);//Meet at x coordinate

    //Left
    //Calc normal, going in counter clockwise fashion as necessary
    glNormal3f(0.0,-0.707107,+0.707107);
    glColor3f(red,0,0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.5,0.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(+0.5,0.0,0.0);//Meet at x coordinate
    glTexCoord2f(0.5,1.0); glVertex3f(0.0,+0.5,+0.5);//Draw top to meet other triangle

    //Back
    //Calc normal, going in counter clockwise fashion as necessary
    glNormal3f(+0.707107,+0.707107,0.0);
    glColor3f(0,0,0);//bottom
    glTexCoord2f(0.0,0.0); glVertex3f(+0.5,0.0,0.0);
    glColor3f(red,0,0.2);
    glTexCoord2f(1.0,0.0); glVertex3f(0.0,+0.5,-0.5);
    glColor3f(red + 0.3,green,blue);//top
    glTexCoord2f(0.5,1.0); glVertex3f(0.0,+0.5,+0.5);

    glEnd();
    glPopMatrix();
    //Disable textures so that entire project not texture enabled
	glDisable(GL_TEXTURE_2D);
}

void cap(double x, double y, double z, double dx, double dy, double dz)
{
    //Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    glScaled(dx,dy,dz);
    glTranslated(x,y,z);
    glRotated(rh,0,1,0);

    //Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glColor3f(1,1,1);

	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//Return the transformation to main
    glBegin(GL_QUADS);

    //Bottom
    //Calc normal, going in counter clockwise fashion as necessary (I think)
    //l = normalP(-0.5,0,+0.5,+0.5,0,+0.5,+0.5,0,-0.5);
    glNormal3f(0.0,-1.0,0.0);
    glColor3f(0, 0,blue);//alternating dark Purple
    glTexCoord2f(0.0,0.0); glVertex3f(+0.5,0.0,-0.5);//back right
    glTexCoord2f(1.0,0.0); glVertex3f(+0.5,0.0,+0.5);//right
    glTexCoord2f(1.0,1.0); glVertex3f(-0.5,0.0,+0.5);//left
    glTexCoord2f(0.0,1.0); glVertex3f(-0.5,0.0,-0.5);//back left
    glEnd();

    glPopMatrix();

    //Disable textures so that entire project not texture enabled
	glDisable(GL_TEXTURE_2D);
}//End of normal scale
