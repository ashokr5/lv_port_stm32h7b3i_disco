/*
 * lv_comp_actubar.c
 *
 *  Created on: Dec 23, 2025
 *      Author: ar5
 */
/*********************
 *      INCLUDES
 *********************/

#include "lv_comp_actubar.h"
#include "../../lvgl.h"
#include "../../src/draw/lv_draw.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/


actubar_t* lv_comp_actubar_draw(lv_obj_t *parent, int32_t x, int32_t y)
{

	actubar_t* bar;

	//if(0 != width && 0 != height)
	//{
		/*Create a buffer for the canvas*/
		LV_DRAW_BUF_DEFINE_STATIC(draw_bar_buf, BAR_CANVAS_WIDTH, BAR_CANVAS_HEIGHT, LV_COLOR_FORMAT_ARGB8888);
		LV_DRAW_BUF_INIT_STATIC(draw_bar_buf);
	//}

    /*Create a canvas and initialize its palette*/
    bar->canvas = lv_canvas_create(parent);
    lv_canvas_set_draw_buf(bar->canvas, &draw_bar_buf);
    lv_canvas_fill_bg(bar->canvas, lv_color_hex(0x171717), LV_OPA_COVER);//24

    lv_canvas_init_layer(bar->canvas, &bar->layer);

    lv_draw_line_dsc_init(&bar->dsc);

    bar->dsc.color = lv_color_hex(0x424242); //lv_palette_main(LV_PALETTE_GREY);
    bar->dsc.width = BAR_LINE_HEIGHT;
    bar->dsc.round_end = 1;
    bar->dsc.round_start = 1;


    for(int i=0;i< BAR_ITEM_MAX ;i++)
    {

    	bar->dsc.p1.x = 0;
    	bar->dsc.p1.y = i*(BAR_LINE_HEIGHT + BAR_LINE_GAP_HEIGHT) + BAR_LINE_HEIGHT_OFFSET;
    	bar->dsc.p2.x = BAR_CANVAS_WIDTH;
    	bar->dsc.p2.y = i*(BAR_LINE_HEIGHT + BAR_LINE_GAP_HEIGHT) + BAR_LINE_HEIGHT_OFFSET;
    	lv_draw_line(&bar->layer, &bar->dsc);

    }

    lv_canvas_finish_layer(bar->canvas, &bar->layer);

    lv_obj_set_pos(bar->canvas, x,y);

    bar->sel_index =0;

    return bar;

}


void lv_comp_actubar_set_value(actubar_t *bar, uint8_t value)
{

//	if(value < ROLLER_ITEM_MAX)
	{
	    bar->dsc.color = lv_color_hex(0x424242);
	    bar->dsc.p1.x = 0;
	    bar->dsc.p1.y = bar->sel_index*(BAR_LINE_HEIGHT + BAR_LINE_GAP_HEIGHT) + BAR_LINE_HEIGHT_OFFSET;
	    bar->dsc.p2.x = BAR_CANVAS_WIDTH;
	    bar->dsc.p2.y = bar->sel_index*(BAR_LINE_HEIGHT + BAR_LINE_GAP_HEIGHT) + BAR_LINE_HEIGHT_OFFSET;
    	lv_draw_line(&bar->layer, &bar->dsc);

    	bar->dsc.color = lv_color_hex(0x008B8B); //lv_color_make(0x4C, 0xC0, 0xEC);
    	bar->dsc.p1.x = 0;
    	bar->dsc.p1.y = value*(BAR_LINE_HEIGHT + BAR_LINE_GAP_HEIGHT) + BAR_LINE_HEIGHT_OFFSET;
    	bar->dsc.p2.x = BAR_CANVAS_WIDTH;
    	bar->dsc.p2.y = value*(BAR_LINE_HEIGHT + BAR_LINE_GAP_HEIGHT) + BAR_LINE_HEIGHT_OFFSET;
    	lv_draw_line(&bar->layer, &bar->dsc);

    	bar->sel_index = value;

	    lv_canvas_finish_layer(bar->canvas, &bar->layer);

	}


}
