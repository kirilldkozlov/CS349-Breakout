#ifndef BRICK_H
#define BRICK_H
  #include "brick.h"
#endif

bool longHit(float x, float y, int height, int width, float ballX, float ballY, int ballSize) {
  float ballBottom = ballY;
  float ballTop = ballY - ballSize;
  float middleX = ballX - (float)ballSize/2;

  if (y - ballSize/2 <= ballBottom && y - ballSize/2 >= ballTop ||
      y + height <= ballBottom && y + height >= ballTop) {
    if (middleX > x && middleX < x + width) {
      return true;
    }
  }

  return false;
}

bool sideHit(float x, float y, int height, int width, float ballX, float ballY, int ballSize) {
  float ballRight = ballX;
  float ballLeft = ballX - ballSize;
  float middleY = ballY - (float)ballSize/2;

  if (x >= ballLeft && x <= ballRight ||
      x + width >= ballLeft && x + width <= ballLeft) {
    if (middleY > y && middleY < y + height) {
      return true;
    }
  }

  return false;
}

void Brick::paint(XInfo &xinfo) {
  GC gc = XCreateGC(xinfo.display, xinfo.window, 0, 0);

  // Draw brick
  XSetForeground(xinfo.display, gc, colourPixel);
  XFillRectangle( xinfo.display, xinfo.pixmap, gc,
                this->x, this->y, this->width, this->height  );

  // Draw border
  XSetForeground(xinfo.display, gc, borderPixel);
  XDrawRectangle( xinfo.display, xinfo.pixmap, gc,
                this->x, this->y, this->width, this->height  );
}

void Brick::clear(XInfo &xinfo) {
  // Erase brick
  XSetForeground(xinfo.display, xinfo.gc, BlackPixel(xinfo.display, DefaultScreen(xinfo.display)));
  XFillRectangle( xinfo.display, xinfo.pixmap, xinfo.gc,
                this->x, this->y, this->width + 2, this->height + 2  );
}

bool Brick::hitFromSide(int ballPosX, int ballPosY, int ballSize) {
  return sideHit(x, y, height, width, ballPosX, ballPosY, ballSize);
}
bool Brick::hitFromAboveOrBelow(int ballPosX, int ballPosY, int ballSize) {
  return longHit(x, y, height, width, ballPosX, ballPosY, ballSize);
}

void Brick::deactivate() {
  this->active = false;
}
void Brick::activate() {
  this->active = true;
}
// constructor
Brick::Brick(int x, int y, unsigned long colourPixel, unsigned long borderPixel) : x(x), y(y), colourPixel(colourPixel), borderPixel(borderPixel) {}
