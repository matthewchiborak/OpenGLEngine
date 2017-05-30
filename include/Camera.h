#ifndef __CAMERA_H
#define __CAMERA_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>
#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/gtx/transform.hpp>
#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/gtc/quaternion.hpp>

class Camera
{
public:
	//Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	Camera(Vec9 atLookUp, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);

		//UP AND FORWARD SHOULD BE NORMALIZED
		m_position = atLookUp.pos;
		m_forward = atLookUp.rot;
		m_up = atLookUp.scale;
		//m_forward = glm::vec3(0, 0, 1);
		//m_up = glm::vec3(0, 1, 0);
		sensitivity = 90.0f / 10000.0f;
	}

	//Constructor for an orthographic camera. 
	Camera(Vec9 atLookUp, float left, float right, float top, float bottom, float zNear, float zFar)
	{
		m_perspective = glm::ortho(left, right, top, bottom, zNear, zFar);

		//UP AND FORWARD SHOULD BE NORMALIZED
		m_position = atLookUp.pos;
		m_forward = atLookUp.rot;
		m_up = atLookUp.scale;
		//m_forward = glm::vec3(0, 0, 1);
		//m_up = glm::vec3(0, 1, 0);
		sensitivity = 90.0f / 10000.0f;
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	void movePosition(glm::fvec3 at)
	{
		m_position += at;
	}
	void moveForward(glm::fvec3 look)
	{
		m_forward += look;
	}
	void moveUp(glm::fvec3 up)
	{
		m_up += up;
	}
	void setPosition(glm::fvec3 at)
	{
		m_position = at;
	}
	void setForward(glm::fvec3 look)
	{
		m_forward = look;
	}
	void setUp(glm::fvec3 up)
	{
		m_up = up;
	}
	glm::fvec3 getPosition()
	{
		return m_position;
	}
	glm::fvec3 getForward()
	{
		return m_forward;
	}
	glm::fvec3 getUp()
	{
		return m_up;
	}
	glm::fvec3 getLeft()
	{
		return glm::normalize(glm::cross(m_up, m_forward));
	}
	glm::fvec3 getRight()
	{
		return glm::normalize(glm::cross(m_forward, m_up));
	}
	void setPerspective(float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	}
	void setOrthographic(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		m_perspective = glm::ortho(left, right, bottom, top, zNear, zFar);
	}
	void setPerspective(glm::mat4 m_perspective)
	{
		this->m_perspective = m_perspective;
	}
	void setOrthographic(glm::mat4 m_ortho)
	{
		this->m_perspective = m_ortho;
	}
	glm::mat4 getPerspective()
	{
		return m_perspective;
	}
	float getSensitivity()
	{
		return sensitivity;
	}

	void rotateXQuat(float angle)
	{

	}

	void rotateX(float angle)
	{
		//glm::fvec3 Haxis(1, 0, 0);
		//glm::fvec3 Vaxis(0, 1, 0);
		glm::fvec3 Vaxis = getUp();
		

		//Forward rotate the angle around y axis. and normalize
		float sinHalfAngle = (float)sin((angle / 2));
		float cosHalfAngle = (float)cos((angle / 2));

		float rX = Vaxis.x * sinHalfAngle;
		float rY = Vaxis.y * sinHalfAngle;
		float rZ = Vaxis.z * sinHalfAngle;
		float rW = cosHalfAngle;

		glm::quat rotation(rW, rX, rY, rZ);

		m_forward = rotation * m_forward;


	/*	m_up = glm::cross(m_forward, Haxis);
		m_up = glm::normalize(m_up);*/
	}

	void rotateY(float angle)
	{
		/*if (m_forward.z > 0)
		{
			angle *= -1;
		}*/

		//glm::fvec3 Haxis(1, 0, 0);
		glm::fvec3 Haxis = getRight();

		//Forward rotate the angle around Haxis.
		//MIGHT NEED TO CONVERT TO RADIANS
		float sinHalfAngle = (float)sin((angle / 2));
		float cosHalfAngle = (float)cos((angle / 2));

		float rX = Haxis.x * sinHalfAngle;
		float rY = Haxis.y * sinHalfAngle;
		float rZ = Haxis.z * sinHalfAngle;
		float rW = cosHalfAngle;

		glm::quat rotation(rW, rX, rY, rZ);

		m_forward = rotation * m_forward;

		/*m_up = glm::cross(m_forward, Haxis);
		m_up = glm::normalize(m_up);*/
	}

private:
	glm::mat4 m_perspective;
	glm::fvec3 m_position;
	glm::fvec3 m_forward;
	glm::fvec3 m_up;

	//How much the camera moves with mouse input. Degrees per pixel
	float sensitivity;
};

#endif