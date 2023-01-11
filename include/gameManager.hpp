#pragma once
#include <vector>
#include "stack.hpp"

struct GLFWwindow;

class gameManager
{
private:
    std::vector<stack> stacks;
    bool pressSpace;
    bool game;
    float epsilon;
    float cameraY;
    float cameraZ;
    float rotate;
    float fadeYTransition;
public:
    gameManager();
    ~gameManager() = default;
    void update(GLFWwindow* window);
    void draw(GLFWwindow *window);
    void cut_stack();
    void cut_stack_axis_x();
    void cut_stack_axis_z();
    void camera();
    void restart();
};
