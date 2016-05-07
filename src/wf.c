#include <pebble.h>
#include <jsmn.h>

static Window *window;
static TextLayer *s_text_layer;
static ScrollLayer *s_scroll_layer;

static void scroll_layer(char strng[]) {
  Layer *root_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(root_layer);
  GRect max_text_bounds = GRect(0, 0, bounds.size.w - 4, 2000);


  s_text_layer = text_layer_create(max_text_bounds);
  text_layer_set_text(s_text_layer, strng);
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));

  GSize max_size = text_layer_get_content_size(s_text_layer);
  text_layer_set_size(s_text_layer, max_size);

  s_scroll_layer = scroll_layer_create(bounds);
  scroll_layer_set_content_size(s_scroll_layer, max_size);

  scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(s_text_layer));
  layer_add_child(root_layer, scroll_layer_get_layer(s_scroll_layer));
  scroll_layer_set_click_config_onto_window(s_scroll_layer, window);
}

static char* parse_joke(char* json) {
  jsmn_parser parser;
  jsmntok_t tokens[128];
  jsmn_init(&parser);
  jsmn_parse(&parser, json, strlen(json), tokens, 128);

  jsmntok_t value = tokens[1];
  int length = key.end - key.start;
  char valueStr[length+1];
  memcpy(valueStr, &json[key.start], length);
  valueeeStr[]
}

static void window_load(Window *window) {
  scroll_layer(parse_joke("{'a':'b'}"));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
  scroll_layer_destroy(s_scroll_layer);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
      .load = window_load,
        .unload = window_unload,
        });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  /* APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window); */

  app_event_loop();
  deinit();
}
