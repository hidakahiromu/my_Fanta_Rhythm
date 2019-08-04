#include"CharacterSet.h"

CharacterSet::CharacterSet(int save[]) {
	
	CSVData csv;

	csv.load(U"resources/charadata.csv");
	for (int i = 0; i < CHANUMBER; i++) {
		cha[i] = new Character(500.0,500);
	}
	cha[0] = new Character(500.0, 500);
	/*
	for (int j = 0; j < csv.rows(); j++) {
		int lane = csv.get<int>(j, 2);
		
	}
	*/
}

CharacterSet::~CharacterSet() {

}

void CharacterSet::draw() {
	for (int i = 0; i < CHANUMBER; i++) {
		cha[0]->draw();
	}
}

void CharacterSet::update() {
	for (int i = 0; i < CHANUMBER; i++) {
		cha[0]->update();
	}
}