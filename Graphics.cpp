#include "Graphics.h"

namespace SDLFramework {

	// this is how we initialize static members in a class. specifically the ones we do not want to be constants.
	// static members cannot be defined on the same line they are declared witout being const. so we do it here.
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;

	// this is where we make this class a singleton
	Graphics* Graphics::Instance() {
		// checking to see if sInsatcen already has an isntace of graphics stored in it.
		if (sInstance == nullptr) {
			sInstance = new Graphics();
		}

		// return the instance after maing sure there is one.
		return sInstance;

	}


	void Graphics::Release() {
		delete sInstance;
		sInstance = nullptr;
		sInitialized = false;
	}


	SDL_Texture* Graphics::LoadTexture(std::string path) {

		SDL_Texture* tex = nullptr;

		SDL_Surface* surface = IMG_Load(path.c_str());

		if (surface == nullptr) {
			std::cerr << "Unable to load " << path << ". IMG Error: " << IMG_GetError() << std::endl;
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		if (tex == nullptr) {
			std::cerr << "Unable to create texture from surface. IMG Error: " << IMG_GetError() << std::endl;
			return nullptr;
		}
		
		return tex;
	}

	void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, float angle, SDL_RendererFlip flip) {
		SDL_RenderCopyEx(mRenderer,texture,srcRect,dstRect,angle,nullptr,flip);
	}


	SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {

		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		if (surface == nullptr) {
			std::cerr << "CreateTexTexture:: TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;
			return nullptr;
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);

		if (tex == nullptr) {
			std::cout << "CreateTexTexture:: SDL_CreateTextureSurface Error: " << SDL_GetError() << std::endl;
			return nullptr;
		}

		SDL_FreeSurface(surface);

		return tex;

	}



	bool Graphics::Initialized() {
		return sInitialized;
	}

	void Graphics::ClearBackBuffer() {
		SDL_RenderClear(mRenderer);
	}

	void Graphics::Render() {
		SDL_RenderPresent(mRenderer);
	}

	Graphics::Graphics() : mRenderer(nullptr) {
		sInitialized = Init();
	}


	Graphics::~Graphics(){
		// destroy th renderer first, reverse order of creation.
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
	}

	bool Graphics::Init() {

		//initialize SDL subsystems
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
			//failed to initialize
			std::cerr << "SDL could not init video: " << SDL_GetError() << std::endl;
			return -1;
		}

		//Draw a Window
		mWindow = SDL_CreateWindow(
			"Test Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (mWindow == nullptr) {
			std::cerr << "unable to create a window! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}

		// index -1 will find the first available rendering driver
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

		if (mRenderer == nullptr) {
			std::cerr << "unable to create a renderer! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}

		if (TTF_Init() == -1) {
			std::cerr << "unable to Initialize SDL_TTF! TTF_Error: " << TTF_GetError() << std::endl;
			return false;
		}


		return true;

	}

	void Graphics::DrawLine(int x1, int y1, int x2, int y2) {

		SDL_Color colorHolder = SDL_Color();

		SDL_GetRenderDrawColor(mRenderer,&colorHolder.r,&colorHolder.g,&colorHolder.b,&colorHolder.a);

		if (SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255) < 0) {
			std::cerr << "DrawLine set color error! " << SDL_GetError();
		}

		if (SDL_RenderDrawLine(mRenderer,x1,y1,x2,y2) < 0) {
			std::cerr << "DrawLine error! " << SDL_GetError();
		}

		if (SDL_SetRenderDrawColor(mRenderer, colorHolder.r, colorHolder.g, colorHolder.b, colorHolder.a) < 0) {
			std::cerr << "DrawLine set color error! " << SDL_GetError();
		}

	}

}