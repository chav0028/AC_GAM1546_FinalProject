# AC_GAM1546_FinalProject
Final project for GAM1546: Game and Graphics Computations II. Starting with a basic C++/OpenGL framework, we had to create a 2D game. I decided to create a top down space shooter game. In it you control a space ship, you can move around,activate a shield, and shoot down enemy ships.

Some of the features in the game were:
- 2D rendering using OpenGL fragment and vertex shaders. This included transforming the meshes from local space to world space to camera space, and finally to "clip" space. This besides filling the vertex buffer object, index buffer object and passing the corresponding vertex attributes, uniforms, and varyings to the shaders, using OpenGL.
- Particle emitters, seen as trailing behind the player or in explosions. This was made using an object pool to manage active and inactive particles.
- Player mechanics for moving, shooting (using object pooled projectiles), and health.
- Enemy behavior to patrol or attack the player.
- Basic circle to circle collision for player, enemies, and projectiles.
- Explosion effect when enemy is killed, made with particles and a vertex shader effect.
- Invincibility effects when picking the shield, including changing the color of the player and the UI using fragment shaders.
- Custom meshes created in code, with attributes for color, UVs, and positions. This as an optimization instead of having basic transparent sprites (rectangles with a texture). These meshes made use of OpenGL vertex buffer object and index buffer object.
- Numbers font system. Using a texture, the system calculated the UV coordinates of the digits to display for a number specified. This allowed to display on realtime the number of enemies left in the game, changing the number shown through the game logic.
