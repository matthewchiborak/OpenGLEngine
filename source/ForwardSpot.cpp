#include "../include/ForwardSpot.h"

ForwardSpot* ForwardSpot::s_instance = 0;

ForwardSpot::ForwardSpot()
{
	//Create new shader program
	m_program = glCreateProgram();

	//Create the vertex and fragment shaders
	m_shaders[0] = CreateShader(LoadShader(".\\res\\ForwardSpot.vs.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(".\\res\\ForwardSpot.fs.txt"), GL_FRAGMENT_SHADER);

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
	uniforms[ForwardSpotUniforms::MVP] = glGetUniformLocation(m_program, "MVP");
	uniforms[ForwardSpotUniforms::MODEL] = glGetUniformLocation(m_program, "model");
	uniforms[ForwardSpotUniforms::SPECULAR_INTENSITY] = glGetUniformLocation(m_program, "specularIntensity");
	uniforms[ForwardSpotUniforms::SPECULAR_EXPONENT] = glGetUniformLocation(m_program, "specularExponent");
	uniforms[ForwardSpotUniforms::EYE_POS] = glGetUniformLocation(m_program, "eyePos");

	uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_POSITION] = glGetUniformLocation(m_program, "spotLight.pointLight.position");
	uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_COLOR] = glGetUniformLocation(m_program, "spotLight.pointLight.base.intensity");
	uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_INTENSITY] = glGetUniformLocation(m_program, "spotLight.pointLight.base.color");
	uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_CONSTANT] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.constant");
	uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_LINEAR] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.linear");
	uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_EXPONENT] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.exponent");
	uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_RANGE] = glGetUniformLocation(m_program, "spotLight.pointLight.range");
	uniforms[ForwardSpotUniforms::SPOT_LIGHT_DIRECTION] = glGetUniformLocation(m_program, "spotLight.direction");
	uniforms[ForwardSpotUniforms::SPOT_LIGHT_CUTOFF] = glGetUniformLocation(m_program, "spotLight.cutoff");
}

ForwardSpot* ForwardSpot::getForwardSpot()
{
	if (!s_instance)
	{
		s_instance = new ForwardSpot();
	}

	return s_instance;
}

ForwardSpot::~ForwardSpot()
{
	if (s_instance)
	{
		delete s_instance;
	}
}

void ForwardSpot::update(const Transform& transform, Camera& camera, Transform parentTransform)
{
	//Get the modelViewProjection
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(uniforms[ForwardSpotUniforms::MODEL], 1, GL_FALSE, &transform.GetModel()[0][0]);
	glUniformMatrix4fv(uniforms[ForwardSpotUniforms::MVP], 1, GL_FALSE, &model[0][0]);
	
	/*glUniform3fv(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_POSITION], 1, &RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getTotalPosition()[0]);*/
	//glUniform3fv(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_POSITION], 1, &RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getPosition()[0]);
	glm::fvec3 newPos = RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getTotalPosition();
	newPos += parentTransform.GetPos();
	glUniform3fv(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_POSITION], 1, &newPos[0]);
	glUniform1f(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_INTENSITY], RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getBaseIntensity());
	glUniform3fv(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_COLOR], 1, &RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getBaseColor()[0]);
	glUniform1f(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_CONSTANT], RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getConstant());
	glUniform1f(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_LINEAR], RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getLinear());
	glUniform1f(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_EXPONENT], RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getExponent());
	glUniform1f(uniforms[ForwardSpotUniforms::SPOT_LIGHT_POINT_RANGE], RenderingEngine::getRenderingEngine()->getSpotLight()->getPointLight().getRange());
	glUniform3fv(uniforms[ForwardSpotUniforms::SPOT_LIGHT_DIRECTION], 1, &RenderingEngine::getRenderingEngine()->getSpotLight()->getDirection()[0]);
	glUniform1f(uniforms[ForwardSpotUniforms::SPOT_LIGHT_CUTOFF], RenderingEngine::getRenderingEngine()->getSpotLight()->getCutoff());

	glUniform1f(uniforms[ForwardSpotUniforms::SPECULAR_INTENSITY], RenderingEngine::getRenderingEngine()->getSpecularIntensity());
	glUniform1f(uniforms[ForwardSpotUniforms::SPECULAR_EXPONENT], RenderingEngine::getRenderingEngine()->getSpecularExponent());
	glUniform3fv(uniforms[ForwardSpotUniforms::EYE_POS], 1, &camera.getPosition()[0]);
}