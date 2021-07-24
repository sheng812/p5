#include "helper.h"
#include "request.h"

// 
// server.c: A very, very simple web server
//
// To run:
//  server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

// CS537: Parse the new arguments too
void getargs(int *port, int *threads, int *buffers, int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port> <threads> <buffers> <shm_name>\n", argv[0]);
    exit(1);
  }
  *port = atoi(argv[1]);
  *threads = atoi(argv[2]);
  *buffers = atoi(argv[3]);
}


int main(int argc, char *argv[])
{
  int listenfd, connfd, port, clientlen, threads, buffers;
  struct sockaddr_in clientaddr;

  getargs(&port, &threads, &buffers, argc, argv);

  //
  // CS537 (Part B): Create & initialize the shared memory region...
  //

  // 
  // CS537 (Part A): Create some threads...
  //
  pthread_mutex_t mutex;
  pthread_mutexattr_t mutex_attr;

  // set mutex
  pthread_mutexattr_init(&mutex_attr);
  pthread_mutex_init(&mutex, &mutex_attr);
  pthread_mutexattr_destroy(&mutex_attr);

  // set condition variable
  pthread_cond_t cond_var;
  pthread_condattr_t cond_var_attr;
  
  pthread_condattr_init(cond_var_attr);
  pthread_cond_init(&cond_var, &cond_var_attr);


  listenfd = Open_listenfd(port);
  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);

    // 
    // CS537 (Part A): In general, don't handle the request in the main thread.
    // Save the relevant info in a buffer and have one of the worker threads 
    // do the work. Also let the worker thread close the connection.
    // 
    requestHandle(connfd);
    Close(connfd);
  }
  pthread_mutex_destroy(&mutex);
}
