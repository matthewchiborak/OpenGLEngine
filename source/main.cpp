#include <iostream>
#include <GL/glew.h>
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "../include/CoreEngine.h"
#include "../include/TestScene.h"

#include "../include/BoundingSphere.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	BoundingSphere sphere1(glm::fvec3(0, 0, 0), 1);
	BoundingSphere sphere2(glm::fvec3(0, 3, 0), 1);
	BoundingSphere sphere3(glm::fvec3(0, 0, 2), 1);
	BoundingSphere sphere4(glm::fvec3(1, 0, 0), 1);

	IntersectData sphere1IntersectSphere2 = sphere1.intersectBoundingSphere(&sphere2);
	IntersectData sphere1IntersectSphere3 = sphere1.intersectBoundingSphere(&sphere3);
	IntersectData sphere1IntersectSphere4 = sphere1.intersectBoundingSphere(&sphere4);

	std::cout << "1 -> 2: " << sphere1IntersectSphere2.getDoesIntersect() << ", Distance: " << sphere1IntersectSphere2.getDistance() << "\n";
	std::cout << "1 -> 3: " << sphere1IntersectSphere3.getDoesIntersect() << ", Distance: " << sphere1IntersectSphere3.getDistance() << "\n";
	std::cout << "1 -> 4: " << sphere1IntersectSphere4.getDoesIntersect() << ", Distance: " << sphere1IntersectSphere4.getDistance() << "\n";

	CoreEngine::getCoreEngine()->init(WIDTH, HEIGHT, 30, "Hello world!!!");

	TextureManager::getTextureManager()->loadTexture("Arwing", ".\\res\\body.png");

	MeshManager::getMeshManager()->loadMesh("Arwing", ".\\res\\arwing.obj");

	Scene* testScene = new TestScene();
	CoreEngine::getCoreEngine()->loadScene(testScene, "Test", "Test");

	CoreEngine::getCoreEngine()->run();
	
	return 0;
}