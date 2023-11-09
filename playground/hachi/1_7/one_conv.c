
#include <stdio.h>
#include "../vector_utils/vector_utils.h"

#define WIDTH 512
#define HEIGHT 512

int main()
{
	int x_s = 382;
	int y_s = 255;

	vector_t pw;

	pw.x = (float)(2 * x_s) / (WIDTH - 1) - 1;
	pw.y = -1 * ((float)(2 * y_s) / (HEIGHT - 1) - 1);
	pw.z = 0;

	printf("(%d,%d) -> %s\n", x_s, y_s, vector_str(&pw));

	return 0;
}