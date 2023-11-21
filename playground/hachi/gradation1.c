#include <stdio.h>
#define WIDTH 512
#define HEIGHT 512
int main() {
	int y, x;
	float fx;
	int gray;
	printf("P3\n"); /* マジックナンバー */
	printf("%d %d\n", WIDTH, HEIGHT); /* 幅と高さ */
	printf("255\n"); /* 色深度 */
	/*0->512までrangeを0->255にする*/
	for(y = 0; y < HEIGHT; ++y)
	{
		for(x = 0; x < WIDTH; ++x)
		{
			fx = (float)x / (float)WIDTH;
			gray = (int)(255 * fx);
			printf("%d %d %d\n", gray, gray, gray);
		}/* for */
	}/* for */
	return 0;
}