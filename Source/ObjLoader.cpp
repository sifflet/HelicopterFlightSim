#include "ObjLoader.h"

using namespace std;

vector<Point3> ObjLoader::getVertices()
{
	return this->vertices;
}

vector<Vector3> ObjLoader::getNormals()
{
	return this->normals;
}

vector<vector<GLuint>> ObjLoader::getFaces()
{
	return this->faces;
}

void ObjLoader::loadObj(const char* filename)
{
	ifstream in(filename, ios::in);

	if(!in)
	{
		cerr << "Cannot open" << filename << endl; exit(1);
	}

	string line;
	while(getline(in, line))
	{
		if(line.substr(0, 2) == "v ")
		{
			istringstream s(line.substr(2));
			Point3 v = Point3();
			s >> v.x;
			s >> v.y;
			s >> v.z;

			vertices.push_back(v);
		}
		else if(line.substr(0, 2) == "f ")
		{
			istringstream s(line.substr(2));
			GLushort a, b, c;
			string elem;
			s >> elem;
			a = atoi(elem.substr(0, elem.find("/")).c_str());

			s >> elem;
			b = atoi(elem.substr(0, elem.find("/")).c_str());
			
			s >> elem;
			c = atoi(elem.substr(0, elem.find("/")).c_str());

			a--;
			b--;
			c--;

			vector<GLuint> tempVec;
			tempVec.push_back(a);
			tempVec.push_back(b);
			tempVec.push_back(c);

			faces.push_back(tempVec);
			normals.push_back(calculateNormal(tempVec).flip());
		}
	}
}

Vector3 ObjLoader::calculateNormal(vector<GLuint> face)
{
	Point3 o = vertices[face[0]];
	Point3 a = vertices[face[1]];
	Point3 b = vertices[face[2]];

	Vector3 OA = Vector3(a.x - o.x, a.y - o.y, a.z - o.z);
	Vector3 OB = Vector3(b.x - o.x, b.y - o.y, b.z - o.z);

	Vector3 OBxOA = OB.cross(OA);
	OBxOA.normalizeVector3();

	return OBxOA;
}