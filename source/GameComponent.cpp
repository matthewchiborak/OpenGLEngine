#include "../include/GameComponent.h"

GameComponent::GameComponent()
{
}

GameComponent::~GameComponent()
{
}

void GameComponent::setGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

void GameComponent::init()
{
	
}
void GameComponent::input(float delta)
{

}
void GameComponent::update(float delta)
{

}
//void GameComponent::render(Camera* camera)
//{
//
//}
void GameComponent::render(Camera* camera)
{

}
void GameComponent::render(Camera* camera, Shader* shader, Transform parentTransform)
{

}

//void GameComponent::addToRenderingEngine()
//{
//
//}