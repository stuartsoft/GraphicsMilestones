#version 130 

in vec3 fs_color;
in vec4 fs_normal;
in vec4 l_pos;
in vec4 l_vec;
in vec4 h_vec;

out vec4 out_Color;

void main() {
    vec3 light_color = vec3(1.0, 1.0, 1.0);
    float diff_i = dot(l_vec,fs_normal);
    vec3 amb_color = vec3(1.0, 1.0, 1.0);
    float amb_i = 0.3;
    float spec = pow(dot(h_vec,fs_normal),25.0);

    vec3 amb_lighting = amb_color*fs_color*amb_i;
    vec3 diff_lighting = light_color*diff_i*fs_color;
    vec3 spec_lighting = light_color*fs_color*spec;

    vec3 final_color = spec_lighting;
    out_Color = vec4(final_color, 1.0);
}