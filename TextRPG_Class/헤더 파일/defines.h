// ����� ��ũ�� ���� �ڵ� ��� ���⿡ ��Ƶ� ��.
#pragma once

// ��ũ�� ����� �ݵ�� �� �ٿ� ���ǰ� �Ǿ�� �Ѵ�.
// �� \ �� �ٿ��ָ� ���� �Ѱܵ� �� �ٷ� �ν��� �ȴ�.
// ��, ���� ������ ���� \ �� ������ �ʴ´�
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = NULL; }

// �̱��� ���� �ڵ����� ������ִ� ��ũ�θ� ���� ����.
// �̱��� ������ Ŭ���� Ÿ�Ը� �޶��� �� ������ �ϴ� ������ �Լ��� �� ������
#define DECLARE_SINGLE(Type) \
private: \
	static Type*	instance;\
public: \
	static Type*	GetInstance()\
		{\
			if(!instance)\
				instance = new Type;\
			return instance;\
		}\
	static void DestroyInstance()\
		{\
			SAFE_DELETE(instance);\
		}\
private:\
	Type();\
	~Type();

#define DEFINITION_SINGLE(Type) Type* Type::instance = NULL;

#define GET_SINGLE(Type)	Type::GetInstance()
#define DESTROY_SINGLE(Type)	Type::DestroyInstance()