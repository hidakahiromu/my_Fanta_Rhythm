#include "Game.h"

Game::Game(const String& music, const String& dif) {
	musicpath = music;
	difpath = dif;

	subject = new NotesSubject();

	
	notes = new NotesManager(subject,difpath);
	
	int tmp[4] = { 0,0,1,1 };
	characterm = new CharacterSet(tmp);
	
	
	TextureAsset::Register(U"back", U"resources/images/back/first.jpg");
	TextureAsset::Preload(U"back");

	FontAsset::Register(U"font", 30);
	FontAsset::Preload(U"font");

	MusicManager::playMusicGame(musicpath);

	
}
Game::~Game() {
	delete notes;
	TextureAsset::UnregisterAll();
	FontAsset::Unregister(U"font");
}

void Game::update() {
	notes->update();
	characterm->update();
}
void Game::draw() {
	//�w�i�摜�`��
	TextureAsset(U"back").draw();
	notes->draw();
	characterm->draw();
}