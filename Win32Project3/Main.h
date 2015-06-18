#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "PixelData.h"
using namespace std;

#pragma pack(push,1)
struct BMPHEADER{
	char signature[2];
	int fileSize;
	short reserved1;
	short reserved2;
	unsigned int offsetToPixArray;
};
struct DIBHEADER{
	unsigned int bytesInDIB;
	int BMPWidth;
	int BMPHeigth;
	short planeUsed;
	short BitsPerPixel;
	unsigned int compression;
	unsigned int sizeOfBMPData;
	int hRes;
	int vRes;
	unsigned int nColors;
	unsigned int importantColors;
};
#pragma pack(pop)


class Main
{
public:
	Main(const int width, const int height);
	void Main::SaveToBmp(const char * fileName);
	char* getBuffer();
	void dumpBuffer(const char * fileName);
	void setType(int option);
	void writeHeader(ofstream* file, int W, int H);
	void newTerrain(int roughness);
	void newBlackWhite();
	void newRandom();

	const int width;
	const int height;
	const int size;
	PixelData PixelArray;
	
	~Main();
};

