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

const PixelColor kDesktopBGColor{45, 118, 237};
const PixelColor kDesktopFGColor{255, 255, 255};

// #@@range_begin(mouse_cursor_shape)
const int kMouseCursorWidth = 15;
const int kMouseCursorHeight = 24;
const char mouse_cursor_shape[kMouseCursorHeight][kMouseCursorWidth + 1] = {
  "@              ",
  "@@             ",
  "@.@            ",
  "@..@           ",
  "@...@          ",
  "@....@         ",
  "@.....@        ",
  "@......@       ",
  "@.......@      ",
  "@........@     ",
  "@.........@    ",
  "@..........@   ",
  "@...........@  ",
  "@............@ ",
  "@......@@@@@@@@",
  "@......@       ",
  "@....@@.@      ",
  "@...@ @.@      ",
  "@..@   @.@     ",
  "@.@    @.@     ",
  "@@      @.@    ",
  "@       @.@    ",
  "         @.@   ",
  "         @@@   ",
};
// #@@range_end(mouse_cursor_shape)

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

  const int kFrameWidth = frame_buffer_config.horizontal_resolution;
  const int kFrameHeight = frame_buffer_config.vertical_resolution;

  // #@@range_begin(draw_desktop)
  FillRectangle(*pixel_writer,
                {0, 0},
                {kFrameWidth, kFrameHeight},
                kDesktopBGColor);
  FillRectangle(*pixel_writer,
                {0 + 20, kFrameHeight - 60},
                {kFrameWidth - 20 * 2, 60 - 5},
                {61, 68, 77});
  // DrawRectangle(*pixel_writer,
  //               {10, kFrameHeight - 40},
  //               {30, 30},
  //               {160, 160, 160});
  
  console = new(console_buf) Console{
    *pixel_writer, kDesktopFGColor, kDesktopBGColor
  };
  printk("Welcome to MikanOS! by yuu\n");
  // #@@range_end(draw_desktop)

  // #@@range_begin(draw_mouse_cursor)
  for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
    for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
      if (mouse_cursor_shape[dy][dx] == '@') {
        pixel_writer->Write(200 + dx, 100 + dy, {0, 0, 0});
      } else if (mouse_cursor_shape[dy][dx] == '.') {
        pixel_writer->Write(200 + dx, 100 + dy, {255, 255, 255});
      }
    }
  }
  // #@@range_end(draw_mouse_cursor)

  while (true) __asm__("hlt");
}
