#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include "GLShader.h"
#include "../../Renderer/ShaderBank.h"
#include "GLConsts.h"
#include <memory>
#include <iostream>
namespace Lava {
	namespace OpenGL {
		class GLShaderBank :public ShaderBank {
		public:
			virtual ~GLShaderBank();
			virtual int GetVariableLocation(const char* name) const override;
			virtual void Bind() const override;
			virtual void Unbind() const override;
			virtual void Activate() override;
			void AddShader(GLShader* shaderType);
			void LogBoundShaders();
		private:
			void CheckLinking();
		};
	}
}