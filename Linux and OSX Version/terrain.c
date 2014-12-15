/*
 * terrain.c
 *
 *  Created on: Nov 18, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

void terrain() {
	int i;
	int j;
	int z = 0;
	int x = 0;
	int step = 1;
	int step2 = 0;
	int lim = res - 1;//currently = 20
	int idx = res + 1;

	//Store terrain in a Display List
    terrainDL = glGenLists (1);
    glNewList(terrainDL, GL_COMPILE);

	glPushMatrix();

	glTranslated(-200,-2,-200);
	glScaled(10,4,10);

	glLineWidth(2.5);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
	//Turn on textures
	glEnable(GL_TEXTURE_2D);
	//GL_Modulate mixes underlying color/lighting to the applied texture
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glColor3f(1.0, 1.0, 1.0);
	//Bind texture at this array position to the object
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	//Draw simplex noise grid
	glBegin(GL_QUADS);
	//glBegin(GL_TRIANGLES);

	for(i = 1; i < lim; i++)
	{
		for(j = 1; j < lim; j++)
		{
             //First point set in simplexVals()
			 glTexCoord2f(0.0,0.0); glVertex3f(data[idx - res + 1].x, data[idx - res + 1].y, (data[idx - res + 1].z + (step - 1)));
			 //Second point set in simplexVals()
			 glTexCoord2f(1.0,0.0); glVertex3f(data[idx - res - 1].x, data[idx - res - 1].y , (data[idx - res - 1].z + (step - 1)));
             //Complete the square with our own derived point, y value always == Second point's y value
			 glTexCoord2f(1.0,1.0); glVertex3f((x + step2), data[idx - res - 1].y, (z + step));//The y value here is always == to second point's y value
			 //Third point set in simplexVals()
			 glTexCoord2f(0.0,1.0); glVertex3f(data[idx + 1].x, data[idx + 1].y, (data[idx + 1].z + step));//Change array order

			 //Pull appropriate normal from the array set in simplex.c
			 glNormal3f(norms[idx].x, norms[idx].y, norms[idx].z);

			 idx++;
			 step2 += 1;
		}
		//Reset for next row
		step2 = 0;
		idx += 2;
		step += 1;
	}
	glEnd();

	glPopMatrix();
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	//End of display list
	glEndList ();
}
