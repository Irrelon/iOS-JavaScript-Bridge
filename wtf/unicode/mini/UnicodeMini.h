
#ifndef __WTF_UNICODE_MINI_H__
#define __WTF_UNICODE_MINI_H__

#include "stdint.h"
#include "wtf/unicode/UnicodeMacrosFromICU.h"

#include "wchar.h"
#include "wstring.h"

#include <string>

typedef uint16_t UChar;
typedef uint32_t UChar32;

namespace WUnicodeTables {
	struct Properties {
		ushort category : 8;
		ushort line_break_class : 8;
		ushort direction : 8;
		ushort combiningClass :8;
		ushort joining : 2;
		signed short digitValue : 6; /* 5 needed */
		ushort unicodeVersion : 4;
		ushort lowerCaseSpecial : 1;
		ushort upperCaseSpecial : 1;
		ushort titleCaseSpecial : 1;
		ushort caseFoldSpecial : 1; /* currently unused */
		signed short mirrorDiff : 16;
		signed short lowerCaseDiff : 16;
		signed short upperCaseDiff : 16;
		signed short titleCaseDiff : 16;
		signed short caseFoldDiff : 16;
	};

	const Properties * properties(uint ucs4);
	const Properties * properties(ushort ucs2);
}

namespace WTF {
	namespace Unicode {

		enum Direction {
			LeftToRight = WChar::DirL,
			RightToLeft = WChar::DirR,
			EuropeanNumber = WChar::DirEN,
			EuropeanNumberSeparator = WChar::DirES,
			EuropeanNumberTerminator = WChar::DirET,
			ArabicNumber = WChar::DirAN,
			CommonNumberSeparator = WChar::DirCS,
			BlockSeparator = WChar::DirB,
			SegmentSeparator = WChar::DirS,
			WhiteSpaceNeutral = WChar::DirWS,
			OtherNeutral = WChar::DirON,
			LeftToRightEmbedding = WChar::DirLRE,
			LeftToRightOverride = WChar::DirLRO,
			RightToLeftArabic = WChar::DirAL,
			RightToLeftEmbedding = WChar::DirRLE,
			RightToLeftOverride = WChar::DirRLO,
			PopDirectionalFormat = WChar::DirPDF,
			NonSpacingMark = WChar::DirNSM,
			BoundaryNeutral = WChar::DirBN
		};

		enum CharCategory {
			NoCategory = 0,
			Mark_NonSpacing = U_MASK(WChar::Mark_NonSpacing),
			Mark_SpacingCombining = U_MASK(WChar::Mark_SpacingCombining),
			Mark_Enclosing = U_MASK(WChar::Mark_Enclosing),
			Number_DecimalDigit = U_MASK(WChar::Number_DecimalDigit),
			Number_Letter = U_MASK(WChar::Number_Letter),
			Number_Other = U_MASK(WChar::Number_Other),
			Separator_Space = U_MASK(WChar::Separator_Space),
			Separator_Line = U_MASK(WChar::Separator_Line),
			Separator_Paragraph = U_MASK(WChar::Separator_Paragraph),
			Other_Control = U_MASK(WChar::Other_Control),
			Other_Format = U_MASK(WChar::Other_Format),
			Other_Surrogate = U_MASK(WChar::Other_Surrogate),
			Other_PrivateUse = U_MASK(WChar::Other_PrivateUse),
			Other_NotAssigned = U_MASK(WChar::Other_NotAssigned),
			Letter_Uppercase = U_MASK(WChar::Letter_Uppercase),
			Letter_Lowercase = U_MASK(WChar::Letter_Lowercase),
			Letter_Titlecase = U_MASK(WChar::Letter_Titlecase),
			Letter_Modifier = U_MASK(WChar::Letter_Modifier),
			Letter_Other = U_MASK(WChar::Letter_Other),
			Punctuation_Connector = U_MASK(WChar::Punctuation_Connector),
			Punctuation_Dash = U_MASK(WChar::Punctuation_Dash),
			Punctuation_Open = U_MASK(WChar::Punctuation_Open),
			Punctuation_Close = U_MASK(WChar::Punctuation_Close),
			Punctuation_InitialQuote = U_MASK(WChar::Punctuation_InitialQuote),
			Punctuation_FinalQuote = U_MASK(WChar::Punctuation_FinalQuote),
			Punctuation_Other = U_MASK(WChar::Punctuation_Other),
			Symbol_Math = U_MASK(WChar::Symbol_Math),
			Symbol_Currency = U_MASK(WChar::Symbol_Currency),
			Symbol_Modifier = U_MASK(WChar::Symbol_Modifier),
			Symbol_Other = U_MASK(WChar::Symbol_Other)
		};
	
	

		inline UChar32 toLower(UChar32 ch)
		{
			 return WChar::toLower(uint32_t(ch));
		}

		inline int toLower(UChar* result, int resultLength, const UChar* src, int srcLength,  bool* error)
		{
			const UChar *e = src + srcLength;
			const UChar *s = src;
			UChar *r = result;
			uint rindex = 0;

			// this avoids one out of bounds check in the loop
			if (s < e && WChar(*s).isLowSurrogate()) {
				if (r)
					r[rindex] = *s++;
				++rindex;
			}

			int needed = 0;
			while (s < e && (rindex < uint(resultLength) || !r)) {
				uint c = *s;
				if (WChar(c).isLowSurrogate() && WChar(*(s - 1)).isHighSurrogate())
					c = WChar::surrogateToUcs4(*(s - 1), c);
				const WUnicodeTables::Properties *prop = WUnicodeTables::properties(c);
				if (prop->lowerCaseSpecial) {
					WString wstring;
					if (c < 0x10000) {
						wstring.append(WChar(c));
					} else {
						wstring.append (WChar(*(s-1)));
						wstring.append(WChar(*s));
					}
					wstring = wstring.toLower();
					for (int i = 0; i < wstring.length(); ++i) {
						if (rindex >= uint(resultLength)) {
							needed += wstring.length() - i;
							break;
						}
						if (r)
							r[rindex] = wstring.at(i).unicode();
						++rindex;
					}
				} else {
					if (r)
						r[rindex] = *s + prop->lowerCaseDiff;
					++rindex;
				}
				++s;
			}
			if (s < e)
				needed += e - s;
			*error = (needed != 0);
			if (rindex < uint(resultLength))
				r[rindex] = 0;
			return rindex + needed;
		}

		inline UChar32 toUpper(UChar32 c)
		{
			 return WChar::toUpper(uint32_t(c));
		}

		inline int toUpper(UChar* result, int resultLength, const UChar* src, int srcLength,  bool* error)
		{
			const UChar *e = src + srcLength;
			const UChar *s = src;
			UChar *r = result;
			int rindex = 0;

			// this avoids one out of bounds check in the loop
			if (s < e && WChar(*s).isLowSurrogate()) {
				if (r)
					r[rindex] = *s++;
				++rindex;
			}

			int needed = 0;
			while (s < e && (rindex < resultLength || !r)) {
				uint c = *s;
				if (WChar(c).isLowSurrogate() && WChar(*(s - 1)).isHighSurrogate())
					c = WChar::surrogateToUcs4(*(s - 1), c);
				const WUnicodeTables::Properties *prop = WUnicodeTables::properties(c);
				if (prop->upperCaseSpecial) {
					WString wstring;
					if (c < 0x10000) {
						wstring.append(WChar(c));
					} else {
						wstring.append(WChar(*(s-1)));
						wstring.append(WChar(*s)) ;
					}
					wstring = wstring.toUpper();
					for (int i = 0; i < wstring.length(); ++i) {
						if (rindex >= resultLength) {
							needed += wstring.length() - i;
							break;
						}
						if (r)
							r[rindex] = wstring.at(i).unicode();
						++rindex;
					}
				} else {
					if (r)
						r[rindex] = *s + prop->upperCaseDiff;
					++rindex;
				}
				++s;
			}
			if (s < e)
				needed += e - s;
			*error = (needed != 0);
			if (rindex < resultLength)
				r[rindex] = 0;
			return rindex + needed;
		}

		inline UChar32 foldCase(UChar32 c)
		{
			return WChar::toCaseFolded(uint32_t(c));
		}

		inline int foldCase(UChar* result, int resultLength, const UChar* src, int srcLength,  bool* error)
		{
			*error = false;
			if (resultLength < srcLength) {
				*error = true;
				return srcLength;
			}
			for (int i = 0; i < srcLength; ++i)
				result[i] = WChar::toCaseFolded(ushort(src[i]));
			return srcLength;
		}

		inline bool isSeparatorSpace(UChar32 c)
		{
			  return WChar::category(uint32_t(c)) == WChar::Separator_Space;
		}

		inline int umemcasecmp(const UChar* a, const UChar* b, int len)
		{
			// handle surrogates correctly
			for (int i = 0; i < len; ++i) {
				uint c1 = WChar::toCaseFolded(ushort(a[i]));
				uint c2 = WChar::toCaseFolded(ushort(b[i]));
				if (c1 != c2)
					return c1 - c2;
			}
			return 0;
		}

		inline Direction direction(UChar32 c)
		{
			 return (Direction)WChar::direction(uint32_t(c));
		}

		inline CharCategory category(UChar32 c)
		{
			 return (CharCategory) U_MASK(WChar::category(uint32_t(c)));
		}

	} 
}

#endif
