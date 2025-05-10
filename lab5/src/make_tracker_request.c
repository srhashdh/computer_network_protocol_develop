#include "util.h"
#include "btdata.h"

char* make_tracker_request(int event, int* mlen)
{ 
  
  char *MESG;
  char* cur;
  int i;

  MESG = (char*)malloc(4096*sizeof(char));
  cur = MESG;
  strcpy(cur,"GET /announce?");
  cur += strlen("GET /announce?");
  
  
  char hexdigs[16] = {'0', '1', '2', '3', '4', '5', '6', '7', 
                      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  strcpy(cur,"info_hash=");
  cur += strlen("info_hash=");
  for(i=0; i<5; i++)
  {
    int j;
    int part = reverse_byte_orderi(g_infohash[i]);
    unsigned char* p = (unsigned char*)&part;
    for(j=0; j<4; j++)
    {
      if((p[j] > 0x2F && p[j] < 0x3A) || (p[j] > 0x41 && p[j] < 0x5B) || 
         (p[j] > 0x60 && p[j] < 0x7B))
      {
        *cur++ = p[j];
      }
      else
      {
        *cur++ = '%';
        cur += sprintf(cur,"%02X",p[j]);
      }
    }
  }

  // Peer id
  int num;
  strcpy(cur,"&peer_id=");
  cur += strlen("&peer_id=");
  for(i=0; i<20; i++)
  {
    *cur++ = '%';
    cur += sprintf(cur,"%02X",(unsigned char)g_my_id[i]);
  }

  // port
  strcpy(cur,"&port=");
  cur += strlen("&port=");
  cur += sprintf(cur,"%d",g_peerport);
  
  // ip
  strcpy(cur,"&ip=");
  cur += strlen("&ip=");
  strcpy(cur,g_my_ip);
  cur += strlen(g_my_ip);

  // uploaded
  strcpy(cur,"&uploaded=");
  cur += strlen("&uploaded=");
  cur += sprintf(cur,"%d",g_uploaded);
  
  // downloaded
  strcpy(cur,"&downloaded=");
  cur += strlen("&downloaded=");
  cur += sprintf(cur,"%d",g_downloaded);
  
  // left
  strcpy(cur,"&left=");
  cur += strlen("&left=");
  cur += sprintf(cur,"%d",g_left);

  switch(event) {
  case BT_STARTED:
    strcpy(cur,"&event=");
    cur += strlen("&event=");
    strcpy(cur,"started");
    cur += strlen("started");
    break;
  case BT_STOPPED:
    strcpy(cur,"&event=");
    cur += strlen("&event=");
    strcpy(cur,"stopped");
    cur += strlen("stopped");
    break;
  case BT_COMPLETED:
    strcpy(cur,"&event=");
    cur += strlen("&event=");
    strcpy(cur,"completed");
    cur += strlen("completed");
    break;
  
  
  }
  
  strcpy(cur," HTTP/1.0\r\n");
  cur += strlen(" HTTP/1.0\r\n");
  strcpy(cur, "User-Agent: NjuCS-BitTorent-Client/1.0\r\n");
  cur += strlen("User-Agent: NjuCS-BitTorent-Client/1.0\r\n");

  strcpy(cur, "\r\n");
  cur += strlen("\r\n");
  
  *cur = '\0';

  *mlen = cur - MESG;
    
  return MESG;
}
