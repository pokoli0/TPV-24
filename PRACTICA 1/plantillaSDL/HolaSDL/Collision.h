#pragma once
class Collision
{
	struct collision 
	{
		bool collides;
		bool damages;
		
		operator bool() const { return collides; }
	};

public:
	Collision(){}

};

