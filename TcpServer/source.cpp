#include <winsock2.h>
#include <stdio.h>
#pragma comment (lib,"ws2_32")


int main(int argc, char *argv[])
{

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);//初始化

	SOCKET  s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sockaddr.sin_port = htons(9876);

	bind(s, (const struct sockaddr *)&sockaddr, sizeof(sockaddr));
	listen(s, 1);//开始监听

				 //wait for connection
	SOCKET  client;
	int nsize = sizeof(SOCKADDR);
	SOCKADDR    clientAddr;
	printf("wait for connection...\n");
	client = accept(s, &clientAddr, &nsize);//等待客户端连接
											//start send message
//	FILE* fp = fopen("D:/test/1028.h264","wb+");



	unsigned char buff[4096] = {};
	int res = 0;
	while (1)
	{
		if ((res = recv(client, (char*)buff, 4096, NULL)) > 0)
		{
			for (size_t i = 0; i < res; i++)
			{
				printf("%02x ", buff[i] & 0xFF);
			}
			printf("\r\n");

		//	printf("receive data size:%d,data:%s\r\n", res, buff);
		//	fwrite(buff, res,1, fp);
		}
			
	}

	printf("start to send msg...\n");
	send(client, "hello", 5, NULL);
	closesocket(client);
	closesocket(s);

	WSACleanup();
	return 0;
}
