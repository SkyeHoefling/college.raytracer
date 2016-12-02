#pragma once
#include "Pixel.h"
class RepoTool
{
public:
	static void wardCompression( Pixel * &pixels, int pixelCount );
	static void reinhardCompression( Pixel * &pixels, int pixelCount );

private:
	static double prepareHDRImageAndReturnLuminaceSum( Pixel * &pixels, int pixelCount );
	static void calculateReinhardScaled(Pixel* &pixels, int pixelCount);
	static void calculateReinhardTarget(Pixel* &pixels, int pixelCount);
	static double getLavg(Pixel * &pixels, int pixelCount);
	static void applyDeviceModel( Pixel * &pixels, int pixelCount );
};

