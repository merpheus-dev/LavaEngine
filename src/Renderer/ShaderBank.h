#pragma once
#include <vector>
#include <memory>
#include "../Utils/MemoryUtils.h"
namespace Lava {
	class Shader;
	class ShaderBank {
	public:
		virtual ~ShaderBank() = default;
		virtual int GetVariableLocation(const char* name) const= 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Activate() = 0;
		virtual void AddVariable(int variableIndex, const char* variableName) = 0;
		std::shared_ptr<Shader> GetShader(int index) { return m_shaderList[index]; }
	protected:
		int m_programId = -1;
		std::vector<std::shared_ptr<Shader>> m_shaderList;
	};
}