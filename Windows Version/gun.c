/*
 * gun.c
 *
 *  Created on: Nov 30, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"
//Citation: Used ex 21 from class to draw the target
//The gun should be the very last thing that gets drawn (think painter's algorithm)
void target()
{
    //Save transform attributes (Matrix Mode and Enabled Modes)
    glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
    //Save projection matrix and set unit transform
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();//Reset to the identity matrix to clear transformations
    glOrtho(-ar,+ar,-1,1,-1,1);
    //Save model view matrix and set to identity
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glLineWidth(0.25);

    glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
	glColor3f(1.0, 1.0, 1.0);

    //Draw target
    glBegin(GL_LINES);

    glVertex2f(-0.03125,0);
    glVertex2f(+0.03125,0);

    glVertex2f(0,-0.03125);
	glVertex2f(0,+0.03125);

	glEnd();

    //Reset model view matrix
    glPopMatrix();
    //Reset projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    //Pop transform attributes (Matrix Mode and Enabled Modes)
    glPopAttrib();
    glDisable(GL_LINE_SMOOTH);
}

//Sway the gun while walking
void movement(int i)
{
	//Walking moves
	//Just get left for now
	if ((walk == 1) || (animating == 1))
	{
		if ((sway == 0))
		{
			animating = 1;
			//Move gun to the left
			if (left == 1)
			{
				walkx -= 0.1;
                gunWalkAngleZ -= 5.0;

                if (walkx <= -0.6)
				{
					//go back to center
					left = 0;
				}
			}
			if (left == 0)
			{
				walkx += 0.1;
				gunWalkAngleZ += 5.0;

				if (walkx >= 0)
				{
					walkx = 0;
					gunWalkAngleZ = 0.0;//Reset Z angle
					animating = 0;//Done animating
					sway = 1;//Switch to right movement
					right = 1;//Switch to right
				}
			}
		}
		//Move gun to the right
		if ((sway == 1) && (((walk == 1) || (animating == 1))))
		{
			animating = 1;
			if (right == 1)
			{
				walkx += 0.1;
				gunWalkAngleZ -= 5.0;

				if (walkx >= 0.6)
				{
					//go back to center
					right = 0;
				}
			}
			if (right == 0)
			{
				walkx -= 0.1;
				gunWalkAngleZ += 5.0;

				if (walkx <= 0)
				{
					walkx = 0;
					gunWalkAngleZ = 0.0;//Reset Z angle
					animating = 0;//done animating
					sway = 0;//Switch to left movement
					left = 1;//Switch to left
				}
			}
		}
	}

	//Turning right
    if (turnRight == 1)
    {
        if(gunTurnAngle > -25.0)
        {
    	     gunTurnAngle -= 5.0;
        }
    }
		//Turning left
		if (turnLeft == 1)
		{
			if(gunTurnAngle < 25.0)
			{
				 gunTurnAngle += 5.0;
			}
		}
			//Looking down
			if (lookDown == 1)
			{
				if(gunLookAngle < 25.0)
				{
					gunLookAngle += 5.0;
				}
			}
				//Looking up
				if (lookUp== 1)
				{
					if(gunLookAngle > -25.0)
					{
						gunLookAngle -= 5.0;
					}
				}

	//Correct left/right
	if (toCenter == 1)
	{
		//Correct turning right
		if(gunTurnAngle < 0.0)
		{
			gunTurnAngle += 5.0;
		}
			//Correct turning left
			if(gunTurnAngle > 0.0)
			{
				gunTurnAngle -= 5.0;
			}

		//Correct looking left/right
		if (gunTurnAngle == 0)
		{
			toCenter = 0;//Turn off center correcting
		}
	}

	//Correct up/down
	if (toCenter2 == 1)
	{
		//Correct looking up
		if(gunLookAngle < 0.0)
		{
			gunLookAngle += 5.0;
		}
			//Correct looking down
			if(gunLookAngle > 0.0)
			{
				gunLookAngle -= 5.0;
			}

	    //Correct looking up/down
		if (gunLookAngle == 0)
		{
			toCenter2 = 0;//Turn off center correcting
		}
	}

	//Recoil
	if ((fire == 1) || (animating2 == 1))
	{
         animating2 = 1;//Begin animation

         if ((gunShootAngle >= -90.0) && (back == 0))
         {
             gunShootAngle -= recoil;

             if (gunShootAngle < -90.0)
             {
            	 back = 1;
             }
         }

         if(back == 1)
         {
             gunShootAngle += recoil;

             if (gunShootAngle > 0.0)
             {
            	 gunShootAngle = 0.0;
            	 animating2 = 0.0;
            	 back = 0;
             }
         }
	}

	//Request display update
	glutPostRedisplay();
	//Try creating an animation
	glutTimerFunc(30, movement, 1);
}

void gun()
{
    glPushMatrix();
    glLoadIdentity();

    //gun centered at x = 0
    glTranslatef(walkx, -1, -2);
    //Rotate the gun in interesting ways
    glRotated(90,0,1,0);
    glRotated(-90,1,0,0);
    glRotated(gunWalkAngleZ,1,1,0);//Control gun movement while walking
    glRotated(gunShootAngle,1,1,0);
    glRotated(gunTurnAngle,1,0,0);
    glRotated(gunLookAngle,0,1,0);//Look down
    //Scale the model
    glScaled(1,1,1);

    //  Draw the model
    glCallList(obj);

	glPopMatrix();
}

