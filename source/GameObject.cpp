#include "../include/GameObject.h"

GameObject::GameObject(std::string name, std::string meshFile, Texture* texture, Shader* shader)
{
	this->name = name;
	mesh = new Mesh(meshFile);
	this->texture = texture;
	this->shader = shader;
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