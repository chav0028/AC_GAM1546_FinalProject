uniform vec4 u_ObjectColor;
uniform vec4 u_ObjectBackColor;
uniform sampler2D u_Texture;
uniform vec2 u_UVOffset;
uniform float u_AnimationTimer;

varying vec2 v_ModelSpacePosition;

void main()
{
        if(u_AnimationTimer>v_ModelSpacePosition.y)//Check time to start fill out
		{
            gl_FragColor = u_ObjectBackColor;//The color being filled in to simulate a ffill out 		          
		}
		else//Display the complete image
		{
            gl_FragColor =u_ObjectColor ;//The orignal color that will appear (complete shape)           
		}
}
