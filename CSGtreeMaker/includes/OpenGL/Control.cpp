#include "Control.h"
#include <stdio.h>

static bool firstMouse;
static glm::vec4 mouse;
static bool updateCamera;
static glm::vec2 cameraRot;
static glm::vec2 scroll;

Control::Control(int width, int height, const char* name, bool fullscreen)  {
	//INIT GLFW
	this->width = width;
	this->height = height;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create GLFW window
	window = (fullscreen) ?
		glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), nullptr) :
		glfwCreateWindow(width, height, name, nullptr, nullptr);

	if (window == nullptr) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	//INIT GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW\n");
		exit(-1);
	}

	//set up cursor
	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(window, cursor);

	//setup Input
	firstMouse = true;
	updateCamera = true;
	cameraRot = glm::vec2(0.0);
	glfwSetKeyCallback(window, keyboardCallback);
	//glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

}

GLFWwindow* Control::getWindow() {
	return window;
}

glm::vec2 Control::getCameraRot() {
	return cameraRot;
}

glm::vec2 Control::getScroll() {
	return scroll;
}

glm::vec4 Control::getMouse() {
	return mouse;
}

glm::vec4 Control::getNormalMouse() {
	return mouse / glm::vec4(float(width), float(height), float(width), float(height));
}

bool Control::keyPressed(int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Control::leftMousePressed() {
	return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool Control::rightMousePressed() {
	return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

bool Control::shouldQuit() { 
	return glfwWindowShouldClose(window);
}

void Control::showMouse() {
	updateCamera = false;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Control::hideMouse() {
	mouse = glm::vec4(width*0.5, height*0.5, 0.0, 0.0);
	firstMouse = true;
	updateCamera = true;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Control::update() {
	glfwPollEvents(); 
}

void Control::swapBuffers() {
	glfwSwapBuffers(window); 
}

double Control::getTime() {
	return glfwGetTime(); 
}

void Control::transparency(bool state) {
	if (state) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else {
		glDisable(GL_BLEND);
	}
}

void Control::depthTest(bool state) {
	if (state)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

//only counter clockwise
//use GL_FRONT or GL_BACK or false
void Control::cull(int state) {
	switch (state) {
	case GL_FRONT:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CCW);
		break;
	case GL_BACK:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		break;
	default:
		glDisable(GL_CULL_FACE);
		break;
	}
}

void Control::wireframe(bool state) {
	if (state)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Control::~Control() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Control::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void Control::mouseCallback(GLFWwindow* window, double x, double y) {
	if (firstMouse) {
		firstMouse = false;
		mouse = glm::vec4(x, y, 0.0, 0.0);
	} else {
		glm::vec2 old = glm::vec2(mouse.x, mouse.y);
		mouse = glm::vec4(x, y, x - old.x, old.y - y);
	}
	if (updateCamera) {
		cameraRot += glm::vec2(mouse.z, mouse.w);
	}
}

void Control::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	scroll.x += xoffset;
	if (scroll.y >= 0.0f && scroll.y <= 100.0f)
		scroll.y -= yoffset;
	if (scroll.y <= 0.0f)
		scroll.y = 0.0f;
	if (scroll.y >= 100.0f)
		scroll.y = 100.0f;
}
