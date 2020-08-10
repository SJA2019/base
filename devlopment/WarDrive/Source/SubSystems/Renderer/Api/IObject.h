#pragma once

#include <memory>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class IObject {

    public:
    virtual glm::mat4 getModelMatrix() = 0;
    virtual void rotate(float angle, glm::vec3 axis) = 0;
    virtual void translate(glm::vec3 offset) = 0;
    virtual void Draw() = 0;

};

typedef std::shared_ptr<IObject> IObjectSPTR;