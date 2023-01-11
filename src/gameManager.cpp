#include "gameManager.hpp"

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <math.h>

gameManager::gameManager()
    : pressSpace{false},
      game{true},
      epsilon{0.00f},
      cameraY{0},
      cameraZ{3},
      rotate{0},
      fadeYTransition{0}
{
    stacks.push_back(stack({0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, true));
    stacks.push_back(stack({0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, false));
}

void gameManager::update(GLFWwindow *window)
{
    stacks[stacks.size() - 1].next_step(stacks.size() - 1);
    stacks[stacks.size() - 1].update();

    bool pressKey = glfwGetKey(window, GLFW_KEY_SPACE);
    if (pressKey && !pressSpace && game)
    {
        cut_stack();
        stacks[stacks.size() - 1].apply_change_on_stack();
        stacks[stacks.size() - 1].change_state_of_set();
        if (game)
            stacks.push_back((stack){stacks[stacks.size() - 1].get_origin(), stacks[stacks.size() - 1].get_scale(), false});
    }
    else if (pressKey && !pressSpace && !game)
    {
        restart();
    }

    pressSpace = pressKey;
}

void gameManager::draw(GLFWwindow *window)
{
    glPushMatrix();
    camera();
    if (!game)
        rotate += 1.0f;

    glRotatef(rotate, 0.0f, 1.0f, 0.0f);
    for (size_t i = 0; i < stacks.size(); i++)
    {
        stacks[i].draw();
    }
    glPopMatrix();
}

void gameManager::cut_stack()
{
    float distance = 0;

    if (stacks[stacks.size() - 1].get_selectAxis())
    {
        cut_stack_axis_z();
        if(game)
        {
            distance = (stacks[stacks.size() - 1].get_origin().z + stacks[stacks.size() - 2].get_origin().z) / 2;
            stacks[stacks.size() - 1].change_z_axis_origin(distance);
        }
    }
    if (!stacks[stacks.size() - 1].get_selectAxis())
    {
        cut_stack_axis_x();
        if(game)
        {
            distance = (stacks[stacks.size() - 1].get_origin().x + stacks[stacks.size() - 2].get_origin().x) / 2;
            stacks[stacks.size() - 1].change_x_axis_origin(distance);
        }
    }
}

void gameManager::cut_stack_axis_x()
{
    float max2 = stacks[stacks.size() - 1].get_origin().x + stacks[stacks.size() - 1].get_scale().x;
    float min2 = stacks[stacks.size() - 1].get_origin().x - stacks[stacks.size() - 1].get_scale().x;

    float max1 = stacks[stacks.size() - 2].get_origin().x + stacks[stacks.size() - 2].get_scale().x;
    float min1 = stacks[stacks.size() - 2].get_origin().x - stacks[stacks.size() - 2].get_scale().x;
    float newSizeX = 0;

    if (max2 >= min1 && max2 <= max1)
    {
        min1 = abs(min1);
        min2 = abs(min2);

        float distanceBetweenMin1AndMin2 = 0;

        if (min1 > min2)
            distanceBetweenMin1AndMin2 = min1 - min2;
        else if (min1 < min2)
            distanceBetweenMin1AndMin2 = min2 - min1;

        if (stacks[stacks.size() - 1].get_scale().x > 0)
            newSizeX = stacks[stacks.size() - 1].get_scale().x - (distanceBetweenMin1AndMin2 / 2.f);
        else
            newSizeX = stacks[stacks.size() - 1].get_scale().x + (distanceBetweenMin1AndMin2 / 2.f);
    }
    else if (min2 >= min1 && min2 <= max1)
    {
        max2 = abs(max2);
        max1 = abs(max1);

        float distanceBetweenMax1AndMax2 = 0;

        if (max1 > max2)
            distanceBetweenMax1AndMax2 = max1 - max2;
        else if (max1 < max2)
            distanceBetweenMax1AndMax2 = max2 - max1;

        if (stacks[stacks.size() - 1].get_scale().x > 0)
            newSizeX = stacks[stacks.size() - 1].get_scale().x - (distanceBetweenMax1AndMax2 / 2.f);
        else
            newSizeX = stacks[stacks.size() - 1].get_scale().x + (distanceBetweenMax1AndMax2 / 2.f);
    }
    else
    {
        game = false;
        stacks.pop_back();
    }
    if (newSizeX > epsilon && game)
        stacks[stacks.size() - 1].change_size_stack_x(newSizeX);
    else if (game)
        stacks[stacks.size() - 1].change_x_axis_origin(stacks[stacks.size() - 2].get_origin().x);

}

void gameManager::cut_stack_axis_z()
{
    float max2 = stacks[stacks.size() - 1].get_origin().z + stacks[stacks.size() - 1].get_scale().z;
    float min2 = stacks[stacks.size() - 1].get_origin().z - stacks[stacks.size() - 1].get_scale().z;

    float max1 = stacks[stacks.size() - 2].get_origin().z + stacks[stacks.size() - 2].get_scale().z;
    float min1 = stacks[stacks.size() - 2].get_origin().z - stacks[stacks.size() - 2].get_scale().z;
    float newSizeZ = 0;

    if (max2 >= min1 && max2 <= max1)
    {
        min1 = abs(min1);
        min2 = abs(min2);

        float distanceBetweenMin1AndMin2 = 0;

        if (min1 > min2)
            distanceBetweenMin1AndMin2 = min1 - min2;
        else if (min1 < min2)
            distanceBetweenMin1AndMin2 = min2 - min1;

        if (stacks[stacks.size() - 1].get_scale().z > 0)
            newSizeZ = stacks[stacks.size() - 1].get_scale().z - (distanceBetweenMin1AndMin2 / 2.f);
        else
            newSizeZ = stacks[stacks.size() - 1].get_scale().z + (distanceBetweenMin1AndMin2 / 2.f);
    }
    else if (min2 >= min1 && min2 <= max1)
    {

        max2 = abs(max2);
        max1 = abs(max1);

        float distanceBetweenMax1AndMax2 = 0;

        if (max1 >= max2)
            distanceBetweenMax1AndMax2 = max1 - max2;
        else if (max1 < max2)
            distanceBetweenMax1AndMax2 = max2 - max1;

        if (stacks[stacks.size() - 1].get_scale().z > 0)
            newSizeZ = stacks[stacks.size() - 1].get_scale().z - (distanceBetweenMax1AndMax2 / 2.f);
        else
            newSizeZ = stacks[stacks.size() - 1].get_scale().z + (distanceBetweenMax1AndMax2 / 2.f);
    }
    else
    {
        game = false;
        stacks.pop_back();
    }

    if (newSizeZ > epsilon && game)
        stacks[stacks.size() - 1].change_size_stack_z(newSizeZ);
    else if (game)
    {
        stacks[stacks.size() - 1].change_z_axis_origin(stacks[stacks.size() - 2].get_origin().z);
    }   
}

void gameManager::camera()
{
    if (!game && cameraY > ((float)stacks.size() / 2.f) * 0.3f )
    {
        cameraY -= 0.01f;
        cameraZ += 0.02f;
    }
    else if (game)
    {
        cameraY = stacks.size() * 0.3f;
        cameraZ = 3.00f;
    }

        gluLookAt(0.0, cameraY + 3.0, cameraZ,
                  0.0, cameraY, 0.0,
                  0.0, 1.0, 0.0);
}

void gameManager::restart()
{
    stacks.clear();
    stacks.push_back(stack({0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, true));
    stacks.push_back(stack({0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, false));
    rotate = 0.00f;
    game = true;
}

