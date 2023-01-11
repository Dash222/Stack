#pragma once

template <typename T>
struct vector2
{
    T x;
    T y;
};


typedef vector2<float> vector2f;
typedef vector2<double> vector2d;

template <typename T>
struct vector3
{
    T x;
    T y;
    T z;
};


typedef vector3<float> vector3f;
typedef vector3<double> vector3d;