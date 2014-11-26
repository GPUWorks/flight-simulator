attribute vec3 vertex;
uniform mat4 MVP;
void main(void)
{
    gl_Position = MVP * vec4(vertex, 1.0);
}
