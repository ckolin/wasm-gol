#define MAX_SIZE 1000*1000
#define uint8 unsigned char

int width, height;
uint8 grid[MAX_SIZE];
uint8 copy[MAX_SIZE];

void init(int w, int h) {
	width = w;
	height = h;
}

uint8* get_grid_pointer() {
	return &grid[0];
}

int get_index(int x, int y) {
	if (x < 0 || x >= width || y < 0 || y >= height)
		return -1;
	return y * width + x;
}

void set_cell(int x, int y, int v) {
	int idx = get_index(x, y);
	if (idx == -1)
		return;
	grid[idx] = v;
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
