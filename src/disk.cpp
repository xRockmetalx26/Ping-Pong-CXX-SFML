#include <disk.h>
#include <iostream>
#include <ctime>
#include <cmath>

Disk::Disk() : sprite(10), active(false), speedX(4), speedY(4), time(1.0) {
	srand(std::time(nullptr));
	std::cout << "OK Disk()." << std::endl;
}

void Disk::setDirection() {
	speedX *= (rand() % 2 == 0) ? -1 : 1;
	speedY *= (rand() % 2 == 0) ? -1 : 1;

	do { angle = rand() % 41 - 20; } while(angle < 1 && angle > -1);
}

void Disk::switchDirectionX() {
	speedX *= -1;

	if(time < 4.8)
		time += 0.2;
}

void Disk::move() {
	sprite.move(speedX * time, speedY * time * sin(angle));
}

void Disk::resetDisk() {
	sprite.setPosition(Vector2f(720 / 2 - 10, 480 / 2 - 10));
	active = false;
	time = 1.0;
	setDirection();
}

Disk::~Disk() {
	std::cout << "OK ~Disk()." << std::endl;
}