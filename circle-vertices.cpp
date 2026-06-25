#include <vector>
#include <cmath>

using namespace std;

int num_h_sides(int h_level) {
    return 3 * (int) round( pow(2, h_level-1) ) - 1;
}

float x_h_coord(int single_h_angle, float h_angle_offset, int pos, float radius) {
    return cos(h_angle_offset + single_h_angle * pos) * radius;
}

float x_h_coord(int single_h_angle, float h_angle_offset, int pos, float radius) {
    return sin(h_angle_offset + single_h_angle * pos) * radius;
}

int num_v_rings(int v_level) {
    return (int) round( pow(2, v_level) );
}

vector<vector<float>> get_circle_vertices(int h_level, int v_level, float radius) {
    int h_sides = num_h_sides(h_level)
    float single_h_angle = 360 / (float) h_sides;
    float l_module = 2 * radius * sin(single_h_angle / 2);

    int v_sides = num_v_rings(v_level) * 2;
    
    float single_v_angle = 360 / v_sides;
}