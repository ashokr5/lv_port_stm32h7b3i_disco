/**
 * @file lv_demo_widgets.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <lvgl/demos/roller/lv_demo_roller.h>
#include "../../lvgl.h"

#if LV_USE_DEMO_ROLLER
/*********************
 *      DEFINES
 *********************/
#define ROLLER_ITEM_MAX		38
#define BAR_MAX_HEIGHT		152
#define BAR_CANVAS_WIDTH	20
#define BAR_SIZE			(BAR_MAX_HEIGHT/ROLLER_ITEM_MAX/2)
#define BAR_CANVAS_HEIGHT	(ROLLER_ITEM_MAX*BAR_SIZE*2) + BAR_SIZE



/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
} disp_size_t;
/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

typedef struct {

	lv_obj_t *canvas;
    lv_layer_t layer;
    lv_draw_line_dsc_t dsc;
    uint8_t sel_index;

}actu_bar;

/**********************
 *  GLOBAL VARIABLES
 **********************/
lv_obj_t * tv;
disp_size_t disp_size;
lv_style_t style_title;
lv_style_t style_text_muted;
lv_style_t style_icon;
lv_style_t style_bullet;

int32_t scroll_y;
uint32_t base_y;
uint32_t base_y_start;
int32_t new_y;

const lv_font_t * font_large;
const lv_font_t * font_normal;

uint32_t toggle_text=0;
lv_style_t style_japanese;
lv_style_t style_taiwanese;
lv_style_t style_arabic;

lv_obj_t * ltr_label2;
volatile uint32_t ct_index=0;
volatile uint32_t op_count=0;
static void timer_step_cb(lv_timer_t * timer);

actu_bar *actu_bar1;
/**********************
 *      MACROS
 **********************/
const uint8_t arrow_icon_map[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xb3, 0x00, 0x14, 0xfa, 0xb6, 0x00, 0xc0, 0xfa, 0xb6, 0x00, 0xf9, 0xfa, 0xb6, 0x00, 0xc4,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf6, 0xb6, 0x00, 0x1c, 0xf9, 0xb6, 0x00, 0xe6, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0xb5, 0x00, 0x34, 0xfa, 0xb6, 0x00, 0xe9, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xb5, 0x00, 0x53, 0xfa, 0xb6, 0x00, 0xeb, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xaa, 0x00, 0x03, 0xf9, 0xb7, 0x00, 0x59, 0xfa, 0xb6, 0x00, 0xf9, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0xff, 0xff, 0x00, 0x01, 0xfb, 0xb7, 0x00, 0x7c, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0xfa, 0xb6, 0x00, 0x99, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0xfb, 0xb7, 0x00, 0x39, 0xfb, 0xb6, 0x00, 0xe3, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0x00, 0x00, 0x00, 0x00, 0xf5, 0xba, 0x00, 0x1a, 0xfa, 0xb6, 0x00, 0xe0, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xaa, 0x00, 0x06, 0xfa, 0xb6, 0x00, 0xd1, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xf9, 0xb6, 0x00, 0xe7,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xb9, 0x00, 0x0b, 0xfa, 0xb5, 0x00, 0xa3, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xe8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xaa, 0x00, 0x03, 0xf9, 0xb5, 0x00, 0x8a, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xff, 0xfa, 0xb6, 0x00, 0xe8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0xb5, 0x00, 0x64, 0xfa, 0xb6, 0x00, 0xea, 0xfa, 0xb6, 0x00, 0xea, 0xfa, 0xb6, 0x00, 0xce,
};

const lv_image_dsc_t arrow_icon = {
  .header.cf = LV_COLOR_FORMAT_ARGB8888,
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.w = 10,
  .header.h = 13,
  .data_size = 130 * 4,
  .data = arrow_icon_map,
};


const uint8_t img_skew_strip2_map[] = {
  0x26, 0x26, 0x26, 0xff, 0x27, 0x27, 0x27, 0xff, 0x27, 0x27, 0x27, 0xff, 0x27, 0x27, 0x27, 0xff, 0x26, 0x26, 0x26, 0xff, 0x26, 0x26, 0x26, 0xff, 0x25, 0x25, 0x25, 0xff, 0x25, 0x25, 0x25, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff,
  0x62, 0x62, 0x62, 0xff, 0x72, 0x72, 0x72, 0xff, 0x72, 0x72, 0x72, 0xff, 0x72, 0x72, 0x72, 0xff, 0x73, 0x73, 0x73, 0xff, 0x73, 0x73, 0x73, 0xff, 0x73, 0x73, 0x73, 0xff, 0x74, 0x74, 0x74, 0xff, 0x74, 0x74, 0x74, 0xff, 0x74, 0x74, 0x74, 0xff, 0x74, 0x74, 0x74, 0xff, 0x74, 0x74, 0x74, 0xff, 0x73, 0x73, 0x73, 0xff, 0x73, 0x73, 0x73, 0xff, 0x73, 0x73, 0x73, 0xff, 0x72, 0x72, 0x72, 0xff, 0x72, 0x72, 0x72, 0xff, 0x71, 0x71, 0x71, 0xff, 0x71, 0x71, 0x71, 0xff, 0x71, 0x71, 0x71, 0xff, 0x70, 0x70, 0x70, 0xff, 0x70, 0x70, 0x70, 0xff, 0x70, 0x70, 0x70, 0xff, 0x6f, 0x6f, 0x6f, 0xff, 0x6f, 0x6f, 0x6f, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x6d, 0x6d, 0x6d, 0xff, 0x5d, 0x5d, 0x5d, 0xff,
  0x4d, 0x4d, 0x4d, 0xff, 0x5a, 0x5a, 0x5a, 0xff, 0x5b, 0x5b, 0x5b, 0xff, 0x5b, 0x5b, 0x5b, 0xff, 0x5c, 0x5c, 0x5c, 0xff, 0x5c, 0x5c, 0x5c, 0xff, 0x5c, 0x5c, 0x5c, 0xff, 0x5d, 0x5d, 0x5d, 0xff, 0x5d, 0x5d, 0x5d, 0xff, 0x5e, 0x5e, 0x5e, 0xff, 0x5e, 0x5e, 0x5e, 0xff, 0x5f, 0x5f, 0x5f, 0xff, 0x5f, 0x5f, 0x5f, 0xff, 0x61, 0x61, 0x61, 0xff, 0x61, 0x61, 0x61, 0xff, 0x62, 0x62, 0x62, 0xff, 0x62, 0x62, 0x62, 0xff, 0x62, 0x62, 0x62, 0xff, 0x63, 0x63, 0x63, 0xff, 0x63, 0x63, 0x63, 0xff, 0x64, 0x64, 0x64, 0xff, 0x64, 0x64, 0x64, 0xff, 0x65, 0x65, 0x65, 0xff, 0x65, 0x65, 0x65, 0xff, 0x66, 0x66, 0x66, 0xff, 0x66, 0x66, 0x66, 0xff, 0x67, 0x67, 0x67, 0xff, 0x67, 0x67, 0x67, 0xff, 0x68, 0x68, 0x68, 0xff, 0x59, 0x59, 0x59, 0xff,
  0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0xff,
};

const lv_image_dsc_t img_skew_strip2 = {
  .header.cf = LV_COLOR_FORMAT_ARGB8888,
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.w = 30,
  .header.h = 4,
  .data_size = 120 * 4,
  .data = img_skew_strip2_map,
};

lv_obj_t *levbar;
lv_obj_t * txt_xy_label;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static void lv_demo_roller_components_init(void)
{

    if(LV_HOR_RES <= 320) disp_size = DISP_SMALL;
    else if(LV_HOR_RES < 720) disp_size = DISP_MEDIUM;
    else disp_size = DISP_LARGE;

    font_large = LV_FONT_DEFAULT;
    font_normal = LV_FONT_DEFAULT;
    if(disp_size == DISP_LARGE) {
#ifdef USE_ALIGNED_FONTS
        font_large     = &lv_font_benchmark_montserrat_24_aligned;
#elif LV_FONT_MONTSERRAT_24
        font_large     = &lv_font_montserrat_24;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_24 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#ifdef USE_ALIGNED_FONTS
        font_normal    = &lv_font_benchmark_montserrat_16_aligned;
#elif LV_FONT_MONTSERRAT_16
        font_normal    = &lv_font_montserrat_16;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_16 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
    else if(disp_size == DISP_MEDIUM) {
#ifdef USE_ALIGNED_FONTS
        font_large     = &lv_font_benchmark_montserrat_20_aligned;
#elif LV_FONT_MONTSERRAT_20
        font_large     = &lv_font_montserrat_20;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_20 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#ifdef USE_ALIGNED_FONTS
        font_normal    = &lv_font_benchmark_montserrat_14_aligned;
#elif LV_FONT_MONTSERRAT_14
        font_normal    = &lv_font_montserrat_14;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_14 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
    else {   /* disp_size == DISP_SMALL */
#ifdef USE_ALIGNED_FONTS
        font_large     = &lv_font_benchmark_montserrat_18_aligned;
#elif LV_FONT_MONTSERRAT_18
        font_large     = &lv_font_montserrat_18;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_18 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#ifdef USE_ALIGNED_FONTS
        font_normal    = &lv_font_benchmark_montserrat_12_aligned;
#elif LV_FONT_MONTSERRAT_12
        font_normal    = &lv_font_montserrat_12;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_12 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
#if LV_USE_THEME_DEFAULT
    lv_theme_default_init(NULL, lv_color_black(), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
                          font_normal);
#endif

    lv_obj_set_style_text_font(lv_screen_active(), font_normal, 0);


    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, font_large);

    lv_style_init(&style_text_muted);
    lv_style_set_text_opa(&style_text_muted, LV_OPA_50);


    lv_style_init(&style_icon);
    lv_style_set_text_color(&style_icon, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_icon, font_large);

    lv_style_init(&style_bullet);
    lv_style_set_border_width(&style_bullet, 0);
    lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);
}

static void timer_step_cb(lv_timer_t * t)
{
    LV_UNUSED(t);
    static uint32_t state = 0;
    lv_label_set_text_fmt(txt_xy_label, "scy=%d, ny=%d", scroll_y, new_y);

}
static void roller_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target_obj(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
       // char buf[32];
       // lv_roller_get_selected_str(obj, buf, sizeof(buf));
      //  LV_LOG_USER("Selected value: %s", buf);
    	ct_index = lv_roller_get_selected(obj);
    	lv_set_actubar_value((uint8_t)ct_index);
    }
}

static void roller_scroll_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    scroll_y = lv_obj_get_scroll_y(obj);
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SCROLL_BEGIN)
    {
    	base_y = actu_bar1->sel_index;
    }

    if(code == LV_EVENT_SCROLL)
    {
        new_y = base_y + (scroll_y/10); // 10-> index to pixel size (H)
        if(new_y<0)new_y = 0;
        lv_label_set_text_fmt(txt_xy_label, "scy=%d, ney=%d", scroll_y, new_y);

        lv_set_actubar_value(new_y);
    }

    if(code == LV_EVENT_SCROLL_END)
    {
    	base_y = actu_bar1->sel_index;
    }
   // base_y = actu_bar1->sel_index;

    //lv_obj_set_y(arrow, new_y);
    //lv_set_actubar_value(ct_index);


}

static void event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch(code) {
        case LV_EVENT_PRESSED:
        //	toggle_text=1-toggle_text;
        //	if(toggle_text){
        //	lv_bar_setRangeLevel(ct_index);
      //  	}
        //	else
        	{


        	}

            break;
        case LV_EVENT_CLICKED:

            break;
        case LV_EVENT_LONG_PRESSED:

            break;
        case LV_EVENT_LONG_PRESSED_REPEAT:
            break;
        default:
            break;
    }
}




void lv_demo_roller(void)
{

	lv_create_roller();

	lv_draw_actu_bar();

	lv_obj_t * arrowicon = lv_image_create(lv_screen_active());
	lv_image_set_src(arrowicon, &arrow_icon); // Use a built-in symbol
	lv_obj_set_pos(arrowicon,180,95);


   // lv_obj_t * ltr_label = lv_label_create(lv_screen_active());
   // lv_label_set_text(ltr_label, "Text in ENG, JAP, PER CHI");
   // lv_obj_set_style_text_font(ltr_label, &lv_font_montserrat_14, 0);
   // lv_obj_set_width(ltr_label, 400);
   // lv_obj_align(ltr_label, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn, 80, 30);
    lv_obj_set_pos(btn, 380, 8);
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Click");
    lv_obj_center(btn_label);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_PRESSED, NULL);
}



#if 0
static void roller_rotary_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target_obj(e);

    if(code == LV_EVENT_PRESSED) {


    	scroll_y = lv_obj_get_scroll_y(obj);


       // char buf[32];
       // lv_roller_get_selected_str(obj, buf, sizeof(buf));
      //  LV_LOG_USER("Selected value: %s", buf);
    	op_count = lv_roller_get_option_count(obj);
    	lv_set_actubar_value((uint8_t)op_count);
    }
}
#endif
/**
 * Add a fade mask to roller.
 */

static void generate_mask(lv_draw_buf_t * mask)
{
    /*Create a "8 bit alpha" canvas and clear it*/
    lv_obj_t * canvas = lv_canvas_create(lv_screen_active());
    lv_canvas_set_draw_buf(canvas, mask);
    lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_TRANSP);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    /*Draw a label to the canvas. The result "image" will be used as mask*/
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_grad.dir = LV_GRAD_DIR_VER;
    rect_dsc.bg_grad.stops[0].color = lv_color_black();
    rect_dsc.bg_grad.stops[1].color = lv_color_make(0x97, 0x97, 0x97);
    rect_dsc.bg_grad.stops[0].opa = LV_OPA_COVER;
    rect_dsc.bg_grad.stops[1].opa = LV_OPA_COVER;
   // rect_dsc.radius = 10; //#ok
    lv_area_t a = {0, 0, mask->header.w - 1, mask->header.h / 2 - 10};
    lv_draw_rect(&layer, &rect_dsc, &a);

    a.y1 = mask->header.h / 2 + 10;
    a.y2 = mask->header.h - 1;
    rect_dsc.bg_grad.stops[0].color = lv_color_make(0x97, 0x97, 0x97);
    rect_dsc.bg_grad.stops[1].color = lv_color_black();
    lv_draw_rect(&layer, &rect_dsc, &a);

    lv_canvas_finish_layer(canvas, &layer);

    /*Comment it to make the mask visible*/
    lv_obj_delete(canvas);
}

void lv_create_roller(void)
{
	LV_IMAGE_DECLARE(arrow_icon); // Declaration
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_black(), 0);

    static lv_style_t style;

    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_make(0x3F, 0x3F, 0x3F));
    lv_style_set_text_color(&style, lv_color_make(0x74, 0x74, 0x74));//lv_color_make(0x00, 0xD2, 0xFC));
    lv_style_set_width(&style, 156);
    //lv_style_set_text_align(&style, LV_TEXT_ALIGN_RIGHT);
    lv_style_set_border_width(&style, 0);
    lv_style_set_radius(&style, 5);
   // lv_style_set_bg_grad_color(&style,  lv_color_make(0xab, 0xdc, 0xee));
    txt_xy_label = lv_label_create(lv_screen_active());
    lv_obj_set_style_text_color(txt_xy_label, lv_color_white(), LV_PART_MAIN);

    lv_obj_set_pos(txt_xy_label, 0, 180);

    lv_obj_t * roller1 = lv_roller_create(lv_screen_active());

    lv_obj_add_style(roller1, &style, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(roller1, LV_OPA_50, LV_PART_SELECTED);
    lv_obj_set_style_text_color(roller1, lv_color_make(0x00, 0xD2, 0xFC), LV_PART_SELECTED);
    lv_obj_set_style_bg_color(roller1, lv_color_make(0x00, 0x9A, 0xB8), LV_PART_SELECTED);
    lv_obj_set_style_text_align(roller1, LV_TEXT_ALIGN_CENTER, LV_PART_ANY);

    //lv_obj_set_style_bg_image_recolor_opa(roller1, lv_color_make(0x08, 0x70, 0x97), LV_PART_SELECTED);
    //lv_obj_set_style_arc_color(roller1, lv_color_make(0x08, 0x70, 0x97), LV_PART_SELECTED);

    lv_obj_add_flag(roller1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_remove_flag(roller1, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);
    lv_roller_set_options(roller1,
                            "0.0mm\n"
                            "0.1mm\n"
                            "0.2mm\n"
                            "0.3mm\n"
                            "0.4mm\n"
                            "0.5mm\n"
                            "0.6mm\n"
                            "0.7mm\n"
                            "0.8mm\n"
                            "0.9mm\n"
                            "1.0mm\n"
    						"1.1mm\n"
							"1.2mm\n"
							"1.3mm\n"
							"1.4mm\n"
							"1.5mm\n"
							"1.6mm\n"
							"1.7mm\n"
							"1.8mm\n"
							"1.9mm\n"
							"2.0mm\n"
    						"2.1mm\n"
							"2.2mm\n"
							"2.3mm\n"
							"2.4mm\n"
							"2.5mm\n"
							"2.6mm\n"
							"2.7mm\n"
							"2.8mm\n"
							"2.9mm\n"
							"3.0mm\n"
    						"3.1mm\n"
							"3.2mm\n"
							"3.3mm\n"
							"3.4mm\n"
							"3.5mm\n"
							"3.6mm\n"
							"3.7mm\n"
							"3.8mm\n",
						//	"3.9mm\n"
						//	"4.0mm\n",
                          LV_ROLLER_MODE_NORMAL);

   // lv_obj_center(roller1);
    lv_obj_set_pos(roller1,200,20);
    lv_roller_set_visible_row_count(roller1, 5);
    lv_roller_set_selected(roller1, 0, LV_ANIM_OFF);
    //lv_obj_set_style_anim_time(roller1, 500, LV_PART_MAIN);
    lv_obj_set_style_radius(roller1, 5, LV_PART_SELECTED);

    lv_obj_add_event_cb(roller1, roller_scroll_event_cb, LV_EVENT_SCROLL | LV_EVENT_SCROLL_BEGIN , NULL);
    lv_obj_add_event_cb(roller1, roller_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

   // lv_timer_create(timer_step_cb, 1000, NULL);
    /* Create the mask to make the top and bottom part of roller faded.
     * The width and height are empirical values for simplicity*/
   // LV_DRAW_BUF_DEFINE_STATIC(mask, 110, 150, LV_COLOR_FORMAT_L8);
   // LV_DRAW_BUF_INIT_STATIC(mask);

   // generate_mask(&mask);
   // lv_obj_set_style_bitmap_mask_src(roller1, &mask, 0);
}




void lv_draw_actu_bar(uint8_t size)
{

    /*Create a buffer for the canvas*/
    LV_DRAW_BUF_DEFINE_STATIC(draw_bar_buf, BAR_CANVAS_WIDTH, BAR_CANVAS_HEIGHT, LV_COLOR_FORMAT_ARGB8888);
    LV_DRAW_BUF_INIT_STATIC(draw_bar_buf);

    /*Create a canvas and initialize its palette*/
    actu_bar1->canvas = lv_canvas_create(lv_screen_active());
    lv_canvas_set_draw_buf(actu_bar1->canvas, &draw_bar_buf);
    lv_canvas_fill_bg(actu_bar1->canvas, lv_color_make(0x3F, 0x3F, 0x3F), LV_OPA_COVER);

    lv_canvas_init_layer(actu_bar1->canvas, &actu_bar1->layer);

    lv_draw_line_dsc_init(&actu_bar1->dsc);

    actu_bar1->dsc.color = lv_palette_main(LV_PALETTE_GREY);
    actu_bar1->dsc.width = BAR_SIZE;
    actu_bar1->dsc.round_end = 1;
    actu_bar1->dsc.round_start = 1;

    for(int i=0;i< ROLLER_ITEM_MAX ;i++)
    {

    	actu_bar1->dsc.p1.x = 0;
    	actu_bar1->dsc.p1.y = i*BAR_SIZE*2;
    	actu_bar1->dsc.p2.x = BAR_CANVAS_WIDTH;
    	actu_bar1->dsc.p2.y = i*BAR_SIZE*2;
    	lv_draw_line(&actu_bar1->layer, &actu_bar1->dsc);

    }

    lv_canvas_finish_layer(actu_bar1->canvas, &actu_bar1->layer);

    lv_obj_set_pos(actu_bar1->canvas, 150,26);

    #if 0
    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t * line1, * line2, * line3;
    line1 = lv_line_create(lv_scr_act());
    lv_line_set_points(line1, line1_points, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);

    line2 = lv_line_create(lv_scr_act());
    lv_line_set_points(line2, line2_points, 2);     /*Set the points*/
    lv_obj_add_style(line2, &style_line, 0);

    line3 = lv_line_create(lv_scr_act());
    lv_line_set_points(line3, line3_points, 2);     /*Set the points*/
    lv_obj_add_style(line3, &style_line, 0);
#endif
   // lv_obj_set_pos(line1,140,25);

}



void lv_set_actubar_value(uint8_t value)
{

	static uint8_t bar_offset = 2;

	if(value < ROLLER_ITEM_MAX)
	{
	    actu_bar1->dsc.color = lv_palette_main(LV_PALETTE_GREY);
    	actu_bar1->dsc.p1.x = 0;
    	actu_bar1->dsc.p1.y = actu_bar1->sel_index*BAR_SIZE*2;
    	actu_bar1->dsc.p2.x = BAR_CANVAS_WIDTH;
    	actu_bar1->dsc.p2.y = actu_bar1->sel_index*BAR_SIZE*2;
    	lv_draw_line(&actu_bar1->layer, &actu_bar1->dsc);

	    actu_bar1->dsc.color = lv_palette_main(LV_PALETTE_BLUE);
    	actu_bar1->dsc.p1.x = 0;
    	actu_bar1->dsc.p1.y = value*BAR_SIZE*2;
    	actu_bar1->dsc.p2.x = BAR_CANVAS_WIDTH;
    	actu_bar1->dsc.p2.y = value*BAR_SIZE*2;
    	lv_draw_line(&actu_bar1->layer, &actu_bar1->dsc);

		actu_bar1->sel_index = value;

	    lv_canvas_finish_layer(actu_bar1->canvas, &actu_bar1->layer);

	}


}

void lv_example_bar(void)
{
   // LV_IMAGE_DECLARE(img_skew_strip2);
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
   // lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);
   // lv_style_set_bg_color(&style_indic, lv_color_make(0x4f, 0x4f, 0x4f));
   // lv_style_set_bg_image_recolor(&style_indic, lv_color_make(0x4f, 0x4f, 0x4f));
   // lv_style_set_bg_image_opa(&style_indic, LV_OPA_100);

   // lv_style_set_bg_image_src(&style_indic, &img_skew_strip2);
   // lv_style_set_bg_image_tiled(&style_indic, true);

    levbar = lv_bar_create(lv_screen_active());
    lv_obj_set_style_bg_image_src(levbar, &img_skew_strip2, LV_PART_MAIN);
    lv_obj_set_style_bg_image_tiled(levbar, true, LV_PART_MAIN);
    lv_obj_set_style_bg_color(levbar, lv_color_make(0x24, 0x24, 0x24), LV_PART_MAIN);
    //lv_obj_set_style_bg_color(bar, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR);

    lv_obj_add_style(levbar, &style_indic, LV_PART_INDICATOR);
    lv_bar_set_orientation(levbar, LV_BAR_ORIENTATION_VERTICAL);
    lv_obj_set_style_radius(levbar,0,LV_PART_MAIN);
    lv_obj_set_style_radius(levbar,2,LV_PART_INDICATOR);

    lv_obj_set_size(levbar, 30, 150);
    lv_bar_set_mode(levbar, LV_BAR_MODE_RANGE);
   // lv_obj_set_style_transform_rotation(bar, 90, 0);
    lv_obj_set_pos(levbar,140,25);
  //  lv_bar_set_value(bar, 52, LV_ANIM_OFF);
   // lv_bar_set_start_value(bar, 50, LV_ANIM_OFF);

    lv_bar_set_max_value(levbar, 40);
    lv_bar_set_min_value(levbar, 0);
   // lv_bar_setRangeLevel(levbar, 0);

    // 2. Add an event callback for when the value changes (e.g., by animation)


}


void lv_bar_setRangeLevel(uint8_t value)
{
	//lv_bar_set_range(bar, value, value+2);
   // lv_bar_set_value(bar, value+2, LV_ANIM_OFF);
	lv_bar_set_start_value(levbar, value*2, LV_ANIM_OFF);
    lv_bar_set_value(levbar, (value*2) +1, LV_ANIM_OFF);

}




#endif

