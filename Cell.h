#pragma once
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

class Apple {
private:
	int x;
	int y;
public:
	Apple() { //Constructor
		this->setxy();
	}
	////////// getters ///////////
	int getx() {
		return this->x;
	}
	int gety() {
		return this->y;
	}
	////////// setters ///////////
	void setxy() { //set a random position for the apple
		this->x = (rand() % 20);
		this->y = (rand() % 20)+1;
	}
	////////// destructor ///////////
	~Apple() {}
};

class Snake {
private:
	string direction;
	int headx;
	int heady;
public:
	Snake(string d,int x, int y) { //Constructor
		this->headx = x;
		this->heady = y;
		this->direction = d;
	}
	////////// getters ///////////
	int getheadx() {
		return this->headx;
	}
	int getheady() {
		return this->heady;
	}
	string getdirection() {
		return this->direction;
	}
	////////// setters ///////////
	void setheadx(int x) {
		this->headx = x;
	}
	void setheady(int y) {
		this->heady = y;
	}
	void setdirection(string d) {
		this->direction = d;
	}
	////////// destructor ///////////
	~Snake() {}
};
