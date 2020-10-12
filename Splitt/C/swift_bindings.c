//
//  swift_bindings.c
//  Splitt
//
//  Created by Adi Mehrotra on 11/10/20.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "swift_bindings.h"
#include "listener.h"
#include "alert.h"

pthread_t thread_id;

void* splitt_thread_handler(void* arg)
{
        int ret = start_listener();
        if (ret == 1) {
                *(int*) arg = 1;
        }
        
        return NULL;
}

void start_splitt_deamon()
{
        int ret_val = 0;
        int err = pthread_create(&thread_id, NULL, splitt_thread_handler, (void*) &ret_val);
        if (err != 0) {
                fprintf(stderr, "Failed to create Splitt deamon");
        }
        
        sleep(1);
        if (ret_val != 0) {
                alert_permission_error();
		exit(1);
        }
}

void stop_splitt_deamon()
{
        pthread_cancel(thread_id);
}
