uniform vec4 u_ObjectColor;
uniform sampler2D u_Texture;
uniform vec2 u_UVOffset;

varying vec2 v_UVCoord;

void main()
{
    //gl_FragColor = u_ObjectColor;//Draw the color of the uniform being set in C++ code

	//Color according to texture	
	vec2 UVcoord=v_UVCoord;//Offset
	vec4 color=texture2D(u_Texture,v_UVCoord)*u_ObjectColor;//Tint the texture according to the object color
	gl_FragColor = color;
}
