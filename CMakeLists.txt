cmake_minimum_required(VERSION 2.8)

project(simi_test_imgui)

add_subdirectory(glfw)

find_package(OpenGL REQUIRED)

set (IMGUI_SOURCES
      "imgui/imgui.h"
      "imgui/imconfig.h"
      "imgui/imgui_internal.h"
      "imgui/imstb_rectpack.h"
      "imgui/imstb_textedit.h"
      "imgui/imstb_truetype.h"
      "imgui/imgui.cpp"
      "imgui/imgui_demo.cpp"
      "imgui/imgui_draw.cpp"
      "imgui/imgui_widgets.cpp"
      "imgui/examples/imgui_impl_glfw.h"
      "imgui/examples/imgui_impl_opengl3.h"
      "imgui/examples/imgui_impl_glfw.cpp"
      "imgui/examples/imgui_impl_opengl3.cpp"
      "imgui/examples/libs/gl3w/GL/gl3w.c"
      "imgui/examples/libs/gl3w/GL/gl3w.h"
      "imgui/examples/libs/gl3w/GL/glcorearb.h"
      )


#message("${IMGUI_SOURCES}")

add_executable(app main.cpp ${GL3W} ${IMGUI_SOURCES})

target_include_directories(app PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(app PUBLIC imgui/examples/libs/gl3w)
target_include_directories(app PUBLIC imgui)


target_link_libraries(app glfw ${OPENGL_gl_LIBRARY})

