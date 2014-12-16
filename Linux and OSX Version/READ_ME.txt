Author: Russell Mehring
Date: 12/15/2014

Liscense: Please only use this source code for personal use and/or educational use, and cite myself or any others whom I have cited below as necessary.  Enjoy!

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
    Esc: To close the program


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

8) Some source files from Professor Willem Schreuder-- "fatal.c", "errcheck.c", "loadtexbmp.c"  "project.c"
