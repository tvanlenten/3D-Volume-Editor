#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0.0);
	dir = glm::vec3(0.0f, 0.0f, -1.0f);
	u = glm::vec3(1.0f, 0.0f, 0.0f);
	v = glm::vec3(0.0f, 1.0f, 0.0f);
	pitch = -90.0f;
	yaw = 0.0f;
	rotaionSpeed = 0.1f;
	movementSpeed = 0.1f;
	fov = 90.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;
	screenWidth = -1;
	screenHeight = -1;
}

Camera::Camera(int screen_width, int screen_height, glm::vec3 position, float fieldOfView, float near, float far, float rSpeed, float mSpeed) {
	this->position = position;
	dir = glm::vec3(0.0f, 0.0f, -1.0f);
	u = glm::vec3(1.0f, 0.0f, 0.0f);
	v = glm::vec3(0.0f, 1.0f, 0.0f);
	pitch = -90.0f;
	yaw = 0.0f;
	rotaionSpeed = rSpeed;
	movementSpeed = mSpeed;
	fov = fieldOfView;
	nearPlane = near;
	farPlane = far;
	screenWidth = screen_width;
	screenHeight = screen_height;
}

void Camera::init(int screen_width, int screen_height) {
	screenWidth = screen_width;
	screenHeight = screen_height;
}

/*
	-1, 0, 1 for each dir compononent
*/
void Camera::keyboardUpdate(int x, int y, int z) {
	/*
	//move position if keys were pressed
	if (control.keyPressed(GLFW_KEY_W))
	position += movementSpeed * dir;
	if (control.keyPressed(GLFW_KEY_S))
	position -= movementSpeed * dir;
	if (control.keyPressed(GLFW_KEY_A))
	position -= glm::normalize(glm::cross(dir, v)) * movementSpeed;
	if (control.keyPressed(GLFW_KEY_D))
	position += glm::normalize(glm::cross(dir, v)) * movementSpeed;
	if (control.keyPressed(GLFW_KEY_Q))
	position += glm::vec3(0.0, 1.0, 0.0) * movementSpeed;
	if (control.keyPressed(GLFW_KEY_E))
	position += glm::vec3(0.0, -1.0, 0.0) * movementSpeed;
	*/
}

void Camera::update(Control* control) {

	glm::vec2 cameraRot = control->getCameraRot();

	yaw = cameraRot.x * MouseSensitivity;
	pitch = cameraRot.y * MouseSensitivity;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	//move position if keys were pressed
	if (control->keyPressed(GLFW_KEY_W))
		position += movementSpeed * dir;
	if (control->keyPressed(GLFW_KEY_S))
		position -= movementSpeed * dir;
	if (control->keyPressed(GLFW_KEY_A))
		position -= glm::normalize(glm::cross(dir, v)) * movementSpeed;
	if (control->keyPressed(GLFW_KEY_D))
		position += glm::normalize(glm::cross(dir, v)) * movementSpeed;
	if (control->keyPressed(GLFW_KEY_Q))
		position += glm::vec3(0.0, 1.0, 0.0) * movementSpeed;
	if (control->keyPressed(GLFW_KEY_E))
		position += glm::vec3(0.0, -1.0, 0.0) * movementSpeed;
	//update camera vectors
	dir = glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	);
	dir = glm::vec3(1.0 / tan(0.5*fov*(PI / 180))) * dir;
	u = glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f)));
	v = glm::normalize(glm::cross(u, dir));


}

void Camera::mouseUpdate(glm::vec4 mouse) {
	yaw += mouse.z * MouseSensitivity;
	pitch += mouse.w * MouseSensitivity;
	if (pitch > 89.0f)
	pitch = 89.0f;
	if (pitch < -89.0f)
	pitch = -89.0f;

	//update camera vectors
	dir = glm::vec3(
	cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
	sin(glm::radians(pitch)),
	sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	);
	dir = glm::vec3(1.0 / tan(0.5*fov*(PI / 180))) * dir;
	u = glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f)));
	v = glm::normalize(glm::cross(u, dir));
}

glm::mat4 Camera::getViewMatrix() { 
	return glm::lookAt(position, position + dir, v);
}

glm::mat4 Camera::getProjMatrix() { 
	return glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, nearPlane, farPlane);
}

glm::vec3 Camera::getDir() { 
	return dir;
}

glm::vec3 Camera::getU() { 
	return u; 
}

glm::vec3 Camera::getV() { 
	return v; 
}

glm::vec3 Camera::getPosition() {
	return position; 
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}
void Camera::setFOV(float fov) { 
	this->fov = fov;
}

void Camera::setMoveSpeed(float moveSpeed) {
	this->movementSpeed = moveSpeed;
}
void Camera::setRotationSpeed(float rotationSpeed) {
	this->rotaionSpeed = rotationSpeed;
}

Camera::~Camera() {

}
