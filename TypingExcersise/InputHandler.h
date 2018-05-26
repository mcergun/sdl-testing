#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

enum ArrowKey
{
	ArrowUp,
	ArrowDown,
	ArrowRight,
	ArrowLeft,
};

typedef void(*EnterKeyEvent)();
typedef void(*BackspaceKeyEvent)();
typedef void(*VisualKeyEvent)(char);
typedef void(*ExitEvent)();
typedef void(*PauseEvent)();
typedef void(*ArrowKeyEvent)(ArrowKey);

class InputHandler
{
public:
	virtual ~InputHandler() {};
	virtual int Initialize() = 0;
	virtual int ReadKey() = 0;
	virtual char KeyToVisualChar(int) = 0;
	virtual void SetEnterKeyNotifier(EnterKeyEvent func)
	{
		enterPressed = func;
	}

	virtual void SetBackspaceKeyNotifier(BackspaceKeyEvent func)
	{
		backspacePressed = func;
	}

	virtual void SetArrowKeyNotifier(ArrowKeyEvent func)
	{
		arrowKeyPressed = func;
	}

	virtual void SetVisualKeyNotifier(VisualKeyEvent func)
	{
		visualPressed = func;
	}

	virtual void SetPauseEventNotifier(PauseEvent func)
	{
		pauseRequested = func;
	}

	virtual void SetExitEventNotifier(ExitEvent func)
	{
		exitRequested = func;
	}

	virtual void SetKeyArrowNotifier(ArrowKeyEvent func)
	{
		arrowKeyPressed = func;
	}

protected:
	EnterKeyEvent enterPressed = nullptr;
	BackspaceKeyEvent backspacePressed = nullptr;
	VisualKeyEvent visualPressed = nullptr;
	ArrowKeyEvent arrowKeyPressed = nullptr;
	PauseEvent pauseRequested = nullptr;
	ExitEvent exitRequested = nullptr;
};

#endif