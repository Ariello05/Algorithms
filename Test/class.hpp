#pragma once

template <class T>
class Tester {
	T * ob;
public:
	Tester() {
	}


	void take(T & ref) {
		ob = &ref;
	}

	void shuff() {
		(*ob)[0] = 9;
	}

};