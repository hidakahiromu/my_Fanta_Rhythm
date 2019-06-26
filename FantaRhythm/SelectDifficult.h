#pragma once
#include"SelectMusic.h"

class SelectDifficult :public SelectMusic {
public:
	SelectDifficult(void);
	~SelectDifficult(void);
	int Dupdate(void);
	void Ddraw(void);
private:
	std::vector<String> Difficult;
	int static cursor;
	int DifficultCount;
	void rotateMusic(void);
	int rotation;
	void moveCursor(void);
};