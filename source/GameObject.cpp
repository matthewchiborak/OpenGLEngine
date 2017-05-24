#include "../include/GameObject.h"

GameObject::GameObject()
{
	enabled = true;
}

GameObject::GameObject(std::string name, std::string meshFile, Texture* texture, Shader* shader)
{
	this->name = name;
	//mesh = new Mesh(meshFile);
	this->texture = texture;
	this->shader = shader;
	enabled = true;
}

GameObject::GameObject(std::string name, Mesh* mesh, Texture* texture, Shader* shader)
{
	this->name = name;
	//this->mesh = mesh;
	this->texture = texture;
	this->shader = shader;
	enabled = true;
}

GameObject::GameObject(std::string name, Mesh* mesh, Texture* texture, Shader* shader, glm::fvec3 dimensions)
{
	this->name = name;
	//this->mesh = mesh;
	this->texture = texture;
	this->shader = shader;
	this->dimensions = dimensions;
	enabled = true;
}

GameObject* GameObject::createSquare(std::string name, float width, float height, float depth, bool oppositeNormal, float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader)
{
	float w = width / 2;
	float h = height / 2;
	float d = depth / 2;

	Vertex vertices[] =
	{
		Vertex(glm::vec3(w, h, 0), glm::vec2(0, repeatFactorY), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(w, -h, 0), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, -h, 0), glm::vec2(repeatFactorX, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, h, 0), glm::vec2(0, 0), glm::vec3(0, 0, -1))
	};

	Vertex vertices2[] =
	{
		Vertex(glm::vec3(w, h, 0), glm::vec2(0, repeatFactorY), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(w, -h, 0), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, -h, 0), glm::vec2(repeatFactorX, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, h, 0), glm::vec2(0, 0), glm::vec3(0, 0, 1))
	};

	Vertex vertices3[] =
	{
		Vertex(glm::vec3(-w, 0, -d), glm::vec2(0, repeatFactorY), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-w, 0, d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(w, 0, d), glm::vec2(repeatFactorX, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(w, 0, -d), glm::vec2(0, 0), glm::vec3(0, -1, 0))
	};

	Vertex vertices4[] =
	{
		Vertex(glm::vec3(-w, 0, -d), glm::vec2(0, repeatFactorY), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-w, 0, d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(w, 0, d), glm::vec2(repeatFactorX, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(w, 0, -d), glm::vec2(0, 0), glm::vec3(0, 1, 0))
	};

	Vertex vertices5[] =
	{
		Vertex(glm::vec3(0, h, -d), glm::vec2(0, repeatFactorY), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(0, -h, -d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(0, -h, d), glm::vec2(repeatFactorX, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(0, h, d), glm::vec2(0, 0), glm::vec3(-1, 0, 0))
	};

	Vertex vertices6[] =
	{
		Vertex(glm::vec3(0, h, -d), glm::vec2(0, repeatFactorY), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(0, -h, -d), glm::vec2(repeatFactorX, repeatFactorY), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(0, -h, d), glm::vec2(repeatFactorX, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(0, h, d), glm::vec2(0, 0), glm::vec3(1, 0, 0))
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	unsigned int indices2[] = {
		2, 1, 0,
		3, 2, 0,
	};

	Mesh* temp; 
	
	if (!oppositeNormal)
	{
		if (width == 0)
		{
			temp = new Mesh(vertices2, sizeof(vertices2) / sizeof(vertices2[0]), indices, sizeof(indices) / sizeof(indices[0]));
		}
		else if (height == 0)
		{
			temp = new Mesh(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), indices, sizeof(indices) / sizeof(indices[0]));
		}
		else
		{
			temp = new Mesh(vertices6, sizeof(vertices6) / sizeof(vertices6[0]), indices, sizeof(indices) / sizeof(indices[0]));
		}
	}
	else
	{
		if (width == 0)
		{
			temp = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
		}
		else if (height == 0)
		{
			temp = new Mesh(vertices3, sizeof(vertices3) / sizeof(vertices3[0]), indices2, sizeof(indices2) / sizeof(indices2[0]));
		}
		else
		{
			temp = new Mesh(vertices5, sizeof(vertices5) / sizeof(vertices5[0]), indices2, sizeof(indices2) / sizeof(indices2[0]));
		}
	}

	return new GameObject(name, temp, texture, shader, glm::fvec3(width, height, depth));
}

GameObject* GameObject::createSquarePartTexture(std::string name, float width, float height, float depth, bool oppositeNormal, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader)
{
	float w = width / 2;
	float h = height / 2;
	float d = depth / 2;

	Vertex vertices[] =
	{
		Vertex(glm::vec3(w, -h, 0), glm::vec2(XHigher, YLower), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, -h, 0), glm::vec2(XLower, YLower), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, h, 0), glm::vec2(XLower, YHigher), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(w, h, 0), glm::vec2(XHigher, YHigher), glm::vec3(0, 0, -1)),
	};

	Vertex vertices2[] =
	{
		Vertex(glm::vec3(w, -h, 0), glm::vec2(XHigher, YLower), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, -h, 0),  glm::vec2(XLower, YLower), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, h, 0),  glm::vec2(XLower, YHigher), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(w, h, 0), glm::vec2(XHigher, YHigher), glm::vec3(0, 0, 1)),
	};

	Vertex vertices3[] =
	{
		Vertex(glm::vec3(w, 0, -d), glm::vec2(XHigher, YLower), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-w, 0, -d),  glm::vec2(XLower, YLower), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-w, 0, d),  glm::vec2(XLower, YHigher), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(w, 0, d), glm::vec2(XHigher, YHigher), glm::vec3(0, -1, 0)),
	};

	Vertex vertices4[] =
	{
		Vertex(glm::vec3(w, 0, -d), glm::vec2(XHigher, YLower), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-w, 0, -d),  glm::vec2(XLower, YLower), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-w, 0, d),  glm::vec2(XLower, YHigher), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(w, 0, d), glm::vec2(XHigher, YHigher), glm::vec3(0, 1, 0)),
	};

	Vertex vertices5[] =
	{
		Vertex(glm::vec3(0, -h, d), glm::vec2(XHigher, YLower), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(0, -h, -d),  glm::vec2(XLower, YLower), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(0, h, -d),  glm::vec2(XLower, YHigher), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(0, h, d), glm::vec2(XHigher, YHigher), glm::vec3(-1, 0, 0)),
	};

	Vertex vertices6[] =
	{
		Vertex(glm::vec3(0, -h, d), glm::vec2(XHigher, YLower), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(0, -h, -d),  glm::vec2(XLower, YLower), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(0, h, -d),  glm::vec2(XLower, YHigher), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(0, h, d), glm::vec2(XHigher, YHigher), glm::vec3(1, 0, 0)),
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	unsigned int indices2[] = {
		2, 1, 0,
		3, 2, 0,
	};

	Mesh* temp;

	if (!oppositeNormal)
	{
		if (width == 0)
		{
			temp = new Mesh(vertices2, sizeof(vertices2) / sizeof(vertices2[0]), indices, sizeof(indices) / sizeof(indices[0]));
		}
		else if (height == 0)
		{
			temp = new Mesh(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), indices, sizeof(indices) / sizeof(indices[0]));
		}
		else
		{
			temp = new Mesh(vertices6, sizeof(vertices6) / sizeof(vertices6[0]), indices, sizeof(indices) / sizeof(indices[0]));
		}
	}
	else
	{
		if (width == 0)
		{
			temp = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
		}
		else if (height == 0)
		{
			temp = new Mesh(vertices3, sizeof(vertices3) / sizeof(vertices3[0]), indices2, sizeof(indices2) / sizeof(indices2[0]));
		}
		else
		{
			temp = new Mesh(vertices5, sizeof(vertices5) / sizeof(vertices5[0]), indices2, sizeof(indices2) / sizeof(indices2[0]));
		}
	}

	return new GameObject(name, temp, texture, shader, glm::fvec3(width, height, depth));
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

	return new GameObject(name, temp, texture, shader, glm::fvec3(width, height, depth));
}

GameObject* GameObject::createCubePartTexture(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader)
{
	float w = width / 2;
	float h = height / 2;
	float d = depth / 2;

	Vertex vertices[] =
	{
		Vertex(glm::vec3(w, -h, -d), glm::vec2(XHigher, YLower), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, -h, -d), glm::vec2(XLower, YLower), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-w, h, -d), glm::vec2(XLower, YHigher), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(w, h, -d), glm::vec2(XHigher, YHigher), glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(w, -h, d), glm::vec2(XHigher, YLower), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, -h, d),  glm::vec2(XLower, YLower), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-w, h, d),  glm::vec2(XLower, YHigher), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(w, h, d), glm::vec2(XHigher, YHigher), glm::vec3(0, 0, 1)),

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
		Vertex(glm::vec3(-w, -h, d), glm::vec2(XHigher, YLower), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-w, -h, -d),  glm::vec2(XLower, YLower), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-w, h, -d),  glm::vec2(XLower, YHigher), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-w, h, d), glm::vec2(XHigher, YHigher), glm::vec3(1, 0, 0)),

		Vertex(glm::vec3(-w, -h, d), glm::vec2(XHigher, YLower), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, -h, -d),  glm::vec2(XLower, YLower), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, h, -d),  glm::vec2(XLower, YHigher), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-w, h, d), glm::vec2(XHigher, YHigher), glm::vec3(-1, 0, 0)),
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,

		4, 6, 5,
		4, 7, 6,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
	};

	Mesh* temp = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	return new GameObject(name, temp, texture, shader, glm::fvec3(width, height, depth));
}

GameObject::~GameObject()
{
	texture = NULL;
	shader = NULL;

	/*if (mesh!=NULL)
	{
		delete mesh;
	}*/
}

//void GameObject::draw(Camera* camera)
//{
//	shader->bind();
//
//	texture->bind(0);
//
//	shader->update(transform, *camera);
//
//	mesh->draw();
//}

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

Transform* GameObject::getTransform()
{
	return &transform;
}



glm::fvec3 GameObject::getDimensions()
{
	return dimensions;
}

bool GameObject::isEnabled()
{
	return enabled;
}


void GameObject::addChild(GameObject* newChild)
{
	children.push_back(newChild);
}

void GameObject::addComponent(GameComponent* newComponent)
{
	newComponent->setGameObject(this);
	components.push_back(newComponent);
}

/////////////////////////

void GameObject::render(Camera* camera)
{
	//draw(camera);

	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->render(camera);
	}

	for (int i = 0; i < children.size(); i++)
	{
		children.at(i)->render(camera);
	}
}
void GameObject::render(Camera* camera, Shader* shader)
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->render(camera, shader);
	}

	for (int i = 0; i < children.size(); i++)
	{
		children.at(i)->render(camera, shader);
	}
}

void GameObject::input() 
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->input();
	}

	for (int i = 0; i < children.size(); i++)
	{
		children.at(i)->input();
	}
}

void GameObject::update()
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->update();
	}

	for (int i = 0; i < children.size(); i++)
	{
		children.at(i)->update();
	}
}

void GameObject::init()
{

}