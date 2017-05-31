#include "../include/MeshRenderer.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Texture* texture, Shader* shader)
{
	this->mesh = mesh;
	this->texture = texture;
	this->shader = shader;
}

MeshRenderer::MeshRenderer(Mesh* mesh, Texture* texture)
{
	this->mesh = mesh;
	this->texture = texture;
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::init()
{

}
void MeshRenderer::input(float delta)
{

}
void MeshRenderer::update(float delta)
{

}
//void MeshRenderer::render(Camera* camera)
//{
//	shader->bind();
//
//	texture->bind(0);
//
//	shader->update(*gameObject->getTransform(), *camera);
//
//	mesh->draw();
//}

void MeshRenderer::render(Camera* camera, Shader* shader, Transform parentTransform)
{
	shader->bind();

	texture->bind(0);

	Transform newTranform = *gameObject->getTransform();
	newTranform.GetPos() += parentTransform.GetPos();
	newTranform.GetRot() += parentTransform.GetRot();
	newTranform.GetScale() *= parentTransform.GetScale();
	//shader->update(*gameObject->getTransform(), *camera);
	shader->update(newTranform, *camera, parentTransform);

	mesh->draw();
}