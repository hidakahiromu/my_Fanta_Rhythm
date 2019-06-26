#include "FantaRhythm_v2.h"
#include "SelectDifficult.h"

#define PI 3.141592

int SelectDifficult::cursor = 0;

SelectDifficult::SelectDifficult(void) {
	cursor = 0;
	TextureAsset::Register(U"back", U"resources/images/back/BackScreen.jpg");
	TextureAsset::Preload(U"back");
	TextureAsset::Register(U"title", U"resources/images/items/title.png");
	TextureAsset::Preload(U"title");

	FontAsset::Register(U"font", 30);
	FontAsset::Preload(U"font");


	/*��Փx�擾*/
	String musicPath,DifficultPath;
		musicPath = FileSystem::DirectoryContents(U"resources/musics/main/", false).at(getCursor());

		//��Փx�̐��̎擾
		DifficultCount = FileSystem::DirectoryContents(U"resources/musics/main/"+FileSystem::BaseName(musicPath)+U"/score",false).count();
		for (int i = 0; i < DifficultCount; i++) {
			DifficultPath = FileSystem::DirectoryContents(U"resources/musics/main/" + FileSystem::BaseName(musicPath) + U"/score", false).at(i);
			Difficult.push_back(FileSystem::BaseName(DifficultPath));
		}
}

SelectDifficult::~SelectDifficult(void) {
	TextureAsset::UnregisterAll();
}

int SelectDifficult::Dupdate(void) {
	moveCursor();
	rotateMusic();
	if (KeyE.down()) {
		return SELECT_MUSIC;
	}
	return SELECT_DIFFICULT;
}

void SelectDifficult::Ddraw(void) {
	//�w�i�摜�`��
	TextureAsset(U"back").draw();

	/*�Ȗ��̕`��*/
	for (int i = 0; i < 5 ; i++) {
		//���W�̎w��
		int angle = 120 + 30 * i + rotation;
		int x = 1800 + cos((angle)* PI / 180.0) * 1000;
		int y = (Window::Height() / 2) - sin((angle)* PI / 180.0) * 500;
		//�`��
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(Difficult[(cursor - 2 + i + DifficultCount) % DifficultCount]).drawAt(x, y, Color(0, 0, 0));
	}
}

void SelectDifficult::moveCursor(void) {
	if (KeyUp.down()) {
		cursor == 0 ? cursor = DifficultCount - 1 : cursor--;
		//�Ȗ�����]�����邽�ߊp�x��30�x�}�C�i�X
		rotation = -30;
	}
	if (KeyDown.down()) {
		cursor == DifficultCount - 1 ? cursor = 0 : cursor++;
		//�Ȗ�����]�����邽�ߊp�x��30�x�v���X
		rotation = 30;

	}
}

void SelectDifficult::rotateMusic(void) {
	if (rotation < 0) {
		//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���v���X
		rotation += 3;
	}
	if (rotation > 0) {
		//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���}�C�i�X
		rotation -= 3;
	}
}