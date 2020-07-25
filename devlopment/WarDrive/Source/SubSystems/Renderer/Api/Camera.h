#pragma once

#include <memory>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <SDL_opengl.h>
#endif
#include <OpenGL/glu.h>

#include "Pipeline.h"
using namespace std;

class Camera {
    //Camera.
    glm::mat4 View;
    glm::mat4 Projection;
    float camX = 0.0f;//4.0f;
    float camY = 0.0f;//3.0f;
    float camZ = 20.0f;
    float camTX = 0.0f;
    float camTY = 0.0f;
    float camTZ = 0.0f;
    void updateViewMatrix();

    public:
    Camera();
    void setPosition(float x, float y, float z);
    void setTargetPositionLookedAt(float x, float y, float z);
    void movePosition(float x, float y, float z);
    void moveTargetPositionLookedAt(float x, float y, float z);
    bool isLookingAtOrigin();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};

typedef shared_ptr<Camera> CameraSPTR;