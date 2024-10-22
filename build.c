
#define CEBUS_IMPLEMENTATION
#include "libs/cebus.h"

// Global Variables
Str raylib_dir = STR("libs/raylib/");
Str build_dir = STR("build");

// Build Functions
void build_raylib(int platform);
void build_app(int platform);
void help();

// TODO: Refactor Build system to use flags  
int main(int argc, char *argv[]) {
  int platform = 0; // desktop
  if(argc > 1) platform = atoi(argv[1]);
  // build_raylib(platform);
  build_app(platform);
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
// Build Raylib Library

void build_raylib(int platform) {
  if (platform != 0 && platform != 1) {
    printf("platform not supported\n");
    return;
  }

  Str build_dir = STR("build/desktop/");
  if (platform == 1) {
    build_dir = STR("build/web/");
  }

  Arena arena = {0};

  Str raylib_modules[8] = {STR("rcore"),     STR("raudio"),
                          STR("rshapes"),   STR("rmodels"), STR("rtext"),
                          STR("rtextures"), STR("utils")};
  if(platform == 0) raylib_modules[7] = STR("rglfw");
  
  Str desktop_flags[] = {STR("-Wall"),
                         STR("-D_GNU_SOURCE"),
                         STR("-DPLATFORM_DESKTOP_GLFW"),
                         STR("-DGRAPHICS_API_OPENGL_33"),
                         STR("-Wno-missing-braces"),
                         STR("-Werror=pointer-arith"),
                         STR("-fno-strict-aliasing"),
                         STR("-std=c99"),
                         STR("-fPIC"),
                         STR("-O1"),
                         STR("-Werror=implicit-function-declaration"),
                         STR("-D_GLFW_X11"),
                         STR("-I."),
                         STR("-Iexternal/glfw/include")};

  Str web_flags[] = {
      STR("-Wall"),
      STR("-DPLATFORM_WEB"),
      STR("-DGRAPHICS_API_OPENGL_ES2"),
  };

  for (int i = 0; i < ARRAY_LEN(raylib_modules); i++) {
    if(raylib_modules[i].len == 0) continue;
    Cmd cmd = cmd_new(&arena);

    Str src_file = str_append(raylib_dir, raylib_modules[i], &arena);
    src_file = str_append(src_file, STR(".c"), &arena);

    Str obj_file = str_append(build_dir, raylib_modules[i], &arena);
    obj_file = str_append(obj_file, STR(".o"), &arena);

    if (platform == 0) {
      cmd_push(&cmd, STR("gcc"));
      cmd_extend(&cmd, desktop_flags);
    } else if (platform == 1) {
      cmd_push(&cmd, STR("emcc"));
      cmd_extend(&cmd, web_flags);
    }

    cmd_push(&cmd, STR("-c"));
    cmd_push(&cmd, src_file);
    cmd_push(&cmd, STR("-o"));
    cmd_push(&cmd, obj_file);

    cmd_exec_da(ErrPanic, &cmd);
  }

  Cmd cmd = cmd_new(&arena);

  if (platform == 0)
    cmd_push(&cmd, STR("ar"), STR("rcs"),
             str_append(build_dir, STR("libraylib.a"), &arena));
  if (platform == 1)
    cmd_push(&cmd, STR("emar"), STR("rcs"),
             str_append(build_dir, STR("libraylib_web.a"), &arena));

  for (int i = 0; i < ARRAY_LEN(raylib_modules); i++) {
    if(raylib_modules[i].len == 0) continue; 
    Str obj_file = str_append(build_dir, raylib_modules[i], &arena);
    obj_file = str_append(obj_file, STR(".o"), &arena);
    cmd_push(&cmd, obj_file);
  }
  cmd_exec_da(ErrPanic, &cmd);
}

void build_app_desktop(Str src_file_path) {
  Arena arena = {0};

  Str build_dir = STR("build/desktop/");

  Cmd cmd = cmd_new(&arena);

  Str app_path = str_append(build_dir, STR("app"), &arena);

  cmd_push(&cmd, STR("gcc"), STR("-std=c99"), STR("-Iraylib"),
           STR("-o"), app_path, src_file_path);
  cmd_push(&cmd, str_append(STR("-L"), build_dir, &arena), STR("-lraylib"));
  cmd_push(&cmd, STR("-lm"), STR("-lpthread"), STR("-ldl"), STR("-lrt"));

  cmd_exec_da(ErrPanic, &cmd);

  Cmd run = cmd_new(&arena);
  cmd_push(&run, str_append(STR("./"), app_path, &arena));
  cmd_exec_da(ErrPanic, &run);
  return;
}

void build_app_web(Str src_file_path) {
  Arena arena = {0};

  Str build_dir = STR("build/web/");

  Cmd cmd = cmd_new(&arena);

  Str app_path = str_append(build_dir, STR("app"), &arena);

  cmd_push(&cmd, STR("emcc"), STR("-o"));
  cmd_push(&cmd, STR("build/web/index.js"), src_file_path, STR("-Os"),
           STR("-Wall"));
  cmd_push(&cmd, str_append(build_dir, STR("libraylib_web.a"), &arena));
  cmd_push(&cmd, STR("-s"), STR("USE_GLFW=3"), STR("-s"), STR("FULL_ES2=1"),
           STR("-DPLATFORM_WEB"), STR("--preload-file"), STR("assets"));
  cmd_exec_da(ErrPanic, &cmd);

  Cmd run = cmd_new(&arena);
  cmd_push(&run, STR("emrun"), STR("build/web/index.html"));
  cmd_exec_da(ErrPanic, &run);
  return;
}

void build_app(int platform) {
  if (platform != 0 && platform != 1) {
    printf("platform not supported\n");
    return;
  }

  if (platform == 0)
    build_app_desktop(STR("game/main.c"));
  if (platform == 1)
    build_app_web(STR("game/main.c"));
}
