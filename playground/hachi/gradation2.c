#include <stdio.h>
#define WIDTH 512
#define HEIGHT 512
int main() {
	int y, x;
	float fx_up, fx_down, fy_up;
	printf("P3\n"); /* マジックナンバー */
	printf("%d %d\n", WIDTH, HEIGHT); /* 幅と高さ */
	printf("255\n"); /* 色深度 */
	/*0->512までrangeを0->255にする*/
	for(y = 0; y < HEIGHT; ++y)
	{
		fy_up = (float)y / (float)HEIGHT;
		for(x = 0; x < WIDTH; ++x)
		{
			fx_up = (float)x / (float)WIDTH;
			fx_down = (float)(WIDTH - x) / (float)WIDTH;
			printf("%d %d %d\n", (int)(255 * fx_down), (int)(255 * fy_up), (int)((255 * fx_up + 255 * fy_up) / 2));
		}/* for */
	}/* for */
	return 0;
}