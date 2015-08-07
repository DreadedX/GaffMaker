#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;
out vec4 fragmentColor;

uniform mat4 mvpMatrix;
uniform vec4 vertexColor;
uniform int index;

void main() {
    vec4 v = vec4(vertexPosition_modelspace, 1);
    gl_Position = mvpMatrix * v;
    
    UV = vertexUV;
    UV.x += index * 0.012195f;

    fragmentColor = vertexColor;
}
