#include "SDL.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "WarDrive.h"



//Notes:
//opengl/SDL includes : https://stackoverflow.com/questions/22118518/use-of-undeclared-identifier-glgenvertexarrays-error-even-after-including-open
//on the fly shaders: https://gist.github.com/SuperV1234/5c5ad838fe5fe1bf54f9
//cube sample: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/ / https://github.com/opengl-tutorials/ogl/blob/master/tutorial04_colored_cube/tutorial04.cpp

// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f, // triangle 1 : begin
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    
    1.0f, 1.0f, -1.0f, // triangle 2 : begin
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f, // triangle 2 : end
    
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f  
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.0f, 0.0f, 0.0f, // triangle 1 : begin
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, // triangle 1 : end
    
    1.0f, 1.0f, 0.0f, // triangle 2 : begin
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, // triangle 2 : end
    
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f
};

// Shader sources
const GLchar *vertexSource =
    "#version 330 core\nlayout(location = 0) in vec3 vertexPosition_modelspace;layout(location = 1) in vec3 vertexColor;out vec3 fragmentColor;uniform mat4 MVP;void main(){gl_Position =  MVP * vec4(vertexPosition_modelspace,1);fragmentColor = vertexColor;}";

const GLchar *fragmentSource =
    "#version 330 core\nin vec3 fragmentColor;out vec3 color;void main(){color = fragmentColor;}";

SDL_Window *window = NULL;


GLuint MatrixID;
GLuint vertexbuffer;
GLuint colorbuffer;

glm::mat4 Model;

float camX = 4.0f;
float camY = 3.0f;
float camZ = 3.0f;
float camTX = 0.0f;
float camTY = 0.0f;
float camTZ = 0.0f;
glm::mat4 View;
glm::mat4 Projection;
glm::mat4 MVP;

//glGetShaderInfoLog
char shaderInfoLog[256];

WarDrive::WarDrive()
{
    std::cout << "WarDrive() ++" << std::endl;
    InputDeviceSelection::DeviceSet inputDeviceSet;
    inputDeviceSet |= InputDeviceSelection::joyInputDevice;
    inputDeviceSet |= InputDeviceSelection::mouseInputDevice;
    inputDeviceSet |= InputDeviceSelection::keyboardDevice;
    shared_ptr<InputManager> t_sptrInputManager(new InputManager(inputDeviceSet));
    m_sptrInputManager = t_sptrInputManager;

    //SDL_Surface* screenSurface = NULL;
    window = SDL_CreateWindow("SampleRendering..",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return;
    }
#if 0
        screenSurface = SDL_GetWindowSurface(window);

        if (!screenSurface) {
            fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
            SDL_Quit();
            return;
        }
#endif
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

    SDL_GLContext context = SDL_GL_CreateContext(window);

    //Cube sample.

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

#define PROGRAM_FROM_STRING 0
#if PROGRAM_FROM_STRING
    programID = CreateProgramFromShaderText(vertexSource, fragmentSource);
#else
    programID = CreateProgramFromShaderFiles("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
#endif

    glUseProgram(programID);

    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(programID, "MVP");

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    View = glm::lookAt(
        glm::vec3(camX, camY, camZ), // Camera is at (4,3,-3), in World Space
        glm::vec3(camTX, camTY, camTZ),  // and looks at the origin
        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    //glClearColor(1, 0, 0, 1);
    //glClear(GL_COLOR_BUFFER_BIT);
    //SDL_GL_SwapWindow(window);
    /* Enable Unicode translation */
    //SDL_EnableUNICODE( 1 );

    std::cout << "WarDrive() --" << std::endl;
}

WarDrive::~WarDrive()
{
    std::cout << "~WarDrive() ++" << std::endl;
    m_sptrInputManager = nullptr;
    std::cout << "~WarDrive() --" << std::endl;
}

void WarDrive::Run()
{
    IMEvent inputEvent = {eIMEventNotAvailable, SDL_EventType()};
    while (true)
    {
        inputEvent = m_sptrInputManager->PollJoyEvents();
        if (EIMJoyEventType::eIMEventBailOut == inputEvent.eventType)
        {
            break;
        }
        else if (EIMJoyEventType::eIMEventAvailable == inputEvent.eventType)
        {
            float objRotX = 0.0f;
            float objRotY = 0.0f;
            float objRotZ = 0.0f;

            float objXOffset = 0.0f;
            float objYOffset = 0.0f;
            float objZOffset = 0.0f;


            float camXOffset = 0.0f;
            float camYOffset = 0.0f;
            float camZOffset = 0.0f;
            
            switch(inputEvent.sdlEvent.key.keysym.sym) {
                //Rotate object 'x','y','z'
                //
                case 'x':
                    objRotX = 1.0f;
                break;
                case 'y':
                    objRotY = 1.0f;
                break;
                case 'z':
                    objRotZ = 1.0f;
                break;
                case SDLK_SPACE:
                    objRotX = 1.0f;
                    objRotY = 1.0f;
                    objRotZ = 1.0f;
                break;
                //Move Object up/down/left/right
                //
                case SDLK_1:
                    objYOffset++;
                break;
                case SDLK_2:
                    objYOffset--;
                break;
                case SDLK_3:
                    objXOffset++;
                break;
                case SDLK_4:
                    objXOffset--;
                break;
                case SDLK_5:
                    objZOffset++;
                break;
                case SDLK_6:
                    objZOffset--;
                break;
                
                //Move Camera up/down/left/right
                //
                case SDLK_UP:
                    camYOffset++;
                break;
                case SDLK_DOWN:
                    camYOffset--;
                break;
                case SDLK_RIGHT:
                    camXOffset++;
                break;
                case SDLK_LEFT:
                    camXOffset--;
                break;
                //Move Camera forward/back
                //
                case '.':
                    camZOffset++;
                break;
                case ',':
                    camZOffset--;
                break;
                //Focus Camera on object
                case '/':
                    camTX = camTY = camTZ = 0;
                break;
                default:
                //noop.
                break;
            }

            //Edit Camera Coordinaties(View)
            //
            if( (!((camXOffset==0) && (camYOffset==0) && (camZOffset==0))) ||
                  ((camTX==0) && (camTY==0) && (camTZ==0)) ) {

                camX+= camXOffset;
                camY+= camYOffset;
                camZ+= camZOffset;

                camTX+= camXOffset;
                camTY+= camYOffset;
                camTZ+= camZOffset;

                std::cout<<"cam-pos="<<camX<<","<<camY<<","<<camZ<<" cam-target="<<camTX<<","<<camTY<<","<<camTZ;
                View = glm::lookAt(
                        glm::vec3(camX, camY, camZ), // Camera is at (4,3,-3), in World Space
                        glm::vec3(camTX, camTY, camTZ),  // and looks at the origin
                        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
                        );
                MVP = Projection * View * Model;
            }            

            //Edit Object coordinates (Model)
            //
            if((objRotX!=0) || (objRotY!=0) || (objRotZ!=0)) {
                std::cout<<"obj-rotation-axis="<<objRotX<<","<<objRotY<<","<<objRotZ;
                glm::vec3 myRotationAxis( objRotX, objRotY, objRotZ);
                float angle = 0.01f;
                Model = glm::rotate(Model, angle, myRotationAxis );
                MVP = Projection * View * Model;
            }

            if((objXOffset!=0) || (objYOffset!=0) || (objZOffset!=0)) {
                std::cout<<"obj-position-offsets="<<objXOffset<<","<<objYOffset<<","<<objZOffset;
                glm::vec3 offsetPosition( objXOffset, objYOffset, objZOffset);
                Model = glm::translate(Model, offsetPosition);
                MVP = Projection * View * Model;
            }

            PerformRender();
        }
    }
}

void WarDrive::PerformRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Background color.
    //
    static float red = 0.0;
    static float green = 0.5;
    static float blue = 1.0;
    red += 0.01;
    green += 0.01;
    blue += 0.01;
    red = (red > 1) ? 0.1 : red;
    green = (green > 1) ? 0.1 : green;
    blue = (blue > 1) ? 0.1 : blue;
    glClearColor(red, green, blue, 1);

    //Cube.
    //
    // Use our shader
    glUseProgram(programID);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,        // attribute. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,        // attribute. No particular reason for 1, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //Send draw commands.
    //
    //glClear(GL_COLOR_BUFFER_BIT);
    // Clear the screen
    //
    SDL_GL_SwapWindow(window);
}

GLuint WarDrive::CreateProgramFromShaderText(const GLchar *vertexShaderAsString, const GLchar *fragmentShaderAsString) {
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

GLuint WarDrive::CreateProgramFromShaderFiles(const char *vertexShaderFileName, const char *fragmentShaderFileName) {
    GLuint programID;

    // Create and compile our GLSL program from the shaders
    GLsizei logSize;
	programID = LoadShaders( vertexShaderFileName, fragmentShaderFileName );
    glGetProgramInfoLog(programID, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';
    std::cout<<"programStatus status:"<<shaderInfoLog;

    return programID;
}


GLuint WarDrive::LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

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
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

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
