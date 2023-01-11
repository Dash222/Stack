#include <cstdio>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "gameManager.hpp"


void errorGLFW(int code,const char* msg)
{
    fprintf(stderr, "Error (%d): %s\n", code, msg);
}

int main()
{
    glfwSetErrorCallback(errorGLFW);
    if (!glfwInit())
    {
        printf("failed to initialize GLFW.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Stack", nullptr, nullptr);
    if (!window) 
    {
        fprintf(stderr, "glfwCreateWindow failed.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGL())
    {
        fprintf(stderr, "gladLoadGL failed.\n");
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1); // enable v-sync

    gameManager game;
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
	    gluPerspective(59.0, (float)1280.f/(float)720.f, 0.001, 1000.0);

        {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            
            game.update(window);
            game.draw(window);
        }

        // Present buffer
        glfwSwapBuffers(window);
    }    
    glfwTerminate();
    return 0;
}