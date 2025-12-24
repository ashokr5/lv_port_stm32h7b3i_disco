/*
 * lv_comp_actubar.h
 *
 *  Created on: Dec 23, 2025
 *      Author: ar5
 */

#ifndef LV_COMP_ACTUBAR_H_
#define LV_COMP_ACTUBAR_H_

#include "../../lvgl.h"

/**********************
 *      MACROS
 **********************/
#define BAR_ITEM_MAX			36
#define BAR_LINE_WIDTH			20
#define BAR_LINE_HEIGHT			2 //(BAR_MAX_HEIGHT/ROLLER_ITEM_MAX/2)
#define BAR_LINE_HEIGHT_OFFSET 	1
#define BAR_LINE_GAP_HEIGHT		(BAR_LINE_HEIGHT-1)

#define BAR_CANVAS_HEIGHT		((BAR_ITEM_MAX)*(BAR_LINE_HEIGHT + BAR_LINE_GAP_HEIGHT) + BAR_LINE_HEIGHT_OFFSET)
#define BAR_CANVAS_WIDTH 		BAR_LINE_WIDTH

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {

	lv_obj_t *canvas;
    lv_layer_t layer;
    lv_draw_line_dsc_t dsc;
    uint8_t sel_index;
}actubar_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
actubar_t* lv_comp_actubar_draw(lv_obj_t *parent, int32_t x, int32_t y);
void lv_comp_actubar_set_value(actubar_t *bar, uint8_t value);
uint8_t lv_comp_actubar_get_value(actubar_t *bar);


#endif /* LV_COMP_ACTUBAR_H_ */
