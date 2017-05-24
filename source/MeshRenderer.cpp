#include "../include/MeshRenderer.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Texture* texture, Shader* shader)
{
	this->mesh = mesh;
	this->texture = texture;
	this->shader = shader;
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::init()
{

}
void MeshRenderer::input()
{

}
void MeshRenderer::update()
{

}
void MeshRenderer::render(Camera* camera)
{
	shader->bind();

	texture->bind(0);

	shader->update(*gameObject->getTransform(), *camera);

	mesh->draw();
}

void MeshRenderer::render(Camera* camera, Shader* shader)
{
	shader->bind();

	texture->bind(0);

	shader->update(*gameObject->getTransform(), *camera);

	mesh->draw();
}