#include <vector>
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include "../support/context.hpp"
#include "../support/error.hpp"

// Struct to store a rectangle with its corners and color
struct Rectangle {
    Vec2f minCorner;
    Vec2f maxCorner;
    ColorU8_sRGB color;
};

namespace {
    bool pro = false;
    double Mx, My;
    Vec2f aMinCorner, aMaxCorner;
    std::vector<Rectangle> rectangles; // List of rectangles
    constexpr int kInitialWindowWidth = 1280;
    constexpr int kInitialWindowHeight = 720;
    constexpr char const* kWindowTitle = "COMP3811-Exercise 1";

    // Callback to capture mouse motion
    void glfw_cb_motion_(GLFWwindow*, double aMouseXPos, double aMouseYPos) {
        Mx = aMouseXPos;
        My = aMouseYPos;
    }

    // Callback to capture mouse button clicks
    void glfw_cb_button_(GLFWwindow*, int aButton, int aAction, int) {
        if (aAction == GLFW_PRESS && aButton == GLFW_MOUSE_BUTTON_LEFT) {
            if (!pro) {
                // First click: set the first corner
                aMinCorner = Vec2f(Mx, My);
                pro = true;
                std::printf("First corner: (%.2f, %.2f)\n", Mx, My);
            }
            else {
                // Second click: set the second corner and store the rectangle
                aMaxCorner = Vec2f(Mx, My);
                rectangles.push_back({ aMinCorner, aMaxCorner, {255, 0, 0} }); // Store red rectangle
                pro = false;
                std::printf("Second corner: (%.2f, %.2f)\n", Mx, My);
            }
        }
    }

    // Callback for keyboard input
    void glfw_callback_key_(GLFWwindow* aWindow, int aKey, int, int aAction, int) {
        if (aKey == GLFW_KEY_ESCAPE && aAction == GLFW_PRESS) {
            glfwSetWindowShouldClose(aWindow, GLFW_TRUE); 
        }
    }

    // Error callback for GLFW
    void glfw_callback_error_(int error, const char* description) {
        std::fprintf(stderr, "GLFW Error: %s (%d)\n", description, error);
    }

    // Cleanup helper for GLFW
    struct GLFWCleanupHelper {
        ~GLFWCleanupHelper() { glfwTerminate(); }
    };
}

int main() try {
    if (GLFW_TRUE != glfwInit()) {
        const char* msg = nullptr;
        int ecode = glfwGetError(&msg);
        throw Error("glfwInit() failed with '%s' (%d)", msg, ecode);
    }

    // Ensure that we call glfwTerminate() at the end of the program.
    GLFWCleanupHelper cleanupHelper;

    glfwSetErrorCallback(glfw_callback_error_);

    // Window hints for GLFW
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#if !defined(__APPLE__)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if !defined(NDEBUG)
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(kInitialWindowWidth, kInitialWindowHeight, kWindowTitle, nullptr, nullptr);
    if (!window) {
        const char* msg = nullptr;
        int ecode = glfwGetError(&msg);
        throw Error("glfwCreateWindow() failed with '%s' (%d)", msg, ecode);
    }

    // Get the framebuffer size and adjust for high DPI (if necessary)
    int iwidth, iheight;
    glfwGetFramebufferSize(window, &iwidth, &iheight);
    float wscale = 1.f, hscale = 1.f;
#if defined(__APPLE__)
    glfwGetWindowContentScale(window, &wscale, &hscale);
#endif
    const std::uint32_t fbwidth = static_cast<std::uint32_t>(iwidth / wscale);
    const std::uint32_t fbheight = static_cast<std::uint32_t>(iheight / hscale);

    // Register callbacks
    glfwSetKeyCallback(window, glfw_callback_key_);
    glfwSetCursorPosCallback(window, glfw_cb_motion_);
    glfwSetMouseButtonCallback(window, glfw_cb_button_);

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    Context context(fbwidth, fbheight);
    Surface surface(fbwidth, fbheight);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Let GLFW process events
        glfwWaitEvents();

        // Clear the surface
        surface.clear();

        // Draw all stored rectangles
        for (const auto& rect : rectangles) {
            draw_rectangle_solid(surface, rect.minCorner, rect.maxCorner, rect.color);
        }

        // Draw the surface to the context
        context.draw(surface);

        // Swap buffers (display the result)
        glfwSwapBuffers(window);
    }

    return 0;
}
catch (std::exception const& eErr) {
    //std::fprintf(stderr, "Top-level Exception (%s):\n", typeid(eErr).name());
    std::fprintf(stderr, "%s\n", eErr.what());
    return 1;
}
