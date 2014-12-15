Author: Russell Mehring
Date: 12/09/2014
CSCI 5229

To Compile: type 'make'

To Run: Linux/OSX: Type 'make run', everything's a target!
        Windows: Type 'Project'

To Clean: Type 'make clean'

*I have also included a backup makefile in it's own folder, if for some reason there is a compilation error with the 
makefile that is in the Project directory, please try replacing that makefile with the one in the folder.  ODE likes to 
complain about being in subdirectories with spaces in the path name, and the current makefile attempts to fix that. 

*******************************************************
                         ODE
(This should also install automatically in the directory for Linux/OSX users)
*******************************************************
TO INSTALL OPEN DYNAMICS ENGINE (ODE) ON LINUX/UBUNTU permanently:
  1) Ideally you should only have to go here and call the needed sudo apt-get's for all 4 'libode' commands at the top page: https://launchpad.net/ubuntu/+source/ode
  2) Worst case you will need to go to: http://ode-wiki.org/wiki/index.php?title=Manual:_Install_and_Use, this will give you directions in case mine are inadequate
     
     1. From here dl the latest tar file from http://sourceforge.net/projects/opende/
     2. Extract this tar file
     3. cd ode-0.13 (The current version as of my install)
     4. ./configure --enable-double-precision --with-trimesh=opcode --enable-new-trimesh --enable-shared 
     5. make
     6. make install
     7. *****ODE should now be installed on your system, but if you decide you like it AND want python bindings you can also call:
     8. cd bindings/python/ 
     9. python setup.py install 
     10. ***BE SURE TO DEFINE YOUR VERSION AS SINGLE PRECISION, otherwise it will throw an error message with this code***

TO INSTALL OPEN DYNAMICS ENGINE (ODE) ON WINDOWS:

   1) Please read my blog post at: https://www.tumblr.com/blog/russellmehring
*******************************************************

CONTROLS:

(1) Zooming (If NOT in first person view)
    
    F1: Zoom-In
    F2: Zoom-Out

(2) Rotations/views
   
    Up Arrow: y-axis up/ look up
    Down Arrow: y-axis down/ look down
    Left Arrow: Turn x-axis left/ look left
    Right Arrow: Turn x-axis right/ look right

(3) Perspectives/Movement/Shooting
    F6: Change from perspective to orthogonal view
    F7: Turn on/off a first person view 
        'w' to move forward
        'a' to move left
        's' to move back
        'd' to move right
        arrow keys to aim the camera view
        'space': Fire a ball from the eye position

(4) Lighting
    'l' or 'L': to turn on light0
	'1': to turn on light1
	'v': Increase Emission lighting %
	'V': Decrease Emission lighting %
	'b': Increase Specular lighting %
	'B': Decrease Specular lighting %
	'n': Increase Ambient lighting %
	'N': Decrease Ambient lighting %
	'm': Increase Diffuse lighting %
	'M': Decrease Diffuse lighting %
	'y': Raise light sources up y axis
	'Y': Lower light down y axis
	'h': Increase light distance
	'H': Decrease light distance
		
(5) Additional keys
    
    F3: Press F3 to launch pyramids
    F4: Press F4 to toggle the axis on/off
    F6: Switch b/w Orthogonal/perspective view (not recommended)
    F7: Turn first person view on/off (not recommended)  
    F8: Turn fog on/off  
    Esc: To close the program


Of Interest (why I should get an A): 

1) My terrain was generated using a simplex algorithm which results in nice curves and variability beyond what a human could specify for terrain.  This did take several days to achieve since C does not have access to GMP math like C++ does, so I had to find a simplex algorithm and get that to work.  Then I had to derive how to get openGL to draw a landscape based on the output.  I also used this method to simulate electricity when the pyramid opens in the center.
        
2) The physics took a couple weeks to get working (and was a stretch goal), ODE is a pretty easy engine to use once you figure it out, but figuring it out took a very long time due to lack of message board activity and example programs that use ODE AND OpenGL.  Hopefully you find the physics aspects of this project entertaining. Please note that the physics do act a bit strangely if you are too close to objects when you fire the ball gun (this is due to single precision being in use in the program), the engine often resolves the collision by pushing one object through the other rather than bouncing it off.

3) It's not a major thing, but getting the skybox to appear without visible lines took a very long time with a lot of tweaking between working on drawing objects in the program. I'm pretty happy with how it turned out, however I was never able to get the 'ground' of the skybox to appear without lines, however you'd have to walk off the terrain to see that. 

4) Getting the first person view with a moving gun took some time, and I think it really draws in the user.  Overall I think I did a nice job of creating an immersive game world--at least as far as one could expect from an amateur.  I was a bit disappointed I didn't quite achieve the same world/look/feel as FRACT-OSC as I had originally planned, but when I realized how many shaders I would need to get that I turned my focus onto getting physics working--which took much longer than anticipated.  Next semester I should be able to combine my physics knowledge with learning shaders.

5) Along with having physical properties applid to (almost) every object in the scene, I have lots of animations happening as well based on whether objects are being interacted with.  This took a bit more time to implement, but was at times a challenge to perfect, and I think it's important to get credit for all those.  

6) The original intention behind most of my objects in the scene was to perfect them once, then draw lots of them later.  However things like the opening doorway turned out to not be as scalable as I wanted them to be once I added physics.  Next time I think I would plan out some of the objects better. I found myself still designing new objects in the last week of class rather than creating the game world.  But this resulted in a lot more targets for the user to shoot at.  

7) Accurate normals/lighting on everything (hard to do when adding in obj files from mysterious sources!)

8) The working makefile took a LOT of panic time to get working

Overall, I think I achieved my major goal of creating a game world along with getting physics working. There are several things I would do differentlyif I were to do it again (mentioned above), however I'm pretty happy with the results.  I think I ended up with more of a shooting range than a FRACT OSC puzzle world like I wanted, but now I think I understand how I would get to the puzzle stuff if I were to do it again.  I also really wanted to add sound to my scene, but I spent  several hours trying to get SDL working on Windows and was unable to get it going.  Again this was delayed due to the complexity of getting physics working, but next time I definitely want sound, and shaders, lots of shaders.  

Citations:

1) I used the code to get gluPerspective to work from ex.9 of the course material.  I also copied the idea for turning the axis on/off.  I also used the code to change between orthogonal/perspective views.

2) I attempted to get the first person view going (it sort of works) but I started by following the code on
http://www.swiftless.com/tutorials/opengl/camera.html 

3) I used the algorithm on http://fullonsoftware.co.uk/snippets/content/Math_-_Calculating_Face_Normals.pdf to calculate the normal vectors of my pyramids

4) To get my terrain I got a significant amount of help from Miles Rufat-Latre and from https://code.google.com/p/battlestar-tux/source/browse/procedural/simplexnoise.cpp to get the simplex algorithm working

5) Thanks to Zach Anders for helping me get my makefile working with ode (BIG thanks!)

6) OBJ file 'raygun_mark2' from http://tf3dm.com/3d-model/raygun-mark-2-20039.html 
submitted by user: n123q45, personnal use only liscense

7) OBJ file 'Drone' from http://tf3dm.com/3d-model/drone-86628.html
submitted by user: 3dregenerator, personnal use only liscense
