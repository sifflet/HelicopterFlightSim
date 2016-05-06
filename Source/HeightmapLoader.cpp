#include "HeightmapLoader.h"

using namespace std;

HeightmapLoader::HeightmapLoader()
{
	this->img_height = 0;
	this->img_width = 0;
}

bool HeightmapLoader::loadHeightmap(char* fileName)
{
	FILE* filePtr;
	int error;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int imageSize, i, j, k, index;
	unsigned char* bitmapImage;
	unsigned char height;

	// open file
	error = fopen_s(&filePtr, fileName, "rb");
	if(error != 0)
	{
		return false;
	}

	// read file header
	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	//read info header
	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	img_width = bitmapInfoHeader.biWidth;
	img_height = bitmapInfoHeader.biHeight;

	imageSize = img_width * img_height * 3;

	bitmapImage = new unsigned char[imageSize];
	if(!bitmapImage)
	{
		return false;
	}

	// beginning of the bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	count = fread(bitmapImage, 1, imageSize, filePtr);
	if(count != imageSize)
	{
		return false;
	}

	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}

	k = 0;

	heightPoints = vector<Point3> (img_width*img_height, Point3());

	for(j = 0; j < img_height; ++j)
	{
		for(i = 0; i < img_width; ++i)
		{
			height = bitmapImage[k];

			index = (img_height * j) + i;

			heightPoints[index].x = (float)i;
			heightPoints[index].y = (float)height;
			heightPoints[index].z = (float)j;

			k += 3;
		}
	}

	normalizeHeightmap(2.0);

	delete[] bitmapImage;
	bitmapImage = 0;

	return true;
}

void HeightmapLoader::normalizeHeightmap(float normalizer)
{
	for(int j = 0; j < img_height; ++j)
	{
		for(int i = 0; i < img_width; ++i)
		{
			heightPoints[(img_height * j) + i].y /= normalizer;
		}
	}
}