#ifndef CORE
#define CORE
	#include <cstdlib>
	#include <iostream>
	#include <unistd.h>
	#include <list>
	#include <sys/time.h>
#endif

#ifndef PADDLE_H
#define PADDLE_H
  #include "paddle.h"
#endif

#ifndef FPS_H
#define FPS_H
  #include "fpsShow.h"
#endif

#ifndef XLIB
#define XLIB
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
#endif

#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
  #include "displayable.h"
#endif

#ifndef TEXT_H
#define TEXT_H
  #include "text.h"
#endif

#ifndef SCORE_H
#define SCORE_H
  #include "score.h"
#endif

#ifndef BALL_H
#define BALL_H
  #include "ball.h"
#endif

#ifndef HEADER_H
#define HEADER_H
  #include "header.h"
#endif

#ifndef BRICK_H
#define BRICK_H
  #include "brick.h"
#endif

#include <cmath>
#include <stdlib.h>

using namespace std;

// Back up frame rate if not defined.
int FPS = 30;

// get current time
unsigned long now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void config(XInfo &xinfo) {
		XSizeHints screenHits;

		// General screen information
		int height = 800;
		int width = 1280;
		char const* screenName = "Breakout";
		int screennum;
		long background;
		long foreground;

		// Create window
		xinfo.display = XOpenDisplay("");
		if (xinfo.display == NULL) exit (-1);
		screennum = DefaultScreen(xinfo.display);
		foreground  = WhitePixel(xinfo.display, screennum);
		background = BlackPixel(xinfo.display, screennum);
		xinfo.window = XCreateSimpleWindow(xinfo.display, DefaultRootWindow(xinfo.display),
															10, 10, width, height, 2, foreground, background);

		// Screen hints to prevent resizing
		screenHits.flags = PAllHints;
		screenHits.min_height = height;
		screenHits.max_height = height;
		screenHits.max_width = width;
		screenHits.min_width = width;
		XSetWMNormalHints(xinfo.display, xinfo.window, &screenHits);
		XStoreName(xinfo.display, xinfo.window, screenName);

		// Set events to monitor and display xinfo.window
		XSelectInput(xinfo.display, xinfo.window, ButtonPressMask | KeyPressMask);
		XMapWindow(xinfo.display, xinfo.window);
		XFlush(xinfo.display);

		// Create gc for drawing
		xinfo.gc = XCreateGC(xinfo.display, xinfo.window, 0, 0);
}

void startScreen(XInfo &xinfo, list<Displayable*> &dList) {
		// Add Header
		dList.push_back(new Header("Welcome to Breakout!"));

		// Init the font
		XFontStruct* font_info;
		string font_name = "*8x13*";
		font_info = XLoadQueryFont(xinfo.display, font_name.c_str());

		XSetFont(xinfo.display, xinfo.gc, font_info->fid);

		int font_height = font_info->ascent + font_info->descent;
		int centerY = (800 - font_height) / 2;

		// Instructions
		string instructions = "Instructions: Use [a] and [d] to move your paddle left or right. Your objective is to keep the ball in play by bouncing it off your paddle.";
		string tips = "Tip: [q] will allow you to quit at any time.";
		string challenge = "Do you want a challenge? Press [i] to start the iNsAnE mOdE, where the ball speed will increase with each hit.";
		string start = "Press [s] to start!";
		string nameAndId = "Kirill Kozlov - k2kozlov - Sep. 28, 2018";

		// Add texts to list
		dList.push_back(new Text((1280 - XTextWidth(font_info, instructions.c_str(), instructions.length())) / 2, centerY - 60, instructions));
		dList.push_back(new Text((1280 - XTextWidth(font_info, tips.c_str(), tips.length())) / 2, centerY - 40, tips));
		dList.push_back(new Text((1280 - XTextWidth(font_info, start.c_str(), start.length())) / 2, centerY - 20, start));
		dList.push_back(new Text((1280 - XTextWidth(font_info, challenge.c_str(), challenge.length())) / 2, centerY + 20, challenge));
		dList.push_back(new Text((1280 - XTextWidth(font_info, nameAndId.c_str(), nameAndId.length())) / 2, centerY + 385, nameAndId));
}

void lostScreen(XInfo &xinfo, list<Displayable*> &dList) {
		// Init the font
		XFontStruct* font_info;
		string font_name = "*8x13*";
		font_info = XLoadQueryFont(xinfo.display, font_name.c_str());

		XSetFont(xinfo.display, xinfo.gc, font_info->fid);

		int font_height = font_info->ascent + font_info->descent;
		int centerY = (800 - font_height) / 2;

		// Instructions
		string instr = "Press [s] to play again and [q] to quit.";

		// Add text
		dList.push_back(new Header("Game Over"));
		dList.push_back(new Text((1280 - XTextWidth(font_info, instr.c_str(), instr.length())) / 2, centerY - 60, instr));
}

void wonScreen(XInfo &xinfo, list<Displayable*> &dList, int score) {
		// Init the font
		XFontStruct* font_info;
		string font_name = "*8x13*";
		font_info = XLoadQueryFont(xinfo.display, font_name.c_str());

		XSetFont(xinfo.display, xinfo.gc, font_info->fid);

		int font_height = font_info->ascent + font_info->descent;
		int centerY = (800 - font_height) / 2;

		std::string scoreVal = std::to_string(score);

		// Instructions
		string scoreAndMessage = "You won the game with a score of " + scoreVal + ".";
		string instr = "Press [s] to play again and [q] to quit.";

		// Add text
		dList.push_back(new Header("Congratulations!"));
		dList.push_back(new Text((1280 - XTextWidth(font_info, scoreAndMessage.c_str(), scoreAndMessage.length())) / 2, centerY - 60, scoreAndMessage));
		dList.push_back(new Text((1280 - XTextWidth(font_info, instr.c_str(), instr.length())) / 2, centerY - 40, instr));
}


void draw(XInfo &xinfo, list<Displayable*> &dList) {
	// Iterate through and draw all the Displayables
	list<Displayable*>::const_iterator begin = dList.begin();
	list<Displayable*>::const_iterator end = dList.end();

	while( begin != end ) {
		Displayable* d = *begin;
		if (d->active) {
			d->paint(xinfo);
		}
		begin++;
	}
}

void resetBricks(list<Brick*> &bricks) {
	// Reset the bricks
	list<Brick*>::const_iterator begin = bricks.begin();
	list<Brick*>::const_iterator end = bricks.end();

	while( begin != end ) {
		Brick* b = *begin;
		b->activate();
		begin++;
	}
}

// Draw and initialize all the bricks
void initBricks(XInfo &xinfo, list<Brick*> &bricks) {
	// Start conditions
	int oddRowStartX = 190;
	int evenRowStartX = 140;
	int yStart = 60;
	int blockYSpacer = 37 + 3;
	int blockXSpacer = 97 + 3;

	XColor brickColour;
	XColor borderColour;

	GC gc = XCreateGC(xinfo.display, xinfo.window, 0, 0);
	Colormap cmap = DefaultColormap(xinfo.display, DefaultScreen(xinfo.display));
	float coloratio = 65535.0 / 255.0;

	// Build aqua blocks - 9
	brickColour.red = (int) (36 * coloratio);
	brickColour.green = (int) (255 * coloratio);
	brickColour.blue = (int) (178 * coloratio);

	borderColour.red = (int) (81 * coloratio);
	borderColour.green = (int) (224 * coloratio);
	borderColour.blue = (int) (186 * coloratio);

	XAllocColor(xinfo.display, cmap, &brickColour);
	XAllocColor(xinfo.display, cmap, &borderColour);

	for (int x = 0; x < 9; x++) {
		bricks.push_back(new Brick(oddRowStartX + (blockXSpacer * x), yStart, brickColour.pixel, borderColour.pixel));
	}

	// Build blue blocks - 10
	brickColour.red = (int) (24 * coloratio);
	brickColour.green = (int) (137 * coloratio);
	brickColour.blue = (int) (214 * coloratio);

	borderColour.red = (int) (59 * coloratio);
	borderColour.green = (int) (137 * coloratio);
	borderColour.blue = (int) (192 * coloratio);

	XAllocColor(xinfo.display, cmap, &brickColour);
	XAllocColor(xinfo.display, cmap, &borderColour);

	for (int x = 0; x < 10; x++) {
		bricks.push_back(new Brick(evenRowStartX + (blockXSpacer * x), yStart + blockYSpacer, brickColour.pixel, borderColour.pixel));
	}

	// Build purple blocks - 9
	brickColour.red = (int) (138 * coloratio);
	brickColour.green = (int) (43 * coloratio);
	brickColour.blue = (int) (226 * coloratio);

	borderColour.red = (int) (162 * coloratio);
	borderColour.green = (int) (81 * coloratio);
	borderColour.blue = (int) (224 * coloratio);

	XAllocColor(xinfo.display, cmap, &brickColour);
	XAllocColor(xinfo.display, cmap, &borderColour);

	for (int x = 0; x < 9; x++) {
		bricks.push_back(new Brick(oddRowStartX + (blockXSpacer * x), yStart + (blockYSpacer * 2), brickColour.pixel, borderColour.pixel));
	}

	// Build orange blocks - 10
	brickColour.red = (int) (255 * coloratio);
	brickColour.green = (int) (126 * coloratio);
	brickColour.blue = (int) (46 * coloratio);

	borderColour.red = (int) (230 * coloratio);
	borderColour.green = (int) (142 * coloratio);
	borderColour.blue = (int) (87 * coloratio);

	XAllocColor(xinfo.display, cmap, &brickColour);
	XAllocColor(xinfo.display, cmap, &borderColour);

	for (int x = 0; x < 10; x++) {
		bricks.push_back(new Brick(evenRowStartX + (blockXSpacer * x), yStart + (blockYSpacer * 3), brickColour.pixel, borderColour.pixel));
	}

	// Build yellow blocks - 9
	brickColour.red = (int) (255 * coloratio);
	brickColour.green = (int) (203 * coloratio);
	brickColour.blue = (int) (61 * coloratio);

	borderColour.red = (int) (230 * coloratio);
	borderColour.green = (int) (196 * coloratio);
	borderColour.blue = (int) (101 * coloratio);

	XAllocColor(xinfo.display, cmap, &brickColour);
	XAllocColor(xinfo.display, cmap, &borderColour);

	for (int x = 0; x < 9; x++) {
		bricks.push_back(new Brick(oddRowStartX + (blockXSpacer * x), yStart + (blockYSpacer * 4), brickColour.pixel, borderColour.pixel));
	}

	// Build pink blocks - 10
	brickColour.red = (int) (255 * coloratio);
	brickColour.green = (int) (69 * coloratio);
	brickColour.blue = (int) (122 * coloratio);

	borderColour.red = (int) (230 * coloratio);
	borderColour.green = (int) (108 * coloratio);
	borderColour.blue = (int) (143 * coloratio);

	XAllocColor(xinfo.display, cmap, &brickColour);
	XAllocColor(xinfo.display, cmap, &borderColour);

	for (int x = 0; x < 10; x++) {
		bricks.push_back(new Brick(evenRowStartX + (blockXSpacer * x), yStart + (blockYSpacer * 5), brickColour.pixel, borderColour.pixel));
	}

	// Build red blocks - 9
	brickColour.red = (int) (217 * coloratio);
	brickColour.green = (int) (3 * coloratio);
	brickColour.blue = (int) (3 * coloratio);

	borderColour.red = (int) (176 * coloratio);
	borderColour.green = (int) (30 * coloratio);
	borderColour.blue = (int) (25 * coloratio);

	XAllocColor(xinfo.display, cmap, &brickColour);
	XAllocColor(xinfo.display, cmap, &borderColour);

	for (int x = 0; x < 9; x++) {
		bricks.push_back(new Brick(oddRowStartX + (blockXSpacer * x), yStart + (blockYSpacer * 6), brickColour.pixel, borderColour.pixel));
	}
}

void blackScreen(XInfo &xinfo) {
	XSetForeground(xinfo.display, xinfo.gc, BlackPixel(xinfo.display, DefaultScreen(xinfo.display)));
	XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc,
								 0, 0, 1280, 800);
	XSetForeground(xinfo.display, xinfo.gc, WhitePixel(xinfo.display, DefaultScreen(xinfo.display)));
}

int main( int argc, char *argv[] ) {
	// Configure the Window
	XInfo xinfo;
	config(xinfo);

	// list of Displayables
	list<Displayable*> dList;

	XWindowAttributes w;
	XGetWindowAttributes(xinfo.display, xinfo.window, &w);

	list<Brick*> bricks;
	initBricks(xinfo, bricks);

	// Ball position and size
	float ballPosX = 636.0;
	float ballPosY = 685.0;
	int ballSize = 13;

	// Speed
	XPoint ballDir;
	ballDir.x = 150;
	ballDir.y = 150;

	// Speed defaults
	int speedHyp = 212;
	double maxX = 35.0;
	double maxY = 35.0;

	// Get game speed from params
	if (argc == 3) {
		speedHyp = strtol(argv[2], NULL, 10) * 40;
		FPS = strtol(argv[1], NULL, 10);
	}

	// save time of last window paint
	unsigned long lastRepaint = 0;
	int gameStatus = 0;
	int score = 0;

	// event handle for current event
	XEvent event;

	// Pixmap for double buffer
	int depth = DefaultDepth(xinfo.display, DefaultScreen(xinfo.display));
	Pixmap	buffer = XCreatePixmap(xinfo.display, xinfo.window, w.width, w.height, depth);

	// Initialize all screen elements
	Ball* ball = new Ball(ballPosX, ballPosY, ballSize);
	Paddle* paddle = new Paddle();
	Score* scoreText = new Score(score);
	FpsShow* fpsShow = new FpsShow(FPS);

	// Game conditions
	bool firstStart = true;
	int examineDelay = 0;
	float radianConvert = 3.14159/180;
	bool insaneMode = false;

	// Event Loops
	while ( true ) {
		// process if we have any events
		if (XPending(xinfo.display) > 0) {
			XNextEvent( xinfo.display, &event );

			switch ( event.type ) {
				case KeyPress:
					KeySym key;
					char text[10];
					int i = XLookupString( (XKeyEvent*)&event, text, 10, &key, 0 );

					// move right
					if ( i == 1 && text[0] == 'd' && gameStatus == 2) {
						paddle->clear(xinfo);
						paddle->shiftRight();
					}

					// start
					if ( i == 1 && text[0] == 's' && gameStatus == 0) {
						gameStatus = 1;
						dList.clear();
					}

					// Start - insane mode
					if ( i == 1 && text[0] == 'i' && gameStatus == 0) {
						gameStatus = 1;
						insaneMode = true;
						dList.clear();
					}

					// start
					if ( i == 1 && text[0] == '1' && gameStatus == 1) {
						double xDegrees = 45.0;
						ballDir.x = -1 * cos(xDegrees*radianConvert) * speedHyp;
						ballDir.y = -1 * sin(xDegrees*radianConvert) * speedHyp;
						gameStatus = 2;
					}

					// start
					if ( i == 1 && text[0] == '2' && gameStatus == 1) {
						double xDegrees = 70.0;
						ballDir.x = -1 * cos(xDegrees*radianConvert) * speedHyp;
						ballDir.y = -1 * sin(xDegrees*radianConvert) * speedHyp;
						gameStatus = 2;
					}

					// start
					if ( i == 1 && text[0] == '3' && gameStatus == 1) {
						double xDegrees = 70.0;
						ballDir.x = cos(xDegrees*radianConvert) * speedHyp;
						ballDir.y = -1 * sin(xDegrees*radianConvert) * speedHyp;
						gameStatus = 2;
					}

					// start
					if ( i == 1 && text[0] == '4' && gameStatus == 1) {
						double xDegrees = 45.0;
						ballDir.x = cos(xDegrees*radianConvert) * speedHyp;
						ballDir.y = -1 * sin(xDegrees*radianConvert) * speedHyp;
						gameStatus = 2;
					}

					// restart
					if ( i == 1 && text[0] == 's' && (gameStatus == 3 || gameStatus == 4)) {
						gameStatus = 1;
						firstStart = true;
						ballPosX = 636.0;
						ballPosY = 680.0;
						score = 0;

						dList.clear();
						resetBricks(bricks);
						paddle->reset();
					}

					// move left
					if ( i == 1 && text[0] == 'a' && gameStatus == 2) {
						paddle->clear(xinfo);
						paddle->shiftLeft();
					}

					// quit game
					if ( i == 1 && text[0] == 'q' ) {
						XCloseDisplay(xinfo.display);
						exit(0);
					}
					break;
				}
		}

		unsigned long end = now();	// get current time in microsecond

		if (end - lastRepaint > 1000000 / FPS) {
			xinfo.pixmap = buffer;

			// Game start screen
			if (gameStatus == 0) {
        blackScreen(xinfo);
				startScreen(xinfo, dList);
				draw(xinfo, dList);
			}
			else if (gameStatus == 1) {
				blackScreen(xinfo);

				// Draw Lines
				XDrawLine(xinfo.display, xinfo.pixmap, xinfo.gc,  637, 680, 687, 630);
				XDrawLine(xinfo.display, xinfo.pixmap, xinfo.gc,  637, 680, 587, 630);
				XDrawLine(xinfo.display, xinfo.pixmap, xinfo.gc,  637, 680, 655.19, 630);
				XDrawLine(xinfo.display, xinfo.pixmap, xinfo.gc,  637, 680, 619.8, 630);

				// Draw numbers
				// Init the font
				XFontStruct* font_info;
				string font_name = "*8x13*";
				font_info = XLoadQueryFont(xinfo.display, font_name.c_str());

				string startInstr = "Press [1], [2], [3] or [4] to select your launch direction";
				dList.push_back(new Text((1280 - XTextWidth(font_info, startInstr.c_str(), startInstr.length())) / 2, 765, startInstr));
				dList.push_back(new Text(687, 625, "4"));
				dList.push_back(new Text(582, 625, "1"));
				dList.push_back(new Text(655.19, 625, "3"));
				dList.push_back(new Text(614.8, 625, "2"));

				list<Brick*>::const_iterator begin = bricks.begin();
				list<Brick*>::const_iterator end = bricks.end();

				while( begin != end ) {
					Brick* b = *begin;
					b->paint(xinfo);
					begin++;
				}

				draw(xinfo, dList);
				paddle->paint(xinfo);
				ball->updatePosition(ballPosX - ballSize/2, ballPosY - ballSize/2);
				ball->paint(xinfo);
			}
			// Gameplay stage
			else if (gameStatus == 2) {
				if (firstStart) {
					blackScreen(xinfo);
					firstStart = false;
				}
				ball->clear(xinfo);
				ball->updatePosition(ballPosX - ballSize/2, ballPosY - ballSize/2);

				// update ball position
				ballPosX = ballPosX + (float) ballDir.x/ FPS;
				ballPosY = ballPosY + (float) ballDir.y / FPS;

				if (examineDelay == 0) {
					if (ballPosY >= 600) {
						if (paddle->sideHit(ballPosX, ballPosY, ballSize)) {
							ballDir.x = -ballDir.x;
							examineDelay = FPS;
						}
						else if (paddle->longHit(ballPosX, ballPosY, ballSize)) {
							ballDir.y = -ballDir.y;
							examineDelay = FPS;
						}
					}
				}
				else {
					examineDelay--;
				}

				list<Brick*>::const_iterator begin = bricks.begin();
				list<Brick*>::const_iterator end = bricks.end();

				// Process bricks
				while( begin != end ) {
					Brick* b = *begin;
					if (b->active) {
						if (ballPosY < 360 && b->hitFromSide(ballPosX, ballPosY, ballSize)) {
							ballDir.x = -ballDir.x;
							ballPosX += (float)ballDir.x/FPS;
							if (insaneMode) {
								ballDir.x += min((float)ballDir.x * 0.1, maxX);
								ballDir.y += min((float)ballDir.y * 0.1, maxY);
							}
							b->deactivate();
							b->clear(xinfo);
							score += b->points;
							begin = bricks.begin();
							continue;
						}
						else if (ballPosY < 360 && b->hitFromAboveOrBelow(ballPosX, ballPosY, ballSize)) {
							ballDir.y = -ballDir.y;
							ballPosY += (float)ballDir.y/FPS;
							if (insaneMode) {
								ballDir.x += min((float)ballDir.x * 0.1, maxX);
								ballDir.y += min((float)ballDir.y * 0.1, maxY);
							}
							b->deactivate();
							b->clear(xinfo);
							score += b->points;
							begin = bricks.begin();
							continue;
						}
						else {
							b->paint(xinfo);
						}
					}
					begin++;
				}

				if (score == bricks.size() * 5) {
					gameStatus = 4;
				}

				scoreText->clear(xinfo);
				fpsShow->clear(xinfo);
				scoreText->updateScore(score);

				// bounce ball
				if (ballPosX + ballSize/2 > w.width ||
					ballPosX - ballSize/2 < 0)
					ballDir.x = -ballDir.x;
				if (ballPosY - ballSize/2 < 0)
					ballDir.y = -ballDir.y;
				if (ballPosY + ballSize/2 > w.height ) {
					gameStatus = 3;
				}

				if (insaneMode) {
					string insane = "iNsAne mOdE!";
					XSetForeground(xinfo.display, xinfo.gc, WhitePixel(xinfo.display, DefaultScreen(xinfo.display)));
					XDrawString( xinfo.display, xinfo.pixmap, xinfo.gc,
												25, 120, insane.c_str(), insane.length() );
				}

				ball->paint(xinfo);
				paddle->paint(xinfo);
				scoreText->paint(xinfo);
				fpsShow->paint(xinfo);
			}
			// Game end stage
			else if (gameStatus == 3) {
				dList.clear();
        blackScreen(xinfo);
				lostScreen(xinfo, dList);
				draw(xinfo, dList);
			}
			else if (gameStatus == 4) {
				dList.clear();
				blackScreen(xinfo);
				wonScreen(xinfo, dList, score);
				draw(xinfo, dList);
			}

			XCopyArea(xinfo.display, xinfo.pixmap, xinfo.window, xinfo.gc,
								0, 0, w.width, w.height,  // region of pixmap to copy
								0, 0); // position to put top left corner of pixmap in window

			XFlush( xinfo.display );
			lastRepaint = now(); // remember when the paint happened
		}

		// IMPORTANT: sleep for a bit to let other processes work
		if (XPending(xinfo.display) == 0) {
			usleep(1000000 / FPS - (end - lastRepaint));
		}
	}
	XCloseDisplay(xinfo.display);
}
