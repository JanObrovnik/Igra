#include "DataBase.h"

std::ostream& operator<<(std::ostream& os, const koordinate& ko) {
	return os << "Location (x: " << ko.x << ", y: " << ko.y << ")";
}