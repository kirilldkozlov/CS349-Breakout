#ifndef FPS_H
#define FPS_H
  #include "fpsShow.h"
#endif

void FpsShow::paint(XInfo &xinfo) {
  std::string fps = std::to_string(this->fpsTrack);
  std::string scoreText = "FPS: " + fps;

  XSetForeground(xinfo.display, xinfo.gc, WhitePixel(xinfo.display, DefaultScreen(xinfo.display)));
  XDrawString( xinfo.display, xinfo.pixmap, xinfo.gc,
                25, 80, scoreText.c_str(), scoreText.length() );
}

void FpsShow::clear(XInfo &xinfo) {
  XSetForeground(xinfo.display, xinfo.gc, BlackPixel(xinfo.display, DefaultScreen(xinfo.display)));
  XFillRectangle( xinfo.display, xinfo.pixmap, xinfo.gc,
                24, 60, 97, 22 );
}

// constructor
FpsShow::FpsShow(int fpsTrack): fpsTrack(fpsTrack)  {}
