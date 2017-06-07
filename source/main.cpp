#include <iostream>
#include <GL/glew.h>
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "../include/CoreEngine.h"
#include "../include/TestScene.h"

//TESTING
#include "../include/BoundingSphere.h"
#include "../include/AABB.h"
#include "../include/Plane.h"

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

	AABB aabb1(glm::fvec3(0, 0, 0), glm::fvec3(1, 1, 1));
	AABB aabb2(glm::fvec3(1, 1, 1), glm::fvec3(2, 2, 2));
	AABB aabb3(glm::fvec3(1, 0, 0), glm::fvec3(2, 1, 1));
	AABB aabb4(glm::fvec3(0, 0, -2), glm::fvec3(1, 1, -1));
	AABB aabb5(glm::fvec3(0, 0.5, 0), glm::fvec3(1, 1.5, 1));

	IntersectData aabb1IntersectAabb2 = aabb1.intersectAABB(&aabb2);
	IntersectData aabb1IntersectAabb3 = aabb1.intersectAABB(&aabb3);
	IntersectData aabb1IntersectAabb4 = aabb1.intersectAABB(&aabb4);
	IntersectData aabb1IntersectAabb5 = aabb1.intersectAABB(&aabb5);

	std::cout << "\n";
	std::cout << "1 -> 2: " << aabb1IntersectAabb2.getDoesIntersect() << ", Distance: " << aabb1IntersectAabb2.getDistance() << "\n";
	std::cout << "1 -> 3: " << aabb1IntersectAabb3.getDoesIntersect() << ", Distance: " << aabb1IntersectAabb3.getDistance() << "\n";
	std::cout << "1 -> 4: " << aabb1IntersectAabb4.getDoesIntersect() << ", Distance: " << aabb1IntersectAabb4.getDistance() << "\n";
	std::cout << "1 -> 5: " << aabb1IntersectAabb5.getDoesIntersect() << ", Distance: " << aabb1IntersectAabb5.getDistance() << "\n";

	std::cout << "\n";
	Plane plane1(glm::fvec3(0, 1, 0), 0);

	IntersectData plane1IntersectSphere1 = plane1.intersectSphere(&sphere1);
	IntersectData plane1IntersectSphere2 = plane1.intersectSphere(&sphere2);
	IntersectData plane1IntersectSphere3 = plane1.intersectSphere(&sphere3);
	IntersectData plane1IntersectSphere4 = plane1.intersectSphere(&sphere4);

	std::cout << "1 -> 1: " << plane1IntersectSphere1.getDoesIntersect() << ", Distance: " << plane1IntersectSphere1.getDistance() << "\n";
	std::cout << "1 -> 2: " << plane1IntersectSphere2.getDoesIntersect() << ", Distance: " << plane1IntersectSphere2.getDistance() << "\n";
	std::cout << "1 -> 3: " << plane1IntersectSphere3.getDoesIntersect() << ", Distance: " << plane1IntersectSphere3.getDistance() << "\n";
	std::cout << "1 -> 4: " << plane1IntersectSphere4.getDoesIntersect() << ", Distance: " << plane1IntersectSphere4.getDistance() << "\n";

	//End of testing TODO

	CoreEngine::getCoreEngine()->init(WIDTH, HEIGHT, 30, "Hello world!!!");

	TextureManager::getTextureManager()->loadTexture("Arwing", ".\\res\\body.png");

	MeshManager::getMeshManager()->loadMesh("Arwing", ".\\res\\arwing.obj");

	Scene* testScene = new TestScene();
	CoreEngine::getCoreEngine()->loadScene(testScene, "Test", "Test");

	CoreEngine::getCoreEngine()->run();
	
	return 0;
}