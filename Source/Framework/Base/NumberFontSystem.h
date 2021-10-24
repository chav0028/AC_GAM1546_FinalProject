#ifndef __NUMBERFONTSYSTEM__H__
#define __NUMBERFONTSYSTEM__H__

const unsigned int NUMBER_FONT_SYSTEM_MAX_NUMBER = 999999;//The max number that can be displayed
const unsigned int NUMBER_FONT_SYSTEM_MAX_DIGITS = 6;
const unsigned int NUMBERS_DISPLAYED_IN_TEXTURE_STRIP = 10;

//Constants used for checking numbers, made into constants to avoid possible mispelling
const unsigned int HUNDRED_THOUSAND = 100000;
const unsigned int TEN_THOUSAND = 10000;
const unsigned int THOUSAND = 1000;
const unsigned int HUNDRED = 100;
const unsigned int TEN = 10;

class RectangleObject;

/*Display the number being passed, using 10 digit boxes.*/
class NumberFontSystem :
    public GameObject
{
public:
    NumberFontSystem(unsigned int number);
    ~NumberFontSystem();

    void setNumber(unsigned int number);
    unsigned int getNumber(){ return m_Number; }
    void loadContent();
    virtual void draw(Vector2 cameraPosition, Vector2 projectionScale);

    //Setters overwritten so that the value of all the boxes are modified in a single call, getters will return the position of the system, which should
    //match the one of all the boxes.
    virtual void setSystemAndDigitsEnabled(bool enabledStatus);
    virtual void setSystemAndDigitsPosition(Vector2 position);    //ANCHOR POINT is in the middle left

    virtual void setSystemAndDigitsScale(Vector2 scale);
    virtual void setSystemAndDigitsAngle(float angle);
    virtual void setSystemAndDigitsColor(Vector4Int color);
    virtual void setSystemAndDigitsBackColor(Vector4Int color);
    virtual void setSystemAndDigitsIndexShaderProgramToUse(ShaderProgramIndex aIndex);

private:
    unsigned int m_Number;
    unsigned int m_NumberOfDigits;
    
    void changeNumberDisplay(unsigned int aNumber,RectangleObject* digitBox);


    std::vector<RectangleObject*> m_DigitBoxes;




};

#endif