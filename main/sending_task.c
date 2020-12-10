#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "sending_task.h"
#include "esp_log.h"

#define TAG "SENDER"
xQueueHandle messages_queue;

void sending_task(void *params)
{
    messages_queue = xQueueCreate(10, sizeof(payload_t));
    int count = 0;
    while (true)
    {
        payload_t payload = {
            .count = count++};
            
        if (!xQueueSend(messages_queue, &payload, pdMS_TO_TICKS(200)))
        {
            ESP_LOGE(TAG, "messages_queue full");
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
