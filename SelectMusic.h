#pragma once
#include "Scene.h"


class SelectMusic:public Scene{
public:
	SelectMusic(void);
	~SelectMusic(void);	
	void update(void);
	void draw(void);

	String getMusicPath(void);
	String getDifPath(void);
private:
	enum SELECTSTATE {
		MUSIC,
		DIFFICULTY,
		TITLE,
		GAME
	};

	Audio* audio;

	//���ꂼ��̗v�f���A���ݑI�����Ă���v�f�Y���A�ړ��p�̒l
	int musiccount, difcount;
	int musiccursor, difcursor;
	int musicrotation, difrotation;
	

	s3d::Array<FilePath> musicarray;
	s3d::Array<FilePath> difarray;

	void(SelectMusic::*stateUpdate)(void);//���s����v�Z�����ւ̊֐��|�C���^
	void(SelectMusic::*stateDraw)(void);//���s����`�揈���ւ̊֐��|�C���^

	void changeState(SELECTSTATE nextstate);//���݂̏�Ԃ�ύX����

	//����������
	void initDifficulty(void);
	void initMusic(void);
	//�������Ŏg�p����֐�
	String getDiffilepath(int musiccursor);
	void setArray(s3d::Array<FilePath>&array, const FilePath& filepath, int& count);
	//s�v�Z����
	void updateMusic(void);
	void updateDifficulty(void);
	//�`�揈��
	void drawMusic(void);
	void drawDifficulty(void);
	//�㉺�ړ����m����
	void difmoveCursor(void);
	void musicmoveCursor(void);
	//�ړ�����
	void rotatemusic(int& rotation);
	//�v���r���[�Đ�
	void playMusic(int musicNum);
};

