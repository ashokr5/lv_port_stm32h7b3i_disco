/**
 * @file lv_demo_widgets.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <lvgl/demos/photoshow/lv_demo_photoshow.h>
#include "../../lvgl.h"

#if LV_USE_DEMO_PHOTOSHOW
/*********************
 *      DEFINES
 *********************/

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
static void auto_step_cb(lv_timer_t * timer);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/
lv_obj_t * tv;
disp_size_t disp_size;
lv_style_t style_title;
lv_style_t style_text_muted;
lv_style_t style_icon;
lv_style_t style_bullet;

const lv_font_t * font_large;
const lv_font_t * font_normal;

uint32_t toggle_text=0;
uint32_t slide_counter=0;
lv_style_t style_japanese;
lv_style_t style_taiwanese;
lv_style_t style_arabic;

lv_obj_t * ltr_label2;

extern const lv_image_dsc_t photoslide1;
extern const lv_image_dsc_t photoslide2;
extern const lv_image_dsc_t photoslide3;
extern const lv_image_dsc_t photoslide4;

const lv_image_dsc_t* slide_array[4]={&photoslide1,&photoslide2,&photoslide3,&photoslide4};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void auto_step_cb(lv_timer_t * t)
{
    LV_UNUSED(t);
    static uint32_t state = 0;

	slide_counter++;
	if(slide_counter>3)slide_counter=0;
	lv_obj_set_style_bg_image_src(lv_screen_active(), slide_array[slide_counter], 0);


}

static void lv_demo_photoshow_components_init(void)
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
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
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


static void event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch(code) {
        case LV_EVENT_PRESSED:

        	slide_counter++;
        	if(slide_counter>3)slide_counter=0;
			lv_obj_set_style_bg_image_src(lv_screen_active(), slide_array[slide_counter], 0);

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


void lv_demo_photoshow(void)
{

    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn, 80, 30);
    lv_obj_set_pos(btn, 380, 8);
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Next");
    lv_obj_center(btn_label);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_PRESSED, NULL);

   // lv_obj_t * obj;
   //	obj = lv_obj_create(lv_screen_active());
   //	lv_obj_set_size(obj, 480, 270);

    lv_obj_set_style_bg_image_src(lv_screen_active(), slide_array[0], 0);

    lv_timer_create(auto_step_cb, 500, NULL);

}


/**
 * Show mixed LTR, RTL and Chinese label
 */
void lv_example_label_ext(void)
{
    lv_obj_t * ltr_label = lv_label_create(lv_screen_active());
    lv_label_set_text(ltr_label, "Text in ENG, JAP, PER CHI");
    lv_obj_set_style_text_font(ltr_label, &lv_font_marbles_16, 0);
    lv_obj_set_width(ltr_label, 400);
    lv_obj_align(ltr_label, LV_ALIGN_TOP_LEFT, 5, 5);

    ltr_label2 = lv_label_create(lv_screen_active());
    lv_label_set_text(ltr_label2, "Loading Chinese, 是一种嵌入机械或电气系统内部、具有专（SoC）。   ");
    lv_obj_set_style_text_font(ltr_label2, &lv_font_source_han_sans_sc_16_cjk, 0);
    lv_obj_set_width(ltr_label2, 400);
    lv_obj_align(ltr_label2, LV_ALIGN_TOP_LEFT, 5, 50);

    lv_obj_t * rtl_label = lv_label_create(lv_screen_active());
    lv_label_set_text(rtl_label,
                      "Loading Persian,מעבד, או בשמו המלא יחידת עיבוד מרכזית (באנגלית:).");
    lv_obj_set_style_base_dir(rtl_label, LV_BASE_DIR_RTL, 0);
    lv_obj_set_style_text_font(rtl_label, &lv_font_dejavu_16_persian_hebrew, 0);
    lv_obj_set_width(rtl_label, 400);
    lv_obj_align(rtl_label, LV_ALIGN_TOP_LEFT, 5, 110);

    lv_obj_t * cz_label = lv_label_create(lv_screen_active());
    lv_label_set_text(cz_label,
                      "Loading 嵌入式系统，\n是一种嵌入机械或电气系统内部、具有专一功能和实时计算性能的计算机系统。");
    lv_obj_set_style_text_font(cz_label, &lv_font_source_han_sans_sc_16_cjk, 0);
    lv_obj_set_width(cz_label, 400);
    lv_obj_align(cz_label, LV_ALIGN_TOP_LEFT, 5,160);
}



#endif

