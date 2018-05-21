#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

class InputHandler
{
public:
	virtual ~InputHandler() {};
	virtual int Initialize() = 0;
	virtual int ReadKey() = 0;
	virtual char KeyToVisualChar(int) = 0;
};

#endif