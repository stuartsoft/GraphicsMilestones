#version 130 

in vec3 fs_color;
in vec4 fs_normal;
in vec4 light_pos;
in vec4 l_vec;
in vec4 v_vec;
in float fs_shinyness;

out vec4 out_Color;

void main() {
    vec4 h_vec = normalize(l_vec + v_vec);
    vec3 light_color = vec3(1.0, 1.0, 1.0);
    float diff_k = clamp(dot(l_vec,normalize(fs_normal)),0,1);
    float amb_k = 0.15;
    float spec_k = max(pow(dot(h_vec,fs_normal),10),0);

    vec3 amb_lighting = fs_color*amb_k;
    vec3 diff_lighting = diff_k*fs_color;
    vec3 spec_lighting = spec_k*light_color*20;

    vec3 final_color = amb_lighting*0.2 + diff_lighting*0.4 + 0.4*spec_lighting;
    out_Color = vec4(final_color, 1.0);
}