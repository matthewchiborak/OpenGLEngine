#include "../include/Monster.h"

float Monster::SIZEX = 0.35;
float Monster::SIZEY = 0.7;

Monster::Monster(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader)
{
	float w = width / 2;
	float h = height / 2;
	float d = depth / 2;

	Vertex vertices[] =
	{
		Vertex(glm::vec3(w, h, d), glm::vec2(XHigher, YLower), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, h, d), glm::vec2(XLower, YLower), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, -h, d), glm::vec2(XLower, YHigher), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(w, -h, d), glm::vec2(XHigher, YHigher), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(w, h, -d), glm::vec2(XHigher, YLower), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, h, -d),  glm::vec2(XLower, YLower), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, -h, -d),  glm::vec2(XLower, YHigher), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(w, -h, -d), glm::vec2(XHigher, YHigher), glm::vec3(0, 0, -1)),

		//Floor and ceiling
		Vertex(glm::vec3(w, -h, -d), glm::vec2(XHigher, YLower), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-w, -h, -d),  glm::vec2(XLower, YLower), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-w, -h, d),  glm::vec2(XLower, YHigher), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(w, -h, d), glm::vec2(XHigher, YHigher), glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(w, h, -d), glm::vec2(XHigher, YLower), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-w, h, -d),  glm::vec2(XLower, YLower), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-w, h, d),  glm::vec2(XLower, YHigher), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(w, h, d), glm::vec2(XHigher, YHigher), glm::vec3(0, 1, 0)),

		//Wall
		//THESE 2 WERE THE SAME TODO FIX IN THE GAMEOBJECT ONE AS WELL
		Vertex(glm::vec3(w, h, d), glm::vec2(XHigher, YLower), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(w, h, -d),  glm::vec2(XLower, YLower), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(w, -h, -d),  glm::vec2(XLower, YHigher), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(w, -h, d), glm::vec2(XHigher, YHigher), glm::vec3(1, 0, 0)),

		Vertex(glm::vec3(-w, h, d), glm::vec2(XHigher, YLower), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, h, -d),  glm::vec2(XLower, YLower), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, -h, -d),  glm::vec2(XLower, YHigher), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, -h, d), glm::vec2(XHigher, YHigher), glm::vec3(-1, 0, 0)),
	};


	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,

		4, 6, 5,
		4, 7, 6,

		/*8, 9, 10,
		8, 10, 11,*/
		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		/*16, 17, 18,
		16, 18, 19,*/
		18, 17, 16,
		19, 18, 16,

		/*22, 21, 20,
		23, 22, 20*/
		20, 21, 22,
		20, 22, 23
	};

	this->name = name;
	this->shader = shader;
	this->texture = texture;

	this->mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	dimensions.x = width;
	dimensions.y = height;
	dimensions.z = depth;
}

Monster::~Monster()
{
}

void Monster::update()
{
	
}

void Monster::init()
{
	
}