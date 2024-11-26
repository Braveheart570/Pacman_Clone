#pragma once
#include <random>
#include <chrono>

namespace SDLFramework {

	class Random {

	public:
		static Random* Instance();
		static void Release();

		unsigned int RandomInt(); //0 to unsigned max
		float RandomFloat(); //0.0 to 1.0;
		int RandomRange(int low, int high); // low to high
		float RandomRange(float lo, float hi); // lo to hi

	private:
		static Random* sInstance;
		std::mt19937 mGenerator;

		Random();
		~Random();

	};

}