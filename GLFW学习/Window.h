#pragma once
class glfwWindow
{
	GLFWwindow* glWindow=nullptr;
public:
	int width;
	int height;
	glfwWindow(GLFWwindow* glWindow) {
		this->glWindow = glWindow;
		RefreshSize();
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
	void RefreshSize() {
		glfwGetFramebufferSize(glWindow, &width, &height);
	}
	void SetWindowSizeCallback(GLFWwindowsizefun callback) {
		glfwSetWindowSizeCallback(glWindow, callback);
	}
	void SetInputMode(int mode,int value) {
		glfwSetInputMode(glWindow, mode, value);
	}
	void SetCursorPosCallback(GLFWcursorposfun callback) {
		glfwSetCursorPosCallback(glWindow,callback);
	}
	void SetScrollCallback(GLFWscrollfun callback) {
		glfwSetScrollCallback(glWindow,callback);
	}
public:
	static glfwWindow* CreateWindow();
};

