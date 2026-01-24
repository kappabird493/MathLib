#pragma once
#include<cmath>
#include<cassert>

namespace math{
    struct Vec3{
        float x, y, z;

        constexpr Vec3() : x(0),y(0),z(0) {}
        constexpr Vec3(float x,float y, float z) : x(x),y(y),z(z) {}

        constexpr Vec3 operator+(const Vec3& rhs) const{
            return {x + rhs.x, y + rhs.y, z + rhs.z};
        }
        
        constexpr Vec3 operator-(const Vec3& rhs) const{
            return {x - rhs.x, y - rhs.y, z - rhs.z};
        }

        constexpr Vec3 operator*(float s) const{
            return {x * s, y * s, z * s};
        }

        Vec3 operator/(float s) const{
            constexpr float eps = 1e-6f;
            assert(std::abs(s) > eps);
            return {x / s, y / s, z / s};
        }

        float length() const{ // 長さ
            return std::sqrt(x*x + y*y + z*z);
        }

        float sq_length() const{ // 長さの二乗
            return x*x + y*y + z*z;
        }

        Vec3 normalized() const{ // 正規化
            float len = length();
            assert(len > 0.0f);
            return *this / len;
        }

        Vec3 translation(float tx, float ty, float tz) { //平行移動
            return {x + tx, y + ty, z + tz};
        }

        static constexpr float dot(const Vec3& lhs, const Vec3& rhs) { //内積
            return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
        }

        static constexpr Vec3 adamar(const Vec3& lhs, const Vec3& rhs) { //アダマール積
            return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
        }

        static constexpr Vec3 cross(const Vec3& lhs, const Vec3& rhs) { //外積
            return {lhs.y*rhs.z - lhs.z*rhs.y, lhs.z*rhs.x - lhs.x*rhs.z, lhs.x*rhs.y - lhs.y*rhs.x};
        }

        static float tri_area(const Vec3& a,const Vec3& b) { //2ベクトルの張る三角形の面積
            float la = a.length();
            float lb = b.length();
            return 0.5f * std::sqrt(la*la*lb*lb - dot(a, b)*dot(a, b));
        }

        static constexpr Vec3 orth_proj(const Vec3& a, const Vec3& b) { //bのaへの正射影ベクトル
            return a * (dot(a,b) / dot(a,a));
        }

        static Vec3 rotation(const Vec3& r, const Vec3& n, const float theta) { //ロドリゲスの回転公式
            float c = std::cos(theta);
            float s = std::sin(theta);
            return r*c + n*(1.0f-c)*dot(r,n) + cross(n,r)*s;
        }
 
        static float dist(const Vec3& a, const Vec3& b) { //2点間の距離
            return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z)); 
        }

        static float sq_dist(const Vec3& a, const Vec3& b) { //距離の2乗
            return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z); 
        }

        static float L1_dist(const Vec3& a, const Vec3& b) { //L1距離
            return std::abs(a.x-b.x) + std::abs(a.y-b.y) + std::abs(a.z-b.z); 
        }

        void print(){
            std::cout << x << " " << y << " " << z << std::endl;
        }
    };
}