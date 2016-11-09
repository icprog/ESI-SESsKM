#include "stdafx.h"
#include "TCPState.h"

void TCPState::ChangeState(TCPConnection* t, TCPState* s) {
	t->ChangeState(s);
}
