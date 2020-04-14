#ifndef DISK_H
#define DISK_H

#include <SFML/Graphics/CircleShape.hpp>

using namespace sf;

class Disk
{
public:

	//------------ BEGIN PUBLIC ------------//

	Disk();
	Disk(Disk const &original);
	virtual ~Disk();

	void setDirection();
	void move();
	void resetDisk();

	void switchDirectionX();
	void switchDirectionY() { speedY *= -1; }
	inline void	activateDisk() { active = true; }

	inline bool const	&isActive() const { return active; }
	inline CircleShape	&getSprite() { return sprite; }

	//------------ END PUBLIC ------------//

private:

	//------------ BEGIN PRIVATE ------------//

	CircleShape sprite;
	float angle;
	float time;
	float speedX;
	float speedY;
	bool active;

	//------------ END PRIVATE ------------//
};

#endif	//DISK_H