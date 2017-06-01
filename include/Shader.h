#ifndef __SHADER_H
#define __SHADER_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include "Transform.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	Shader();
	Shader(const std::string& name, const std::string& fileName);
	Shader(const std::string& fileName);

	std::string getName();

	//Set cpu to use shader
	void bind();

	virtual void update(const Transform& transform, Camera& camera, Transform parentTransform);

	void setAmbientLight(glm::fvec3 light);
	glm::fvec3 getAmbientLight();
	void setBaseColor(glm::fvec3 color);
	glm::fvec3 getBaseColor();

	void setDirectionalBase(glm::fvec3 color, float intensity);
	void setDirectionalDirection(glm::fvec3 direction);

	void setSpecularIntensity(float value);
	void setSpecularExponent(float value);

	static void setPointLight(int index, glm::fvec3 position, glm::fvec3 color, float intensity, float range, float constant, float linear, float exponent);
	static void setSpotLight(int index, glm::fvec3 position, glm::fvec3 color, float intensity, float range, float constant, float linear, float exponent, glm::fvec3 direction, float cutoff);

	virtual ~Shader();

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	//Loads text file from the harddrive
	static std::string LoadShader(const std::string& fileName);

	//Create shader from full text
	static GLuint CreateShader(const std::string& text, GLenum shaderType);

	void addAllUniforms(std::string shaderText);

protected:
	std::string name;
	//If using a geometry shader this will be 3. 2 is just vertex and fragment
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other){}

	enum
	{
		TRANSFORM_U,
		TRANSFORM_PROJECTED,
		BASE_COLOR,
		AMBIENT_LIGHT,
		DIRECTIONAL_LIGHT_BASE_COLOR,
		DIRECTIONAL_LIGHT_BASE_INTENSITY,
		DIRECTIONAL_LIGHT_DIRECTION,

		SPECULAR_INTENSITY,
		SPECULAR_EXPONENT,
		EYE_POS,

		POINT_LIGHT_POSITION0,
		POINT_LIGHT_BASE_COLOR0,
		POINT_LIGHT_BASE_INTENSITY0,
		POINT_LIGHT_ATTEN_CONSTANT0,
		POINT_LIGHT_ATTEN_LINEAR0,
		POINT_LIGHT_ATTEN_EXPONENT0,
		POINT_LIGHT_RANGE0,

		POINT_LIGHT_POSITION1,
		POINT_LIGHT_BASE_COLOR1,
		POINT_LIGHT_BASE_INTENSITY1,
		POINT_LIGHT_ATTEN_CONSTANT1,
		POINT_LIGHT_ATTEN_LINEAR1,
		POINT_LIGHT_ATTEN_EXPONENT1,
		POINT_LIGHT_RANGE1,

		POINT_LIGHT_POSITION2,
		POINT_LIGHT_BASE_COLOR2,
		POINT_LIGHT_BASE_INTENSITY2,
		POINT_LIGHT_ATTEN_CONSTANT2,
		POINT_LIGHT_ATTEN_LINEAR2,
		POINT_LIGHT_ATTEN_EXPONENT2,
		POINT_LIGHT_RANGE2,

		POINT_LIGHT_POSITION3,
		POINT_LIGHT_BASE_COLOR3,
		POINT_LIGHT_BASE_INTENSITY3,
		POINT_LIGHT_ATTEN_CONSTANT3,
		POINT_LIGHT_ATTEN_LINEAR3,
		POINT_LIGHT_ATTEN_EXPONENT3,
		POINT_LIGHT_RANGE3,

		SPOT_LIGHT_POINT_POSITION_0,
		SPOT_LIGHT_POINT_COLOR_0,
		SPOT_LIGHT_POINT_INTENSITY_0,
		SPOT_LIGHT_POINT_CONSTANT_0,
		SPOT_LIGHT_POINT_LINEAR_0,
		SPOT_LIGHT_POINT_EXPONENT_0,
		SPOT_LIGHT_POINT_RANGE_0,
		SPOT_LIGHT_DIRECTION_0,
		SPOT_LIGHT_CUTOFF_0,

		SPOT_LIGHT_POINT_POSITION_1,
		SPOT_LIGHT_POINT_COLOR_1,
		SPOT_LIGHT_POINT_INTENSITY_1,
		SPOT_LIGHT_POINT_CONSTANT_1,
		SPOT_LIGHT_POINT_LINEAR_1,
		SPOT_LIGHT_POINT_EXPONENT_1,
		SPOT_LIGHT_POINT_RANGE_1,
		SPOT_LIGHT_DIRECTION_1,
		SPOT_LIGHT_CUTOFF_1,

		SPOT_LIGHT_POINT_POSITION_2,
		SPOT_LIGHT_POINT_COLOR_2,
		SPOT_LIGHT_POINT_INTENSITY_2,
		SPOT_LIGHT_POINT_CONSTANT_2,
		SPOT_LIGHT_POINT_LINEAR_2,
		SPOT_LIGHT_POINT_EXPONENT_2,
		SPOT_LIGHT_POINT_RANGE_2,
		SPOT_LIGHT_DIRECTION_2,
		SPOT_LIGHT_CUTOFF_2,

		SPOT_LIGHT_POINT_POSITION_3,
		SPOT_LIGHT_POINT_COLOR_3,
		SPOT_LIGHT_POINT_INTENSITY_3,
		SPOT_LIGHT_POINT_CONSTANT_3,
		SPOT_LIGHT_POINT_LINEAR_3,
		SPOT_LIGHT_POINT_EXPONENT_3,
		SPOT_LIGHT_POINT_RANGE_3,
		SPOT_LIGHT_DIRECTION_3,
		SPOT_LIGHT_CUTOFF_3,

		NUM_UNIFORMS
	};

	//Keeps track of where program is
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	//MUST BE THE SAME AS IT IS IN THE SHADER glsl. 
	static const int MAX_POINT_LIGHTS = 4;
	static PointLight pointLights[MAX_POINT_LIGHTS];
	//GLuint m_pointLight_uniforms[MAX_POINT_LIGHTS * 5];

	//Spot lights
	static const int MAX_SPOT_LIGHTS = 4;
	static SpotLight spotLights[MAX_SPOT_LIGHTS];

	glm::fvec3 ambientLight;
	glm::fvec3 baseColor;

	DirectionalLight directionalLight;

	float specularIntensity;
	//This is how wide the reflection is
	float specularExponent;

	std::string vertexShaderText;
	std::string fragmentShaderText;
};

#endif