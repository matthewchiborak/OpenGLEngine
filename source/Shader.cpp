#include "../include/Shader.h"


PointLight Shader::pointLights[] = {};
SpotLight Shader::spotLights[] = {};
//
//static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
////Loads text file from the harddrive
//static std::string LoadShader(const std::string& fileName);
//
////Create shader from full text
//static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader()
{

}

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

	//POINT LIGHTS
	m_uniforms[POINT_LIGHT_POSITION0] = glGetUniformLocation(m_program, "pointLights[0].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY0] = glGetUniformLocation(m_program, "pointLights[0].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR0] = glGetUniformLocation(m_program, "pointLights[0].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT0] = glGetUniformLocation(m_program, "pointLights[0].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR0] = glGetUniformLocation(m_program, "pointLights[0].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT0] = glGetUniformLocation(m_program, "pointLights[0].atten.exponent");
	m_uniforms[POINT_LIGHT_RANGE0] = glGetUniformLocation(m_program, "pointLights[0].range");

	m_uniforms[POINT_LIGHT_POSITION1] = glGetUniformLocation(m_program, "pointLights[1].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY1] = glGetUniformLocation(m_program, "pointLights[1].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR1] = glGetUniformLocation(m_program, "pointLights[1].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT1] = glGetUniformLocation(m_program, "pointLights[1].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR1] = glGetUniformLocation(m_program, "pointLights[1].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT1] = glGetUniformLocation(m_program, "pointLights[1].atten.exponent");
	m_uniforms[POINT_LIGHT_RANGE1] = glGetUniformLocation(m_program, "pointLights[1].range");

	m_uniforms[POINT_LIGHT_POSITION2] = glGetUniformLocation(m_program, "pointLights[2].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY2] = glGetUniformLocation(m_program, "pointLights[2].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR2] = glGetUniformLocation(m_program, "pointLights[2].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT2] = glGetUniformLocation(m_program, "pointLights[2].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR2] = glGetUniformLocation(m_program, "pointLights[2].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT2] = glGetUniformLocation(m_program, "pointLights[2].atten.exponent");
	m_uniforms[POINT_LIGHT_RANGE2] = glGetUniformLocation(m_program, "pointLights[2].range");

	m_uniforms[POINT_LIGHT_POSITION3] = glGetUniformLocation(m_program, "pointLights[3].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY3] = glGetUniformLocation(m_program, "pointLights[3].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR3] = glGetUniformLocation(m_program, "pointLights[3].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT3] = glGetUniformLocation(m_program, "pointLights[3].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR3] = glGetUniformLocation(m_program, "pointLights[3].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT3] = glGetUniformLocation(m_program, "pointLights[3].atten.exponent");
	m_uniforms[POINT_LIGHT_RANGE3] = glGetUniformLocation(m_program, "pointLights[3].range");

	//SPOT LIGHTS
	m_uniforms[SPOT_LIGHT_POINT_POSITION_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.position");
	m_uniforms[SPOT_LIGHT_POINT_COLOR_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.base.intensity");
	m_uniforms[SPOT_LIGHT_POINT_INTENSITY_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.base.color");
	m_uniforms[SPOT_LIGHT_POINT_CONSTANT_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.constant");
	m_uniforms[SPOT_LIGHT_POINT_LINEAR_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.linear");
	m_uniforms[SPOT_LIGHT_POINT_EXPONENT_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.exponent");
	m_uniforms[SPOT_LIGHT_POINT_RANGE_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.range");
	m_uniforms[SPOT_LIGHT_DIRECTION_0] = glGetUniformLocation(m_program, "spotLights[0].direction");
	m_uniforms[SPOT_LIGHT_CUTOFF_0] = glGetUniformLocation(m_program, "spotLights[0].cutoff");

	m_uniforms[SPOT_LIGHT_POINT_POSITION_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.position");
	m_uniforms[SPOT_LIGHT_POINT_COLOR_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.base.intensity");
	m_uniforms[SPOT_LIGHT_POINT_INTENSITY_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.base.color");
	m_uniforms[SPOT_LIGHT_POINT_CONSTANT_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.constant");
	m_uniforms[SPOT_LIGHT_POINT_LINEAR_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.linear");
	m_uniforms[SPOT_LIGHT_POINT_EXPONENT_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.exponent");
	m_uniforms[SPOT_LIGHT_POINT_RANGE_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.range");
	m_uniforms[SPOT_LIGHT_DIRECTION_1] = glGetUniformLocation(m_program, "spotLights[1].direction");
	m_uniforms[SPOT_LIGHT_CUTOFF_1] = glGetUniformLocation(m_program, "spotLights[1].cutoff");

	m_uniforms[SPOT_LIGHT_POINT_POSITION_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.position");
	m_uniforms[SPOT_LIGHT_POINT_COLOR_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.base.intensity");
	m_uniforms[SPOT_LIGHT_POINT_INTENSITY_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.base.color");
	m_uniforms[SPOT_LIGHT_POINT_CONSTANT_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.atten.constant");
	m_uniforms[SPOT_LIGHT_POINT_LINEAR_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.atten.linear");
	m_uniforms[SPOT_LIGHT_POINT_EXPONENT_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.atten.exponent");
	m_uniforms[SPOT_LIGHT_POINT_RANGE_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.range");
	m_uniforms[SPOT_LIGHT_DIRECTION_2] = glGetUniformLocation(m_program, "spotLights[2].direction");
	m_uniforms[SPOT_LIGHT_CUTOFF_2] = glGetUniformLocation(m_program, "spotLights[2].cutoff");

	m_uniforms[SPOT_LIGHT_POINT_POSITION_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.position");
	m_uniforms[SPOT_LIGHT_POINT_COLOR_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.base.intensity");
	m_uniforms[SPOT_LIGHT_POINT_INTENSITY_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.base.color");
	m_uniforms[SPOT_LIGHT_POINT_CONSTANT_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.atten.constant");
	m_uniforms[SPOT_LIGHT_POINT_LINEAR_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.atten.linear");
	m_uniforms[SPOT_LIGHT_POINT_EXPONENT_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.atten.exponent");
	m_uniforms[SPOT_LIGHT_POINT_RANGE_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.range");
	m_uniforms[SPOT_LIGHT_DIRECTION_3] = glGetUniformLocation(m_program, "spotLights[3].direction");
	m_uniforms[SPOT_LIGHT_CUTOFF_3] = glGetUniformLocation(m_program, "spotLights[3].cutoff");

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

Shader::Shader(const std::string& name, const std::string& fileName)
{
	this->name = name;

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
	//Atributes
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

	//POINT LIGHTS
	m_uniforms[POINT_LIGHT_POSITION0] = glGetUniformLocation(m_program, "pointLights[0].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY0] = glGetUniformLocation(m_program, "pointLights[0].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR0] = glGetUniformLocation(m_program, "pointLights[0].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT0] = glGetUniformLocation(m_program, "pointLights[0].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR0] = glGetUniformLocation(m_program, "pointLights[0].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT0] = glGetUniformLocation(m_program, "pointLights[0].atten.exponent");
	m_uniforms[POINT_LIGHT_RANGE0] = glGetUniformLocation(m_program, "pointLights[0].range");

	m_uniforms[POINT_LIGHT_POSITION1] = glGetUniformLocation(m_program, "pointLights[1].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY1] = glGetUniformLocation(m_program, "pointLights[1].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR1] = glGetUniformLocation(m_program, "pointLights[1].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT1] = glGetUniformLocation(m_program, "pointLights[1].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR1] = glGetUniformLocation(m_program, "pointLights[1].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT1] = glGetUniformLocation(m_program, "pointLights[1].atten.exponent");
	m_uniforms[POINT_LIGHT_RANGE1] = glGetUniformLocation(m_program, "pointLights[1].range");

	m_uniforms[POINT_LIGHT_POSITION2] = glGetUniformLocation(m_program, "pointLights[2].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY2] = glGetUniformLocation(m_program, "pointLights[2].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR2] = glGetUniformLocation(m_program, "pointLights[2].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT2] = glGetUniformLocation(m_program, "pointLights[2].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR2] = glGetUniformLocation(m_program, "pointLights[2].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT2] = glGetUniformLocation(m_program, "pointLights[2].atten.exponent");
	m_uniforms[POINT_LIGHT_RANGE2] = glGetUniformLocation(m_program, "pointLights[2].range");

	m_uniforms[POINT_LIGHT_POSITION3] = glGetUniformLocation(m_program, "pointLights[3].position");
	m_uniforms[POINT_LIGHT_BASE_INTENSITY3] = glGetUniformLocation(m_program, "pointLights[3].base.intensity");
	m_uniforms[POINT_LIGHT_BASE_COLOR3] = glGetUniformLocation(m_program, "pointLights[3].base.color");
	m_uniforms[POINT_LIGHT_ATTEN_CONSTANT3] = glGetUniformLocation(m_program, "pointLights[3].atten.constant");
	m_uniforms[POINT_LIGHT_ATTEN_LINEAR3] = glGetUniformLocation(m_program, "pointLights[3].atten.linear");
	m_uniforms[POINT_LIGHT_ATTEN_EXPONENT3] = glGetUniformLocation(m_program, "pointLights[3].atten.exponent");
	m_uniforms[POINT_LIGHT_RANGE3] = glGetUniformLocation(m_program, "pointLights[3].range");

	//SPOT LIGHTS
	m_uniforms[SPOT_LIGHT_POINT_POSITION_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.position");
	m_uniforms[SPOT_LIGHT_POINT_COLOR_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.base.intensity");
	m_uniforms[SPOT_LIGHT_POINT_INTENSITY_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.base.color");
	m_uniforms[SPOT_LIGHT_POINT_CONSTANT_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.constant");
	m_uniforms[SPOT_LIGHT_POINT_LINEAR_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.linear");
	m_uniforms[SPOT_LIGHT_POINT_EXPONENT_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.exponent");
	m_uniforms[SPOT_LIGHT_POINT_RANGE_0] = glGetUniformLocation(m_program, "spotLights[0].pointLight.range");
	m_uniforms[SPOT_LIGHT_DIRECTION_0] = glGetUniformLocation(m_program, "spotLights[0].direction");
	m_uniforms[SPOT_LIGHT_CUTOFF_0] = glGetUniformLocation(m_program, "spotLights[0].cutoff");

	m_uniforms[SPOT_LIGHT_POINT_POSITION_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.position");
	m_uniforms[SPOT_LIGHT_POINT_COLOR_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.base.intensity");
	m_uniforms[SPOT_LIGHT_POINT_INTENSITY_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.base.color");
	m_uniforms[SPOT_LIGHT_POINT_CONSTANT_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.constant");
	m_uniforms[SPOT_LIGHT_POINT_LINEAR_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.linear");
	m_uniforms[SPOT_LIGHT_POINT_EXPONENT_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.exponent");
	m_uniforms[SPOT_LIGHT_POINT_RANGE_1] = glGetUniformLocation(m_program, "spotLights[1].pointLight.range");
	m_uniforms[SPOT_LIGHT_DIRECTION_1] = glGetUniformLocation(m_program, "spotLights[1].direction");
	m_uniforms[SPOT_LIGHT_CUTOFF_1] = glGetUniformLocation(m_program, "spotLights[1].cutoff");

	m_uniforms[SPOT_LIGHT_POINT_POSITION_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.position");
	m_uniforms[SPOT_LIGHT_POINT_COLOR_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.base.intensity");
	m_uniforms[SPOT_LIGHT_POINT_INTENSITY_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.base.color");
	m_uniforms[SPOT_LIGHT_POINT_CONSTANT_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.atten.constant");
	m_uniforms[SPOT_LIGHT_POINT_LINEAR_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.atten.linear");
	m_uniforms[SPOT_LIGHT_POINT_EXPONENT_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.atten.exponent");
	m_uniforms[SPOT_LIGHT_POINT_RANGE_2] = glGetUniformLocation(m_program, "spotLights[2].pointLight.range");
	m_uniforms[SPOT_LIGHT_DIRECTION_2] = glGetUniformLocation(m_program, "spotLights[2].direction");
	m_uniforms[SPOT_LIGHT_CUTOFF_2] = glGetUniformLocation(m_program, "spotLights[2].cutoff");

	m_uniforms[SPOT_LIGHT_POINT_POSITION_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.position");
	m_uniforms[SPOT_LIGHT_POINT_COLOR_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.base.intensity");
	m_uniforms[SPOT_LIGHT_POINT_INTENSITY_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.base.color");
	m_uniforms[SPOT_LIGHT_POINT_CONSTANT_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.atten.constant");
	m_uniforms[SPOT_LIGHT_POINT_LINEAR_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.atten.linear");
	m_uniforms[SPOT_LIGHT_POINT_EXPONENT_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.atten.exponent");
	m_uniforms[SPOT_LIGHT_POINT_RANGE_3] = glGetUniformLocation(m_program, "spotLights[3].pointLight.range");
	m_uniforms[SPOT_LIGHT_DIRECTION_3] = glGetUniformLocation(m_program, "spotLights[3].direction");
	m_uniforms[SPOT_LIGHT_CUTOFF_3] = glGetUniformLocation(m_program, "spotLights[3].cutoff");

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

std::string Shader::getName()
{
	return name;
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
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

std::string Shader::LoadShader(const std::string& fileName)
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

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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

void Shader::update(const Transform& transform, Camera& camera, Transform parentTransform)
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
	glUniform1f(m_uniforms[POINT_LIGHT_RANGE0], pointLights[0].getRange());

	glUniform3fv(m_uniforms[POINT_LIGHT_POSITION1], 1, &pointLights[1].getPosition()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_BASE_INTENSITY1], pointLights[1].getBaseIntensity());
	glUniform3fv(m_uniforms[POINT_LIGHT_BASE_COLOR1], 1, &pointLights[1].getBaseColor()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_CONSTANT1], pointLights[1].getConstant());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_LINEAR1], pointLights[1].getLinear());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_EXPONENT1], pointLights[1].getExponent());
	glUniform1f(m_uniforms[POINT_LIGHT_RANGE1], pointLights[1].getRange());

	glUniform3fv(m_uniforms[POINT_LIGHT_POSITION2], 1, &pointLights[2].getPosition()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_BASE_INTENSITY2], pointLights[2].getBaseIntensity());
	glUniform3fv(m_uniforms[POINT_LIGHT_BASE_COLOR2], 1, &pointLights[2].getBaseColor()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_CONSTANT2], pointLights[2].getConstant());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_LINEAR2], pointLights[2].getLinear());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_EXPONENT2], pointLights[2].getExponent());
	glUniform1f(m_uniforms[POINT_LIGHT_RANGE2], pointLights[2].getRange());

	glUniform3fv(m_uniforms[POINT_LIGHT_POSITION3], 1, &pointLights[3].getPosition()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_BASE_INTENSITY3], pointLights[3].getBaseIntensity());
	glUniform3fv(m_uniforms[POINT_LIGHT_BASE_COLOR3], 1, &pointLights[3].getBaseColor()[0]);
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_CONSTANT3], pointLights[3].getConstant());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_LINEAR3], pointLights[3].getLinear());
	glUniform1f(m_uniforms[POINT_LIGHT_ATTEN_EXPONENT3], pointLights[3].getExponent());
	glUniform1f(m_uniforms[POINT_LIGHT_RANGE3], pointLights[3].getRange());

	//SPOT LIGHTS
	glUniform3fv(m_uniforms[SPOT_LIGHT_POINT_POSITION_0], 1, &spotLights[0].getPointLight().getPosition()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_INTENSITY_0], spotLights[0].getPointLight().getBaseIntensity());
	glUniform3fv(m_uniforms[SPOT_LIGHT_POINT_COLOR_0], 1, &spotLights[0].getPointLight().getBaseColor()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_CONSTANT_0], spotLights[0].getPointLight().getConstant());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_LINEAR_0], spotLights[0].getPointLight().getLinear());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_EXPONENT_0], spotLights[0].getPointLight().getExponent());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_RANGE_0], spotLights[0].getPointLight().getRange());
	glUniform3fv(m_uniforms[SPOT_LIGHT_DIRECTION_0], 1, &spotLights[0].getDirection()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_CUTOFF_0], spotLights[0].getCutoff());

	glUniform3fv(m_uniforms[SPOT_LIGHT_POINT_POSITION_1], 1, &spotLights[1].getPointLight().getPosition()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_INTENSITY_1], spotLights[1].getPointLight().getBaseIntensity());
	glUniform3fv(m_uniforms[SPOT_LIGHT_POINT_COLOR_1], 1, &spotLights[1].getPointLight().getBaseColor()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_CONSTANT_1], spotLights[1].getPointLight().getConstant());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_LINEAR_1], spotLights[1].getPointLight().getLinear());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_EXPONENT_1], spotLights[1].getPointLight().getExponent());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_RANGE_1], spotLights[1].getPointLight().getRange());
	glUniform3fv(m_uniforms[SPOT_LIGHT_DIRECTION_1], 1, &spotLights[1].getDirection()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_CUTOFF_1], spotLights[1].getCutoff());

	glUniform3fv(m_uniforms[SPOT_LIGHT_POINT_POSITION_2], 1, &spotLights[2].getPointLight().getPosition()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_INTENSITY_2], spotLights[2].getPointLight().getBaseIntensity());
	glUniform3fv(m_uniforms[SPOT_LIGHT_POINT_COLOR_2], 1, &spotLights[2].getPointLight().getBaseColor()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_CONSTANT_2], spotLights[2].getPointLight().getConstant());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_LINEAR_2], spotLights[2].getPointLight().getLinear());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_EXPONENT_2], spotLights[2].getPointLight().getExponent());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_RANGE_2], spotLights[2].getPointLight().getRange());
	glUniform3fv(m_uniforms[SPOT_LIGHT_DIRECTION_2], 1, &spotLights[2].getDirection()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_CUTOFF_2], spotLights[2].getCutoff());

	glUniform3fv(m_uniforms[SPOT_LIGHT_POINT_POSITION_3], 1, &spotLights[3].getPointLight().getPosition()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_INTENSITY_3], spotLights[3].getPointLight().getBaseIntensity());
	glUniform3fv(m_uniforms[SPOT_LIGHT_POINT_COLOR_3], 1, &spotLights[3].getPointLight().getBaseColor()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_CONSTANT_3], spotLights[3].getPointLight().getConstant());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_LINEAR_3], spotLights[3].getPointLight().getLinear());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_EXPONENT_3], spotLights[3].getPointLight().getExponent());
	glUniform1f(m_uniforms[SPOT_LIGHT_POINT_RANGE_3], spotLights[3].getPointLight().getRange());
	glUniform3fv(m_uniforms[SPOT_LIGHT_DIRECTION_3], 1, &spotLights[3].getDirection()[0]);
	glUniform1f(m_uniforms[SPOT_LIGHT_CUTOFF_3], spotLights[3].getCutoff());

	/*SPOT_LIGHT_POINT_POSITION_0,
	SPOT_LIGHT_POINT_COLOR_0,
	SPOT_LIGHT_POINT_INTENSITY_0,
	SPOT_LIGHT_POINT_CONSTANT_0,
	SPOT_LIGHT_POINT_LINEAR_0,
	SPOT_LIGHT_POINT_EXPONENT_0,
	SPOT_LIGHT_POINT_RANGE_0,
	SPOT_LIGHT_DIRECTION_0,
	SPOT_LIGHT_CUTOFF_0,*/
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

void Shader::setPointLight(int index, glm::fvec3 position, glm::fvec3 color, float intensity, float range, float constant, float linear, float exponent)
{
	if (index >= MAX_POINT_LIGHTS)
	{
		std::cerr << "Error: Not a valid point light. Maximum point lights: " << MAX_POINT_LIGHTS << "\n";
		return;
	}

	pointLights[index].setPosition(position);
	pointLights[index].setBaseLight(color, intensity);
	pointLights[index].setAtten(constant, linear, exponent);
	//pointLights[index].setRange(range);
}

void Shader::setSpotLight(int index, glm::fvec3 position, glm::fvec3 color, float intensity, float range, float constant, float linear, float exponent, glm::fvec3 direction, float cutoff)
{
	if (index >= MAX_SPOT_LIGHTS)
	{
		std::cerr << "Error: Not a valid point light. Maximum spot lights: " << MAX_SPOT_LIGHTS << "\n";
		return;
	}

	/*pointLights[index].setPosition(position);
	pointLights[index].setBaseLight(color, intensity);
	pointLights[index].setAtten(constant, linear, exponent);
	pointLights[index].setRange(range);*/
	spotLights[index].setPointLight(position, range, color, intensity, constant, linear, exponent);
	spotLights[index].setDirection(direction);
	spotLights[index].setCutoff(cutoff);
}

void Shader::addAllUniforms(std::string shaderText)
{

}