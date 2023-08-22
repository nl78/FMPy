#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#ifdef WIN32
#	include <windows.h>
#else
#	include <semaphore.h>
#	include <fcntl.h>
#	include <sys/mman.h>
#endif

/*-----------------------------------------------------------------------------
             C O M M U N I C A T I O N _ E N D P O I N T _ T
-----------------------------------------------------------------------------*/

typedef enum {
	COMMUNICATION_CLIENT,
	COMMUNICATION_SERVER
} communication_endpoint_t;


/*-----------------------------------------------------------------------------
                             S H M _ H A N D L E _ T
-----------------------------------------------------------------------------*/
#ifdef WIN32
typedef HANDLE shm_handle_t;
#	define SHM_INVALID	NULL
#else
typedef int shm_handle_t;
#	define SHM_INVALID	-1
#endif


/*-----------------------------------------------------------------------------
                             S E M _ H A N D L E _ T
-----------------------------------------------------------------------------*/
#ifdef WIN32
typedef HANDLE sem_handle_t;
#else
typedef sem_t * sem_handle_t;
#endif


/*-----------------------------------------------------------------------------
                         C O M M U N I C A T I O N _ T
-----------------------------------------------------------------------------*/
#define COMMUNICATION_KEY_LEN         16
#define COMMUNICATION_TIMEOUT_DEFAULT 3000
typedef struct {
	char				*event_client_name;
	char				*event_server_name;
	char				*memory_name;
	char				*sem_name;
	shm_handle_t		map_file;
	sem_handle_t		client_ready;
	sem_handle_t		server_ready;
	size_t				data_size;
	void				*data;
} communication_t;


/*-----------------------------------------------------------------------------
                               P R O T O T Y P E S
-----------------------------------------------------------------------------*/

extern void communication_free(communication_t* communication);
extern communication_t* communication_new(const char* prefix, int memory_size, communication_endpoint_t endpoint);
extern void communication_client_ready(const communication_t* communication);
extern void communication_waitfor_server(const communication_t* communication);
extern int communication_timedwaitfor_server(const communication_t* communication, int timeout);
extern void communication_waitfor_client(const communication_t* communication);
extern int communication_timedwaitfor_client(const communication_t* communication, int timeout);
extern void communication_server_ready(const communication_t* communication);

#endif
