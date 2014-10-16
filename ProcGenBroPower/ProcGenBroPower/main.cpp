#include <GLFW/glfw3.h>
#include <GLUT/GLUT.h>
#include "glm.hpp"
#include "matrix_transform.hpp"
#include <iostream>
#include "SOIL.h"
#include "controls.h"
#include "tile.h"
#include "level.h"

GLFWwindow* window;
Camera camera;
int width = 1280;
int height = 800;
int camPosX = 0;
int camPosY = 0;
float camPosZ = 0.1;
int nearPlane = 0;
int farPlane = 2;
Tile tilesSheet1[1000];
Tile tilesSheet2[1000];
Tile tilesSheet3[1000];
Level level(120,20);
GLuint _textureId;


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void custom_fbsize_callback(GLFWwindow* window, int widthR, int heightR)
{
    width = widthR;
    height = heightR;
    /* use system width,height */
    /* glViewport(0, 0, width, height); */
    
    /* use custom width,height */
    glViewport(0, 0, width, height);
}

GLuint loadPNG()
{
    GLuint tex_2d = SOIL_load_OGL_texture( "/Users/bertbosch/Documents/delft/Zelf/ProcGenBroPower/ProcGenBroPower/textures/Sprite_background_effects_0013.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    return tex_2d;
}

void initGL(int widthR, int heightR)
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glViewport(0, 0, (GLsizei)widthR, (GLsizei)heightR);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-1, 1, -1 * (GLfloat) height / (GLfloat) width, (GLfloat) height/ (GLfloat) width, -1, 1);
	// ----- OpenGL settings -----
	glfwSwapInterval(1); 		// Lock to vertical sync of monitor (normally 60Hz, so 60fps)
    
	glEnable(GL_SMOOTH);		// Enable (gouraud) shading
    
	glDisable(GL_DEPTH_TEST); 	// Disable depth testing
    
	glEnable(GL_BLEND);		// Enable blending (used for alpha) and blending function to use
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    
	glLineWidth(1.0f);		// Set a 'chunky' line width
    
	glEnable(GL_LINE_SMOOTH);	// Enable anti-aliasing on lines
    
	glPointSize(1.0f);		// Set a 'chunky' point size
    
	glEnable(GL_POINT_SMOOTH);
}

void drawBackground(){
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_QUADS);
    glTexCoord2d( 0,  0); glVertex2f(0.f,0.f);
    glTexCoord2d(1,  0); glVertex2f(40.f,0.f);
    glTexCoord2d(1, 1); glVertex2f(40.f, 20.f);
    glTexCoord2d( 0, 1); glVertex2f(0.f, 20.f);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d( 0,  0); glVertex2f(40.f,0.f);
    glTexCoord2d(1,  0); glVertex2f(80.f,0.f);
    glTexCoord2d(1, 1); glVertex2f(80.f, 20.f);
    glTexCoord2d(0, 1); glVertex2f(40.f, 20.f);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d( 0,  0); glVertex2f(80.f,   0.f);
    glTexCoord2d(1,  0); glVertex2f(120.f,   0.f);
    glTexCoord2d(1, 1); glVertex2f(120.f,  20.f);
    glTexCoord2d( 0, 1); glVertex2f( 80.f,  20.f);
    glEnd();
    
}

void drawGrid(){
    //horizontal
    glColor3f(1.f, 1.f, 0.f);
    for(int i = 0; i<=20; i++){
        glBegin(GL_LINES);
            glVertex2f(0.f, 0.f + (i));
            glVertex2f(120.f, 0.f + (i));
        glEnd();
    }
    //vertical
    for(int i = 0; i<=120; i++){
        glBegin(GL_LINES);
        glVertex2f(0.f + (i),0.f);
        glVertex2f(0.f + (i),20);
        glEnd();
    }
}

void highLightTile(){
    GLfloat winX, winY, winZ;
    double mouseXPos, mouseYPos;
	glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    GLint viewportL[4];
    glGetIntegerv( GL_VIEWPORT, viewportL );
    
    winX = (float)mouseXPos;
    winY = (float)viewportL[3] - (float)mouseYPos;
	winZ = 0;
    glm::vec4 viewport = glm::vec4(viewportL[0], viewportL[1], viewportL[2], viewportL[3]);
    glm::mat4 viewMatrix = glm::mat4(1.0f); //View matrix is translated 5 units back.
    viewMatrix = glm::scale(viewMatrix, glm::vec3(camera.getPosition().z, camera.getPosition().z, 1));
    viewMatrix = glm::translate(viewMatrix,glm::vec3(camera.getPosition().x, camera.getPosition().y, 0));
    glm::mat4 projectionMatrix = glm::ortho<float>(-1, 1, -1 * (GLfloat) height / (GLfloat) width, (GLfloat) height/ (GLfloat) width, -1, 1);
    
    glm::vec3 win = glm::vec3(winX,winY,winZ);
    glm::vec3 v = glm::unProject(win, viewMatrix, projectionMatrix, viewport);
    
    //worldPos = worldPos / (worldPos.z * -1.f);
    int newPosX = v[0];
    int newPosY = v[1];
    
    std::cout<< "mousePos X2 " << newPosX;
    std::cout<< "mousePos Y2 " << newPosY;
    std::cout<< "\n";
    
    glColor4f(1.f, 1.f, 0.f,0.5f);
    glBegin(GL_QUADS);
        glVertex2f(newPosX,       newPosY);
        glVertex2f(newPosX+1.f,     newPosY);
        glVertex2f(newPosX+1.f,     newPosY+1.f);
        glVertex2f(newPosX,     newPosY + 1.f);
    glEnd();
}

void drawScene(){
    // Clear the screen
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset the matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //double a = width / height;
    glOrtho(-1, 1, -1 * (GLfloat) height / (GLfloat) width, (GLfloat) height/ (GLfloat) width, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glScaled(camera.getPosition().z, camera.getPosition().z, 1);
    glTranslatef(camera.getPosition().x, camera.getPosition().y, 0);
    
    drawBackground();
    drawGrid();
    highLightTile();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}


int main(void)
{
    camera.setPosition(glm::vec3(camPosX,camPosY,camPosZ));
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
    
	//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    
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
    glfwSetFramebufferSizeCallback(window, custom_fbsize_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    _textureId = loadPNG();
    
    while (!glfwWindowShouldClose(window))
    {
        camera.computeInputs(window);
        drawScene();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}