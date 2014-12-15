/*
 * idle.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Russ Mehring
 */
#include "5229_Project.h"

void idle()
{
    //Elapsed time in seconds
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;

    if (stop == 0)
    {
    	//Now update light's position such that it rotates around
        az = fmod(90*t,360.0);
    }

    //Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}
