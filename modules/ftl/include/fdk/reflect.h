#ifndef __FDK_REFLECT_H__
#define __FDK_REFLECT_H__

#include "fdk/ftl_defs.h"

FDK_NS_BEGIN

enum CTYPE {
	CTYPE_VOID         = 0,
	CTYPE_U8           = 1,
	CTYPE_U16          = 2,
	CTYPE_U32          = 3,
	CTYPE_U64          = 4,
	CTYPE_I8           = 5,
	CTYPE_I16          = 6,
	CTYPE_I32          = 7,
	CTYPE_I64          = 8,
	CTYPE_F32          = 9,
	CTYPE_F64          = 10,
	CTYPE_BOOL_FORMAT  = 64,
	CTYPE_UTF8_FORMAT  = 128,
	CTYPE_UTF16_FORMAT = 256,
	CTYPE_UTF32_FORMAT = 512,
	CTYPE_ASCII_FORMAT = 1024,
	CTYPE_PTR          = 2048,
	CTYPE_PTR_PTR      = 4096,
	CTYPE_BOOL         = CTYPE_U8   | CTYPE_BOOL_FORMAT,
	CTYPE_ASCII        = CTYPE_U8   | CTYPE_ASCII_FORMAT,
	CTYPE_UTF8         = CTYPE_U8   | CTYPE_UTF8_FORMAT,
	CTYPE_UTF16        = CTYPE_U16  | CTYPE_UTF16_FORMAT,
	CTYPE_UTF32        = CTYPE_U32  | CTYPE_UTF32_FORMAT,
	CTYPE_VOID_PTR     = CTYPE_VOID | CTYPE_PTR,
	CTYPE_U8_PTR       = CTYPE_U8   | CTYPE_PTR,
	CTYPE_U16_PTR      = CTYPE_U16  | CTYPE_PTR,
	CTYPE_U32_PTR      = CTYPE_U32  | CTYPE_PTR,
	CTYPE_U64_PTR      = CTYPE_U64  | CTYPE_PTR,
	CTYPE_I8_PTR       = CTYPE_I8   | CTYPE_PTR,
	CTYPE_I16_PTR      = CTYPE_I16  | CTYPE_PTR,
	CTYPE_I32_PTR      = CTYPE_I32  | CTYPE_PTR,
	CTYPE_I64_PTR      = CTYPE_I64  | CTYPE_PTR,
	CTYPE_F32_PTR      = CTYPE_F32  | CTYPE_PTR,
	CTYPE_F64_PTR      = CTYPE_F64  | CTYPE_PTR,
	CTYPE_VOID_PTR_PTR = CTYPE_VOID | CTYPE_PTR_PTR,
	CTYPE_U8_PTR_PTR   = CTYPE_U8   | CTYPE_PTR_PTR,
	CTYPE_U16_PTR_PTR  = CTYPE_U16  | CTYPE_PTR_PTR,
	CTYPE_U32_PTR_PTR  = CTYPE_U32  | CTYPE_PTR_PTR,
	CTYPE_U64_PTR_PTR  = CTYPE_U64  | CTYPE_PTR_PTR,
  	CTYPE_I8_PTR_PTR   = CTYPE_I8   | CTYPE_PTR_PTR,
	CTYPE_I16_PTR_PTR  = CTYPE_I16  | CTYPE_PTR_PTR,
	CTYPE_I32_PTR_PTR  = CTYPE_I32  | CTYPE_PTR_PTR,
	CTYPE_I64_PTR_PTR  = CTYPE_I64  | CTYPE_PTR_PTR,
	CTYPE_F32_PTR_PTR  = CTYPE_F32  | CTYPE_PTR_PTR,
	CTYPE_F64_PTR_PTR  = CTYPE_F64  | CTYPE_PTR_PTR
};

typedef bool Bool;
typedef wchar_t wchar;

struct CVariant {
	CTYPE type;
	U32 count;
	union Data {
		void *p, **pp;
		F32  f32, *f32p, **f32pp;
		F64  f64, *f64p, **f64pp;
		I8   i8, *i8p, **i8pp;
		I16  i16, *i16p, **i16pp;
		I32  i32, *i32p, **i32pp;
		I64  i64, *i64p, **i64pp;
		U8   u8, *u8p, **u8pp;
		U16  u16, *u16p, **u16pp;
		U32  u32, *u32p, **u32pp;
		U64  u64, *u64p, **u64pp;
		wchar_t wc, *wcp, **wpp;
		char    cc, *cp, **cpp;
	} d;
};

FDK_NS_END

#endif