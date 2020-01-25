#include "Texture.hpp"
#include "./../dep/stb_image/stb_image.hpp"

Texture::Texture(const char *filePath)
    : m_RendererID(0), m_filePath(filePath), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(true);
    m_localBuffer = stbi_load(m_filePath, &m_width, &m_height, &m_BPP, 4);
    GLErrCall(glGenTextures(1, &m_RendererID));
    GLErrCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    GLErrCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLErrCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLErrCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLErrCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLErrCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    GLErrCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_localBuffer)
        stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
    GLErrCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLErrCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLErrCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
    GLErrCall(glBindTexture(GL_TEXTURE_2D, 0));
}
