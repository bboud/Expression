#ifndef CONFIG
#define CONFIG

#define WINDOW_NAME "Graphics"
#define WINDOW_HEIGHT 1920
#define WINDOW_WIDTH 1080
#define DARK_COLORS
#define DEBUG

#ifdef __APPLE__
#define GLSL_VERSION "#version 330"
#else
#define GLSL_VERSION "#version 140"
#endif
#endif