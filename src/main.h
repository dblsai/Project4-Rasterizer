// CIS565 CUDA Rasterizer: A simple rasterization pipeline for Patrick Cozzi's CIS565: GPU Computing at the University of Pennsylvania
// Written by Yining Karl Li, Copyright (c) 2012 University of Pennsylvania

#ifndef MAIN_H
#define MAIN_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glslUtil/glslUtility.hpp>
#include <iostream>
#include <objUtil/objloader.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>


#include "rasterizeKernels.h"
#include "utilities.h"
#include "FreeImage.h"  //for loading texture from ".jpg", ".png", ".bmp"

using namespace std;

//-------------------------------
//------------GL STUFF-----------
//-------------------------------
int frame;
int fpstracker;
double seconds;
int fps = 0;
GLuint positionLocation = 0;
GLuint texcoordsLocation = 1;
const char *attributeLocations[] = { "Position", "Tex" };
GLuint pbo = (GLuint)NULL;
GLuint displayImage;
uchar4 *dptr;

GLFWwindow *window;

obj* mesh;

float* vbo;
int vbosize;
float* cbo;
int cbosize;
int* ibo;
int ibosize;
float* nbo;
int nbosize;
float* uvbo;
int uvbosize;

//-------------------------------
//----------CUDA STUFF-----------
//-------------------------------

int width = 800; int height = 800;

//-------------------------------
//-------------MAIN--------------
//-------------------------------

int main(int argc, char** argv);

//-------------------------------
//---------RUNTIME STUFF---------
//-------------------------------

void runCuda();

#ifdef __APPLE__
	void display();
#else
	void display();
	void keyboard(unsigned char key, int x, int y);
#endif



//-------------------------------
//----------SETUP STUFF----------
//-------------------------------
bool init(int argc, char* argv[]);
void initPBO();
void initCuda();
void initTextures();
void initVAO();
void initTextureMap(char* textureFileName);
int loadTexture(char* file, std::vector<glm::vec3> &c, int &h,int &w );
GLuint initShader();

//-------------------------------
//---------CLEANUP STUFF---------
//-------------------------------

void cleanupCuda();
void deletePBO(GLuint* pbo);
void deleteTexture(GLuint* tex);

//------------------------------
//-------GLFW CALLBACKS---------
//------------------------------
void mainLoop();
void rotateMouseCam(double x, double y, double xlast, double ylast);
void translateMouseCam(double x, double y, double xlast, double ylast);
void errorCallback(int error, const char *description);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mousebuttonCallback(GLFWwindow* window, int button, int action, int mods);
void mousescrollCallback(GLFWwindow * window, double xoffset, double yoffset );
void mousemoveCallback(GLFWwindow *window, double xpos, double ypos);

#endif