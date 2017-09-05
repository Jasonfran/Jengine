#include "ShaderLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

std::unordered_map<Path, GLuint, std::hash<Path>, PathComparator> ShaderLoader::loadedPrograms;

GLuint ShaderLoader::loadShader( std::string vertex, std::string fragment, std::string geometry )
{
	Path path = Path{ vertex, geometry, fragment };
	if (loadedPrograms.count( path ))
		return loadedPrograms[Path{ "test", "test", "test" }];

	std::string vertexCode;
	std::string geometryCode;
	std::string fragmentCode;

	std::ifstream vertexInput;
	std::ifstream geomInput;
	std::ifstream fragmentInput;
	vertexInput.exceptions( std::ifstream::badbit );
	geomInput.exceptions( std::ifstream::badbit );
	fragmentInput.exceptions( std::ifstream::badbit );
	try
	{
		vertexInput.open( vertex );
		fragmentInput.open( fragment );
		std::stringstream vertStream, fragStream;
		vertStream << vertexInput.rdbuf();
		fragStream << fragmentInput.rdbuf();
		vertexInput.close();
		fragmentInput.close();
		vertexCode = vertStream.str();
		fragmentCode = fragStream.str();

		if (geometry != "")
		{
			geomInput.open( geometry );
			std::stringstream geomStream;
			geomStream << geomInput.rdbuf();
			geomInput.close();
			geometryCode = geomStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "SHADER ERROR: FAILED TO READ SHADER FILE(S)" << std::endl;
	}
	const GLchar* vertexShaderCode = vertexCode.c_str();
	const GLchar* fragmentShaderCode = fragmentCode.c_str();
	const GLchar* geometryShaderCode = geometry != "" ? geometryCode.c_str() : nullptr;

	GLuint fragShader, vertShader, geomShader;
	vertShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertShader, 1, &vertexShaderCode, NULL );
	glCompileShader( vertShader );
	checkCompileErrors( vertShader, "VERTEX" );

	fragShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragShader, 1, &fragmentShaderCode, NULL );
	glCompileShader( fragShader );
	checkCompileErrors( fragShader, "FRAGMENT" );

	if (geometryShaderCode != nullptr)
	{
		geomShader = glCreateShader( GL_GEOMETRY_SHADER );
		glShaderSource( geomShader, 1, &geometryShaderCode, NULL );
		glCompileShader( geomShader );
		checkCompileErrors( geomShader, "GEOMETRY" );
	}

	GLuint shaderID = glCreateProgram();
	glAttachShader( shaderID, vertShader );
	glAttachShader( shaderID, fragShader );
	if (geometryShaderCode != nullptr)
		glAttachShader( shaderID, geomShader );
	glLinkProgram( shaderID );
	checkCompileErrors( shaderID, "PROGRAM" );
	glDeleteShader( vertShader );
	glDeleteShader( fragShader );
	if (geometryShaderCode != nullptr)
		glDeleteShader( geomShader );
	
	loadedPrograms[path] = shaderID;
	return shaderID;
}

void ShaderLoader::checkCompileErrors( GLuint object, std::string type )
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv( object, GL_COMPILE_STATUS, &success );
		if (!success)
		{
			glGetShaderInfoLog( object, 1024, NULL, infoLog );
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv( object, GL_LINK_STATUS, &success );
		if (!success)
		{
			glGetProgramInfoLog( object, 1024, NULL, infoLog );
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}

void ShaderLoader::setFloat( GLuint shaderID, const GLchar *name, GLfloat value, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniform1f( glGetUniformLocation( shaderID, name ), value );
}
void ShaderLoader::setInteger( GLuint shaderID, const GLchar *name, GLint value, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniform1i( glGetUniformLocation( shaderID, name ), value );
}
void ShaderLoader::setVector2f( GLuint shaderID, const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniform2f( glGetUniformLocation( shaderID, name ), x, y );
}
void ShaderLoader::setVector2f( GLuint shaderID, const GLchar *name, const glm::vec2 &value, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniform2f( glGetUniformLocation( shaderID, name ), value.x, value.y );
}
void ShaderLoader::setVector3f( GLuint shaderID, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniform3f( glGetUniformLocation( shaderID, name ), x, y, z );
}
void ShaderLoader::setVector3f( GLuint shaderID, const GLchar *name, const glm::vec3 &value, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniform3f( glGetUniformLocation( shaderID, name ), value.x, value.y, value.z );
}
void ShaderLoader::setVector4f( GLuint shaderID, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniform4f( glGetUniformLocation( shaderID, name ), x, y, z, w );
}
void ShaderLoader::setVector4f( GLuint shaderID, const GLchar *name, const glm::vec4 &value, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniform4f( glGetUniformLocation( shaderID, name ), value.x, value.y, value.z, value.w );
}
void ShaderLoader::setMatrix4( GLuint shaderID, const GLchar *name, const glm::mat4 &matrix, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	glUniformMatrix4fv( glGetUniformLocation( shaderID, name ), 1, GL_FALSE, glm::value_ptr( matrix ) );
}

void ShaderLoader::setVP( GLuint shaderID, glm::mat4 view, glm::mat4 projection, GLboolean useShader )
{
	if (useShader)
		glUseProgram( shaderID );
	setMatrix4( shaderID, "view", view );
	setMatrix4( shaderID, "projection", projection );
}
