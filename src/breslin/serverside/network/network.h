#ifndef NETWORK_H
#define NETWORK_H

#include <string.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stddef.h>

// Define SOCKET data type for UNIX (defined in WinSock for Win32)
// And socklen_t for Win32
typedef int SOCKET;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// Connection protocols
#define DREAMSOCK_TCP					0
#define DREAMSOCK_UDP					1

	#define DREAMSOCK_INVALID_SOCKET	-1

class DreamLinuxSock;

class Client;

class Network 
{
public:
Network(Client* client,const char netInterface[32], int port);
Network(const char netInterface[32], int port);
~Network();

DreamLinuxSock* mDreamLinuxSock;

// Function prototypes
void dreamSock_Shutdown(void);
SOCKET dreamSock_Socket(int protocol);
int dreamSock_SetNonBlocking(SOCKET sock, u_long setMode);
int dreamSock_SetBroadcasting(SOCKET sock, int mode);
int dreamSock_StringToSockaddr(const char *addressString, struct sockaddr *sadr);
SOCKET dreamSock_OpenUDPSocket(const char netInterface[32], int port);
void dreamSock_CloseSocket(SOCKET sock);

int dreamSock_GetPacket(SOCKET sock, char *data, struct sockaddr *from);
void dreamSock_SendPacket(SOCKET sock, int length, char *data, struct sockaddr addr);
void dreamSock_Broadcast(SOCKET sock, int length, char *data, int port);

int dreamSock_Linux_GetCurrentSystemTime(void);

int dreamSock_GetCurrentSystemTime(void);

SOCKET mSocket;

Client* mClient;
};
#endif
