#include <cstdio>

#include "LocalListener.h"
int main()
{
	LocalListener listener;
	listener.startAcceptingWS();
	listener.StartAccept();

	return 0;
}