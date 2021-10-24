uniform vec4 u_ObjectColor;
uniform vec4 u_ObjectBackColor;
uniform vec2 u_UVOffset;
uniform sampler2D u_Texture;

varying vec2 v_ModelSpacePosition;
varying vec4 v_Color;
varying vec2 v_UVCoord;


uniform float u_TotalAnimationTime;
uniform float u_AnimationTimer;
uniform vec2 u_ModelSize;

void main()
{
	//Not ideal to do so many ifs in fragment shader. But polish demands me to do somethign special, though it will probably look horrible.
	vec4 color=u_ObjectColor;

	if(u_TotalAnimationTime>=u_AnimationTimer)
	{
		color+=u_AnimationTimer;
	}
	else if(u_TotalAnimationTime/3>u_AnimationTimer)
	{
		color+=sin(u_AnimationTimer);
	}	
	else if(u_TotalAnimationTime/3>u_AnimationTimer)
	{
		color.x+=u_AnimationTimer;
	}	
	else if(u_TotalAnimationTime/4>=u_AnimationTimer)
	{
		color.x+=sin(u_AnimationTimer);
	}

	vec2 UVcoord=v_UVCoord;//Offset
	color=texture2D(u_Texture,v_UVCoord)*color;//Tint the texture according to the object color

	gl_FragColor=color;
}
