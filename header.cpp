#ifndef HEADER_H
#define HEADER_H
  #include "header.h"
#endif

void Header::paint(XInfo &xinfo) {
  XFontStruct* font_info;
  XColor purple;

  GC gc = XCreateGC(xinfo.display, xinfo.window, 0, 0);
  Colormap cmap = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
  float coloratio = 65535.0 / 255.0;

  purple.red = (int) (138 * coloratio);
  purple.green = (int) (43 * coloratio);
  purple.blue = (int) (226 * coloratio);

  XAllocColor(xinfo.display, cmap, &purple);
  XSetForeground(xinfo.display, gc, purple.pixel);

  // Init the font
  std::string font_name = "*12x24*";
  font_info = XLoadQueryFont(xinfo.display, font_name.c_str());

  // Position text
  int string_width = XTextWidth(font_info, this->s.c_str(), this->s.length());
  int font_height = font_info->ascent + font_info->descent;
  int x = (1280 - string_width) / 2;
  int y = (800 - font_height) / 2 - 75;

  // Print text
  XSetFont(xinfo.display, gc, font_info->fid);
  XDrawString( xinfo.display, xinfo.pixmap, gc,
                x, y, this->s.c_str(), this->s.length() );
}

// Constructor
Header::Header(std::string s): s(s)  {}
