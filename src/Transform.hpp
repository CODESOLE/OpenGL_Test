#pragma once
#include "renderer.hpp"

class Transform
{
public:
    static void TranslateX(glm::mat4 &, const float &);
    static void TranslateY(glm::mat4 &, const float &);
    static void TranslateZ(glm::mat4 &, const float &);
    static void TranslateXY(glm::mat4 &, const float &, const float &);
    static void TranslateYZ(glm::mat4 &, const float &, const float &);
    static void TranslateXZ(glm::mat4 &, const float &, const float &);
    static void TranslateXYZ(glm::mat4 &, const float &, const float &, const float &);

    static void RotateX(glm::mat4 &, const float &);
    static void RotateY(glm::mat4 &, const float &);
    static void RotateZ(glm::mat4 &, const float &);
    static void RotateXY(glm::mat4 &, const float &, const float &);
    static void RotateYZ(glm::mat4 &, const float &, const float &);
    static void RotateXZ(glm::mat4 &, const float &, const float &);
    static void RotateXYZ(glm::mat4 &, const float &, const float &, const float &);

    static void ScaleX(glm::mat4 &, const float &);
    static void ScaleY(glm::mat4 &, const float &);
    static void ScaleZ(glm::mat4 &, const float &);
    static void ScaleXY(glm::mat4 &, const float &, const float &);
    static void ScaleYZ(glm::mat4 &, const float &, const float &);
    static void ScaleXZ(glm::mat4 &, const float &, const float &);
    static void ScaleXYZ(glm::mat4 &, const float &, const float &, const float &);
};
