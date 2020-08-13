#define width 200
#define height 180
#define uint8 unsigned char

uint8 grid[width * height];
uint8 copy[width * height];

uint8* get_grid_pointer() {
	return &grid[0];
}

int get_width() {
	return width;
}

int get_height() {
	return height;
}

int get_index(int x, int y) {
	if (x < 0 || x >= width || y < 0 || y >= height)
		return -1;
	return y * width + x;
}

void init() {
	for (int i = 0; i < width * height; i++)
		if (i % 2 == 0 || i % 7 == 0)
			grid[i] = 1;
}

int count_live_neighbors(int x, int y) {
	int res = 0;
	for (int ox = -1; ox <= 1; ox++) {
		for (int oy = -1; oy <= 1; oy++) {
			int idx = get_index(x + ox, y + oy);
			if (idx == -1 || (ox == 0 && oy == 0))
				continue;
			res += copy[idx];
		}
	}
	return res;
}

void tick() {
	for (int i = 0; i < width * height; i++)
		copy[i] = grid[i];

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int idx = get_index(x, y);
			int live_neighbors = count_live_neighbors(x, y);
			grid[idx] = live_neighbors == 3 || (grid[idx] && live_neighbors == 2);
		}
	}
}
