#ifndef __INPUTMANAGER_H
#define __INPUTMANAGER_H

/*The class to substitute a global, basically it just has the state of  the keys, whether they are pressed or not.*/
class InputManager
{
public:
    InputManager();
    ~InputManager();
    void setKeyState(WPARAM wParam, bool status);
    bool getKeyState(WPARAM wParam);

private:
    bool m_KeyStates[256];


};

#endif