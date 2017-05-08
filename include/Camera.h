#ifndef __CAMERA_H
#define __CAMERA_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>
#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/gtx/transform.hpp>

class Camera
{
public:
	//Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	Camera(Vec9 atLookUp, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = atLookUp.pos;
		m_forward = atLookUp.rot;
		m_up = atLookUp.scale;
		//m_forward = glm::vec3(0, 0, 1);
		//m_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	void movePosition(glm::vec3 at)
	{
		m_position += at;
	}
	void moveForward(glm::vec3 look)
	{
		m_forward += look;
	}
	void moveUp(glm::vec3 up)
	{
		m_up += up;
	}
	void setPosition(glm::vec3 at)
	{
		m_position = at;
	}
	void setForward(glm::vec3 look)
	{
		m_forward = look;
	}
	void setUp(glm::vec3 up)
	{
		m_up = up;
	}
	void setPerspective(float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	}

private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

#endif