#include "stdafx.h"
#include "Context.h"

void Context::turnOn()
{
	current->turnOn(this);
}

void Context::turnedOn()
{
	current->turnedOn(this);
}

void Context::turnOff()
{
	current->turnOff(this);
}

void Context::turnedOff()
{
	current->turnedOff(this);
}

void Context::alarm()
{
	current->alarm(this);
}

void Context::error()
{
	current->error(this);
}
void Context::idle()
{
	current->idle(this);
}