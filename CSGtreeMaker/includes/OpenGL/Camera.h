#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Control.h"

#define PI 3.14159265359
#define MouseSensitivity 0.1f

/*
	FIX!!! rasterizing and ray casting do not line up!
	FOV does not work for ray casting
*/

class Camera {
public:
	Camera();
	Camera(int screen_width, int screen_height, glm::vec3 position, float fieldOfView, float near, float far, float rSpeed, float mSpeed);
	void init(int screen_width, int screen_height);

	void keyboardUpdate(int x, int y, int z);
	void mouseUpdate(glm::vec4 mouse);
	void update(Control* control);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	glm::vec3 getDir();
	glm::vec3 getU();
	glm::vec3 getV();
	glm::vec3 getPosition();

	void setPosition(glm::vec3 position);
	void setFOV(float fov);
	void setMoveSpeed(float moveSpeed);
	void setRotationSpeed(float rotationSpeed);

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 dir;
	glm::vec3 u;
	glm::vec3 v;
	float pitch;
	float yaw;
	float rotaionSpeed;
	float movementSpeed;
	float fov;
	float nearPlane;
	float farPlane;
	int screenWidth;
	int screenHeight;
};

#endif //Camera.h

