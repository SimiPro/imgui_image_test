
#include <iostream>
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#define STB_DEFINE                                                     
#include <stb.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // for & before imgui
    gl3wInit();
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    bool show_another_window = true;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool first_run = true;
    GLuint my_opengl_texture;             
    int my_image_width, my_image_height;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Poll for and process events */
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");


        // texture
        if (first_run) {
            unsigned char* my_image_data = stbi_load("/home/simi/Pictures/shutdown_buttom.jpeg", &my_image_width, &my_image_height, NULL, 4);
            cout << "image height x width: " << my_image_height << " x " << my_image_width << endl;
            // Turn the RGBA pixel data into an OpenGL texture:
            glGenTextures(1, &my_opengl_texture);
            glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
           // glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, my_image_width, my_image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_image_data);
            // Now that we have an OpenGL texture, assuming our imgui rendering function (imgui_impl_xxx.cpp file) takes GLuint as ImTextureID, we can display it:
            first_run = false;
        }

        ImGui::Image((void*)(intptr_t)my_opengl_texture, ImVec2(my_image_width, my_image_height));
        ImGui::ImageButton((void*)(intptr_t)my_opengl_texture, ImVec2(200.f, 200.f));


        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}