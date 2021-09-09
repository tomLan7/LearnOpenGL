// GLFWѧϰ.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Camera.h"
#include"Shader.h"
#include"Window.h"

using namespace std;
using namespace glm;
void initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(-1);
    }
}
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
float Rotation = 0;
float x, y, z;
float scale = 1;
vec3 lightPos(5, 1, 1);
mat4 lightModel;

mat4 projection;
float angleView = 45;


void someOpenGLFunctionThatDrawsOurTriangle(ShaderProgram* shaderProgram) {
    //ʹ���߿�ģʽ
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto TransMat = glm::translate(glm::mat4(1), glm::vec3(x, y, 0.0f));
    shaderProgram->Uniform("transform", TransMat);
    auto ScaleMat = glm::scale(glm::mat4(1), glm::vec3(::scale, ::scale, ::scale));
    shaderProgram->Uniform("scaleform", ScaleMat);
    auto RotationMat = glm::rotate(glm::mat4(1), radians(Rotation), glm::vec3(0.0, 0.0, 1.0));
    shaderProgram->Uniform("rotation", RotationMat);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawArrays(GL_TRIANGLES,0,3);
    //ʹ�õ�ǰ�������ɫ����֮ǰ�Ķ����������ú�VBO�Ķ�������(��VAO��Ӱ�)��
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void shaderTestMainLoop(ShaderProgram* shaderProgram) {
    // ����uniform��ɫ
    GLfloat timeValue = glfwGetTime();
    GLfloat offsetValue = (sin(timeValue) / 2);
    shaderProgram->Uniform("offset", offsetValue);
    static GLfloat preTime = timeValue;
    std::cout << "������" << timeValue - preTime << "��ʱ��" << std::endl;
    preTime = timeValue;
}
GLfloat mixValue = 0.2;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void changeState(Window* window);
void scroll_callback(GLFWwindow*, double, double);

bool keys[1024] = { 0 };
EulerFPSCamera* camera = new EulerFPSCamera();
GLuint CreateTexture(std::string textureName) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int texWidth, texHeight;
    unsigned char* image = SOIL_load_image(textureName.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //�Զ����ɶ༶ͼ��
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}
int main()
{
    Window* window = Window::CreateWindow();
    //����ʹ�ø߼�����
    initGLEW();

    //�����ӿڱ任
    glViewport(0, 0, window->width, window->height);
    window->SetKeyCallback(key_callback2);
    window->SetWindowSizeCallback([](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        });
    window->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window->SetCursorPosCallback(mouse_callback);
    window->SetScrollCallback(scroll_callback);
    //model = glm::rotate(mat4(1), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 cubePositions[] = {
      glm::vec3(2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(5.4f, -0.4f, -1.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f,  2.0f, -2.5f),
      glm::vec3(1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    GLuint texture1= CreateTexture("container2.png");
    GLuint texture2 = CreateTexture("container2_specular.png");
    

    ShaderProgram* shaderProgram = ShaderProgram::CreateFromVertexAndFragmentPath("lx21.vert", "lx21.frag");
    ShaderProgram* LightShaderProgram = ShaderProgram::CreateFromVertexAndFragmentPath("lx18.vs", "lx16light.frag");

    GLuint VBO;
    //��������1��ʾ���ɻ�������������������Ժ������������ɶ�����󣬴�ʱVBOҲӦ���Ƕ�Ӧ��GLuint����ĵ�ַ����������������һ��ָ�롣
    glGenBuffers(1, &VBO);
    GLuint VAO;
    //����������������
    glGenVertexArrays(1, &VAO);

    //�󶨶�������ΪĿ��
    glBindVertexArray(VAO);
    // 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ�� �ϱ��Ѿ����ù�
    //�����ͣ�һ������ֻ����һ��GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //���ݷ��͵��Կ��Ķ��㻺���С�ʵ���ϾͶ�Ӧ��VBO����������
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 4. ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //5. ���VAO��״̬�Ѿ��洢������������
    glBindVertexArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnable(GL_DEPTH_TEST);
    //��ѭ��
    double NextFrameDelay = 1 / 60.;
    double nextTime = glfwGetTime() + NextFrameDelay;
    while (!window->IsShouldClose())
    {
        double needSleep = nextTime - glfwGetTime();
        needSleep = needSleep > 0 ? needSleep : 0;
        nextTime += NextFrameDelay;
        glfwWaitEventsTimeout(needSleep);
        //����¼�
        glfwPollEvents();
        changeState(window);
        shaderTestMainLoop(shaderProgram);

        //shaderProgram->Uniform("model", model);
        shaderProgram->User();
        shaderProgram->Uniform("view", camera->ToViewMatrix());
        projection = glm::perspective(glm::radians(angleView), window->width / (float)window->height, 0.1f, 100.0f);
        shaderProgram->Uniform("projection", projection);

        auto TransMat = glm::translate(glm::mat4(1), glm::vec3(x, y, 0.0f));
        shaderProgram->Uniform("transform", TransMat);
        auto ScaleMat = glm::scale(glm::mat4(1), glm::vec3(::scale, ::scale, ::scale));
        shaderProgram->Uniform("scaleform", ScaleMat);
        auto RotationMat = glm::rotate(glm::mat4(1), radians(Rotation), glm::vec3(0.0, 0.0, 1.0));
        shaderProgram->Uniform("rotation", RotationMat);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(VAO);

        shaderProgram->Uniform("light.ambient", vec3(0.3f, 0.3f, 0.3f));
        shaderProgram->Uniform("light.diffuse", vec3(0.6f, 0.6f, 0.6f));
        shaderProgram->Uniform("light.specular", vec3(1.0f, 1.0f, 1.0f));
        shaderProgram->Uniform("light.position", vec3(TransMat * vec4(lightPos, 1)));
        shaderProgram->Uniform("viewPos", camera->pos);
        shaderProgram->Uniform("material.ambient", vec3(1.0f, 1.0f, 1.0f));
        shaderProgram->Uniform("material.diffuse", vec3(1.0f, 1.0f, 1.0f));
        shaderProgram->Uniform("material.specular", vec3(1.0f, 1.0f, 1.0f));
        shaderProgram->Uniform("material.shininess", 64.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        shaderProgram->Uniform("material.diffuse",0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        shaderProgram->Uniform("material.specular",1);

        for (GLuint i = 0; i < sizeof(cubePositions) / sizeof(decltype(cubePositions[0])); i++)
        {
            glm::mat4 model;
            model = glm::translate(mat4(1), cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram->Uniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        LightShaderProgram->User();
        LightShaderProgram->Uniform("rotation", RotationMat);
        LightShaderProgram->Uniform("scaleform", glm::scale(glm::mat4(1), glm::vec3(0.1, 0.1, 0.1)));
        LightShaderProgram->Uniform("transform", TransMat);
        LightShaderProgram->Uniform("projection", projection);
        LightShaderProgram->Uniform("view", camera->ToViewMatrix());

        lightModel = translate(mat4(1), lightPos);
        LightShaderProgram->Uniform("model", lightModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glBindVertexArray(0);
        //someOpenGLFunctionThatDrawsOurTriangle(shaderProgram);


        //������������˫�������
        window->SwapBuffers();
    }
    glfwTerminate();
    return 0;
}
//�滮һ�°�����
//���ּ��������Ƴ�����Ԫ�ص�ģ�;���8462�ƶ���79��ת��13���š�+-��ɫ��
//�����������wasdǰ�����ˡ�q��ת��e��ת���ո����ƣ�ctrl����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_KP_ADD:
            mixValue += 0.1f;
            if (mixValue >= 1.0f)
                mixValue = 1.0f;
            break;
        case GLFW_KEY_KP_SUBTRACT:
            mixValue -= 0.1f;
            if (mixValue <= 0.0f)
                mixValue = 0.0f;
            break;
        case GLFW_KEY_KP_1:
            ::scale *= 1.1;
            break;
        case GLFW_KEY_KP_2:
            y -= 0.1f;
            break;
        case GLFW_KEY_KP_3:
            ::scale *= 0.9;
            break;
        case GLFW_KEY_KP_4:
            x -= 0.1f;
            break;
        case GLFW_KEY_KP_5:
            break;
        case GLFW_KEY_KP_6:
            x += 0.1f;
            break;
        case GLFW_KEY_KP_7:
            Rotation += 15;
            break;
        case GLFW_KEY_KP_8:
            y += 0.1f;
            break;
        case GLFW_KEY_KP_9:
            Rotation -= 15;
            break;
        case GLFW_KEY_W:
        case GLFW_KEY_A:
        case GLFW_KEY_S:
        case GLFW_KEY_D:
        case GLFW_KEY_Q:
        case GLFW_KEY_E:
        case GLFW_KEY_SPACE:
        case GLFW_KEY_LEFT_CONTROL:
        case GLFW_KEY_R:
        case GLFW_KEY_F:
            camera->keyOrder(key);
            break;
        default:
            break;
        }
    }
}
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS) {
        keys[key] = true;
    }
    if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}
void changeState(Window* window) {
    for (int i = 0; i < 1024; i++) {
        if (keys[i] == true)
            switch (i)
            {
            case GLFW_KEY_ESCAPE:
                window->SetWindowShouldClose(GL_TRUE);
                break;
            case GLFW_KEY_KP_ADD:
                mixValue += 0.1f;
                if (mixValue >= 1.0f)
                    mixValue = 1.0f;
                break;
            case GLFW_KEY_KP_SUBTRACT:
                mixValue -= 0.1f;
                if (mixValue <= 0.0f)
                    mixValue = 0.0f;
                break;
            case GLFW_KEY_KP_1:
                ::scale *= 1.1;
                break;
            case GLFW_KEY_KP_2:
                y -= 0.1f;
                break;
            case GLFW_KEY_KP_3:
                ::scale *= 0.9;
                break;
            case GLFW_KEY_KP_4:
                x -= 0.1f;
                break;
            case GLFW_KEY_KP_5:
                break;
            case GLFW_KEY_KP_6:
                x += 0.1f;
                break;
            case GLFW_KEY_KP_7:
                Rotation += 15;
                break;
            case GLFW_KEY_KP_8:
                y += 0.1f;
                break;
            case GLFW_KEY_KP_9:
                Rotation -= 15;
                break;

            case GLFW_KEY_W:
            case GLFW_KEY_A:
            case GLFW_KEY_S:
            case GLFW_KEY_D:
            case GLFW_KEY_Q:
            case GLFW_KEY_E:
            case GLFW_KEY_SPACE:
            case GLFW_KEY_LEFT_CONTROL:
            case GLFW_KEY_R:
            case GLFW_KEY_F:
                camera->keyOrder(i);
                break;
            case GLFW_KEY_LEFT:
            {
                vec4 newViewPos = translate(mat4(1), vec3(-0.1, 0, 0)) * camera->ToViewMatrix() * vec4(lightPos, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                lightPos = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_RIGHT:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0.1, 0, 0)) * camera->ToViewMatrix() * vec4(lightPos, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                lightPos = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_UP:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0, 0.1, 0)) * camera->ToViewMatrix() * vec4(lightPos, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                lightPos = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;
            case GLFW_KEY_DOWN:
            {
                vec4 newViewPos = translate(mat4(1), vec3(0, -0.1, 0)) * camera->ToViewMatrix() * vec4(lightPos, 1);
                vec4 newWorldPos = inverse(camera->ToViewMatrix()) * newViewPos;
                lightPos = vec3(newWorldPos.x, newWorldPos.y, newWorldPos.z);
            }
            break;

            default:
                break;
            }
    }
}

double preX, preY;
bool start = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    if (start) {
        start = false;
        preX = xpos;
        preY = ypos;
        return;
    }
    double offsetX = xpos - preX;
    double offsetY = ypos - preY;
    camera->mouseOrder(offsetX, offsetY);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    preX = xpos;
    preY = ypos;
}

void scroll_callback(GLFWwindow*, double dx, double dy) {
    angleView += dy;
}