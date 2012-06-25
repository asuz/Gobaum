#include <cmath>
#include <cstdio>
#include <string>
#include "Vector3D.h"

using namespace std;

// Construtores
Vector3D::Vector3D(const double nx, const double ny, const double nz)
{
    x = nx;
    y = ny;
    z = nz;
}

void Vector3D::set_coords(const double nx, const double ny, const double nz)
{
    x = nx;
    y = ny; 
    z = nz;
}

// Operações booleanas
bool Vector3D::operator==(const Vector3D &a) const
{
    return (x == a.x && y == a.y && z == a.z);
}

bool Vector3D::operator!=(const Vector3D &a) const
{
    return !(x == a.x && y == a.y && z == a.z);
}

// Operações diversas
void Vector3D::set_to_zero()
{
    x = y = z = 0;
}

Vector3D Vector3D::negate() const
{
    return Vector3D(-x, -y, -z);
}

// Soma e subtração vetorial
Vector3D Vector3D::operator+(const Vector3D &a) const
{
    return Vector3D(x + a.x, y + a.y, z + a.z);
}

Vector3D Vector3D::operator-(const Vector3D &a) const
{
    return Vector3D(x - a.x, y - a.y, z - a.z);
}

Vector3D & Vector3D::operator+=(const Vector3D &a)
{
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}

Vector3D & Vector3D::operator-=(const Vector3D &a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}

// Multiplicação e divisão por escalar
Vector3D Vector3D::operator*(const double a) const
{
    return Vector3D(x*a, y*a, z*a);
}

Vector3D Vector3D::operator/(const double a) const
{
    double inv = 1.0/a;
    return Vector3D(x*inv, y*inv, z*inv);
}

Vector3D & Vector3D::operator*=(const double a)
{
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vector3D & Vector3D::operator/=(const double a)
{
    double inv = 1.0/a;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

double Vector3D::norm() const
{
    return sqrt(x*x + y*y + z*z);
}

// Normaliza o vetor
void Vector3D::normalize()
{
    double magSq = x*x + y*y + z*z;
    if (magSq > 0.0)
    {
        double inv = 1.0 / sqrt(magSq);
        x *= inv;
        y *= inv;
        z *= inv;
    }
}

// Produto interno
double Vector3D::dot_product(const Vector3D &a) const
{
    return x*a.x + y*a.y + z*a.z;
}

// Produto vetorial
Vector3D Vector3D::cross_product(const Vector3D &a) const
{
    return Vector3D(y*a.z - z*a.y,
                    z*a.x - x*a.z,
                    x*a.y - y*a.x);
}

void Vector3D::print(string msg) const
{
    printf(msg.c_str());
    printf("(%f, %f, %f)\n", x, y, z);
}
