#include "../include/Bitmap.h"

Bitmap::Bitmap(int width, int height)
{
	this->width = width;
	this->height = height;
	this->pixels = new Pixel[width * height];
}

Bitmap::Bitmap(std::string fileName)
{
	int numComponents;

	//Load texture data
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << fileName << "\n";
	}

	pixels = new Pixel[width * height];

	//Read the data from the image
	//See what colour it is
	for (int i = 0; i < width * height * 4; i++)
	{
		if (i%4 == 0)
		{
			pixels[(i)/4].r = imageData[i];
		}
		else if (i % 4 == 1)
		{
			pixels[i/4].g = imageData[i];
		}
		else if (i % 4 == 2)
		{
			pixels[i/4].b = imageData[i];
		}
		else if (i % 4 == 3)
		{
			pixels[i/4].a = imageData[i];
		}
	}

	stbi_image_free(imageData);
}

Bitmap::~Bitmap()
{
}

int Bitmap::getWidth()
{
	return width;
}
int Bitmap::getHeight()
{
	return height;
}
Pixel* Bitmap::getPixels()
{
	return pixels;
}

Pixel Bitmap::getPixel(int x, int y)
{
	if (x + y*width >= width * height)
	{
		Pixel nope;
		return nope;
	}

	return pixels[x + y*width];
}

void Bitmap::setPixel(int x, int y, int r, int g, int b, int a)
{
	pixels[(x + y * width)].r = r;
	pixels[(x + y * width)].g = g;
	pixels[(x + y * width)].b = b;
	pixels[(x + y * width)].a = a;
}

void Bitmap::flipY()
{
	Pixel* temp = new Pixel[width * height];

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			temp[i + j * width] = pixels[(width - i - 1) + j * width];
		}
	}

	delete pixels;

	pixels = temp;
}
void Bitmap::flipX()
{
	Pixel* temp = new Pixel[width * height];

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			temp[i + j * width] = pixels[( i ) + (height - j - 1) * width];
		}
	}

	delete pixels;

	pixels = temp;
}

void Bitmap::calcTexCoords(int value, int numTextures, int numTexExp, float* XLow, float* XHigh, float* YLow, float* YHigh)
{
	int texX = value / numTextures; //16 textures in the collection
	int texY = texX % numTexExp;
	texX /= numTexExp;

	*XLow = (1.0f - (float)texX / (float)numTexExp) - (1.0f / (float)numTexExp);
	*XHigh = 1.0f - (float)texX / (float)numTexExp;
	*YLow = 1.0f - (float)texY / (float)numTexExp;
	*YHigh = (1.0f - (float)texY / (float)numTexExp) - (1.0f / (float)numTexExp);
}