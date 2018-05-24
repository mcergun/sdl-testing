#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

typedef void(*KeyEnterEvent)();
typedef void(*KeyBackspaceEvent)();
typedef void(*KeyVisualEvent)(char);
typedef void(*ExitEvent)();

class InputHandler
{
public:
	virtual ~InputHandler() {};
	virtual int Initialize() = 0;
	virtual int ReadKey() = 0;
	virtual char KeyToVisualChar(int) = 0;
	virtual void SetKeyEnterNotifier(KeyEnterEvent func)
	{
		enterPressed = func;
	}
	virtual void SetKeyBackspaceNotifier(KeyBackspaceEvent func)
	{
		backspacePressed = func;
	}
	virtual void SetKeyVisualNotifier(KeyVisualEvent func)
	{
		visualPressed = func;
	}
	virtual void SetExitEventNotifier(ExitEvent func)
	{
		exitRequested = func;
	}

protected:
	KeyEnterEvent enterPressed = nullptr;
	KeyBackspaceEvent backspacePressed = nullptr;
	KeyVisualEvent visualPressed = nullptr;
	ExitEvent exitRequested = nullptr;
};

#endif