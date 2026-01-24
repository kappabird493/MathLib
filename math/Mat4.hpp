#pragma once
#include<cmath>
#include<cassert>
#include<iostream>
#include "Vec4.hpp"

namespace math{
    struct Mat4{
        float m[4][4];

        Mat4(){ //行列の初期化
            m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
            m[1][0] = 0; m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
            m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
            m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
        }

        Mat4(float v00, float v01, float v02, float v03,
         float v10, float v11, float v12, float v13,
         float v20, float v21, float v22, float v23,
         float v30 ,float v31, float v32, float v33){ //行列の代入
            m[0][0] = v00; m[0][1] = v01; m[0][2] = v02; m[0][3] = v03;
            m[1][0] = v10; m[1][1] = v11; m[1][2] = v12; m[1][3] = v13;
            m[2][0] = v20; m[2][1] = v21; m[2][2] = v22; m[2][3] = v23;
            m[3][0] = v30; m[3][1] = v31; m[3][2] = v32; m[3][3] = v33;
        }

        Mat4 operator+(const Mat4& rhs) const{　//行列の足し算
            Mat4 r;
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    r.m[i][j] = m[i][j] + rhs.m[i][j];
                }
            }
            return r;
        }

        Mat4 operator-(const Mat4& rhs) const{ //行列の引き算
            Mat4 r;
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    r.m[i][j] = m[i][j] - rhs.m[i][j];
                }
            }
            return r;
        }

        Mat4 operator*(const Mat4& rhs) const{ //行列の積
            Mat4 r;
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    r.m[i][j] = m[i][0]*rhs.m[0][j] + m[i][1]*rhs.m[1][j] + m[i][2]*rhs.m[2][j] + m[i][3]*rhs.m[3][j];
                }
            }
            return r;
        }

        Vec4 operator*(const Vec4& v) const{ //行列×ベクトル
            return {m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3]*v.w, m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3]*v.w, m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3]*v.w, m[3][0]*v.x + m[3][1]*v.y + m[3][2]*v.z + m[3][3]*v.w};
        }

        Mat4 operator*(const float& s) const{ //行列の定数倍
            Mat4 r;
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    r.m[i][j] = m[i][j]*s;
                }
            }
            return r;
        }

        Mat4 operator/(const float& s) const{ //行列の定数での割り算
            assert(std::abs(s)>1e-8f);
            Mat4 r;
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    r.m[i][j] = m[i][j]/s;
                }
            }
            return r;
        }

        static Mat4 id(){ //単位行列
            return Mat4(
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );
        }
        
        static Mat4 zeros(){ //ゼロ行列
            return Mat4(
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
            );
        }

        static Mat4 ones(){ //成分が全て1の行列
            return Mat4(
                1, 1, 1, 1,
                1, 1, 1, 1, 
                1, 1, 1, 1,
                1, 1, 1, 1
            );
        }

        static Mat4 adamar(const Mat4& A, const Mat4& B){ //アダマール積
            Mat4 r;
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    r.m[i][j] = A.m[i][j]*B.m[i][j];
                }
            }
            return r;
        }

        static Mat4 scale(float sx, float sy, float sz){ //スケール行列
            return Mat4(
                sx, 0, 0, 0,
                0, sy, 0, 0,
                0, 0, sz, 0,
                0, 0, 0, 1
            );
        }

        Mat4 transpose() const{ //転置
            return Mat4(
                m[0][0], m[1][0], m[2][0], m[3][0],
                m[0][1], m[1][1], m[2][1], m[3][1],
                m[0][2], m[1][2], m[2][2], m[3][2],
                m[0][3], m[1][3], m[2][3], m[3][3]
            );
        }

        Mat4 inverse() const{ //逆行列
            float d = det();
            assert(std::abs(d) > 1e-8f);
            
            Mat4 cof;
            
            const float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], a03 = m[0][3];
            const float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3];
            const float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3];
            const float a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3];
            
            cof.m[0][0] =  det3(a11,a12,a13,a21,a22,a23,a31,a32,a33);
            cof.m[0][1] = -det3(a10,a12,a13,a20,a22,a23,a30,a32,a33);
            cof.m[0][2] =  det3(a10,a11,a13,a20,a21,a23,a30,a31,a33);
            cof.m[0][3] = -det3(a10,a11,a12,a20,a21,a22,a30,a31,a32);
            
            cof.m[1][0] = -det3(a01,a02,a03,a21,a22,a23,a31,a32,a33);
            cof.m[1][1] =  det3(a00,a02,a03,a20,a22,a23,a30,a32,a33);
            cof.m[1][2] = -det3(a00,a01,a03,a20,a21,a23,a30,a31,a33);
            cof.m[1][3] =  det3(a00,a01,a02,a20,a21,a22,a30,a31,a32);

            cof.m[2][0] =  det3(a01,a02,a03,a11,a12,a13,a31,a32,a33);
            cof.m[2][1] = -det3(a00,a02,a03,a10,a12,a13,a30,a32,a33);
            cof.m[2][2] =  det3(a00,a01,a03,a10,a11,a13,a30,a31,a33);
            cof.m[2][3] = -det3(a00,a01,a02,a10,a11,a12,a30,a31,a32);

            cof.m[3][0] = -det3(a01,a02,a03,a11,a12,a13,a21,a22,a23);
            cof.m[3][1] =  det3(a00,a02,a03,a10,a12,a13,a20,a22,a23);
            cof.m[3][2] = -det3(a00,a01,a03,a10,a11,a13,a20,a21,a23);
            cof.m[3][3] =  det3(a00,a01,a02,a10,a11,a12,a20,a21,a22);

            Mat4 adj = cof.transpose();
            return adj / d;
        }


        static float det3( //3次の行列式
            float a00, float a01, float a02,
            float a10, float a11, float a12,
            float a20, float a21, float a22)
            {
                return a00*(a11*a22 - a12*a21) - a01*(a10*a22 - a12*a20) + a02*(a10*a21 - a11*a20);
            }

        float det() const{ //4次の行列式
            const float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], a03 = m[0][3];
            const float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3];
            const float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3];
            const float a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3];
            
            return
            a00 * det3(a11, a12, a13, a21, a22, a23, a31, a32, a33)
            - a01 * det3(a10, a12, a13, a20, a22, a23, a30, a32, a33)
            + a02 * det3(a10, a11, a13, a20, a21, a23, a30, a31, a33)
            - a03 * det3(a10, a11, a12, a20, a21, a22, a30, a31, a32);
        }


        float trace() const{ //トレース
            return m[0][0] + m[1][1] + m[2][2] + m[3][3];
        }

        void print() const{ //標準出力に行列を表示
            std::cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << "\n";
            std::cout << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << "\n";
            std::cout << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << "\n";
            std::cout << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << "\n";
        }
    }; 
}