/*
 * ships.c
 *
 *  Created on: Dec 8, 2014
 *      Author: Russ Mehring
 */
#include "5229_Project.h"

//Drone
void shipOne()
{
	float Position[]  = {300*Cos(az),90,300*Sin(az),1.0};
	//Adjust pitch
	if ((Position[0] >= 0) && (pitch < 40))
    {
    	pitch += 1.0;
    }
		if ((Position[0] < 0) && (pitch > -40))
		{
			pitch -= 1.0;
		}

    //Adjust yaw
	if ((Position[0] >= 0) && (yaw < -180))
	{
		yaw -= 5.0;
	}
		if ((Position[0] < 0) && (yaw >= -360))
		{
			yaw -= 5.0;
		}
	if ((Position[0] >= 0)&&(yaw < -360))
	{
		yaw = 0;
	}
    //Drone 1
	glPushMatrix();
	glTranslatef(Position[0], Position[1], Position[2]);

    //glRotated(yaw,0,1,0);
	//glRotated(pitch,0,0,1);
	glRotated(pitch,0,0,1);
	glRotated(yaw,0,1,0);
    //Scale the model
    glScaled(4,4,4);

    //  Draw the model
    glCallList(obj2);
	glPopMatrix();

	//Drone 2
	glPushMatrix();
	glTranslatef((Position[0] + 20), (Position[1]-5), Position[2]);

	//glRotated(yaw,0,1,0);
	//glRotated(pitch,0,0,1);
	glRotated(pitch,0,0,1);
	glRotated(yaw,0,1,0);
	//Scale the model
	glScaled(4,4,4);

	//  Draw the model
	glCallList(obj2);
	glPopMatrix();

	//Drone 3
	glPushMatrix();
	glTranslatef((Position[0] - 10), (Position[1] - 5), Position[2]);

	//glRotated(yaw,0,1,0);
	//glRotated(pitch,0,0,1);
	glRotated(pitch,0,0,1);
	glRotated(yaw,0,1,0);
	//Scale the model
	glScaled(4,4,4);

	//  Draw the model
	glCallList(obj2);
	glPopMatrix();

	//Drone 4
	glPushMatrix();
	glTranslatef(Position[0], (Position[1] + 10), Position[2]);

	//glRotated(yaw,0,1,0);
	//glRotated(pitch,0,0,1);
	glRotated(pitch,0,0,1);
	glRotated(yaw,0,1,0);
	//Scale the model
	glScaled(4,4,4);

	//  Draw the model
	glCallList(obj2);
	glPopMatrix();
}
