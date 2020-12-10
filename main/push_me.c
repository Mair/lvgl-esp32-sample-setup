#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "lvgl/lvgl.h"
#include "push_me.h"
#include "sending_task.h"

extern xSemaphoreHandle on_btn_press;

static void simulate_btn(lv_task_t *t);

static void poll_payload(lv_task_t *t)
{
    if(messages_queue == NULL) return;
    payload_t payload;
    if(xQueueReceive(messages_queue,&payload,0))
    {
        lv_obj_t* lbl_count = t->user_data;
        lv_label_set_text_fmt(lbl_count,"count is %d",payload.count);
    }
}

static void on_button_pressed(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_SHORT_CLICKED)
    {
        printf("pressed\n");
        xSemaphoreGive(on_btn_press);
    }
}

void push_me(void)
{
    lv_obj_t* btn = lv_btn_create(lv_scr_act(),NULL);
    lv_obj_t* lbl = lv_label_create(btn,NULL);
    lv_label_set_text(lbl,"push me");
    lv_obj_align(btn,NULL,LV_ALIGN_CENTER,0,0);
    lv_obj_set_event_cb(btn,on_button_pressed);

    lv_obj_t* lbl_count = lv_label_create(lv_scr_act(),NULL);
    lv_obj_align(lbl_count,btn,LV_ALIGN_OUT_BOTTOM_LEFT,0,5);
    lv_label_set_text(lbl_count,"");
    lv_task_create(poll_payload,500,LV_TASK_PRIO_HIGH,lbl_count);
    

    //simulate a btn press after 3 seconds
    lv_task_t *task = lv_task_create(simulate_btn,3000,LV_TASK_PRIO_MID,btn);
    lv_task_once(task);
}

// I dont have a touch screen setup so simulate a click
void simulate_btn(lv_task_t *t)
{
    lv_obj_t* btn = t->user_data;
    lv_event_send(btn,LV_EVENT_SHORT_CLICKED, NULL);
}
