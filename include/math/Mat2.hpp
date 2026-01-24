#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include<cassert>
#include<iostream>
#include "Vec2.hpp"

namespace math{
    struct Mat2{
        float m00, m01;
        float m10, m11;

        Mat2(){ //行列の初期化
            m00 = 0; m01 = 0;
            m10 = 0; m11 = 0;
        } 

        Mat2(float v00, float v01, float v10, float v11){ //行列の代入
            m00 = v00; m01 = v01;
            m10 = v10; m11 = v11;
        }

        Mat2 operator+(const Mat2& rhs) const{ //行列の足し算
            return {m00 + rhs.m00, m01 + rhs.m01, m10 + rhs.m10, m11 + rhs.m11};
        }

        Mat2 operator-(const Mat2& rhs) const{ //行列の引き算
            return {m00 - rhs.m00, m01 - rhs.m01, m10 - rhs.m10, m11 - rhs.m11};
        }

        Mat2 operator*(const Mat2& rhs) const{ //行列の積
            return {
                m00*rhs.m00 + m01*rhs.m10,
                m00*rhs.m01 + m01*rhs.m11,
                m10*rhs.m00 + m11*rhs.m10,
                m10*rhs.m01 + m11*rhs.m11
            };
        }

        Vec2 operator*(const Vec2& v) const{ //行列×ベクトル
            return {m00*v.x + m01*v.y, m10*v.x + m11*v.y};
        }

        Mat2 operator*(const float& s) const{ //行列の定数倍
            return {s*m00, s*m01, s*m10, s*m11};
        }

        Mat2 operator/(const float& s) const{ //行列の定数での割り算
            assert(std::abs(s)>1e-8f);
            return {m00/s, m01/s, m10/s, m11/s};
        }

        static Mat2 id(){ return {1,0,0,1}; } //単位行列
        static Mat2 zeros(){ return {0,0,0,0}; } //ゼロ行列
        static Mat2 ones(){ return {1,1,1,1}; } //成分がすべて1の行列

        static Mat2 rotation(float deg){ //回転行列
            float theta = deg * M_PI / 180.0f;
            float c = std::cos(theta);
            float s = std::sin(theta);
            if (std::abs(c) < 1e-6) { c = 0.0f; }
            if (std::abs(s) < 1e-6) { s = 0.0f; }
            return {c, -s, s, c};
        }

        static Mat2 adamar(const Mat2& A, const Mat2& B){ //アダマール積
            return {
                A.m00 * B.m00, A.m01 * B.m01,
                A.m10 * B.m10, A.m11 * B.m11
            };
        }

        static Mat2 scale(float sx, float sy){ //スケール行列
            return {sx, 0, 0, sy};
        }

        Mat2 transpose() const{ //転置
            return {m00, m10, m01, m11};
        }

        Mat2 inverse() const{ //逆行列
            float d = det();
            assert(std::abs(d)>1e-8f);
            return {m11/d, -m01/d, -m10/d, m00/d};
        }

        float det() const{ //行列式
            return m00*m11 - m01*m10;
        }

        float trace() const{ //トレース
            return m00 + m11;
        }

        float rotationAngleDeg() const{ //行列の回転角(度数法)
            return std::atan2(m10, m00) * 180.0f / M_PI;
        }

        float rotationAngleRad() const{ //行列の回転角(弧度法)
            return std::atan2(m10, m00);
        }


        void print() const{ //標準出力に行列を表示
            std::cout << m00 << " " << m01 << "\n";
            std::cout << m10 << " " << m11 << "\n";
        }


    }; 
}