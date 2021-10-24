/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : set and get key presses

November 22 :
--Made the g_keystates a member variable of the input manager.
*/

#include "CommonHeader.h"


InputManager::InputManager()
{
//Set all the key states initial status as false
for (int i = 0; i < 256; i++)
{
m_KeyStates[i] = false;
}
}

InputManager::~InputManager()
{
}

void InputManager::setKeyState(WPARAM aWParam, bool aStatus)
{
m_KeyStates[aWParam] = aStatus;
}

bool InputManager::getKeyState(WPARAM aWParam)
{
return m_KeyStates[aWParam];
}
