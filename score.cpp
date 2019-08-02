#ifndef SCORE_H
#define SCORE_H
  #include "score.h"
#endif

void Score::paint(XInfo &xinfo) {
  std::string scoreVal = std::to_string(this->scoreTrack);
  std::string scoreText = "Score: " + scoreVal;

  XSetForeground(xinfo.display, xinfo.gc, WhitePixel(xinfo.display, DefaultScreen(xinfo.display)));
  XDrawString( xinfo.display, xinfo.pixmap, xinfo.gc,
                25, 100, scoreText.c_str(), scoreText.length() );
}

void Score::clear(XInfo &xinfo) {
  XSetForeground(xinfo.display, xinfo.gc, BlackPixel(xinfo.display, DefaultScreen(xinfo.display)));
  XFillRectangle( xinfo.display, xinfo.pixmap, xinfo.gc,
                24, 80, 97, 22 );
}

void Score::updateScore(int score) {
  this->scoreTrack = score;
}

// constructor
Score::Score(int scoreTrack): scoreTrack(scoreTrack)  {}
