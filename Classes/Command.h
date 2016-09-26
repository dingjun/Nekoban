#ifndef __COMMAND_H__
#define __COMMAND_H__

/**
	Base class for various types of command
 */
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	virtual void undo() = 0;
};

#endif // __COMMAND_H__
