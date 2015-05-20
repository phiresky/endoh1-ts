"use strict";
// compiled from endoh1.ts
var Gravity = 1;
var Pressure = 4;
var Viscosity = 4;
var w = 79, h = 25, scale = 1;
var particle = (function () {
    function particle(posx, posy, wallflag) {
        this.posx = posx;
        this.posy = posy;
        this.wallflag = wallflag;
        this.velx = 0;
        this.vely = 0;
        this.forcex = 0;
        this.forcey = 0;
        this.density = 0;
    }
    return particle;
})();
;
var a = [];
canvas.width = w * scale;
canvas.height = h * scale;
var ctx = canvas.getContext('2d');
ctx.fillStyle = "rgba(0,0,0,0.7)";
var interval, frameid = 0, lastdate, lastframe;
previewarea.cols = w;
previewarea.rows = h;
function ord(c) {
    return c.charCodeAt(0);
}
function chr(c) {
    return String.fromCharCode(c);
}
var input = "";
function loadfile() {
    var req = new XMLHttpRequest();
    req.open('GET', file.value, true);
    req.onload = function () {
        if (this.status >= 200 && this.status < 400)
            previewarea.textContent = input = this.response;
        else
            console.error(this);
    };
    req.send();
}
function init() {
    a = [];
    var y = 0, x = 0;
    for (var i = 0; i < input.length; i++) {
        var c = input.charCodeAt(i);
        if (c === ord('\n')) {
            y += 2;
            x = 0;
        }
        else if (c !== ord(' ')) {
            a.push(new particle(x, y, c === ord('#')));
            a.push(new particle(x, y + 1, c === ord('#')));
            x++;
        }
        else {
            x++;
        }
    }
}
function int(d) {
    return ~~d;
}
function calcfps() {
    if (frameid % 30 === 0) {
        var f = (frameid - lastframe) * 1000 / (Date.now() - lastdate);
        fps.textContent = f.toFixed(1) + " fps";
        lastdate = Date.now();
        lastframe = frameid;
    }
}
function density() {
    for (var _i = 0; _i < a.length; _i++) {
        var p = a[_i];
        p.density = p.wallflag ? 9 : 0;
        for (var _a = 0; _a < a.length; _a++) {
            var q = a[_a];
            var dx = p.posx - q.posx, dy = p.posy - q.posy;
            var d2 = dx * dx + dy * dy;
            if (d2 < 4) {
                var w_1 = Math.sqrt(d2) / 2 - 1;
                p.density += w_1 * w_1;
            }
        }
    }
}
function force() {
    for (var _i = 0; _i < a.length; _i++) {
        var p = a[_i];
        p.forcey = Gravity;
        p.forcex = 0;
        for (var _a = 0; _a < a.length; _a++) {
            var q = a[_a];
            var dy = p.posy - q.posy, dx = p.posx - q.posx;
            var d2 = dy * dy + dx * dx;
            if (d2 < 4) {
                var w_2 = Math.sqrt(d2) / 2 - 1;
                p.forcey += (dy * (3 - p.density - q.density) * Pressure + p.vely * Viscosity - q.vely * Viscosity) * w_2 / p.density;
                p.forcex += (dx * (3 - p.density - q.density) * Pressure + p.velx * Viscosity - q.velx * Viscosity) * w_2 / p.density;
            }
        }
    }
}
function draw() {
    ctx.clearRect(0, 0, w * scale, h * scale);
    for (var _i = 0; _i < a.length; _i++) {
        var p = a[_i];
        var x = p.posx, y = p.posy / 2;
        if (!p.wallflag) {
            p.posy += p.vely += p.forcey / 10;
            p.posx += p.velx += p.forcex / 10;
        }
        if (0 <= x && x < w && 0 <= y && y < h) {
            ctx.fillRect(x * scale, y * scale, scale, scale / 2);
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
    lastdate = Date.now();
    lastframe = frameid = 0;
    init();
    interval = setInterval(nextframe, 1000 / 60);
}
function stop() {
    clearInterval(interval);
}
loadfile();
