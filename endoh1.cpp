#include <stdio.h>//  .IOCCC                                         Fluid-  #
#include <unistd.h>  //2012                                         _Sim!_  #
#include <cmath>
#include <vector>
using namespace std;
#define G 1
#define P 4
#define V 4

int w=80,h=25;

struct complex {
	complex() :x(0),y(0) {}
	complex(double x) :x(x),y(0) {}
	complex(double x,double y) :x(x),y(y) {}

	complex operator +(complex p) {
		return {x+p.x,y+p.y};
	}
	complex operator -(complex p) {
		return {x-p.x,y-p.y};
	}
	complex operator *(complex p) {
		return {x*p.x-y*p.y, x*p.y+y*p.x};
	}
	complex operator /(double p) {
		return {x/p,y/p};
	}
	complex& operator +=(complex p) {
		x += p.x;
		y += p.y;
		return *this;
	}
	double x,y;
	double abs() {
		return sqrt(x*x+y*y);
	}
};

struct particle {
	particle(complex pos, bool wallflag):pos(pos),wallflag(wallflag) {}
	complex pos,vel,force;
	bool wallflag;
	double density;
};

complex operator -(double p, complex q) {
	return complex{p,0} - q;
}

vector<particle> a;
char b[6856] = "\x1b[2J\x1b[1;1H"; // clear screen, go to pos 1,1

void init() {
	int x;
	complex w;
	while ((x = getchar()) != EOF) {
		if (x > 10) {
			if (32 < x) {
				a.push_back(particle(w, x == '#'));
				a.push_back(particle(w + 1, x == '#'));
			}
			w.y--;
		} else {
			w.x += 2;
			w.y = 0;
		}
	}
}

int main() {
	init();
	puts(b);
	while(true) {
		for (particle& p : a) {
			p.density = p.wallflag * 9;
			for (particle& q : a) {
				double w = (p.pos - q.pos).abs() / 2 - 1;
				if (0 < int(1 - w))
					p.density += w * w;
			}
		}
		for (particle& p : a) {
			p.force = G;
			for (particle& q : a) {
				complex d = p.pos - q.pos;
				double w = d.abs() / 2 - 1;
				if (int(1-w) > 0)
					p.force +=
						(d * (3 - p.density - q.density) * P
						 + p.vel * V - q.vel * V
						 ) * w / p.density;
			}
		}
		for (int x = 0; x<=w*h; x++)
			b[x + 10] = 0;
		for (particle& p : a) {
			int x = -p.pos.y;
			int y = p.pos.x / 2;
			int t = 10 + x + 80 * y;
			p.pos += p.vel += p.force / 10 * !p.wallflag;
			if (0 <= x && x < 79 && 0 <= y && y < 23) {
				// on screen
				b[t] |= 8;
				b[t + 1] |= 4;
				t += 80;
				b[t + 1] = 1;
				b[t] |= 2;
			}
		}
		for (int x = 10; x<2011; x++) {
			if(x % 80 - 9)
				b[x] = " '`-.|//,\\|\\_\\/#\n"[int(b[x])];
			else b[x] = '\n';
		}

		usleep(12321);
		puts(b + 4);
	}
	return 0;
}
