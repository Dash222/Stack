#ifndef __STACK_H__
#define __STACK_H__

#include <math.h>
#include <vector>
#include "vector.hpp"

class stack
{
private:
    float speed;
    vector3f origin;
    vector3f scale;
    vector3f color;
    bool set;
    bool pressSpace;
    bool selectAxis;
    std::vector<vector3f> array;

public:
    stack(vector3f _origin, vector3f _scale);
    stack(vector3f _origin, vector3f _scale, bool setOrNot);
    ~stack();

    void update();
    float get_speed();
    void move_position();
    void change_speed(float newSpeed);
    void draw_stack();
    void draw();
    void z_axis_translation();
    void x_axis_translation();
    void next_step(size_t step);
    bool change_state_of_set();
    vector3f get_scale();
    void set_origin();
    vector3f get_origin();
    void change_size_stack_x(float newValue);
    void change_size_stack_z(float newValue);
    void change_x_axis_origin(float newValue);
    void change_z_axis_origin(float newValue);
    void apply_change_on_stack();
    bool get_selectAxis();
};

void display_cube();
void initial_block();
#endif