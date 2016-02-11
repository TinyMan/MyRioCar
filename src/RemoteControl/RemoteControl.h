/*
 * RemoteControl.h
 *
 *  Created on: 11 févr. 2016
 *      Author: TinyMan
 */

#ifndef REMOTECONTROL_H_
#define REMOTECONTROL_H_
#include <iostream>
#include <memory>
#include <thread>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "protocol.h"
#include "../MyRioCar.h"

using namespace std;


/*
 * Represents the link between server and client
 * Remote server & client are using UDP socket
 */
class RemoteControl {
private:
	typedef struct{
		remote_message_header header;
		void* message;
	} message_t;

	void serverThread();
	void dispatchMessage(message_t message);
	thread* server_thread = nullptr;

	struct sockaddr_in me;
	struct sockaddr_in remote;
	int _sock=0;

	MyRioCar& car;
public:
	RemoteControl(MyRioCar& car);
	virtual ~RemoteControl();

	void startServer(uint16_t port = 1337);
	void send(const string& message);

	void stop();
};

#endif /* REMOTECONTROL_H_ */
