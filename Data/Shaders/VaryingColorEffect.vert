uniform vec2 u_ObjectPosition;
uniform vec2 u_ObjectScale;
uniform float u_ObjectRotation;
uniform vec2 u_CameraPosition;//It is the inverse of the camera position, so we only have to add it.
uniform vec2 u_ProjectionScale;

uniform vec2 u_UVOffset;
uniform vec2 u_UVScale;

attribute vec2 a_Position;
attribute vec2 a_UVCoord;
attribute vec4  a_ObjectColor;

uniform float u_TotalAnimationTime;
uniform float u_AnimationTimer;

varying vec4 v_Color;

void main()
{
	vec2 position=a_Position;
	
	//Send varyings
	float theta=u_AnimationTimer*1.1;//Multiply by 1.1 so that it almost complete a full spin
	a_ObjectColor.x+=sin(-theta);//Change colors
	a_ObjectColor.y+=cos(-theta);
	v_Color=a_ObjectColor;

	//Scale object
	position*=u_ObjectScale;//Scale the object bigger than normal

	//Rotate the object (2D rotation)
	vec2 tempPosition=position;
	position.x=tempPosition.x*cos(u_ObjectRotation)-tempPosition.y*sin(u_ObjectRotation);
	position.y=tempPosition.x*sin(u_ObjectRotation)+tempPosition.y*cos(u_ObjectRotation);

	//Move in a circle
	position.x+=cos(theta)-sin(theta);
	position.y+=sin(theta)+cos(theta);

	//Move object to World Coordinates
	position+=u_ObjectPosition;
	
	//Hard coded value so it doesn't interfere with numbers

	//Move objects according to camera  to get the camera view
	position+=u_CameraPosition;//Add the inverse of the camera position

	//Transform the camera view to clip space
	position/=u_ProjectionScale;



    gl_Position = vec4( position, 0,1 );
}
