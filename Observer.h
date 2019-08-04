#pragma once
#include <list>

/*---------------------------------------------------------
	Observer �p�^�[�� �Ϗ����Ďg���Ƃ����炵���H
	addObserver�Ŋώ@����l��o�^


-----------------------------------------------------------*/

enum Massage {//�C�x���g���ꗗ�@�����܂ő��������ɂȂ��̂ňꊇ�Ǘ�
	NONE,//�Ȃ��ꍇ
	ATTACK,
	SMALLDAMAGE,
	BIGDAMAGE,
};

typedef struct _Obj {//�C�x���g�p�I�u�W�F�N�g�@
	Massage msg;//�C�x���g��
	int val;//�ėp�l
}Obj;

/*--------------------------------------------------------
	�N���X���FObserver
	�@�\�F�ώ@��

---------------------------------------------------------*/
class Observer{
public:
	//virtual ~Observer(void); 
	virtual void funcEvent(Obj o) = 0;

	void setObject(class Subject* pSubject){//�Ăяo�����n���h�� Subject������Ăяo�����
		m_pSubject = pSubject;
	}
protected://�h�����private�����o�ɂȂ�protected
	class Subject* m_pSubject;

};

/*--------------------------------------------------------
	�N���X���FSubject
	�@�\�F�ώ@�Ώ� �ʒm���鑤
		  �I�u�U�[�o�̃��X�g��ێ�
		�@�����ɏ�Ԃ̕ω�������ƕێ����Ă���I�u�U�[�o�B�ɒʒm�𑗂�


-----------------------------------------------------------*/
class Subject {
public:
	//Observer�S�č폜
	virtual ~Subject(void) {
		std::list<Observer*>::iterator it;
		for (it = m_observers.begin(); it != m_observers.end(); it++) {
			(*it)->setObject(NULL);
		}
	}
	//�o�^���ꂽObserver�̃n���h�����Ăяo��
	virtual void notifyObservers(void) {
		std::list<Observer*>::iterator it;
		for (it = m_observers.begin(); it != m_observers.end(); it++) {
			(*it)->funcEvent(getMassage());
		}
	}
	//Observer��o�^
	virtual void addObserver(class Observer* pObserver) {
		m_observers.push_back(pObserver);
		pObserver->setObject(this);
	}
	virtual Obj getMassage() = 0;


protected:
	std::list<class Observer*> m_observers;//�I�u�U�[�o��ێ�
};

class NotesSubject : public Subject {
private:
	Obj o;
public:
	//�C�x���g�p�̃��b�Z�[�W��Ԃ�
	Obj getMassage() {
		return o;
	}
	//�C�x���g���Z�b�g����
	void setEvent(Massage msg, int val) {
		o = {msg,val};
	}
};
