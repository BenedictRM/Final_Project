/*
 ============================================================================
 Name        : ode.c
 Author      : Russell Mehring
 Version     : 10/30/2014
 Copyright   : Your copyright notice
 Description : Lighting for CSCI 5229
 ============================================================================
 */
#include "5229_Project.h"
#include <ode/odeconfig.h>//Needed so that dInfinity macro is seen by these functions

//Assistance with ode from http://www.alsprogrammingresource.com/basic_ode.html
//and from the ODE user manual, not a lot of resources out there!
void initODE()
{
	int i;
	int j = 0;//For placing skyPanels
	int k = 0;//For placing sphere in box
	int q = 0;//For placing target boxes
	int r = 0;//For placing targetBoxes
	int s = 0;//FOr placing targetBoxes
	dReal radius = 0.5;//For sphere's in scene that bounce around/ get shot
	dMass m;//For mass of sphere
	dMass mp;//For mass of platform
	dMass md;//For mass of doorway
	dMass mpy;//For mass of pyramid
	dMass mbox;//For box of balls
	dMass msp;//For skyPanels
	dMass mtb;//For targetBox

	// Create a new, empty world and assign its ID number to World. Most applications will only need one world.
    world = dWorldCreate();

    // Create a new collision space and assign its ID number to Space, passing 0 instead of an existing dSpaceID.
    // There are three different types of collision spaces we could create here depending on the number of objects
    // in the world but dSimpleSpaceCreate is fine for a small number of objects. If there were more objects we
    // would be using dHashSpaceCreate or dQuadTreeSpaceCreate (look these up in the ODE d
    spacePhy = dSimpleSpaceCreate(0);

    // Create a joint group object and assign its ID number to contactgroup. dJointGroupCreate used to have a
    // max_size parameter but it is no longer used so we just pass 0 as its argument.
    contactgroup = dJointGroupCreate(0);

    //Set the gravity of the world where y is up
    dWorldSetGravity(world, 0, -0.1, 0);

    // These next two functions control how much error correcting and constraint force mixing occurs in the world.
    // Don't worry about these for now as they are set to the default values and we could happily delete them from
    // this example. Different values, however, can drastically change the behaviour of the objects colliding, so
    // I suggest you look up the full info on them in the ODE docs.
    dWorldSetERP(world, 0.2);
    dWorldSetCFM(world, 1e-5);

    // This function sets the velocity that inter-penetrating objects will separate at. The default value is infinity.
    dWorldSetContactMaxCorrectingVel(world, 0.9);

    // This function sets the depth of the surface layer around the world objects. Contacts are allowed to sink into
    // each other up to this depth. Setting it to a small value reduces the amount of jittering between contacting
    // objects, the default value is 0.
    dWorldSetContactSurfaceLayer(world, 0.0);

    // To save some CPU time we set the auto disable flag to 1. This means that objects that have come to rest (based
    // on their current linear and angular velocity) will no longer participate in the simulation, unless acted upon
    // by a moving object. If you do not want to use this feature then set the flag to 0. You can also manually enable
    // or disable objects using dBodyEnable and dBodyDisable, see the docs for more info on this.
    dWorldSetAutoDisableFlag(world, 1);

    //This brings us to the end of the world settings, now we have to initialize the objects themselves.

    //****************Ball 1
    // Create a new body for our object in the world and get its ID.
    ball_body = dBodyCreate(world);
    //Set ball1 geometries
    dMassSetZero(&ball_mass);
    dMassSetSphereTotal(&ball_mass, DENSITY, 2.0);
    dBodySetMass(ball_body, &ball_mass);

    ball_geom = dCreateSphere(spacePhy, radius);
    dGeomSetData(ball_geom, (void *)"ball");
    dGeomSetBody(ball_geom, ball_body);
    dBodyEnable(ball_body);
    //Next we set the position of the new body
	dBodySetPosition(ball_body, 5, 100, 15);

    //****************Ball 2
    // Create a new body for our object in the world and get its ID.
	ball_body2 = dBodyCreate(world);
	//Set ball1 geometries
	dMassSetZero(&ball_mass2);
	dMassSetSphereTotal(&ball_mass2, DENSITY, 2.0);
	dBodySetMass(ball_body2, &ball_mass2);

	ball_geom2 = dCreateSphere(spacePhy, radius);
	dGeomSetData(ball_geom2, (void *)"ball2");
	dGeomSetBody(ball_geom2, ball_body2);
	dBodySetGravityMode (ball_body2, 0);

    //******End of ball 2

	//*************Ball 3, a new way of creating a ball with physical properties
	ball_body3 = dBodyCreate(world);
	dMatrix3 R;

	dBodySetPosition(ball_body3, -5, 100, 15);
	dRFromAxisAndAngle(R, 1, 0, 0, -1.57);
	dBodySetRotation(ball_body3, R);

	// Here we use dMassSetSphere instead of dMassSetBox
	// and we pass the local radius variable as the third parameter
	dMassSetSphere(&m, DENSITY, radius);

	// To create the sphere object we use dCreateSphere and pass it the same local radius variable
	ball_geom3 = dCreateSphere(spacePhy, radius);
	dGeomSetBody(ball_geom3, ball_body3);
	dBodySetMass(ball_body3, &m);
    //*****End of ball3

	//*************Box o balls properties
    for (i = 0; i < 61; i++)
    {
    	// Create a new body for our object in the world and get its ID.
		balls_body[i] = dBodyCreate(world);
		//Set ball1 geometries
		dMassSetZero(&balls_mass[i]);
		dMassSetSphereTotal(&balls_mass[i], DENSITY, 2.0);
		dBodySetMass(balls_body[i], &balls_mass[i]);

		balls_geom[i] = dCreateSphere(spacePhy, radius);
		dGeomSetData(balls_geom[i], (void *)"ball");
		dGeomSetBody(balls_geom[i], balls_body[i]);
		dBodyDisable(balls_body[i]);//Disable bodies, enabled auto after hit
		//Box 1
		if (i <31)
		{
		     dBodySetPosition(balls_body[i], (-20), 28.5, 7.0);//(xpos b/w -20 and -12, ypos b/w 28 and 32, zpos between 0 and 16)
		}
			//Box 2
			if (i >= 31)
			{
				 dBodySetPosition(balls_body[i], (25), 38.5, -14.0);//(xpos b/w -20 and -12, ypos b/w 28 and 32, zpos between 0 and 16)
			}
		k++;
    }
	//******End of Box o Balls

	//**************platform geometries
	//create 5 platform's with physics things
	for (i = 0; i < 15; i++)
	{
		platform_body[i] = dBodyCreate(world);//Add the platform body to the world
		//Set the geom platform

		// Here we use dMassSetBox
		//set DENSITY to be very high to prevent it from being moved from balls
		dMassSetBox(&mp, DENSITY*1500,  4.5, 0.5, 18.0);

		//It works better if the invisible physics box is slightly larger than the object we're drawing
		platform_geom[i] = dCreateBox(spacePhy,  4.5, 0.5, 18.0);
		dGeomSetBody(platform_geom[i], platform_body[i]);
		dBodySetMass(platform_body[i], &mp);

		//Set/get whether the body is influenced by the world's gravity or not. If mode is nonzero it is, if mode is zero, it isn't. Newly created bodies are always influenced by the world's gravity.
		dBodySetGravityMode (platform_body[i], 0);
	}
    //*******End of platform geometries

	//*******Set the doorway properties, 18 platforms make all 3 doors
    for (i = 0; i < 18; i++)
    {
		doorway_body[i] = dBodyCreate(world);//Add the platform body to the world
		//Set the geom platform

		// Here we use dMassSetBox
		//set DENSITY to be very high to prevent it from being moved from balls
		dMassSetBox(&md, DENSITY*1500, 4.0, 0.25, 2.0);

		//It works better if the invisible physics box is slightly larger than the object we're drawing
		doorway_geom[i] = dCreateBox(spacePhy, 4.0, 0.25, 2.0);
		dGeomSetBody(doorway_geom[i], doorway_body[i]);
		dBodySetMass(doorway_body[i], &md);

		//Set/get whether the body is influenced by the world's gravity or not. If mode is nonzero it is, if mode is zero, it isn't. Newly created bodies are always influenced by the world's gravity.
		dBodySetGravityMode (doorway_body[i], 0);
    }
	//*******End of doorway properties

    //*******Set the Box o' Balls properties, 6 sides total make the larger box
    for (i = 0; i < 12; i++)
    {
         boxSide_body[i] = dBodyCreate(world);
    }

    //Box 1
    //Need to set position here to affect the box with gravity
    dBodySetPosition(boxSide_body[0], -20.0, 28.0, 16);//Front, rotated 0 deg. on y axis
    dBodySetPosition(boxSide_body[1], -12.25, 28.0, 8.0);//Right, rotated 90 deg. on y axis
    dBodySetPosition(boxSide_body[2], -20.0, 28.0, 0);//Back, rotated 0 deg. on y axis
    dBodySetPosition(boxSide_body[3], -27.75, 28.0, 8.0);//Left, rotated 90 deg. on y axis
    dBodySetPosition(boxSide_body[4], -20.0, 32.0, -0.23);//Top, rotated 90 deg. on x axis
    dBodySetPosition(boxSide_body[5], -20.0, 28.0, -0.23);//Bottom, rotated 90 deg. on x axis

    //Need to set position here to affect the box with gravity
    //Box 2
	dBodySetPosition(boxSide_body[6], 30.0, 38.0, -16);//Front, rotated 0 deg. on y axis
	dBodySetPosition(boxSide_body[7], 22.25, 38.0, -8.0);//Right, rotated 90 deg. on y axis
	dBodySetPosition(boxSide_body[8], 30.0, 38.0, 0);//Back, rotated 0 deg. on y axis
	dBodySetPosition(boxSide_body[9], 37.75, 38.0, -8.0);//Left, rotated 90 deg. on y axis
	dBodySetPosition(boxSide_body[10], 30.0, 42.0, -16.23);//Top, rotated 90 deg. on x axis*****Unsure about z here
	dBodySetPosition(boxSide_body[11], 30.0, 38.0, -16.23);//Bottom, rotated 90 deg. on x axis

	//Box 1
    for (i = 0; i < 6; i++)
	{
		if (i < 4)//Small sides
		{
			// Here we use dMassSetBox, we want a lower density here to be able to destroy the box
			dMassSetBox(&mbox, DENSITY, 16, 1, 0.25);

			//It works better if the invisible physics box is slightly larger than the object we're drawing
			boxSide_geom[i] = dCreateBox(spacePhy, 16, 1, 0.25);

			dGeomSetBody(boxSide_geom[i], boxSide_body[i]);
			dBodySetMass(boxSide_body[i], &mbox);
		}
		     if (i >=4)//Large top and bottom
		     {
		    	// Here we use dMassSetBox, we want a lower density here to be able to destroy the box
				dMassSetBox(&mbox, DENSITY, 16, 16, 0.5);

				//It works better if the invisible physics box is slightly larger than the object we're drawing
				boxSide_geom[i] = dCreateBox(spacePhy, 16, 16, 0.5);

				dGeomSetBody(boxSide_geom[i], boxSide_body[i]);
				dBodySetMass(boxSide_body[i], &mbox);
		     }
		//Turn off colliding object force effects on this geom so that it is stationary (less density = greater effect on objects colliding into this one)
		dBodyDisable(boxSide_body[i]);

		//Set/get whether the body is influenced by the world's gravity or not. If mode is nonzero it is, if mode is zero, it isn't. Newly created bodies are always influenced by the world's gravity.
		dBodySetGravityMode (boxSide_body[i], 1);
	}
    //Box 2
    for (; i < 12; i++)
	{
    	if (i < 10)//Small sides
		{
			// Here we use dMassSetBox, we want a lower density here to be able to destroy the box
			dMassSetBox(&mbox, DENSITY, 16, 1, 0.5);

			//It works better if the invisible physics box is slightly larger than the object we're drawing
			boxSide_geom[i] = dCreateBox(spacePhy, 16, 1, 0.5);

			dGeomSetBody(boxSide_geom[i], boxSide_body[i]);
			dBodySetMass(boxSide_body[i], &mbox);
		}
			 if (i >=10)//Large top and bottom
			 {
				// Here we use dMassSetBox, we want a lower density here to be able to destroy the box
				dMassSetBox(&mbox, DENSITY, 16, 16, 1.0);

				//It works better if the invisible physics box is slightly larger than the object we're drawing
				boxSide_geom[i] = dCreateBox(spacePhy, 16, 16, 1.0);

				dGeomSetBody(boxSide_geom[i], boxSide_body[i]);
				dBodySetMass(boxSide_body[i], &mbox);
			 }
		//Turn off colliding object force effects on this geom so that it is stationary (less density = greater effect on objects colliding into this one)
		dBodyDisable(boxSide_body[i]);

		//Set/get whether the body is influenced by the world's gravity or not. If mode is nonzero it is, if mode is zero, it isn't. Newly created bodies are always influenced by the world's gravity.
		dBodySetGravityMode (boxSide_body[i], 1);
	}
    //*******End of Box o' Balls properties

    //*******Set the pyramid properties, 120 pyramids make diamond excluding inverted that fill holes (gotta cheat)
	pyramid_body = dBodyCreate(world);//Add the platform body to the world
	//Set the geom platform

	// Here we use dMassSetBox
	//set DENSITY to be very high to prevent it from being moved from balls
	dMassSetBox(&mpy, DENSITY*1500, 2.6, 4.5, 2.6);

	//It works better if the invisible physics box is slightly larger than the object we're drawing
	pyramid_geom = dCreateBox(spacePhy, 2.6, 4.5, 2.6);
	dGeomSetBody(pyramid_geom, pyramid_body);
	dBodySetMass(pyramid_body, &mpy);
	dBodyDisable(pyramid_body);
	//Set/get whether the body is influenced by the world's gravity or not. If mode is nonzero it is, if mode is zero, it isn't. Newly created bodies are always influenced by the world's gravity.
	dBodySetGravityMode (pyramid_body, 0);
    //*******End of pyramid properties

	//*******skyPanels physics
    for(j = 0; j < 60; j++)
    {
		skyPanel_body[j] = dBodyCreate(world);//Add the skypanel body to the world
		//Set the geom skypanel
		// Here we use dMassSetBox
		//set DENSITY to be very high to prevent it from being moved from balls
		dMassSetBox(&msp, DENSITY*1500, 3.0, 7.0, 1.0);

		//It works better if the invisible physics box is slightly larger than the object we're drawing
		skyPanel_geom[j] = dCreateBox(spacePhy, 3.0, 7.0, 1.0);
		dGeomSetBody(skyPanel_geom[j], skyPanel_body[j]);//Bind the geom to the body so that we only need to place the body to also set the geom
		dBodySetMass(skyPanel_body[j], &msp);
		dBodyDisable(skyPanel_body[j]);
		//Set/get whether the body is influenced by the world's gravity or not. If mode is nonzero it is, if mode is zero, it isn't. Newly created bodies are always influenced by the world's gravity.
		dBodySetGravityMode (skyPanel_body[j], 0);//Gravity off
    }
	//*******End of skyPanels physics
    //*******Set targetBox physics
    for(q = 0; q < 114; q++)
	{
    	targetBox_body[q] = dBodyCreate(world);//Add the skypanel body to the world
    	//Set the geom target box
		// Here we use dMassSetBox
		dMassSetBox(&mtb, (0.05), 4.0, 4.0, 4.0);

		//It works better if the invisible physics box is slightly larger than the object we're drawing
		targetBox_geom[q] = dCreateBox(spacePhy, 4.0, 4.0, 4.0);
		dGeomSetBody(targetBox_geom[q], targetBox_body[q]);//Bind the geom to the body so that we only need to place the body to also set the geom
		dBodySetMass(targetBox_body[q], &mtb);
		dBodyDisable(targetBox_body[q]);
		//Set/get whether the body is influenced by the world's gravity or not. If mode is nonzero it is, if mode is zero, it isn't. Newly created bodies are always influenced by the world's gravity.
		dBodySetGravityMode (targetBox_body[q], 1);//Gravity on
		//Pile 1
		if(q < 22)
		{
		     dBodySetPosition(targetBox_body[q], (-60 + (s * 4)), (2 + r), -30);//Set position here, otherwise unaffected by gravity
		     s++;//update x axis
		     if (q == 8)
		     {
		    	 r += 4;
		    	 s = 0;
		     }
		        if (q == 14)
		        {
		        	r += 4;
		        	s = 0;
		        }
		            if (q == 18)
		            {
		            	r += 4;
		            	s = 0;
		            }
		                if (q == 20)
		                {
		                	r += 4;
		                	s = 0;
		                }
							//Reset values for next pile of boxes
							if (q == 21)
							{
								r = 0;
								s = 0;
							}
		}
		     //Pile 2
			 if((q > 21) && (q < 43))
		     {
		    	 dBodySetPosition(targetBox_body[q], (-30 + (s * 4)), (2 + r), 90);
		    	 s++;//Update x pos
		    	 if (q == 29)
				 {
					 r += 4;
					 s = 0;
				 }
					if (q == 35)
					{
						r += 4;
						s = 0;
					}
						if (q == 39)
						{
							r += 4;
							s = 0;
						}
							if (q == 41)
							{
								r += 4;
								s = 0;
							}
								//Reset values for next pile of boxes
								if (q == 42)
								{
									r = 0;
									s = 0;
								}
		     }
             //Pile 3
		     if((q > 42) && (q < 64))
			 {
				 dBodySetPosition(targetBox_body[q], (110), (2 + r), (0 + (s * 4)));
				 s++;//Update x pos
				 if (q == 50)
				 {
					 r += 4;
					 s = 0;
				 }
					if (q == 56)
					{
						r += 4;
						s = 0;
					}
						if (q == 60)
						{
							r += 4;
							s = 0;
						}
							if (q == 62)
							{
								r += 4;
								s = 0;
							}
								//Reset values for next pile of boxes
								if (q == 63)
								{
									r = 0;
									s = 0;
								}
			 }
				 //Pile 4
		         if((q > 63) && (q < 85))
				 {
					 dBodySetPosition(targetBox_body[q], (-90), (2 + r), (0 + (s * 4)));
					 s++;//Update x pos
					 if (q == 71)
					 {
						 r += 4;
						 s = 0;
					 }
						if (q == 77)
						{
							r += 4;
							s = 0;
						}
							if (q == 81)
							{
								r += 4;
								s = 0;
							}
								if (q == 83)
								{
									r += 4;
									s = 0;
								}
									//Reset values for next pile of boxes
									if (q == 84)
									{
										r = 0;
										s = 0;
									}
				 }
	     //Box tower 1
		 if((q > 84) && (q < 94))
		 {
			 dBodySetPosition(targetBox_body[q], (-60), (2 + r), (30));
			 r+=1;//Put boxes slightly inside each other
			 if (q == 93)
			 {
				 r = 0;//Reset r
			 }
		 }
			 //Box tower 2
			 if((q > 93) && (q < 104))
			 {
				 dBodySetPosition(targetBox_body[q], (70), (2 + r), (-90));
				 r+=1;//Put boxes slightly inside each other
				 if (q == 103)
				 {
					 r = 0;//Reset r
				 }
			 }
				 //Box tower 3
				 if((q > 103) && (q < 114))
				 {
					 dBodySetPosition(targetBox_body[q], (60), (2 + r), (90));
					 r+=1;//Put boxes slightly inside each other
					 if (q == 103)
					 {
						 r = 0;//Reset r
					 }
				 }
	}
    //*******End of targetBox Physics
    //Set the ground location:
	//First three param's set the normal vector, last param sets the distance according to the plane equation equation a*x+b*y+c*z=d and must have length 1
	ground = dCreatePlane(spacePhy, 0, 2.0, 0, 0);//Plane where I have most objects sitting, y =2

    // Here I have set the initial linear velocity to stationary and let gravity do the work on our spheres, but you can experiment
    // with the velocity vector to change the starting behavior. You can also set the rotational velocity for the new
    // body using dBodySetAngularVel which takes the same parameters.
    tempVect.x = 0.0;
    tempVect.y = 0.0;
    tempVect.z = 0.0;
    dBodySetLinearVel(ball_body, tempVect.x, tempVect.y, tempVect.z);
    dBodySetLinearVel(ball_body2, tempVect.x, tempVect.y, tempVect.z);
    dBodySetLinearVel(ball_body3, tempVect.x, tempVect.y, tempVect.z);

    dWorldSetLinearDamping(world, 0.00001);
    dWorldSetAngularDamping(world, 0.005);
    dWorldSetMaxAngularSpeed(world, 200);
}


//Simulation Loop to test for collisions on every frame
void simLoop()
{
	//dSpaceCollide determines whih pairs of geoms are potentially interecting,
    //the callback function det's actual collisions before adding all the contact joints to groupcontact
    //This allows us control over the effect in the contact joints
    dSpaceCollide(spacePhy, 0, &nearCallback);

    // Now we advance the simulation by calling dWorldQuickStep. This is a faster version of dWorldStep but it is also
    // slightly less accurate. As well as the World object ID we also pass a step size value. In each step the simulation
    // is updated by a certain number of smaller steps or iterations. The default number of iterations is 20 but you can
    // change this by calling dWorldSetQuickStepNumIterations.
    dWorldQuickStep(world, 0.3);

    //Remove all temporary collision joints now that the world has been stepped
    dJointGroupEmpty(contactgroup);

    //And we finish by calling DrawGeom which renders the objects according to their type or class
   // DrawGeom(object.Geom[0], 0, 0, 0);
}

//All pairs of geoms that are potentially intersecting will be passed by dSpaceCollide to this function.
//Here we can determine which objects are actually colliding by making a call to dCollide and change the
//behavior of the joints before adding them to the joint group. The first parameter would be the user data
//pointer passed to dSpaceCollide if we had provided it. The second and third parameters are the two potentially intersecting geoms.
void nearCallback (void *data, dGeomID o1, dGeomID o2)
{
    //Temporary index for each contact
    int i;
    int numc = 0;

    //Get the dynamics body for each geom
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);

    //Create an array of dContact objects to hold the contact joints
    dContact contact[MAX_CONTACTS];

    // Now we set the joint properties of each contact. Going into the full details here would require a tutorial of its
    // own. I'll just say that the members of the dContact structure control the joint behaviour, such as friction,
    // velocity and bounciness. See section 7.3.7 of the ODE manual and have fun experimenting to learn more.

    for (i = 0; i < MAX_CONTACTS; i++)
    {
        contact[i].surface.mode = dContactBounce | dContactSoftCFM;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.mu2 = 5000;
        contact[i].surface.bounce = 0.98;
        contact[i].surface.bounce_vel = 0.5;
        contact[i].surface.soft_cfm = 0.01;
    }

    // Here we do the actual collision test by calling dCollide. It returns the number of actual contact points or zero
    // if there were none. As well as the geom IDs, max number of contacts we also pass the address of a dContactGeom
    // as the fourth parameter. dContactGeom is a substructure of a dContact object so we simply pass the address of
    // the first dContactGeom from our array of dContact objects and then pass the offset to the next dContactGeom
    // as the fifth paramater, which is the size of a dContact structure. That made sense didn't it?
    numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact));
    if (numc > 0)
    {
        // To add each contact point found to our joint group we call dJointCreateContact which is just one of the many
        // different joint types available.
        for (i = 0; i < numc; i++)
        {
            //dJointCreateContact needs to know which world and joint group to work with as well as the dContact
            //object itself. It returns a new dJointID which we then use with dJointAttach to finally create the
            //temporary contact joint between the two geom bodies.

            dJointID c = dJointCreateContact(world, contactgroup, &contact[i]);
            dJointAttach(c, b1, b2);
        }
    }
}

//This function serves as a generic rendering routine for all types of geoms, using a different
//rendering function for each class of geom. In keeping with the examples that came with the ODE
//library, the DrawGeom function takes four parameters. The first is the geom's ID, then its
//position vector, rotation matrix and lastly a flag used to toggle the rendering of the geoms axis aligned bounding box

void DrawGeom (dGeomID g, const dReal *pos, const dReal *R, int show_aabb)
{
    // If the geom ID is missing then return immediately.
    if (!g)
    {
        return;
    }

    // If there was no position vector supplied then get the existing position.
    if (!pos)
    {
        pos = dGeomGetPosition (g);
    }

    // If there was no rotation matrix given then get the existing rotation.
    if (!R)
    {
        R = dGeomGetRotation (g);
    }

    // Get the geom's class type.
    int type = dGeomGetClass (g);

    if (type == dBoxClass)
    {
        // Create a temporary array of floats to hold the box dimensions.
        dReal sides[3];
        dGeomBoxGetLengths(g, sides);

        // Now to actually render the box we make a call to DrawBox, passing the geoms dimensions, position vector and
        // rotation matrix. And this function is the subject of our next discussion.
       // DrawBox(sides, pos, R);
    }
}
