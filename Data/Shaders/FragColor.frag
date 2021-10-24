uniform vec4 u_ObjectColor;

void main()
{
    gl_FragColor = u_ObjectColor;//Draw the color of the uniform being set in C++ code
}
