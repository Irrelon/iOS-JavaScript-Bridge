#include "wstring.h"

#include "wunicodetables_p.h"

#include <memory>
#include <assert.h>

using namespace WUnicodeTables;

#define BASIC_ATOMIC_INITIALIZER(a) {(a)}

WString::Data WString::shared_null = { BASIC_ATOMIC_INITIALIZER(1), 0, 0, shared_null.array, 0, 0, 0, 0, 0, 0, {0} };
WString::Data WString::shared_empty = { BASIC_ATOMIC_INITIALIZER(1),0, 0, shared_empty.array, 0, 0, 0, 0, 0, 0, {0} };


const WChar WString::at(int i) const
{ 
	assert(i >= 0 && i < d->size); return d->data[i]; 
}

template <typename T>
inline const T &min(const T &a, const T &b) { if (a < b) return a; return b; }

void WString::realloc(int alloc)
{
	if (d->ref != 1 || d->data != d->array) {
		Data *x = static_cast<Data *>(malloc(sizeof(Data) + alloc * sizeof(WChar)));
		x->size = min(alloc, d->size);
		::memcpy(x->array, d->data, x->size * sizeof(WChar));
		x->array[x->size] = 0;
		x->asciiCache = 0;
		x->ref = 1;
		x->alloc = alloc;
		x->clean = d->clean;
		x->simpletext = d->simpletext;
		x->righttoleft = d->righttoleft;
		x->capacity = d->capacity;
		x->data = x->array;
		if (!d->ref.deref())
			::free(d);
		d = x;
	} else {
		d = static_cast<Data *>(::realloc(d, sizeof(Data) + alloc * sizeof(WChar)));
		d->alloc = alloc;
		d->data = d->array;
	}
}


void WString::resize(int size)
{
	if (size < 0)
		size = 0;

	if (size == 0 && !d->capacity) {
		Data *x = &shared_empty;
		x->ref.ref();
		if (!d->ref.deref())
			::free(d);
		d = x;
	} else {
		if (d->ref != 1 || size > d->alloc ||
			(!d->capacity && size < d->size && size < d->alloc >> 1))
			realloc(grow(size));
		if (d->alloc >= size) {
			d->size = size;
			if (d->data == d->array) {
				d->array[size] = '\0';
			}
		}
	}
}

int AllocMore(int alloc, int extra)
{
	if (alloc == 0 && extra == 0)
		return 0;
	const int page = 1 << 12;
	int nalloc;
	alloc += extra;
	if (alloc < 1<<6) {
		nalloc = (1<<3) + ((alloc >>3) << 3);
	} else  {
		if (alloc >= INT_MAX/2)
			return INT_MAX;
		nalloc = (alloc < page) ? 1 << 3 : page;
		while (nalloc < alloc) {
			if (nalloc <= 0)
				return INT_MAX;
			nalloc *= 2;
		}
	}
	return nalloc - extra;
}


int WString::grow(int size)
{
	return AllocMore(size * sizeof(WChar), sizeof(Data)) / sizeof(WChar);
}

WString &WString::append(WChar ch)
{
	if (d->ref != 1 || d->size + 1 > d->alloc)
		realloc(grow(d->size + 1));
	d->data[d->size++] = ch.unicode();
	d->data[d->size] = '\0';
	return *this;
}

WString WString::toLower() const
{
	const ushort *p = d->data;
	if (!p)
		return *this;
	if (!d->size)
		return *this;

	const ushort *e = d->data + d->size;

	if (WChar(*p).isLowSurrogate())
		++p;

	while (p != e) {
		uint c = *p;
		if (WChar(c).isLowSurrogate() && WChar(*(p - 1)).isHighSurrogate())
			c = WChar::surrogateToUcs4(*(p - 1), c);
		const WUnicodeTables::Properties *prop = wGetProp(c);
		if (prop->lowerCaseDiff || prop->lowerCaseSpecial) {
			WString s(d->size, 0);
			memcpy(s.d->data, d->data, (p - d->data)*sizeof(ushort));
			ushort *pp = s.d->data + (p - d->data);
			while (p < e) {
				uint c = *p;
				if (WChar(c).isLowSurrogate() && WChar(*(p - 1)).isHighSurrogate())
					c = WChar::surrogateToUcs4(*(p - 1), c);
				prop = wGetProp(c);
				if (prop->lowerCaseSpecial) {
					int pos = pp - s.d->data;
					s.resize(s.d->size + SPECIAL_CASE_MAX_LEN);
					pp = s.d->data + pos;
					const ushort *specialCase = specialCaseMap + prop->lowerCaseDiff;
					while (*specialCase)
						*pp++ = *specialCase++;
				} else {
					*pp++ = *p + prop->lowerCaseDiff;
				}
				++p;
			}
			s.truncate(pp - s.d->data);
			return s;
		}
		++p;
	}
	return *this;
}


WString WString::toUpper() const
{
	const ushort *p = d->data;
	if (!p)
		return *this;
	if (!d->size)
		return *this;

	const ushort *e = d->data + d->size;

	if (WChar(*p).isLowSurrogate())
		++p;

	while (p != e) {
		uint c = *p;
		if (WChar(c).isLowSurrogate() && WChar(*(p - 1)).isHighSurrogate())
			c = WChar::surrogateToUcs4(*(p - 1), c);
		const WUnicodeTables::Properties *prop = wGetProp(c);
		if (prop->upperCaseDiff || prop->upperCaseSpecial) {
			WString s(d->size, 0);
			memcpy(s.d->data, d->data, (p - d->data)*sizeof(ushort));
			ushort *pp = s.d->data + (p - d->data);
			while (p < e) {
				uint c = *p;
				if (WChar(c).isLowSurrogate() && WChar(*(p - 1)).isHighSurrogate())
					c = WChar::surrogateToUcs4(*(p - 1), c);
				prop = wGetProp(c);
				if (prop->upperCaseSpecial) {
					int pos = pp - s.d->data;
					s.resize(s.d->size + SPECIAL_CASE_MAX_LEN);
					pp = s.d->data + pos;
					const ushort *specialCase = specialCaseMap + prop->upperCaseDiff;
					while (*specialCase)
						*pp++ = *specialCase++;
				} else {
					*pp++ = *p + prop->upperCaseDiff;
				}
				++p;
			}
			s.truncate(pp - s.d->data);
			return s;
		}
		++p;
	}
	return *this;
}

void WString::truncate(int pos)
{
	if (pos < d->size)
		resize(pos);
}

WString::WString(int size, int initvalue)
{
	d = (Data*) ::malloc(sizeof(Data)+size*sizeof(WChar));

	d->ref = 1;
	d->alloc = d->size = size;
	d->clean = d->asciiCache = d->simpletext = d->righttoleft = d->capacity = 0;
	d->data = d->array;
	d->array[size] = '\0';
}
