#pragma once
#include <GL/glut.h>
#include <GL/GL.h>
#include "Entity.h"
#include "Vector2.h"
#include "RayCannon.h"
#include "World.h"
#include "Pixel.h"
#include "RepoTool.h"

class ViewPlane : public Entity
{
private:
	Vector3 _orientation;
	Vector3 _up;
	RayCannon* _rayCannon;
	Pixel* _superPixels;
	int _superPixelLength;
	float* _pixels;
	int _windowWidth;
	int _windowHeight;
	int _size;
	int _colorAttributeCount;

	void initialize();
	void setWindowSize();
	void setPixelColor3(RayColor pixelColor, int position);
	void updateToneRepoPixels();
	void setToneRepoPixels();

	Vector3 getPixelWorldPosition(Vector2 pixel);
	
public:
	ViewPlane(void);
	ViewPlane(int winWidth, int winHeight, Vector3 pos, Vector3 fwd, Vector3 up, RayCannon** rayCannon);
	~ViewPlane(void);
	int getWindowSize();
	float * getPixels();
	float* getToneRepoPixels();
	void updatePixels(World* worldRef);
};

