/*
 * spin.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Russ Mehring
 */
#include "5229_Project.h"

int colorred = 0;
int colorgreen = 0;
int colorblue = 0;

//Disassembles pyramid, rotates the parts 180 degrees, then reassembles the greater pyramid!
void Spin(int value)
{
    if ((rh < ((180.0*rotations))))
    {
        if((posZ < 2.0) && (posX < 2.0))
        {

            posZ += 0.01;
            posX += 0.01;
            if (posZ > 0.5)
            {
                space += 0.01;
            }
        }
        //Begin rotation out in space
        if((posZ > 0.75) && (posX > 0.75))
        {
        	//Call Lightning
        	pyramidRotating = 1;
        	//Rotate value to rotate pyramids
            rh += 1.0;
            //Handle red transformations
            if ((red > 0.00) && (colorred == 0))
            {
                red -= 0.001;
            }

                if(red <= 0.00)
                {
                    colorred = 1;
                }

                    if (colorred == 1)
                    {
                        red += 0.001;
                        //Time to revert colors in opposite direction
                        if (red >= 1.00)
                        {
                            colorred = 0;
                        }
                    }
            //Handle green transformations
            if ((green > 0.00) && (colorgreen == 0))
            {
                green -= 0.001;
            }

                if(green <= 0.00)
                {
                    colorgreen = 1;
                }

                    if (colorgreen == 1)
                    {
                        green += 0.001;
                        //Time to revert colors in opposite direction
                        if (green>= 1.00)
                        {
                            colorgreen = 0;
                        }
                    }
            //Handle blue transformations
            if ((blue > 0.3) && (colorblue == 0))
            {
                blue -= 0.001;
            }

                if(blue <= 0.3)
                {
                    colorblue = 1;
                }

                    if (colorblue == 1)
                    {
                        blue += 0.001;
                        //Time to revert colors in opposite direction
                        if (blue >= 1.00)
                        {
                            colorblue = 0;
                        }
                    }
        }

        //Request display update
        glutPostRedisplay();
        //Try creating an animation
        glutTimerFunc(30, Spin, 1);
    }

    //rotation complete, reassemble pyramid
    if (rh == (180.0 * rotations) && (posZ > 0.0) && (posX > 0.0))
    {
    	//Turn off lightning, reassembling
    	pyramidRotating = 0;
    	posZ -= 0.01;
        posX -=0.01;
        //keep the pyramid in the correct y plane
        if(space > 0.0)
        {
            space -=0.01;
        }

        if (posZ < 0.0)
        {
            posZ = 0.0;
            space = 0.0;
        }
            if (posX < 0.0)
            {
                posX = 0.0;
            }
        //Request display update
        glutPostRedisplay();
        //Try creating an animation
        glutTimerFunc(30, Spin, 1);
    }
}
