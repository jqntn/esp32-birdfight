#include <cstdint>
#include <cstdio>
#include <ctime>
#include <process.h>
#include <raylib.h>
#include <rlgl.h>

extern "C"
{
  void LoadFontDefault(void);
  void UnloadFontDefault(void);
}

#define PRINT_RGBA(col)                                                        \
  printf("RGBA(%d, %d, %d, %d)\n",                                             \
         (col) & 0xFF,                                                         \
         ((col) >> 8) & 0xFF,                                                  \
         ((col) >> 16) & 0xFF,                                                 \
         ((col) >> 24) & 0xFF)

int
main()
{
  SetConfigFlags(FLAG_WINDOW_TOPMOST);
  InitWindow(320, 240, "birdfight");
  SetExitKey(KEY_NULL);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RED);
    DrawCircle(320 * 0.5f, 240 * 0.5f, 100.0f, GREEN);
    EndDrawing();
    SwapScreenBuffer();
    PollInputEvents();
  }

  CloseWindow();

  /**/

  SetRandomSeed((unsigned int)time(NULL));

  rlglInit(320, 240);

  LoadFontDefault();
  Rectangle rec = GetFontDefault().recs[95];
  SetShapesTexture(
    GetFontDefault().texture,
    Rectangle{ rec.x + 1, rec.y + 1, rec.width - 2, rec.height - 2 });

  rlViewport(0, 0, 320, 240);
  rlMatrixMode(RL_PROJECTION);
  rlLoadIdentity();
  rlOrtho(0.0, 320.0, 240.0, 0.0, 0.0, 1.0);
  rlMatrixMode(RL_MODELVIEW);
  rlLoadIdentity();

  BeginDrawing();
  ClearBackground(RED);
  DrawCircle(320 * 0.5f, 240 * 0.5f, 100.0f, GREEN);
  EndDrawing();

  uint32_t* dst = new uint32_t[320 * 240];
  rlCopyFramebuffer(0, 0, 320, 240, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, dst);

  for (int i = 0; i < 320 * 240; i++) {
    uint32_t c = dst[i];
    dst[i] =
      (c & 0xFF00FF00) | ((c & 0x000000FF) << 16) | ((c & 0x00FF0000) >> 16);
  }

  uint32_t c = dst[0];
  PRINT_RGBA(c);

  Image img = {
    .data = dst,
    .width = 320,
    .height = 240,
    .mipmaps = 1,
    .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
  };
  ExportImage(img, "out.png");
  system("out.png");

  UnloadFontDefault();

  rlglClose();
}