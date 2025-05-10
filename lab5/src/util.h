
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#include "btdata.h"
#include "bencode.h"

#ifndef UTIL_H
#define UTIL_H

#define MAXLINE 4096

int is_bigendian();


int recvline(int fd, char **line);
int recvlinef(int fd, char *format, ...);


int connect_to_host(char* ip, int port);


int make_listen_port(int port);


int file_len(FILE* fname);

torrentmetadata_t* parsetorrentfile(char* filename);


tracker_response* preprocess_tracker_response(int sockfd);


tracker_data* get_tracker_data(char* data, int len);
void get_peers(tracker_data* td, be_node* peer_list); 
void get_peer_data(peerdata* peer, be_node* ben_res); 


char* make_tracker_request(int event, int* mlen);


int reverse_byte_orderi(int i);
int make_big_endian(int i);
int make_host_orderi(int i);


void client_shutdown(int sig);


announce_url_t* parse_announce_url(char* announce);

#endif
