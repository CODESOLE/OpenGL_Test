#include "Transform.hpp"

void Transform::TranslateX(glm::mat4 &mat, const float &val)
{
    mat = glm::translate(glm::mat4(1.f), glm::vec3(val, 0.f, 0.f));
}

void Transform::TranslateY(glm::mat4 &mat, const float &val)
{
    mat = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, val, 0.f));
}

void Transform::TranslateZ(glm::mat4 &mat, const float &val)
{
    mat = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, val));
}

void Transform::TranslateXY(glm::mat4 &mat, const float &valx, const float &valy)
{
    mat = glm::translate(glm::mat4(1.f), glm::vec3(valx, valy, 0.f));
}

void Transform::TranslateYZ(glm::mat4 &mat, const float &valy, const float &valz)
{
    mat = glm::translate(glm::mat4(1.f), glm::vec3(0.f, valy, valz));
}

void Transform::TranslateXZ(glm::mat4 &mat, const float &valx, const float &valz)
{
    mat = glm::translate(glm::mat4(1.f), glm::vec3(valx, 0.f, valz));
}

void Transform::TranslateXYZ(glm::mat4 &mat, const float &valx, const float &valy, const float &valz)
{
    mat = glm::translate(glm::mat4(1.f), glm::vec3(valx, valy, valz));
}

void Transform::RotateX(glm::mat4 &mat, const float &val)
{
    mat = glm::rotate(mat, glm::radians(val), glm::vec3(1.f, 0.f, 0.f));
}

void Transform::RotateY(glm::mat4 &mat, const float &val)
{
    mat = glm::rotate(mat, glm::radians(val), glm::vec3(0.0f, 1.f, 0.f));
}

void Transform::RotateZ(glm::mat4 &mat, const float &val)
{
    mat = glm::rotate(mat, glm::radians(val), glm::vec3(0.f, 0.f, 1.0f));
}

void Transform::RotateXY(glm::mat4 &mat, const float &valx, const float &valy)
{
    mat = glm::rotate(mat, glm::radians(valx), glm::vec3(1.f, 0.f, 0.f));
    mat = glm::rotate(mat, glm::radians(valy), glm::vec3(0.0f, 1.f, 0.f));
}

void Transform::RotateYZ(glm::mat4 &mat, const float &valy, const float &valz)
{
    mat = glm::rotate(mat, glm::radians(valy), glm::vec3(0.0f, 1.f, 0.f));
    mat = glm::rotate(mat, glm::radians(valz), glm::vec3(0.f, 0.f, 1.0f));
}

void Transform::RotateXZ(glm::mat4 &mat, const float &valx, const float &valz)
{
    mat = glm::rotate(mat, glm::radians(valx), glm::vec3(1.f, 0.f, 0.f));
    mat = glm::rotate(mat, glm::radians(valz), glm::vec3(0.f, 0.f, 1.0f));
}

void Transform::RotateXYZ(glm::mat4 &mat, const float &valx, const float &valy, const float &valz)
{
    mat = glm::rotate(mat, glm::radians(valx), glm::vec3(1.f, 0.f, 0.f));
    mat = glm::rotate(mat, glm::radians(valy), glm::vec3(0.0f, 1.f, 0.f));
    mat = glm::rotate(mat, glm::radians(valz), glm::vec3(0.f, 0.f, 1.0f));
}

void Transform::ScaleX(glm::mat4 &mat, const float &val)
{
    mat = glm::scale(mat, glm::vec3(val, 1.f, 1.f));
}

void Transform::ScaleY(glm::mat4 &mat, const float &val)
{
    mat = glm::scale(mat, glm::vec3(1.0f, val, 1.f));
}

void Transform::ScaleZ(glm::mat4 &mat, const float &val)
{
    mat = glm::scale(mat, glm::vec3(1.f, 1.f, val));
}

void Transform::ScaleXY(glm::mat4 &mat, const float &valx, const float &valy)
{
    mat = glm::scale(mat, glm::vec3(valx, valy, 1.f));
}

void Transform::ScaleYZ(glm::mat4 &mat, const float &valy, const float &valz)
{
    mat = glm::scale(mat, glm::vec3(1.0f, valy, valz));
}

void Transform::ScaleXZ(glm::mat4 &mat, const float &valx, const float &valz)
{
    mat = glm::scale(mat, glm::vec3(valx, 1.f, valz));
}

void Transform::ScaleXYZ(glm::mat4 &mat, const float &valx, const float &valy, const float &valz)
{
    mat = glm::scale(mat, glm::vec3(valx, valy, valz));
}