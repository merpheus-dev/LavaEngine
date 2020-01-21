#include "GLShaderBank.h"

Lava::OpenGL::GLShaderBank::~GLShaderBank()
{
	Unbind();
	for (int i = 0; i < m_shaderList.size(); i++) {
		glDetachShader(m_programId, m_shaderList[i]->m_shaderId);
		glDeleteShader(m_shaderList[i]->m_shaderId);
	}
	glDeleteProgram(m_programId);
	m_programId = -1;
}

int Lava::OpenGL::GLShaderBank::GetVariableLocation(const char* name) const
{
	return glGetUniformLocation(m_programId, name);
}

void Lava::OpenGL::GLShaderBank::AddShader(GLShader* shaderType)
{
	m_shaderList.push_back(CreateRef<GLShader>(*shaderType));
}

void Lava::OpenGL::GLShaderBank::LogBoundShaders()
{
	const char* ShaderTypes[]{
		"Vertex",
		"Fragment"
	};
	for (int i = 0; i < m_shaderList.size(); i++) {
		std::cout << ShaderTypes[m_shaderList[i]->GetShaderName()] << std::endl;
	}
}

//To-Do: Include getprogramiv to get length
void Lava::OpenGL::GLShaderBank::CheckLinking()
{
	GLint program_linked;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(m_programId, 1024, &log_length, message);
		std::cout << message << std::endl;
	}
}

void Lava::OpenGL::GLShaderBank::AddVariable(int variableIndex, const char* variableName)
{
	glBindAttribLocation(m_programId, variableIndex, variableName);
}

void Lava::OpenGL::GLShaderBank::Bind() const
{
	if (m_programId == -1)
	{
		Debug::Log("Bank is not activated yet!!");
		return;
	}
	glUseProgram(m_programId);
}

void Lava::OpenGL::GLShaderBank::Unbind() const
{
	glUseProgram(LAVA_BUFFER_CLEAR_ID);
}

void Lava::OpenGL::GLShaderBank::Activate()
{
	m_programId = glCreateProgram();
	for (int i = 0; i < m_shaderList.size(); i++) 
		glAttachShader(m_programId, m_shaderList[i]->m_shaderId);

	glLinkProgram(m_programId);
	glValidateProgram(m_programId);
	CheckLinking();
}
