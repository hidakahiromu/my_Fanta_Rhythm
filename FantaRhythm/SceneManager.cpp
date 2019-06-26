#include "SceneManager.h"

SceneManager::SceneManager() {
	nowScene = TITLE;
	nextScene = TITLE;
	title = new Title();
}

void SceneManager::sceneUpdate() {
	//�V�[���ɕύX���������Ƃ�
	if (nowScene != nextScene) {
		changeScene();
		nowScene = nextScene;
	}

	//�V�[���̌Ăяo��
	switch (nowScene){
	case TITLE:
		nextScene = title->update();
		title->draw();
		break;

	case SELECT_MUSIC:
		nextScene = selectMusic->update();
		selectMusic->draw();
		break;
	case SELECT_DIFFICULT:
		nextScene = selectDifficult->Dupdate();
		selectDifficult->Ddraw();
		break;

	default:

		break;
	}
}

void SceneManager::changeScene(){
	//���݂̃V�[���̔j��
	switch (nowScene){
	case TITLE:
		delete title;
		break;
	case SELECT_MUSIC:
		delete selectMusic;
		break;
	case SELECT_DIFFICULT:
		delete selectDifficult;
		break;
	default:
		break;
	}

	//���̃V�[���̏�����
	switch (nextScene){
	case TITLE:
		title = new Title();
		break;

	case SELECT_MUSIC:
		selectMusic = new SelectMusic();
		break;

	case SELECT_DIFFICULT:
		selectDifficult = new SelectDifficult();
		break;

	default:
		break;
	}
}