#include <stdio.h>//  .IOCCC                                         Fluid-  #
#include <unistd.h>  //2012                                         _Sim!_  #
#include <complex.h>  //||||                     ,____.              IOCCC-  #
double complex a[97687], w = 0, d;
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
				if (0 < (x = 1 - w))
					a[p + 2] += w * w;
			}
		}
		for (p = 0; p < r; p += 5) {
			a[p + 3] = G;
			for (q = 0; q < r; q += 5) {
				d = a[p] - a[q];
				w = cabs(d) / 2 - 1;
				x = 1 - w;
				if (x > 0)
					a[p + 3] += w
							* (d * (3 - a[p + 2] - a[q + 2]) * P + a[p + 4] * V
									- a[q + 4] * V) / a[p + 2];
			}
		}
		for (x = 011; 2012 - 1 > x++;)
			b[x] = 0;
		for (p = 0; p < r; p += 5) {
			t = 10 + (x = a[p] * I) + 80 * (y = a[p] / 2);
			a[p] += a[p + 4] += a[p + 3] / 10 * !a[p + 1];
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

