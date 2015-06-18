#include "stdafx.h"
#include "PixelData.h"


PixelData::PixelData(int width, int height)
	:W(width),
	H(height),
	size(W*H * 4)
{
	buffer = (char*)malloc(size);
	srand(time(NULL));
	pixelArray = (int**)malloc((W)* sizeof(int *));
	for (int i = 0; i < W; i++){
		pixelArray[i] = (int*)malloc((H)* sizeof(int));
	}
	for (int y = 0; y < H; y++){
		for (int x = 0; x < W; x++){
			pixelArray[x][y] = NULL;
		}
	}
}


PixelData::~PixelData()
{
	dumpBuffer("dump.txt");
	free(buffer);
}


//Options for creating different types of images
void PixelData::fillPixelArray(char* type, ...){
	va_list list;
	va_start(list, type);
	if (type == "Random"){

		FPARandom();
	}
	if (type == "BlackWhite"){

		FPABlackWhite();
	}
	if (type == "DiamondSquare"){

		float roughness = va_arg(list, int);
		FPADiamondSquare(roughness);
	}
	if (type == "test"){
		FPAtest();
	}
	va_end(list);
}

// Its random.
void PixelData::FPARandom(){
	srand(time(NULL));
	int i = 0;
	for (int h = 0; h < H; h++)
	{
		for (int w = 0; w < W; w++){
			buffer[i] = rand() % 256;
			i++;
			buffer[i] = rand() % 256;
			i++;
			buffer[i] = rand() % 256;
			i++;
		}

		for (int i = 0; i < W % 4; i++){
			buffer[i] = 0;
			i++;
		}
	}
}

// for testing new ideas, ignore it.
void PixelData::FPAtest(){
	int i = 0;
	double c = 0;
	rgb col;
	for (int y = 0; y < H; y++){

		for (int x = 0; x < W; x++){
			col = hslToRgb(c, 1, 1);
			buffer[i] = (int)col.b;
			i++;
			buffer[i] = (int)col.g;
			i++;
			buffer[i] = (int)col.r;
			i++;

		}
		c++;
		if (c == 360){ c = 0; }
		for (int index = 0; index < W % 4; index++){
			buffer[i] = 0;
			i++;
		}
	}
}

// Black and white checkerboard
void PixelData::FPABlackWhite(){

	int i = 0;
	
	rgb col0 = { 255, 255, 255 };
	rgb col1 = { 0, 0, 0 };
	rgb col = col0;
	for (int y = 0; y < H; y++){

		for (int x = 0; x < W; x++){
			
				buffer[i] = col.r;
				i++;
				buffer[i] = col.g;
				i++;
				buffer[i] = col.b;
				i++;
			
				if (col.r == 255){ 
					col = col1;
				}
				else if (col.r == 0){
					col = col0;
				}
		}

		for (int index = 0; index < W % 4; index++){
			buffer[i] = 0;
			i++;
		}
	}
}

char* PixelData::getPixelArray(){

	return buffer;
}

void PixelData::resetPixelArray(){
	for (int y = 0; y < H; y++){
		for (int x = 0; x < W; x++){
			pixelArray[x][y] = NULL;
		}
	}
}

char PixelData::getPixel(int x){

	return buffer[x];
}

// for debugging. DOES NOT WORK
void PixelData::dumpBuffer(const char* fileName){
	std::ofstream file;
	file.open(fileName, std::ios::out);
	int i = 0;
	for (int y = 0; y < H; y++){
		for (int x = 0; x < W; x++){
			file << "{";
			file << (int)buffer[i] << ", ";
			i++;
			file << (int)buffer[i] << ", ";
			i++;
			file << (int)buffer[i] << ", ";
			i++;
			file << "}, ";
			
		}
		for (int index = 0; index < W % 4; index++){
			
			i++;
		}
		file << '\n';
	}

	file.close();

}

// Pretty terrain
void PixelData::fillBufferTerrain(){
	int i = 0;
	rgb col;
	for (int y = 0; y < H; y++){

		for (int x = 0; x < W; x++){
			
			if (pixelArray[x][y] <= 60){
				if (pixelArray[x][y] % 3 == 0){ col = { 0, 0, pixelArray[x][y] + 145 }; }
				else{
					col = { 0, 0, pixelArray[x][y] + 160 };
				}
			}
			else if (pixelArray[x][y] > 60 && pixelArray[x][y] <= 180){
				if (pixelArray[x][y] % 3 == 0){ col = { 0, 25 + pixelArray[x][y] / 2, 0 }; }
				else{ col = { 0, 50 + pixelArray[x][y] / 2, 0 }; }
			}
			else if (pixelArray[x][y] > 180 && pixelArray[x][y] <= 220){
				if (pixelArray[x][y] % 3 == 0){ col = { -125 + pixelArray[x][y], -125 + pixelArray[x][y], -125 + pixelArray[x][y] }; }
				else{
					col = { pixelArray[x][y] - 100, pixelArray[x][y] - 100, pixelArray[x][y] - 100 };
				}
			}
			else {
				if (pixelArray[x][y] % 3 == 0){ col = { 100 + pixelArray[x][y] / 2, 100 + pixelArray[x][y] / 2, 100 + pixelArray[x][y] / 2 }; }
				else{
					col = { 125 + pixelArray[x][y] / 2, 125 + pixelArray[x][y] / 2, 125 + pixelArray[x][y] / 2 };
				}
			}
			
		
			buffer[i] = col.r;
			i++;
			buffer[i] = col.g;
			i++;
			buffer[i] = col.b;
			i++;
		}
		for (int index = 0; index < W % 4; index++){
			buffer[i] = 0;
			i++;
		}
	}
}

//Greyscale
void PixelData::fillBufferBW(){
	int i = 0;
	rgb col;
	for (int y = 0; y < H; y++){

		for (int x = 0; x < W; x++){
			
			col = (hslToRgb(0, 0, 1-(((double)pixelArray[x][y]) / 360.0)));

			buffer[i] = col.r;
			i++;
			buffer[i] = col.g;
			i++;
			buffer[i] = col.b;
			i++;
		}
		for (int index = 0; index < W % 4; index++){
			buffer[i] = 0;
			i++;
		}
	}
}

//Colors
void PixelData::fillBufferCOL(){
	int i = 0;
	rgb col;
	for (int y = 0; y < H; y++){

		for (int x = 0; x < W; x++){

			col = hslToRgb(pixelArray[x][y], 1.0, 0.5);
			
			buffer[i] = col.r;
			i++;
			buffer[i] = col.g;
			i++;
			buffer[i] = col.b;
			i++;
		}
		for (int index = 0; index < W % 4; index++){
			buffer[i] = 0;
			i++;
		}
	}
}

//Only works if the seed is part of the first few loops of the algorithm
void PixelData::addSeed(int x, int y, int value){
	pixelArray[x][y] = value;

}

// THE ALGORITHM, Needs to be optimized. ALOT!
void PixelData::FPADiamondSquare(float roughness){

	int curWidth = W - 1;

	while (curWidth != 1){

		square(curWidth, roughness);
		diamond(curWidth, roughness);
		curWidth = curWidth / 2;
		roughness = ceil(roughness / 2);
	}
	fillBufferCOL();
}

void PixelData::diamond(int curWidth, int roughness){
	std::cout << "diamond \n";
	int HcurWidth = curWidth / 2;
	point t = { HcurWidth, 0 };
	point p1 = { 0, 0 };
	point p2 = { 0, 0 };
	point p3 = { 0, 0 };
	point p4 = { 0, 0 };
	int count = 0;
	std::vector<point> list;
	while (t.y <= H - 1){
		while (t.x <= W - 1){
			if (pixelArray[t.x][t.y] == NULL){
				p1 = { t.x - HcurWidth, t.y };
				//if (p1.x < 0){ p1.x = W - 1;} //OLD doesnt work
				if (p1.x >= 0){ list.push_back(p1); count++; }
				p2 = { t.x, t.y - HcurWidth };
				//if (p2.y < 0){ p2.y = H - 1; } //OLD doesnt work
				if (p2.y >= 0){ list.push_back(p2); count++; }
				p3 = { t.x + HcurWidth, t.y };
				//if (p3.x > W - 1){ p3.x = 0; } //OLD doesnt work
				if (p3.x <= W - 1){ list.push_back(p3); count++; }
				p4 = { t.x, t.y + HcurWidth };
				//if (p4.y > H - 1){ p4.y = 0;} //OLD doesnt work
				if (p4.y <= H - 1){ list.push_back(p4); count++; }

				pixelArray[t.x][t.y] = getNewPoint(list, count, roughness);
				count = 0;
				list.clear();
			}
			t.x = t.x + curWidth;


		}
		t.x = t.x - (W - 1) - HcurWidth;
		t.y = t.y + HcurWidth;

	}

}

void PixelData::square(int curWidth, int roughness){
	std::cout << "square \n";
	int HcurWidth = curWidth / 2;
	point t = { HcurWidth, HcurWidth };
	point p1 = { 0, 0 };
	point p2 = { 0, 0 };
	point p3 = { 0, 0 };
	point p4 = { 0, 0 };
	int count = 0;
	std::vector<point> list;
	while (t.y < H - 1){

		while (t.x < W - 1){
			if (pixelArray[t.x][t.y] == NULL){
				p1 = { t.x - HcurWidth, t.y - HcurWidth };
				list.push_back(p1); count++;
				p2 = { t.x + HcurWidth, t.y - HcurWidth };
				list.push_back(p2); count++;
				p3 = { t.x - HcurWidth, t.y + HcurWidth };
				list.push_back(p3); count++;
				p4 = { t.x + HcurWidth, t.y + HcurWidth };
				list.push_back(p4); count++;
				pixelArray[t.x][t.y] = getNewPoint(list, count, roughness);

				count = 0;
				list.clear();
			}
			t.x = t.x + curWidth;
		}
		t.x = HcurWidth;
		t.y = t.y + curWidth;

	}

}

int PixelData::getNewPoint(std::vector<point> list, const int size, int roughness){
	//int ans = ( pixelArray[p1.x][p1.y] + pixelArray[p2.x][p2.y] + pixelArray[p3.x][p3.y] + pixelArray[p4.x][p4.y] ) / 4;
	int ans = 0;
	for (int i = 0; i < size; i++){

		ans = ans + (pixelArray[list[i].x][list[i].y]);
	}
	ans = ans / size;
	ans = ans + ceil(((rand() % roughness) - (roughness / 2)));

	if (ans < 0){ ans = 0; }
	if (ans > 360){ ans = 360; }

	return ans;
}
// END OF ALGORITHM

// Finally works
PixelData::rgb PixelData::hslToRgb(double h, double s, double l){

		rgb col = { 0, 0, 0 };

		double C = (1.0 - abs(2.0f*l - 1.0f)) * s;

		double temp = h / 60.0;
		temp = fmod(temp, 2.0);
		temp -= 1.0;
		temp = abs(temp);
		temp = 1.0 - temp;
		temp = C * temp;
		double X = temp;

		//double X = C * (1.0 - abs(remainder(((h / 60.0)), 2.0) - 1.0));
		double m = l - C/2.0;
		if (h >= 0 && h < 60){ col.r = C; col.g = X; col.b = 0; }
		else if (h >= 60 && h < 120){ col.r = X; col.g = C; col.b = 0; }
		else if (h >= 120 && h < 180){ col.r = 0; col.g = C; col.b = X; }
		else if (h >= 180 && h < 240){ col.r = 0; col.g = X; col.b = C; }
		else if (h >= 240 && h < 300){ col.r = X; col.g = 0; col.b = C; }
		else if (h >= 300 && h < 360){ col.r = C; col.g = 0; col.b = X; }

		col.r += m;
		col.g += m;
		col.b += m;

		col.r = floor(col.r * 255);
		col.g = floor(col.g * 255);
		col.b = floor(col.b * 255);

		return col;
	}