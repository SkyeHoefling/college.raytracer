#include "RepoTool.h"
#define WARD_COSNT 1.219
#define LdMax 100
#define ONE_OVER_NUMBER_OF_PIXELS 0.0000015625 
#define a 0.4
// a == 0.18


void RepoTool::wardCompression( Pixel * &pixels, int pixelCount )
{
	double Lavg = getLavg(pixels, pixelCount);
	double sf = 0;
	double num =   WARD_COSNT + pow(( LdMax / 2 ), .4);
	double denom = WARD_COSNT + pow(( Lavg      ), .4 );
	sf = pow( num / denom, 2.5 );

	for( int i = 0; i < pixelCount; i++ ){
		pixels[i].setColorR( (pixels[i].getColorR() * sf) /LdMax );
		pixels[i].setColorG( (pixels[i].getColorG() * sf) /LdMax );
		pixels[i].setColorB( (pixels[i].getColorB() * sf) /LdMax );
	}
}

void RepoTool::reinhardCompression(Pixel* &pixels, int pixelCount){
	calculateReinhardScaled(pixels, pixelCount);
	calculateReinhardTarget(pixels, pixelCount);
	applyDeviceModel(pixels, pixelCount);
}

void RepoTool::calculateReinhardScaled(Pixel* &pixels, int pixelCount){
	double Lavg = getLavg(pixels, pixelCount);
	for(int i = 0; i < pixelCount; i ++){
		pixels[i].setColorR( (a * pixels[i].getColorR()) / Lavg);
		pixels[i].setColorG( (a * pixels[i].getColorG()) / Lavg);
		pixels[i].setColorB( (a * pixels[i].getColorB()) / Lavg);
	}
}

void RepoTool::calculateReinhardTarget(Pixel* &pixels, int pixelCount){
	for(int i = 0; i < pixelCount; i ++){
		pixels[i].setColorR( ( (pixels[i].getColorR()) / (1 + pixels[i].getColorR())) * LdMax);
		pixels[i].setColorG( ( (pixels[i].getColorG()) / (1 + pixels[i].getColorG())) * LdMax);
		pixels[i].setColorB( ( (pixels[i].getColorB()) / (1 + pixels[i].getColorB())) * LdMax);
	}
}

void RepoTool::applyDeviceModel(Pixel* &pixels, int pixelCount){
	for( int i = 0; i < pixelCount; i++ ){
		pixels[i].setColorR( (pixels[i].getColorR()) /LdMax );
		pixels[i].setColorG( (pixels[i].getColorG()) /LdMax );
		pixels[i].setColorB( (pixels[i].getColorB()) /LdMax );
	}
}

double RepoTool::getLavg(Pixel* &pixels, int pixelCount){
	double sumOfLuminance = prepareHDRImageAndReturnLuminaceSum( pixels, pixelCount );
	double smallNum = ONE_OVER_NUMBER_OF_PIXELS;
	double lavghelper = smallNum * sumOfLuminance;
	double Lavg = exp(lavghelper);
	return Lavg;
}

double RepoTool::prepareHDRImageAndReturnLuminaceSum(Pixel * &pixels, int pixelCount )
{
	double sum = 0;
	double lambda = .0000000000000000000000000001;

	for( int i = 0; i < pixelCount;i++){
		pixels[i].setColorR( pixels[i].getColorR() * Pixel::maxLuminance );
		pixels[i].setColorG( pixels[i].getColorG() * Pixel::maxLuminance );
		pixels[i].setColorB( pixels[i].getColorB() * Pixel::maxLuminance );

		pixels[i].setLuminance( .27 * pixels[i].getColorR() + 
								.67 * pixels[i].getColorG() + 
								.06 * pixels[i].getColorB() );
		sum += log( lambda + pixels[i].getLuminance() );
		//pixels[i].setColor(&pixels[i].getColor()->normalized());
	}
	return sum;
}

/*void RepoTool::applyDeviceModel( Pixel * pixels, int pixelCount ) { }*/