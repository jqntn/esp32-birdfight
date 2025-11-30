#include <cstdint>
#include <cstdio>
#include <ctime>
#include <process.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

extern "C"
{
  void LoadFontDefault(void);
  void UnloadFontDefault(void);
}

extern "C"
{
  extern bool isGpuReady;
}

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
  DrawCircle((float)ESP_W * 0.5f, (float)ESP_H * 0.5f, 100.0f, GREEN);
}

static void
close()
{
}

static void
init_esp()
{
  SetRandomSeed((unsigned int)time(nullptr));

  rlglInit(ESP_W, ESP_H);
  isGpuReady = true;

  rlViewport(0, 0, ESP_W, ESP_H);
  rlMatrixMode(RL_PROJECTION);
  rlLoadIdentity();
  rlOrtho(0.0, (double)ESP_W, (double)ESP_H, 0.0, 0.0, 1.0);
  rlMatrixMode(RL_MODELVIEW);
  rlLoadIdentity();

  LoadFontDefault();
  Rectangle rec = GetFontDefault().recs[95];
  SetShapesTexture(GetFontDefault().texture,
                   { rec.x + 1, rec.y + 1, rec.width - 2, rec.height - 2 });
}

static void
loop_esp()
{
  // while (true) {
  tick();
  rlLoadIdentity();
  draw();
  rlDrawRenderBatchActive();

  uint32_t* dst = new uint32_t[ESP_W * ESP_H];

  rlCopyFramebuffer(0, 0, ESP_W, ESP_H, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, dst);

  print_rgba(dst[0]);

  Image img = {
    .data = dst,
    .width = ESP_W,
    .height = ESP_H,
    .mipmaps = 1,
    .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
  };
  ExportImage(img, "out.png");
  system("out.png");
  //}
}

static void
close_esp()
{
  UnloadFontDefault();

  rlglClose();
}

static void
init_pc()
{
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(ESP_W, ESP_H, "birdfight");
  SetExitKey(KEY_NULL);
}

static void
loop_pc()
{
  while (!WindowShouldClose()) {
    tick();
    BeginDrawing();
    draw();
    EndDrawing();
  }
}

static void
close_pc()
{
  CloseWindow();
}

static void
init_platform()
{
#ifdef ESP32
  init_esp();
#else
  init_pc();
#endif
}

static void
loop_platform()
{
#ifdef ESP32
  loop_esp();
#else
  loop_pc();
#endif
}

static void
close_platform()
{
#ifdef ESP32
  close_esp();
#else
  close_pc();
#endif
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