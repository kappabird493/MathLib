#include <iostream>
#include "math/Vec3.hpp"
using namespace math;

int main() {
    Vec3 a{1, 0, 0};
    Vec3 b{0, 1, 0};

    auto c = Vec3::cross(a, b);
    auto d = Vec3::dot(a,b);
    auto e = Vec3::L1_dist(a,b);

    std::cout << c.x << " " << c.y << " " << c.z << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;

    std::cin.get();
    return 0;
}
