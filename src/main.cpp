#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Init function that will verify if we have initialized
// SDL2 and its subsystems

const int WINDOW_WIDTH {800};
const int WINDOW_HEIGHT {640};

bool successfullInit();
void moveSquare(SDL_Rect &rect);

int main(int argc, char* args[]){

    if (!successfullInit()) {
        std::cout << "Initialization has failed somewhere." << std::endl;
    }
    else {
        std::cout << "Let's get rollin'!" << std::endl;
    }

    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};

    // Create a SDL Window
    window = SDL_CreateWindow(
        "My SDL Template", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_HEIGHT, WINDOW_WIDTH, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect square {0, 0, 64, 64};
    

    bool isRunning = true;
    SDL_Event event;

    while(isRunning) {
        // Get events
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym)
            {
            case SDLK_d:
                //moveSquare(square);
                break;
            
            default:
                break;
            }
        }

        // Update
        square.x += 1;
        
        // Draw/Render to the window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 18, 206, 106, 255);

        SDL_RenderDrawRect(renderer, &square);

        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

bool successfullInit() {
    bool success {true};

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failure initializing SDL video subsystem." << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    if (TTF_Init() < 0) {
        std::cout << "Failure initializing SDL font subsystem." << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << "An error occured initializing the image module." << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        success = false;
	}

    std::cout << "Status: " << success << std::endl;
    return success;
}

void moveSquare(SDL_Rect &rect) {
    rect.x += 1;
}

