const dbg = (obj) => { console.log(obj); return obj; };
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const options = {
	width: 400,
	height: 300,
	scale: 2,
	fps: 20
};

WebAssembly.instantiateStreaming(fetch("gol.wasm"))
	.then(obj => obj.instance.exports)
	.then(gol => {
		gol.init(options.width, options.height);
		const buf = new Uint8Array(gol.memory.buffer,
			gol.get_grid_pointer(),
			options.width * options.height);

		canvas.width = options.width * options.scale;
		canvas.height = options.height * options.scale;
		ctx.scale(options.scale, options.scale);
		
		setInterval(() => {
			gol.tick();
			ctx.clearRect(0, 0, options.width, options.height);
			for (let y = 0; y < options.height; y++) {
				for (let x = 0; x < options.width; x++) {
					if (buf[y * options.width + x] == 1)
						ctx.fillRect(x, y, 1, 1);
				}
			}
		}, 1000 / options.fps);
	});