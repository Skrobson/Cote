#include "Camera.h"





Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraDirection, const int& frameX, const int& frameY, Projection projection)
	:mCameraPos(cameraPos),mCameraDirection(cameraDirection),mWorldUp(0.0f,1.0f,0.0f)
{
	//mCameraDirection= glm::normalize(mCameraPos - mCameraDirection);
	mCameraRight = glm::normalize(glm::cross(mWorldUp, mCameraDirection));
	mCameraUp = glm::cross(mCameraDirection, mCameraRight);

	mView= glm::lookAt(cameraPos, cameraPos + mCameraDirection, mCameraUp);
	switch (projection) {
	case PERSPECTIVE:
		mProjection= glm::perspective(glm::radians(45.0f), (float)frameX / frameY, 0.1f, 1000.0f);
		break;
	case ORTHOGRAPHIC:
		mProjection= glm::ortho(0.0f, (float)frameX, 0.0f, (float)frameY, 0.1f, 1000.0f);
		break;
	default:
		break;
	}


}

glm::mat4 Camera::translate(glm::vec3 translation)
{
	mCameraPos += translation;
	return getView();
}

glm::mat4 Camera::rotate(glm::vec3 rotVector)
{
	mCameraDirection = glm::normalize(rotVector);
	
	mCameraRight = glm::normalize(glm::cross(mCameraDirection, mWorldUp));
	mCameraUp = glm::cross(mCameraRight, mCameraDirection);
	return getView();
}

glm::mat4 Camera::rotate(float pitch, float yaw, float roll)
{
	return glm::mat4();
}

Camera::~Camera()
{
}

void Camera::updateView()
{
	mView=glm::lookAt(mCameraPos, mCameraPos + mCameraDirection, mCameraUp);
}
