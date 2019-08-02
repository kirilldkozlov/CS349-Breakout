#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
  #include "displayable.h"
#endif

#include <algorithm>

class Paddle : public Displayable {
  int x = 590;
  int y = 700;
  const int height = 13;
  const int width = 95;
  const int shiftWeight = 18;
public:
  bool longHit(float ballX, float ballY, int ballSize);
  bool sideHit(float ballX, float ballY, int ballSize);
  void shiftLeft();
  void reset();
  void shiftRight();
  void clear(XInfo &xinfo);
  virtual void paint(XInfo &xinfo);
  // constructor
  Paddle();
};
