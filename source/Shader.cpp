#include "../include/Shader.h"


PointLight Shader::pointLights[] = {};

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
	m_uniforms[SPECULAR_INTENSITY] = glGetUniformLocation(m_program, "specularIntensity");
	m_uniforms[SPECULAR_EXPONENT] = glGetUniformLocation(m_program, "specularExponent");
	m_uniforms[EYE_POS] = glGetUniformLocation(m_program, "eyePos");

	/*POINT_LIGHT_POSITION0,
		POINT_LIGHT_BASE_COLOR0,
		POINT_LIGHT_BASE_INTENSITY0,
		POINT_LIGHT_ATTEN_CONSTANT0,
		POINT_LIGHT_ATTEN_LINEAR0,
		POINT_LIGHT_ATTEN_EXPONENT0,*/

	m_uniforms[POINT_LIGHT_POSITION0] = glGetUniformLocation(m_program, "pointLights[0].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY0] = glGetUniformLocation(m_program, "pointLights[0].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR0] = glGetUniformLocation(m_program, "pointLights[0].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT0] = glGetUniformLocation(m_program, "pointLights[0].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR0] = glGetUniformLocation(m_program, "pointLights[0].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT0] = glGetUniformLocation(m_program, "pointLights[0].atten.exponent");

	m_uniforms[POINT_LIGHT_POSITION1] = glGetUniformLocation(m_program, "pointLights[1].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY1] = glGetUniformLocation(m_program, "pointLights[1].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR1] = glGetUniformLocation(m_program, "pointLights[1].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT1] = glGetUniformLocation(m_program, "pointLights[1].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR1] = glGetUniformLocation(m_program, "pointLights[1].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT1] = glGetUniformLocation(m_program, "pointLights[1].atten.exponent");

	m_uniforms[POINT_LIGHT_POSITION2] = glGetUniformLocation(m_program, "pointLights[2].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY2] = glGetUniformLocation(m_program, "pointLights[2].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR2] = glGetUniformLocation(m_program, "pointLights[2].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT2] = glGetUniformLocation(m_program, "pointLights[2].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR2] = glGetUniformLocation(m_program, "pointLights[2].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT2] = glGetUniformLocation(m_program, "pointLights[2].atten.exponent");

	m_uniforms[POINT_LIGHT_POSITION3] = glGetUniformLocation(m_program, "pointLights[3].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY3] = glGetUniformLocation(m_program, "pointLights[3].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR3] = glGetUniformLocation(m_program, "pointLights[3].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT3] = glGetUniformLocation(m_program, "pointLights[3].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR3] = glGetUniformLocation(m_program, "pointLights[3].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT3] = glGetUniformLocation(m_program, "pointLights[3].atten.exponent");

	////Point light stuff
	//char temp[1];
	//std::string result = "";
	//for (int i = 0; i < MAX_POINT_LIGHTS * 5; i += 5)
	//{
	//	result = "";
	//	itoa(i, temp, 1);
	//	result.append("pointLights[");
	//	result.append(temp);
	//	result.append("].base.color");
	//	
	//	const int SIZE = result.size();
	//	
	//	GLchar charResult[SIZE];

	//	m_pointLight_uniforms[i] = glGetUniformLocation(m_program, result);
	//}
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

void Shader::update(const Transform& transform, Camera& camera)
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

	//Specular lighting
	glUniform1f(m_uniforms[SPECULAR_INTENSITY], specularIntensity);
	glUniform1f(m_uniforms[SPECULAR_EXPONENT], specularExponent);
	glUniform3fv(m_uniforms[EYE_POS], 1, &camera.getPosition()[0]);

	//Point lights
	glUniform3fv(m_uniforms[POINT_LIGHT_POSITION0], 1, &pointLights[0].getPosition()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_BASE_INTENSITY0], pointLights[0].getBaseIntensity());
	glUniform3fv(m_uniforms[POINT_LIGHT_BASE_COLOR0], 1, &pointLights[0].getBaseColor()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_CONSTANT0], pointLights[0].getConstant());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_LINEAR0], pointLights[0].getLinear());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_EXPONENT0], pointLights[0].getExponent());

	glUniform3fv(m_uniforms[POINT_LIGHT_POSITION1], 1, &pointLights[1].getPosition()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_BASE_INTENSITY1], pointLights[1].getBaseIntensity());
	glUniform3fv(m_uniforms[POINT_LIGHT_BASE_COLOR1], 1, &pointLights[1].getBaseColor()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_CONSTANT1], pointLights[1].getConstant());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_LINEAR1], pointLights[1].getLinear());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_EXPONENT1], pointLights[1].getExponent());

	glUniform3fv(m_uniforms[POINT_LIGHT_POSITION2], 1, &pointLights[2].getPosition()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_BASE_INTENSITY2], pointLights[2].getBaseIntensity());
	glUniform3fv(m_uniforms[POINT_LIGHT_BASE_COLOR2], 1, &pointLights[2].getBaseColor()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_CONSTANT2], pointLights[2].getConstant());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_LINEAR2], pointLights[2].getLinear());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_EXPONENT2], pointLights[2].getExponent());

	glUniform3fv(m_uniforms[POINT_LIGHT_POSITION3], 1, &pointLights[3].getPosition()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_BASE_INTENSITY3], pointLights[3].getBaseIntensity());
	glUniform3fv(m_uniforms[POINT_LIGHT_BASE_COLOR3], 1, &pointLights[3].getBaseColor()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_CONSTANT3], pointLights[3].getConstant());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_LINEAR3], pointLights[3].getLinear());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_EXPONENT3], pointLights[3].getExponent());
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
void Shader::setSpecularIntensity(float value)
{
	specularIntensity = value;
}
void Shader::setSpecularExponent(float value)
{
	specularExponent = value;
}

void Shader::setPointLight(int index, glm::fvec3 position, glm::fvec3 color, float intensity, float constant, float linear, float exponent)
{
	if (index >= MAX_POINT_LIGHTS)
	{
		std::cerr << "Error: Not a valid point light. Maximum point lights: " << MAX_POINT_LIGHTS << "\n";
		return;
	}

	pointLights[index].setPosition(position);
	pointLights[index].setBaseLight(color, intensity);
	pointLights[index].setAtten(constant, linear, exponent);
}
