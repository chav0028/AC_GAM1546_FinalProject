#ifndef __CommonHeader_H__
#define __CommonHeader_H__

#include <windows.h>
#include <stdio.h>
#include <map>
#include <string.h>
#define assert myassert

#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL/GLExtensions.h"

#include "Utility/Helpers.h"

#include "Math/Utility.h"
#include "Math/Vector.h"
#include "Math/MyMatrix.h"

#include "lodepng/lodepng.h"
#include "Utility/ShaderProgram.h"

#include "Framework/Services/GameFramework.h"
#include "Framework/Services/InputManager.h"
#include "Framework/Services/ResourcesManager.h"
#include "Framework/Services/SceneManager.h"
#include "Framework/Services/Shapes.h"
#include "Framework/Services/Structs.h"
#include "Framework/Services/Pool.h"

#include "Framework/Base/Camera.h"
#include "Framework/Base/GameObject.h"
#include "Framework/Base/RectangleObject.h"
#include "Framework/Base/Mesh.h"
#include "Framework/Base/Scene.h"
#include "Framework/Base/NumberFontSystem.h"

#include "Framework/Base/Particles/Particle.h"
#include "Framework/Base/Particles/ParticleEmitter.h"
#include "Framework/Base/Particles/ParticleRenderer.h"
#include "Framework/Base/Particles/ParticleSystem.h"

#include "Game.h"
#include "LivingObject.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "Projectile.h"

#endif //__CommonHeader_H__
							  