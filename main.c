#include <raylib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#define MAX_ITER 200

int main(void)
{
	float zoom = 1.0f;
	float offset_x = 0.0f;
	float offset_y = 0.0f;
	int max_iter = MAX_ITER;
	Vector2 resolution = {SCREEN_WIDTH, SCREEN_HEIGHT};

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mandelbrot");
	
	RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	Shader shader = LoadShader(0, "mandelbrot.frag");
	SetTargetFPS(60);

	SetShaderValue(shader, GetShaderLocation(shader, "resolution"), &resolution, SHADER_UNIFORM_VEC2);

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_W))
			zoom = zoom * 1.01f;
		if (IsKeyDown(KEY_S))
			zoom = zoom / 1.01f;

		if (IsKeyDown(KEY_H) || IsKeyDown(KEY_LEFT))
			offset_x -= 0.02f / zoom;
		if (IsKeyDown(KEY_L) || IsKeyDown(KEY_RIGHT))
			offset_x += 0.02f / zoom;
		if (IsKeyDown(KEY_J) || IsKeyDown(KEY_DOWN))
			offset_y += 0.02f / zoom;
		if (IsKeyDown(KEY_K) || IsKeyDown(KEY_UP))
			offset_y -= 0.02f / zoom;

		if (IsKeyDown(KEY_Q))
			if (max_iter > 0)
				max_iter -= 1;
		if (IsKeyDown(KEY_E))
			max_iter += 1;

		if (IsKeyPressed(KEY_R)) {
			zoom = 1.0;
			offset_x = 0.0;
			offset_y = 0.0;
			max_iter = MAX_ITER;
		}

		SetShaderValue(shader, GetShaderLocation(shader, "max_iter"), &max_iter, SHADER_UNIFORM_INT);
		SetShaderValue(shader, GetShaderLocation(shader, "zoom"), &zoom, SHADER_UNIFORM_FLOAT);
		SetShaderValue(shader, GetShaderLocation(shader, "offset_x"), &offset_x, SHADER_UNIFORM_FLOAT);
		SetShaderValue(shader, GetShaderLocation(shader, "offset_y"), &offset_y, SHADER_UNIFORM_FLOAT);

		BeginDrawing();
			BeginTextureMode(target);
				DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
			EndTextureMode();

			BeginShaderMode(shader);
				DrawTexture(target.texture, 0, 0, BLACK);
			EndShaderMode();
		EndDrawing();
	}
	UnloadRenderTexture(target);
	UnloadShader(shader);
	CloseWindow();

	return 0;
}
