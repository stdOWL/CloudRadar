#pragma once
#include <iostream>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <netdb.h>

#define ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <functional>


#include "CBitReader.h"
uint64_t GetTickCountMs();

class LocalListener
{
public:
	LocalListener();
	~LocalListener();
	void StartAccept();
	void printTcpPacket(user_container *container, const char *data, int length);
	user_shared_container *getOrCreateSharedContainer(user_container *container,int userid);
	void printUdpPacket(user_container * container, const char *data, int length, bool bRecv);
	void startAcceptingWS();
	void onWSMessage(websocketpp::lib::weak_ptr<void> hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);
	void onWSClose(websocketpp::lib::weak_ptr<void> hdl);
	void onWSOpen(websocketpp::lib::weak_ptr<void> hdl);
	websocketpp::server<websocketpp::config::asio> *wsServer;
	std::vector< websocketpp::lib::weak_ptr<void> >	wsHandles;
private:

	int serverSock, clientSock;
	struct sockaddr_in serverAddr, clientAddr;
	
	std::map<int, std::string>	keys;
	std::map<int, user_shared_container*>	containers;
	pthread_mutex_t	containerslock;

	std::vector<user_container*>	maincontainers;
	pthread_mutex_t	maincontainerslock;
	void GarbageCollector();
	void ReceivedPacket_sub_218A5B8(user_container *container, CBitReader &Ar);
	int MainChannelManager(user_container *container, UINT32 nChannelIndex);
	void InsertActorToChannel(user_container *container, int nChannelNo);
	void Find_MapIndex(FInBunch & Bunch, user_container *container);
	bool ChangeMyActorPlace(user_container *container, float X0, float Y0, float Z0, float X1, float Y1, float Z1);
	void SendPacketFilter(user_container *container, LPBYTE pBuf, int nBufLen);
	int My_6633EncDecKeyMake_B3BD4(char* szEncDecKeyBuffer, char* szEncDecKeyMakeKey, int a3);
	int My_6633EncKeyMake_sub_B164C(char* a1, int a2, char* a3);
	int My_6633DecKeyMake_sub_B1954(char* a1, int a2, char* a3);
	int Mydecode6633Packet_sub_C1520(char* szEncDecKeyBuffer, char* szEncodedSrc, int nSrcLen, char *szDecodedDest);
	int MyDec_6633Packet_sub_B3B28(char* szEncodeSrc, int nSrcLen, char* szEncDecKeyBuffer, char* szDecodedDest);
	char* MyDec_6633Packet_sub_B3888(char* szEncodedSrc, char* szDecodedDest, int nSrcLen, char* szDecKeyBuffer, char* a5, int a6);
	char* MyDec_6633Packet_sub_B2984(char* a1, char* a2, char* a3);
	int decode_s64(int64_t *a1, char *a2, unsigned int a3);
	int decode_u64(uint64_t *a1, char *a2, unsigned int a3);
	void DecodeUDPPacketKeyMake_F12E3C(user_container *container);
	void printRawData(user_container * container, const char *data, int length, bool bRecv);
	int DecodeUDPPacket_sub_F12680(user_container * container, char* Src, char* Dest, signed int nLen);
	void RecvPacketFilter(user_container *container, LPBYTE pBuf, int nBuflen, int nArNum = 0, DWORD * BunchPackID = nullptr);
	void UChannel_ReceivedRawBunch(user_container *container, FInBunch & Bunch);
	bool RemoveChannel(user_container *container, UINT32 nChannelNo);
	void VehicleSeatOperation(user_container *container, int nChannelNo, UINT32 nAttachParent, UINT32 nSeatNo, BYTE byteActorType);
	void ShiftBuffer(user_container *container, BYTE * OutStr, BYTE * InStr, int nBuflen, int nShiftCnt);
	void ResetTeammateInfo(user_container *container);
	void ItemTypeRegist(user_container *container, OBJECT obj);
	bool ProcessBunch(FInBunch & Bunch, UINT32 *pPos, UINT32 * nPosCnt, user_container * container);
	bool ReceivedBunch(FInBunch & Bunch);
	int UActorChannel_ReadContentBlockPayload(FInBunch &Bunch, CBitReader& OutPayload, bool& bOutHasRepLayout, user_container * container);
};
extern LocalListener* gLListener;