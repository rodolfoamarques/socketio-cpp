
#include <iostream>

#include "SocketAPI/SocketModel.hpp"


int main ( int argc, char *argv[] )
{
	/* initiallize the socket connection */
	SocketModel::init( "http://127.0.0.1:3000", 1 );

	/* send a message to the socket */
	for( uint32_t i=0; i<10; i++ ) {

		SocketModel::sendMessage(
			"new message", "hello " + std::to_string(i) );
	}

	/* close socket connection */
	SocketModel::cleanUp();

	return 0;
}
