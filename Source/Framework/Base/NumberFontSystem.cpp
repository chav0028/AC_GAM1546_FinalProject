/*
Student:    Alvaro Chavez Mixco
Date:       Monday, October 19 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Display in numbers the digits from 0 to 9.


December 1: =Adapted code from class to file
December 7:-Create number font system texture.
-Implemented logic to get single digits out from a unsigned int, so that they can
be displayed. (display code not yet implemented).
*/

#include "CommonHeader.h"

NumberFontSystem::NumberFontSystem(unsigned int aNumber) :GameObject(ShaderProgramIndex_Texture, "FontNumbers"),//Set basic shader by default
m_Number(aNumber)
{
}


NumberFontSystem::~NumberFontSystem()
{
    //Delete all objects
    while (m_DigitBoxes.empty() == false)
    {
        delete m_DigitBoxes.back();
        m_DigitBoxes.back() = nullptr;
    }

    m_DigitBoxes.clear();//Clear vector

}

void NumberFontSystem::loadContent()
{
    //Create all the digit boxes
    for (unsigned int i = 0; i < NUMBER_FONT_SYSTEM_MAX_DIGITS; i++)
    {
        RectangleObject* tempRectangle = new RectangleObject(m_IndexShaderProgramToUse, getScale(), m_IndexTextureToUse);//Create a rectangle for each digit
        tempRectangle->loadContent();//Load its mesh
        tempRectangle->setEnabled(true);//Disable them
        tempRectangle->setUVScale(Vector2(10, 1));//Set the scale of the to match the number of digits (from 0-9) in the number font sprite strip
        m_DigitBoxes.push_back(tempRectangle);//Add it to the list
    }
    setNumber(m_Number);//Set the number their will display
    setSystemAndDigitsPosition(m_Position);//Set their position   
}

void NumberFontSystem::draw(Vector2 aCameraPosition, Vector2 aProjectionScale)
{
    if (m_NumberOfDigits-1 < m_DigitBoxes.size())//Num digits -1 , because the number of digits index starts at 1 and not 0
    {
        //Draw the digits according to the ones that are in the number
		for (unsigned int i = 0; i < m_NumberOfDigits; i++) //Num digits +1 , because the number of digits index starts at 1 and not 0
		{
			if (m_DigitBoxes.at(i) != nullptr)
			{
				m_DigitBoxes.at(i)->draw(aCameraPosition, aProjectionScale);
			}
		}
    }
}

//Sets the number variable and calls the function to change the number displayed
void NumberFontSystem::setNumber(unsigned int aNumber)
{
    if (aNumber <= NUMBER_FONT_SYSTEM_MAX_NUMBER)
    {
        unsigned int singleDigit = 0;
        unsigned int numberDigits = 0;

        // Display digit in hundred thousand spot
        if (aNumber >= HUNDRED_THOUSAND)
        {
            singleDigit = aNumber / HUNDRED_THOUSAND % 10;//Get the value of the digit in the hundred thousan spot

            changeNumberDisplay(singleDigit, m_DigitBoxes.at(5));//Change the number that will be displayed
            numberDigits++;//Increase the digit count
        }

        // Display digit in ten thousand spot
        if (aNumber >= TEN_THOUSAND)
        {
            singleDigit = aNumber / TEN_THOUSAND % 10;//Get the value of the digit in the ten thousand spot

            changeNumberDisplay(singleDigit, m_DigitBoxes.at(4));//Change the number that will be displayed
            numberDigits++;//Increase the digit count
        }

        // Display digit in thousand spot
        if (aNumber >= THOUSAND)
        {
            singleDigit = aNumber / THOUSAND % 10;//Get the value of the digit in the thousand spot

            changeNumberDisplay(singleDigit, m_DigitBoxes.at(3));//Change the number that will be displayed
            numberDigits++;//Increase the digit count

        }

        // Display digit in hundred spot
        if (aNumber >= HUNDRED)
        {
            singleDigit = aNumber / HUNDRED % 10;//Get the value of the digit in the hundred spot

            changeNumberDisplay(singleDigit, m_DigitBoxes.at(2));//Change the number that will be displayed
            numberDigits++;//Increase the digit count
        }

        // Display digit in tens spot
        if (aNumber >= TEN)
        {
            singleDigit = aNumber / TEN % 10;//Get the value of the digit in the ten  spot

            changeNumberDisplay(singleDigit, m_DigitBoxes.at(1));//Change the number that will be displayed
            numberDigits++;//Increase the digit count
        }


        //Display digit in ones spot
        singleDigit = aNumber % 10;//Get the value of the digit in the ten thousand spot

        //Always display something in the ones spot, even 0.
        changeNumberDisplay(singleDigit, m_DigitBoxes.at(0));//Change the number that will be displayed
        numberDigits++;//Increase the digit count

        //Save the number of digits
        m_NumberOfDigits = numberDigits;
           
        //Save the current number
        m_Number = aNumber;

        //Reset numbers position
        setSystemAndDigitsPosition(m_Position);
    }
}

//Sets which number will be displayed
void NumberFontSystem::changeNumberDisplay(unsigned int aNumber, RectangleObject* aDigitBox)
{
    float offsetX = 0.0f;
    float offsetY = 0.0f;

    //Calculate the UV offset using math
    if (aNumber < NUMBERS_DISPLAYED_IN_TEXTURE_STRIP)
    {
        offsetX = (float)aNumber / (float)NUMBERS_DISPLAYED_IN_TEXTURE_STRIP;
        offsetY = 0.0f;
    }
    else
    {
        //Set the UV to display empty space
        offsetX = 0.0f;
        offsetY = 0.5f;
    }

    aDigitBox->setUVoffset(Vector2(offsetX, offsetY));//Set the offset

    //switch (aNumber)//Check which number to display
    //{
    //case 0://Display number 0
    //        offsetX = 0.0f;
    //        offsetY = 0.0f;
    //    break;
    //case 1://Display number 1
    //    offsetX = 0.1f;
    //    offsetY = 0.0f;
    //    break;
    //case 2://Display number 2
    //    offsetX = 0.2f;
    //    offsetY = 0.0f;
    //    break;
    //case 3://Display number 3
    //    offsetX = 0.3f;
    //    offsetY = 0.0f;
    //    break;
    //case 4://Display number 4
    //    offsetX = 0.4f;
    //    offsetY = 0.0f;
    //    break;
    //case 5://Display number 5
    //    offsetX = 0.5f;
    //    offsetY = 0.0f;
    //    break;
    //case 6://Display number 6
    //    offsetX = 0.6f;
    //    offsetY = 0.0f;
    //    break;
    //case 7://Display number 7
    //    offsetX = 0.7f;
    //    offsetY = 0.0f;
    //    break;
    //case 8://Display number 8
    //    offsetX = 0.8f;
    //    offsetY = 0.0f;
    //    break;
    //case 9://Display number 9
    //    offsetX = 0.9f;
    //    offsetY = 0.0f;
    //    break;
    //default://Set the UV to display empty space
    //    offsetX = 0.0f;
    //    offsetY = 0.5f;
    //    break;
    //}

}


//Setters, merely ensure that the properties is set in this system, AND in ALL the digit boxes this system has
void NumberFontSystem::setSystemAndDigitsEnabled(bool aEnabledStatus)
{
    m_Enabled = aEnabledStatus;//Set the status in this system

    //Go through all the digits
    for (unsigned int i = 0; i < m_DigitBoxes.size(); i++)
    {
        if (m_DigitBoxes.at(i) != nullptr)//If they are not null
        {
            m_DigitBoxes.at(i)->setEnabled(aEnabledStatus);//Set is status
        }
    }
}

void NumberFontSystem::setSystemAndDigitsPosition(Vector2 aPosition)
{
    m_Position = aPosition;//Set the status in this system

    //Calculate how wide a single digit box is
    float singleDigitWidth = 0;
    if (m_DigitBoxes.empty() == false)
    {
        if (m_DigitBoxes.at(0) != nullptr)//if we have digit boxes
        {
            singleDigitWidth = m_DigitBoxes.at(0)->getScale().x;
        }
    }

    //ANCHOR POINT is in the middle left

    //Go through all the digits, from left to right
    unsigned int digitModified = 0;//Get a variable so that we modify the values from right to left
    for (unsigned int i = m_NumberOfDigits-1; i < m_DigitBoxes.size(); i--)
    {
        if (m_DigitBoxes.at(digitModified) != nullptr)//If they are not null
        {
            float xValue = m_Position.x + (singleDigitWidth*i);
            m_DigitBoxes.at(digitModified)->setPosition(Vector2(xValue, m_Position.y));//Set the position, according to the number of digits
            //between the anchor point on the left and the current digit being modified
        }
        digitModified++;
    }
}

void NumberFontSystem::setSystemAndDigitsScale(Vector2 aScale)
{
    setScale(aScale);//Set the status in this system

    //Go through all the digits
    for (unsigned int i = 0; i < m_DigitBoxes.size(); i++)
    {
        if (m_DigitBoxes.at(i) != nullptr)//If they are not null
        {
            m_DigitBoxes.at(i)->setScale(aScale);
            setPosition(m_Position);//Place the number again, so that the distance between them is reset
        }
    }
}

void NumberFontSystem::setSystemAndDigitsAngle(float aAngle)
{
    setAngle(aAngle);//Set the status in this system

    //Go through all the digits
    for (unsigned int i = 0; i < m_DigitBoxes.size(); i++)
    {
        if (m_DigitBoxes.at(i) != nullptr)//If they are not null
        {
            m_DigitBoxes.at(i)->setAngle(aAngle);
        }
    }
}

void NumberFontSystem::setSystemAndDigitsColor(Vector4Int aColor)
{
    setColor(aColor);//Set system status

    //Go through all the digits
    for (unsigned int i = 0; i < m_DigitBoxes.size(); i++)
    {
        if (m_DigitBoxes.at(i) != nullptr)//If they are not null
        {
            m_DigitBoxes.at(i)->setColor(aColor);
        }
    }
}

void NumberFontSystem::setSystemAndDigitsBackColor(Vector4Int aColor)
{
    setBackColor(aColor);//Set status in system

    //Go through all the digits
    for (unsigned int i = 0; i < m_DigitBoxes.size(); i++)
    {
        if (m_DigitBoxes.at(i) != nullptr)//If they are not null
        {
            m_DigitBoxes.at(i)->setBackColor(aColor);
        }
    }
}

void NumberFontSystem::setSystemAndDigitsIndexShaderProgramToUse(ShaderProgramIndex aIndex)
{
    setIndexShaderProgramToUse(aIndex);//Set status in system

    //Go through all the digits
    for (unsigned int i = 0; i < m_DigitBoxes.size(); i++)
    {
        if (m_DigitBoxes.at(i) != nullptr)//If they are not null
        {
            m_DigitBoxes.at(i)->setIndexShaderProgramToUse(aIndex);
        }
    }


}