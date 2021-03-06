#version 130

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform vec4 u_camVecLocation;

in vec3 vs_color;
in vec4 vs_normal;
in vec4 vs_position;
in float vs_shinyness;

out vec3 fs_color;
out vec4 fs_normal;
out float fs_shinyness;
out vec4 light_pos;
out vec4 l_vec;
out vec4 v_vec;

void main() { 
  //gl_Position is built-in
  fs_color = vs_color;
  fs_shinyness = vs_shinyness;
  light_pos = u_viewMatrix* vec4(0.0, 0.0, -3, 1.0);
  gl_Position = u_viewMatrix * u_modelMatrix * vs_position;
  fs_normal = u_viewMatrix * u_modelMatrix * vs_normal;
  fs_normal = normalize(fs_normal);
  v_vec = normalize((u_camVecLocation) - gl_Position);
  l_vec = normalize(light_pos - gl_Position);
}