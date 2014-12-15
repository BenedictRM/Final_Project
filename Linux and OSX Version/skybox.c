/*
 * skybox.c
 *
 *  Created on: Oct 29, 2014
 *      Author: Russ Mehring
 */
#include "5229_Project.h"
//Some source code from http://www.davidwparker.com/2012/12/26/opengl-screencast-video-21-skybox/
void initSkybox()
{
    /*
	SKY_FRONT 0
	SKY_RIGHT 1
	SKY_BACK 2
	SKY_LEFT 3
	SKY_TOP 4
   */
   skyBox[SKY_FRONT] = LoadTexBMP("violentdays_large.bmp");
   /*skyBox[SKY_FRONT] = LoadTexBMP("flatrock_front.bmp");
   skyBox[SKY_RIGHT] = LoadTexBMP("flatrock_right.bmp");
   skyBox[SKY_BACK] = LoadTexBMP("flatrock_back.bmp");
   skyBox[SKY_LEFT] = LoadTexBMP("flatrock_left.bmp");
   skyBox[SKY_TOP] = LoadTexBMP("flatrock_top.bmp");
   skyBox[SKY_BOTTOM] = LoadTexBMP("stars_dn.bmp");*/

}

void drawSky()
{
	//dim is 5.0 when writing this, with perspective view set at 0.1, 1000
	//Now that depth bit disabled we actually dont need to worry about what depth is, it will automatically draw correctly
	drawSkybox(3.5*dim);
}

void drawSkybox (double D)
{
	  glColor3f(1,1,1);//white
	  //Turn on textures
	  glEnable(GL_TEXTURE_2D);

	  //GL_Modulate mixes underlying color/lighting to the applied texture
	  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	  //  Sides
	  glBindTexture(GL_TEXTURE_2D,skyBox[0]);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  glBegin(GL_QUADS);
	  //Back (where we are facing)
	  glTexCoord2f(0.00,0.335); glVertex3f(-D,-D,-D);//bottom left of image
	  glTexCoord2f(0.25,0.335); glVertex3f(+D,-D,-D);//bottom right of image
	  glTexCoord2f(0.25,0.663); glVertex3f(+D,+D,-D);//top right of image
	  glTexCoord2f(0.00,0.663); glVertex3f(-D,+D,-D);//top left of image

	  //Left (starting pos's right)
	  glTexCoord2f(0.25,0.335); glVertex3f(+D,-D,-D);//bottom left
	  glTexCoord2f(0.50,0.335); glVertex3f(+D,-D,+D);//bottom right
	  glTexCoord2f(0.50,0.663); glVertex3f(+D,+D,+D);
	  glTexCoord2f(0.25,0.663); glVertex3f(+D,+D,-D);

	  //Front (behind starting pos)
	  glTexCoord2f(0.50,0.335); glVertex3f(+D,-D,+D);//bottom left
	  glTexCoord2f(0.75,0.335); glVertex3f(-D,-D,+D);//bottom right
	  glTexCoord2f(0.75,0.663); glVertex3f(-D,(+D + 0.01),+D);
	  glTexCoord2f(0.50,0.663); glVertex3f(+D,(+D + 0.01),+D);

	  //Right (starting pos's left)
	  glTexCoord2f(0.75,0.335); glVertex3f(-D,-D,+D);//bottom left
	  glTexCoord2f(1.00,0.335); glVertex3f(-D,-D,-D);//bottom right
	  glTexCoord2f(1.00,0.663); glVertex3f(-D,+D,-D);
	  glTexCoord2f(0.75,0.663); glVertex3f(-D,+D,+D);

	  //Top
	  glTexCoord2f(0.251,0.663); glVertex3f(+D,+D,-D);//bottom left of image, clip in from x
	  glTexCoord2f(0.499,0.663); glVertex3f(+D,+D,+D);//bottom right of image, clip in from x
	  glTexCoord2f(0.499, 1.0); glVertex3f(-D,+D,+D);//top right of image, clip in from x
	  glTexCoord2f(0.251, 1.0); glVertex3f(-D,+D,-D);//top left of image, clip in from x

	  //Bottom
	  glTexCoord2f(0.251,0.0); glVertex3f(-D,-D, +D);//bottom left of image, clip in from x.
	  glTexCoord2f(0.251,0.335); glVertex3f(+D,-D, +D);//top left of image, clip in from x.
	  glTexCoord2f(0.499,0.335); glVertex3f(+D,-D,-D);//top right of image, clip in from x.
	  glTexCoord2f(0.499,0.0);  glVertex3f(-D,-D,-D);//bottom right of image, clip in from x.

	  glEnd();

	  //Sides counterclockwise for face culling to still work
	  /*
	  //Sides
	  //Back (where we are facing)
	  glBindTexture(GL_TEXTURE_2D,skyBox[SKY_BACK]);
	  glBegin(GL_QUADS);
	  glTexCoord2f(0.00,0); glVertex3f(-D,-D,-D);
	  glTexCoord2f(1.0,0); glVertex3f(+D,-D,-D);
	  glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
	  glTexCoord2f(0.00,1); glVertex3f(-D,+D,-D);
	  glEnd();

	  //Left (starting pos's right)
	  glBindTexture(GL_TEXTURE_2D,skyBox[SKY_LEFT]);
	  glBegin(GL_QUADS);
	  glTexCoord2f(0.0,0); glVertex3f(+D,-D,-D);
	  glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
	  glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
	  glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
	  glEnd();

	  //Front (behind starting pos)
	  glBindTexture(GL_TEXTURE_2D, skyBox[SKY_FRONT]);
	  glBegin(GL_QUADS);
	  glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
	  glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
	  glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
	  glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
	  glEnd();

	  //Right (starting pos's left)
	  glBindTexture(GL_TEXTURE_2D,skyBox[SKY_RIGHT]);
	  glBegin(GL_QUADS);
	  glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
	  glTexCoord2f(1.00,0); glVertex3f(-D,-D,-D);
	  glTexCoord2f(1.00,1); glVertex3f(-D,+D,-D);
	  glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
	  glEnd();
*/
	  //Return to old matrix
	  glDisable(GL_TEXTURE_2D);
}
