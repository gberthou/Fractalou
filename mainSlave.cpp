#include <iostream>
#include "SlaveSocket.h"

int main(void)
{
	SlaveSocket ss("localhost", 54000);
	ss.Run();
}
