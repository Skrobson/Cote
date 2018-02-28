#pragma once
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtx\transform.hpp>

namespace cote
{
	class Transform
	{
	public:
		Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

		inline glm::mat4 getModel()const { return model; }

		glm::mat4 rotateAround(glm::vec3 point, glm::vec3 axis, float angle);
		glm::mat4 rotate(glm::vec3 axis, float angle);

		inline glm::vec3 getPos()const { return pos; }
		inline glm::vec3 getRot()const { return rot; }
		inline glm::vec3 getScale()const { return scale; }




		inline void setPos(const glm::vec3& pos) { this->pos = pos; calcModel(); }
		inline void setRot(const glm::vec3& rot) { this->rot = rot; calcModel(); }
		inline void setScale(const glm::vec3& scale) { this->scale = scale; calcModel(); }
	protected:

		glm::mat4 model;
		glm::vec3 pos;
		glm::vec3 rot;
		glm::vec3 scale;

		void calcModel();
	};
}



