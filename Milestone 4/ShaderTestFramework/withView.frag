#version 130 

in vec3 fs_color;
in vec4 fs_normal;
in vec4 light_pos;
in vec4 l_vec;
in vec4 h_vec;

out vec4 out_Color;

void main() {
    vec3 light_color = vec3(1.0, 1.0, 1.0);
    float diff_k = max(dot(l_vec,fs_normal),0) * 1.0;
    float amb_k = 0.2;
    float spec_k = pow(dot(h_vec,fs_normal),25.0);

    vec3 amb_lighting = fs_color*amb_k;
    vec3 diff_lighting = diff_k*fs_color;
    vec3 spec_lighting = light_color*fs_color*spec_k;

    vec3 final_color = diff_lighting;
    out_Color = vec4(final_color, 1.0);
}