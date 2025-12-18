/**
 * @file lv_demo_widgets.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <lvgl/demos/texter/lv_demo_texter.h>
#include "../../lvgl.h"

#if LV_USE_DEMO_TEXTER
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
lv_style_t style_japanese;
lv_style_t style_taiwanese;
lv_style_t style_arabic;

lv_obj_t * ltr_label2;

/**********************
 *      MACROS
 **********************/


const uint8_t txt_str_en[]={"Hi Apple this is Me @1234 & 0<1;"};
const uint8_t txt_str_jp[]={"こんにちは、Apple。私です @1234 & 0<1;"};
const uint8_t txt_str_kr[]={"안녕하세요, 애플입니다. 저는 @1234 & 0<1;입니다."};
const uint8_t txt_str_tc[]={"你好蘋果，我是@1234 & 0<1;"};
const uint8_t txt_str_sc[]={"你好苹果，我是@1234 & 0<1;"};
const uint8_t txt_str_ru[]={"Привет, Apple, это я @1234 & 0<1;"};
const uint8_t txt_str_th[]={"สวัสดี Apple ฉันเอง @1234 & 0<1;"};
const uint8_t txt_str_ta[]={"ஹாய் ஆப்பிள் இது நான் @1234 & 0<1;"};
const uint8_t txt_str_ar[]={"سلام اپل، من هستم @1234 & 0<1;"};
const uint8_t txt_str_ge[]={"Hallo Apple, hier ist ich @1234 & 0<1;"};
const uint8_t txt_str_du[]={"Hoi Apple, dit ben ik @1234 & 0<1;"};
const uint8_t txt_str_fr[]={"Salut Apple, c'est moi @1234 & 0<1;"};
const uint8_t txt_str_sp[]={"Hola Apple, soy yo @1234 & 0<1;"};




/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static void lv_demo_texter_components_init(void)
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


lv_obj_t * lv_demo_texter_title_create(lv_obj_t * parent, const char * text)
{
    lv_obj_t * label = lv_label_create(parent);
    lv_obj_add_style(label, &style_title, 0);
    lv_label_set_text_static(label, text);

    return label;
}


static void event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch(code) {
        case LV_EVENT_PRESSED:
        	toggle_text=1-toggle_text;
        	if(toggle_text){
        		lv_obj_set_style_text_font(ltr_label2, &lv_font_notosansjp_regular_20, 0);
        	    lv_label_set_text(ltr_label2, txt_str_jp);

        	}
        	else
        		{
        	    lv_obj_set_style_text_font(ltr_label2, &lv_font_notosansjp_regular_14, 0);
        	    lv_label_set_text(ltr_label2, txt_str_jp);
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




void lv_demo_texter(void)
{
#if 0
    lv_demo_texter_components_init();

    tv = lv_tabview_create(lv_screen_active());
    lv_tabview_set_tab_bar_size(tv, disp_size == DISP_LARGE ? 75 : 45);

    lv_obj_t * t1 = lv_tabview_add_tab(tv, "Japanese");
    lv_obj_t * t2 = lv_tabview_add_tab(tv, "Taiwanese");
    lv_obj_t * t3 = lv_tabview_add_tab(tv, "Arabic");

   // LV_FONT_DECLARE(lv_font_banda)
    LV_FONT_DECLARE(lv_font_lobster)

    lv_style_init(&style_japanese);
    lv_style_init(&style_taiwanese);

 //   lv_style_set_text_font(&style_japanese, &my_font);
    lv_style_set_text_font(&style_taiwanese, &lv_font_lobster);

    //lv_style_set_text_color(&style_japanese, lv_color_black());
   // LV_FONT_DECLARE(lv_font_banda);
   lv_demo_texter_create(t1, &style_taiwanese);
  //  lv_demo_texter_create(t2, &style_japanese);
    lv_demo_texter_create(t3, &style_text_muted);

#endif

    lv_example_label_ext();
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


/**
 * Show mixed LTR, RTL and Chinese label
 */
void lv_example_label_ext(void)
{
    lv_obj_t * ltr_label = lv_label_create(lv_screen_active());
    lv_label_set_text(ltr_label, txt_str_jp);
    lv_obj_set_style_text_font(ltr_label, &lv_font_notosansjp_regular_14, 0);
    lv_obj_set_width(ltr_label, 400);
    lv_obj_align(ltr_label, LV_ALIGN_TOP_LEFT, 5, 5);

    ltr_label2 = lv_label_create(lv_screen_active());
    lv_label_set_text(ltr_label2, txt_str_jp);
    lv_obj_set_style_text_font(ltr_label2, &lv_font_notosansjp_regular_16, 0);
    lv_obj_set_width(ltr_label2, 400);
    lv_obj_align(ltr_label2, LV_ALIGN_TOP_LEFT, 5, 50);

    lv_obj_t * rtl_label = lv_label_create(lv_screen_active());
    lv_label_set_text(rtl_label,txt_str_jp);
    lv_obj_set_style_base_dir(rtl_label, LV_BASE_DIR_RTL, 0);
    lv_obj_set_style_text_font(rtl_label, &lv_font_notosansjp_regular_14, 0);
    lv_obj_set_width(rtl_label, 400);
    lv_obj_align(rtl_label, LV_ALIGN_TOP_LEFT, 5, 110);

    lv_obj_t * cz_label = lv_label_create(lv_screen_active());
    lv_label_set_text(cz_label,txt_str_jp);
    lv_obj_set_style_text_font(cz_label, &lv_font_notosansjp_regular_16, 0);
    lv_obj_set_width(cz_label, 400);
    lv_obj_align(cz_label, LV_ALIGN_TOP_LEFT, 5,160);
}

void lv_demo_texter_create(lv_obj_t * parent, lv_style_t *style)
{

    lv_obj_t * panel1 = lv_obj_create(parent);
    lv_obj_set_height(panel1, LV_SIZE_CONTENT);

    lv_obj_t * text1 = lv_label_create(panel1);
    lv_label_set_text_static(text1, "TEXTER..");
   // lv_obj_add_style(text1, &style_text_muted, 0);
    lv_obj_add_style(text1, style, 0);


}

#endif

