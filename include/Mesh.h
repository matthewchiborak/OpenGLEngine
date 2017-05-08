#ifndef __MESH_H
#define __MESH_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "obj_loader.h"

//Opengl wants xyz cord and forms a triangle between -1 and 1
class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& textCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->pos = pos;
		this->texCoord = textCoord;
		this->normal = normal;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }

private:
	//X y and z cordinates
	glm::vec3 pos;
	//For texture mapping
	glm::vec2 texCoord;
	//Normals for lighting
	glm::vec3 normal;
};

class Mesh
{
public: 
	//Can have any number of triangle
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	//Obj based constructor
	Mesh(const std::string& fileName);

	//Draw the mesh with the graphics card
	void draw();

	virtual ~Mesh();
private:
	Mesh(const Mesh& other) {}
	void operator=(const Mesh& other) {}

	void initMesh(const IndexedModel& model);

	//Enumerate the buffers that will be used for the vertex array buffers, Last one should be num buffers so always know 
	//how many bufferes there are total
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	//Opengl way of refering to mesh data on the cpu. 
	GLuint m_vertexArrayObject;

	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	//Tell opengl how much of the array object we want to be drawn.
	unsigned int m_drawCount;
};

#endif