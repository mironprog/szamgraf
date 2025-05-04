#include "matrix.h"

#include <stdio.h>
#include <math.h>

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        
        for (j = 0; j < 3; j++) {
            
            if (i == j) {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}

void scalar_multiplication(int scalar, float matrix[3][3]) 
{
    int i;
    int j;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] *= scalar;
        }
    }
}

float multiply_matrices(float matrix1[3][3], float matrix2[3][3], float result_matrix[3][3])
{
    
    int i;
    int j;

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++ ) {
            result_matrix[i][j]=matrix1[i][j] * matrix2[i][j];
        }
    }

    return result_matrix[3][3];
}

void transform_point(float matrix[3][3], const float point[3], float result_matrix[3]){

    int j;
    int i;
    for(i = 0; i < 3; i++){
        result_matrix[i] = 0;
        for(j = 0; j < 3; j++){
            result_matrix[i] = matrix[i][j] * point[j]; 
        }
    }
}

void scale(float matrix[3][3], const float x, const float y, float result_matrix[3][3])
{
    float transform[3][3];
    init_identity_matrix(transform);

    transform[0][0] = x;
    transform[1][1] = y;

    multiply_matrices(transform, matrix, result_matrix); 
}

void rotate(float matrix[3][3], const float angle, float result_matrix[3][3])
{
    float transform[3][3];
    init_identity_matrix(transform);

    transform[0][0] = transform[1][1] = cos(angle);
    transform[1][0] = sin(angle);
    transform[0][1] = -transform[1][0];

    multiply_matrices(transform, matrix, result_matrix);
}

void shift(float matrix[3][3], const float vector[2], float result_matrix[3][3])
{
    float transform[3][3];
    init_identity_matrix(transform);

    transform[0][2] = vector[0];
    transform[1][2] = vector[1];
    
    multiply_matrices(transform, matrix, result_matrix);
}