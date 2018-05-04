#pragma once
#include "client.h"
#include "server.h"
#include "paquete.h"
#include "Worm.h"
#include "netData.h"
//Who? Client or server pointer , What? defines client or server
bool handshake(void * who, mode what, string ip, Worm& w1, Worm& w2);
