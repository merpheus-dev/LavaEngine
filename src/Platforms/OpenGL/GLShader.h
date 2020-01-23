#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include "../../Renderer/Shader.h"
namespace Lava {
	namespace OpenGL {
		class GLShaderBank;
		class GLShader :public Shader {
		public:
			GLShader(const char* shaderDirectory,ShaderType shaderType, GLShaderBank* bank);
			virtual void SetBool(const char* name, bool value) override;
			virtual void SetFloat1(const char* name, float value) override;
			virtual void SetFloat2(const char* name, glm::vec2 value) override;
			virtual void SetFloat3(const char* name, glm::vec3 value) override;
			virtual void SetFloat4(const char* name, glm::vec4 value) override;
			virtual void SetMatrix4x4(const char* name, glm::mat4 value) override;
		private:
			virtual int LoadShader() override;
			virtual int GetShaderType() override;
		};
	}
}