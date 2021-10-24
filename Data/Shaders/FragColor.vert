uniform vec2 u_ObjectPosition;
uniform vec2 u_ObjectScale;
uniform float u_ObjectRotation;
uniform vec2 u_CameraPosition;//It is the inverse of the camera position, so we only have to add it.
uniform vec2 u_ProjectionScale;

attribute vec2 a_Position;
attribute vec2 a_UVCoord;
attribute vec4 a_ObjectColor;

varying vec2 v_UVCoord;
varying vec2 v_ModelSpacePosition;
varying vec4 v_Color;

void main()
{
	vec2 position=a_Position;
	
	//Scale object
	position*=u_ObjectScale;//Scale the object according to its real size

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

    gl_Position = vec4( position, 0,1 );
}
