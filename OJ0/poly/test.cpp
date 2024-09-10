#include <iostream>
#include <sstream>
#include <string>
#include "poly.h"

std::string poly_print(const std::vector<int>& p) {
	bool is_first = true;
	std::stringstream s;
	for (size_t i = 0; i < p.size(); ++i) {
		if (p[i] == 0) {
			continue;
		}
		if (!is_first && p[i] > 0) {
			s << " +";
		} else if (!is_first) {
			s << " ";
		}
		s << p[i];
		if (i == 1) {
			s << "x";
		} else if (i > 1) {
			s << "x^" << i;
		}
		is_first = false;
	}
	return s.str();
}

int main() {
	std::vector<int> p1 = {1, -1, 2, 3};
	std::vector<int> p2 = {3, -1, -4};
	std::cout << "A = " << poly_print(p1) << "\n";
	std::cout << "B = " << poly_print(p2) << "\n";
	std::cout << "Your code says A + B = " << poly_print(poly_plus(p1, p2)) << "\n";
	std::cout << "Your code says A * B = " << poly_print(poly_mul(p1, p2)) << "\n";
}
