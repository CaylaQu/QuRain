/*******************************************************************************
* File Name   :		 
* Description :	
* Author      :	
* Created     :	
* Modified    :	
*******************************************************************************/

// SDL includes pasted for convenience. Move/copy to relevant files.
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Engine.h"
#include <iostream>

int main(int argc, char* argv[])
{
	return Engine::Instance().Run();
}