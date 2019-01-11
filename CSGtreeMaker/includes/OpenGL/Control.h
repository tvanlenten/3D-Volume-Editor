#ifndef CONTROL_H_
#define CONTROL_H_

#include <glm/glm.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <string>

// TODO
/*
	create constructor for control
	impliment methods for control
	delete text.h, text.vt, text.frag, input.h,
	add .cpp files for all major classes
*/

class Control {
public:
	Control(int width, int height, const char* name, bool fullscreen);

	glm::vec2 getCameraRot();
	glm::vec2 getScroll();
	glm::vec4 getMouse();
	glm::vec4 getNormalMouse();
	bool keyPressed(int key);
	bool leftMousePressed();
	bool rightMousePressed();
	
	/*
		shows the mouse and halts cameraRotation movement
	*/
	void showMouse();

	/*
		hides the mouse, resets it to the center and begins
		recording cameraRotation movement
	*/
	void hideMouse();


	void update();
	bool shouldQuit();
	double getTime();
	void cull(int state);
	void wireframe(bool state);
	void depthTest(bool state);
	void transparency(bool state);
	void swapBuffers();

	GLFWwindow* getWindow();

	~Control();
private:
	GLFWwindow* window;
	int width;
	int height;
	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseCallback(GLFWwindow* window, double x, double y);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif //Control.h