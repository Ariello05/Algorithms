#include "Route.h"

Route::Route()
{
}

Route::Route(unsigned int v, unsigned int l)
:capacity(l)
{
	this->v = v;
	flow = 0;
}

bool Route::operator<(const Route& s2)
{
	return this->capacity < s2.capacity;
}

void Route::Print() {
	std::cerr << "v: " << v << "\t capacity: " << capacity << "\t flow: " << flow << std::endl;
}