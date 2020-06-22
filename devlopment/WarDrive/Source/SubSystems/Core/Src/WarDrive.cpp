#include "SDL.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <SDL_opengl.h>
#endif
#include <OpenGL/glu.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
#include <iostream>
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
    1.0f, -1.0f, 1.0f};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.583f, 0.771f, 0.014f,
    0.609f, 0.115f, 0.436f,
    0.327f, 0.483f, 0.844f,
    0.822f, 0.569f, 0.201f,
    0.435f, 0.602f, 0.223f,
    0.310f, 0.747f, 0.185f,
    0.597f, 0.770f, 0.761f,
    0.559f, 0.436f, 0.730f,
    0.359f, 0.583f, 0.152f,
    0.483f, 0.596f, 0.789f,
    0.559f, 0.861f, 0.639f,
    0.195f, 0.548f, 0.859f,
    0.014f, 0.184f, 0.576f,
    0.771f, 0.328f, 0.970f,
    0.406f, 0.615f, 0.116f,
    0.676f, 0.977f, 0.133f,
    0.971f, 0.572f, 0.833f,
    0.140f, 0.616f, 0.489f,
    0.997f, 0.513f, 0.064f,
    0.945f, 0.719f, 0.592f,
    0.543f, 0.021f, 0.978f,
    0.279f, 0.317f, 0.505f,
    0.167f, 0.620f, 0.077f,
    0.347f, 0.857f, 0.137f,
    0.055f, 0.953f, 0.042f,
    0.714f, 0.505f, 0.345f,
    0.783f, 0.290f, 0.734f,
    0.722f, 0.645f, 0.174f,
    0.302f, 0.455f, 0.848f,
    0.225f, 0.587f, 0.040f,
    0.517f, 0.713f, 0.338f,
    0.053f, 0.959f, 0.120f,
    0.393f, 0.621f, 0.362f,
    0.673f, 0.211f, 0.457f,
    0.820f, 0.883f, 0.371f,
    0.982f, 0.099f, 0.879f};

// Shader sources
const GLchar *vertexSource =
    "#version 330 core\nlayout(location = 0) in vec3 vertexPosition_modelspace;layout(location = 1) in vec3 vertexColor;out vec3 fragmentColor;uniform mat4 MVP;void main(){gl_Position =  MVP * vec4(vertexPosition_modelspace,1);fragmentColor = vertexColor;}";

const GLchar *fragmentSource =
    "#version 330 core\nin vec3 fragmentColor;out vec3 color;void main(){color = fragmentColor;}";

SDL_Window *window = NULL;

GLuint programID;
GLuint MatrixID;
GLuint vertexbuffer;
GLuint colorbuffer;

float angle = 0.0f;
glm::mat4 Model;
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
#if 1
    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLsizei logSize;
    glGetShaderInfoLog(vertexShader, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';
    std::cout<<"vertexShader status:"<<shaderInfoLog;

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderInfoLog(fragmentShader, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';
    std::cout<<"fragmentShader status:"<<shaderInfoLog;

    // Link the vertex and fragment shader into a shader program
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    // glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(programID);


    glGetProgramInfoLog(programID, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';
    std::cout<<"programStatus status:"<<shaderInfoLog;
#endif
#if 0
    // Create and compile our GLSL program from the shaders
	programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
    glGetProgramInfoLog(programID, 256, &logSize, shaderInfoLog);
    shaderInfoLog[256]='\0';
    std::cout<<"programStatus status:"<<shaderInfoLog;

#endif

    glUseProgram(programID);

    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(programID, "MVP");

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    View = glm::lookAt(
        glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
        glm::vec3(0, 0, 0),  // and looks at the origin
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
    IMJoyEventTypes inputEvent = IMJoyEventTypes::eIMEventNotAvailable;
    while (true)
    {
        inputEvent = m_sptrInputManager->PollJoyEvents();
        if (IMJoyEventTypes::eIMEventBailOut == inputEvent)
        {
            break;
        }
        else if (IMJoyEventTypes::eIMEventAvailable == inputEvent)
        {
            angle += 0.001f;
            if(angle>360.0f) {
                angle = 0.0f;
            }
            glm::vec3 myRotationAxis( 1.0f, 1.0f, 1.0f);
            Model = glm::rotate(Model, angle, myRotationAxis );
            MVP = Projection * View * Model;
            #if 0
            MVP = MVP + glm::mat4(0.01f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 0.0f);
            #endif
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
