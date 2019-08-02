#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
  #include "displayable.h"
#endif

class Brick {
private:
  int x;
  int y;
  unsigned long colourPixel;
  unsigned long borderPixel;
  int width = 97;
  int height = 37;
public:
  int points = 5;
  bool active = true;
  void paint(XInfo &xinfo);
  bool hitFromSide(int ballPosX, int ballPosY, int ballSize);
  bool hitFromAboveOrBelow(int ballPosX, int ballPosY, int ballSize);
  void clear(XInfo &xinfo);
  void deactivate();
  void activate();
  // constructor
  Brick(int x, int y, unsigned long colourPixel, unsigned long borderPixel);
};
