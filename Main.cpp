#include <GL/glut.h>
#include <GL/GL.h>
#include <stdlib.h>
#include <time.h>

#include "Camera.h"
#include "ViewPlane.h"
#include "Light.h"
#include "AmbientLight.h"
#include "World.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "math.h"

#define INSTRUCTIONS "Left click : All object positions\nRight Click: clear output\n\ d or D to toggle Debug on\n"
#define wWidth 800
#define wHeight 800
#define fullscreen false;
bool rayTracing = true;
bool debugOn = false;
// TODO: Add terrain parameters via #define's

//camera* c;
ViewPlane* vp;
Camera* cam;
Light * lightSource;
AmbientLight* ambientLight;
World* worldController;
// todo: add light source info here

void mouse (int button, int state, int x, int y);
void motion (int x, int y);
void pmotion (int x, int y);

// Initialize EVERYTHING
// Called at program start
void init(){
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_DEPTH_TEST);
        //if(fullscreen) glutFullScreen();
}

// creates light source, camera, viewplane
void createEntities(){
	int numberOfShapes = 3;
	Shape* shapes = new Shape[numberOfShapes];			
	shapes[0] = Sphere(Vector3(30,20,80), 60, RayColor(1,0,0), RayColor(1,0,0), RayColor(.9, .9, .9),
		RayColor(1,0,0), 5, 1, 0);
	shapes[1] = Sphere(Vector3(-40,-25,10), 90, RayColor(0,1,0), RayColor(.8, 0, 0), RayColor(.7, .7, .9),
		RayColor(1,0,0), 6, 1,0);	
	shapes[2] = Plane(Vector3(135,0,-25), Vector3(-1,0,0), 10, 10, RayColor(1,1,0));

	// create the camera
	Vector3 position = Vector3(0.0f, 0.0f, 300.0f);
	Vector3 orientation = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	// normalize vectors
	orientation.normalize();
	up.normalize();
	cam = new Camera(position, orientation, up);

	// create the light source
	// vector 4 parameters as follows(w,x,y,z)
	//position = Vector3(0.0f,200.0f,400.0f);
	RayColor color = RayColor(1.0f, 1.0f, 1.0f, 1.0f);
	lightSource = new Light(position, color);
	// the lightsource index starts at 1 that means.
	int numberOfLights = 1;
	Light lightSourceArray[] = {Light(Vector3(-200.0f,0.0f,100.0f), color)};//500,500,50
	//lightSourceArray = {lightSource};


	// create an ambient light
	color = RayColor(100.0f, 104.0f, 237.0f, 1.0f);
	color = color.getNormalized();

	ambientLight = new AmbientLight(position, color, 1000);

	// init the worldController
	worldController = new World(shapes, numberOfShapes, lightSourceArray,
		numberOfLights, ambientLight, cam);
	// create local ray cannon to be sent to the viewPlane
	//Entity* shapes = new Entity[3];
	RayCannon* rayCannon = new RayCannon(position, worldController);

	position = cam->getPosition();
	// create the view Plane
	position.addZ(-150);
	position.addZ(-275);
	//position.addX(-150);
	orientation = Vector3(0.0f, 0.0f, 1.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
	// normalize vectors
	orientation.normalize();
	up.normalize();
	vp = new ViewPlane(wWidth, wHeight, position, orientation, up, &rayCannon);
}
void createObjects(){
}


void createObjectsWithExtra(){
	Shape* shapes = new Shape[3];
	shapes[0] = Sphere(Vector3(30,20,-30), 30, RayColor(0,1,0));
	shapes[1] = Sphere(Vector3(-5,-15,-50), 30, RayColor(1,0,0));
	shapes[2] = Plane(Vector3(5,0,-25), Vector3(-1,0,0), 10, 10, RayColor(0,0,1));
	//worldController = new World(shapes, 3 +c .getNumTriangles() );
}

void createWorld(){
	// create world objects
	bool renderExtraShape = false;

	if( renderExtraShape ){
		createObjectsWithExtra();
	}else{
		createObjects();
	}
	// create non-object components
	createEntities();

}

// Draws everything to the screen when glutPostRedisplay() is called
// TODO:
//      Check if only images in the view frustrum are being drawn
void displayRayTracing(){
        /*float* pixels = new float[wWidth*wHeight*3];
        for(int i = 0; i < (wWidth*wHeight*3); i ++){
                if( i % 3 == 2) pixels[i] = 1;
                else pixels[i] = 0;
        }*/
	vp->updatePixels(worldController);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawPixels(wWidth, wHeight, GL_RGB, GL_FLOAT, vp->getPixels());
    glutSwapBuffers();
}

// Adjusts the camera for when the user modifies the window size
// called when window is adjusted and when program launches
void reshape(int w, int h){
        glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluPerspective(60.0, (GLdouble) w/(GLdouble) h, 1.0, 300.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Call this before you exit so you can clean up all of your data
void unload(){
        // TODO: Clean up attributes in the main
        // TODO: Clean up objects

        // Clean up all the environment objects
}

void keyboard(unsigned char key, int x, int y){
        switch(key){
                // quit the program and clean up data
                case 'q': case 'Q': case 27:
                        unload();
                        exit(0);
                        break;
                // change to full screen
               /* case 'f': case 'F':
                        glutFullScreen();
                        break;*/
				case 'r': case 'R':
					rayTracing = true;
					displayRayTracing();
					break;
				case 'd': case 'D':
					debugOn = !debugOn;
					if( debugOn )
						printf( "DEBUG mode toggled ON\n" );
					else
						printf( "DEBUG mode toggled OFF\n" );
					break;
        }
}

int main(int argc, char** argv){
        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize (wWidth, wHeight); 
        glutInitWindowPosition (0, 0);
        glutCreateWindow ("Ray Tracer Checkpoint 2");
        glutDisplayFunc(displayRayTracing); 
        //glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
		glutMouseFunc (mouse);
		glutMotionFunc (motion);
		glutPassiveMotionFunc (pmotion); 
        init ();
		createWorld();
		printf( "%s",INSTRUCTIONS );
        glutMainLoop();
}


//Mouse Click handler
void mouse (int button, int state, int x, int y)
{
	if( !debugOn )
		return;
	switch (button)
    {
        //  Left Button Clicked
        case GLUT_LEFT_BUTTON:

            switch (state)
            {
                case GLUT_DOWN:
                    break;
                case GLUT_UP:
					printf( "==================\nCamera: (%f,%f,%f)\n", worldController->getCamera()->getPosition().getX(),
																		worldController->getCamera()->getPosition().getY(),
																		worldController->getCamera()->getPosition().getZ() );
					for( int i = 0; i < worldController->getTotalLightSources(); i++ ){
						printf( "Light %d: (%f,%f,%f)\n", i , worldController->getLightSources()[i].getPosition().getX(),
															worldController->getLightSources()[i].getPosition().getY(),
															worldController->getLightSources()[i].getPosition().getZ() );
					}
					for( int i = 0; i < worldController->getTotalShapes(); i++ ){
						printf( "[%d] Object (%f,%f,%f)\n", i, worldController->getShapes()[i].getPosition().getX(), 
															   worldController->getShapes()[i].getPosition().getY(), 
															   worldController->getShapes()[i].getPosition().getZ() );
					}
					printf( "==================\n" );
                    break;
            }

            break;

        //  Middle Button clicked
        case GLUT_MIDDLE_BUTTON:

            switch (state)
            {
                case GLUT_DOWN:
                    break;
                case GLUT_UP:
                    break;
            }

            break;

        //  Right Button Clicked
        case GLUT_RIGHT_BUTTON:

            switch (state)
            {
                case GLUT_DOWN:
                    break;
                case GLUT_UP:
					printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
            }

            break;
    }
}

//mouse move handler while button is pressed
void motion (int x, int y)
{
	if( debugOn ){
		 //  Print the mouse drag position
		printf ("Mouse Drag Position: %d, %d.\n", x, y);
	}
}

//mouse move handelr while no button is pressed
void pmotion (int x, int y)
{
	if( debugOn ){
		 //  Print mouse move position
		printf ("Mouse Move Position: %d, %d.\n", x, y);
	}
}