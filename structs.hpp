#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <SDL.h>
struct ipoint {
	int x, y;
	ipoint() : x(0), y(0) {}
	ipoint(int _x, int _y) : x(_x), y(_y) {}
};
struct fpoint {
	float x, y;
	fpoint() : x(0.0f), y(0.0f) {}
	fpoint(int _x, int _y) : x(_x), y(_y) {}
};
struct ivec {
	int m, a;
	ivec() : m(0), a(0) {}
	ivec(int _m, int _a) : m(_m), a(_a) {}
};
struct fvec {
	float m, a;
	fvec() : m(0.0f), a(0.0f) {}
	fvec(float _m, float _a) : m(_m), a(_a) {}
};
struct s_particle {
	float x, y, xv, yv;
	SDL_Color c;
	s_particle() : x(0), y(0), xv(0), yv(0), c{ 255,255,255,255 } {};
	s_particle(float _x, float _y, float _xv, float _yv, SDL_Color _c) :
		x(_x), y(_y), xv(_xv), yv(_yv), c(_c) {}
};
struct camera {
	fpoint position;
	camera() : position() {}
};
struct inputState {
	//todo
};
struct piece {
	int type;
	SDL_Color color;
};
#endif