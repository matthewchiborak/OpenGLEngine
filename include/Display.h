#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>
#include <GL/glew.h>

#include <string>
#include <iostream>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Update();
	bool isClosed();
	void clear(float r, float g, float b, float a);
	bool checkKey(int key);
	bool checkKeyDown(int key);
	bool checkKeyUp(int key);

	bool checkMouse(int key);
	bool checkMouseDown(int key);
	bool checkMouseUp(int key);

	int getMouseDifX();
	int getMouseDifY();

	float getScreenCenterX();
	float getScreenCenterY();

	virtual ~Display();
private:
	Display(const Display& other) {}
	//Display& operator=(const Display& other){}
	void operator=(const Display& other) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;

	const int NUM_KEYS = 322;

	bool KEYS[322];  // 322 is the number of SDLK_DOWN events
	bool KEYDOWN[322]; //Keeps track of if the key press has been handled
	bool KEYUP[322]; //Keeps track of if the key release has been handled

	int mouseX;
	int mouseY;
	int mousePrevX;
	int mousePrevY;

	bool MOUSE_CLICK[2];
	bool MOUSE_CLICK_DOWN[2];
	bool MOUSE_CLICK_UP[2];

	int windowWidth;
	int windowHeight;
};

#endif