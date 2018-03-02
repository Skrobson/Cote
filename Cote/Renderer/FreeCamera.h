#pragma once
#include "Camera.h"
#include "Window.h"
#include "Input.h"

namespace cote
{
	enum CameraMove {
		UP,
		DOWN,
		RIGHT,
		LEFT,
		FORWARD,
		BACKWARD

	};

	/**Prototype class for tests */
	class FreeCamera :
		public Camera
	{
	public:
		FreeCamera(const glm::vec3& cameraPos, const glm::vec3& cameraDirection, std::shared_ptr< Window> window);

		virtual void update() override;
		glm::mat4 move(GLfloat delta, CameraMove direction);

		inline void setSpeed(GLfloat speed) {
			mSpeed = speed;
		}
		~FreeCamera();
	private:
		GLfloat mSpeed;
		InputHandler* mInput;

		GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
		GLfloat lastFrame = 0.0f;

		GLfloat mLastX, mLastY;
		GLfloat mYaw = 0, mPitch = 0;
		bool mFirstMouseUse = true;

	};

}

