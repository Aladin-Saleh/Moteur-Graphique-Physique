#ifndef __CAPS_INTERFACE_INPUT_MANAGER__
#define __CAPS_INTERFACE_INPUT_MANAGER__

class I_InputManager
{
public:
	virtual bool GetKey(int key) = 0;
	virtual bool GetKeyUp(int key) = 0;
	virtual bool GetKeyDown(int key) = 0;
	virtual bool GetMouse(int key) = 0;
	virtual double AxisMouseX() = 0;
	virtual double AxisMouseY() = 0;
	virtual double GetMousePosX() = 0;
	virtual double GetMousePosY() = 0;
	virtual const char * GetGamepadName(int jid) = 0;
	virtual bool GetGamepadState(int jid, int key) = 0;
	virtual float GetGamepadAxis(int jid, int indice) = 0;
};


#endif // !__CAPS_INTERFACE_INPUT_MANAGER__