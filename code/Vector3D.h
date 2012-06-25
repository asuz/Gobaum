#ifndef __VECTOR3D__H__
#define __VECTOR3D__H__

#include <string>


class Vector3D
{
    public:
        double x, y, z;

        // Construtores
        Vector3D() {}
        Vector3D(const double nx, const double ny, const double nz);

        void set_coords(const double nx, const double ny, const double nz);

        // Operações booleanas
        bool operator==(const Vector3D &a) const;
        bool operator!=(const Vector3D &a) const;

        // Operações diversas
        void set_to_zero();
        Vector3D negate() const;

        // Soma e subtração vetorial
        Vector3D operator+(const Vector3D &a) const;
        Vector3D operator-(const Vector3D &a) const;
        Vector3D & operator+=(const Vector3D &a);
        Vector3D & operator-=(const Vector3D &a);

        // Multiplicação e divisão por escalar
        Vector3D operator*(const double a) const;
        Vector3D operator/(const double a) const;
        Vector3D & operator*=(const double a);
        Vector3D & operator/=(const double a);
        
        // Norma
        double norm() const;

        // Normaliza o vetor
        void normalize();

        // Produto interno
        double dot_product(const Vector3D &a) const;

        // Produto vetorial
        Vector3D cross_product(const Vector3D &a) const;

        // Imprime vetor (com uma string anterior)
        void print(std::string msg) const;
};

#endif
