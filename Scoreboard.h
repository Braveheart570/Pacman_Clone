#pragma once
#include "texture.h"
#include <vector>

using namespace SDLFramework;

class Scoreboard : public GameEntity {

public:
	Scoreboard();
	Scoreboard(SDL_Color color);
	~Scoreboard();

	void Score(int score);

	void Render();

private:

	std::vector<Texture*> mScore;
	SDL_Color mColor;


	void ClearBoard();


};