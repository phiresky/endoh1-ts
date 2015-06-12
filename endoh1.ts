"use strict";
// compiled from endoh1.ts
// https://github.com/phiresky/endoh1-ts

var accuracy = 2;
var Gravity = 1;
var Pressure = 4;
var Viscosity = 4;

var w = 79*accuracy, h = 25*accuracy, scale = 1;

type double = number;
type int = number;

class particle {
	constructor(public posx: double, public posy: double, public wallflag: boolean) { }
	velx: double = 0; vely: double = 0;
	forcex: double = 0; forcey: double = 0;
	density: double = 0;
};

var a: particle[] = [];

declare var canvas: HTMLCanvasElement, previewarea: HTMLTextAreaElement, 
	file: HTMLSelectElement, fps: HTMLSpanElement;
canvas.width = w * scale; canvas.height = h * scale;
var ctx = <CanvasRenderingContext2D>canvas.getContext('2d');
ctx.fillStyle = "rgba(0,0,0,0.7)";

var interval, frameid = 0, lastdate, lastframe;
previewarea.cols = w;
previewarea.rows = h;

function ord(c: string) {
	return c.charCodeAt(0);
}
function chr(c: int) {
	return String.fromCharCode(c);
}

var input = "";

function loadfile() {
	var req = new XMLHttpRequest();
	req.open('GET', file.value, true);
	req.onload = function() {
		if (this.status >= 200 && this.status < 400)
			previewarea.textContent = input = this.response;
		else console.error(this);
	}
	req.send();
}

function init() {
	a = [];
	var y: double = 0, x: double = 0;
	for (var i = 0; i < input.length; i++) {
		let c = input.charCodeAt(i);
		if (c === ord('\n')) {
			y += accuracy;
			x = 0;
		} else if (c !== ord(' ')) {
			var wall = c === ord('#');
			for(let dx = 0; dx < accuracy; dx++)
				for(let dy = 0; dy < accuracy; dy++)
					a.push(new particle(x+dx, y+dy, wall));
			x+=accuracy;
		} else {
			x+=accuracy;
		}
	}
}

function int(d: double) {
	return ~~d;
}

function calcfps() {
	if (frameid % 30 === 0) {
		var f = (frameid - lastframe) * 1000 / (Date.now() - lastdate);
		fps.textContent = `${f.toFixed(1) } fps`;
		lastdate = Date.now();
		lastframe = frameid;
	}
}

function density() {
	for (let p of a) {
		p.density = p.wallflag ? 9 : 0;
		for (let q of a) {
			let dx = p.posx - q.posx, dy = p.posy - q.posy;
			let d2 = dx * dx + dy * dy;
			if (d2 < 4) {
				let w = Math.sqrt(d2) / 2 - 1;
				p.density += w * w;
			}
		}
	}
}

function force() {
	for (let p of a) {
		p.forcey = Gravity;
		p.forcex = 0;
		for (let q of a) {
			let dy = p.posy - q.posy, dx = p.posx - q.posx;

			let d2 = dy * dy + dx * dx;
			if (d2 < 4) {
				let w = Math.sqrt(d2) / 2 - 1;
				p.forcey += (dy * (3 - p.density - q.density) * Pressure + p.vely * Viscosity - q.vely * Viscosity) * w / p.density;
				p.forcex += (dx * (3 - p.density - q.density) * Pressure + p.velx * Viscosity - q.velx * Viscosity) * w / p.density;
			}
		}
	}
}

function draw() {
	ctx.clearRect(0, 0, w * scale, h * scale);
	for (let p of a) {
		let x = p.posx, y = p.posy;
		if (!p.wallflag) {
			p.posy += p.vely += p.forcey / 10;
			p.posx += p.velx += p.forcex / 10;
		}
		if (0 <= x && x < w && 0 <= y && y < h) {
			ctx.fillRect(x * scale, y * scale, scale, scale);
		}
	}
}

function nextframe() {
	frameid++;
	calcfps();
	density();
	force();
	draw();
}

function run() {
	stop();
	lastdate = Date.now(); lastframe = frameid = 0;
	init();
	interval = setInterval(nextframe, 1000 / 60);
}

function stop() {
	clearInterval(interval);
}

loadfile();
