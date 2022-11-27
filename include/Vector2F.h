#pragma once
namespace lan {
	struct Vector2F
	{
		float x = 0.f;
		float y = 0.f;
		Vector2F(int x, int y) {
			this->x = x;
			this->y = y;
		}
		Vector2F(float x, float y) {
			this->x = x;
			this->y = y;
		}
		Vector2F() = default;
	};
}


