#ifndef TEXT_H
#define TEXT_H
  #include "text.h"
#endif

void Text::paint(XInfo &xinfo) {
  XDrawString( xinfo.display, xinfo.pixmap, xinfo.gc,
                this->x, this->y, this->s.c_str(), this->s.length() );
}
// constructor
Text::Text(int x, int y, std::string s): x(x), y(y), s(s)  {}
