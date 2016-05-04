#include <pebble.h>

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

static void window_load(Window *window) {
  scroll_layer("Lorem ipsum dolor sit amet, consectetur adipiscing \
  elit. Phasellus lectus ex, faucibus ac rhoncus eget, scelerisque \
  quis felis. Donec est nisl, tincidunt eget arcu nec, pretium \
  vulputate mi. Pellentesque gravida massa eros. Praesent pulvinar dui \
  neque, ac dapibus lacus tempor vel. Vivamus posuere sem quam, nec \
  suscipit lectus luctus vel. Sed porta ligula ac erat volutpat \
  placerat. Praesent ut cursus risus, interdum congue ex. Donec eu \
  interdum mi. Phasellus vel magna finibus, mattis ipsum vitae, \
  aliquam libero. Curabitur felis dolor, commodo et arcu sed, congue \
  elementum elit. Vivamus dictum augue et vulputate efficitur. Duis in \
  massa quis metus pellentesque aliquam. Nunc viverra odio a hendrerit \
  bibendum. Pellentesque tincidunt facilisis justo eget \
  mollis. Phasellus ex ligula, tincidunt in lacus at, malesuada cursus \
  sapien. Sed enim est, consequat porttitor tellus ac, sodales rutrum \
  velit. Ut nibh nibh, eleifend nec efficitur sed, convallis quis \
  dui. Mauris placerat ligula a erat pellentesque consequat. Donec \
  egestas commodo purus vitae auctor. Sed aliquet lorem tortor, sit \
  amet gravida leo tempus nec. Phasellus sagittis, leo ac cursus \
  hendrerit, tellus felis mattis felis, sed sollicitudin mi lacus eget \
  orci. Sed commodo elementum justo, et commodo turpis porta \
  a. Maecenas non consequat neque, non facilisis nulla. Vestibulum \
  iaculis tristique aliquam. Vivamus scelerisque mattis \
  consectetur. Nullam mollis lorem finibus turpis porta tempus. Duis \
  in lacinia justo. Curabitur semper dui quis ipsum tempor \
  tincidunt. Aenean pretium massa et venenatis convallis. Nam \
  condimentum blandit nunc at eleifend. Sed eu dignissim turpis, eu \
  lobortis metus. Aenean metus diam, consequat nec diam in, vehicula \
  iaculis diam. Donec libero turpis, sollicitudin in commodo id, \
  maximus eget elit. Duis tristique libero eget dictum dictum. Cras \
  hendrerit nibh ut aliquet vulputate. Donec sem tortor, mattis nec \
  venenatis non, placerat eget enim. Praesent porttitor finibus \
  tortor, et dapibus quam scelerisque ut. Sed aliquet velit eu lacus \
  venenatis, non scelerisque sem dapibus. Praesent congue tempor \
  vulputate. Proin ullamcorper placerat turpis, non venenatis eros \
  laoreet semper. Aenean cursus libero et turpis dictum, a accumsan \
  turpis rutrum. In eget pellentesque dolor. In hac habitasse platea \
  dictumst. Phasellus blandit dolor et ligula fermentum auctor. Nulla \
  sem nunc, vulputate sed nisl euismod, facilisis laoreet \
  sapien. Proin fermentum tempus molestie. Morbi volutpat orci eu \
  bibendum placerat. Nam sit amet laoreet sem. Etiam at elit in nisl \
  congue gravida. Etiam consectetur ultrices dui, et dignissim libero \
  bibendum nec. Nunc lorem eros, molestie at ultricies nec, \
  sollicitudin nec odio. Pellentesque posuere maximus turpis sit amet \
  tincidunt. Vivamus scelerisque et magna id feugiat. Aenean ut \
  fermentum urna. Fusce convallis ex sit amet enim scelerisque \
  interdum. Maecenas sem ex, suscipit sit amet arcu at, pharetra \
  rutrum enim. Curabitur vitae ex arcu. Etiam eget velit condimentum, \
  pharetra nunc eget, mollis leo. Aliquam arcu mauris, fringilla sit \
  amet magna at, pretium lacinia quam. Etiam commodo rhoncus \
  tempor. Fusce porta fringilla metus at aliquam. Vivamus varius \
  bibendum sem at suscipit. Aliquam non commodo metus. Morbi vulputate \
  lacus sed pharetra tempus. Vivamus eget sagittis augue, at mollis \
  sapien. Class aptent taciti sociosqu ad litora torquent per conubia \
  nostra, per inceptos himenaeos. Mauris vehicula libero eu tellus \
  maximus elementum.");
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
