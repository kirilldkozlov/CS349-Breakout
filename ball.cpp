#ifndef BALL_H
#define BALL_H
  #include "ball.h"
#endif

void Ball::clear(XInfo &xinfo) {
  XSetForeground(xinfo.display, xinfo.gc, BlackPixel(xinfo.display, DefaultScreen(xinfo.display)));

  // draw ball from centre
  XFillArc(xinfo.display, xinfo.pixmap, xinfo.gc,
    this->x,
    this->y,
    this->ballSize, this->ballSize,
    0, 360*64);
}

void Ball::paint(XInfo &xinfo) {
  XColor ballGray;

  GC gc = XCreateGC(xinfo.display, xinfo.window, 0, 0);
  Colormap cmap = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
  float coloratio = 65535.0 / 255.0;

  ballGray.red = (int) (119 * coloratio);
  ballGray.green = (int) (136 * coloratio);
  ballGray.blue = (int) (152 * coloratio);

  XAllocColor(xinfo.display, cmap, &ballGray);
  XSetForeground(xinfo.display, gc, ballGray.pixel);

  // draw ball from centre
  XFillArc(xinfo.display, xinfo.pixmap, gc,
    this->x,
    this->y,
    this->ballSize, this->ballSize,
    0, 360*64);
}

void Ball::updatePosition(int x, int y) {
  this->x = x;
  this->y = y;
}

// Constructor
Ball::Ball(int x, int y, int ballSize): x(x), y(y), ballSize(ballSize)  {}
