#include "../include/Shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
//Loads text file from the harddrive
static std::string LoadShader(const std::string& fileName);

//Create shader from full text
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	//Create new shader program
	m_program = glCreateProgram();

	//Create the vertex and fragment shaders
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs.txt"), GL_FRAGMENT_SHADER);

	//Add shaders to the shader program
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	//Tells opengl what part of data to read as what variable.
	//Need to map variable in the mesh to variable in shader so that it knows about it
	glBindAttribLocation(m_program, 0, "position"); //MUST BE SPELLED THE SAME AS IN THE VERTEX
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	//Link
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program failed to link: ");

	//Validation
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid: ");

	//Get access to the transform uniform in the shader
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[TRANSFORM_PROJECTED] = glGetUniformLocation(m_program, "transformProjected");
	m_uniforms[BASE_COLOR] = glGetUniformLocation(m_program, "baseColor");
	m_uniforms[AMBIENT_LIGHT] = glGetUniformLocation(m_program, "ambientLight");
	m_uniforms[DIRECTIONAL_LIGHT_BASE_COLOR] = glGetUniformLocation(m_program, "directionalLight.base.color");
	m_uniforms[DIRECTIONAL_LIGHT_BASE_INTENSITY] = glGetUniformLocation(m_program, "directionalLight.base.intensity");
	m_uniforms[DIRECTIONAL_LIGHT_DIRECTION] = glGetUniformLocation(m_program, "directionalLight.direction");
}

Shader::~Shader()
{
	//Deleting program doesnt delete the shaders
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		//Not given a shader
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	//Compile the shader
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << "\n";
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'\n";
	}
}

void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::update(const Transform& transform, const Camera& camera)
{
	//Get the modelViewProjection
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	//glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &transform.GetModel()[0][0]);
	glUniformMatrix4fv(m_uniforms[TRANSFORM_PROJECTED], 1, GL_FALSE, &model[0][0]);

	//Update base color and ambient light???
	//glUniformMatrix4fv(m_uniforms[AMBIENT_LIGHT], 1, GL_FALSE, &model[0][0]);
	glUniform3fv(m_uniforms[AMBIENT_LIGHT], 1, &ambientLight[0]);
	glUniform3fv(m_uniforms[BASE_COLOR], 1, &baseColor[0]);
	
	//Directional Light
	glUniform3fv(m_uniforms[DIRECTIONAL_LIGHT_BASE_COLOR], 1, &directionalLight.getBaseLight().getColor()[0]);
	glUniform1f(m_uniforms[DIRECTIONAL_LIGHT_BASE_INTENSITY], directionalLight.getBaseLight().getIntensity());
	glUniform3fv(m_uniforms[DIRECTIONAL_LIGHT_DIRECTION], 1, &directionalLight.getDirection()[0]);
}

void Shader::setAmbientLight(glm::fvec3 light)
{
	ambientLight = light;
}
glm::fvec3 Shader::getAmbientLight()
{
	return ambientLight;
}
void Shader::setBaseColor(glm::fvec3 color)
{
	baseColor = color;
}
glm::fvec3 Shader::getBaseColor()
{
	return baseColor;
}

void Shader::setDirectionalBase(glm::fvec3 color, float intensity)
{
	directionalLight.setBase(color, intensity);
}
void Shader::setDirectionalDirection(glm::fvec3 direction)
{
	directionalLight.setDirection(direction);
}