#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>
#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/gtx/transform.hpp>

enum Direction
{
	MOVE_X,
	MOVE_Y,
	MOVE_Z,
	ROT_X,
	ROT_Y,
	ROT_Z,
	SCALE_ALL,
	SCALE_X,
	SCALE_Y,
	SCALE_Z
};

class Vec9
{
public:
	Vec9()
	{

	}
	Vec9(float posx, float posy, float posz, float rotx, float roty, float rotz, float scalex, float scaley, float scalez)
	{
		pos.x = posx;
		pos.y = posy;
		pos.z = posz;
		rot.x = rotx;
		rot.y = roty;
		rot.z = rotz;
		scale.x = scalex;
		scale.y = scaley;
		scale.z = scalez;
	}

	Vec9 multiplyByScalar(float scalar)
	{
		Vec9 result;

		result.pos.x = this->pos.x * scalar;
		result.pos.y = this->pos.y * scalar;
		result.pos.z = this->pos.z * scalar;

		result.rot.x = this->rot.x * scalar;
		result.rot.y = this->rot.y * scalar;
		result.rot.z = this->rot.z * scalar;

		result.scale.x = this->scale.x * scalar;
		result.scale.y = this->scale.y * scalar;
		result.scale.z = this->scale.z * scalar;

		return result;
	}

	Vec9(int direction, float magnitude)
	{
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
		rot.x = 0;
		rot.y = 0;
		rot.z = 0;
		scale.x = 0;
		scale.y = 0;
		scale.z = 0;

		if (direction == MOVE_X)
		{
			pos.x = magnitude;
		}
		else if (direction == MOVE_Y)
		{
			pos.y = magnitude;
		}
		else if (direction == MOVE_Z)
		{
			pos.z = magnitude;
		}
		else if (direction == ROT_X)
		{
			rot.x = magnitude;
		}
		else if (direction == ROT_Y)
		{
			rot.y = magnitude;
		}
		else if (direction == ROT_Z)
		{
			rot.z = magnitude;
		}
		else if (direction == SCALE_X)
		{
			scale.x = magnitude;
		}
		else if (direction == SCALE_Y)
		{
			scale.y = magnitude;
		}
		else if (direction == SCALE_Z)
		{
			scale.z = magnitude;
		}
		else if (direction == SCALE_ALL)
		{
			scale.x = magnitude;
			scale.y = magnitude;
			scale.z = magnitude;
		}
	}

	glm::fvec3 pos;
	glm::fvec3 rot;
	glm::fvec3 scale;

	static Vec9 createVec9(float posx, float posy, float posz, float rotx, float roty, float rotz, float scalex, float scaley, float scalez)
	{
		return Vec9(posx, posy, posz, rotx, roty, rotz, scalex, scaley, scalez);
	}

	static Vec9 createVec9(int direction, float magnitude)
	{
		return Vec9(direction, magnitude);
	}

	static glm::fvec3 rotate(float angle, glm::vec3 axis)
	{
		
	}

	static glm::fvec3 lerp(glm::fvec3 start, glm::fvec3 end, double lerpFactor)
	{
		glm::fvec3 result;
		result.x = (1 - lerpFactor) * start.x + lerpFactor * end.x;
		result.y = (1 - lerpFactor) * start.y + lerpFactor * end.y;
		result.z = (1 - lerpFactor) * start.z + lerpFactor * end.z;

		return result;
	}
};

class Transform
{
public:
	Transform(const glm::fvec3& pos = glm::fvec3(), const glm::fvec3& rot = glm::fvec3(), const glm::fvec3& scale = glm::fvec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}
	

	//Convert attributes to matrix representation
	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(m_pos);

		//Rot use quaterions to prevent gimble lock
		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));

		glm::mat4 scaleMatrix = glm::scale(m_scale);

		//Multiply them together. Order matters. Order is right to left. 
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::fvec3& GetPos() { return m_pos; }
	inline glm::fvec3& GetRot() { return m_rot; }
	inline glm::fvec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::fvec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::fvec3& rot) { m_rot = rot; }
	inline void SetScale(const glm::fvec3& scale) { m_scale = scale; }
private:
	glm::fvec3 m_pos;
	//VERY IMPORTANT. THIS IS IN RADIANS
	glm::fvec3 m_rot;
	glm::fvec3 m_scale;
};

#endif