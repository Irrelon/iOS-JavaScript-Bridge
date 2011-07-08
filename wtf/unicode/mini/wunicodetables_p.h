

#ifndef __WUNICODETABLES_P_H__
#define __WUNICODETABLES_P_H__

#include "wchar.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#define UNICODE_DATA_VERSION WChar::Unicode_5_0

#define UNICODE_LAST_CODEPOINT 0x10ffff

#define SPECIAL_CASE_MAX_LEN 3

extern const ushort specialCaseMap[] ;

namespace WUnicodeTables {

    struct Properties {
        ushort category         : 8; /* 5 needed */
        ushort line_break_class : 8; /* 6 needed */
        ushort direction        : 8; /* 5 needed */
        ushort combiningClass   : 8;
        ushort joining          : 2;
        signed short digitValue : 6; /* 5 needed */
        ushort unicodeVersion   : 4;
        ushort lowerCaseSpecial : 1;
        ushort upperCaseSpecial : 1;
        ushort titleCaseSpecial : 1;
        ushort caseFoldSpecial  : 1; /* currently unused */
        signed short mirrorDiff    : 16;
        signed short lowerCaseDiff : 16;
        signed short upperCaseDiff : 16;
        signed short titleCaseDiff : 16;
        signed short caseFoldDiff  : 16;
        ushort graphemeBreak    : 8; /* 4 needed */
        ushort wordBreak        : 8; /* 4 needed */
        ushort sentenceBreak    : 8; /* 4 needed */
    };
     const Properties *  properties(uint ucs4);
     const Properties *  properties(ushort ucs2);

    // See http://www.unicode.org/reports/tr24/tr24-5.html
    enum Script {
        Common,
        Greek,
        Cyrillic,
        Armenian,
        Hebrew,
        Arabic,
        Syriac,
        Thaana,
        Devanagari,
        Bengali,
        Gurmukhi,
        Gujarati,
        Oriya,
        Tamil,
        Telugu,
        Kannada,
        Malayalam,
        Sinhala,
        Thai,
        Lao,
        Tibetan,
        Myanmar,
        Georgian,
        Hangul,
        Ogham,
        Runic,
        Khmer,
        Nko,
        Inherited,
        ScriptCount = Inherited,
        Latin = Common,
        Ethiopic = Common,
        Cherokee = Common,
        CanadianAboriginal = Common,
        Mongolian = Common,
        Hiragana = Common,
        Katakana = Common,
        Bopomofo = Common,
        Han = Common,
        Yi = Common,
        OldItalic = Common,
        Gothic = Common,
        Deseret = Common,
        Tagalog = Common,
        Hanunoo = Common,
        Buhid = Common,
        Tagbanwa = Common,
        Limbu = Common,
        TaiLe = Common,
        LinearB = Common,
        Ugaritic = Common,
        Shavian = Common,
        Osmanya = Common,
        Cypriot = Common,
        Braille = Common,
        Buginese = Common,
        Coptic = Common,
        NewTaiLue = Common,
        Glagolitic = Common,
        Tifinagh = Common,
        SylotiNagri = Common,
        OldPersian = Common,
        Kharoshthi = Common,
        Balinese = Common,
        Cuneiform = Common,
        Phoenician = Common,
        PhagsPa = Common
    };
    enum { ScriptSentinel = 32 };


    enum GraphemeBreak {
        GraphemeBreakOther,
        GraphemeBreakCR,
        GraphemeBreakLF,
        GraphemeBreakControl,
        GraphemeBreakExtend,
        GraphemeBreakL,
        GraphemeBreakV,
        GraphemeBreakT,
        GraphemeBreakLV,
        GraphemeBreakLVT
    };


    enum WordBreak {
        WordBreakOther,
        WordBreakFormat,
        WordBreakKatakana,
        WordBreakALetter,
        WordBreakMidLetter,
        WordBreakMidNum,
        WordBreakNumeric,
        WordBreakExtendNumLet
    };


    enum SentenceBreak {
        SentenceBreakOther,
        SentenceBreakSep,
        SentenceBreakFormat,
        SentenceBreakSp,
        SentenceBreakLower,
        SentenceBreakUpper,
        SentenceBreakOLetter,
        SentenceBreakNumeric,
        SentenceBreakATerm,
        SentenceBreakSTerm,
        SentenceBreakClose
    };


    // see http://www.unicode.org/reports/tr14/tr14-19.html
    // we don't use the XX, AI and CB properties and map them to AL instead.
    // as we don't support any EBDIC based OS'es, NL is ignored and mapped to AL as well.
    enum LineBreakClass {
        LineBreak_OP, LineBreak_CL, LineBreak_QU, LineBreak_GL, LineBreak_NS,
        LineBreak_EX, LineBreak_SY, LineBreak_IS, LineBreak_PR, LineBreak_PO,
        LineBreak_NU, LineBreak_AL, LineBreak_ID, LineBreak_IN, LineBreak_HY,
        LineBreak_BA, LineBreak_BB, LineBreak_B2, LineBreak_ZW, LineBreak_CM,
        LineBreak_WJ, LineBreak_H2, LineBreak_H3, LineBreak_JL, LineBreak_JV,
        LineBreak_JT, LineBreak_SA, LineBreak_SG,
        LineBreak_SP, LineBreak_CR, LineBreak_LF, LineBreak_BK
    };


     WUnicodeTables::LineBreakClass  lineBreakClass(uint ucs4);
     
	 inline int lineBreakClass(const WChar &ch)
     { 
		return lineBreakClass(ch.unicode());
	 }

     int  script(uint ucs4);
    inline int script(const WChar &ch)
    { return script(ch.unicode()); }
	
} 

const WUnicodeTables::Properties  * wGetProp(uint ucs4);

#endif 
