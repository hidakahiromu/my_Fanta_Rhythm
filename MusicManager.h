#pragma once
#include "FantaRhythm_v2.h"

class MusicManager {
private:
	static Audio* audio;

public:
	MusicManager() = delete;
	static void playMusicPrev(String path);
	static void playMusicGame(String path);

	static double getMusicTime();//���̍Đ����Ԃ�ms�P�ʂŎ擾����
	static double getMilliSec();//1ms���T���v�����O���[�g����擾/*����*/
};