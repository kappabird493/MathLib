#include <iostream>
#include "../include/math/Vec2.hpp"
#include "../include/math/Vec3.hpp"
#include "../include/math/Mat2.hpp"
#include "../include/math/Mat3.hpp"

int main()
{
    using namespace math;

    // --- Vec2 基本計算 ---
    std::cout << "=== Vec2 ===\n";
    Vec2 a{1.0f, 2.0f};
    Vec2 b{3.0f, -1.0f};

    Vec2 c = a + b;
    Vec2 d = a * 2.0f;
    float dot = Vec2::dot(a,b);

    std::cout << "a = "; a.print();
    std::cout << "b = "; b.print();
    std::cout << "a + b = "; c.print();
    std::cout << "a * 2 = "; d.print();
    std::cout << "dot(a, b) = " << dot << "\n\n";

    // --- Vec3 基本計算 ---
    std::cout << "=== Vec3 ===\n";
    Vec3 u{1.0f, 0.0f, 0.0f};
    Vec3 v{0.0f, 1.0f, 0.0f};

    Vec3 cross = Vec3::cross(u,v);
    float dot3 = Vec3::dot(u,v);

    std::cout << "u = "; u.print();
    std::cout << "v = "; v.print();
    std::cout << "u x v = "; cross.print();
    std::cout << "dot(u, v) = " << dot3 << "\n\n";

    // --- Mat2 回転 ---
    std::cout << "=== Mat2 Rotation ===\n";
    float angleDeg = 90.0f;
    Mat2 R = Mat2::rotation(angleDeg);
    Vec2 p{1.0f, 0.0f};

    Vec2 rotated = R * p;
    R.print();
    rotated.print();

    std::cout << "rotation angle from matrix = "
              << R.rotationAngleDeg() << " deg\n\n";


    Mat3 A = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10
    };
    
    std::cout << "A = " << std::endl;

    A.print();

    Mat3 inv = A.inverse();

    std::cout << "inverse of A =" << std::endl;
    inv.print();

    // --- Mat3 を使った 2D 変換 (スケール + 平行移動) ---
    std::cout << "=== Mat3 Affine 2D (Scale + Translate) ===\n";

    // スケール行列
    Mat3 S = {
        2, 0, 0,
        0, 2, 0,
        0, 0, 1
    };

    // 平行移動行列
    Mat3 T = {
        1, 0, 5,
        0, 1, 3,
        0, 0, 1
    };

    // 合成変換
    Mat3 M = T * S;

    // 同次座標（Vec3で）
    Vec3 p2{1, 1, 1};
    Vec3 transformed = M * p2;

    std::cout << "Point (1,1) scaled x2 then translated by (5,3) = ";
    transformed.print();

    return 0;
}
