#include "handshake.h"

bool handshake(void * who, bool what, netData net, Worm& w1,Worm& w2)
{
	package_data data;
	data.clean();
	string packet;
	if (what)// server is true
	{
		server * sv = (server *)who;
		sv->start_to_listen();
		data.header = I_AM_READY;
		data.x_coord = w1.getX();
		packet = compose_pkt(data);
		sv->sendMessage((packet.c_str()), packet.length());
		packet.clear();
		packet = sv->receiveMessage();
		decompose_data(packet, data);
		if (data.header == I_AM_READY)
		{
			w2.setX(data.x_coord);
			data.clean();
			data.header = ACKS;
			packet.clear();
			packet = compose_pkt(data);
			sv->sendMessage(packet.c_str(), packet.length());
			return true;
		}
		else return false;
	}
	else
	{
		client * cl = (client*)who;
		cl->startConnection((net.getOwnIP()).c_str());
		cl->receiveMessage();
		decompose_data(packet, data);
		if (data.header == I_AM_READY)
		{
			w1.setX(data.x_coord);
			data.clean();
			packet.clear();
			data.header = I_AM_READY;
			packet = compose_pkt(data);
			cl->send_message(packet.c_str(), packet.length());
			packet.clear();
			packet = cl->receiveMessage();
			decompose_data(packet, data);
			if (data.header == ACKS) { return true; }
			else return false;
		}
		else return false;
	}
}
