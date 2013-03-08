// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies). 
// See Licence.txt 

#ifndef __FDK_FTL_DEFS_H__
#define __FDK_FTL_DEFS_H__

#include "fdk/base_defs.h"


FDK_NS_BEGIN

	enum IS_POD_TAG_ID {
		IS_POD_TAG_ID_FALSE,
		IS_POD_TAG_ID_TRUE
	};

	struct IsPodTrueTag {
		static const IS_POD_TAG_ID ID = IS_POD_TAG_ID_TRUE;
	};

	struct IsPodFalseTag {
		static const IS_POD_TAG_ID ID = IS_POD_TAG_ID_FALSE;	
	};


	template <typename T> struct ValueIsPodTrait           { typedef IsPodFalseTag Type; };
	template <typename T> struct ValueIsPodTrait<T*>       { typedef IsPodTrueTag  Type; };
	template <typename T> struct ValueIsPodTrait<const T*> { typedef IsPodTrueTag  Type; };

	template <typename T>
	IS_POD_TAG_ID ValueIsPod(T&);

	template < typename TYPE >
	void Swap(TYPE& l, TYPE& r);


	template <typename T>
	void CompSwap(T& left, T& right);

#define FDK_VALUE_IS_POD(deviceName) template <> struct ValueIsPodTrait<deviceName> { typedef IsPodTrueTag Type; }
	
	FDK_VALUE_IS_POD(bool);
	FDK_VALUE_IS_POD(int);
	FDK_VALUE_IS_POD(unsigned int);
	FDK_VALUE_IS_POD(short);
	FDK_VALUE_IS_POD(unsigned short);
	FDK_VALUE_IS_POD(signed char);
	FDK_VALUE_IS_POD(unsigned char);
	FDK_VALUE_IS_POD(float);
	FDK_VALUE_IS_POD(double);
	FDK_VALUE_IS_POD(long);
	FDK_VALUE_IS_POD(unsigned long);
	FDK_VALUE_IS_POD(long long);
	FDK_VALUE_IS_POD(unsigned long long);


	template <typename Data, typename Base>
	struct Member : public Base {
		Member() {}
		Member(const Base& base) : Base(base) {}
		Member(const Base& base, Data data) : Base(base), d(data) {}
		Member(const Data& data) : d(data) {}
		Member& operator=(const Data& data) {
			if (&data == &d) {
				return *this;
			}
			d = data;
			return* this;
		}
		Data d;
	};

FDK_NS_END

#include "fdk/ftl_defs_inl.h"

#endif