#include "Vector3.h"
std::ostream& operator<<(std::ostream& out, const lan::Vector3F& vec) {
	out << vec.toString();
	return out;
}