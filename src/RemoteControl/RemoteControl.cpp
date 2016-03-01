/*
 * RemoteControl.cpp
 *
 *  Created on: 11 févr. 2016
 *      Author: TinyMan
 */

#include "RemoteControl.h"
#include <cstring>
#include <vector>

RemoteControl::RemoteControl(MyRioCar& c) : car(c){
	// TODO Auto-generated constructor stub

}

void RemoteControl::serverThread() {
	/* first identify the remote end
	 * we wait until data is comming on the socket
	 * then data is only accepted from the client that sent the first data
	 */
	size_t slen = sizeof(remote);

	std::vector<char> headerBuff(sizeof(remote_message_header));
	std::vector<char> buff(0);

	message_t message;
	int n = 0;
	do {
		n = recvfrom(_sock, headerBuff.data(), headerBuff.size(), 0,
				(struct sockaddr*) &remote, &slen);

		message.header =
				*(reinterpret_cast<remote_message_header*>(headerBuff.data()));
	} while (message.header.type != MESSAGE_HELLO && n > 0); // First we wait until a client say HELLO and we store his address in this->remote

	// then we start looping forever until we got a msg of the server stops

	while ((n = recvfrom(_sock, headerBuff.data(), headerBuff.size(), 0, NULL,
			NULL)) > 0) {
		// first receive the header with the type and length of the message
		message.header =
				*(reinterpret_cast<remote_message_header*>(headerBuff.data()));

		buff.reserve(message.header.length);
		if (recvfrom(_sock, buff.data(), message.header.length, 0, NULL, NULL)
				> 0) {
			message.message = buff.data();
			dispatchMessage(message);

		} else {
			throw "Protocol error";
		}
	}
	if (n == -1)
		throw "Unexpected end";
}

RemoteControl::~RemoteControl() {
	stop();
	server_thread->join();
	close(_sock);
	delete server_thread;
}

void RemoteControl::startServer(uint16_t port) {
	_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_sock == -1)
		throw "socket()";

	memset((char *) &me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_port = htons(port);
	me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (::bind(_sock, (const struct sockaddr*) &me, sizeof(me)) == -1)
		throw "bind()";

	server_thread = new thread(&RemoteControl::serverThread, this);
}

void RemoteControl::send(const string& message) {
	if(sendto(_sock, message.c_str(), message.length(), 0, (const sockaddr*)&remote, sizeof(remote)) == -1) throw "Error sendto()";
}

void RemoteControl::dispatchMessage(message_t message) {
	switch (message.header.type) { // reinterpret depending on the type of the message
	case MESSAGE_CMD:{
		remote_command* cmd = reinterpret_cast<remote_command*>(message.message);
		// set the speed and angle of the car
		car.Control.Speed.setSpeed(cmd->speed, cmd->forward);
		car.Control.Direction.setAngle(cmd->angle);
		break;
	}
	default:
		break;
	}
}

void RemoteControl::stop() {
	shutdown(_sock, SHUT_RDWR); // the server thread will end this way (recvfrom will be unblocked and return 0)
}
