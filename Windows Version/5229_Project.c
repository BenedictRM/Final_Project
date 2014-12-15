/*
 ============================================================================
 Name        : 5229_Project.c
 Author      : Russell Mehring
 Version     : 10/23/2014
 Copyright   : Your copyright notice
 Description : Lighting for CSCI 5229
 ============================================================================
 */
#include "5229_Project.h"

//Define all variables here
double th = 0.0;  // Rotation angle
double ph = 0.0; //Elevation of view angle for gluPerspective
double rh = 0.0;  //Rotation angle for individual triangles
double zh = 0.0;  //Spin angle
double ar = 1.0; //Aspect Ratio
double dim = 5.0;
double posZ = 0.0;//For moving pyramid toward positive/negative z
double posX = 0.0;//For moving pyramid toward pos/neg x plane
double space = 0.0;//For spacing out pyramids
double red = 1.0;//to morph colors
double green = 1.0;//to morph colors
double blue = 1.0;//to morph colors
double xpos = 0.0;//X pos of camera
double ypos = 2.0;//Y pos of camera
double zpos = 30.0;//Z pos of camera
//Doorway variables
double size = 0.1;
double xplace = 0.0;
double yplace = 0.0;
double yplacetb = 0.0;
double rotate = 0.0;
//Door 2
double size2 = 0.1;
double xplace2 = 0.0;
double yplace2 = 0.0;
double yplacetb2 = 0.0;
double rotate2 = 0.0;
//Door 3
double size3 = 0.1;
double xplace3 = 0.0;
double yplace3 = 0.0;
double yplacetb3 = 0.0;
double rotate3 = 0.0;
double r = 0.5;//radius of spheres
double pitch = 0.0;//For rolling drones
double yaw = 0.0;//For rolling drone
float walkx = 0.0;
float spin = 1.5707963268;//Spin the box  o balls when it's hit
float spin2 = 1.5707963268;//Spin skyPanels
float zero = 0.0;//SPin the box o balls when it's hit
float zero2 = 0.0;
float ylight = 18;//Elevation of light
float shinyvec[1];//Shininess (value)
//Simplex stuff (sets the terrain elevation etc.
float octaves = 1.0;
float persistence = 1.0;
float scale = 1.0;
float gunShootAngle = 0;//Control the angle of the gun on the y axis
float gunWalkAngleZ = 0;//Control the angle of the gun on the z axis
float recoil = 20.0;//To control how fast gun recoil
float gunTurnAngle = 0.0;//To control turning left/right
float gunLookAngle = 0.0;//To look up/down
float lineWidth = 0.05;//Spacing between points in lightning
//Simplex stuff
int width = 40;//For width of simplex terrain
int sqwidth = 1;//For simplex terrain individual squares width
int res = 0.0;//For simplex terrain
int tot = 0.0;//For simplex terrain
//Other variables
int widthActual;
int heightActual;
int rotations = 0;//To allow multiple spins to happen
int axis = 0;//For displaying axis code from example 9
int scaled = 0;//For displaying a scaled model to meet project requirements
int fps = 1;//Start with fps on
int light = 1;//To turn lighting on/off
int light1 = 0;//To turn lighting on/off with an additional light
int emission  = 0;  //Emission intensity (%)
int ambient = 30;  // Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 0;  // Specular intensity (%)
int az = 90;  //Light azimuth
int distance = 30;  //Light distance
int stop = 0;//stop the light from rotating
int view = 0;//For perspective vs. ortho
int draw = 0;  //draw ball
int inc = 0;//For incrementing box o balls for loop (spheres specifically)
int ballx = 1;//For coloring spheres in box o balls
int bally = 0;//For coloring spheres in box o balls
int ballz = 1;//For coloring spheres in box o balls
int obj;//Object display list for gun specifically
int obj2;//Object display list for space ship
int walk = 0;//for moving gun
int left = 0;//for moving gun
int right = 0;
int sway = 0;
int fire = 0;//To tell program gun has been fired
int w = 0;//w key not pressed
int animating = 0;//To test if gun movement still needs to complete
int animating2 = 0;//To test if gun is still firing
int back = 0;//Return gun to center after firing
int turnRight = 0;//For turning animation
int turnLeft = 0;//For turning animation
int lookDown = 0;//For looking down
int lookUp = 0;//For looking up
int toCenter = 0;//Correcting for turning the gun, returns gun to center of screen
int toCenter2 = 0;//Correcting for turning the gun, returns gun to center of screen
int noPoints = 200;//Number of points in lightning, must equal array size of lightning in header file
int randOctaves = 0;//Random octaves for lightning
int randPersistence = 0;//Random persistencefor lightning
int randScale = 0;//Random scale for lightning
int range = 2;//Range of random values for simplex for lightning calc's
int colorStep = 0;//To step through color array
int pyramidRotating = 0;//Turn lightning on/off
int fog = 1;
unsigned int texture[25];  //Texture names
unsigned int skyBox[1];  //Texture names for skybox specifically

//Create a window
void display(void){
     double x = 0;//x coord of pyramid
     double y = 0;//y coord of pyramid
     double z = 0;//z coord of pyramid
     double k = 0;//For placing pyramids
     double half = 0.5;//For placing pyramids
     double Ex = 0;
     double Ey = 0;
     double Ez = 0;
     float yellow[] = {1.0,1.0,0.0,1.0};
     float blue[] = {1.0,0.0,0.0,1.0};
     float Emission[]  = {0.0,0.0,0.01*emission,1.0};
     int i = 0;
     int j = 0;
     int q = 0;
     int iterations = 5;
     int iterInvert = 4;
     static struct normal p;

     //When the screen clears set it to this color
     glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
     //clear the screen, we MUST clear the DEPTH_BUFFER_BIT by enabling GL_DEPTH_TEST to get correct depth of the drawing!
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

     glEnable(GL_DEPTH_TEST);
     /*
     glEnable(GL_LINE_SMOOTH);//Enable antialiasing
     glEnable(GL_BLEND);//anti-aliasing related call
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//anti-aliasing related call
     glLineWidth(1.0);//Need to increase the size of lines being drawn to see anti-aliasing
     */
     glEnable(GL_POLYGON_SMOOTH);
     glEnable(GL_CULL_FACE);//Enable face culling for extra frames
     glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
     glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

     //Load identity matrix
     glLoadIdentity();

     //Turn on/off fps view
     if (fps == 1)
     {
          Ex = 2*dim*Sin(th)*Cos(ph);
          Ey = -2*dim        *Sin(ph);
          Ez = -2*dim*Cos(th)*Cos(ph);
          //xpos etc sets where I'm standing, Ex etc sets where I'm looking, next 3 set what dir is up
          gluLookAt(xpos ,ypos ,zpos, (Ex + xpos), (Ey + ypos), (Ez + zpos), 0.0,Cos(ph),0.0);
     }
         //Fps view on, therefore should not be able to move around
         if (fps == 0)
         {
             Ex = -2*dim*Sin(th)*Cos(ph);
             Ey = +2*dim        *Sin(ph);
             Ez = +2*dim*Cos(th)*Cos(ph);
             gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
         }

     //*******Draw SkyBox first to lock the box around us*****
     //Disable the depth test and mask to be able to force the skybox to infinity
     glDisable(GL_DEPTH_TEST);
     glDepthMask(GL_FALSE);

     glPushMatrix();
     glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
     glTranslatef (xpos,ypos,zpos);//translate to camera world position to hold skybox at seemingly infinity

     //Draw SkyBox first to lock the box around us
     drawSky();

     //Return the normal attributes to OpenGL
     glPopAttrib();
     glPopMatrix();
     //Reenable depth test and depth mask
     glEnable(GL_DEPTH_TEST);
     glDepthMask(GL_TRUE);
     
     //Handle fog
     if(fog == 1)
     {
     //Fog (for future reference)     
	 GLfloat density = 0.005;
	 GLfloat fogColor[4] = {1.0, 0.5, 0.0, 1.0};
	 glEnable(GL_FOG);
	 glFogi(GL_FOG_MODE, GL_EXP);
	 glFogfv(GL_FOG_COLOR, fogColor);
	 glFogf(GL_FOG_DENSITY, density);
	 glHint(GL_FOG_HINT, GL_NICEST);
     }
		 if(fog == 0)
		 {
			glDisable(GL_FOG);
		 } 

     if(light == 1)
     {
         //Translate intensity to color vectors
         float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
         float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
         float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
         //Light position
         float Position[]  = {distance*Cos(az),ylight,distance*Sin(az),1.0};
         //Be sure to normalize calculated normals, should be done in our funciton but this will force it
         glEnable(GL_NORMALIZE);

         //Draw a point for light
         glPointSize((10));
         //White dot
         glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
         glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,yellow);
         glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
         glEnable(GL_POINT_SMOOTH);//Create circles instead of squares
         glBegin(GL_POINTS);//start drawing a line loop
         //Create a white orb and set it's normal
         glColor3f(1.0f, 1.0f, 1.0f);
         p = normalP(0.0,4.0,0.0,0.0,0.0,0.0,4.0,0.0,0.0);
         glNormal3d(p.x,p.y,p.z);
         glVertex3f(Position[0],Position[1],Position[2]);
         glEnd();

         //Turn lighting on
         glEnable(GL_LIGHTING);
         //Request the ability to set ambient and diffuse colors
         glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
         glEnable(GL_COLOR_MATERIAL);//Turn on coloring
         //Set ambient, diffuse, specular components and position of light 0
         //Turn on light #0
         glEnable(GL_LIGHT0);
         glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
         glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
         glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
         glLightfv(GL_LIGHT0,GL_POSITION,Position);
     }
     //Turn on a second light
     if(light1 == 1)
     {
        //Translate intensity to color vectors
        float Ambient1[]   = {0.01*ambient ,0.01*ambient ,0.00*ambient ,1.0};
        float Diffuse1[]   = {0.01*diffuse ,0.01*diffuse ,0.00*diffuse ,1.0};
        float Specular1[]  = {0.01*specular,0.01*specular,0.00*specular,1.0};
        //Light position
        float Position1[]  = {-distance*Cos(az),ylight,-distance*Sin(az),1.0};
        //Be sure to normalize calculated normals, should be done in our funciton but this will force it
        glEnable(GL_NORMALIZE);

        //Draw a point for light
        glPointSize((10));
        //White dot
        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,blue);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
        glEnable(GL_POINT_SMOOTH);//Create circles instead of squares
        glBegin(GL_POINTS);//start drawing a line loop
        //Create a white orb and set it's normal
        glColor3f(1.0f, 1.0f, 1.0f);
        p = normalP(0.0,4.0,0.0,0.0,0.0,0.0,4.0,0.0,0.0);
        glNormal3d(p.x,p.y,p.z);
        glVertex3f(Position1[0],Position1[1],Position1[2]);
        glEnd();

        //Turn lighting on
        glEnable(GL_LIGHTING);
        //Request the ability to set ambient and diffuse colors
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);//Turn on coloring
        //Set ambient, diffuse, specular components and position of light 0
        //Turn on light #0
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1,GL_AMBIENT ,Ambient1);
        glLightfv(GL_LIGHT1,GL_DIFFUSE ,Diffuse1);
        glLightfv(GL_LIGHT1,GL_SPECULAR,Specular1);
        glLightfv(GL_LIGHT1,GL_POSITION,Position1);
      }

         else if (light == 0 && light1 == 0)
         {
             glDisable(GL_LIGHTING);
         }

     if (dBodyIsEnabled(pyramid_body))
     {
    	 rotations++;
    	 glutTimerFunc(30, Spin, 1);
     }

     //******************Draw right side up pyramids for 4 sided***************************
     for (j = 0; j < 5; j++){//Controls the height of the pyramid
         for (i = 0; i < iterations; i++)
         {
             //+2 on z to center, and -2 on x to center, pyramids(xpos, ypos, zpos, scalex, scaley, scalez)
             pyramids((x + (i+k) -2), (y + k + space + 5), ((z-k) + posZ - 8), 1, 1, 1);//Front Face shifts into +y plane
             pyramids(((x + k) - posX-2), (y + k + 5) , (z - (i+k) - 8), 1, 1, 1);//Left side
             pyramids(((4 - k) + posX-2), (y + k + 5) , (z - (i+k) - 8), 1, 1, 1);//Right Side
             pyramids((x + (i+k)-2), (y + k + space + 5) , ((-4 + k)-(1.5*posZ) - 8), 1, 1, 1);//Back Side shifts into -y plane (1.5*posZ) controls distance out into space
         }
         //Update height of pyramid
         k += 0.5;
         iterations--;
     }

     //reset k
     k=0;

     //Fill in inverted triangles front and back
     for (j = 0; j < 4; j++){
         for (i = 0; i < iterInvert; i++)
         {
             triInvertfb((x + (i + k + half)-2), (y + k + 5), (z - k - 8), 1, 1, 1);//Front Face
             triInvertfb((x + (i+k+half)-2), (y + k + 5) , (-4 + k - 8), 1, 1, 1);//Back Side
         }
         //Update height of pyramid
         k += 0.5;
         iterInvert--;
     }

     //reset values
     k=0;
     iterInvert = 4;

     //Fill in inverted triangles Left and Right
     for (j = 0; j < 4; j++){
         for (i = 0; i < iterInvert; i++)
         {
             triInvertlr((x + k -2), (y + k + 5) , (z - (i+k +half) - 8), 1, 1, 1);//Left side
             triInvertlr((4 - k-2), (y + k + 5) , (z - (i+k +half) - 8), 1, 1, 1);//Right Side
         }
         //Update height of pyramid
         k += 0.5;
         iterInvert--;
     }

//**********Draw inverted pyramids to form diamond*********************
     //Reset counter values
     iterations = 5;
     iterInvert = 4;
     k=0;
     for (j = 0; j < 5; j++){
         for (i = 0; i < iterations; i++)
         {
             //+2 on z to center, and -2 on x to center
             invertPyramids((x + (i+k) -2), (-(y + k + space) + 5), ((z-k) + posZ - 8), 1, 1, 1);//Front Face shifts into +y plane
             invertPyramids(((x + k) - posX-2), (-(y + k) + 5) , (z - (i+k) - 8), 1, 1, 1);//Left side
             invertPyramids(((4 - k) + posX-2), (-(y + k) + 5) , (z - (i+k) - 8), 1, 1, 1);//Right Side
             invertPyramids((x + (i+k)-2), (-(y + k + space) + 5) , ((-4 + k)-(1.5*posZ) - 8), 1, 1, 1);//Back Side shifts into -y plane (1.5*posZ) controls distance out into space
         }
         //Update height of pyramid
         k += 0.5;
         iterations--;
     }

     //reset k
     k=0;

     //Fill in inverted triangles front and back
     for (j = 0; j < 4; j++){
         for (i = 0; i < iterInvert; i++)
         {
             invertTriInvertfb((x + (i + k + half)-2), (-(y + k) + 5), (z - k - 8), 1, 1, 1);//Front Face
             invertTriInvertfb((x + (i+k+half)-2), (-(y + k) + 5) , (-4 + k - 8), 1, 1, 1);//Back Side
         }
         //Update height of pyramid
         k += 0.5;
         iterInvert--;
     }
     //reset values
     k=0;
     iterInvert = 4;

     //Fill in inverted triangles Left and Right
     for (j = 0; j < 4; j++){
         for (i = 0; i < iterInvert; i++)
         {
             invertTriInvertlr((x + k -2), (-(y + k) + 5) , (z - (i+k +half) - 8), 1, 1, 1);//Left side
             invertTriInvertlr((4 - k-2), (-(y + k) + 5) , (z - (i+k +half) - 8), 1, 1, 1);//Right Side
         }
         //Update height of pyramid
         k += 0.5;
         iterInvert--;
     }
//**********End of inverted pyramid routine**************
/*
//***********Call Tron routine to grid the layout***********
     int vv = 0;
     int yy = 0;
     //For near/far lines
     for (yy = -1000; yy < 1000; yy += 100){
         for (vv = -1000; vv < 1000; vv += 100)
         {
            tron(vv,yy,0);
         }
     }

     //For up/down lines
     for (yy = -1000; yy < 1000; yy += 100){
         for (vv = -1000; vv < 1000; vv += 100)
         {
            tron2(vv,0,yy);
         }
      }
      //For horizontal lines to form boxes
      for (yy = -1000; yy < 1000; yy += 100){
         for (vv = -1000; vv < 1000; vv += 100)
         {
            tron3(vv,yy,vv);
         }
      }*/
     /*//Scaled pyramid just looks weird, but useful to keep for records
     //Scaled pyramid
	 //Reset counter values
	 iterations = 5;
	 iterInvert = 4;
	 k = 0;

	 //Draw right side up pyramids for 4 sided
	 for (j = 0; j < 5; j++){
		 for (i = 0; i < iterations; i++)
		 {
			 pyramids((x + (i+k) -20), (y + k + space), ((z-k + 2) + posZ - 60), 0.5, 0.5, 0.5);//Front Face shifts into +y plane
			 pyramids(((x + k) - posX-20), (y + k) , (z - (i+k) + 2 - 60), 0.5, 0.5, 0.5);//Left side
			 pyramids(((4 - k) + posX-20), (y + k) , (z - (i+k) + 2 - 60), 0.5, 0.5, 0.5);//Right Side
			 pyramids((x + (i+k)-20), (y + k + space) , (((-4 + k)-(3*posZ)) + 2 - 60), 0.5, 0.5, 0.5);//Back Side shifts into -y plane
		 }
		 //Update height of pyramid
		 k += 0.5;
		 iterations--;
	 }
	 //reset k
	 k=0;

	 //Fill in inverted triangles front and back
	 for (j = 0; j < 4; j++){
		 for (i = 0; i < iterInvert; i++)
		 {
			 triInvertfb((x + (i + k + half)-20), (y + k), (z - k + 2 - 60), 0.5, 0.5, 0.5);//Front Face
			 triInvertfb((x + (i+k+half)-20), (y + k) , (-4 + k + 2 - 60), 0.5, 0.5, 0.5);//Back Side

		 }
		 //Update height of pyramid
		 k += 0.5;
		 iterInvert--;
	 }

	 //reset values
	 k=0;
	 iterInvert = 4;

	 //Fill in inverted triangles Left and Right
	 for (j = 0; j < 4; j++){
		 for (i = 0; i < iterInvert; i++)
		 {
			 triInvertlr((x + k -20), (y + k) , (z - (i+k +half) + 2 - 60), 0.5, 0.5, 0.5);//Left side
			 triInvertlr((4 - k-20), (y + k) , (z - (i+k +half) + 2 - 60), 0.5, 0.5, 0.5);//Right Side
		 }
		 //Update height of pyramid
		 k += 0.5;
		 iterInvert--;
	 }

	 //Cap the bottom
	 for(i = 0; i < 3; i++)
	 {
		 cap((x + (i + 1)-20), (y) ,(z + 1 - 60), 0.5, 0.5, 0.5);
		 cap((x + (i + 1)-20), (y) ,(z - 60), 0.5, 0.5, 0.5);
		 cap((x + (i + 1)-20), (y) ,(z - 1 - 60), 0.5, 0.5, 0.5);
	 }*/
     //End of banana for scale routine**********

     //**************Begin doorway routine**********************
     /*//End locations and sizes: Effectively how this works (much more basic version commented out here)
     doorway(0.0,0.0,0.0,0.5,0.5,0.5,0.0,1.0,0.0,0.0);//(bottom)
     doorway(-2.0,1.0,0.0,0.5,0.5,0.5,0.0,0.0,1.0,-60.0);//Left lower
     doorway(-2.0,3.0,0.0,0.5,0.5,0.5,0.0,0.0,1.0,-120.0);//left upper
     doorway(0.0,4.0,0.0,0.5,0.5,0.5,1.0,0.0,0.0,180.0);//Top
     doorway(2.0,3.0,0.0,0.5,0.5,0.5,0.0,0.0,1.0,120.0);//Right upper
     doorway(2.0,1.0,0.0,0.5,0.5,0.5,0.0,0.0,1.0,60.0);//Right lower*/

     //Door 1 (move around on z plane), the last value in this string is the array pos of the platforms, rotations in RADIANS
     doorway(0.0, 1.5 - yplacetb, 0.0, size, size, size, 0.0, 1.0, 0.0, 0.0 + rotate, 0);//(bottom) 0 deg. rot
     doorway(-0.5 - xplace, 1.75 - yplace, 0.0, size, size, size, 0.0, 0.0, 1.0, -1.0471975512 + rotate, 1);//Left lower, -60 deg. rot.
     doorway(-0.5 - xplace, 2.25 + yplace, 0.0, size, size, size, 0.0, 0.0, 1.0, -2.0943951024 + rotate, 2);//left upper, -120 deg. rot
     doorway(0.0, 2.5 + yplacetb, 0.0, size, size, size, 1.0, 0.0, 0.0, 3.1415926536 + rotate, 3);//Top, +180 deg. rot. = pi
     doorway(0.5 + xplace, 2.25 + yplace, 0.0, size, size, size, 0.0, 0.0, 1.0, 2.0943951024 + rotate, 4);//Right upper, +120 deg. rot
     doorway(0.5 + xplace, 1.75 - yplace, 0.0, size, size, size, 0.0, 0.0, 1.0, 1.0471975512 + rotate, 5);//Right lower, +60 deg. rot.

     //Door 2 (move around on z plane)
     doorway(0.0, 1.5 - yplacetb2, 2.0, size2, size2, size2, 0.0, 1.0, 0.0, 0.0 + rotate2, 6);//(bottom), 0 deg. rot.
     doorway(-0.5 - xplace2, 1.75 - yplace2, 2.0, size2, size2, size2, 0.0, 0.0, 1.0, -1.0471975512 + rotate2, 7);//Left lower, -60 deg. rot.
     doorway(-0.5 - xplace2, 2.25 + yplace2, 2.0, size2, size2, size2, 0.0, 0.0, 1.0, -2.0943951024 + rotate2, 8);//left upper, -120 deg. rot.
     doorway(0.0, 2.5 + yplacetb2, 2.0, size2, size2, size2, 1.0, 0.0, 0.0, 3.1415926536 + rotate2, 9);//Top, +180 deg. rot. = pi
     doorway(0.5 + xplace2, 2.25 + yplace2, 2.0, size2, size2, size2, 0.0, 0.0, 1.0, 2.0943951024 + rotate2, 10);//Right upper, +120 deg rot
     doorway(0.5 + xplace2, 1.75 - yplace2, 2.0, size2, size2, size2, 0.0, 0.0, 1.0, 1.0471975512 + rotate2, 11);//Right lower, +60 deg rot

     //Door 3 (move around on z plane)
     doorway(0.0, 1.5 - yplacetb3, 4.0, size3, size3, size3, 0.0, 1.0, 0.0, 0.0 + rotate3, 12);//(bottom), 0 deg. rot.
     doorway(-0.5 - xplace3, 1.75 - yplace3, 4.0, size3, size3, size3, 0.0, 0.0, 1.0, -1.0471975512 + rotate3, 13);//Left lower, -60 deg. rot.
     doorway(-0.5 - xplace3, 2.25 + yplace3, 4.0, size3, size3, size3, 0.0, 0.0, 1.0, -2.0943951024 + rotate3, 14);//left upper, -120. deg. rot.
     doorway(0.0, 2.5 + yplacetb3, 4.0, size3, size3, size3, 1.0, 0.0, 0.0, 3.1415926536 + rotate3, 15);//Top, +180 deg. rot. =pi
     doorway(0.5 + xplace3, 2.25 + yplace3, 4.0, size3, size3, size3, 0.0, 0.0, 1.0, 2.0943951024 + rotate3, 16);//Right upper, +120 deg. rot.
     doorway(0.5 + xplace3, 1.75 - yplace3, 4.0, size3, size3, size3, 0.0, 0.0, 1.0, 1.0471975512 + rotate3, 17);//Right lower, +60 deg. rot.

	 //**************End doorway routine**********************

     //**************Begin platform routine*******************
     //The last value in this string sets the correct geom for this platform, rotations in radians not degrees
     platform(0.0, 0.0, 18.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 0.0, 0);//(bottom)
     platform(-2.5, 2.0, 18.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, -1.3962634016, 1);//(Left lower) rotated -80 deg.
     platform(-1.5, 5.7, 18.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, -2.2689280276, 2);//(Left upper) rotated -130 deg.
     platform(1.5, 5.7, 18.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 2.2689280276, 3);//(Right upper) rotated +130 deg.
     platform(2.5, 2.0, 18.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 1.3962634016, 4);//(Right lower) rotated +80 deg.
     //Platform 2
     platform(0.0, 0.0, 60.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 0.0, 5);//(bottom)
	 platform(-2.5, 2.0, 60.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, -1.3962634016, 6);//(Left lower) rotated -80 deg.
	 platform(-1.5, 5.7, 60.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, -2.2689280276, 7);//(Left upper) rotated -130 deg.
	 platform(1.5, 5.7, 60.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 2.2689280276, 8);//(Right upper) rotated +130 deg.
	 platform(2.5, 2.0, 60.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 1.3962634016, 9);//(Right lower) rotated +80 deg.
	 //Platform 3
	 platform(0.0, 0.0, -38.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 0.0, 10);//(bottom)
	 platform(-2.5, 2.0, -38.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, -1.3962634016, 11);//(Left lower) rotated -80 deg.
	 platform(-1.5, 5.7, -38.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, -2.2689280276, 12);//(Left upper) rotated -130 deg.
	 platform(1.5, 5.7, -38.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 2.2689280276, 13);//(Right upper) rotated +130 deg.
	 platform(2.5, 2.0, -38.0, 1.0, 1.0, 10.0, 0.0, 0.0, 1.0, 1.3962634016, 14);//(Right lower) rotated +80 deg.

     /*****Keep this for now since this was a solution that took days, just in case:
     dMatrix3 R;
     dBodySetPosition(platform_body[0], 0, 0, 18);
     //The last value of dRFromAxisAndAngle takes RADIANS, not degrees
     dRFromAxisAndAngle(R, 0.0, 0.0, 1.0, 0.0);//Set the rotation matrix for this side
     dBodySetRotation(platform_body[0], R);//Rotate the body in space (invisible) using the previously calc'd rotation matrix

     dBodySetPosition(platform_body[1], -2.5, 2.0, 18);
     //Set the rotation matrix for this side, rotated -80 degrees, in radians below
     dRFromAxisAndAngle(R, 0.0, 0.0, 1.0, -1.3962634016);
     dBodySetRotation(platform_body[1], R);//Rotate this body

     dBodySetPosition(platform_body[2], -1.5, 5.7, 18);
     //Set the rotation matrix for this side, rotated -130 degrees
	 dRFromAxisAndAngle(R, 0.0, 0.0, 1.0, -2.2689280276);
	 dBodySetRotation(platform_body[2], R);//Rotate this body

     dBodySetPosition(platform_body[3], 1.5, 5.7, 18);
     //Set the rotation matrix for this side, rotated 130 degrees
     dRFromAxisAndAngle(R, 0.0, 0.0, 1.0, 2.2689280276);
     dBodySetRotation(platform_body[3], R);//Rotate this body

     dBodySetPosition(platform_body[4], 2.5, 2.0, 18);
     //Set the rotation matrix for this side, rotated 80 degrees, in radians below
     dRFromAxisAndAngle(R, 0.0, 0.0, 1.0, 1.3962634016);
     dBodySetRotation(platform_body[4], R);//Rotate this body

     //Setting these velocities prevents the object from moving: i.e. sets them to 'push back' on any collisions
     dBodySetLinearVel(platform_body[0], tempVect.x, tempVect.y, tempVect.z);
     dBodySetAngularVel (platform_body[0], 0, 0, 0);//Force a linear angle, if this is not set then some default turns on and causes a curve
	 dBodySetLinearVel(platform_body[1], tempVect.x, tempVect.y, tempVect.z);
	 dBodySetAngularVel (platform_body[1], 0, 0, 0);
	 dBodySetLinearVel(platform_body[2], tempVect.x, tempVect.y, tempVect.z);
	 dBodySetAngularVel (platform_body[2], 0, 0, 0);
     dBodySetLinearVel(platform_body[3], tempVect.x, tempVect.y, tempVect.z);
     dBodySetAngularVel (platform_body[3], 0, 0, 0);
	 dBodySetLinearVel(platform_body[4], tempVect.x, tempVect.y, tempVect.z);
	 dBodySetAngularVel (platform_body[4], 0, 0, 0);
	 */
     //**************End platform routine**********************

     //Draw sphere's for shootin'
     for (inc = 0; inc < 61; inc++)
     {
    	 boxSpheres(r,inc);
     }
     //Balls outside of box
     sphere(r);

     //This if statement causes the sides of the box of balls to spin while it 'explodes'
     if (dBodyIsEnabled(boxSide_body[0]))
     {
    	 spin += 0.0872664626;//Radians
    	 zero += 0.0872664626;
     }

     	  if (dBodyIsEnabled(boxSide_body[6]))
          {
         	 spin2 += 0.0872664626;//Radians
         	 zero2 += 0.0872664626;
          }
     //Box O' Balls
     //Call six sides to create the large box, difference of 8 between sides on z plane
     //Box 1
     boxSide(-20.0, 20.0, 16.0, 2.0, 1.0, 0.25, 0.0, 1.0, 0.0, zero, 0);//Front, rotated 0 deg. on y axis
     boxSide(-12.25, 20, 8.0, 2.0, 1.0, 0.25, 0.0, 1.0, 0.0,   spin , 1);//Right, rotated 90 deg. on y axis
     boxSide(-20.0, 20.0, 0.0, 2.0, 1.0, 0.25, 0.0, 1.0, 0.0, zero, 2);//Back, rotated 0 deg. on y axis
     boxSide(-27.75, 20.0, 8.0, 2.0, 1.0, 0.25, 0.0, 1.0, 0.0, spin, 3);//Left, rotated 90 deg. on y axis
     boxSide(-20.0, 36.0, -0.23, 2.0, 4.12, 0.25, 1.0, 0.0, 0.0,  1.5707963268, 4) ;//Top, rotated 90 deg. on x axis
     boxSide(-20.0, 20.0, -0.23, 2.0, 4.12, 0.25, 1.0, 0.0, 0.0,  1.5707963268, 5) ;//Bottom, rotated 90 deg. on x axis
     //Box 2
     boxSide(30.0, 20.0, -16.0, 2.0, 1.0, 0.25, 0.0, 1.0, 0.0, zero2, 6);//Front, rotated 0 deg. on y axis
	 boxSide(22.25, 20, -8.0, 2.0, 1.0, 0.25, 0.0, 1.0, 0.0,   spin2 , 7);//Right, rotated 90 deg. on y axis
	 boxSide(30.0, 20.0, 0.0, 2.0, 1.0, 0.25, 0.0, 1.0, 0.0, zero2, 8);//Back, rotated 0 deg. on y axis
     boxSide(37.75, 20.0, -8.0, 2.0, 1.0, 0.25, 0.0, 1.0, 0.0, spin2, 9);//Left, rotated 90 deg. on y axis
	 boxSide(30.0, 36.0, -16.23, 2.0, 4.12, 0.25, 1.0, 0.0, 0.0,  1.5707963268, 10) ;//Top, rotated 90 deg. on x axis
	 boxSide(30.0, 20.0, -16.23, 2.0, 4.12, 0.25, 1.0, 0.0, 0.0,  1.5707963268, 11) ;//Bottom, rotated 90 deg. on x axis

	 //SkyPanels
	 //Left side
     skyPanel(-30,65,20,1,6,1,0,1,0,1.5707963268,0);//Rotated 90 deg.
     skyPanel(-35,60,10,1,6,1,0,1,0,1.5707963268,1);//Rotated 90 deg.
     skyPanel(-40,55,0,1,6,1,0,1,0,1.5707963268,2);//Rotated 90 deg.
     skyPanel(-45,50,-10,1,6,1,0,1,0,1.5707963268,3);//Rotated 90 deg.
     skyPanel(-50,45,-20,1,6,1,0,1,0,1.5707963268,4);//Rotated 90 deg.
     skyPanel(-50,35,-20,1,6,1,0,1,0,1.5707963268,5);//Rotated 90 deg.
     skyPanel(-45,30,-10,1,6,1,0,1,0,1.5707963268,6);//Rotated 90 deg.
     skyPanel(-40,25,0,1,6,1,0,1,0,1.5707963268,7);//Rotated 90 deg.
     skyPanel(-35,20,10,1,6,1,0,1,0,1.5707963268,8);//Rotated 90 deg.
     skyPanel(-30,15,20,1,6,1,0,1,0,1.5707963268,9);//Rotated 90 deg.
     //Right side
     skyPanel(35,65,20,1,6,1,0,1,0,1.5707963268,10);//Rotated 90 deg.
	 skyPanel(40,60,10,1,6,1,0,1,0,1.5707963268,11);//Rotated 90 deg.
	 skyPanel(45,55,0,1,6,1,0,1,0,1.5707963268,12);//Rotated 90 deg.
	 skyPanel(50,50,-10,1,6,1,0,1,0,1.5707963268,13);//Rotated 90 deg.
	 skyPanel(55,45,-20,1,6,1,0,1,0,1.5707963268,14);//Rotated 90 deg.
	 skyPanel(55,35,-20,1,6,1,0,1,0,1.5707963268,15);//Rotated 90 deg.
	 skyPanel(50,30,-10,1,6,1,0,1,0,1.5707963268,16);//Rotated 90 deg.
	 skyPanel(45,25,0,1,6,1,0,1,0,1.5707963268,17);//Rotated 90 deg.
	 skyPanel(40,20,10,1,6,1,0,1,0,1.5707963268,18);//Rotated 90 deg.
	 skyPanel(35,15,20,1,6,1,0,1,0,1.5707963268,19);//Rotated 90 deg.
	 //Front (behind pyramid)
	 //1st row
	 skyPanel(-40,20,-60,1,6,1,0,1,0,0,20);//Rotated 0 deg.
	 skyPanel(-30,20,-60,1,6,1,0,1,0,0,21);//Rotated 0 deg.
	 skyPanel(-20,20,-60,1,6,1,0,1,0,0,22);//Rotated 0 deg.
	 skyPanel(-10,20,-60,1,6,1,0,1,0,0,23);//Rotated 0 deg.
	 skyPanel(0,20,-60,1,6,1,0,1,0,0,24);//Rotated 0 deg.
	 skyPanel(10,20,-60,1,6,1,0,1,0,0,25);//Rotated 0 deg.
	 skyPanel(20,20,-60,1,6,1,0,1,0,0,26);//Rotated 0 deg.
	 skyPanel(30,20,-60,1,6,1,0,1,0,0,27);//Rotated 0 deg.
	 skyPanel(40,20,-60,1,6,1,0,1,0,0,28);//Rotated 0 deg.
	 skyPanel(50,20,-60,1,6,1,0,1,0,0,29);//Rotated 0 deg.
	 //2nd row
	 skyPanel(-40,40,-60,1,6,1,0,1,0,0,30);//Rotated 0 deg.
	 skyPanel(-30,40,-60,1,6,1,0,1,0,0,31);//Rotated 0 deg.
	 skyPanel(-20,40,-60,1,6,1,0,1,0,0,32);//Rotated 0 deg.
	 skyPanel(-10,40,-60,1,6,1,0,1,0,0,33);//Rotated 0 deg.
	 skyPanel(0,40,-60,1,6,1,0,1,0,0,34);//Rotated 0 deg.
	 skyPanel(10,40,-60,1,6,1,0,1,0,0,35);//Rotated 0 deg.
	 skyPanel(20,40,-60,1,6,1,0,1,0,0,36);//Rotated 0 deg.
	 skyPanel(30,40,-60,1,6,1,0,1,0,0,37);//Rotated 0 deg.
	 skyPanel(40,40,-60,1,6,1,0,1,0,0,38);//Rotated 0 deg.
	 skyPanel(50,40,-60,1,6,1,0,1,0,0,39);//Rotated 0 deg.
	 //3rd row
	 skyPanel(-40,60,-60,1,6,1,0,1,0,0,40);//Rotated 0 deg.
	 skyPanel(-30,60,-60,1,6,1,0,1,0,0,41);//Rotated 0 deg.
	 skyPanel(-20,60,-60,1,6,1,0,1,0,0,42);//Rotated 0 deg.
	 skyPanel(-10,60,-60,1,6,1,0,1,0,0,43);//Rotated 0 deg.
	 skyPanel(0,60,-60,1,6,1,0,1,0,0,44);//Rotated 0 deg.
	 skyPanel(10,60,-60,1,6,1,0,1,0,0,45);//Rotated 0 deg.
	 skyPanel(20,60,-60,1,6,1,0,1,0,0,46);//Rotated 0 deg.
	 skyPanel(30,60,-60,1,6,1,0,1,0,0,47);//Rotated 0 deg.
	 skyPanel(40,60,-60,1,6,1,0,1,0,0,48);//Rotated 0 deg.
	 skyPanel(50,60,-60,1,6,1,0,1,0,0,49);//Rotated 0 deg.
	 //4th row
	 skyPanel(-40,80,-60,1,6,1,0,1,0,0,50);//Rotated 0 deg.
	 skyPanel(-30,80,-60,1,6,1,0,1,0,0,51);//Rotated 0 deg.
	 skyPanel(-20,80,-60,1,6,1,0,1,0,0,52);//Rotated 0 deg.
	 skyPanel(-10,80,-60,1,6,1,0,1,0,0,53);//Rotated 0 deg.
	 skyPanel(0,80,-60,1,6,1,0,1,0,0,54);//Rotated 0 deg.
	 skyPanel(10,80,-60,1,6,1,0,1,0,0,55);//Rotated 0 deg.
	 skyPanel(20,80,-60,1,6,1,0,1,0,0,56);//Rotated 0 deg.
	 skyPanel(30,80,-60,1,6,1,0,1,0,0,57);//Rotated 0 deg.
	 skyPanel(40,80,-60,1,6,1,0,1,0,0,58);//Rotated 0 deg.
	 skyPanel(50,80,-60,1,6,1,0,1,0,0,59);//Rotated 0 deg.
     //****End of skyPanels

     //Lightning Sphere
	 lightningSphere();
	 //Lightning effects from pyramid(hopefully)
	 if (pyramidRotating == 1)
	 {
		 //Top
		 rays(7.5 , -2.5, -10.0, 50, 0, 0, 1);
		 rays(10.0 , 5.0, -10.0, 90.0, 0, 0, 1);
		 rays(10.0 , 15.0, -10.0, 180.0, 0, 0, 1);
		 rays(0.0 , 15.0, -10.0, 180.0, 0, 0, 1);
		 rays(5.0 , 12.5, -10.0, 140.0, 0, 0, 1);
		 //Bottom
		 rays(-7.0 , 12.5, -10.0, 220.0, 0, 0, 1);
		 rays(-6.0 , -2.5, -10.0, -40.0, 0, 0, 1);
		 rays(10.0 , -2.5, -10.0, 90.0, 0, 0, 1);
		 //Back
		 rays(-5.0 , 0.0, -17.5, 90.0, 1, 1, 0);
		 rays(0.0 , 15.0, -20.0, 180, 1, 0, 1);//Back center
		 rays(-10.0 , -5.0, -10.0, 270.0, 1, 1, 0);//Back, bottom
		 //Front
		 rays(0.0 , 15.0, -10.0, 180, 1, 0, 1);//front center
		 rays(7.0, -7.5, -7.5, 90.0, 0, 1, 1);//Front bottom
		 rays(-5.0 , 0.0, -2.5, -90.0, 1, 1, 0);
	 }
    // Box targets
     for (q = 0; q < 114; q++)
     {
         //First 3 vals set scale, next 3 set rotation, then angle, then array position
    	 boxes(1,1,1,0,1,0,0,q);
     }

	 //Draw terrain from display list
	 glCallList(terrainDL);

	 //Draw space ship(s)
	 shipOne();

	 if (axis)
     {
         //Draw a Cartesian plane, I did borrow this code from example 6 from class
         glDisable(GL_LIGHTING);//Disable lighting so that axis is unaffected by lighting
         //Draw x axis
         glBegin(GL_LINES);
         glColor3f(1,1,1);
         glVertex3d(0,0,0);//From center
         glVertex3d(5,0,0);//X Axis
         glEnd();//End of Cartesian plane drawing
         //Draw y axis
         glBegin(GL_LINES);
         glColor3f(1,1,1);
         glVertex3d(0,0,0);//Back to center
         glVertex3d(0,5,0);//Y Axis
         glEnd();
         //Draw Z axis
         glBegin(GL_LINES);
         glColor3f(1,1,1);
         glVertex3d(0,0,0);//Back to center
         glVertex3d(0,0,5);//Z Axis
         glEnd();
         glColor3f(1,1,1);
         //  Label axes
         glRasterPos3d(5,0,0);
         Print("X");
         glRasterPos3d(0,5,0);
         Print("Y");
         glRasterPos3d(0,0,5);
         Print("Z");
     }
     glDisable(GL_LIGHTING);

     //Display parameters
     glColor3f(1,0,0);
     glWindowPos2i(5,5);
     Print("Projection= %s", view?"Orthogonal":"Perspective");

     if (fps == 1)
     {
          glDisable(GL_LIGHTING);
          //Display parameters
          glColor3f(1,0,0);
          glWindowPos2i(5,85);
          Print("FPS ON = W,A,S,D to move camera, arrows to look");
          //Display parameters
          glColor3f(1,1,1);
          glWindowPos2i(5,65);
          Print("xpos:%f   zpos%f   th %f    ph %f", xpos, zpos, th, ph);
     }
     if (light == 1 || light1 == 1)
     {
         glDisable(GL_LIGHTING);
         //Display parameters
         glColor3f(1,1,0);
         glWindowPos2i(5,25);
         Print("Lighting on: v/V +/- Emission; b/B +/- Specular; n/N +/- Ambient; m/M +/- Diffuse");
         //Display parameters
         glColor3f(1,1,1);
         glWindowPos2i(5,45);
         Print("Emission: %d   Specular: %d   Ambient: %d   Diffuse: %d", emission, specular, ambient, diffuse);
     }

     //Draw gun last, think painter's algorithm as to why
     glClear(GL_DEPTH_BUFFER_BIT);
	 target();
	 glClear(GL_DEPTH_BUFFER_BIT);
	 gun();
     simLoop();//Step the physics simulation
     //Force an update to the screen
     glFlush();
     //Double buffer magic trick :)
     glutSwapBuffers();
}

/*
 *  Main
 */
int main(int argc, char *argv[])
{
   //Initialize GLUT
   glutInit(&argc,argv);
   //Request double buffered true color window with Z-buffer
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   //create a window of a particular size in pixels:
   glutInitWindowSize(1000,1000);
   //Actually make a window called A Lorenz Attractor, W/O this there is no window
   glutCreateWindow("Final Project by Russ Mehring");
   glutFullScreen();//Set the window to full screen
   //Register the screen, should call our function that actually draws to the screen
   //Contains a pointer that points to the display()function below
   glutDisplayFunc(display);
   glutIdleFunc (idle);//when idle, redisplay
   glutReshapeFunc(reshape);
   //Call animations
   glutTimerFunc(30, Spin, 1);
   glutTimerFunc(30, animateDoor, 1);
   glutTimerFunc(30, movement, 1);
   //Pass control to GLUT for events, i.e. let us control the pixel at a location so that we can set it to 1
   //when we clear the buffer! I.e. enables correct depth perception by setting that pixel to it's value in
   //terms of the camera position (Note: 0 is as close as you can get to the viewer)
   //Enable mouse movement
   //glutPassiveMotionFunc(mouseMovement);
   //Enable keyboard interaction with glut
   glutSpecialFunc(special);
   glutSpecialUpFunc(specialUp);
   glutKeyboardFunc(keyPressed);
   glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events

   //Load textures
   texture[0] = LoadTexBMP("tech_skin_1.bmp");
   texture[1] = LoadTexBMP("metalbridgetoprailbig.bmp");
   texture[2] = LoadTexBMP("mp_diff_red.bmp");
   texture[3] = LoadTexBMP("Microscheme_0.bmp");
   texture[4] = LoadTexBMP("tech_skin_1.bmp");
   texture[5] = LoadTexBMP("UECTD-17.bmp");
   texture[6] = LoadTexBMP("painting-29.bmp");
   texture[7] = LoadTexBMP("Circus_converted.bmp");
   texture[8] = LoadTexBMP("metal001_converted.bmp");
   texture[9] = LoadTexBMP("metal003.bmp");
   texture[10] = LoadTexBMP("crate.bmp");
   texture[11] = LoadTexBMP("futuristic.bmp");
   texture[12] = LoadTexBMP("asteroid.bmp");
   texture[13] = LoadTexBMP("lava.bmp");
   texture[14] = LoadTexBMP("rocks.bmp");
   texture[15] = LoadTexBMP("glowrock.bmp");
   texture[16] = LoadTexBMP("tron.bmp");
   texture[17] = LoadTexBMP("tron2.bmp");
   texture[18] = LoadTexBMP("tron3.bmp");
   texture[19] = LoadTexBMP("tron4.bmp");
   texture[20] = LoadTexBMP("borg.bmp");
   texture[21] = LoadTexBMP("metalBox.bmp");

   //Load gun object
   obj = LoadOBJ("raygun_mark2.obj");
   //Load ship
   obj2 = LoadOBJ("Drone.obj");

   //Initialize terrain values
   simplexValsInit(width, sqwidth);//These values must give the same calculation as in header file where structs vec3 and 2 are defined
   //Set terrain values
   simplexVals();
   //Call terrain here, store it in a display list, call that display list in display()
   terrain();
   //Initialize Lightning
   raysInit();
   //Load skybox textures
   initSkybox();
   //Load physics
   // Create a new, empty world and assign its ID number to World. Most applications will only need one world.
   // dWorldID world = dWorldCreate();
   dInitODE();//Initialize ode with itself
   //Initialize ode values that we need with our own function (otherwise main() would be enormous)
   initODE();

   //Return to OS i.e. actually draw the thing
   glutMainLoop();
   //Return ODE physics bodies to memory
   dWorldDestroy(world);
   dCloseODE();
   //Delete display lists (return to memory), glDeleteLists(id, range), range is no. of DL's
   glDeleteLists(terrainDL,1);

   return 0;
}
