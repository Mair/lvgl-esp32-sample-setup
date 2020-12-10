#ifndef sending_task_h
#define sending_task_h

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

extern xQueueHandle messages_queue;

typedef struct payload_t
{
    int count;
}payload_t;

void sending_task(void *params);

#endif