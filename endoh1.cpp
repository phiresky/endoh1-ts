#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <iostream>
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

ostream& operator <<(ostream& o, complex& c) {
	return o<<'('<<c.x<<','<<c.y<<')';
}
struct particle {
	particle(complex pos, bool wallflag):pos(pos),wallflag(wallflag) {}
	complex pos,vel,force;
	bool wallflag;
	double density = 0;
};


vector<particle> a;
#define CLEARSCREEN "\x1b[2J"
#define RESETPOS "\x1b[1;1H"
char d[6856];


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
void debuglog() {
	for(particle& p:a) {
		cout << p.pos << p.vel << p.force << p.wallflag << p.density << endl;
	}
}

int main() {
	cout.precision(3);
	cout << std::fixed;
	init();
	fputs(CLEARSCREEN, stdout);
	int frameid = 0;
	while(true) {
		++frameid;
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
		for (int x = 0; x<w*h; x++)
			d[x] = 0;
		for (particle& p : a) {
			int x = -p.pos.y;
			int y = p.pos.x / 2;
			int t = x + w * y;
			if(!p.wallflag)
				p.pos += p.vel += p.force / 10;
			if (0 <= x && x < w-1 && 0 <= y && y < h-2) {
				// on screen
				d[t] |= 8;
				d[t + 1] |= 4;
				t += w;
				d[t + 1] = 1;
				d[t] |= 2;
			}
		}
		for (int x = 0; x<w*h; x++) {
			if((x+1) % w)
				d[x] = " '`-.|//,\\|\\_\\/#\n"[int(d[x])];
			else d[x] = '\n';
		}
		usleep(12321);
		fputs(RESETPOS, stdout);
		fputs(d, stdout);
	}
	return 0;
}
