attribute vec3 vertex;
uniform mat4 MVP;

varying vec3 color;

void main(void)
{
    color = vertex;
    gl_Position = MVP * vec4(vertex, 1.0);
}
