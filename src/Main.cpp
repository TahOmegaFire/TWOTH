#include "Headers/Player.h"
#include "Headers/Map.h"
#include <time.h>
#include <iostream>
#include "Headers/Log.h"

Log logger;

//Constants for windows - TESTING AAAA
const int WINDOW_HEIGHT = 480;
const int WINDOW_WIDTH = 640;

//Function prototypes
bool Init();
bool Finish();

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

int main(int argc, char* argv[])
{
    if(!Init())
    {
        logger.WriteToLog("Close program");
        return -1;
    }
	/*//Initialization of Box2D
	b2Vec2 gravity(0.0f, -10.0f);
	
	b2World world(gravity);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.f, 10.0f);
	
	*///Endof Init

    bool endProgram = false;

    SDL_Event e;

    Point2D camera;
    camera.x = 0;
    camera.y = 0;
    const Uint8* currentKeyStates;

    Player mainPlayer;
	Map mainMap;
	mainMap.CreateTestMap();
	std::cout << "hh";
	mainMap.PrepareMap();
	std::cout << "hh";
	mainPlayer.collisionBox.m_X = mainMap.spawnPoint.x;
	mainPlayer.collisionBox.m_Y = mainMap.spawnPoint.y;

    while(!endProgram)
    {
        //Update phase
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                endProgram = true;
                break;
            }
        }

        currentKeyStates = SDL_GetKeyboardState(NULL);
        if(currentKeyStates[SDL_SCANCODE_ESCAPE])
            endProgram = true;

		mainPlayer.Update(currentKeyStates, mainMap);
        mainMap.Update();
		
		camera.x = mainPlayer.collisionBox.m_X - (WINDOW_WIDTH / 2);
		camera.y = mainPlayer.collisionBox.m_Y - (WINDOW_HEIGHT / 2);
		
		//Render phase
        SDL_RenderClear(mainRenderer);
		
		mainMap.Render(camera);

        mainPlayer.Render(camera);

        SDL_RenderPresent(mainRenderer);
    }

    Finish();

    return 0;
}

bool Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logger.WriteToLog("FATAL: Cannot init SDL_Init with flags SDL_INIT_VIDEO");
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        logger.WriteToLog("WARNING: Cannot activate linear filtering");
    }

    mainWindow = SDL_CreateWindow("World over the Heaven", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(mainWindow == NULL)
    {
        logger.WriteToLog("FATAL: Cannot create window");
        return false;
    }

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(mainRenderer == NULL)
    {
        logger.WriteToLog("FATAL: Cannot create renderer");
        return false;
    }

    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0xFF);

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        logger.WriteToLog("FATAL: Cannot initialize SDL_image");
        return false;
    }

    logger.WriteToLog("Initialization complete");

    srand(time(NULL));

    return true;
}

bool Finish()
{
    SDL_DestroyWindow(mainWindow);

    SDL_Quit();

    return true;
}
