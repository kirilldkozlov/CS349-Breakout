#ifndef PADDLE_H
#define PADDLE_H
  #include "paddle.h"
#endif

bool Paddle::longHit(float ballX, float ballY, int ballSize) {
  float ballBottom = ballY;
  float ballTop = ballY - ballSize;
  float middleX = ballX - (float)ballSize/2;

  if (this->y - ballSize/2 <= ballBottom && this->y - ballSize/2 >= ballTop ||
      this->y + this->height <= ballBottom && this->y + this->height >= ballTop) {
    if (middleX > this->x && middleX < this->x + this->width) {
      return true;
    }
  }

  return false;
}

bool Paddle::sideHit(float ballX, float ballY, int ballSize) {
  float ballRight = ballX;
  float ballLeft = ballX - ballSize;
  float middleY = ballY - (float)ballSize/2;

  if (this->x >= ballLeft && this->x <= ballRight ||
      this->x + this->width >= ballLeft && this->x + this->width <= ballLeft) {
    if (middleY > this->y && middleY < this->y + this->height) {
      return true;
    }
  }

  return false;
}

void Paddle::clear(XInfo &xinfo) {
  XSetForeground(xinfo.display, xinfo.gc, BlackPixel(xinfo.display, DefaultScreen(xinfo.display)));

  XFillRectangle( xinfo.display, xinfo.pixmap, xinfo.gc,
                this->x, this->y, this->width + 5, this->height + 5 );
}

void Paddle::paint(XInfo &xinfo) {
  XColor brown;

  GC gc = XCreateGC(xinfo.display, xinfo.window, 0, 0);
  Colormap cmap = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
  float coloratio = 65535.0 / 255.0;

  brown.red = (int) (120 * coloratio);
  brown.green = (int) (43 * coloratio);
  brown.blue = (int) (24 * coloratio);

  XAllocColor(xinfo.display, cmap, &brown);
  XSetForeground(xinfo.display, gc, brown.pixel);

  XFillRectangle( xinfo.display, xinfo.pixmap, gc,
                this->x, this->y, this->width, this->height  );

  brown.red = (int) (145 * coloratio);
  brown.green = (int) (75 * coloratio);
  brown.blue = (int) (58 * coloratio);

  XAllocColor(xinfo.display, cmap, &brown);
  XSetForeground(xinfo.display, gc, brown.pixel);

  XDrawRectangle( xinfo.display, xinfo.pixmap, gc,
                this->x, this->y, this->width, this->height  );
}

void Paddle::shiftLeft() {
    x = std::max(0, x - this->shiftWeight);
}

void Paddle::shiftRight() {
  x = std::min(1280 - this->width, x + this->shiftWeight);
}

void Paddle::reset() {
  x = 590;
  y = 700;
}

// constructor
Paddle::Paddle()  {}
