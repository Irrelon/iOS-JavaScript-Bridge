#ifndef __WSTRING_H__
#define __WSTRING_H__

#include "wchar.h"
#include "wbasicatomic.h"

class WString
{
public:
	WString() : d(&shared_null) { d->ref.ref(); }
	WString(int size, int initvalue);

	WString &append(WChar c);
	WString toLower() const;
	WString toUpper() const;
	inline int length() const
	{ return d->size; }
	const WChar at(int i) const;
	int grow(int size);
	void realloc(int alloc);
	void resize(int size);
	void truncate(int pos);

protected:

private:
	struct Data {
		WBasicAtomicInt ref;
		int alloc, size;
		ushort *data; 
		ushort clean : 1;
		ushort simpletext : 1;
		ushort righttoleft : 1;
		ushort asciiCache : 1;
		ushort capacity : 1;
		ushort reserved : 11;
		ushort array[1];
	};
	static Data shared_null;
	static Data shared_empty;
	Data *d;
};

#endif
