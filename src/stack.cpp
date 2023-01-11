#include "stack.hpp"

#include <cstdio>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

stack::stack(vector3f _origin, vector3f _scale)
{
    origin = _origin;
    scale = _scale;
    set = true;
    pressSpace = false;
    speed = 0.02f;

    srand(glfwGetTime());

    array.push_back({-scale.x, -scale.y, scale.z});
    array.push_back({scale.x, -scale.y, scale.z});
    array.push_back({-scale.x, -scale.y, -scale.z});
    array.push_back({scale.x, -scale.y, -scale.z});
    array.push_back({scale.x, scale.y, -scale.z});
    array.push_back({scale.x, -scale.y, scale.z});
    array.push_back({scale.x, scale.y, scale.z});
    array.push_back({-scale.x, -scale.y, scale.z});
    array.push_back({-scale.x, scale.y, scale.z});
    array.push_back({-scale.x, -scale.y, -scale.z});
    array.push_back({-scale.x, scale.y, -scale.z});
    array.push_back({scale.x, scale.y, -scale.z});
    array.push_back({-scale.x, scale.y, scale.z});
    array.push_back({scale.x, scale.y, scale.z});

    float random1 = rand() % 100;
    float random2 = rand() % 100;
    float random3 = rand() % 100;

    color.x = random1 * 0.01;
    color.y = random2 * 0.01;
    color.z = random3 * 0.01;
}

stack::stack(vector3f _origin, vector3f _scale, bool setOrNot) : stack(_origin, _scale)
{
    set = setOrNot;
    if (!set)
        set_origin();
}

stack::~stack() {}

float stack::get_speed()
{
    return speed;
}

void stack::change_speed(float newSpeed)
{
    speed = newSpeed;
}

void stack::update()
{
    if (!set)
        move_position();
}

void stack::draw_stack()
{
    glBegin(GL_TRIANGLE_STRIP);
    for (vector3f &i : array)
    {
        glVertex3f(origin.x + i.x, origin.y + i.y, origin.z + i.z);
    }

    glEnd();
}

void stack::z_axis_translation()
{
    if (origin.z >= 3.0f)
        speed *= -1;
    else if (origin.z <= -3.0f)
        speed *= -1;

    origin.z += speed;
}

void stack::x_axis_translation()
{
    if (origin.x >= 3.0f)
        speed *= -1;
    else if (origin.x <= -3.0f)
        speed *= -1;

    origin.x += speed;
}

bool stack::change_state_of_set()
{
    set = true;
    return set;
}

void stack::draw()
{
    glPushMatrix();
    glColor3f(color.x, color.y, color.z);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 0.3f, 1.0f);
    draw_stack();
    glPopMatrix();
}

void stack::move_position()
{
    if (selectAxis)
        z_axis_translation();
    else if (!selectAxis)
        x_axis_translation();
}

void stack::next_step(size_t step)
{
    origin.y = (float)step;
}

void stack::set_origin()
{
    srand(glfwGetTime());

    int random = rand() % 100;

    if(random >= 0 && random <= 49)
    {
        selectAxis = true;
        origin.z   += 2.0f;
    }
    else
    {
        selectAxis = false;
        origin.x   += -2.0f;
    }
    
}

vector3f stack::get_scale()
{
    return scale;
}


vector3f stack::get_origin()
{
    return origin;
}

void stack::change_size_stack_x(float newValue)
{
    scale.x = newValue;
}

void stack::change_size_stack_z(float newValue)
{
    scale.z = newValue;
}

void stack::change_x_axis_origin(float newValue)
{
    origin.x = newValue;
}

void stack::change_z_axis_origin(float newValue)
{
    origin.z = newValue;
}

void stack::apply_change_on_stack()
{
    array[0] = {-scale.x, -scale.y, scale.z};
    array[1] = {scale.x, -scale.y, scale.z};
    array[2] = {-scale.x, -scale.y, -scale.z};
    array[3] = {scale.x, -scale.y, -scale.z};
    array[4] = {scale.x, scale.y, -scale.z};
    array[5] = {scale.x, -scale.y, scale.z};
    array[6] = {scale.x, scale.y, scale.z};
    array[7] = {-scale.x, -scale.y, scale.z};
    array[8] = {-scale.x, scale.y, scale.z};
    array[9] = {-scale.x, -scale.y, -scale.z};
    array[10] = {-scale.x, scale.y, -scale.z};
    array[11] = {scale.x, scale.y, -scale.z};
    array[12] = {-scale.x, scale.y, scale.z};
    array[13] = {scale.x, scale.y, scale.z};
}

bool stack::get_selectAxis()
{
    return selectAxis;
}
