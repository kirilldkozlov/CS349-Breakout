#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
  #include "displayable.h"
#endif

#include <string>
#include <sstream>

class FpsShow : public Displayable {
private:
  int fpsTrack;
public:
  virtual void paint(XInfo &xinfo);
  void clear(XInfo &xinfo);
  // constructor
  FpsShow(int fpsTrack);
};
