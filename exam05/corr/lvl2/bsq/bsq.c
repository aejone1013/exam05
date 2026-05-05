#include "bsq.h"

void free_map(t_bsq *b) {
	for (int i = 0; i < b->height; i++) if (b->map[i]) free(b->map[i]);
	free(b->map);
}
void print_map(t_bsq *b) { for (int i = 0; i < b->height; i++) fprintf(stdout, "%s\n", b->map[i]); }
int ft_strlen(char *s) { int i = 0; while (s[i]) i++; return i; }
int ft_isprint(int c) { return c >= 32 && c <= 126; }

char **get_map(t_bsq *b, char *filename) {
	FILE *file = filename ? fopen(filename, "r") : stdin;
	if (!file) return NULL;
	if (fscanf(file, "%d%c%c%c\n", &b->height, &b->empty, &b->obstacle, &b->full) != 4 || b->height <= 0)
		{ if (filename) fclose(file); return NULL; }
	char **map = malloc(sizeof(char *) * (b->height + 1));
	if (!map) { if (filename) fclose(file); return NULL; }
	for (int i = 0; i < b->height; i++) {
		char *line = NULL; size_t len = 0;
		ssize_t r = getline(&line, &len, file);
		if (r == -1) {
			for (int k = 0; k < i; k++) free(map[k]);
			free(map); if (filename) fclose(file); return NULL;
		}
		if (line[r - 1] == '\n') line[r - 1] = '\0';
		map[i] = line;
	}
	b->width = ft_strlen(map[0]); map[b->height] = NULL;
	if (filename) fclose(file);
	return map;
}

int check_map(t_bsq *b) {
	if (!b->map || b->height < 1 || b->width < 1) return 0;
	if (!ft_isprint(b->empty) || !ft_isprint(b->full) || !ft_isprint(b->obstacle)) return 0;
	if (b->empty == b->full || b->empty == b->obstacle || b->full == b->obstacle) return 0;
	for (int i = 0; i < b->height; i++) {
		int j = 0;
		while (b->map[i][j]) {
			if (b->map[i][j] != b->empty && b->map[i][j] != b->full && b->map[i][j] != b->obstacle) return 0;
			j++;
		}
		if (j != b->width) return 0;
	}
	return 1;
}

int min(int a, int b, int c) { return a<=b&&a<=c ? a : b<=c ? b : c; }

int bsq_solver(t_bsq *b) {
	int mi=0, mj=0, ms=0;
	int *m = malloc(sizeof(int) * b->height * b->width);
	if (!m) return 1;
	for (int i = 0; i < b->height; i++) {
		for (int j = 0; j < b->width; j++) {
			int idx = i * b->width + j;
			if (b->map[i][j] == b->obstacle) m[idx] = 0;
			else if (i == 0 || j == 0) m[idx] = 1;
			else m[idx] = 1 + min(m[(i-1)*b->width+(j-1)], m[(i-1)*b->width+j], m[i*b->width+(j-1)]);
			if (m[idx] > ms) { mi = i; mj = j; ms = m[idx]; }
		}
	}
	for (int i = mi-ms+1; i <= mi; i++)
		for (int j = mj-ms+1; j <= mj; j++) b->map[i][j] = b->full;
	free(m); return 0;
}

int bsq(char *filename) {
	t_bsq *b = malloc(sizeof(t_bsq));
	if (!b) return 1;
	b->map = get_map(b, filename);
	if (!b->map || !check_map(b) || bsq_solver(b) == 1)
		{ if (b->map) free_map(b); fprintf(stderr, "map error\n"); free(b); return 1; }
	print_map(b); free_map(b); free(b); return 0;
}

int main(int ac, char **av) {
	if (ac == 1) bsq(NULL);
	else for (int i = 1; i < ac; i++) { bsq(av[i]); if (i < ac-1) fprintf(stdout, "\n"); }
	return 0;
}
