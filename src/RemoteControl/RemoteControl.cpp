/*
 * RemoteControl.cpp
 *
 *  Created on: 11 févr. 2016
 *      Author: TinyMan
 */

#include "RemoteControl.h"
#include <cstring>
#include <vector>

RemoteControl::RemoteControl(MyRioCar& c, Radar& r) :
		car(c), radar(r) {
	// TODO Auto-generated constructor stub

}

void RemoteControl::serverThread() {
	cout << "Starting server thread" << endl;

	try {
		/* first identify the remote end
		 * we wait until data is comming on the socket
		 * then data is only accepted from the client that sent the first data
		 */
		size_t slen = sizeof(remote);

		std::vector<char> buff(4096);

		message_t message;
		int n = 0;
		do {
			cout << "Waiting for message" << endl;
			n = recvfrom(_sock, buff.data(), buff.size(), 0,
					(struct sockaddr*) &remote, &slen);
			if (n > 0) {
				message.header =
						*(reinterpret_cast<remote_message_header*>(buff.data()));
				cout << "Message comming : " << message.header.type << endl;
			}
		} while (false && message.header.type != MESSAGE_HELLO && n > 0); // First we wait until a client say HELLO and we store his address in this->remote

		if (n > 0) {
			cout << "Hello message arrived" << endl;
			connected = true;

			state_thread = new thread(&RemoteControl::stateThread, this);
		}

		// then we start looping forever until we got a msg of the server stops
		while ((n = recvfrom(_sock, buff.data(), buff.size(), 0,
		NULL,
		NULL)) > 0) {
			// first receive the header with the type and length of the message
			message.header =
					*(reinterpret_cast<remote_message_header*>(buff.data()));

			/*cout << " Message coming:" << message.header.type << endl;
			 cout << "size: " << message.header.length << endl;
			 cout << "message: " << n << endl;*/
			message.message = buff.data() + sizeof(remote_message_header);
			dispatchMessage(message);

		}
		if (n == -1)
			throw "Unexpected end";
	} catch (const char* e) {
		cout << e << endl;
	}
	connected = false;
}

RemoteControl::~RemoteControl() {
	stop();
	if (server_thread)
		server_thread->join();
	if (state_thread)
		state_thread->join();
	close(_sock);
	delete server_thread;
	delete state_thread;
}

void RemoteControl::startServer(uint16_t port) {
	_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_sock == -1)
		throw "socket()";

	memset((char *) &me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_port = htons(port);
	me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(_sock, (const struct sockaddr*) &me, sizeof(me)) == -1)
		throw "bind()";

	server_thread = new thread(&RemoteControl::serverThread, this);
}

void RemoteControl::send(const void* message, size_t len) {
	//cout << "Sending: " << message<< endl;
	if (connected) {
		if (sendto(_sock, message, len, 0, (const sockaddr*) &remote,
				sizeof(remote)) == -1)
			throw "Error sendto()";
	}
}

void RemoteControl::dispatchMessage(message_t message) {
	cout << "Dispatching message ";
	switch (message.header.type) { // reinterpret depending on the type of the message
	case MESSAGE_CMD: {
		cout << "(type: message_cmd)" << endl;
		remote_command* cmd = reinterpret_cast<remote_command*>(message.message);
		//cout << "CMD Message: speed: " << cmd->speed << ", angle: " << cmd->angle << endl;
		// set the speed and angle of the car
		car.Control.Speed.setSpeed(cmd->speed, cmd->forward);
		car.Control.Direction.setAngle(cmd->angle);
		break;
	}
	default:
		cout << "(type: " << message.header.type << ")" << endl;
		break;
	}
}

void RemoteControl::stateThread() {
	while ((connected) && !_quit) {

		cout << "Remote control state thread" << endl;
		if (sendEachPoint) {
			auto tab = radar.getTab();
			for (auto it : tab) {
				sendUSDPoint((us_point ) { it.first, it.second });
			}
		}

	}
	usleep(usleep_time);

}

void RemoteControl::sendUSDPoint(const us_point& point) {
	vector<char> buff;
	remote_message_header header;
	header.type = MESSAGE_SATE;
	header.length = sizeof(point) + sizeof(remote_state);

	us_state uss;
	uss.npoints = 1;

	remote_state msg;
	msg.us_detection = uss;

	buff.reserve(sizeof(header) + sizeof(msg) + sizeof(point));

	buff.insert(buff.begin(), (const char*) &header,
			(const char*) &header + sizeof(header));
	buff.insert(buff.begin() + sizeof(header), (const char*) &msg,
			(const char*) &msg + sizeof(msg));
	buff.insert(buff.begin() + sizeof(header) + sizeof(msg),
			(const char*) &point, (const char*) &point + sizeof(point));
	/*
	 for (auto it = buff.begin(); it != buff.end(); ++it) {
	 printf("%x ", *it);
	 }*/
	send(buff.data(), sizeof(header) + sizeof(msg) + sizeof(point));
}

void RemoteControl::stop() {
	_quit = true;
	shutdown(_sock, SHUT_RDWR); // the server thread will end this way (recvfrom will be unblocked and return 0)
}
