#pragma once
#include <iostream>
#include <vector>
#include "stdarg.h"
#include "time.h"
#include "math.h"
#include <fstream>



class PixelData
{
private:
	struct point{
		int x;
		int y;
	};
	struct rgb{
		double r;
		double g;
		double b;
	};


public:
	PixelData(int width, int height);
	~PixelData();
	void fillPixelArray(char* type, ...);
	void addSeed(int x, int y, int value);
	char* getPixelArray();
	char getPixel(int x);
	void dumpBuffer(const char* fileName);
	void fillBufferTerrain();
	void fillBufferBW();
	void fillBufferCOL();
	void resetPixelArray();
private:

	int getNewPoint(std::vector<point> list, const int size, int roughness);
	void diamond(int curWidth, int roughness);
	void square(int curWidth, int roughness);
	rgb hslToRgb(double h, double s, double l);
	void FPARandom();
	void FPABlackWhite();
	void FPADiamondSquare(float roughness);
	void FPAtest();

	
	const int W;
	const int H;
	char* buffer;
	int **pixelArray;
	const int size;
};

