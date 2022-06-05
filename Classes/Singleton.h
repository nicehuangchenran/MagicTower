#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "Headers.h"

template <class T>
class Singleton {
public:
	static inline T* instance();
	void release();
protected:
	Singleton(void) {}
	~Singleton(void) {}
	static T* _instance;
};

template <class T>
inline T* Singleton<T>::instance() {
	if (!_instance)
		_instance = new T;
	return _instance;
}

//template <class T>
//void Singleton<T>::release() {
//	unique_ptr<T>instPtr(_instance);
//	if (!instPtr)
//		return;
//}

//声明静态变量
#define DECLARE_SINGLETON_MEMBER(_Ty)	\
	template <> _Ty* Singleton<_Ty>::_instance = NULL;

#endif
