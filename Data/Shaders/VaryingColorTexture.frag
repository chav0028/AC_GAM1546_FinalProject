uniform sampler2D u_Texture;

varying vec2 v_UVCoord;
varying vec4 v_Color;

void main()
{
	//Color according to texture	
	vec4 color=texture2D(u_Texture,v_UVCoord)*v_Color;//Tint texture according to varying

	gl_FragColor = color;
}
