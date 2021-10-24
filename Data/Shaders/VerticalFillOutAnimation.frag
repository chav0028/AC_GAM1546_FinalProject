uniform vec4 u_ObjectColor;
uniform vec4 u_ObjectBackColor;
uniform sampler2D u_Texture;
uniform vec2 u_UVOffset;
uniform float u_AnimationTimer;

varying vec2 v_UVCoord;
varying vec2 v_ModelSpacePosition;
varying vec4 v_Color;

void main()
{
        if(v_ModelSpacePosition.y>u_AnimationTimer)//Check time to start fade out
		{
            gl_FragColor = u_ObjectBackColor;//The color being filled in to simulate a fade out           
		}
		else//Display the complete image
		{
            gl_FragColor = u_ObjectColor;//The orignal color that will appear (complete shape)           
		}
}
