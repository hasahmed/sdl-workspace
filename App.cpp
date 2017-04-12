//==============================================================================
#include <iostream>
#include "App.h"
#include "Log.h"
#include "CSurface.h"
App App::Instance;

//==============================================================================
App::App() {
}

//------------------------------------------------------------------------------
void App::OnEvent(SDL_Event* Event) {
}

//------------------------------------------------------------------------------
bool App::Init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    	Log("Unable to Init SDL: %s", SDL_GetError());
    	return false;
    }
/*
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        Log("Unable to Init hinting: %s", SDL_GetError());
    }
*/
    if((Window = SDL_CreateWindow(
    	"Operation Tetris",
    	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	WindowWidth, WindowHeight, SDL_WINDOW_SHOWN)
    ) == NULL) {
    	Log("Unable to create SDL Window: %s", SDL_GetError());
    	return false;
    }


    PrimarySurface = SDL_GetWindowSurface(Window);
    image = SDL_LoadBMP("finn.bmp");
  //  secondarySurface = CSurface::OnLoad("blah.png");
    if(image == NULL){
        SDL_ClearError();
        Log("Error creating secondary surface. Error");
        return false;
    }
    SDL_BlitSurface(image, NULL, PrimarySurface, NULL);
    SDL_UpdateWindowSurface(Window);
/*
    if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        Log("Unable to create renderer: %s", SDL_GetError());
     //   return false;
    }
*/
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 0);
    return true;
}

//------------------------------------------------------------------------------
void App::Loop() {
}

//------------------------------------------------------------------------------
void App::Render() {
    SDL_RenderClear(Renderer);

	SDL_RenderPresent(Renderer);
}

//------------------------------------------------------------------------------
void App::Cleanup() {
    SDL_FreeSurface(PrimarySurface);
    SDL_FreeSurface(image);
	if(Renderer) {
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}

	if(Window) {
		SDL_DestroyWindow(Window);
		Window = NULL;
	}

    SDL_Quit();
}

//------------------------------------------------------------------------------
int App::Execute(int argc, char* argv[]) {
    if(!Init()) return 0;

	SDL_Event Event;

	while(Running) {
		while(SDL_PollEvent(&Event) != 0) {
			OnEvent(&Event);

			if(Event.type == SDL_QUIT) Running = false;
            if(Event.type == SDL_WINDOWEVENT){
                if(Event.window.event == SDL_WINDOWEVENT_MOVED){
                    SDL_Log("Window %d moved to %d,%d",
                            Event.window.windowID, Event.window.data1,
                            Event.window.data2);
                }
            }

//keyboard
        if(Event.type == SDL_KEYDOWN){

            std::cout << Event.key.keysym.sym << "\n";
        }


		}

		Loop();
		Render();

		SDL_Delay(1); // Breath
	}

	Cleanup();

	return 1;
}

//==============================================================================
App* App::GetInstance() { return &App::Instance; }

int App::GetWindowWidth()  { return WindowWidth; }
int App::GetWindowHeight() { return WindowHeight; }

//==============================================================================
