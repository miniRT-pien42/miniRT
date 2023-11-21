#include <stdio.h>
#define WIDTH 512
#define HEIGHT 512
int main() {
	int y, x;
	unsigned char r, g, b;
	r=255;
	g=127;
	b=64;
	printf("P3\n"); /* マジックナンバー */
	printf("%d %d\n", WIDTH, HEIGHT); /* 幅と高さ */
	printf("255\n"); /* 色深度 */
	for(y = 0; y < HEIGHT; ++y)
	{
		for(x = 0; x < WIDTH; ++x)
		{
			printf("%hhu %hhu %hhu\n", r, g, b);
		}/* for */
	}/* for */
	return 0;
}