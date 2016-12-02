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
	_superPixels = new Pixel[_size];
}
void ViewPlane::setWindowSize(){
	_size = _windowWidth * _windowHeight;
}
int ViewPlane::getWindowSize()	{	return _size;	}
float* ViewPlane::getPixels()	{	return _pixels;	}
float* ViewPlane::getToneRepoPixels(){
	int length = _size*_colorAttributeCount;
	float* result = new float[length];
	int position = 0;
	for(int i = 0; i < _superPixelLength; i ++){
			result[position] = _superPixels[i].getColorR();
			result[position + 1] = _superPixels[i].getColorG();
			result[position + 2] = _superPixels[i].getColorB();
			position+= 3;
	}
	return result;
}

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
			//printf( "(%d,%d)\n", j, k );
			pixelColor = _rayCannon->shootRayAt(getPixelWorldPosition(Vector2(j,k)));
			setPixelColor3(pixelColor, pixelPosition);
			pixelPosition += _colorAttributeCount;
		}
	}
	setToneRepoPixels();
	updateToneRepoPixels();
	//for(int i = 0; i < _size * _colorAttributeCount; i+= _colorAttributeCount){
	//	// shoot ray
	//	pixelColor = _rayCannon->shootRayAt(getPixelWorldPosition(Vector2(0,0)));
	//	_pixels[i] = pixelColor.getR();
	//	_pixels[i + 1] = pixelColor.getG();
	//	_pixels[i + 2] = pixelColor.getB();
	//}
}
void ViewPlane::updateToneRepoPixels(){
	//RepoTool::wardCompression(_superPixels, _superPixelLength);
	RepoTool::reinhardCompression(_superPixels, _superPixelLength);
}
void ViewPlane::setToneRepoPixels(){
	int count = 0;
	int positionCount = 0;
	for(int x = 0; x < _windowWidth; x++){
		for(int y = 0; y < _windowHeight; y++){
			_superPixels[positionCount] = Pixel(Vector2(x,y), 
												Vector3(_pixels[count],
														_pixels[count+1],
														_pixels[count+2]));

			count += _colorAttributeCount;
			positionCount++;
		}
	}
	_superPixelLength = positionCount;
}

// TODO: get proper position
Vector3 ViewPlane::getPixelWorldPosition(Vector2 pixel){
	Vector3 pixelPosition = _position;
	pixelPosition = pixelPosition + Vector3(pixel.getX() - _windowWidth/2, 0.0f, 0.0f);
	pixelPosition = pixelPosition + Vector3(0.0f, pixel.getY() - _windowHeight/2, 0.0f);
	return pixelPosition;
}

