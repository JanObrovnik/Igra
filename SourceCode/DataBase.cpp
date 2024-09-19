#include "DataBase.h"

std::ostream& operator<<(std::ostream& os, const koordinate& ko) {
	return os << "(" << ko.x << " " << ko.y << ")";
}

std::istream& operator>>(std::istream& is, koordinate& ko) {
	char c;
	is >> c >> ko.x >> ko.y >> c;
	return is;
}
