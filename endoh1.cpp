#include <stdio.h>//  .IOCCC                                         Fluid-  #
#include <unistd.h>  //2012                                         _Sim!_  #
#include <cmath>
using namespace std;
#define G 1
#define P 4
#define V 4

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
	complex operator /(complex p) {
		double den = p.x*p.x+p.y*p.y;
		return {(x*p.x+y*p.y)/den,(y*p.x-x*p.y)/den};
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
	complex pos,wallflag,density,force,vel;
};

complex operator -(double p, complex q) {
	return complex{p,0} - q;
}

particle a[19538];
char b[6856] = "\x1b[2J\x1b[1;1H"; // clear screen, go to pos 1,1

int init() {
	int x,r = 0;
	complex w;
	while ((x = getchar()) != EOF) {
		if (x > 10) {
			if (32 < x) {
				a[r].pos = w;
				a[r].wallflag = a[r+1].wallflag = {double(x == '#'),0};
				a[r+1].pos = {w.x + 1, w.y};
				r += 2;
			}
			w.y--;
		} else {
			w.x += 2;
			w.y = 0;
		}
	}
	return r;
}

int main() {
	int r = init();
	puts(b);
	while(true) {
		for (int p = 0; p < r; p++) {
			a[p].density = a[p].wallflag * 9;
			for (int q = 0; q < r; q++) {
				double w = (a[p].pos - a[q].pos).abs() / 2 - 1;
				if (0 < int(1 - w))
					a[p].density += w * w;
			}
		}
		for (int p = 0; p < r; p++) {
			a[p].force = G;
			for (int q = 0; q < r; q++) {
				complex d = a[p].pos - a[q].pos;
				double w = d.abs() / 2 - 1;
				if (int(1-w) > 0)
					a[p].force +=
						(d * (3 - a[p].density - a[q].density) * P + a[p].vel * V - a[q].vel * V) * w/ a[p].density;
			}
		}
		for (int x = 10; x<2011; x++)
			b[x] = 0;
		for (int p = 0; p < r; p++) {
			int x = -a[p].pos.y;
			int y = a[p].pos.x / 2;
			int t = 10 + x + 80 * y;
			a[p].pos += a[p].vel += a[p].force / 10 * !(a[p].wallflag).x;
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
