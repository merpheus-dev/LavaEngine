#pragma once
#include <string>
#include <glm.hpp>
#include "../Utils/TextUtils.h"
#include "../Utils/Debug.h"
#include "ShaderBank.h"
#include "ShaderType.h"
namespace Lava {
	class Shader {
	public:
		virtual void SetBool(const char* name, bool value) = 0;
		virtual void SetFloat1(const char* name, float value) = 0;
		virtual void SetInt1(const char* name, int value) = 0;
		virtual void SetFloat2(const char* name, glm::vec2 value) = 0;
		virtual void SetFloat3(const char* name, glm::vec3 value) = 0;
		virtual void SetFloat4(const char* name, glm::vec4 value) = 0;
		virtual void SetMatrix4x4(const char* name, glm::mat4 value) = 0;
		int m_shaderId = 0;
		int GetShaderName() { return m_shaderType; }
	protected:
		virtual int LoadShader() = 0;
		virtual int GetShaderType() = 0;
		const char* m_shaderDirectory;
		const ShaderBank* m_bank;
		ShaderType m_shaderType;
	};
}