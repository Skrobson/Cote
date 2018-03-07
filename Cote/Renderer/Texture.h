#pragma once
#include <GL\glew.h>
#include <string>
#include <memory>
#include "Bitmap.h"

namespace cote {
	namespace graphic {


		//TODO: initialize gdzies indziej, np do textureManagera
#define TEX_DIFFUSE "texture_diffuse"
#define TEX_SPECULAR "texture_specular"
#define TEX_NORMALS   "texture_normals"

		class Texture
		{
		public:
			enum Repeat : GLint
			{
				NORMAL = GL_REPEAT,
				MIRROR = GL_MIRRORED_REPEAT
			};

			Texture(size_t width , size_t height);
			Texture(Texture&&) = default;
			Texture(const Texture&) = default;

			unsigned getTextureID();

			void setSamplerName(const std::string& type);
			std::string getSamplerName()const;
			void bind(unsigned slot);
			void unbind(unsigned slot);
			virtual ~Texture();

		protected:
			unsigned width, height;
			
			std::string samplerName;
			
			std::shared_ptr<unsigned> handler;
			
			virtual void bindImpl() = 0;
			virtual void unbindImpl() = 0;
		};

		class Texture2d :public Texture
		{
		public:
			Texture2d(size_t width, size_t height, const unsigned char* data, Repeat repeat );

			Texture2d(Bitmap& image, Repeat repeat);

			Texture2d(Bitmap& image);

		protected:
			void bindImpl()override;

			void unbindImpl() override;
		};

	}
}
