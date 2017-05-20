#include "../include/Monster.h"

float Monster::SIZEX = 0.35;
float Monster::SIZEY = 0.7;

Monster::Monster(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader, Camera* camera, Scene* myScene)
{
	currentState = IDLE;
	//currentState = CHASE;
	random = rand();

	health = MAX_HEALTH;

	canLook = false;
	canAttack = false;

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

Monster::~Monster()
{
}

void Monster::update()
{
	//All updates that affect all states
	//Maybe should force on the ground?

	//Have the enemy always face the player
	glm::fvec3 directToCam = transform.GetPos() - camera->getPosition();

	float angleToFaceCam = atan((directToCam.z / directToCam.x));
	
	if (directToCam.x > 0)
	{
		angleToFaceCam += 3.1415;
	}

	transform.SetRot(glm::fvec3(0, (angleToFaceCam + (3.1415/2)) * -1, 0));
	
	switch (currentState)
	{
		case IDLE:
			idleUpdate();
			break;
		case CHASE:
			chaseUpdate();
			break;
		case ATTACK:
			attackUpdate();
			break;
		case DYING:
			dyingUpdate();
			break;
		case DEAD:
			deadUpdate();
			break;
	}
}

void Monster::idleUpdate()
{
	std::chrono::high_resolution_clock::time_point timeChrono = Time::getTimeNanoseconds();
	
	if ((timeChrono - lastIdle).count() > 5000000000)
	{
		canLook = true;

		//Reset the last time
		lastIdle = timeChrono;
	}
	else
	{
		if (canLook)
		{
			//-------
			//Line from monster to player. See what parts of world it interests. See if hits player.
			glm::fvec2 lineStart(transform.GetPos().x, transform.GetPos().z);
			glm::fvec3 castDirectionInit(-1 * (transform.GetPos().x - camera->getPosition().x), 0, -1 * (transform.GetPos().z - camera->getPosition().z));

			//glm::mat4 rotMatrix = glm::rotate((float)random, glm::vec3(0, 1, 0));

			glm::fvec2 castDirection(castDirectionInit.x, castDirectionInit.z);
			glm::fvec2 lineEnd = lineStart + castDirection * SHOOT_DISTANCE;

			//Check intersection of the 2 lines
			glm::fvec2 collisionVector;
			bool foundOne = myScene->checkIntersection(&collisionVector, lineStart, lineEnd, false);

			glm::fvec2 playerIntersectVector;
			bool foundPlayer = myScene->lineInterestRect(&playerIntersectVector, lineStart, lineEnd);

			if (foundOne && foundPlayer && (myScene->getLineLength(playerIntersectVector - lineStart) < myScene->getLineLength(collisionVector - lineStart)))
			{
				std::cout << "We've seen the player\n";
				currentState = CHASE;
			}

			//---------

			canLook = false;
		}
	}
}
void Monster::chaseUpdate()
{
	glm::fvec3 directionToCam = transform.GetPos() - camera->getPosition();
	float distanceToCam = sqrtf(directionToCam.x * directionToCam.x + directionToCam.y * directionToCam.y + directionToCam.z * directionToCam.z);

	if (rand() < attackConstant * (Time::getTimeNanoseconds() - lastAttack).count())
	{
		lastAttack = Time::getTimeNanoseconds();
	}

	//TODO factor in deltatime. 
	if (distanceToCam > MOVEMENT_STOP_DISTANCE)
	{
		//glm::fvec3 movementVector(transform.GetPos().x - (directionToCam.x * MOVE_SPEED), 0, transform.GetPos().z - (directionToCam.z * MOVE_SPEED));
		glm::fvec3 movementVector((directionToCam.x * MOVE_SPEED), 0, (directionToCam.z * MOVE_SPEED));
		//glm::fvec3 moveNorm = glm::normalize(movementVector);

		//Collision dectection
		glm::fvec3 collisionResult = myScene->checkCollisionEnemyWalls(this, movementVector, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);

		movementVector.x *= collisionResult.x;
		movementVector.y *= collisionResult.y;
		movementVector.z *= collisionResult.z;

		transform.GetPos() -= movementVector;
	}
	else
	{
		currentState = ATTACK;
	}
}
void Monster::attackUpdate()
{
	std::chrono::high_resolution_clock::time_point timeChrono = Time::getTimeNanoseconds();

	if ((timeChrono - lastAttackStart).count() > 5000000000)
	{
		canAttack = true;

		//Reset the last time
		lastAttackStart = timeChrono;
	}
	else if(canAttack)
	{
		//Line from monster to player. See what parts of world it interests. See if hits player.
		glm::fvec2 lineStart(transform.GetPos().x, transform.GetPos().z);
		glm::fvec3 castDirectionInit(-1 * (transform.GetPos().x - camera->getPosition().x), 0, -1 * (transform.GetPos().z - camera->getPosition().z));

		//glm::mat4 rotMatrix = glm::rotate((float)random, glm::vec3(0, 1, 0));

		glm::fvec2 castDirection(castDirectionInit.x, castDirectionInit.z);
		glm::fvec2 lineEnd = lineStart + castDirection * SHOOT_DISTANCE;

		//Check intersection of the 2 lines
		glm::fvec2 collisionVector;
		bool hitSomething = myScene->checkIntersection(&collisionVector, lineStart, lineEnd, false);

		glm::fvec2 playerIntersectVector;
		bool foundPlayer = myScene->lineInterestRect(&playerIntersectVector, lineStart, lineEnd);

		if (hitSomething && foundPlayer && (myScene->getLineLength(playerIntersectVector - lineStart) < myScene->getLineLength(collisionVector - lineStart)))
		{
			std::cout << "Hit Player\n";
			camera->damage(MONSTER_DAMAGE);
		}

		if (!hitSomething)
		{
			//Missed
			std::cout << "Miss\n";
		}
		else
		{
			//Hit something
			std::cout << "Hit\n";
		}

		//Only attack once
		currentState = CHASE;
		canAttack = false;
	}
}
void Monster::dyingUpdate()
{
	currentState = DEAD;
}
void Monster::deadUpdate()
{
	std::cout << "Im dead.\n";
}

void Monster::init()
{
	
}

void Monster::damage(int amt)
{
	if (currentState == IDLE)
	{
		currentState = CHASE;
	}

	health -= amt;

	if (health <= 0)
	{
		currentState = DYING;
	}
}