/**
 * I am yet to Implement Strassen's Matrix Multiplication.
*/

#include <random>
#include <time.h>
#include "matrix.h"

int pow2roundup (int x) {
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}

template<class T>
Mat2d<T> matMult(const Mat2d<T>& mat1, const Mat2d<T>& mat2) {
    assert(mat1.getn() == mat2.getm());
    auto mat = Mat2d<T>(mat1.getm(), mat2.getn());
    for(int i = 0; i < mat1.getm(); i++) {
        for(int j = 0; j < mat2.getn(); j++) {
            for(int k = 0; k < mat1.getn(); k++) {
                mat.set(i, j, mat.get(i, j) + mat1.get(i, k) * mat2.get(k, j));
            }
        }
    }
    return mat;
}

template<class T>
Mat2d<T> matMult(Mat2d<T>& mat1, Mat2d<T>& mat2, Mat2d<T>& mat) {
    assert(mat1.getn() == mat2.getm());
    assert((mat1.getm() == mat.getm()) && (mat2.getn() == mat.getn()));
    if(mat1.isZero() || mat2.isZero()) {
        return mat;
    }
    for(int i = 0; i < mat1.getm(); i++) {
        for(int j = 0; j < mat2.getn(); j++) {
            for(int k = 0; k < mat1.getn(); k++) {
                mat.set(i, j, mat.get(i, j) + mat1.get(i, k) * mat2.get(k, j));
            }
        }
    }
    return mat;
}

// template<class T>
// Mat2d<T> fmm(Mat2d<T> mat1, Mat2d<T> mat2) {
//     assert(mat1.getn() == mat2.getm());
//     auto mat = Mat2d<T>(mat1.getm(), mat2.getn());
//     if (mat1.getn() > 8 && mat1.getm() > 8 && mat2.getn() > 8) {
//         auto A11 = mat1.createSubMat(0,0,mat1.getm()/2,mat1.getn()/2);
//         auto A12 = mat1.createSubMat(0,mat1.getn()/2,mat1.getm()/2,mat1.getn()/2);
//         auto A21 = mat1.createSubMat(mat1.getm()/2,0,mat1.getm()/2,mat1.getn()/2);
//         auto A22 = mat1.createSubMat(mat1.getm()/2,mat1.getn()/2,mat1.getm()/2,mat1.getn()/2);
//         auto B11 = mat2.createSubMat(0,0,mat2.getm()/2,mat2.getn()/2);
//         auto B12 = mat2.createSubMat(0,mat2.getn()/2,mat2.getm()/2,mat2.getn()/2);
//         auto B21 = mat2.createSubMat(mat2.getm()/2,0,mat2.getm()/2,mat2.getn()/2);
//         auto B22 = mat2.createSubMat(mat2.getm()/2,mat2.getn()/2,mat2.getm()/2,mat2.getn()/2);
//         auto P1 = fmm(A11 + A22, B11 + B22);
//         auto P2 = fmm(A21 + A22, B11);
//         auto P3 = fmm(A11      , B12 - B22);
//         auto P4 = fmm(A22      , B21 - B11);
//         auto P5 = fmm(A11 + A12, B22);
//         auto P6 = fmm(A21 - A11, B11 + B12);
//         auto P7 = fmm(A12 + A22, B21 + B22);
//         mat.emplaceSubMat(P1 + P4 - P5 + P7, 0, 0);
//         mat.emplaceSubMat(P3 + P3, 0, mat.getn()/2);
//         mat.emplaceSubMat(P2 + P4, mat.getm()/2, 0);
//         mat.emplaceSubMat(P1 - P2 + P3 + P6, mat.getm()/2, mat.getn()/2);
//         return mat;
//     }
//     else {
//         return matMult(mat1, mat2, mat);
//     }
// }

// template<class T>
// Mat2d<T> fmm(Mat2d<T>& mat1, Mat2d<T>& mat2, Mat2d<T>& mat) {
//     assert(mat1.getn() == mat2.getm());
//     if (mat1.getn() > 8 && mat1.getm() > 8 && mat2.getn() > 8) {
//         auto A11 = mat1.createSubMat(0,0,mat1.getm()/2,mat1.getn()/2);
//         auto A12 = mat1.createSubMat(0,mat1.getn()/2,mat1.getm()/2,mat1.getn()/2);
//         auto A21 = mat1.createSubMat(mat1.getm()/2,0,mat1.getm()/2,mat1.getn()/2);
//         auto A22 = mat1.createSubMat(mat1.getm()/2,mat1.getn()/2,mat1.getm()/2,mat1.getn()/2);
//         auto B11 = mat2.createSubMat(0,0,mat2.getm()/2,mat2.getn()/2);
//         auto B12 = mat2.createSubMat(0,mat2.getn()/2,mat2.getm()/2,mat2.getn()/2);
//         auto B21 = mat2.createSubMat(mat2.getm()/2,0,mat2.getm()/2,mat2.getn()/2);
//         auto B22 = mat2.createSubMat(mat2.getm()/2,mat2.getn()/2,mat2.getm()/2,mat2.getn()/2);
//         auto P1 = fmm(A11 + A22, B11 + B22);
//         auto P2 = fmm(A21 + A22, B11);
//         auto P3 = fmm(A11      , B12 - B22);
//         auto P4 = fmm(A22      , B21 - B11);
//         auto P5 = fmm(A11 + A12, B22);
//         auto P6 = fmm(A21 - A11, B11 + B12);
//         auto P7 = fmm(A12 + A22, B21 + B22);
//         mat.emplaceSubMat(P1 + P4 - P5 + P7, 0, 0);
//         mat.emplaceSubMat(P3 + P3, 0, mat.getn()/2);
//         mat.emplaceSubMat(P2 + P4, mat.getm()/2, 0);
//         mat.emplaceSubMat(P1 - P2 + P3 + P6, mat.getm()/2, mat.getn()/2);
//         return mat;
//     }
//     else {
//         return matMult(mat1, mat2, mat);
//     }
// }

int main() {
    std::cout << "================================================\n";
    std::cout << "TESTING DIFFERENT ALGO FOR MATRIX MULTIPLICATION\n";
    std::cout << "================================================\n\n";

    long mat1_vals[100];
    long mat2_vals[100];
    srand(time(0));
    for(int i = 0; i < 100; i++) {
        mat1_vals[i] = ((rand() % 200) - 100);// / (double)((rand() % 10) + 1);
        mat2_vals[i] = ((rand() % 200) - 100);// / (double)((rand() % 10) + 1);
    }
    auto mat1 = Mat2d<long>(7U, 10U, mat1_vals);
    auto mat2 = Mat2d<long>(10U, 6U, mat2_vals);

    mat1.print();
    mat2.print();
    matMult(mat1, mat2).print();
    // fmm(mat1, mat2).print();

    return 0;
}