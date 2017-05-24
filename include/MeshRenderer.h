#ifndef __MESHRENDERER_H
#define __MESHRENDERER_H

#include "GameComponent.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh* mesh, Texture* texture, Shader* shader);
	~MeshRenderer();

	void init();
	void input();
	void update();
	void render(Camera* camera);
	void render(Camera* camera, Shader* shader);

private:
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
};

#endif