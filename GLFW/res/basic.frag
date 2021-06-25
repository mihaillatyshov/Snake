#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA
{
    in vec4 position;
    in vec4 color;
} fs_in;

void main(){
    float intensity = 1.0 / length(fs_in.position.xy - light_pos);
    color = colour * intensity;
    color = fs_in.color * intensity;
}
