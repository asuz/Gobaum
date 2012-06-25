#ifndef __CAMERA__H__
#define __CAMERA__H__

#include "Vector3D.h"

class Camera
{
    public:
        Vector3D translation;
        double **rotation_matrix;
        double fovy, near, far;

        void init(double _fovy, double _near, double _far);
        void setup_position(double x, double y, double z);

        double fAspect;

        Camera() {}

        void look() const;

        void rot_up_down(double angle);
        void rot_left_right(double angle);
        void rot_roll(double angle);
        void move_forward_back(double dist);
        void move_left_right(double dist);
        void move_up_down(double dist);

        double *create_view_matrix() const;

        void update_rotation(double **rel_rotation);

    //---------------- non-member functions --------------------------
        double **new_square_matrix(int dimension);
        void init_with_identity(double **mat3x3);
        double **multiply_matrices(double **mat1, double **mat2, int dimension);
};

#endif
