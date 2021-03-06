// Filename: ffmpegVirtualFile.h
// Created by: jyelon (01Aug2007)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#ifndef FFMPEGVIRTUALFILE_H
#define FFMPEGVIRTUALFILE_H

#include "pandabase.h"
#include "config_movies.h"
#include "filename.h"
#include "subfileInfo.h"

#include <stdarg.h>
extern "C" {
  #include "libavformat/avio.h"
}

struct URLContext;
struct AVFormatContext;

////////////////////////////////////////////////////////////////////
//       Class : FfmpegVirtualFile
// Description : Enables ffmpeg to access panda's VFS.  Create an
//               instance of the FfmpegVirtualFile for each ffmpeg
//               stream you wish to open.
////////////////////////////////////////////////////////////////////
class EXPCL_FFMPEG FfmpegVirtualFile {
public:
  FfmpegVirtualFile();
  ~FfmpegVirtualFile();
private:
  FfmpegVirtualFile(const FfmpegVirtualFile &copy);
  void operator = (const FfmpegVirtualFile &copy);

public:
  bool open_vfs(const Filename &filename);
  bool open_subfile(const SubfileInfo &info);
  void close();

  INLINE bool is_open() const;
  INLINE AVFormatContext *get_format_context() const;

  static void register_protocol();

private:
  // These are callbacks passed to ffmpeg and cannot change signature.
  static int read_packet(void *opaque, uint8_t *buf, int buf_size);
  static int64_t seek(void *opaque, int64_t offset, int whence);

  static void log_callback(void *ptr, int level, const char *fmt, va_list v1);

private:
  AVIOContext *_io_context;
  AVFormatContext *_format_context;
  streampos _start;
  streamsize _size;
  istream *_in;
  pifstream _file_in;
  bool _owns_in;
  int _buffer_size;
};

#include "ffmpegVirtualFile.I"

#endif // FFMPEGVIRTUALFILE_H
