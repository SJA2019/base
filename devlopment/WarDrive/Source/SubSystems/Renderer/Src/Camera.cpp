// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera()
{
    std::cout << "Camera() ++" << std::endl;
    //Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 1.0f, 1000.0f);
    std::cout << "Camera() --" << std::endl;
}
void Camera::updateViewMatrix() {
    View = glm::lookAt(
        glm::vec3(camX, camY, camZ), // Camera is at (4,3,-3), in World Space
        glm::vec3(camTX, camTY, camTZ),  // and looks at the origin
        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
    );
}
void Camera::setPosition(float x, float y, float z) {
    camX = x;
    camY = y;
    camZ = z;
    updateViewMatrix();
}
void Camera::setTargetPositionLookedAt(float x, float y, float z) {
    camTX = x;
    camTY = y;
    camTZ = z;
    updateViewMatrix();
}
void Camera::movePosition(float xOffset, float yOffset, float zOffset) {
    camX += xOffset;
    camY += yOffset;
    camZ += zOffset;
    updateViewMatrix();
}
void Camera::moveTargetPositionLookedAt(float xOffset, float yOffset, float zOffset) {
    camTX += xOffset;
    camTY += yOffset;
    camTZ += zOffset;
    updateViewMatrix();
}
glm::mat4 Camera::getViewMatrix() {
    return View;
}
glm::mat4 Camera::getProjectionMatrix(){
    return Projection;
}
bool Camera::isLookingAtOrigin() {
    bool retVal = false;
    if((camTX==0) && (camTY==0) && (camTZ==0)) {
        retVal = true;
    }
    return retVal;
}