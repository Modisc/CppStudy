// 상수나 매크로 관련 코드 모두 여기에 모아둘 것.
#pragma once

// 매크로 기능은 반드시 한 줄에 정의가 되어야 한다.
// 단 \ 를 붙여주면 줄을 넘겨도 한 줄로 인식이 된다.
// 단, 제일 마지막 줄은 \ 을 붙이지 않는다
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = NULL; }

// 싱글톤 패턴 자동으로 만들어주는 매크로를 만들 것임.
// 싱글톤 패턴은 클래스 타입만 달라질 뿐 만들어야 하는 변수나 함수는 다 동일함
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