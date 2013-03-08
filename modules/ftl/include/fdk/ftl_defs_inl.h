#ifndef __FDK_FTL_DEFS_INL_H__
#define __FDK_FTL_DEFS_INL_H__

FDK_NS_BEGIN

template <typename T>
IS_POD_TAG_ID ValueIsPod(T&) {
	return ValueIsPodTrait<T>::Type::ID;
}

template < typename TYPE >
void Swap(TYPE& l, TYPE& r) {     
	TYPE temp = l;                
	l = r;                        
	r = temp;                  
}

template <typename T>
void CompSwap(T& left, T& right) {
	if (left < right)
		Swap(left, right);
}

FDK_NS_END

#endif