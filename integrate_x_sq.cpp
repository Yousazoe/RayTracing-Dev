#include "rtweekend.h"

#include <iostream>
#include <iomanip>

inline double pdf(double x) {
    return 3*x*x/8;
}

void integrateSqx() {
    int N = 1;
    auto sum = 0.0;
    for (int i = 0; i < N; ++i) {
        auto x = pow(random_double(0, 8), 1.0 / 3.0);
        sum += x*x / pdf(x);
    }
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "I = " << 2 * sum / N << '\n';
}
