#include <GLFW/glfw3.h>
#include "controls.h"
#include <iostream>
GLFWwindow* window;
Camera camera;
int width = 800;
int height = 600;
int nearPlane = 0;
int farPlane = 2;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void initGL(int width, int height)
{
	// Setup our viewport to be the entire size of the window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    
	// Change to the projection matrix, reset the matrix and set up orthagonal projection (i.e. 2D)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, nearPlane, farPlane); // Paramters: left, right, bottom, top, near, far
    
	// ----- OpenGL settings -----
    
	glfwSwapInterval(1); 		// Lock to vertical sync of monitor (normally 60Hz, so 60fps)
    
	glEnable(GL_SMOOTH);		// Enable (gouraud) shading
    
	glDisable(GL_DEPTH_TEST); 	// Disable depth testing
    
	glEnable(GL_BLEND);		// Enable blending (used for alpha) and blending function to use
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	glLineWidth(5.0f);		// Set a 'chunky' line width
    
	glEnable(GL_LINE_SMOOTH);	// Enable anti-aliasing on lines
    
	glPointSize(5.0f);		// Set a 'chunky' point size
    
	glEnable(GL_POINT_SMOOTH);	// Enable anti-aliasing on points
}

void drawGrid(){
    for(int i = 0; i<=20; i++){
        glBegin(GL_LINES);
            glColor3f(1.f, 1.f, 0.f);
            glVertex2f(20.f, 0.f + (i));
            glVertex2f(0.f, 0.f + (i));
        glEnd();
    }
    for(int i = 0; i<=20; i++){
        glBegin(GL_LINES);
        glColor3f(1.f, 1.f, 0.f);
        glVertex2f(0.f + (i),0.f);
        glVertex2f(0.f + (i),20);
        glEnd();
    }
    
}

void drawScene(){
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScaled(camera.getPosition().z, camera.getPosition().z, 1);
    glTranslatef(camera.getPosition().x, camera.getPosition().y, 0);
    
    //glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    /*
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex2f(-0.6f, -0.4f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex2f(0.6f, -0.4f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex2f(0.f, 0.6f);
    glEnd();
    */
    drawGrid();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}


int main(void)
{
    camera.setPosition(glm::vec3(-2,-2,1));
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
    
	glfwWindowHint(GLFW_SAMPLES, 4);
	   
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
    
    initGL(width,height);
	glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
    while (!glfwWindowShouldClose(window))
    {
        camera.computeInputs(window);
        drawScene();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}