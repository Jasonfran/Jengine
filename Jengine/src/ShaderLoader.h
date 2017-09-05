#pragma once
#include <unordered_map>
#include <GL\glew.h>
#include <string>
#include <glm\common.hpp>

struct Path
{
	std::string vertex;
	std::string geometry;
	std::string fragment;
};

struct PathComparator
{
	bool operator()( Path const & a, Path const & b ) const
	{
		return (a.vertex == b.vertex && a.geometry == b.geometry && a.fragment == b.fragment);
	}
};

namespace std
{
	template <>
	struct hash<Path>
	{
		size_t operator()( Path const & x ) const
		{
			return hash<string>()(x.vertex + x.geometry + x.fragment);
		}
	};
}

class ShaderLoader
{
	static std::unordered_map<Path, GLuint, std::hash<Path>, PathComparator> loadedPrograms;
	static void checkCompileErrors( GLuint object, std::string type );
public:
	static GLuint loadShader( std::string vertex, std::string fragment, std::string geometry = "" );
	static void setFloat( GLuint shaderID, const GLchar *name, GLfloat value, GLboolean useShader = false );
	static void setInteger( GLuint shaderID, const GLchar *name, GLint value, GLboolean useShader = false );
	static void setVector2f( GLuint shaderID, const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false );
	static void setVector2f( GLuint shaderID, const GLchar *name, const glm::vec2 &value, GLboolean useShader = false );
	static void setVector3f( GLuint shaderID, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false );
	static void setVector3f( GLuint shaderID, const GLchar *name, const glm::vec3 &value, GLboolean useShader = false );
	static void setVector4f( GLuint shaderID, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false );
	static void setVector4f( GLuint shaderID, const GLchar *name, const glm::vec4 &value, GLboolean useShader = false );
	static void setMatrix4( GLuint shaderID, const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false );
	static void setVP( GLuint shaderID, glm::mat4 view, glm::mat4 projection, GLboolean useShader = false );
};