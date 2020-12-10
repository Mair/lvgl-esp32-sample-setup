#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "init_lvgl.h"
#include "sending_task.h"

xSemaphoreHandle on_btn_press;

void some_other_task(void * params)
{
  while (true)
  {
    xSemaphoreTake(on_btn_press, portMAX_DELAY);
    printf("another Task received semaphore\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


void app_main(void)
{

  on_btn_press = xSemaphoreCreateBinary();
  lvgl_main();

  xTaskCreate(some_other_task,"some_other_task", 1024*5,NULL,5,NULL);

  xTaskCreate(sending_task,"sending_task", 1024*5,NULL,5,NULL);
  
}
