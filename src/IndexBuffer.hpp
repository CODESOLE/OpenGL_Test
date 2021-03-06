#pragma once

class IndexBuffer
{
private:
    unsigned int m_RenderID;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int *data, unsigned int m_Count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount() const { return m_Count; };
};
