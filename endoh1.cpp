#include <stdio.h>//  .IOCCC                                         Fluid-  #
#include <unistd.h>  //2012                                         _Sim!_  #
#include <cmath>
using namespace std;
#define G 1
#define P 4
#define V 4

struct complex {
	complex() :x(0),y(0) {}
	complex(double real) :x(real),y(0) {}
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
	explicit operator double() {
		return x;
	}
	double x,y;
};

complex I = {0,1};

complex operator -(double p, complex q) {
	return complex{p} - q;
}

double cabs(complex p) {
	return sqrt(p.x*p.x+p.y*p.y);
}

double creal(complex p) { return p.x;}
complex a[97687], w = 0, d;
int p, q, r = 0;
int x, y;
char b[6856] = "\x1b[2J" "\x1b" "[1;1H     ";
int o = 0, t;



int main() {

	while (0 < (x = getc(stdin))) {
		if (x > 10) {
			if (32 < x) {
				a[r++] = w;
				a[r + 4] = w + 1;
				a[r] = a[r + 5] = x == 35;
				r += 9;
			}
			w = w - I;
		} else {
			w = (int) creal(w) + 2;
		}
	}
	while (1) {
		for (p = 0; p < r; p += 5) {
			a[p + 2] = a[p + 1] * 9;
			for (q = 0; q < r; q += 5) {
				d = a[p] - a[q];
				w = cabs(d) / 2 - 1;
				if (0 < (x = double(1 - w)))
					a[p + 2] += w * w;
			}
		}
		for (p = 0; p < r; p += 5) {
			a[p + 3] = G;
			for (q = 0; q < r; q += 5) {
				d = a[p] - a[q];
				w = cabs(d) / 2 - 1;
				x = double(1 - w);
				if (x > 0)
					a[p + 3] += w
							* (d * (3 - a[p + 2] - a[q + 2]) * P + a[p + 4] * V
									- a[q + 4] * V) / a[p + 2];
			}
		}
		for (x = 011; 2012 - 1 > x++;)
			b[x] = 0;
		for (p = 0; p < r; p += 5) {
			t = 10 + (x = double(a[p] * I)) + 80 * (y = double(a[p] / 2));
			a[p] += a[p + 4] += a[p + 3] / 10 * !double(a[p + 1]);
			x = 0 <= x && x < 79 && 0 <= y && y < 23;
			if (x) {
				b[t] |= 8;
				b[t + 1] |= 4;
				t += 80;
				b[t + 1] = 1;
				b[t] |= 2;
			}
		}
		for (x = 011; 2012 - 1 > x++;)
			b[x] = " '`-.|//,\\" "|\\_" "\\/\x23\n"[x % 80 - 9 ? x[b] : 16];

		usleep(12321);
		puts(b + o);
		o = 4;
	}
	return 0;
}
/*
int main() {

	while (0 < (x = getc(stdin))) {
		if (x > 10) {
			if (32 < x) {
				a[r++] = w;
				a[r + 4] = w + 1;
				a[r] = a[r + 5] = x == 35;
				r += 9;
			}
			w.y -= 1;
		} else {
			w = (int) w.x + 2;
		}
	}
	while (1) {
		for (p = 0; p < r; p += 5) {
			a[p + 2] = a[p + 1] * 9;
			for (q = 0; q < r; q += 5) {
				d = a[p] - a[q];
				w = cabs(d) / 2 - 1;
				if (0 < (x = 1 - w.x))
					a[p + 2] += w * w;
			}
		}
		for (p = 0; p < r; p += 5) {
			a[p + 3] = G;
			for (q = 0; q < r; q += 5) {
				d = a[p] - a[q];
				w = cabs(d) / 2 - 1;
				x = 1 - w.x;
				if (x > 0)
					a[p + 3] += w
							* (d * (complex{3,0} - a[p + 2] - a[q + 2]) * P + a[p + 4] * V
									- a[q + 4] * V) / a[p + 2];
			}
		}
		for (x = 011; 2012 - 1 > x++;)
			b[x] = 0;
		for (p = 0; p < r; p += 5) {
			t = 10 + (x = (a[p] * I).x) + 80 * (y = (a[p] / 2).x);
			a[p] += a[p + 4] += a[p + 3] / 10 * !(a[p + 1].x);
			x = 0 <= x && x < 79 && 0 <= y && y < 23;
			if (x) {
				b[t] |= 8;
				b[t + 1] |= 4;
				t += 80;
				b[t + 1] = 1;
				b[t] |= 2;
			}
		}
		for (x = 011; 2012 - 1 > x++;)
			b[x] = " '`-.|//,\\" "|\\_" "\\/\x23\n"[x % 80 - 9 ? x[b] : 16];

		usleep(12321);
		puts(b + o);
		o = 4;
	}
	return 0;
}*/
