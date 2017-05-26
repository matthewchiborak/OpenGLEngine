#include "../include/ForwardAmbient.h"

ForwardAmbient* ForwardAmbient::s_instance = 0;

//ForwardAmbient::ForwardAmbient(const std::string& fileName)
ForwardAmbient::ForwardAmbient()
{
	//Create new shader program
	m_program = glCreateProgram();

	//Create the vertex and fragment shaders
	//m_shaders[0] = CreateShader(LoadShader(fileName + ".vs.txt"), GL_VERTEX_SHADER);
	//m_shaders[1] = CreateShader(LoadShader(fileName + ".fs.txt"), GL_FRAGMENT_SHADER);
	m_shaders[0] = CreateShader(LoadShader(".\\res\\ForwardAmbient.vs.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(".\\res\\ForwardAmbient.fs.txt"), GL_FRAGMENT_SHADER);

	//Add shaders to the shader program
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	//Attributes
	glBindAttribLocation(m_program, 0, "position"); //MUST BE SPELLED THE SAME AS IN THE VERTEX
	glBindAttribLocation(m_program, 1, "texCoord");

	//Link
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program failed to link: ");

	//Validation
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid: ");

	//Uniforms
	//Get access to the transform uniform in the shader
	uniforms[ForwardAmbientUniforms::MVP] = glGetUniformLocation(m_program, "MVP");
	uniforms[ForwardAmbientUniforms::AMBIENT_INTENSITY] = glGetUniformLocation(m_program, "ambientIntensity");
}

ForwardAmbient* ForwardAmbient::getForwardAmbient()
{
	if (!s_instance)
	{
		s_instance = new ForwardAmbient();
	}

	return s_instance;
}

ForwardAmbient::~ForwardAmbient()
{
	if (s_instance)
	{
		delete s_instance;
	}
}

void ForwardAmbient::update(const Transform& transform, Camera& camera)
{
	//Get the modelViewProjection
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	//glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	//glUniformMatrix4fv(uniforms[ForwardAmbientUniforms::MVP], 1, GL_FALSE, &transform.GetModel()[0][0]);
	glUniformMatrix4fv(uniforms[ForwardAmbientUniforms::MVP], 1, GL_FALSE, &model[0][0]);
	//Get the ambient light from the rendering engine
	glUniform3fv(uniforms[ForwardAmbientUniforms::AMBIENT_INTENSITY], 1, &RenderingEngine::getRenderingEngine()->getAmbientLight()[0]);
}