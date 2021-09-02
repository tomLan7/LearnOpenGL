#pragma once
class Window
{
	GLFWwindow* glWindow=nullptr;
public:
	int width;
	int height;
	Window(GLFWwindow* glWindow) {
		this->glWindow = glWindow;

		glfwGetFramebufferSize(glWindow, &width, &height);
	}
	void SetKeyCallback(GLFWkeyfun callback){

		glfwSetKeyCallback(glWindow, callback);
	}
	bool IsShouldClose() {
		return glfwWindowShouldClose(glWindow);
	}
	void SwapBuffers() {
		glfwSwapBuffers(glWindow);
	}
	void SetWindowShouldClose(GLboolean BOOL) {
		glfwSetWindowShouldClose(glWindow, BOOL);
	}
public:
	static Window* CreateWindow();
};

