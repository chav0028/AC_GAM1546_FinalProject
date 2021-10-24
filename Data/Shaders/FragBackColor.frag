uniform vec4 u_ObjectBackColor;

void main()
{
    gl_FragColor = u_ObjectBackColor;//Draw the color of the uniform being set in C++ code
}
