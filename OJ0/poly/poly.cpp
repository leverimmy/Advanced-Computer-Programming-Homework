#include "poly.h"
#include <vector>

std::vector<int> poly_plus(const std::vector<int> &poly0, const std::vector<int> &poly1) {
    std::vector<int> res(std::max(poly0.size(), poly1.size()), 0);
    for (size_t i = 0; i < poly0.size(); ++i) {
        res[i] += poly0[i];
    }
    for (size_t i = 0; i < poly1.size(); ++i) {
        res[i] += poly1[i];
    }
    return res;
}

std::vector<int> poly_mul(const std::vector<int> &poly0, const std::vector<int> &poly1) {
    std::vector<int> res(poly0.size() + poly1.size() - 1, 0);
    for (size_t i = 0; i < poly0.size(); ++i) {
        for (size_t j = 0; j < poly1.size(); ++j) {
            res[i + j] += poly0[i] * poly1[j];
        }
    }
    return res;
}