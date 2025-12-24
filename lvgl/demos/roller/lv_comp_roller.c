/*
 * lv_comp_roller.c
 *
 *  Created on: Dec 24, 2025
 *      Author: ar5
 */
/*********************
 *      INCLUDES
 *********************/
#include "../../lvgl.h"
#include "../../src/draw/lv_draw.h"
#include "lv_comp_roller.h"
/*********************
 *      DEFINES
 *********************/

#define ROLLER_STYLE_BGCOLOR_MAIN 	0x000000
#define ROLLER_STYLE_BGCOLOR_SEL 	0x008B8B
#define ROLLER_STYLE_FGCOLOR_MAIN 	0xFFFFFF
#define ROLLER_STYLE_FGCOLOR_SEL 	0x00B6FA


static uint8_t mask_generated = 0;
/**********************
 *      TYPEDEFS
 **********************/
roller_data_t data_default = {
		.row_count = 7,
		.row_list  = "row1\nrow2\nrow3\nrow4\nrow5\nrow6\nrow7",
		.row_visible = 5
};

roller_style_t style_default = {
		.bgcolor_main = ROLLER_STYLE_BGCOLOR_MAIN,
		.bgcolor_sel = ROLLER_STYLE_BGCOLOR_SEL,
		.textcolor_main = ROLLER_STYLE_FGCOLOR_MAIN,
		.textcolor_sel = ROLLER_STYLE_FGCOLOR_SEL,
		.line_space = 7
};



/**********************
 *  STATIC PROTOTYPES
 **********************/

static void generate_mask(lv_draw_buf_t * mask)
{
    lv_obj_t * canvas = lv_canvas_create(lv_screen_active());
    lv_canvas_set_draw_buf(canvas, mask);
    lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_TRANSP);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_grad.dir = LV_GRAD_DIR_VER;

    rect_dsc.bg_grad.stops[0].color = lv_color_hex(0x171717);//0x008B8Blv_color_black();// lv_color_make(0x38, 0x38, 0x38);
    rect_dsc.bg_grad.stops[1].color = lv_color_black();
    rect_dsc.bg_grad.stops[0].opa = LV_OPA_100;
    rect_dsc.bg_grad.stops[1].opa = LV_OPA_0;

    lv_area_t a = {0, 0, mask->header.w - 1,( mask->header.h / 4) + 4};
    lv_draw_rect(&layer, &rect_dsc, &a);

    a.y1 = mask->header.h - ((mask->header.h / 4) + 4);
    a.y2 = mask->header.h - 1;
    rect_dsc.bg_grad.stops[0].color = lv_color_black();
    rect_dsc.bg_grad.stops[1].color = lv_color_hex(0x171717); //grey
    rect_dsc.bg_grad.stops[0].opa = LV_OPA_0;
    rect_dsc.bg_grad.stops[1].opa = LV_OPA_100;
    lv_draw_rect(&layer, &rect_dsc, &a);
    lv_canvas_finish_layer(canvas, &layer);
    lv_obj_delete(canvas);
}


roller_t* lv_comp_roller_draw(lv_obj_t *parent, uint8_t height, uint8_t weight, roller_data_t *data)
{

	roller_t* roller;

	roller->height = height;
	roller->weight = weight;

    LV_DRAW_BUF_DEFINE_STATIC(fade_mask, 208, 120, LV_COLOR_FORMAT_L8);

    if (!mask_generated)
    {
        LV_DRAW_BUF_INIT_STATIC(fade_mask);
        generate_mask(&fade_mask);
        mask_generated = true;
    }

    roller->obj = lv_roller_create(parent);

	lv_comp_roller_set_data(roller, &data_default);

    lv_roller_set_selected(roller->obj, 2, LV_ANIM_ON);
    lv_obj_set_width(roller->obj, weight);
    lv_obj_set_height(roller->obj, height);
    lv_obj_set_align(roller->obj, LV_ALIGN_RIGHT_MID);

    lv_comp_roller_set_style(roller, data);

    lv_obj_add_flag(roller->obj, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);
    lv_obj_set_scrollbar_mode(roller->obj, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_bitmap_mask_src(roller->obj, &fade_mask, LV_PART_MAIN);

    return roller;

}

void lv_comp_roller_set_data(roller_t *roller, roller_data_t *data)
{

	if(NULL != data->row_list)
	{
	    lv_roller_set_options(roller->obj, data->row_list, LV_ROLLER_MODE_NORMAL);
	}
	else
	{
	    lv_roller_set_options(roller->obj, data_default.row_list, LV_ROLLER_MODE_NORMAL);
	}


    lv_roller_set_visible_row_count(roller->obj, data->row_visible);


}

void lv_comp_roller_set_style(roller_t *roller, roller_style_t *style)
{

    lv_obj_set_style_bg_opa(roller->obj, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(roller->obj, LV_OPA_50, LV_PART_SELECTED);

    lv_obj_set_style_border_width(roller->obj, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(roller->obj, 4, LV_PART_SELECTED);

    lv_obj_set_style_text_font(roller->obj, &lv_font_montserrat_14, 0);

    lv_obj_set_style_bg_color(roller->obj, lv_color_hex(style_default.bgcolor_sel), LV_PART_SELECTED);
    lv_obj_set_style_text_color(roller->obj, lv_color_hex(style_default.textcolor_main), LV_PART_MAIN);
    lv_obj_set_style_text_color(roller->obj, lv_color_hex(style_default.textcolor_sel), LV_PART_SELECTED);
    lv_obj_set_style_text_line_space(roller->obj, style_default.line_space, 0);

	if(NULL != style)
	{
	    lv_obj_set_style_bg_color(roller->obj, lv_color_hex(style->bgcolor_sel), LV_PART_SELECTED);
	    lv_obj_set_style_text_color(roller->obj, lv_color_hex(style->textcolor_main), LV_PART_MAIN);
	    lv_obj_set_style_text_color(roller->obj, lv_color_hex(style->textcolor_sel), LV_PART_SELECTED);
	    lv_obj_set_style_text_line_space(roller->obj, style->line_space, 0);
	}


}

void lv_comp_roller_set_event(roller_t *roller, roller_event *event)
{

    lv_obj_add_event_cb(roller->obj, (roller_event) event , LV_EVENT_VALUE_CHANGED, NULL);

}

void lv_comp_roller_clear_event(roller_t *roller, roller_event *event)
{

	lv_obj_remove_event(roller->obj, 0);

}
