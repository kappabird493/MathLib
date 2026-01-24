#pragma once
#include<cmath>
#include<cassert>
#include<iostream>
#include "Vec3.hpp"

namespace math{
    struct Mat3{
        float m[3][3];

        Mat3(){ //行列の初期化
            m[0][0] = 0; m[0][1] = 0; m[0][2] = 0;
            m[1][0] = 0; m[1][1] = 0; m[1][2] = 0;
            m[2][0] = 0; m[2][1] = 0; m[2][2] = 0;
        }

        Mat3(float v00, float v01, float v02,
         float v10, float v11, float v12,
         float v20, float v21, float v22){ //行列の代入
            m[0][0] = v00; m[0][1] = v01; m[0][2] = v02;
            m[1][0] = v10; m[1][1] = v11; m[1][2] = v12;
            m[2][0] = v20; m[2][1] = v21; m[2][2] = v22;
        }

        Mat3 operator+(const Mat3& rhs) const{ //行列の足し算
            Mat3 r;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    r.m[i][j] = m[i][j] + rhs.m[i][j];
                }
            }
            return r;
        }

        Mat3 operator-(const Mat3& rhs) const{ //行列の引き算
            Mat3 r;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    r.m[i][j] = m[i][j] - rhs.m[i][j];
                }
            }
            return r;
        }

        Mat3 operator*(const Mat3& rhs) const{ //行列の積
            Mat3 r;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    r.m[i][j] = m[i][0]*rhs.m[0][j] + m[i][1]*rhs.m[1][j] + m[i][2]*rhs.m[2][j];
                }
            }
            return r;
        }

        Vec3 operator*(const Vec3& v) const{ //行列×ベクトル
            return {m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z, m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z, m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z};
        }

        Mat3 operator*(const float& s) const{  //行列の定数倍
            Mat3 r;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    r.m[i][j] = m[i][j]*s;
                }
            }
            return r;
        }

        Mat3 operator/(const float& s) const{ //行列の定数での割り算
            assert(std::abs(s)>1e-8f);
            Mat3 r;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    r.m[i][j] = m[i][j]/s;
                }
            }
            return r;
        }

        static Mat3 id(){ //単位行列
            return Mat3(
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
            );
        }
        
        static Mat3 zeros(){ //ゼロ行列
            return Mat3(
                0, 0, 0,
                0, 0, 0,
                0, 0, 0
            );
        }

        static Mat3 ones(){ //成分が全て1の行列
            return Mat3(
                1, 1, 1,
                1, 1, 1,
                1, 1, 1
            );
        }

        static Mat3 adamar(const Mat3& A, const Mat3& B){ //アダマール積
            Mat3 r;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    r.m[i][j] = A.m[i][j]*B.m[i][j];
                }
            }
            return r;
        }

        static Mat3 scale(float sx, float sy, float sz){ //スケール行列
            return Mat3(
                sx, 0, 0,
                0, sy, 0,
                0, 0, sz
            );
        }

        Mat3 transpose() const{ //転置
            return Mat3(
                m[0][0], m[1][0], m[2][0],
                m[0][1], m[1][1], m[2][1],
                m[0][2], m[1][2], m[2][2]
            );
        }

        Mat3 inverse() const{ //逆行列
            float d = det();
            assert(std::abs(d)>1e-8f);

            Mat3 r;
            
            r.m[0][0] =  (m[1][1]*m[2][2] - m[1][2]*m[2][1]);
            r.m[0][1] = -(m[0][1]*m[2][2] - m[0][2]*m[2][1]);
            r.m[0][2] =  (m[0][1]*m[1][2] - m[0][2]*m[1][1]);

            r.m[1][0] = -(m[1][0]*m[2][2] - m[1][2]*m[2][0]);
            r.m[1][1] =  (m[0][0]*m[2][2] - m[0][2]*m[2][0]);
            r.m[1][2] = -(m[0][0]*m[1][2] - m[0][2]*m[1][0]);

            r.m[2][0] =  (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
            r.m[2][1] = -(m[0][0]*m[2][1] - m[0][1]*m[2][0]);
            r.m[2][2] =  (m[0][0]*m[1][1] - m[0][1]*m[1][0]);
            
            return r / d;
        }

        float det() const{ //行列式
            return m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0] + m[0][2]*m[1][0]*m[2][1] - m[0][2]*m[1][1]*m[2][0] - m[0][1]*m[1][0]*m[2][2] - m[0][0]*m[1][2]*m[2][1];
        }

        float trace() const{ //トレース
            return m[0][0] + m[1][1] + m[2][2];
        }

        void print() const{ //標準出力に行列を表示
            std::cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << "\n";
            std::cout << m[1][0] << " " << m[1][1] << " " << m[1][2] << "\n";
            std::cout << m[2][0] << " " << m[2][1] << " " << m[2][2] << "\n";
        }
    }; 
}