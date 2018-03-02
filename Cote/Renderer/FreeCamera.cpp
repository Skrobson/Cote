#include "FreeCamera.h"
#include <cmath>

using namespace cote;

FreeCamera::FreeCamera(const glm::vec3& cameraPos, const glm::vec3& cameraDirection, std::shared_ptr< Window> window) :Camera(cameraPos,cameraDirection,window->getFrameX(),window->getFrameY(),PERSPECTIVE),
	mInput(new InputHandler(window)),mSpeed(20.0f)
{	
	mPitch = 0;// asin(cameraDirection.y);
	mYaw = 0;//atan2(cameraDirection.x, cameraDirection.z);
	//Log debugLog;
	//debugLog() << cameraDirection.x << " " <<
	//	cameraDirection.y << " " <<
	//	cameraDirection.z << " " <<
	//	" pitch"<<mPitch<<" yaw"<<mYaw<< std::endl;

}

void FreeCamera::update()
{
	//Log debugLog;
	GLfloat currentFrame = (GLfloat)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Camera controls
	GLfloat cameraSpeed = 0.5f*deltaTime;
	if (mInput->keyEvent(GLFW_KEY_W))
		move(cameraSpeed, CameraMove::FORWARD);
	if (mInput->keyEvent(GLFW_KEY_S))
		move(cameraSpeed, CameraMove::BACKWARD);
	if (mInput->keyEvent(GLFW_KEY_A))
		move(cameraSpeed, CameraMove::LEFT);
	if (mInput->keyEvent(GLFW_KEY_D))
		move(cameraSpeed, CameraMove::RIGHT);
	if (mInput->keyEvent(GLFW_KEY_Q))
		move(cameraSpeed, CameraMove::UP);
	if (mInput->keyEvent(GLFW_KEY_E))
		move(cameraSpeed, CameraMove::DOWN);
	//mouse
	

	//issue pierwsze u¿ycie dziwnie przeskakuje, pozniej juz jest ok

	if (mInput->mouseButtonEvent(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 pos = mInput->mousePosition();

		if (mFirstMouseUse)
		{
			//debugLog() << "first use" << std::endl;
			mLastX = pos.x;
			mLastY = pos.y;
			mFirstMouseUse = false;
		}

		GLfloat xoffset = pos.x - mLastX;
		GLfloat yoffset = mLastY - pos.y; // Reversed since y-coordinates range from bottom to top
		mLastX = pos.x;
		mLastY = pos.y;
		//debugLog() << "ofsset xy:" << xoffset << " " << yoffset << std::endl;
		GLfloat sensitivity = 0.5f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		mYaw += xoffset;
		mPitch += yoffset;
		if (mPitch > 89.0f)
			mPitch = 89.0f;
		if (mPitch < -89.0f)
			mPitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		front.y = sin(glm::radians(mPitch));
		front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

		rotate(front);

		//debugLog() << front.x << " " <<
		//	front.y << " " <<
		//	front.z << " " <<
		//	" pitch" << mPitch << " yaw" << mYaw << std::endl;
	}
	if (!(mInput->mouseButtonEvent(GLFW_MOUSE_BUTTON_LEFT)))
		mFirstMouseUse = true;
	updateView();
}

glm::mat4 FreeCamera::move(GLfloat delta, CameraMove direction)
{
	GLfloat velocity = mSpeed*delta;
	switch (direction)
	{
	case FORWARD:
		mCameraPos += mCameraDirection*velocity;
		break;
	case BACKWARD:
		mCameraPos -= mCameraDirection*velocity;
		break;
	case LEFT:
		mCameraPos -= mCameraRight * velocity;
		break;
	case RIGHT:
		mCameraPos += mCameraRight * velocity;
		break;
	case UP:
		mCameraPos += mWorldUp*velocity;
		break;
	case DOWN:
		mCameraPos -= mWorldUp*velocity;
		break;
	default:
		break;
	}
	return getView();
}

FreeCamera::~FreeCamera()
{
	delete mInput;
}
