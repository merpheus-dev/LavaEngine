#include "GLShader.h"
#include <vector>
#include <iostream>
namespace Lava
{
	namespace OpenGL
	{
		GLShader::GLShader(const char* shaderDirectory, ShaderType shaderType,GLShaderBank* bank)
		{
			m_shaderDirectory = shaderDirectory;
			m_shaderType = shaderType;
			m_bank = (ShaderBank*)bank;
			LoadShader();
		}

		int GLShader::LoadShader()
		{
			std::string readString = TextUtils::ReadText(m_shaderDirectory);
			m_shaderId = glCreateShader(GetShaderType());
			const GLchar* shaderSource = readString.c_str();
			const int shaderSourceLength = readString.size();
			glShaderSource(m_shaderId, 1, &shaderSource, &shaderSourceLength);
			glCompileShader(m_shaderId);

			int compile_result;
			glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compile_result);
			if (compile_result != GL_TRUE) {
				int maxLogLength = 0;
				glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &maxLogLength);
				std::vector<GLchar> logInfo(maxLogLength);
				glGetShaderInfoLog(m_shaderId, maxLogLength, &maxLogLength, &logInfo[0]);
				Debug::LogError(&logInfo[0]);
			}

			return m_shaderId;
		}

		int GLShader::GetShaderType()
		{
			switch (m_shaderType) {
			case ShaderType::Vertex:
				return GL_VERTEX_SHADER;
			case ShaderType::Fragment:
				return GL_FRAGMENT_SHADER;
			case ShaderType::Geometry:
				return GL_GEOMETRY_SHADER;
			case ShaderType::TessEval:
				return GL_TESS_EVALUATION_SHADER;
			case ShaderType::TessControl:
				return GL_TESS_CONTROL_SHADER;
			case ShaderType::Compute:
				return GL_COMPUTE_SHADER;
			default:
				return 0;
			}
		}

		void GLShader::SetBool(const char* name, bool value)
		{
			glUniform1i(m_bank->GetVariableLocation(name), value ? 1 : 0);
		}

		void GLShader::SetFloat1(const char* name, float value)
		{
			glUniform1f(m_bank->GetVariableLocation(name), value);
		}

		void GLShader::SetInt1(const char* name, int value)
		{
			glUniform1i(m_bank->GetVariableLocation(name), value);
		}

		void GLShader::SetFloat2(const char* name, glm::vec2 value)
		{
			glUniform2f(m_bank->GetVariableLocation(name), value.x, value.y);
		}

		void GLShader::SetFloat3(const char* name, glm::vec3 value)
		{
			glUniform3f(m_bank->GetVariableLocation(name), value.x, value.y, value.z);
		}

		void GLShader::SetFloat4(const char* name, glm::vec4 value)
		{
			glUniform4f(m_bank->GetVariableLocation(name), value.x, value.y, value.z, value.w);
		}
		void GLShader::SetMatrix4x4(const char* name, glm::mat4 value)
		{
			glUniformMatrix4fv(m_bank->GetVariableLocation(name), 1, GL_FALSE, &value[0][0]);
		}
	}
}