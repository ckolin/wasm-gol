const dbg = (obj) => { console.log(obj); return obj; };
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
const scale = 2;

WebAssembly.instantiateStreaming(fetch("gol.wasm"))
	.then(obj => obj.instance.exports)
	.then(gol => {
		gol.init();
		const width = gol.get_width();
		const height = gol.get_height();		
		const buf = new Uint8Array(gol.memory.buffer,
			gol.get_grid_pointer(),
			width * height);

		canvas.width = width * scale;
		canvas.height = height * scale
		ctx.scale(scale, scale);
		
		setInterval(() => {
			gol.tick();
			ctx.clearRect(0, 0, canvas.width, canvas.height);
			for (let y = 0; y < height; y++) {
				for (let x = 0; x < width; x++) {
					if (buf[y * width + x] == 1)
						ctx.fillRect(x, y, 1, 1);
				}
			}
		}, 1000/20);
	});