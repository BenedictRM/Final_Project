//Declare includes
#ifndef CSCIx229
#define CSCIx229

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

//Be sure to add the ode_singled.dll file to the same place as the executable!
//The path is defined in 'preferences' -> 'includes' -> 'include paths' then specify 'include' from ode-0.13, only include the parent 'include', not child 'ode'
#include <ode/ode.h>

//look at #include glm for math for simplex etc. for vectors and terrains, c++ strictly for this library!
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//Declare project variables
extern double th;  // Rotation angle
extern double ph; //Elevation of view angle for gluPerspective
extern double rh;  //Rotation angle for individual triangles
extern double dim;//dimension of the world
extern double ar; //Aspect Ratio
extern double red;//to morph colors
extern double green;//to morph colors
extern double blue;//to morph colors
extern double posZ;//For moving pyramid toward positive/negative z
extern double posX;//For moving pyramid toward pos/neg x plane
extern double space;//For spacing out pyramids
extern double xpos;//X pos of camera
extern double ypos;//Y pos of camera
extern double zpos;//Z pos of camera
extern double zh;  //Spin angle
//Door variables
extern double size;  //Size of door
extern double size2;  //Size of door
extern double size3;  //Size of door
extern double xplace;
extern double yplace;
extern double yplacetb;
extern double rotate;
//Door 2
extern double xplace2;
extern double yplace2;
extern double yplacetb2;
extern double rotate2;
//Door 3
extern double xplace3;
extern double yplace3;
extern double yplacetb3;
extern double rotate3;
extern double r;//Radius of spheres
extern double pitch;//For rolling drones
extern double yaw;
extern float walkx;//For moving gun left while walking
extern float shinyvec[];//Shininess (value)
extern float ylight;//Elevation of light
extern float spin;
extern float spin2;
extern float zero;
extern float zero2;
extern float octaves;//Simplex
extern float persistence;//Simplex
extern float scale;//Simplex
extern float gunShootAngle;//Control the angle of the gun on the y axis
extern float gunWalkAngleZ;//Control the angle of the gun on the z axis
extern float recoil;//To control how fast gun recoil
extern float gunTurnAngle;//For turning angle for gun
extern float gunLookAngle;//For looking up/down angle for gun
extern float lineWidth;//Spacing between points in lightning
extern int width;//For simplex
extern int sqwidth;//For simplex
extern int res;//For simplex
extern int tot;//For simplex
extern int rotations;//To allow multiple spins to happen
extern int colorred;
extern int colorgreen;
extern int colorblue;
extern int view;
extern int axis;//For displaying axis code from example 9
extern int scaled;//For displaying a scaled model to meet project requirements
extern int fps;
extern int light;//To turn lighting on/off
extern int light1;//To turn lighting on/off with an additional light
extern int distance;  //Light distance
extern int emission;  //Emission intensity (%)
extern int ambient;  // Ambient intensity (%)
extern int diffuse;  // Diffuse intensity (%)
extern int specular;  // Specular intensity (%)
extern int stop;//stop the light from rotating
extern int widthActual;//For reshape func
extern int heightActual;//For reshape func
extern int az;  //Light azimuth
extern int draw;  //draw ball
extern int inc;//For incrementing box o balls for loop (spheres specifically)
extern int ballx;//For coloring spheres in box o balls
extern int bally;//For coloring spheres in box o balls
extern int ballz;//For coloring spheres in box o balls
extern int obj;//for object list for gun specifically
extern int obj2;//for object list for star destroyer
extern int walk;//For moving gun while walking
extern int left;//For moving gun to left while walking
extern int right;//For moving gun right
extern int sway;//For controlling alternating left and right gun movement
extern int fire;//To tell program gun has been fired
extern int w;
extern int animating;//to test if gun still needs to complete its animation
extern int animating2;//To test if gun is still firing
extern int turnRight;//For turning gun animation
extern int turnLeft;//For turning gun animation
extern int lookDown;//For looking up/down gun animation
extern int lookUp;//For looking up/down gun animation
extern int back;//Return gun to center after firing
extern int toCenter;//Correcting for turning the gun, returns gun to center of screen
extern int toCenter2;//Correcting for turning the gun, returns gun to center of screen
extern int noPoints;//Number of points in lightning
extern int randOctaves;//Random octaves for lightning
extern int randPersistence;//Random persistence for lightning
extern int randScale;//Random scale for lightning
extern int range;//Range of random values for simplex for lightning cal's
extern int colorStep;//To step through color array
extern int pyramidRotating;//For turning lightning on/off
extern int fog;
extern unsigned int texture[];  //Texture names
extern unsigned int skyBox[];  //Texture names for skybox specifically

//For calculating normals
struct normal{
    double x;
    double y;
    double z;
};
//Struct to hold values for SIMPLEX vectors
struct vec3{
	float x;
	float y;
	float z;
};
//Struct to hold values for SIMPLEX vectors
struct vec2{
	float x;
	float y;
};

//Must declare and define these structs in the header for other functions to see them
/*
int res = (initwidth / initsqwidth) + 1;
int	tot = res * res;*/
struct vec3 norms[1681];//Use tot value to get array size
struct vec3 data[1681];//Use tot value to get array size
struct vec3 lightning[200];//For lightning
struct vec3 color[300];//For lightning color
//Declare display lists
GLuint terrainDL;//Terrain display list

//Declare physics globals, for whatever reason it fails if these are global
dWorldID world;
dSpaceID spacePhy;
dJointGroupID contactgroup;
dGeomID ground; //Holds the geometry of the plane, or the ground location
//Sphere geometries
dMass ball_mass;
dGeomID ball_geom;
dBodyID ball_body;
//Second Ball
dMass ball_mass2;
dGeomID ball_geom2;
dBodyID ball_body2;
//Third ball
dMass ball_mass3;
dGeomID ball_geom3;
dBodyID ball_body3;
//Balls for box o balls
dMass balls_mass[61];
dGeomID balls_geom[61];
dBodyID balls_body[61];
//Platform
dMass platform_mass[15];
dGeomID platform_geom[15];
dBodyID platform_body[15];
//Doorways, 18 platforms make up the 3 doors
dMass doorway_mass[17];
dGeomID doorway_geom[17];
dBodyID doorway_body[17];
//Pyramids, 1 box sits around the pyramid that gorws/shrinks with the diamond--too complex w/o triangle box existing in ODE
dMass pyramid_mass;
dGeomID pyramid_geom;
dBodyID pyramid_body;
//Box o' balls physics, 6 sides--we have two of these in the world
dMass boxSide_mass[12];
dGeomID boxSide_geom[12];
dBodyID boxSide_body[12];
//skyPanels physics
dMass skyPanel_mass[60];
dGeomID skyPanel_geom[60];
dBodyID skyPanel_body[60];
//targetBox physics
dMass targetBox_mass[114];
dGeomID targetBox_geom[114];
dBodyID targetBox_body[114];

//Physics geometries
#define GEOMSPERBODY 1  //Maximum number of geometries per body
#define DENSITY 0.5 //Density of our objects
#define GL_MIRRORED_REPEAT 0x8370
#define GL_CLAMP_TO_EDGE 0x812F
#define MAX_CONTACTS 12
#define PI 3.1415926
//For physics
struct MyObject
{
    dBodyID Body;  // the dynamics body
    dGeomID Geom[GEOMSPERBODY];  // geometries representing this body
    dMass Mass;//The dynamics mass
};

struct VECTOR
{
    float x;
    float y;
    float z;
};

//Declare a global myObject and vector
struct MyObject object;
struct VECTOR tempVect;

#define LEN 8192  //  Maximum amount of text in Print function
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
//Skybox defines counter clockwise style
#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_BACK 2
#define SKY_LEFT 3
#define SKY_TOP 4
#define SKY_BOTTOM 5

//Declare Project Functions
//Texture loader
void Reverse(void* x,const int n);
unsigned int LoadTexBMP(const char* file);
//Project stuff
void Print(const char* format , ...);
void Project(double ar,double dim);
void Spin(int value);
void pyramids(double x, double y, double z, double dx, double dy, double dz);
void invertPyramids(double x, double y, double z, double dx, double dy, double dz);
void triInvertfb(double x, double y, double z, double dx, double dy, double dz);
void invertTriInvertfb(double x, double y, double z, double dx, double dy, double dz);
void triInvertlr(double x, double y, double z, double dx, double dy, double dz);
void invertTriInvertlr(double x, double y, double z, double dx, double dy, double dz);
void cap(double x, double y, double z, double dx, double dy, double dz);
//Keyboard control functions
void special(int key,int x,int y);
void specialUp(int key,int x,int y);
void keyPressed (unsigned char key, int x, int y);
void keyUp (unsigned char key, int x, int y);//To detect when keys have stopped being pressed
void idle();
void reshape(int width,int height);
//Load OBJ functions
int LoadOBJ(const char* file);
//Functions to draw the tron-like landscape
void tron (double x, double y, double z);
void tron2 (double xx, double yy, double zz);
void tron3 (double xx, double yy, double zz);
//Functions to create doorway
void doorway(double x, double y, double z, double dx, double dy, double dz, double rx, double ry, double rz, double angle, int i);
void animateDoor(int value);
//Platfor function
void platform(double x, double y, double z, double dx, double dy, double dz, double rx, double ry, double rz, double angle, int i);
//Big Box functions
void boxSide(double x, double y, double z,double dx, double dy, double dz,double rx, double ry, double rz, double angle, int i);
//Error handeling
void Fatal(const char* format , ...);
void ErrCheck(const char* where);
struct normal normalP(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z, double p3x, double p3y, double p3z);
//Skybox
void initSkybox();
void drawSky();//Calls draw skybox, just another layer of abstraction
void drawSkybox (double d);
//Physics
void initODE();//initialize ode
void closeODE();//close ode returning memory alloc
void simLoop();
void nearCallback (void *data, dGeomID o1, dGeomID o2);
void sphere(double r);//For drawing spheres with physics properties
void boxSpheres(double r, int i);//For spheres inside of exploding box
void Vertex(double th,double ph);
//Simplex algorithm
float raw_noise_2d( const float x, const float y);//Raw noise for 2d simplex (send in x and z and set y to return value)
float raw_noise_3d( const float x, const float y, const float z);//Return raw noise for simplex
float octave_noise_2d( const float octaves, const float persistence, const float scale, const float x, const float y);
float octave_noise_3d( const float octaves, const float persistence, const float scale, const float x, const float y, const float z);
float dot2D( const int* g, const float x, const float y );//2D dot
float dot(const int* g, const float x, const float y, const float z);//For simplex (defined inline) defined in simplex.c, 3D dot
int fastfloor(const float x);//For simplex defined inline in simplex.c
void simplexValsInit(int initwidth, int initsqwidth);//To initialize array
void simplexVals();//To set heights
void terrain();//For developing terrain based on simplex
//Skypanel
void skyPanel(double x, double y, double z, double dx, double dy, double dz, double rx, double ry, double rz, double angle, int i);
//Target boxes
void boxes(double dx, double dy, double dz, double rx, double ry, double rz, double angle, int i);
//Gun
void target();
void gun();
void movement(int i);
//Lightning
void raysInit();
void rays(float x, float y, float z, float angle, float rx, float ry, float rz);
void lightningSphere();
//Space Ships
void shipOne();

#ifdef __cplusplus
}
#endif

#endif
