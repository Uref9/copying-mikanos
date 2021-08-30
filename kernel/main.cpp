/**
 * @file main.cpp
 *
 * カーネル本体のプログラムを書いたファイル．
 *
 */

#include <cstdint>
#include <cstddef>
#include <cstdio>

// #@@range_begin(includes)
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "console.hpp"
// #@@range_end(includes)

// #@@range_begin(placement_new)
void* operator new(size_t size, void* buf) {
  return buf;
}

void operator delete(void* obj) noexcept {
}
// #@@range_end(placement_new)

// #@@range_begin(buf)
char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

char console_buf[sizeof(Console)];
Console* console;
// #@@range_end(buf)

// #@@range_begin(printk)
int printk(const char* format, ...) {
  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsprintf(s, format, ap);
  va_end(ap);

  console->PutString(s);
  return result;
}
// #@@range_end(printk)

// #@@range_begin(call_write_pixel)
extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
  switch (frame_buffer_config.pixel_format) {
    case kPixelRGBResv8BitPerColor:
      pixel_writer = new(pixel_writer_buf)
        RGBResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
    case kPixelBGRResv8BitPerColor:
      pixel_writer = new(pixel_writer_buf)
        BGRResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
  }

  for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
    for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
      pixel_writer->Write(x, y, {255, 255, 255});
    }
  }
  
  // #@@range_begin(new_console)
  console = new(console_buf) Console{*pixel_writer, {0, 0, 0}, {255, 255, 255}};
  // #@@range_end(new_console)

  // #@@range_begin(use_printk)
  for (int i = 0; i < 27; ++i) {
    printk("printk: %d\n", i);
  }
  // #@@range_end(use_printk)
  while (1) __asm__("hlt");
}
