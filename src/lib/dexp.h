#ifndef ADEP_H
#define ADEP_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "peer.h"
#include "utils.h"
#include "config.h"
#include "common.h"
#include <stdint.h>
#include <sys/epoll.h>


//Queries
#define DEXP_GETDOCUMENT "GET_DOCUMENT"
#define DEXP_GETINFOS "GET_INFOS\r\n"
#define DEXP_GETCAPA "GET_CAPA\r\n"
#define DEXP_GETCATALOG "GET_CATALOG\r\n"
#define DEXP_ANNOUNCE "ANNOUNCE"
#define DEXP_STARTTLS "STARTTLS\r\n"
#define DEXP_NEGOTIATE "NEGOTIATE"


//notifications
#define DEXP_READY "READY\r\n"
#define DEXP_FIN "FIN\r\n"


//Announce modes
#define DEXP_AN_ADD 0x01
#define DEXP_AN_MOD 0x02
#define DEXP_AN_DEL 0x03

#define DEXP_AN_ADD_STR "ADD"
#define DEXP_AN_MOD_STR "MOD"
#define DEXP_AN_DEL_STR "MOD"


//Modes
#define DEXPMODE_IDLE 0x00
#define DEXPMODE_WAIT_CATALOG_HEADER 0x01
#define DEXPMODE_CATALOG_XFR 0x02
#define DEXPMODE_FILE_XFR 0x03
#define DEXPMODE_FETCHDOCS 0x04
#define DEXPMODE_BUSY 0x05

//Headers
#define DEXPHEAD_CATALOG  "CATALOG"


#define BEGIN_XFR "BEGIN_XFR"
#define END_XFR "END_XFR"
#define BEGIN_ANNOUNCE "BEGIN_ANNOUNCE"
#define END_ANNOUNCE "END_ANNOUNCE"

#define SOCK_IDLE 0x00
#define SOCK_ANNOUNCE_RECV_MODE 0x01
#define SOCK_XFR_RECV_MODE 0x02

#define SOCK_ANNOUNCE_SEND_MODE 0x03
#define SOCK_XFR_SEND_MODE 0x04


int has_document(char*,char**,int);
int parse_cmd(char*,char**,int) ;

void *dexp_cli_ioth(void *);
void *dexp_serv_ioth(void *);


void* keepalive_thread();

int announce(char*,int);
int process_announce(peer*,char*);
int fetch_doc(peer*,char*);
char* receive_catalog(peer*);
hash_queue* register_hashes(char *,hash_queue*,int*);
void fetch_docs(peer*,hash_queue*,int*);
int parse_capacity(peer*,char*);
int negotiate(peer*);
int receiveNego(peer*);
int createPeer(char*,int,uint8_t);
int dexp_input_handler(peer*);
dexp_queue* dexp_enqueue(dexp_queue*,dexp_queue,int);
int dexp_add_output(peer*,void*);
int dexp_take_action(int,peer*,void*);


#endif

