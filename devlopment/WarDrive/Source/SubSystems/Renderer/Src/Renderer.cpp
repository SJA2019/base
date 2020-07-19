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

#include "Renderer.h"

//Notes:
//opengl/SDL includes : https://stackoverflow.com/questions/22118518/use-of-undeclared-identifier-glgenvertexarrays-error-even-after-including-open
//on the fly shaders: https://gist.github.com/SuperV1234/5c5ad838fe5fe1bf54f9
//cube sample: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/ / https://github.com/opengl-tutorials/ogl/blob/master/tutorial04_colored_cube/tutorial04.cpp

//Camera.
glm::mat4 View;
glm::mat4 Projection;
float camX = 0.0f;//4.0f;
float camY = 0.0f;//3.0f;
float camZ = 20.0f;
float camTX = 0.0f;
float camTY = 0.0f;
float camTZ = 0.0f;


//Window
SDL_Window *window = NULL;

Renderer::Renderer()
{
    std::cout << "Renderer() ++" << std::endl;

    //SDL_Surface* screenSurface = NULL;
    window = SDL_CreateWindow("SampleRendering..",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return;
    }
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

    SDL_GLContext context = SDL_GL_CreateContext(window);
    pipelineInstance = make_shared<Pipeline>();
    objectInstance = make_shared<Object>();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    auto programID = pipelineInstance->GetProgramId();
    glUseProgram(programID);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    View = glm::lookAt(
        glm::vec3(camX, camY, camZ), // Camera is at (4,3,-3), in World Space
        glm::vec3(camTX, camTY, camTZ),  // and looks at the origin
        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Our ModelViewProjection : multiplication of our 3 matrices
    auto Model = objectInstance->getModelMatrix();
    pipelineInstance->updateMVPMatrix(Projection * View * Model);

    std::cout << "Renderer() --" << std::endl;
}

Renderer::~Renderer()
{
    std::cout << "~Renderer() ++" << std::endl;
    std::cout << "~Renderer() --" << std::endl;
}


void Renderer::HandleInput(SDL_Keycode input) {

            float objRotX = 0.0f;
            float objRotY = 0.0f;
            float objRotZ = 0.0f;

            float objXOffset = 0.0f;
            float objYOffset = 0.0f;
            float objZOffset = 0.0f;


            float camXOffset = 0.0f;
            float camYOffset = 0.0f;
            float camZOffset = 0.0f;
            
            switch(input) {
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
                    objXOffset++;
                break;
                case SDLK_2:
                    objXOffset--;
                break;
                case SDLK_3:
                    objYOffset++;
                break;
                case SDLK_4:
                    objYOffset--;
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
                auto MVP = Projection * View * objectInstance->getModelMatrix();
                pipelineInstance->updateMVPMatrix(MVP);
            }            

            //Edit Object coordinates (Model)
            //
            if((objRotX!=0) || (objRotY!=0) || (objRotZ!=0)) {
                std::cout<<"obj-rotation-axis="<<objRotX<<","<<objRotY<<","<<objRotZ;
                glm::vec3 myRotationAxis( objRotX, objRotY, objRotZ);
                float angle = 0.01f;
                //Model = glm::rotate(Model, angle, myRotationAxis );
                objectInstance->rotate(angle, myRotationAxis);
                auto MVP = Projection * View * objectInstance->getModelMatrix();
                pipelineInstance->updateMVPMatrix(MVP);
            }

            if((objXOffset!=0) || (objYOffset!=0) || (objZOffset!=0)) {
                std::cout<<"obj-position-offsets="<<objXOffset<<","<<objYOffset<<","<<objZOffset;
                glm::vec3 offsetPosition( objXOffset, objYOffset, objZOffset);
                //Model = glm::translate(Model, offsetPosition);
                objectInstance->translate(offsetPosition);
                auto MVP = Projection * View * objectInstance->getModelMatrix();
                pipelineInstance->updateMVPMatrix(MVP);
            }
}

void Renderer::Render()
{
    PerformRender();
}

void Renderer::PerformRender()
{
    
    //Paint Background Color.
    //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

    //Draw..
    //
    auto programID = pipelineInstance->GetProgramId();
    glUseProgram(programID);
    pipelineInstance->submitMVPMatrix();
    objectInstance->Draw();

    SDL_GL_SwapWindow(window);
}
