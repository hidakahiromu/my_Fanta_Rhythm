#include "NotesManager.h"


NotesManager::NotesManager(NotesSubject* sub, const String& difpath) {
	TextureAsset::Register(U"note", U"resources/images/items/Nort3rd.png");
	TextureAsset::Preload(U"note");
	TextureAsset::Register(U"longef", U"resources/images/items/longNortsEffect2.png");
	TextureAsset::Preload(U"longef");


	CSVData csv;//���ʂ̎擾�@�������z��ŊǗ� 0 ���莞��(ms) 1 �����H 2 �������[��[0-3]
	Print << difpath;

	subject = sub;

	csv.load(difpath);//���ʂ̃��[�h
	NotesManager::Notes note;
	for (int j = 0; j < csv.rows(); j++) {
		int lane = csv.get<int>(j, 2);
		note.time = csv.get<int>(j, 0);
		note.longtime = note.time + csv.get<int>(j, 1);
		switch (csv.get<int>(j, 3)) {
			case 0:
				note.type = NORMAL;
				break;
			case 1:
				note.type = LONG;
				break;
		}
		note.display = true;
		notelist[lane].push_back(note);
	}

	note.type = SENTINEL;
	note.time = 0;
	note.longtime = 0;
	note.display = false;

	for (int lane = 0; lane < LANESIZE; lane++) {//���[�����Ƃɓ������Ԃ��i�[
		notelist[lane].push_back(note);//�ԕ��̐ݒu
		displayitr[lane] = checkitr[lane] = notelist[lane].begin();//�`�F�b�N�p�̃C�e���[�^����
		longflag[lane] = false;
	}

	//�`��֌W�̕ϐ��̏�����
	//X���W
	int Center = Window::Width() / 2;//���[���Q�̒��S
	int StartBetween = 80;//��[�ł̃��[���Ԃ̋���
	int JudgeBetween = 140;//������ł̃��[���Ԃ̋���
	for (int i = 0;i < LANESIZE;i++) {
		laneStartX[i] = Center + (int)((i - (LANESIZE - 1) / 2.0) * StartBetween);
		laneJudgeX[i] = Center + (int)((i - (LANESIZE - 1) / 2.0) * JudgeBetween);
	}
	//Y���W
	laneStartY = 100;
	laneJudgeY = 650;
	laneGoalY = 730;//(���Y���W���E + 10)
	//����
	notespeed = 1.0;
	timeRequired = 1500 / notespeed;

	notewidth = TextureAsset(U"note").width();
}
NotesManager::~NotesManager() {
	TextureAsset::UnregisterAll();
}


void NotesManager::update(void)
{
	nowTime = (int)(MusicManager::getMusicTime());
	checkAttack();
	controlJudge();
}

void NotesManager::plusItr(noteitr& itr) {
	if (itr->type != SENTINEL)//�ԕ����ǂ�������
		itr++;
}


void NotesManager::checkAttack(void) {
	 down[0] = KeyA.down();
	press[0] = KeyA.pressed();
	 down[1] = KeyS.down();
	press[1] = KeyS.pressed();
	 down[2] = KeyD.down();
	press[2] = KeyD.pressed();
	 down[3] = KeyF.down();
	press[3] = KeyF.pressed();
}
void NotesManager::controlJudge(void) {
	for (int i = 0;i < LANESIZE;i++) {
		switch (checkitr[i]->type) {
		case NORMAL:
			judgeNormal(i);
			break;
		case LONG:
			judgeLong(i);
			break;
		default:
			break;
		}
	}
}
void NotesManager::judgeNormal(int lane) {
	static const int bad = 200;//����̍ő�͈�[ms]��2
	static const int good = 100;//GOOD����͈�[ms]��2
	static const int great = 25;//GREAT����͈�[ms]��2
	int checktime = abs(nowTime - checkitr[lane]->time);
	if (down[lane] && checktime <= bad) {//������Ă邩���莞�ԓ��Ȃ画�菈��
		if (checktime <= great) {//GREAT
			
		}
		else if (checktime < good) {//GOOD
			
		}
		else{//BAD
			setEvent(Massage::SMALLDAMAGE, 0);
		}
		checkitr[lane]->display = false;
		plusItr(checkitr[lane]);
	}
	else if (nowTime >= checkitr[lane]->time + bad) {//������ĂȂ��܂܏I����
		setEvent(Massage::SMALLDAMAGE, 0);
		plusItr(checkitr[lane]);
	}
}
void NotesManager::judgeLong(int lane) {
	static const int good = 150;//����̍ő�͈�
	int checktime = abs(nowTime - checkitr[lane]->time);

	if (down[lane] && checktime <= good) {//�����ꂽ��t���O�𗧂Ă�
		longflag[lane] = true;
	}
	if (longflag[lane]) {
		if (press[lane]) {//�{�^��������
			checkitr[lane]->time = (int)(nowTime);//����ʒu�ȍ~�Ŏ~�߂�
			if (nowTime >= checkitr[lane]->longtime) {//������Ă���܂ܔ���ʒu�֗�����
				checkitr[lane]->time = checkitr[lane]->longtime;
				if (nowTime >= checkitr[lane]->longtime + good) {//������Ă���Ԃ͔��莞�Ԃ��肬��܂őҋ@�����邽��good���Z
					longflag[lane] = false;
					plusItr(checkitr[lane]);
				}
			}
		}
		else {//������
			if ((abs(nowTime - checkitr[lane]->longtime)) <= good) {
				checkitr[lane]->display = false;//����
			}
			else {//���s
				setEvent(Massage::SMALLDAMAGE, 0);
			}
			plusItr(checkitr[lane]);
			longflag[lane] = false;
		}
	}
	else if (nowTime >= checkitr[lane]->longtime) {//������Ă��Ȃ��܂܏I����
		setEvent(Massage::SMALLDAMAGE, 0);
		plusItr(checkitr[lane]);
		longflag[lane] = false;
	}
}



void NotesManager::draw(void){
	Line(0, laneJudgeY, 1920, laneJudgeY).draw(3, Palette::Black);
	for(int i = 0; i < LANESIZE; i++){
		Line(laneStartX[i], laneStartY, laneJudgeX[i], laneJudgeY).draw(1, Palette::Red);
		for (noteitr itr = displayitr[i]; itr != notelist[i].end(); itr++) {
			if (nowTime < itr->time - timeRequired)//�`��O�Ȃ�`��ł��؂�
				break;
			if (itr->display == false)
				continue;

			switch (itr->type){
			case NORMAL:
				displayNormal(i, itr->time);
				break;
			case LONG:
				displayLong(i, itr->time, itr->longtime);
				break;
			default:
				break;
			}
		}	
	}
}

double NotesManager::getProgress(int time) {
	return (timeRequired - (time - nowTime)) / timeRequired;
}
double NotesManager::getCurrentPosition(int startPos, int endPos, double progressRate) {
	return startPos + (endPos - startPos) * progressRate;
}

double NotesManager::getScale(double currenty) {
	double temp = currenty / (laneJudgeY - 100);//�������߂ɏk���������Ƃɖ߂����߈����Ă݂Ă���
	return  temp;
}

void NotesManager::displayNormal(int lane, int time) {
	double progressRate = getProgress(time);
	double currentY = getCurrentPosition(laneStartY, laneJudgeY, progressRate);
	if (currentY > laneGoalY) {
		plusItr(displayitr[lane]);
		return;
	}
	double currentX = getCurrentPosition(laneStartX[lane], laneJudgeX[lane], progressRate);
	TextureAsset(U"note").scaled(getScale(currentY)).drawAt(currentX, currentY);
}
void NotesManager::displayLong(int lane, int time, int longtime) {
	//�`��ʒu�̌v�Z
	//�㑤
	double progressRateEnd = getProgress(longtime);
	double currentEndY = getCurrentPosition(laneStartY, laneJudgeY, progressRateEnd);//�`��ʒuY���W���v�Z
	if (currentEndY > laneGoalY) {//�`�悪�I�����Ă���Ȃ�
		plusItr(displayitr[lane]);
		return;
	}
	double currentEndX = getCurrentPosition(laneStartX[lane], laneJudgeX[lane], progressRateEnd);//�`��ʒuX���W���v�Z
	if (currentEndY < laneStartY) {//�㑤���܂��`��ʒu�ɓ��B���Ă��Ȃ��Ȃ�
		currentEndX = laneStartX[lane];
		currentEndY = laneStartY;//�����ʒu�֌Œ�
	}

	//����
	double progressRateBgn = getProgress(time);
	double currentBgnY = getCurrentPosition(laneStartY, laneJudgeY, progressRateBgn);//�`��ʒuY���W���v�Z
	double currentBgnX = getCurrentPosition(laneStartX[lane], laneJudgeX[lane], progressRateBgn);//�`��ʒuX���W���v�Z

	//�g�嗦�v�Z
	double scaleEnd = getScale(currentEndY);
	double scaleBgn = getScale(currentBgnY);

	//�`�揈��
	for (int linex = 0; linex <= 25; linex++) {
		Line(currentEndX + linex * scaleEnd, currentEndY, currentBgnX + linex * scaleBgn, currentBgnY).draw(1, Color(150 + linex * 2, 50, 50));
		Line(currentEndX - linex * scaleEnd, currentEndY, currentBgnX - linex * scaleBgn, currentBgnY).draw(1, Color(150 + linex * 2, 50, 50));
	}
	
	TextureAsset(U"note").scaled(scaleEnd).drawAt(currentEndX, currentEndY);
	TextureAsset(U"note").scaled(scaleBgn).drawAt(currentBgnX, currentBgnY);

}

void NotesManager::setEvent(Massage msg, int val) {
	subject->setEvent(msg, val);//�C�x���g�I�u�W�F�N�g�Z�b�g
	subject->notifyObservers();//�C�x���g�N��
}
