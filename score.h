#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
  #include "displayable.h"
#endif

#include <string>
#include <sstream>

class Score : public Displayable {
private:
  int scoreTrack;
public:
  virtual void paint(XInfo &xinfo);
  void clear(XInfo &xinfo);
  void updateScore(int scoreTrack);
  // constructor
  Score(int scoreTrack);
};
