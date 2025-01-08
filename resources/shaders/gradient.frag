#version 450 core

in vec2 uv;
out vec4 color;

uniform vec4 color1;
uniform vec4 color2;
uniform float time;

void main(){
//    float speed = 0.5;
//    float offset_ = fract(uv.x + time * speed);

//    vec4 color_1_2 = mix(color1, color2, offset_ + 0.1);
//    color = mix(color_1_2, color1, offset_ - 0.1);
    color = mix(color1, color2, uv.x);
}
