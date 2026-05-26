#pragma once
#include<cmath>
#include<cassert>

namespace math{
    struct Vec2 {
        float x, y;

        constexpr Vec2() : x(0), y(0) {}
        constexpr Vec2(float x, float y) : x(x), y(y) {}

        constexpr Vec2 operator+(const Vec2& rhs) const {
            return { x + rhs.x, y + rhs.y };
        }

        constexpr Vec2 operator-(const Vec2& rhs) const {
            return { x - rhs.x, y - rhs.y };
        }

        constexpr Vec2 operator*(float s) const {
            return { x * s, y * s };
        }

        Vec2 operator/(float s) const {
            constexpr float eps = 1e-6f;
            assert(std::abs(s) > eps);
            return { x / s, y / s };
        }

        float length() const { // 長さ
            return std::sqrt(x * x + y * y);
        }

        float sq_length() const { // 長さの二乗
            return x * x + y * y;
        }

        Vec2 normalized() const { // 正規化
            float len = length();
            assert(len > 0.0f);
            return *this / len;
        }

        Vec2 translation(float tx, float ty) { //平行移動
            return { x + tx, y + ty };
        }

        static constexpr float dot(const Vec2& lhs, const Vec2& rhs) { //内積
            return lhs.x * rhs.x + lhs.y * rhs.y;
        }

        static constexpr float cross(const Vec2& lhs, const Vec2& rhs) { //外積
            return lhs.x * rhs.y - lhs.y * rhs.x;
        }

        static constexpr Vec2 adamar(const Vec2& lhs, const Vec2& rhs) { //アダマール積
            return { lhs.x * rhs.x, lhs.y * rhs.y };
        }


        static float tri_area(const Vec2& a, const Vec2& b) { //2ベクトルの張る三角形の面積
            float la = a.length();
            float lb = b.length();
            return 0.5f * std::sqrt(la*la*lb*lb - dot(a, b)*dot(a, b));
        }

        static Vec2 orth_proj(const Vec2& a, const Vec2& b) { //bのaへの正射影ベクトル
            return a * (dot(a, b) / dot(a, a));
        }

        static float dist(const Vec2& a, const Vec2& b) { //2点間の距離
            return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }

        static float sq_dist(const Vec2& a, const Vec2& b) { //距離の2乗
            return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
        }

        static float L1_dist(const Vec2& a, const Vec2& b) { //L1距離
            return std::abs(a.x - b.x) + std::abs(a.y - b.y);
        }

        void print(){
            std::cout << x << " " << y << std::endl;
        }
    };
}