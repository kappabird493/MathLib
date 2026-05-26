#pragma once
#include<cmath>
#include<cassert>

namespace math{
    struct Vec4{
        float x, y, z, w;

        constexpr Vec4() : x(0),y(0),z(0),w(0) {}
        constexpr Vec4(float x, float y, float z, float w) : x(x),y(y),z(z),w(w) {}

        constexpr Vec4 operator+(const Vec4& rhs) const{
            return {x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w};
        }
        
        constexpr Vec4 operator-(const Vec4& rhs) const{
            return {x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
        }

        constexpr Vec4 operator*(float s) const{
            return {x * s, y * s, z * s, w * s};
        }

        Vec4 operator/(float s) const{
            constexpr float eps = 1e-6f;
            assert(std::abs(s) > eps);
            return {x / s, y / s, z / s};
        }

        float length() const{ // 長さ
            return std::sqrt(x*x + y*y + z*z + w*w);
        }

        float sq_length() const{ // 長さの二乗
            return x*x + y*y + z*z + w*w;
        }

        Vec4 normalized() const{ // 正規化
            float len = length();
            assert(len > 0.0f);
            return *this / len;
        }

        Vec4 translation(float tx, float ty, float tz, float tw) { //平行移動
            return {x + tx, y + ty, z + tz, w + tw};
        }

        static constexpr float dot(const Vec4& lhs, const Vec4& rhs) { //内積
            return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
        }

        static constexpr Vec4 adamar(const Vec4& lhs, const Vec4& rhs) { //アダマール積
            return {lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z, lhs.w*rhs.w}
        }

        static float tri_area(const Vec4& a,const Vec4& b) { //2ベクトルの張る三角形の面積
            la = a.length();
            lb = b.length
            return 0.5f * std::sqrt(a.length()*a.length()*b.length()*b.length - dot(a,b)*dot(a,b));
        }

        static Vec4 orth_proj(const Vec4& a, const Vec4& b) { //bのaへの正射影ベクトル
            return (dot(a,b) / dot(a,a)) * a;
        }
 
        static Vec4 dist(const Vec4& a, const Vec4& b) { //2点間の距離
            return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z) + (a.w-b.w)*(a.w-b.w)); 
        }

        static Vec4 sq_dist(const Vec4& a, const Vec4& b) { //距離の2乗
            return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z) + (a.w-b.w)*(a.w-b.w); 
        }

        static Vec4 L1_dist(const Vec4& a, const Vec4& b) { //L1距離
            return std::abs(a.x-b.x) + std::abs(a.y-b.y) + std::abs(a.z-b.z) + std::abs(a.w-b.w); 
        }

        void print(){
            std::cout << x << " " << y << " " << z << " " << w << endl;
        }
    }
}