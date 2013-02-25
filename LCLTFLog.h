//
//
// LCLTFLog.h
//
//
// Copyright (c) 2013 Alaksiej Nieścieraŭ <alaksiej@screencustoms.com>
// Copyright (c) 2008-2012 Arne Harren <ah@0xc0.de>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


//
// LCLTFLog
//
// This file provides a simple LibComponentLogging logger implementation which
// redirects logging to TestFlight log.
//
// The logger uses the following format
//
//   <TFLog Prefix> <Level> <Component> <Message>
//
// where <TFLog Prefix> is
//
//   <Date> <Time> <Application>[<PID>:<TID>]
//
// Examples:
//
//   2009-02-01 12:38:32.796 Example[4964:10b] D [c1] M1
//   2009-02-01 12:38:32.798 Example[4964:10b] D [c2] M2
//   2009-02-01 12:38:32.799 Example[4964:10b] D [c3] M3
//


//
// Integration with LibComponentLogging Core.
//


// ARC/non-ARC autorelease pool
#define _lcl_logger_autoreleasepool_arc 0
#if defined(__has_feature)
#   if __has_feature(objc_arc)
#   undef  _lcl_logger_autoreleasepool_arc
#   define _lcl_logger_autoreleasepool_arc 1
#   endif
#endif
#if _lcl_logger_autoreleasepool_arc
#   define _lcl_logger_autoreleasepool_begin                                   \
        @autoreleasepool {
#   define _lcl_logger_autoreleasepool_end                                     \
        }
#else
#   define _lcl_logger_autoreleasepool_begin                                   \
        NSAutoreleasePool *_lcl_logger_autoreleasepool = [[NSAutoreleasePool alloc] init];
#   define _lcl_logger_autoreleasepool_end                                     \
        [_lcl_logger_autoreleasepool release];
#endif

#ifndef _LCL_NO_IGNORE_WARNINGS
#   ifdef __clang__
    // Ignore some warnings about variadic macros when using '-Weverything'.
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-pragmas"
#   pragma clang diagnostic ignored "-Wvariadic-macros"
#   pragma clang diagnostic ignored "-Wpedantic"
#   endif
#endif

// A very simple logger, which redirects to TFLog().
#define _lcl_logger(_component, _level, _format, ...) {                        \
    _lcl_logger_autoreleasepool_begin                                          \
    TFLog(@"%s [%s] " _format,                                                 \
          _lcl_level_header_1[_level],                                         \
          _lcl_component_header[_component],                                   \
          ## __VA_ARGS__);                                                     \
    _lcl_logger_autoreleasepool_end                                            \
}

#ifndef _LCL_NO_IGNORE_WARNINGS
#   ifdef __clang__
#   pragma clang diagnostic pop
#   endif
#endif
