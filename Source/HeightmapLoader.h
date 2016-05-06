#ifndef HEIGHTMAPLOADER_H
#define HEIGHTMAPLOADER_H
#include <iostream>
#include <d3d11.h>
#include "Point3.h"
#include <vector>

using namespace std;

class HeightmapLoader
{
public:
	HeightmapLoader();
	bool loadHeightmap(char* filename);
	vector<Point3> heightPoints;
private:
	void normalizeHeightmap(float);
	int img_width;
	int img_height;
};

#endif