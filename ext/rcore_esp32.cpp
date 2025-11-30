#include <config.h>
#include <raylib.h>
#include <rgestures.h>
#include <utils.h>

extern "C"
{
#define MAX_GAMEPAD_NAME_LENGTH 128

  //----------------------------------------------------------------------------------
  // Types and Structures Definition
  //----------------------------------------------------------------------------------
  typedef struct
  {
    int x;
    int y;
  } Point;
  typedef struct
  {
    unsigned int width;
    unsigned int height;
  } Size;

  // Core global state context data
  typedef struct CoreData
  {
    struct
    {
      const char* title;  // Window text title const pointer
      unsigned int flags; // Configuration flags (bit based), keeps window state
      bool ready;         // Check if window has been initialized successfully
      bool fullscreen;    // Check if fullscreen mode is enabled
      bool shouldClose;   // Check if window set for closing
      bool resizedLastFrame; // Check if window has been resized last frame
      bool eventWaiting;     // Wait for events before ending frame
      bool usingFbo; // Using FBO (RenderTexture) for rendering instead of
                     // default framebuffer

      Point position;         // Window position (required on fullscreen toggle)
      Point previousPosition; // Window previous position (required on
                              // borderless windowed toggle)
      Size
        display; // Display width and height (monitor, device-screen, LCD, ...)
      Size screen;         // Screen width and height (used render area)
      Size previousScreen; // Screen previous width and height (required on
                           // borderless windowed toggle)
      Size
        currentFbo; // Current render width and height (depends on active fbo)
      Size render; // Framebuffer width and height (render area, including black
                   // bars if required)
      Point renderOffset; // Offset from render area (must be divided by 2)
      Size screenMin; // Screen minimum width and height (for resizable window)
      Size screenMax; // Screen maximum width and height (for resizable window)
      Matrix screenScale; // Matrix to scale screen (framebuffer rendering)

      char**
        dropFilepaths; // Store dropped files paths pointers (provided by GLFW)
      unsigned int dropFileCount; // Count dropped files strings
    } Window;
    struct
    {
      const char* basePath; // Base path for data storage
    } Storage;
    struct
    {
      struct
      {
        int exitKey;                              // Default exit key
        char currentKeyState[MAX_KEYBOARD_KEYS];  // Registers current frame key
                                                  // state
        char previousKeyState[MAX_KEYBOARD_KEYS]; // Registers previous frame
                                                  // key state

        // NOTE: Since key press logic involves comparing previous vs currrent
        // key state, key repeats needs to be handled specially
        char keyRepeatInFrame[MAX_KEYBOARD_KEYS]; // Registers key repeats for
                                                  // current frame

        int keyPressedQueue[MAX_KEY_PRESSED_QUEUE]; // Input keys queue
        int keyPressedQueueCount;                   // Input keys queue count

        int charPressedQueue[MAX_CHAR_PRESSED_QUEUE]; // Input characters queue
                                                      // (unicode)
        int charPressedQueueCount; // Input characters queue count
      } Keyboard;
      struct
      {
        Vector2 offset;           // Mouse offset
        Vector2 scale;            // Mouse scaling
        Vector2 currentPosition;  // Mouse position on screen
        Vector2 previousPosition; // Previous mouse position
        Vector2 lockedPosition;   // Mouse position when locked

        int cursor;          // Tracks current mouse cursor
        bool cursorHidden;   // Track if cursor is hidden
        bool cursorLocked;   // Track if cursor is locked (disabled)
        bool cursorOnScreen; // Tracks if cursor is inside client area

        char currentButtonState[MAX_MOUSE_BUTTONS];  // Registers current mouse
                                                     // button state
        char previousButtonState[MAX_MOUSE_BUTTONS]; // Registers previous mouse
                                                     // button state
        Vector2 currentWheelMove;  // Registers current mouse wheel variation
        Vector2 previousWheelMove; // Registers previous mouse wheel variation
      } Mouse;
      struct
      {
        int pointCount;                     // Number of touch points active
        int pointId[MAX_TOUCH_POINTS];      // Point identifiers
        Vector2 position[MAX_TOUCH_POINTS]; // Touch position on screen
        char
          currentTouchState[MAX_TOUCH_POINTS]; // Registers current touch state
        char previousTouchState[MAX_TOUCH_POINTS]; // Registers previous touch
                                                   // state
      } Touch;
      struct
      {
        int lastButtonPressed; // Register last gamepad button pressed
        int
          axisCount[MAX_GAMEPADS]; // Register number of available gamepad axes
        bool ready[MAX_GAMEPADS];  // Flag to know if gamepad is ready
        char name[MAX_GAMEPADS][MAX_GAMEPAD_NAME_LENGTH]; // Gamepad name holder
        char currentButtonState[MAX_GAMEPADS]
                               [MAX_GAMEPAD_BUTTONS]; // Current gamepad buttons
                                                      // state
        char previousButtonState[MAX_GAMEPADS]
                                [MAX_GAMEPAD_BUTTONS];   // Previous gamepad
                                                         // buttons state
        float axisState[MAX_GAMEPADS][MAX_GAMEPAD_AXES]; // Gamepad axes state
      } Gamepad;
    } Input;
    struct
    {
      double current;  // Current time measure
      double previous; // Previous time measure
      double update;   // Time measure for frame update
      double draw;     // Time measure for frame draw
      double frame;    // Time measure for one frame
      double target;   // Desired time for one frame, if 0 not applied
      unsigned long long int base; // Base time measure for hi-res timer
                                   // (PLATFORM_ANDROID, PLATFORM_DRM)
      unsigned int frameCounter;   // Frame counter
    } Time;
  } CoreData;

  //----------------------------------------------------------------------------------
  // Global Variables Definition
  //----------------------------------------------------------------------------------
  extern CoreData CORE; // Global CORE state context

  //----------------------------------------------------------------------------------
  // Module Functions Definition: Window and Graphics Device
  //----------------------------------------------------------------------------------

  // Check if application should close
  bool WindowShouldClose(void)
  {
    if (CORE.Window.ready)
      return CORE.Window.shouldClose;
    else
      return true;
  }

  // Toggle fullscreen mode
  void ToggleFullscreen(void)
  {
    TRACELOG(LOG_WARNING,
             "ToggleFullscreen() not available on target platform");
  }

  // Toggle borderless windowed mode
  void ToggleBorderlessWindowed(void)
  {
    TRACELOG(LOG_WARNING,
             "ToggleBorderlessWindowed() not available on target platform");
  }

  // Set window state: maximized, if resizable
  void MaximizeWindow(void)
  {
    TRACELOG(LOG_WARNING, "MaximizeWindow() not available on target platform");
  }

  // Set window state: minimized
  void MinimizeWindow(void)
  {
    TRACELOG(LOG_WARNING, "MinimizeWindow() not available on target platform");
  }

  // Restore window from being minimized/maximized
  void RestoreWindow(void)
  {
    TRACELOG(LOG_WARNING, "RestoreWindow() not available on target platform");
  }

  // Set window configuration state using flags
  void SetWindowState(unsigned int flags)
  {
    TRACELOG(LOG_WARNING, "SetWindowState() not available on target platform");
  }

  // Clear window configuration state flags
  void ClearWindowState(unsigned int flags)
  {
    TRACELOG(LOG_WARNING,
             "ClearWindowState() not available on target platform");
  }

  // Set icon for window
  void SetWindowIcon(Image image)
  {
    TRACELOG(LOG_WARNING, "SetWindowIcon() not available on target platform");
  }

  // Set icon for window
  void SetWindowIcons(Image* images, int count)
  {
    TRACELOG(LOG_WARNING, "SetWindowIcons() not available on target platform");
  }

  // Set title for window
  void SetWindowTitle(const char* title)
  {
    CORE.Window.title = title;
  }

  // Set window position on screen (windowed mode)
  void SetWindowPosition(int x, int y)
  {
    TRACELOG(LOG_WARNING,
             "SetWindowPosition() not available on target platform");
  }

  // Set monitor for the current window
  void SetWindowMonitor(int monitor)
  {
    TRACELOG(LOG_WARNING,
             "SetWindowMonitor() not available on target platform");
  }

  // Set window minimum dimensions (FLAG_WINDOW_RESIZABLE)
  void SetWindowMinSize(int width, int height)
  {
    CORE.Window.screenMin.width = width;
    CORE.Window.screenMin.height = height;
  }

  // Set window maximum dimensions (FLAG_WINDOW_RESIZABLE)
  void SetWindowMaxSize(int width, int height)
  {
    CORE.Window.screenMax.width = width;
    CORE.Window.screenMax.height = height;
  }

  // Set window dimensions
  void SetWindowSize(int width, int height)
  {
    TRACELOG(LOG_WARNING, "SetWindowSize() not available on target platform");
  }

  // Set window opacity, value opacity is between 0.0 and 1.0
  void SetWindowOpacity(float opacity)
  {
    TRACELOG(LOG_WARNING,
             "SetWindowOpacity() not available on target platform");
  }

  // Set window focused
  void SetWindowFocused(void)
  {
    TRACELOG(LOG_WARNING,
             "SetWindowFocused() not available on target platform");
  }

  // Get native window handle
  void* GetWindowHandle(void)
  {
    TRACELOG(LOG_WARNING,
             "GetWindowHandle() not implemented on target platform");
    return NULL;
  }

  // Get number of monitors
  int GetMonitorCount(void)
  {
    TRACELOG(LOG_WARNING,
             "GetMonitorCount() not implemented on target platform");
    return 1;
  }

  // Get current monitor where window is placed
  int GetCurrentMonitor(void)
  {
    TRACELOG(LOG_WARNING,
             "GetCurrentMonitor() not implemented on target platform");
    return 0;
  }

  // Get selected monitor position
  Vector2 GetMonitorPosition(int monitor)
  {
    TRACELOG(LOG_WARNING,
             "GetMonitorPosition() not implemented on target platform");
    return Vector2{ 0, 0 };
  }

  // Get selected monitor width (currently used by monitor)
  int GetMonitorWidth(int monitor)
  {
    TRACELOG(LOG_WARNING,
             "GetMonitorWidth() not implemented on target platform");
    return 0;
  }

  // Get selected monitor height (currently used by monitor)
  int GetMonitorHeight(int monitor)
  {
    TRACELOG(LOG_WARNING,
             "GetMonitorHeight() not implemented on target platform");
    return 0;
  }

  // Get selected monitor physical width in millimetres
  int GetMonitorPhysicalWidth(int monitor)
  {
    TRACELOG(LOG_WARNING,
             "GetMonitorPhysicalWidth() not implemented on target platform");
    return 0;
  }

  // Get selected monitor physical height in millimetres
  int GetMonitorPhysicalHeight(int monitor)
  {
    TRACELOG(LOG_WARNING,
             "GetMonitorPhysicalHeight() not implemented on target platform");
    return 0;
  }

  // Get selected monitor refresh rate
  int GetMonitorRefreshRate(int monitor)
  {
    TRACELOG(LOG_WARNING,
             "GetMonitorRefreshRate() not implemented on target platform");
    return 0;
  }

  // Get the human-readable, UTF-8 encoded name of the selected monitor
  const char* GetMonitorName(int monitor)
  {
    TRACELOG(LOG_WARNING,
             "GetMonitorName() not implemented on target platform");
    return "";
  }

  // Get window position XY on monitor
  Vector2 GetWindowPosition(void)
  {
    TRACELOG(LOG_WARNING,
             "GetWindowPosition() not implemented on target platform");
    return Vector2{ 0, 0 };
  }

  // Get window scale DPI factor for current monitor
  Vector2 GetWindowScaleDPI(void)
  {
    TRACELOG(LOG_WARNING,
             "GetWindowScaleDPI() not implemented on target platform");
    return Vector2{ 1.0f, 1.0f };
  }

  // Set clipboard text content
  void SetClipboardText(const char* text)
  {
    TRACELOG(LOG_WARNING,
             "SetClipboardText() not implemented on target platform");
  }

  // Get clipboard text content
  // NOTE: returned string is allocated and freed by GLFW
  const char* GetClipboardText(void)
  {
    TRACELOG(LOG_WARNING,
             "GetClipboardText() not implemented on target platform");
    return NULL;
  }

  // Get clipboard image
  Image GetClipboardImage(void)
  {
    Image image = { 0 };

    TRACELOG(LOG_WARNING,
             "GetClipboardImage() not implemented on target platform");

    return image;
  }

  // Show mouse cursor
  void ShowCursor(void)
  {
    CORE.Input.Mouse.cursorHidden = false;
  }

  // Hides mouse cursor
  void HideCursor(void)
  {
    CORE.Input.Mouse.cursorHidden = true;
  }

  // Enables cursor (unlock cursor)
  void EnableCursor(void)
  {
    // Set cursor position in the middle
    SetMousePosition(CORE.Window.screen.width / 2,
                     CORE.Window.screen.height / 2);

    CORE.Input.Mouse.cursorHidden = false;
  }

  // Disables cursor (lock cursor)
  void DisableCursor(void)
  {
    // Set cursor position in the middle
    SetMousePosition(CORE.Window.screen.width / 2,
                     CORE.Window.screen.height / 2);

    CORE.Input.Mouse.cursorHidden = true;
  }

  // Swap back buffer with front buffer (screen drawing)
  void SwapScreenBuffer(void) {}

  //----------------------------------------------------------------------------------
  // Module Functions Definition: Misc
  //----------------------------------------------------------------------------------

  // Get elapsed time measure in seconds since InitTimer()
  double GetTime(void)
  {
    return 0.0;
  }

  void OpenURL(const char* url) {}

  //----------------------------------------------------------------------------------
  // Module Functions Definition: Inputs
  //----------------------------------------------------------------------------------

  // Set internal gamepad mappings
  int SetGamepadMappings(const char* mappings)
  {
    TRACELOG(LOG_WARNING,
             "SetGamepadMappings() not implemented on target platform");
    return 0;
  }

  // Set gamepad vibration
  void SetGamepadVibration(int gamepad,
                           float leftMotor,
                           float rightMotor,
                           float duration)
  {
    TRACELOG(LOG_WARNING,
             "SetGamepadVibration() not implemented on target platform");
  }

  // Set mouse position XY
  void SetMousePosition(int x, int y)
  {
    CORE.Input.Mouse.currentPosition = Vector2{ (float)x, (float)y };
    CORE.Input.Mouse.previousPosition = CORE.Input.Mouse.currentPosition;
  }

  // Set mouse cursor
  void SetMouseCursor(int cursor)
  {
    TRACELOG(LOG_WARNING,
             "SetMouseCursor() not implemented on target platform");
  }

  // Get physical key name.
  const char* GetKeyName(int key)
  {
    TRACELOG(LOG_WARNING, "GetKeyName() not implemented on target platform");
    return "";
  }

  // Register all input events
  void PollInputEvents(void)
  {
#if defined(SUPPORT_GESTURES_SYSTEM)
    // NOTE: Gestures update must be called every frame to reset gestures
    // correctly because ProcessGestureEvent() is just called on an event, not
    // every frame
    UpdateGestures();
#endif

    // Reset keys/chars pressed registered
    CORE.Input.Keyboard.keyPressedQueueCount = 0;
    CORE.Input.Keyboard.charPressedQueueCount = 0;

    // Reset key repeats
    for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
      CORE.Input.Keyboard.keyRepeatInFrame[i] = 0;

    // Reset last gamepad button/axis registered state
    CORE.Input.Gamepad.lastButtonPressed = 0; // GAMEPAD_BUTTON_UNKNOWN
    // CORE.Input.Gamepad.axisCount = 0;

    // Register previous touch states
    for (int i = 0; i < MAX_TOUCH_POINTS; i++)
      CORE.Input.Touch.previousTouchState[i] =
        CORE.Input.Touch.currentTouchState[i];

    // Reset touch positions
    // TODO: It resets on target platform the mouse position and not filled
    // again until a move-event, so, if mouse is not moved it returns a (0, 0)
    // position... this behaviour should be reviewed!
    for (int i = 0; i < MAX_TOUCH_POINTS; i++)
      CORE.Input.Touch.position[i] = Vector2{ 0, 0 };

    // Register previous keys states
    // NOTE: Android supports up to 260 keys
    for (int i = 0; i < 260; i++) {
      CORE.Input.Keyboard.previousKeyState[i] =
        CORE.Input.Keyboard.currentKeyState[i];
      CORE.Input.Keyboard.keyRepeatInFrame[i] = 0;
    }

    // TODO: Poll input events for current platform
  }

  //----------------------------------------------------------------------------------
  // Module Internal Functions Definition
  //----------------------------------------------------------------------------------

  // Initialize platform: graphics, inputs and more
  int InitPlatform(void)
  {
    CORE.Window.ready = true;

    CORE.Window.render.width = CORE.Window.screen.width;
    CORE.Window.render.height = CORE.Window.screen.height;
    CORE.Window.currentFbo.width = CORE.Window.render.width;
    CORE.Window.currentFbo.height = CORE.Window.render.height;

    TRACELOG(LOG_INFO, "DISPLAY: Device initialized successfully");
    TRACELOG(LOG_INFO,
             "    > Display size: %i x %i",
             CORE.Window.display.width,
             CORE.Window.display.height);
    TRACELOG(LOG_INFO,
             "    > Screen size:  %i x %i",
             CORE.Window.screen.width,
             CORE.Window.screen.height);
    TRACELOG(LOG_INFO,
             "    > Render size:  %i x %i",
             CORE.Window.render.width,
             CORE.Window.render.height);
    TRACELOG(LOG_INFO,
             "    > Viewport offsets: %i, %i",
             CORE.Window.renderOffset.x,
             CORE.Window.renderOffset.y);

    CORE.Time.previous = GetTime(); // InitTimer()

    // TODO: Initialize storage system
    CORE.Storage.basePath = GetWorkingDirectory();

    TRACELOG(LOG_INFO, "PLATFORM: ESP32: Initialized successfully");

    return 0;
  }

  // Close platform
  void ClosePlatform(void)
  {
    // TODO: De-initialize graphics, inputs and more
  }
}