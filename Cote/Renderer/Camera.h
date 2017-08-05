#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtx\transform.hpp>
#include "Window.h"

//TODO: poprawic konstrukto, camera direction , cameratarget
class Camera
{
public:
	enum Projection {
		PERSPECTIVE,
		ORTHOGRAPHIC
	};
	Camera(glm::vec3 cameraPos, glm::vec3 cameraDirection,const int& frameX,const int& frameY, Projection projection);
	glm::mat4 translate(glm::vec3 translation);
	//zostanie przeniesione na wyzszy poziom
	
	
	glm::mat4 rotate(glm::vec3 rotVector);
	glm::mat4 rotate(float pitch, float yaw, float roll);

	virtual void update() = 0;

	inline const glm::vec3& getPosition() const{
		return mCameraPos;
	}

	inline const glm::vec3& getDirection() const {
		return mCameraDirection;
	}

	inline const glm::mat4& getView()const {
		return mView;
	}

	inline const glm::mat4& getProjection()const {
		return mProjection;
	}

	virtual ~Camera();
protected:

	glm::mat4 mView;
	glm::mat4 mProjection;
	glm::vec3 mCameraPos;

	glm::vec3 mCameraTarget;
	glm::vec3 mCameraDirection; 
	glm::vec3 mCameraRight ;
	
	glm::vec3 mCameraUp ;
	glm::vec3 mWorldX;
	glm::vec3 mWorldUp;


	GLfloat mLastX, mLastY;
	GLfloat mYaw = 0, mPitch = 0;
	bool firstMouse = true;

	void updateView();
};

