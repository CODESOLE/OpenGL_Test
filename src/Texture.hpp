#pragma once
#include "renderer.hpp"

class Texture
{
private:
    unsigned int m_RendererID;
    const char *m_filePath;
    unsigned char *m_localBuffer;
    int m_width, m_height, m_BPP; //BBP => BYTE PER PIXEL

public:
    Texture(const char *filePath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void UnBind() const;

    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }
    inline int GetBPP() const { return m_BPP; }
};