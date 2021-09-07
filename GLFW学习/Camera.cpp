
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
using namespace glm;

void WeightlessnessCamera::keyOrder(int key) {
       switch (key)
        {
        case GLFW_KEY_W:
            view = viewRotation * view;
            viewRotation = glm::mat4(1);
            viewMove = glm::translate(viewMove, vec3(0, 0, 0.1));
            break;
        case GLFW_KEY_A:
            view = viewRotation * view;
            viewRotation = mat4(1);
            viewMove = translate(viewMove, vec3(0.1, 0, 0));
            break;
        case GLFW_KEY_S:
            view = viewRotation * view;
            viewRotation = mat4(1);
            viewMove = translate(viewMove, vec3(0, 0, -0.1));
            break;
        case GLFW_KEY_D:
            view = viewRotation * view;
            viewRotation = mat4(1);
            viewMove = translate(viewMove, vec3(-0.1, 0, 0));
            break;
        case GLFW_KEY_Q:
            view = viewMove * view;
            viewMove = mat4(1);
            viewRotation = rotate(viewRotation, radians(-10.f), vec3(0, 1, 0));
            break;
        case GLFW_KEY_E:
            view = viewMove * view;
            viewMove = mat4(1);
            viewRotation = rotate(viewRotation, radians(10.f), vec3(0, 1, 0));
            break;
        case GLFW_KEY_SPACE:
            view = viewRotation * view;
            viewRotation = mat4(1);
            viewMove = translate(viewMove, vec3(0, -0.1, 0));
            break;
        case GLFW_KEY_LEFT_CONTROL:
            view = viewRotation * view;
            viewRotation = mat4(1);
            viewMove = translate(viewMove, vec3(0, 0.1, 0));
            break;
        case GLFW_KEY_R:
            view = viewRotation * view;
            viewRotation = mat4(1);
            viewMove = translate(viewMove, vec3(0, 0.1, 0));
            break;
        case GLFW_KEY_F:
            view = viewRotation * view;
            viewRotation = mat4(1);
            viewMove = translate(viewMove, vec3(0, 0.1, 0));
            break;
        default:
            break;
        }
}

void WeightlessnessCamera::mouseOrder(float offsetX, float offsetY)
{
    view = viewMove * view;
    viewMove = mat4(1);
    view = viewRotation * view;
    viewRotation = mat4(1);
    viewRotation = rotate(viewRotation, radians(offsetX), vec3(0, 1, 0));
    viewRotation = rotate(viewRotation, radians(offsetY), vec3(1, 0, 0));

}

void FPSCamera::keyOrder(int key)
{
    vec3 faceV=face();
    switch (key)
    {
    case GLFW_KEY_W:
        pos += vec3(faceV.x,faceV.y,0)*0.1f;
        target+= vec3(faceV.x, faceV.y, 0) * 0.1f;
        break;
    case GLFW_KEY_A:
        pos += -cross(vec3(faceV.x, faceV.y, 0),up) * 0.1f;
        target += -cross(vec3(faceV.x, faceV.y, 0), up) * 0.1f;
        break;
    case GLFW_KEY_S:
        pos += -vec3(faceV.x, faceV.y, 0) * 0.1f;
        target += -vec3(faceV.x, faceV.y, 0) * 0.1f;
        break;
    case GLFW_KEY_D:
        pos += cross(vec3(faceV.x, faceV.y, 0), up) * 0.1f;
        target += cross(vec3(faceV.x, faceV.y, 0), up) * 0.1f;
        break;
    case GLFW_KEY_Q:
        target=pos+(vec3)(rotate(mat4(1), radians(3.f), vec3(0, 0, 1))*vec4(faceV,0));
        break;
    case GLFW_KEY_E:
        target = pos + (vec3)(rotate(mat4(1), radians(-3.f), vec3(0, 0, 1)) * vec4(faceV, 0));
        break;
    case GLFW_KEY_SPACE:
        pos += vec3(0, 0, 1) * 0.1f;
        target += vec3(0, 0, 1) * 0.1f;
        break;
    case GLFW_KEY_LEFT_CONTROL:
        pos += -vec3(0, 0, 1) * 0.1f;
        target += -vec3(0, 0, 1) * 0.1f;
        break;
    case GLFW_KEY_R:
        target = pos + (vec3)(rotate(mat4(1), radians(3.f),cross(faceV,up)) * vec4(faceV, 0));
        break;
    case GLFW_KEY_F:
        target = pos + (vec3)(rotate(mat4(1), -radians(3.f), cross(faceV, up)) * vec4(faceV, 0));
        break;
    default:
        break;
    }
}

void FPSCamera::mouseOrder(float offsetX, float offsetY)
{
    vec3 faceV = face();
    target = pos + (vec3)(rotate(mat4(1), -radians(offsetX), vec3(0, 0, 1)) * vec4(faceV, 0));
    faceV = face();
    target = pos + (vec3)(rotate(mat4(1), -radians(offsetY), cross(faceV, up)) * vec4(faceV, 0));

}