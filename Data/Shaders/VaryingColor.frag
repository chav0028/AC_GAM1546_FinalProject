varying vec4 v_Color;

void main()
{
	gl_FragColor = v_Color;//Color according to varying, causing a gradient. Unless all vertices have the same color
}
