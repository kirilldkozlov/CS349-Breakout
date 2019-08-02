all:
	@echo "Compiling..."
	g++ -std=c++14 -o breakout breakout.cpp fpsShow.cpp brick.cpp ball.cpp paddle.cpp text.cpp header.cpp score.cpp -L/opt/X11/lib -lX11 -lstdc++

run: all
	@echo "Running..."
	./breakout 30 6

clean:
	-rm *o
