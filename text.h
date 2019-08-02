#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
  #include "displayable.h"
#endif

class Text : public Displayable {
private:
  int x;
  int y;
  std::string s;
public:
  virtual void paint(XInfo &xinfo);
  // constructor
  Text(int x, int y, std::string s);
};
