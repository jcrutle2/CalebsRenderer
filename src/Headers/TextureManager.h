#pragma once

//#include "FreeImage.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#   define STB_IMAGE_IMPLEMENTATION

#include "glew.h"
#include "glm.hpp"
#include "stb_image.h"
#include <vector>

#endif

class TextureManager
{
public:
	static TextureManager* Inst()
	{
		if (!m_inst)
			m_inst = new TextureManager();
		stbi_set_flip_vertically_on_load(true);
		return m_inst;
	}
	virtual ~TextureManager()
	{
		UnloadAllTextures();
	}

	GLuint LoadTexture(const char* filename, GLenum image_format, GLint internal_format, GLint level, GLint border);

	//free the memory for a texture
	void UnloadTexture(const unsigned int texID);

	//set the current texture
	void BindTexture(const unsigned int texID);

	//free all texture memory
	void UnloadAllTextures();

protected:
	TextureManager();

	TextureManager(const TextureManager& tm);

	TextureManager& operator=(const TextureManager& tm);

	static TextureManager* m_inst;
	std::vector<GLuint> m_texID;
};

TextureManager* TextureManager::m_inst = nullptr;