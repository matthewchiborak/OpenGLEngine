#include "../include/ForwardDirectional.h"

ForwardDirectional* ForwardDirectional::s_instance = 0;

//ForwardDirectional::ForwardDirectional(const std::string& fileName)
ForwardDirectional::ForwardDirectional()
{
	//Create new shader program
	m_program = glCreateProgram();

	//Create the vertex and fragment shaders
	//m_shaders[0] = CreateShader(LoadShader(fileName + ".vs.txt"), GL_VERTEX_SHADER);
	//m_shaders[1] = CreateShader(LoadShader(fileName + ".fs.txt"), GL_FRAGMENT_SHADER);
	m_shaders[0] = CreateShader(LoadShader(".\\res\\ForwardDirectional.vs.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(".\\res\\ForwardDirectional.fs.txt"), GL_FRAGMENT_SHADER);

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
	uniforms[ForwardDirectionalUniforms::MVP] = glGetUniformLocation(m_program, "MVP");
	uniforms[ForwardDirectionalUniforms::MODEL] = glGetUniformLocation(m_program, "model");
	uniforms[ForwardDirectionalUniforms::SPECULAR_INTENSITY] = glGetUniformLocation(m_program, "specularIntensity");
	uniforms[ForwardDirectionalUniforms::SPECULAR_EXPONENT] = glGetUniformLocation(m_program, "specularExponent");
	uniforms[ForwardDirectionalUniforms::EYE_POS] = glGetUniformLocation(m_program, "eyePos");
	uniforms[ForwardDirectionalUniforms::DIRECTIONAL_LIGHT_BASE_COLOR] = glGetUniformLocation(m_program, "directionalLight.base.color");
	uniforms[ForwardDirectionalUniforms::DIRECTIONAL_LIGHT_BASE_INTENSITY] = glGetUniformLocation(m_program, "directionalLight.base.intensity");
	uniforms[ForwardDirectionalUniforms::DIRECTIONAL_LIGHT_DIRECTION] = glGetUniformLocation(m_program, "directionalLight.direction");
}

ForwardDirectional* ForwardDirectional::getForwardDirectional()
{
	if (!s_instance)
	{
		s_instance = new ForwardDirectional();
	}

	return s_instance;
}

ForwardDirectional::~ForwardDirectional()
{
	if (s_instance)
	{
		delete s_instance;
	}
}

void ForwardDirectional::update(const Transform& transform, Camera& camera, Transform parentTransform)
{
	//Get the modelViewProjection
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(uniforms[ForwardDirectionalUniforms::MODEL], 1, GL_FALSE, &transform.GetModel()[0][0]);
	glUniformMatrix4fv(uniforms[ForwardDirectionalUniforms::MVP], 1, GL_FALSE, &model[0][0]);
	
	glUniform3fv(uniforms[ForwardDirectionalUniforms::DIRECTIONAL_LIGHT_BASE_COLOR], 1, &RenderingEngine::getRenderingEngine()->getDirectionalLight()->getBaseLight().getColor()[0]);
	glUniform1f(uniforms[ForwardDirectionalUniforms::DIRECTIONAL_LIGHT_BASE_INTENSITY], RenderingEngine::getRenderingEngine()->getDirectionalLight()->getBaseLight().getIntensity());
	glUniform3fv(uniforms[ForwardDirectionalUniforms::DIRECTIONAL_LIGHT_DIRECTION], 1, &RenderingEngine::getRenderingEngine()->getDirectionalLight()->getDirection()[0]);

	glUniform1f(uniforms[ForwardDirectionalUniforms::SPECULAR_INTENSITY], RenderingEngine::getRenderingEngine()->getSpecularIntensity());
	glUniform1f(uniforms[ForwardDirectionalUniforms::SPECULAR_EXPONENT], RenderingEngine::getRenderingEngine()->getSpecularExponent());
	glUniform3fv(uniforms[ForwardDirectionalUniforms::EYE_POS], 1, &camera.getPosition()[0]);
}

//void ForwardDirectional::setForwardDirectional(ForwardDirectional* forwardDirectional)
//{
//	s_instance = forwardDirectional;
//}