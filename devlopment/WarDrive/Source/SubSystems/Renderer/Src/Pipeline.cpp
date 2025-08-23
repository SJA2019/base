#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "SDL.h"
#include "Pipeline.h"

using namespace glm;


// Shader sources
const GLchar *vertexSource =
    "#version 330 core\nlayout(location = 0) in vec3 vertexPosition_modelspace;layout(location = 1) in vec3 vertexColor;out vec3 fragmentColor;uniform mat4 MVP;void main(){gl_Position =  MVP * vec4(vertexPosition_modelspace,1);fragmentColor = vertexColor;}";

const GLchar *fragmentSource =
    "#version 330 core\nin vec3 fragmentColor;out vec3 color;void main(){color = fragmentColor;}";

GLuint Pipeline::CreateProgramFromShaderText(const GLchar *vertexShaderAsString, const GLchar *fragmentShaderAsString) {
    GLuint programID;

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderAsString, NULL);
    glCompileShader(vertexShader);

    GLsizei logSize;
    glGetShaderInfoLog(vertexShader, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';

    std::cout<<"vertexShader status:"<<shaderInfoLog;

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderAsString, NULL);
    glCompileShader(fragmentShader);

    glGetShaderInfoLog(fragmentShader, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';
    std::cout<<"fragmentShader status:"<<shaderInfoLog;

    // Link the vertex and fragment shader into a shader program
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);


    glGetProgramInfoLog(programID, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';
    std::cout<<"programStatus status:"<<shaderInfoLog;

    return programID;
}

GLuint Pipeline::CreateProgramFromShaderFiles(const char *vertexShaderFileName, const char *fragmentShaderFileName) {
    GLuint programID;

    // Create and compile our GLSL program from the shaders
    GLsizei logSize;
	programID = LoadShaders( vertexShaderFileName, fragmentShaderFileName );
    glGetProgramInfoLog(programID, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';
    std::cout<<"programStatus status:"<<shaderInfoLog;

    return programID;
}


GLuint Pipeline::LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		//getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program..\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	printf("Linking program - done\n");

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

Pipeline::Pipeline(char* vertexShaderFileName, char* fragmentShaderFileName){
	printf("Pipeline()");
	m_programID = 0;
	MVP = glm::mat4();

	#define PROGRAM_FROM_STRING 0
#if PROGRAM_FROM_STRING
    m_programID = CreateProgramFromShaderText(vertexSource, fragmentSource);
#else
	if(vertexShaderFileName == nullptr) {
		vertexShaderFileName = "TransformVertexShader.vertexshader";
	}
	if(fragmentShaderFileName == nullptr) {
		fragmentShaderFileName = "ColorFragmentShader.fragmentshader";
	}
    m_programID = CreateProgramFromShaderFiles(vertexShaderFileName, fragmentShaderFileName);
#endif

	// Get a handle for our "MVP" uniform
    //MatrixID = glGetUniformLocation(programID, "MVP");
	MatrixID = glGetUniformLocation(m_programID, "MVP");
}

GLuint Pipeline::GetProgramId() {
	return m_programID;
}

GLuint Pipeline::updateMVPMatrix(glm::mat4 MVPIn) {
	MVP = MVPIn;
}

void Pipeline::submitMVPMatrix() {
	glUseProgram(m_programID);
	// Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}