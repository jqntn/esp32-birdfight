#include <raylib.h>

int
main()
{
  SetConfigFlags(FLAG_WINDOW_TOPMOST);
  InitWindow(320, 240, "birdfight");
  SetExitKey(KEY_NULL);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RED);
    DrawCircle(
      GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f, 100.0f, GREEN);
    EndDrawing();
  }

  CloseWindow();
}