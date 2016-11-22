#include "stdafx.h"
#include "Repository.h"

void Repository::add(Structure s)
{
	m.lock();
	vec->push(s);
	m.unlock();
}

void Repository::remove(Structure s)
{
	m.lock();
	vec->pop();
	m.unlock();
}

void Repository::get(Structure * s)
{
	m.lock();
	*s = vec->top();
	m.unlock();
}
