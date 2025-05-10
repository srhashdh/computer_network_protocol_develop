#include "btdata.h"

char g_my_ip[128] = {0};
int g_peerport = 0;
int g_infohash[5] = {0};
char g_my_id[20] = {0};

int g_done = 0;

torrentmetadata_t* g_torrentmeta = NULL;
char* g_filedata = NULL;
int g_filelen = 0;
int g_num_pieces = 0;
char* g_filename = NULL;

char g_tracker_ip[16] = {0};
int g_tracker_port = 0;
tracker_data *g_tracker_response = NULL;

int g_uploaded = 0;
int g_downloaded = 0;
int g_left = 0;
