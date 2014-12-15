/*
 * lightning.c
 *
 *  Created on: Dec 6, 2014
 *      Author: Russ Mehring
 */
#include "5229_Project.h"

void raysInit()
{
	int i;
	struct vec2 pos = {0.f, 0.f};
	struct vec3 colors = {1.0, 1.0, 1.0};

	for (i = 0; i <= noPoints; i++)
	{
		//Update data array
		lightning[i].x = pos.x;
		lightning[i].y = pos.y;
		lightning[i].z = 0.f;

		pos.x += lineWidth;
	}
	//Initialize all whites for lightning
	for (i = 0; i < 100; i++)
	{
		//Update data array
		color[i].x = colors.x;
		color[i].y = colors.y;
		color[i].z = colors.z;

		//Update colors vector
		colors.z -= 0.01;//Slowly get to yellow
	}
		//Initialize all yellows for lightning
		for (; i < 200; i++)
		{
			//Update data array
			color[i].x = colors.x;
			color[i].y = colors.y;
			color[i].z = colors.z;

			//Update colors vector
			colors.x -= 0.01;//reduce yellow
			colors.y -= 0.01;//reduce yellow
			colors.z += 0.01;//Bring up blue

		}
			//Initialize all blues for lightning
			for (; i < 300; i++)
			{
				//Update data array
				color[i].x = colors.x;
				color[i].y = colors.y;
				color[i].z = colors.z;

				//Update colors vector
				colors.x += 0.01;//Bring back white
				colors.y += 0.01;//Bring back white
			}
}

//when pyramid is hit, draw rays coming from center of pyramid (x,y,z = translate, rx,ry,rz = rotate
void rays(float x, float y, float z,
		   float angle, float rx, float ry, float rz)
{
	int i;
	struct vec3 curr;

	glDisable(GL_LIGHTING);
	glEnable(GL_LINE_SMOOTH);//Enable antialiasing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//The max thickness of glLineWidth is 20
	glLineWidth(3.0);

	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(angle,rx,ry,rz);

	glBegin(GL_LINE_STRIP);
    //Step color array
    if((colorStep + 1) < 300)
    {
    	colorStep += 1;
    }
    //COnsider calling a color vector array to change between yellow, blue, white
    glColor3f(color[colorStep].x, color[colorStep].y, color[colorStep].z);
    //Reset colorStep after calling last color in array
	if((colorStep == 299))
	{
		colorStep = 0;
	}

    randOctaves = rand() % range;
    randPersistence = rand() % range;
    randScale = rand() % range;

    for(i = 0; i <= noPoints; i++)
	{
		curr = lightning[i];
		//Calls the simplex algorithm, first three param's set the variability of the terrain
		//First 3 values are: octaves, persistence (can be from 0 to 1), scale
		lightning[i].y = octave_noise_2d(randOctaves, randPersistence, randScale, curr.x, curr.z) + 10;
		glVertex3f(lightning[i].x, lightning[i].y, lightning[i].z);
	}

	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	glLineWidth(1.0);//reset line width
}
