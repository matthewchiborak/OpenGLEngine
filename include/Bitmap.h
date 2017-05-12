#ifndef __BITMAP_H
#define __BITMAP_H

#include <string>
#include <iostream>

//#include "stb_image.h"
#include "Texture.h"

class Pixel
{
public:
	Pixel() { r = 0; b = 0; g = 0; a = 0; }
	Pixel(int r, int g, int b, int a) { this->r = r; this->g = g; this->b = b; this->a = a; }
	int r;
	int g;
	int b;
	int a;
};

class Bitmap
{
public:
	Bitmap(int width, int height);
	Bitmap(std::string fileName);
	~Bitmap();

	int getWidth();
	int getHeight();
	Pixel* getPixels();
	Pixel getPixel(int x, int y);
	void setPixel(int x, int y, int r, int g, int b, int a);

	void flipX();
	void flipY();

private:
	int width;
	int height;
	Pixel* pixels;
};

#endif
