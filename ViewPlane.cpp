#include "ViewPlane.h"
// TODO: Add ray cannon

ViewPlane::ViewPlane(void)
{
	_position = Vector3();
	_orientation = Vector3();
	_windowWidth = 800;
	_windowHeight = 600;
	_colorAttributeCount = 3;
	initialize();
}
ViewPlane::ViewPlane(int winWidth, int winHeight, 
	Vector3 pos, Vector3 fwd, Vector3 upVector, RayCannon** rayCannon) : Entity(pos){
	_orientation = fwd;
	_up = upVector;
	_windowWidth = winWidth;
	_windowHeight = winHeight;
	_colorAttributeCount = 3;
	_rayCannon = *rayCannon;
	initialize();
}
ViewPlane::~ViewPlane(void)
{
	delete _rayCannon;
}
void ViewPlane::initialize(){
	setWindowSize();
	_pixels = new float[_size * _colorAttributeCount];
}
void ViewPlane::setWindowSize(){
	_size = _windowWidth * _windowHeight;
}
int ViewPlane::getWindowSize()	{	return _size;	}
float* ViewPlane::getPixels()	{	return _pixels;	}

void ViewPlane::setPixelColor3(RayColor pixelColor, int position){
	_pixels[position] = pixelColor.getR();
	_pixels[position + 1] = pixelColor.getG();
	_pixels[position + 2] = pixelColor.getB();
}

void ViewPlane::updatePixels(World* worldRef){
	RayColor pixelColor;
	int pixelPosition = 0;
	for(int j = 0; j < _windowWidth; j++){
		for(int k = 0; k < _windowHeight; k++){
			pixelColor = _rayCannon->shootRayAt(getPixelWorldPosition(Vector2(j,k)));
			setPixelColor3(pixelColor, pixelPosition);
			pixelPosition += _colorAttributeCount;
		}
	}
	//for(int i = 0; i < _size * _colorAttributeCount; i+= _colorAttributeCount){
	//	// shoot ray
	//	pixelColor = _rayCannon->shootRayAt(getPixelWorldPosition(Vector2(0,0)));
	//	_pixels[i] = pixelColor.getR();
	//	_pixels[i + 1] = pixelColor.getG();
	//	_pixels[i + 2] = pixelColor.getB();
	//}
}
// TODO: get proper position
Vector3 ViewPlane::getPixelWorldPosition(Vector2 pixel){
	Vector3 pixelPosition = _position;
	pixelPosition = pixelPosition + Vector3(pixel.getX() - _windowWidth/2, 0.0f, 0.0f);
	pixelPosition = pixelPosition + Vector3(0.0f, pixel.getY() - _windowHeight/2, 0.0f);
	return pixelPosition;
}

