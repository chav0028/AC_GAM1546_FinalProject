uniform vec2 u_ObjectPosition;
uniform vec2 u_ObjectScale;
uniform float u_ObjectRotation;
uniform float u_ObjecCRotation;
uniform vec2 u_CameraPosition;//It is the inverse of the camera position, so we only have to add it.
uniform vec2 u_ProjectionScale;
uniform vec4 u_ObjectColor;

uniform vec2 u_UVOffset;
uniform vec2 u_UVScale;

uniform float u_AnimationTimer;
uniform vec2 u_ModelSize;

attribute vec2 a_Position;
attribute vec2 a_UVCoord;
attribute vec4  a_ObjectColor;
varying vec2 v_ModelSpacePosition;

varying vec4 v_Color;

void main()
{
	vec2 position=a_Position;
	
	v_ModelSpacePosition=a_Position;


	//Send varyings
	v_Color=vec4(u_ObjectColor.x,u_ObjectColor.y,0.0,u_AnimationTimer);


		//Scale object
	position/=u_ObjectScale;//Scale the object according to its real size
		

	//Math to create "spike" like effects
	position.x=cos(position.x*u_ModelSize.x+u_AnimationTimer)*sin(position.y*u_ModelSize.y+u_AnimationTimer)*5;//5 and 3 are scale of "explosion"
	position.y=cos(position.x*u_ModelSize.x+u_AnimationTimer)*sin(position.y*u_ModelSize.y+u_AnimationTimer)*3;


	//Rotate the object (2D rotation)
	vec2 tempPosition=position;
	position.x=tempPosition.x*cos(u_ObjectRotation)-tempPosition.y*sin(u_ObjectRotation);
	position.y=tempPosition.x*sin(u_ObjectRotation)+tempPosition.y*cos(u_ObjectRotation);

	//Move object to World Coordinates
	position+=u_ObjectPosition;

	//Move objects according to camera  to get the camera view
	position+=u_CameraPosition;//Add the inverse of the camera position

	//Transform the camera view to clip space
	position/=u_ProjectionScale;

    gl_Position = vec4( position, 0.0,1.0 );
}
