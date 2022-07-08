#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <iostream>
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
using namespace std;

class Engine
{
private: // private properties.
	bool m_running = false;
	Uint32 m_start, m_end, m_delta, m_fps;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

private: // private method prototypes.
	Engine() { cout << "Engine object created..." << endl; }
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvents();
	// Moved KeyDown from here to EventManager.
	void Update();
	void Render();
	void Sleep();

public: // public method prototypes.
	int Run();
	// Add static method for singleton here
	static Engine& Instance(); // We can invoke this without having an object of Engine.
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	bool& Running() { return m_running; } // For EventManager.
};

#endif

// Reminder: you can ONLY have declarations in headers, not logical code
