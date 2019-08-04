#pragma once
#include "Game.h"
#include "FantaRhythm_v2.h"
#include "Observer.h"
#include <vector>
#include <list>

#define LANESIZE 4		//LANE�̐�

/*--------------------------------------------


-----------------------------------------------*/
class NotesManager {
private:
	enum NOTESTYPE {
		NORMAL,
		LONG,
		SENTINEL
	};
	typedef struct _Notes {
		NOTESTYPE type;
		int time;
		int longtime;
		bool display;
	}Notes;

	int notewidth;
	
	class NotesSubject* subject;
	
	std::list<Notes> notelist[LANESIZE];
	using noteitr = std::list<Notes>::iterator;
	noteitr checkitr[LANESIZE];		//���肷�ׂ��C�e���[�^�ێ�
	noteitr displayitr[LANESIZE];	//�\�����ׂ��C�e���[�^�ێ�

	int nowTime;	//���ݎ���[ms]

	bool down[4];	//�����I�ɂ�bool�ł͂Ȃ��Ȃ艟���ꂽ�u�ԁA�����ꂽ�u�Ԃ̍Đ�����������
	bool press[4];	//������bool�ŉ�����Ă��ԗ�����Ă��Ԃ��Ǘ�

	bool longflag[4];

	//�`��֌W�̕ϐ�
	int laneStartX[4];	//Start = ���[���̏�[
	int laneJudgeX[4];	//Judge = ���[���Ɣ����������鏊
	int laneStartY;
	int laneJudgeY;
	int laneGoalY;		//Goal = ����؂����m�[�c�̕\������߂鏊
	float timeRequired;	//�m�[�c�̏o�����画��܂ŗ���鎞��[ms]
	float notespeed;	//�m�[�c���x�̕␳�{��

	void plusItr(noteitr& itr);	//notelist�̃C�e���[�^��i�߂�
	void checkAttack(void);		//�{�^���̉����󋵂��m�F����

	void controlJudge(void);	//�m�[�c�̎�ޖ��ɔ���p�֐����Ăяo��
	void judgeNormal(int lane);	//�m�[�}���m�[�c�𔻒�
	void judgeLong(int lane);	//�����O�m�[�c�𔻒�

	double getProgress(int time);//���[����[���画����܂ł̐i�񂾊�����Ԃ�
	double getCurrentPosition(int startPos, int endPos, double progressRate);//���ݍ��W��Ԃ�
	double getScale(double currenty);//�g�嗦�v�Z

	void displayNormal(int lane, int time);				//�m�[�}���m�[�c��\��
	void displayLong(int lane, int time, int longtime);	//�����O�m�[�c��\��

	void setEvent(Massage msg, int val);
	
public:
	NotesManager(NotesSubject* sub,const String& difpath);
	~NotesManager();
	void update(void);
	void draw(void);

};