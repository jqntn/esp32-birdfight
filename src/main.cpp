#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

constexpr int ESP_W = 320;
constexpr int ESP_H = 240;

static void
print_rgba(uint32_t col)
{
  printf("RGBA(%d, %d, %d, %d)\n",
         (col) & 0xFF,
         ((col) >> 8) & 0xFF,
         ((col) >> 16) & 0xFF,
         ((col) >> 24) & 0xFF);
}

static void
init()
{
}

static void
tick()
{
}

static void
draw()
{
  ClearBackground(RED);
  DrawCircle(ESP_W * 0.5f, ESP_H * 0.5f, 100.0f, GREEN);
}

static void
close()
{
#ifdef ESP32
  Image img = {
    .data = new uint32_t[ESP_W * ESP_H],
    .width = ESP_W,
    .height = ESP_H,
    .mipmaps = 1,
    .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
  };

  rlCopyFramebuffer(
    0, 0, ESP_W, ESP_H, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, img.data);

  ExportImage(img, "out.png");

  system("out.png");
#endif
}

static void
init_platform()
{
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIDDEN);
#ifdef ESP32
  InitWindow(ESP_W, ESP_H, "birdfight");
#else
  InitWindow(0, 0, "birdfight");
  int f = GetScreenHeight() / ESP_H / 2;
  SetWindowSize(ESP_W * f, ESP_H * f);
  SetWindowPosition((GetMonitorWidth(0) - GetScreenWidth()) / 2,
                    (GetMonitorHeight(0) - GetScreenHeight()) / 2);
#endif
  SetExitKey(KEY_NULL);
  ClearWindowState(FLAG_WINDOW_HIDDEN);
}

static void
loop_platform()
{
#ifdef ESP32
  tick();
  BeginDrawing();
  draw();
  EndDrawing();
#else
  static RenderTexture2D rt = LoadRenderTexture(ESP_W, ESP_H);

  while (!WindowShouldClose()) {
    tick();

    BeginTextureMode(rt);
    draw();
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    float s = std::min((float)GetScreenWidth() / ESP_W,
                       (float)GetScreenHeight() / ESP_H);

    int w = ESP_W * s;
    int h = ESP_H * s;
    int x = (GetScreenWidth() - w) / 2;
    int y = (GetScreenHeight() - h) / 2;

    DrawTexturePro(rt.texture,
                   Rectangle{ 0.0f, 0.0f, (float)ESP_W, -(float)ESP_H },
                   Rectangle{ (float)x, (float)y, (float)w, (float)h },
                   Vector2Zeros,
                   0.0f,
                   WHITE);
    EndDrawing();
  }
#endif
}

static void
close_platform()
{
  CloseWindow();
}

int
main()
{
  init_platform();

  init();

  loop_platform();

  close();

  close_platform();
}