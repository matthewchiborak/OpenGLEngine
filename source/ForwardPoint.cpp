#include "../include/ForwardPoint.h"

ForwardPoint* ForwardPoint::s_instance = 0;

ForwardPoint::ForwardPoint()
{
	//Create new shader program
	m_program = glCreateProgram();

	//Create the vertex and fragment shaders
	m_shaders[0] = CreateShader(LoadShader(".\\res\\ForwardPoint.vs.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(".\\res\\ForwardPoint.fs.txt"), GL_FRAGMENT_SHADER);

	//Add shaders to the shader program
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	//Attributes
	glBindAttribLocation(m_program, 0, "position"); //MUST BE SPELLED THE SAME AS IN THE VERTEX
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	//Link
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program failed to link: ");

	//Validation
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid: ");

	//Uniforms
	//Get access to the transform uniform in the shader
	uniforms[ForwardPointUniforms::MVP] = glGetUniformLocation(m_program, "MVP");
	uniforms[ForwardPointUniforms::MODEL] = glGetUniformLocation(m_program, "model");
	uniforms[ForwardPointUniforms::SPECULAR_INTENSITY] = glGetUniformLocation(m_program, "specularIntensity");
	uniforms[ForwardPointUniforms::SPECULAR_EXPONENT] = glGetUniformLocation(m_program, "specularExponent");
	uniforms[ForwardPointUniforms::EYE_POS] = glGetUniformLocation(m_program, "eyePos");
	
	uniforms[ForwardPointUniforms::POINT_LIGHT_POSITION] = glGetUniformLocation(m_program, "pointLight.position");
	uniforms[ForwardPointUniforms::POINT_LIGHT_BASE_INTENSITY] = glGetUniformLocation(m_program, "pointLight.base.intensity");
	uniforms[ForwardPointUniforms::POINT_LIGHT_BASE_COLOR] = glGetUniformLocation(m_program, "pointLight.base.color");
	uniforms[ForwardPointUniforms::POINT_LIGHT_ATTEN_CONSTANT] = glGetUniformLocation(m_program, "pointLight.atten.constant");
	uniforms[ForwardPointUniforms::POINT_LIGHT_ATTEN_LINEAR] = glGetUniformLocation(m_program, "pointLight.atten.linear");
	uniforms[ForwardPointUniforms::POINT_LIGHT_ATTEN_EXPONENT] = glGetUniformLocation(m_program, "pointLight.atten.exponent");
	uniforms[ForwardPointUniforms::POINT_LIGHT_RANGE] = glGetUniformLocation(m_program, "pointLight.range");
}

ForwardPoint* ForwardPoint::getForwardPoint()
{
	if (!s_instance)
	{
		s_instance = new ForwardPoint();
	}

	return s_instance;
}

ForwardPoint::~ForwardPoint()
{
	if (s_instance)
	{
		delete s_instance;
	}
}

void ForwardPoint::update(const Transform& transform, Camera& camera)
{
	//Get the modelViewProjection
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(uniforms[ForwardPointUniforms::MODEL], 1, GL_FALSE, &transform.GetModel()[0][0]);
	glUniformMatrix4fv(uniforms[ForwardPointUniforms::MVP], 1, GL_FALSE, &model[0][0]);

	/*POINT_LIGHT_POSITION,
	POINT_LIGHT_BASE_COLOR,
	POINT_LIGHT_BASE_INTENSITY,
	POINT_LIGHT_ATTEN_CONSTANT,
	POINT_LIGHT_ATTEN_LINEAR,
	POINT_LIGHT_ATTEN_EXPONENT,
	POINT_LIGHT_RANGE,*/
	
	glUniform3fv(uniforms[ForwardPointUniforms::POINT_LIGHT_POSITION], 1, &RenderingEngine::getRenderingEngine()->getPointLight()->getPosition()[0]);
	glUniform1f(uniforms[ForwardPointUniforms::POINT_LIGHT_BASE_INTENSITY], RenderingEngine::getRenderingEngine()->getPointLight()->getBaseIntensity());
	glUniform3fv(uniforms[ForwardPointUniforms::POINT_LIGHT_BASE_COLOR], 1, &RenderingEngine::getRenderingEngine()->getPointLight()->getBaseColor()[0]);
	glUniform1f(uniforms[ForwardPointUniforms::POINT_LIGHT_ATTEN_CONSTANT], RenderingEngine::getRenderingEngine()->getPointLight()->getConstant());
	glUniform1f(uniforms[ForwardPointUniforms::POINT_LIGHT_ATTEN_LINEAR], RenderingEngine::getRenderingEngine()->getPointLight()->getLinear());
	glUniform1f(uniforms[ForwardPointUniforms::POINT_LIGHT_ATTEN_EXPONENT], RenderingEngine::getRenderingEngine()->getPointLight()->getExponent());
	glUniform1f(uniforms[ForwardPointUniforms::POINT_LIGHT_RANGE], RenderingEngine::getRenderingEngine()->getPointLight()->getRange());

	glUniform1f(uniforms[ForwardPointUniforms::SPECULAR_INTENSITY], RenderingEngine::getRenderingEngine()->getSpecularIntensity());
	glUniform1f(uniforms[ForwardPointUniforms::SPECULAR_EXPONENT], RenderingEngine::getRenderingEngine()->getSpecularExponent());
	glUniform3fv(uniforms[ForwardPointUniforms::EYE_POS], 1, &camera.getPosition()[0]);
}