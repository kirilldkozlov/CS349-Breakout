#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
  #include "displayable.h"
#endif

class Ball : public Displayable {
private:
  int x;
  int y;
  int ballSize;
public:
  void clear(XInfo &xinfo);
  virtual void paint(XInfo &xinfo);
  void updatePosition(int x, int y);
  // constructor
  Ball(int x, int y, int ballSize);
};
