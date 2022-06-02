#include "Singleton.h"

template <class T>
inline T* Singleton<T>::instance()
{
	if (!_instance)
		_instance = new T;
	return _instance;
}

template <class T>
void Singleton<T>::release()
{
	if (!_instance)
		return;
	delete _instance;
	//_instance = 0;
}
