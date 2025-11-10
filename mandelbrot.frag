#version 330

precision highp float;

uniform vec2 resolution;
uniform int max_iter;
uniform float zoom;
uniform float offset_x;
uniform float offset_y;

in vec2 fragTexCoord;
out vec4 finalColor;

#define INIT_X_SHIFT 0.5

vec3 get_color(int iter)
{
	if (iter == max_iter)
		return vec3(0.0, 0.0, 0.0);
	return vec3(sin(iter / 32.0) * 0.86 + 0.2, sin(iter / 48.0) * 0.75 + 0.1, sin(iter / 64.0) * 0.64 + 0.3);
}

int mandelbrot(float cx, float cy)
{
	float zx = cx;
	float zy = cy;
	int iter = 0;

	float temp_zx;
	while (iter < max_iter && zx * zx + zy * zy <= 4.0) {
		temp_zx = zx;
		zx = zx * zx - zy * zy + cx;
		zy = 2 * temp_zx * zy + cy;
		iter++;
	}
	return iter;
}

void main()
{
	float zx = (resolution[0] * fragTexCoord.x - resolution[0] / 2.0) / (resolution[0] * 0.35 * zoom) + offset_x - INIT_X_SHIFT;
	float zy = (resolution[1] * fragTexCoord.y - resolution[1] / 2.0) / (resolution[1] * 0.35 * zoom) + offset_y;
	int iter = mandelbrot(zx, zy);
	finalColor = vec4(get_color(iter), 1.0);
}
