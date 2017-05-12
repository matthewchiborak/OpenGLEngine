#include "../include/GameObject.h"

GameObject::GameObject(std::string name, std::string meshFile, Texture* texture, Shader* shader)
{
	this->name = name;
	mesh = new Mesh(meshFile);
	this->texture = texture;
	this->shader = shader;
}

GameObject::GameObject(std::string name, Mesh* mesh, Texture* texture, Shader* shader)
{
	this->name = name;
	this->mesh = mesh;
	this->texture = texture;
	this->shader = shader;
}

GameObject* GameObject::createSquare(std::string name, float width, float height, float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader)
{
	float w = width / 2;
	float h = height / 2;

	Vertex vertices[] =
	{
		Vertex(glm::vec3(-w, -h, 0), glm::vec2(repeatFactorX, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, h, 0), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(w, h, 0), glm::vec2(0, repeatFactorY), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(w, -h, 0), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, 0, -1)),
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	Mesh* temp = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	return new GameObject(name, temp, texture, shader);
}

GameObject* GameObject::createCube(std::string name, float width, float height, float depth, float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader)
{
	//fvec3??????
	float w = width / 2;
	float h = height / 2;
	float d = depth / 2;

	Vertex vertices[] =
	{
		Vertex(glm::vec3(-w, -h, -d), glm::vec2(repeatFactorX, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, h, -d), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(w, h, -d), glm::vec2(0, repeatFactorY), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(w, -h, -d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-w, -h, d), glm::vec2(repeatFactorX, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, h, d), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(w, h, d), glm::vec2(0, repeatFactorY), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(w, -h, d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-w, -h, -d), glm::vec2(0, repeatFactorY), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-w, -h, d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(w, -h, d), glm::vec2(repeatFactorX, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(w, -h, -d), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(-w, h, -d), glm::vec2(0, repeatFactorY), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-w, h, d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(w, h, d), glm::vec2(repeatFactorX, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(w, h, -d), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-w, -h, -d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, -h, d), glm::vec2(repeatFactorX, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, h, d), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, h, -d), glm::vec2(0, repeatFactorY), glm::vec3(-1, 0, 0)),

		Vertex(glm::vec3(w, -h, -d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(w, -h, d), glm::vec2(repeatFactorX, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(w, h, d), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(w, h, -d), glm::vec2(0, repeatFactorY), glm::vec3(1, 0, 0)),
	};

	unsigned int indices[] = { 
		0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
	};

	Mesh* temp = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	return new GameObject(name, temp, texture, shader);
}

GameObject::~GameObject()
{
	texture = NULL;
	shader = NULL;

	if (mesh!=NULL)
	{
		delete mesh;
	}
}

void GameObject::draw(Camera* camera)
{
	shader->bind();

	texture->bind(0);

	shader->update(transform, *camera);

	mesh->draw();
}

void GameObject::move(Vec9 change)
{
	transform.GetPos().x += change.pos.x;
	transform.GetPos().y += change.pos.y;
	transform.GetPos().z += change.pos.z;

	transform.GetRot().x += change.rot.x;
	transform.GetRot().y += change.rot.y;
	transform.GetRot().z += change.rot.z;

	transform.GetScale().x += change.scale.x;
	transform.GetScale().y += change.scale.y;
	transform.GetScale().z += change.scale.z;
}
void GameObject::setTransform(Vec9 change)
{
	transform.SetPos(change.pos);
	transform.SetRot(change.rot);
	transform.SetScale(change.scale);
}

std::string GameObject::getName()
{
	return name;
}