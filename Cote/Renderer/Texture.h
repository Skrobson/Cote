#pragma once
#include <GL/glew.h>
#include <string>
#include <memory>
#include "Image.h"

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
			Texture(Texture&&) = default;
			Texture(const Texture&) = default;
			unsigned getTextureID();

			void bind(unsigned slot);
			void unbind(unsigned slot);
			virtual ~Texture();

		protected:
			unsigned m_width, m_height;
			
			
			std::shared_ptr<unsigned> m_handler;
			
			virtual void bindImpl() = 0;
			virtual void unbindImpl() = 0;
		};

		class Texture2d :public Texture
		{
		public:
			Texture2d(size_t width, size_t height, const unsigned char* data);

			Texture2d(Bitmap& image);

		protected:
			void bindImpl()override;

			void unbindImpl() override;
		};

	}
}
