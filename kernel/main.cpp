/**
 * @file main.cpp
 *
 * カーネル本体のプログラムを書いたファイル．
 *
 */

#include <cstdint>
#include <cstddef>

// #@@range_begin(includes)
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "font.hpp"
// #@@range_end(includes)

// #@@range_begin(placement_new)
void* operator new(size_t size, void* buf) {
  return buf;
}

void operator delete(void* obj) noexcept {
}
// #@@range_end(placement_new)

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

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
  for (int x = 0; x < 200; ++x) {
    for (int y = 0; y < 100; ++y) {
      pixel_writer->Write(x, y, {0, 255, 0});
    }
  }

  // #@@range_begin(write_fonts)
    WriteAscii(*pixel_writer, 50, 50, 'm', {0, 0, 0});
    WriteAscii(*pixel_writer, 58, 50, 'i', {0, 0, 0});
    WriteAscii(*pixel_writer, 66, 50, 'k', {0, 0, 0});
    WriteAscii(*pixel_writer, 74, 50, 'a', {0, 0, 0});
    WriteAscii(*pixel_writer, 82, 50, 'n', {0, 0, 0});
    WriteAscii(*pixel_writer, 90, 50, 'O', {0, 0, 0});
    WriteAscii(*pixel_writer, 98, 50, 'S', {0, 0, 0});
    WriteAscii(*pixel_writer, 106, 50, 'b', {0, 0, 0});
    WriteAscii(*pixel_writer, 114, 50, 'y', {0, 0, 0});
    WriteAscii(*pixel_writer, 122, 50, 'Y', {0, 0, 0});
    WriteAscii(*pixel_writer, 130, 50, 'u', {0, 0, 0});
    WriteAscii(*pixel_writer, 138, 50, 'u', {0, 0, 0});
  // #@@range_end(write_fonts)

  while (1) __asm__("hlt");
}
