uniform sampler2D u_Texture;

varying vec2 v_UVCoord;


void main()
{
	

	//Color according to texture	
	vec4 color=texture2D(u_Texture,v_UVCoord);

	gl_FragColor = color;
}
