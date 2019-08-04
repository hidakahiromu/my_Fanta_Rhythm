#include "FantaRhythm_v2.h"
#include "SelectMusic.h"
#include "SceneManager.h"

#define PI 3.141592

#define DEFAULT_ANGLE 120
#define FORWARD_ANGLE 30
#define SPEED_ROTATION 3
#define DEFAULT_ROTATION 30

SelectMusic::SelectMusic(void)  {
	TextureAsset::Register(U"back", U"resources/images/back/BackScreen.jpg");
	TextureAsset::Preload(U"back");
	TextureAsset::Register(U"title", U"resources/images/items/title.png");
	TextureAsset::Preload(U"title");

	FontAsset::Register(U"font", 30);
	FontAsset::Preload(U"font");
	musicrotation = difrotation = 0;
	initMusic();
	initDifficulty();

	changeState(MUSIC);//������Ԃ��ȑI����
	playMusic(musiccursor);//�ŏ��̋ȃv���r���[���Đ�
}

SelectMusic::~SelectMusic(void) {
	delete audio;
	TextureAsset::UnregisterAll();
	FontAsset::Unregister(U"font");

}

void SelectMusic::changeState(SELECTSTATE nextstate) {
	switch (nextstate) {
	case MUSIC:
		stateUpdate = &SelectMusic::updateMusic;
		stateDraw = &SelectMusic::drawMusic;
		break;
	case DIFFICULTY:
		stateUpdate = &SelectMusic::updateDifficulty;
		stateDraw = &SelectMusic::drawDifficulty;
		break;
	case TITLE:
		SceneManager::setNextScene(SceneManager::SCENE_TITLE);
		break;
	case GAME:
		SceneManager::setNextScene(SceneManager::SCENE_GAME);
		break;

	}
}

void SelectMusic::initMusic(void) {
	musiccursor = 0;
	setArray(musicarray, U"resources/musics/main/", musiccount);
}

void SelectMusic::initDifficulty(void) {
	difcursor = 0;
	setArray(difarray, getDiffilepath(musiccursor), difcount);
}

void SelectMusic::setArray(s3d::Array<FilePath>&array,const FilePath& filepath,int& count) {
	array = FileSystem::DirectoryContents(filepath, false);
	count = (int)array.count();
}
String SelectMusic::getDiffilepath(int cursor) {//��Փx�t�@�C���p�X�擾
	return (musicarray[cursor] + U"/score/");
}

void SelectMusic::update(void) {
	//��Ԃɍ��킹���v�Z����
	(this->*stateUpdate)();
}

void SelectMusic::updateMusic(void) {
	if (!musicrotation) {//�ړ��������������Ă���Ƃ�
		musicmoveCursor();
		if (KeyRight.down()) {//��Փx��
			changeState(DIFFICULTY);
		}else if (KeyLeft.down()) {//�^�C�g���֖߂�
			changeState(TITLE);
		}
	}
	else {
		rotatemusic(musicrotation);//�ړ�����
	}
}
void SelectMusic::updateDifficulty(void) {
	if (!difrotation) {//�ړ��������������Ă���Ƃ�
		difmoveCursor();//�㉺�ړ�����
		if (KeyRight.down()) {//�Q�[����
			changeState(GAME);
		}else if (KeyLeft.down()) {//�ȑI����
			changeState(MUSIC);
		}
	}
	else {
		rotatemusic(difrotation);//�ړ�����
	}
}

void SelectMusic::rotatemusic(int& rotation) {
	if (rotation < 0) {
		rotation += SPEED_ROTATION;//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���v���X
	}else if (rotation > 0) {
		rotation -= SPEED_ROTATION;//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���}�C�i�X
	}
}

void SelectMusic::draw(void) {
	//�w�i�摜�`��
	TextureAsset(U"back").draw();
	//���݂̏�Ԃɍ��킹���I�����̕`��
	(this->*stateDraw)();
}

void SelectMusic::musicmoveCursor(void) {
	if (KeyUp.pressed() == 1 && KeyDown.pressed() == 1) {//�㉺����������Ă�Έړ������Ȃ�
		return;
	}
	if (KeyUp.pressed()) {
		musiccursor == 0 ? musiccursor = musiccount - 1 : musiccursor--;//0�@�`�@count - 1����������[�v
		musicrotation = -DEFAULT_ROTATION;//�I��������]�����邽�ߊp�x��30�x�}�C�i�X
		playMusic(musiccursor);
		initDifficulty();//�Ȃɍ��킹����Փx�֏�����
	}
	else if (KeyDown.pressed()) {
		musiccursor == musiccount - 1 ? musiccursor = 0 : musiccursor++;
		musicrotation = DEFAULT_ROTATION;//�I��������]�����邽�ߊp�x��30�x�v���X
		playMusic(musiccursor);
		initDifficulty();//�Ȃɍ��킹����Փx�֏�����
	}
}

void SelectMusic::difmoveCursor(void) {
	if (KeyUp.pressed() == 1 && KeyDown.pressed() == 1) {//�㉺����������Ă�Έړ������Ȃ�
		return;
	}
	if (KeyUp.pressed()) {
		difcursor == 0 ? difcursor = difcount - 1 : difcursor--;//0�@�`�@count - 1����������[�v
		difrotation = -DEFAULT_ROTATION;//�I��������]�����邽�ߊp�x��30�x�}�C�i�X
	}else if (KeyDown.pressed()) {
		difcursor == difcount - 1 ? difcursor = 0 : difcursor++;
		difrotation = DEFAULT_ROTATION;//�I��������]�����邽�ߊp�x��30�x�v���X
	}
}


void SelectMusic::playMusic(int musicNum) {
	delete audio;
	audio = new Audio(musicarray[musicNum] + U"/preview.wav");
	audio->setLoop(true);
	audio->play();
}

void SelectMusic::drawMusic(void) {
	/*�Ȗ��̕`��*/
	for (int i = 0; i < 5; i++) {
		//���W�̎w��
		int angle = DEFAULT_ANGLE + FORWARD_ANGLE * i + musicrotation;
		int x = (int)(1800 + cos((angle)* PI / 180.0) * 1000);
		int y = (int)((Window::Height() / 2) - sin((angle)* PI / 180.0) * 500);
		//�`��
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(FileSystem::BaseName(musicarray[(musiccursor - 2 + i + musiccount) % musiccount])).drawAt(x, y, Color(0, 0, 0));
	}
}
void SelectMusic::drawDifficulty(void) {
	/*�Ȗ��̕`��*/
	for (int i = 0; i < 5; i++) {
		//���W�̎w��
		int angle = DEFAULT_ANGLE + FORWARD_ANGLE * i + difrotation;
		int x = (int)(1800 + cos((angle)* PI / 180.0) * 1000);
		int y = (int)((Window::Height() / 2) - sin((angle)* PI / 180.0) * 500);
		//�`��
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(FileSystem::BaseName(difarray[(difcursor - 2 + i + difcount) % difcount])).drawAt(x, y, Color(0, 0, 0));
	}
}

String SelectMusic::getMusicPath(void) {
	return musicarray[musiccursor];
}
String SelectMusic::getDifPath(void) {
	return difarray[difcursor];
}