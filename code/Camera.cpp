/* --------------------------------------------------------------------------------
 *
 *  Implementation of a rotation-matrix based camera.
 *
 *  Rotation:
 *      R' = Rrot * Rold
 *
 *  Translation:
 *      T = dist * R[3][*] + Told
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdio>
#include "Camera.h"

const double PI = 3.1415965;

void Camera::init(double _fovy, double _near, double _far)
{
    translation.set_coords(0.0, 0.0, 0.0);

    rotation_matrix = new_square_matrix(3);
    init_with_identity(rotation_matrix);
    rotation_matrix[0][0] = -1.0;

    fovy = _fovy;
    near = _near;
    far = _far;
}

void Camera::setup_position(double x, double y, double z)
{
    translation.set_coords(x, y, z);
}

void Camera::look() const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fovy, fAspect, near, far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLoadMatrixd(create_view_matrix());
}

double * Camera::create_view_matrix() const
{
    double * transform_matrix = new double [16];

    transform_matrix[0] = rotation_matrix[0][0];
    transform_matrix[1] = rotation_matrix[1][0];
    transform_matrix[2] = rotation_matrix[2][0];
    transform_matrix[3] = 0.0;

    transform_matrix[4] = rotation_matrix[0][1];
    transform_matrix[5] = rotation_matrix[1][1];
    transform_matrix[6] = rotation_matrix[2][1];
    transform_matrix[7] = 0.0;

    transform_matrix[8] = rotation_matrix[0][2];
    transform_matrix[9] = rotation_matrix[1][2];
    transform_matrix[10] = rotation_matrix[2][2];
    transform_matrix[11] = 0.0;

    transform_matrix[15] = 1.0;

    Vector3D first_row = Vector3D(rotation_matrix[0][0], rotation_matrix[0][1], rotation_matrix[0][2]);
    Vector3D second_row = Vector3D(rotation_matrix[1][0], rotation_matrix[1][1], rotation_matrix[1][2]);
    Vector3D third_row = Vector3D(rotation_matrix[2][0], rotation_matrix[2][1], rotation_matrix[2][2]);

    transform_matrix[12] = first_row.dot_product(translation);
    transform_matrix[13] = second_row.dot_product(translation);
    transform_matrix[14] = third_row.dot_product(translation);

    return transform_matrix;
}

void Camera::update_rotation(double **rel_rotation)
{
    double **updated_matrix = multiply_matrices(rel_rotation, rotation_matrix, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rotation_matrix[i][j] = updated_matrix[i][j];
        }
    }
}

void Camera::rot_up_down(double angle)
{
    double rad_angle = angle*PI/180.0;
    double **relative_rot_matrix = new_square_matrix(3);

    init_with_identity(relative_rot_matrix);

    relative_rot_matrix[1][1] = cos(rad_angle);
    relative_rot_matrix[1][2] = -sin(rad_angle);
    relative_rot_matrix[2][1] = sin(rad_angle);
    relative_rot_matrix[2][2] = cos(rad_angle);

    update_rotation(relative_rot_matrix);
}

void Camera::rot_left_right(double angle)
{
    double rad_angle = angle*PI/180.0;
    double **relative_rot_matrix = new_square_matrix(3);

    init_with_identity(relative_rot_matrix);

    relative_rot_matrix[0][0] = cos(rad_angle);
    relative_rot_matrix[0][2] = sin(rad_angle);
    relative_rot_matrix[2][0] = -sin(rad_angle);
    relative_rot_matrix[2][2] = cos(rad_angle);

    update_rotation(relative_rot_matrix);
}

void Camera::rot_roll(double angle)
{
    double rad_angle = angle*PI/180.0;
    double **relative_rot_matrix = new_square_matrix(3);

    init_with_identity(relative_rot_matrix);

    relative_rot_matrix[0][0] = cos(rad_angle);
    relative_rot_matrix[0][1] = -sin(rad_angle);
    relative_rot_matrix[1][0] = sin(rad_angle);
    relative_rot_matrix[1][1] = cos(rad_angle);

    update_rotation(relative_rot_matrix);
}

void Camera::move_left_right(double dist)
{
    translation.set_coords(
            translation.x + (-dist)*rotation_matrix[0][0],
            translation.y + (-dist)*rotation_matrix[0][1],
            translation.z + (-dist)*rotation_matrix[0][2]);
}

void Camera::move_forward_back(double dist)
{
    translation.set_coords(
            translation.x + (-dist)*rotation_matrix[2][0],
            translation.y + (-dist)*rotation_matrix[2][1],
            translation.z + (-dist)*rotation_matrix[2][2]);
}

void Camera::move_up_down(double dist)
{
    translation.set_coords(
            translation.x + (-dist)*rotation_matrix[1][0],
            translation.y + (-dist)*rotation_matrix[1][1],
            translation.z + (-dist)*rotation_matrix[1][2]);
}

double ** Camera::new_square_matrix(int dimension)
{
    double **matrix;

    matrix = new double* [dimension];
    for (int i = 0; i < dimension; i++)
        matrix[i] = new double[dimension];

    return matrix;
}

void Camera::init_with_identity(double **mat3x3)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
                mat3x3[i][j] = 1.0;
            else
                mat3x3[i][j] = 0.0;
        }
    }
}

double ** Camera::multiply_matrices(double **mat1, double **mat2, int dimension)
{
    double **result = new_square_matrix(dimension);

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < dimension; k++)
            {
                sum += mat1[i][k] * mat2[k][j];
            }

            result[i][j] = sum;
        }
    }

    return result;
}
