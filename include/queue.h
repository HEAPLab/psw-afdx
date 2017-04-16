#ifndef QUEUE_H_
#define QUEUE_H_

#include <netinet/in.h>
#include <semaphore.h>
#include <unistd.h>

#include "network_protocol.h"

#ifndef SIZE_QUEUE
#define SIZE_QUEUE 100
#endif

typedef struct nqnode_s nqnode;
struct nqnode_s
{
    struct sockaddr_in source;
    afdx_packet_t packet;
    time_t last_update;
};

/* Semaphores related to queue. To be initialized on an init function */
extern sem_t *sync_elab_net_mutex; // 0
extern sem_t *queue_mutex; // 1
extern sem_t *nr_nodes_queue; // 0

/* Returns the next node available for input in the queue or NULL
 * if queue is full */
nqnode *next_nqnode_in();

/* Returns the next node available in the queue for output or blocks if empty.
 * Pointers are not updated so that the node is not overwritten by an incoming
 * packet. */
nqnode *next_nqnode_out();

/* Updates the pointers in the queue to free last output node */
void dispose_last_nqnode();

#endif /* QUEUE_H_ */
