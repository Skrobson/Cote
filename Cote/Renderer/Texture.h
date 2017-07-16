#pragma once
#include <GL/glew.h>
#include <string>

namespace cote {
	namespace graphic {


		//TODO: initialize gdzies indziej, np do textureManagera
//#define TEX_DIFFUSE "texture_diffuse"
//#define TEX_SPECULAR "texture_specular"
//#define TEX_NORMALS   "texture_normals"

		class Texture
		{
		public:
			Texture(size_t width , size_t height);
			Texture(Texture&&) = delete;
			Texture(const Texture&) = delete;
			GLuint getTextureID();

			void bind(unsigned slot);
			void unbind(unsigned slot);
			virtual ~Texture();

		protected:
			unsigned m_width, m_height;
			
			
			GLuint m_handler;
			
			virtual void bindImpl() = 0;
			virtual void unbindImpl() = 0;
		};

		class Texture2d :public Texture
		{
		public:
			Texture2d(size_t width, size_t height, const uint8_t* data);
		protected:
			void bindImpl()override;
			void unbindImpl() override;
		};

	}
}
