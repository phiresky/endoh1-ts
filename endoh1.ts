var G = 1;
var P = 4;
var V = 4;

var w=80,h=25;

type double = number;
type int = number;

class complex {
	constructor(public x:double = 0, public y:double = 0) {}

	minus(p:complex) {
		return new complex(this.x-p.x,this.y-p.y);
	}
	abs() {
		return Math.sqrt(this.x*this.x+this.y*this.y);
	}
	clone() {
		return new complex(this.x,this.y);
	}
};

class particle {
	constructor(public pos:complex, public wallflag:boolean) {}
	vel:complex = new complex(); force:complex = new complex();
	density:double = 0;
};


var a:particle[] = [];
var d = new Uint8Array(w*h);
var EOF = -1;
var interval;
var frameid = 0;


var input:string = document.getElementById("input").textContent, inputpos = 0;
function getchar() {
	if(inputpos >= input.length) return EOF;
	return input.charCodeAt(inputpos++);
}

function ord(c:string) {
	return c.charCodeAt(0);
}
function chr(c:int) {
	return String.fromCharCode(c);
}

function init() {
	var c:int;
	var x:double = 0, y:double = 0;
	while ((c = getchar()) != EOF) {
		if (c > 10) {
			if (32 < c) {
				a.push(new particle(new complex(x,y), c == ord('#')));
				a.push(new particle(new complex(x+1,y), c == ord('#')));
			}
			y--;
		} else {
			x += 2;
			y = 0;
		}
	}
}

function fputs(data:string) {
	console.log(data);
}

function int(d:double) {
	return ~~d;
}

function nextframe() {
	if(frameid == 30) clearInterval(interval);
	frameid++;
	for (let p of a) {
		p.density = p.wallflag ? 9 : 0;
		for (let q of a) {
			let w = p.pos.minus(q.pos).abs() / 2 - 1;
			if (0 < int(1 - w))
				p.density += w * w;
		}
	}
	for (let p of a) {
		p.force = new complex(G);
		for (let q of a) {
			let d = p.pos.minus(q.pos);
			let w = d.abs() / 2 - 1;
			if (int(1-w) > 0) {
				p.force.x +=
					(d.x * (3 - p.density - q.density) * P
					 + p.vel.x * V - q.vel.x * V
					 ) * w / p.density;
				p.force.y +=
					(d.y * (3 - p.density - q.density) * P
					 + p.vel.y * V - q.vel.y * V
					 ) * w / p.density;
			}
		}
	}
	for (let x = 0; x<w*h; x++)
		d[x] = 0;
	for (let p of a) {
		let x = int(-p.pos.y);
		let y = int(p.pos.x / 2);
		let t = int(x + w * y);
		if(!p.wallflag) {
			p.pos.x += p.vel.x += p.force.x / 10;
			p.pos.y += p.vel.y += p.force.y / 10;
		}
		if (0 <= x && x < w-1 && 0 <= y && y < h-2) {
			// on screen
			d[t] |= 8;
			d[t + 1] |= 4;
			t += w;
			d[t] |= 2;
			d[t + 1] = 1;
		}
	}
	var o = "";
	for (var x = 0; x<w*h; x++) {
		if((x+1) % w)
			o += " '`-.|//,\\|\\_\\/#"[d[x]];
		else o += '\n';
	}
	return o;
}

function main() {
	init();
	interval = setInterval("output.textContent = nextframe();", 12.321);
	return 0;
}
