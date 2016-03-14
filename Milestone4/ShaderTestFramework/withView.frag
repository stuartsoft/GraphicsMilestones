#version 130 

in vec3 fs_color;
in vec4 fs_normal;
in vec4 l_pos;
in vec4 l_vec;

out vec4 out_Color;

void main() {
    float diff_intensity = dot(l_vec,fs_normal);
    vec3 amb_color = vec3(0.5, 0.5, 0.5);
    out_Color = vec4(fs_color*diff_intensity, 1.0);
}