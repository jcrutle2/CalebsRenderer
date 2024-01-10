//
// Created by Caleb Rutledge on 1/7/24.
//

#include "Headers/TextureManager.h"

/*
GLuint LoadTexture(const char* filename, GLenum image_format = GL_RGB, GLint internal_format = GL_RGB, GLint level = 0, GLint border = 0)
{
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE* bits(0);
    //image width and height
    unsigned int width(0), height(0);
    //OpenGL's image ID to map to
    GLuint gl_texID;

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    //if still unkown, return failure
    if (fif == FIF_UNKNOWN)
        return -1;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
    //if the image failed to load, return failure
    if (!dib)
        return -1;

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
        return -1;

    //generate an OpenGL texture ID for this texture
    glGenTextures(1, &gl_texID);
    //store the texture ID mapping
    m_texID.push_back(gl_texID);
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, gl_texID);
    //store the texture data for OpenGL use
    glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
        border, image_format, GL_UNSIGNED_BYTE, bits);

    //Free FreeImage's copy of the data
    FreeImage_Unload(dib);

    //return success
    return gl_texID;
}
*/

GLuint TextureManager::LoadTexture(const char* filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
    int width, height;
    int nrChannels;
    unsigned char* data;
    GLuint gl_texID;

    // load image file
    data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if ((data == 0) || (width == 0) || (height == 0))
        return -1;

    //generate an OpenGL texture ID for this texture
    glGenTextures(1, &gl_texID);
    //store the texture ID mapping
    m_texID.push_back(gl_texID);
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, gl_texID);
    //store the texture data for OpenGL use
    glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
                 border, image_format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    return gl_texID;
}

//free the memory for a texture
void TextureManager::UnloadTexture(const unsigned int texID)
{
    auto id = find(m_texID.begin(), m_texID.end(), texID);
    glDeleteTextures(1, &texID);
    m_texID.erase(id);
}

//set the current texture
void TextureManager::BindTexture(const unsigned int texID)
{
    glBindTexture(GL_TEXTURE_2D, texID);
}

//free all texture memory
void TextureManager::UnloadAllTextures()
{
    //start at the begginning of the texture map
    auto i = m_texID.begin();

    while (m_texID.size() != 0)
    {
        glDeleteTextures(1, &m_texID[0]);
        m_texID.erase(m_texID.begin());
    }

    //clear the texture map
    m_texID.clear();
}

TextureManager::TextureManager()
{
    // call this ONLY when linking with FreeImage as a static library
    //#ifdef FREEIMAGE_LIB
    //FreeImage_Initialise();
    //#endif
    m_inst = nullptr;
}

TextureManager::TextureManager(const TextureManager& tm)
{
    if (!m_inst)
        m_inst = new TextureManager();
    m_texID.clear();
}