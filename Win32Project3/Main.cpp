#include "stdafx.h"
#include "Main.h"


Main::Main(const int width, const int height) :
width(width),
height(height),
size(width*height*4),
PixelArray(PixelData(width, height))
{
	PixelArray.addSeed(0, 0, 130);
	PixelArray.addSeed(0, height-1, 130);
	PixelArray.addSeed(0, height-1, 130);
	PixelArray.addSeed(width-1, height-1, 130);
	PixelArray.fillPixelArray("DiamondSquare", 200);

	
};

void Main::newTerrain(int roughness){
	PixelArray.resetPixelArray();
	PixelArray.addSeed(0, 0, 130);
	PixelArray.addSeed(0, height - 1, 130);
	PixelArray.addSeed(0, height - 1, 130);
	PixelArray.addSeed(width - 1, height - 1, 130);
	PixelArray.fillPixelArray("DiamondSquare", 200);
}

void Main::newRandom(){
	PixelArray.resetPixelArray();
	PixelArray.fillPixelArray("Random");
}

void Main::newBlackWhite(){
	PixelArray.resetPixelArray();
	PixelArray.fillPixelArray("BlackWhite");
}

void Main::dumpBuffer(const char * fileName){

	PixelArray.dumpBuffer(fileName);
}

void Main::SaveToBmp(const char * fileName){

	ofstream file;
	file.open(fileName, ios::out | ios::binary);
	writeHeader(&file, width, height);
	file.write(PixelArray.getPixelArray(), size);
	file.close();
}

Main::~Main()
{
}


char* Main::getBuffer(){

	return PixelArray.getPixelArray();

}

void Main::setType(int option){

	switch (option){
	case 0:
		PixelArray.fillBufferBW();
		break;
	case 1:
		PixelArray.fillBufferCOL();
		break;
	case 2:
		PixelArray.fillBufferTerrain();
		break;
	}
}

// thank you random wiki picture
// https://upload.wikimedia.org/wikipedia/commons/c/c4/BMPfileFormat.png
void Main::writeHeader(ofstream* file, int W, int H){

	BMPHEADER bmpheader;
	bmpheader.signature[0] = 0x42;
	bmpheader.signature[1] = 0x4d;
	bmpheader.fileSize = 0x46; //14 + 40 + ( WIDTH * HEIGHT * 4 );
	bmpheader.reserved1 = 0;
	bmpheader.reserved2 = 0;
	bmpheader.offsetToPixArray = 0x36;

	DIBHEADER dibheader;
	dibheader.bytesInDIB = 40;
	dibheader.BMPHeigth = -H;
	dibheader.BMPWidth = W;
	dibheader.planeUsed = 1;
	dibheader.BitsPerPixel = 24;
	dibheader.compression = 0;
	dibheader.sizeOfBMPData = W*H * 4;
	dibheader.hRes = 2835;
	dibheader.vRes = 2835;
	dibheader.nColors = 0;
	dibheader.importantColors = 0;


	file->write((char*)(&bmpheader), 14);
	file->write((char*)(&dibheader), 40);
}
