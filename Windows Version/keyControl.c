/*
 * keyControl.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Russ Mehring
 */

#include "5229_Project.h"

/*
 * This function is called by GLUT when special keys are pressed
 * Allows user to rotate and spin the model
 * ***PLEASE NOTE that this works because redisplay contains the call to glRotatef
 * When redisplay is called the new zh and the parameters are read in and the new drawing is rotated
 */
void special(int key,int x,int y)
{
   //  Right arrow - increase rotation by 5 degree
   if (key == GLUT_KEY_RIGHT){
      th -= 2;
      turnRight = 1;
      toCenter = 0;
   }
   //  Left arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_LEFT){
      th += 2;
      turnLeft = 1;
      toCenter = 0;
   }
   //  up arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_UP){
      ph += 2;
      lookDown = 1;
	  toCenter2 = 0;
   }
   //  down arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_DOWN){
      ph -= 2;
      lookUp = 1;
	  toCenter2 = 0;
   }
   //Enable zooming in!
   else if ((key == GLUT_KEY_F1) && (dim > 5.0)){
       dim -= 0.1;
   }
   //Enable zooming out!
   else if (key == GLUT_KEY_F2){
       dim += 0.1;
   }
   else if (key == GLUT_KEY_F3){
       rotations++;
       glutTimerFunc(30, Spin, 1);
   }
   //code from example 9
   else if (key == GLUT_KEY_F4){
      axis = 1-axis;
   }
   //Turn on scaled model
   else if (key == GLUT_KEY_F5){
      scaled += 1;

      if (scaled > 24)
      {
    	  scaled = 0;
      }
   }
   //Switch viewing mode
   else if (key == GLUT_KEY_F6){
      view = 1-view;
   }
   //Turn on FPS
   else if (key == GLUT_KEY_F7){
       //Save the state of the eye position so that orientation is correct when we view in FP
       xpos = +2*dim*Sin(th)*Cos(ph);
       ypos = +2*dim        *Sin(ph);
       zpos = +2*dim*Cos(th)*Cos(ph);
       fps = 1-fps;
   }
   //Switch viewing mode
   else if (key == GLUT_KEY_F8){
      fog= 1-fog;
   }
   //Switch viewing mode
   else if (key == GLUT_KEY_PAGE_UP){
	   range += 1;
   }
   //Switch viewing mode
   else if (key == GLUT_KEY_PAGE_DOWN){

	  if (range - 1 > 0)
	  {
		  range -= 1;
	  }
   }
   //Call project to re-orient glOrtho
   Project(ar, dim);
   //Request display update
   glutPostRedisplay();
}

void specialUp(int key,int x,int y)
{
	//  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT){
	   turnRight = 0;
	   toCenter = 1;
    }
    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT){
	   turnLeft = 0;
	   toCenter = 1;
    }
    else if (key == GLUT_KEY_UP){
	   lookDown = 0;
	   toCenter2 = 1;
    }
    //  down arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_DOWN){
       lookUp = 0;
	   toCenter2 = 1;
    }
}

void keyUp (unsigned char key, int x, int y) {

	switch(key){

        case 'w': {
            //Done walking
        	walk = 0;

            break;
        }
        case 'W': {
            //Done walking
        	walk = 0;

            break;
        }
        case 'a': {
			//Done walking
			walk = 0;

			break;
		}
        case 'A': {
			//Done walking
			walk = 0;

			break;
		}
        case 's': {
			//Done walking
			walk = 0;

			break;
		}
		case 'S': {
			//Done walking
			walk = 0;

			break;
		}
		case 'd': {
			//Done walking
			walk = 0;

			break;
		}
		case 'D': {
			//Done walking
			walk = 0;

			break;
		}

		//Space no longer pressed
		case 32:{
			fire = 0;
			break;
		}
	}

}

void keyPressed (unsigned char key, int x, int y) {
	//These next 3 are for shooting our ball gun so that they go in the direction of the eye (hopefully)
	double eyeX = 2*dim*Sin(th)*Cos(ph);
	double eyeY = -2*dim        *Sin(ph);
	double eyeZ = -2*dim*Cos(th)*Cos(ph);
	dReal force = 1;//for force of gun

	switch(key){

        case 'w': {
            xpos += (Sin(th)* 0.3);
            zpos -= (Cos(th)* 0.3);
            //Start swaying gun while walking
            walk = 1;

            break;
        }
        case 'W': {
            xpos += (Sin(th)* 0.3);
            zpos -= (Cos(th)* 0.3);
            //Start swaying gun while walking
            walk = 1;

            break;
        }
        //strafing
        case 'a': {
        {
            xpos -= (Cos(th)) * 0.3;//Set x negative i.e. move object into negative x
            zpos -= (Sin(th)) * 0.3;//Set z negative
            //Start swaying gun while walking
			walk = 1;
        }
        break;
        }
        case 'A': {
        {
            xpos -= (Cos(th)) * 0.3;//Set x negative i.e. move object into negative x
            zpos -= (Sin(th)) * 0.3;//Set z negative
            //Start swaying gun while walking
			walk = 1;
        }
        break;
        }
        case 's': {
            xpos -= (Sin(th)* 0.3);
            zpos += (Cos(th)* 0.3);
            //Start swaying gun while walking
            walk = 1;

            break;
        }
        case 'S': {
            xpos -= (Sin(th)* 0.3);
            zpos += (Cos(th)* 0.3);
            //Start swaying gun while walking
            walk = 1;

            break;
        }
        //strafing
        case 'd': {
            xpos += (Cos(th)) * 0.3;//Set z positive
            zpos += (Sin(th)) * 0.3;//Set x positive i.e. move object into positive x
            //Start swaying gun while walking
			walk = 1;
            break;
        }
        case 'D': {
            xpos += (Cos(th)) * 0.3;//Set z positive
            zpos += (Sin(th)) * 0.3;//Set x positive i.e. move object into positive x
            //Start swaying gun while walking
			walk = 1;
            break;
        }
        case 'l':{
            light = 1 - light;
            glDisable(GL_LIGHT0);//Turn the light off if on
            break;
        }
        case 'L':{
            light = 1 - light;
            glDisable(GL_LIGHT0);//Turn the light off if on
            break;
        }
        case 'y':{
            ylight += 1;
            break;
        }
        case 'Y':{
            ylight -= 1;
            break;
        }
        case 'h':{
            distance += 1;
            break;
        }
        case 'H':{
            distance -= 1;

            if (distance <= 0)
            {
                distance = 0;
            }

            break;
        }
        //Alter lighting intensities
        case 'v':{
            emission += 1;

            if (emission >= 100)
            {
                emission = 100;
            }

            break;
        }
        case 'V':{
            emission -= 1;

            if (emission <= 0)
            {
                emission = 0;
            }

            break;
        }
        case 'b':{
            specular += 1;

            if (specular >= 100)
            {
                specular = 100;
            }

            break;
        }
        case 'B':{
            specular -= 1;

            if (specular <= 0)
            {
                specular = 0;
            }

            break;
        }
        case 'm':{
            diffuse += 1;

            if (diffuse >= 100)
            {
                diffuse = 100;
            }

            break;
        }
        case 'M':{
            diffuse -= 1;

            if (diffuse <= 0)
            {
                diffuse = 0;
            }

            break;
        }
        case 'n':{
             ambient += 1;

            if (ambient >= 100)
            {
                ambient = 100;
            }

            break;
        }
        case 'N':{
             ambient -= 1;

            if (ambient <= 0)
            {
                ambient = 0;
            }

            break;
        }

        //Space to fire balls
        case 32:{
            draw = 1;
            fire = 1;//Animate gun
        	dMatrix3 R;
            //Thanks to the source code for demo_crash in ode demo programs
        	dBodyEnable(ball_body2);
        	dBodySetPosition(ball_body2, xpos, ypos, zpos);//****Maybe lower y position to be level with the ground? did not try 11/4
        	dBodySetLinearVel(ball_body2, eyeX*force, ((eyeY*force)), eyeZ*force);//+ypos to give it same elevation as starting eyepos
        	dBodySetAngularVel (ball_body2, 0, 0, 0);//Force a linear angle, if this is not set then some default turns on and causes a curve
        	dRFromAxisAndAngle(R, 1, 0, 0, -(PI / 2));//Set the rotation matrix that sets the rotation of the ball
        	dBodySetRotation(ball_body2, R);

        	break;
        }
        //Press '1' to get another light
        case 49:{
            light1 = 1 - light1;
            glDisable(GL_LIGHT1);//Turn the light off if on
            break;
        }
        //Esc to close program
        case 27:{
            //Return ODE physics bodies to memory, requires dInitODE() in main() to not crash
            dWorldDestroy(world);
            dCloseODE();
            //Exit the program
            exit(0);
        }
    }
}
