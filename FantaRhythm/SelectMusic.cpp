#include "FantaRhythm_v2.h"
#define PI 3.141592

int SelectMusic::cursor = 0;

SelectMusic::SelectMusic(void)  {

	cursor=0;

	TextureAsset::Register(U"back", U"resources/images/back/BackScreen.jpg");
	TextureAsset::Preload(U"back");
	TextureAsset::Register(U"title", U"resources/images/items/title.png");
	TextureAsset::Preload(U"title");

	FontAsset::Register(U"font", 30);
	FontAsset::Preload(U"font");

	//�Ȑ��̎擾
	musicCount = FileSystem::DirectoryContents(U"resources/musics/main/", false).count();

	/*�Ȗ��擾*/
	String musicPath;
	for (int i = 0; i < musicCount; i++) {
		musicPath = FileSystem::DirectoryContents(U"resources/musics/main/", false).at(i);
		music.push_back(FileSystem::BaseName(musicPath));
	}

	//�ȃv���r���[�̍Đ�
	playMusic(0);
}

SelectMusic::~SelectMusic(void) {
	TextureAsset::UnregisterAll();
	delete audio;
}

int SelectMusic::update(void) {
	moveCursor();
	rotateMusic();
	if (KeyR.down()) {
		return SELECT_DIFFICULT;
	}
	if (KeyA.down()) {
		return TITLE;
	}
	return SELECT_MUSIC;
}

void SelectMusic::draw(void) {
	//�w�i�摜�`��
	TextureAsset(U"back").draw();

	/*�Ȗ��̕`��*/
	for (int i = 0; i < 5; i++) {
		//���W�̎w��
		int angle = 120 + 30 * i + rotation;
		int x = 1800 + cos((angle)* PI / 180.0) * 1000;
		int y = (Window::Height() / 2) - sin((angle)* PI / 180.0) * 500;
		//�`��
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(music[(cursor - 2 + i + musicCount) % musicCount]).drawAt(x, y, Color(0, 0, 0));
	}
}

void SelectMusic::moveCursor(void) {
	if (KeyUp.down()) {
		cursor == 0 ? cursor = musicCount - 1 : cursor--;
		//�Ȗ�����]�����邽�ߊp�x��30�x�}�C�i�X
		rotation = -30;

		//�V�����Ȃ̃Z�b�g&�Đ�
		delete audio;
		playMusic(cursor);
	}
	if (KeyDown.down()) {
		cursor == musicCount - 1 ? cursor = 0 : cursor++;
		//�Ȗ�����]�����邽�ߊp�x��30�x�v���X
		rotation = 30;

		//�V�����Ȃ̃Z�b�g&�Đ�
		delete audio;
		playMusic(cursor);
	}
}

void SelectMusic::rotateMusic(void) {
	if (rotation < 0) {
		//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���v���X
		rotation += 3;
	}
	if (rotation > 0) {
		//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���}�C�i�X
		rotation -= 3;
	}
}

void SelectMusic::playMusic(int musicNum) {
	audio = new Audio(U"resources/musics/main/" + music[musicNum] + U"/preview.wav");
	audio->setLoop(true);
	audio->play();
}

int SelectMusic::getCursor(void) {
	return cursor;
}