#ifndef __RECTANGLEOBJECT__H__
#define __RECTANGLEOBJECT__H__

/* Basic class to make a rectangle, useful for making sprites, backgrounds, etc.*/
class RectangleObject: public GameObject
{

public:
    RectangleObject(ShaderProgramIndex indexShaderProgram, Vector2 scale, unsigned int textureIndex);
    ~RectangleObject();

    virtual void loadContent();

};

#endif //__RectangeObject_H__