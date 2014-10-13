//
//  controls.cpp
//  opengl
//
//  Created by Bert Bosch on 13-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#include "controls.h"
float speed = 1.0f;

Camera::Camera() :
    _position(0.0f, 0.0f, 1.0f)
{}

const glm::vec3& Camera::getPosition() const {
    return _position;
}

void Camera::setPosition(const glm::vec3& position) {
    _position = position;
}

void Camera::computeInputs(GLFWwindow* window){
    // glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();
    
	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		_position.y += 1 * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		_position.y -= 1 * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		_position.x += 1 * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		_position.x -= 1 * deltaTime * speed;
	}
    
	lastTime = currentTime;
}