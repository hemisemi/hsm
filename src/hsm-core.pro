QT       -= core gui

TARGET = Swapi
TEMPLATE = lib

INCLUDEPATH += /usr/include/freetype2

DEFINES += HEMISEMI_LIBRARY

SOURCES += private/file_private.cpp \
    private/file_default.cpp \
    uri.cpp \
    sizef.cpp \
    size.cpp \
    rectf.cpp \
    rect.cpp \
    rawfont_ft.cpp \
    rawfont_fnt.cpp \
    rawfont.cpp \
    pointf.cpp \
    point.cpp \
    pen.cpp \
    painter.cpp \
    paintengine.cpp \
    paintdevice.cpp \
    iodevice.cpp \
    graphiccontext.cpp \
    fontmetrics.cpp \
    fontlibrary.cpp \
    font.cpp \
    filesystementry.cpp \
    file.cpp \
    datastream.cpp \
    color.cpp \
    brush.cpp \
    bitmap.cpp \
    bitmap_paintengine.cpp \
    matrix.cpp \
    vector.cpp \
    algorithm.cpp \
    bytearray.cpp \
    cairo_paintengine.cpp

HEADERS += uri.h \
    types.h \
    sizef.h \
    size.h \
    rectf.h \
    rect.h \
    rawfont_ft.h \
    rawfont_fnt.h \
    rawfont.h \
    pointf.h \
    point.h \
    pen.h \
    painter.h \
    paintengine.h \
    paintdevice.h \
    iodevice.h \
    graphiccontext.h \
    fontmetrics.h \
    fontlibrary.h \
    font.h \
    filesystementry.h \
    file.h \
    enum.h \
    datastream.h \
    color.h \
    bytearray.h \
    brush.h \
    bitmap.h \
    private/file_private.h \
    private/file_default.h \
    private/bitmap_png.h \
    private/bitmap_jpeg.h \
    private/bitmap_bmp.h \
    vector.h \
    algorithm.h \
    matrix4x4.h \
    matrix3x3.h \
    bitmap_paintengine.h \
    cairo_paintengine.h \
    cairo_compatible_paintdevice.h
