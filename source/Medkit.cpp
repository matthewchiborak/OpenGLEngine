#include "../include/Medkit.h"

float Medkit::SIZEY = 0.3;
float Medkit::SIZEX = 0.3;
int Medkit::healAmount = 25;

Medkit::Medkit(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader, Camera* camera, TestScene* myScene)
{
	this->camera = camera;
	this->myScene = myScene;

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

Medkit::~Medkit()
{
}

void Medkit::init()
{

}

void Medkit::update()
{
	//Have the medkit always face the player
	glm::fvec3 directToCam = transform.GetPos() - camera->getPosition();

	float angleToFaceCam = atan((directToCam.z / directToCam.x));

	if (directToCam.x > 0)
	{
		angleToFaceCam += 3.1415;
	}

	transform.SetRot(glm::fvec3(0, (angleToFaceCam + (3.1415 / 2)) * -1, 0));

	if (((int)camera->getPosition().x / myScene->SPOT_WIDTH) == ((int)transform.GetPos().x / myScene->SPOT_WIDTH) &&
		((int)camera->getPosition().z / myScene->SPOT_DEPTH) == ((int)transform.GetPos().z / myScene->SPOT_DEPTH))
	{
		camera->damage(-healAmount);
		enabled = false;
	}
}