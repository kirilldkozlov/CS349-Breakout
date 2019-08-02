#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
  #include "displayable.h"
#endif

class Header : public Displayable {
private:
  std::string s;
public:
  virtual void paint(XInfo &xinfo);
  // constructor
  Header(std::string s);
};
