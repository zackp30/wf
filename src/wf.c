#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

static TextLayer *s_text_layer;
static ScrollLayer *s_scroll_layer;

static void scroll_layer(char* strng) {
  Layer *root_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_get_root_layer(window));

  s_text_layer = text_layer_create(bounds);
  text_layer_set_text(s_text_layer, strng);
  text_layer_set_size(s_text_layer, GSize(10, 10));
  Layer *f_text_layer = text_layer_get_layer(s_text_layer);

  s_scroll_layer = scroll_layer_create(bounds);
  Layer *f_scroll_layer = scroll_layer_get_layer(s_scroll_layer);

  layer_add_child(root_layer, f_scroll_layer);
  layer_add_child(f_scroll_layer, f_text_layer);

}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
}


static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void window_load(Window *window) {
  scroll_layer("wow ndsoajidjasoidjaos doasnidasonid aosnd asnodn spoia dnoiasndoipsn oidnsoipan");
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
  scroll_layer_destroy(s_scroll_layer);
}

static void init(void) {
  window = window_create();
  scroll_layer_set_click_config_onto_window(s_scroll_layer, window);
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

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
