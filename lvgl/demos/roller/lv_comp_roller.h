/*
 * lv_comp_roller.h
 *
 *  Created on: Dec 24, 2025
 *      Author: ar5
 */

#ifndef LV_COMP_ROLLER_H_
#define LV_COMP_ROLLER_H_

#include "../../lvgl.h"

/**********************
 *      MACROS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
	uint8_t row_count;
	uint8_t row_visible;
	void *row_list;

}roller_data_t;

typedef struct {

	uint32_t bgcolor_main;
	uint32_t bgcolor_sel;
	uint32_t textcolor_main;
	uint32_t textcolor_sel;
	uint8_t line_space;
}roller_style_t;

typedef struct {

	lv_obj_t *obj;
	uint8_t height;
	uint8_t weight;
	roller_data_t data;
	roller_style_t style;
}roller_t;

typedef void (*roller_event)(lv_event_t * e);

/**********************
 * GLOBAL PROTOTYPES
 **********************/
roller_t* lv_comp_roller_draw(lv_obj_t *parent, uint8_t height, uint8_t weight, roller_data_t *data);

void lv_comp_roller_set_data(roller_t *roller, roller_data_t *data);
void lv_comp_roller_set_style(roller_t *roller, roller_style_t *style);
void lv_comp_roller_set_event(roller_t *roller, roller_event *event);
void lv_comp_roller_clear_event(roller_t *roller, roller_event *event);

#endif /* LV_COMP_ROLLER_H_ */
