
#ifndef __WCHAR_H__
#define __WCHAR_H__

#include "config.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

class WChar {
public:
    WChar();
    WChar(uchar c, uchar r);
    inline WChar(ushort rc) : ucs(rc){}
    WChar(short rc);
    WChar(uint rc);
    WChar(int rc);
    enum SpecialCharacter {
        Null = 0x0000,
        Nbsp = 0x00a0,
        ReplacementCharacter = 0xfffd,
        ObjectReplacementCharacter = 0xfffc,
        ByteOrderMark = 0xfeff,
        ByteOrderSwapped = 0xfffe,
        ParagraphSeparator = 0x2029,
        LineSeparator = 0x2028
    };
    WChar(SpecialCharacter sc);

    // Unicode information

    enum Category
    {
        NoCategory,

        Mark_NonSpacing,          //   Mn
        Mark_SpacingCombining,    //   Mc
        Mark_Enclosing,           //   Me

        Number_DecimalDigit,      //   Nd
        Number_Letter,            //   Nl
        Number_Other,             //   No

        Separator_Space,          //   Zs
        Separator_Line,           //   Zl
        Separator_Paragraph,      //   Zp

        Other_Control,            //   Cc
        Other_Format,             //   Cf
        Other_Surrogate,          //   Cs
        Other_PrivateUse,         //   Co
        Other_NotAssigned,        //   Cn

        Letter_Uppercase,         //   Lu
        Letter_Lowercase,         //   Ll
        Letter_Titlecase,         //   Lt
        Letter_Modifier,          //   Lm
        Letter_Other,             //   Lo

        Punctuation_Connector,    //   Pc
        Punctuation_Dash,         //   Pd
        Punctuation_Open,         //   Ps
        Punctuation_Close,        //   Pe
        Punctuation_InitialQuote, //   Pi
        Punctuation_FinalQuote,   //   Pf
        Punctuation_Other,        //   Po

        Symbol_Math,              //   Sm
        Symbol_Currency,          //   Sc
        Symbol_Modifier,          //   Sk
        Symbol_Other,             //   So

        Punctuation_Dask = Punctuation_Dash // oops
    };

    enum Direction
    {
        DirL, DirR, DirEN, DirES, DirET, DirAN, DirCS, DirB, DirS, DirWS, DirON,
        DirLRE, DirLRO, DirAL, DirRLE, DirRLO, DirPDF, DirNSM, DirBN
    };

    enum Decomposition
    {
        NoDecomposition,
        Canonical,
        Font,
        NoBreak,
        Initial,
        Medial,
        Final,
        Isolated,
        Circle,
        Super,
        Sub,
        Vertical,
        Wide,
        Narrow,
        Small,
        Square,
        Compat,
        Fraction
    };

    enum Joining
    {
        OtherJoining, Dual, Right, Center
    };

    enum CombiningClass
    {
        Combining_BelowLeftAttached       = 200,
        Combining_BelowAttached           = 202,
        Combining_BelowRightAttached      = 204,
        Combining_LeftAttached            = 208,
        Combining_RightAttached           = 210,
        Combining_AboveLeftAttached       = 212,
        Combining_AboveAttached           = 214,
        Combining_AboveRightAttached      = 216,

        Combining_BelowLeft               = 218,
        Combining_Below                   = 220,
        Combining_BelowRight              = 222,
        Combining_Left                    = 224,
        Combining_Right                   = 226,
        Combining_AboveLeft               = 228,
        Combining_Above                   = 230,
        Combining_AboveRight              = 232,

        Combining_DoubleBelow             = 233,
        Combining_DoubleAbove             = 234,
        Combining_IotaSubscript           = 240
    };

    enum UnicodeVersion {
        Unicode_Unassigned,
        Unicode_1_1,
        Unicode_2_0,
        Unicode_2_1_2,
        Unicode_3_0,
        Unicode_3_1,
        Unicode_3_2,
        Unicode_4_0,
        Unicode_4_1,
        Unicode_5_0
    };

    Category category() const;
    Direction direction() const;

    WChar toLower() const;
    WChar toUpper() const;
    WChar toCaseFolded() const;

    UnicodeVersion unicodeVersion() const;

    const char toAscii() const;
    inline const char toLatin1() const;
    inline const ushort unicode() const { return ucs; }

    inline ushort &unicode() { return const_cast<ushort&>(ucs); }

    static WChar fromAscii(char c);
    static WChar fromLatin1(char c);

    inline bool isNull() const { return ucs == 0; }

    bool isSpace() const;

    inline bool isLower() const { return category() == Letter_Lowercase; }
    inline bool isUpper() const { return category() == Letter_Uppercase; }
    inline bool isTitleCase() const { return category() == Letter_Titlecase; }

    inline bool isHighSurrogate() const {
        return ((ucs & 0xfc00) == 0xd800);
    }
    inline bool isLowSurrogate() const {
        return ((ucs & 0xfc00) == 0xdc00);
    }

    inline uchar cell() const { return uchar(ucs & 0xff); }
    inline uchar row() const { return uchar((ucs>>8)&0xff); }
    inline void setCell(uchar cell);
    inline void setRow(uchar row);

    static inline bool isHighSurrogate(uint ucs4) {
        return ((ucs4 & 0xfffffc00) == 0xd800);
    }
    static inline bool isLowSurrogate(uint ucs4) {
        return ((ucs4 & 0xfffffc00) == 0xdc00);
    }
    static inline bool requiresSurrogates(uint ucs4) {
        return (ucs4 >= 0x10000);
    }
    static inline uint surrogateToUcs4(ushort high, ushort low) {
        return (uint(high)<<10) + low - 0x35fdc00;
    }
    static inline uint surrogateToUcs4(WChar high, WChar low) {
        return (uint(high.ucs)<<10) + low.ucs - 0x35fdc00;
    }
    static inline ushort highSurrogate(uint ucs4) {
        return ushort((ucs4>>10) + 0xd7c0);
    }
    static inline ushort lowSurrogate(uint ucs4) {
        return ushort(ucs4%0x400 + 0xdc00);
    }

    static Category  category(uint ucs4);
    static Category  category(ushort ucs2);
    static Direction  direction(uint ucs4);
    static Direction  direction(ushort ucs2);
    static Joining  joining(uint ucs4);
    static Joining  joining(ushort ucs2);
    static unsigned char  combiningClass(uint ucs4);
    static unsigned char  combiningClass(ushort ucs2);

    static uint  mirroredChar(uint ucs4);
    static ushort  mirroredChar(ushort ucs2);
    static Decomposition  decompositionTag(uint ucs4);

    static int  digitValue(uint ucs4);
    static int  digitValue(ushort ucs2);
    static uint  toLower(uint ucs4);
    static ushort  toLower(ushort ucs2);
    static uint  toUpper(uint ucs4);
    static ushort  toUpper(ushort ucs2);
    static uint  toTitleCase(uint ucs4);
    static ushort  toTitleCase(ushort ucs2);
    static uint  toCaseFolded(uint ucs4);
    static ushort  toCaseFolded(ushort ucs2);

private:
    ushort ucs;
};


inline WChar::WChar() : ucs(0) {}

inline WChar WChar::fromLatin1(char c) { return WChar(ushort(uchar(c))); }

inline WChar::WChar(uchar c, uchar r) : ucs(ushort((r << 8) | c)){}
inline WChar::WChar(short rc) : ucs(ushort(rc)){}
inline WChar::WChar(uint rc) : ucs(ushort(rc & 0xffff)){}
inline WChar::WChar(int rc) : ucs(ushort(rc & 0xffff)){}
inline WChar::WChar(SpecialCharacter s) : ucs(ushort(s)) {}

inline void WChar::setCell(uchar acell)
{ ucs = ushort((ucs & 0xff00) + acell); }
inline void WChar::setRow(uchar arow)
{ ucs = ushort((ushort(arow)<<8) + (ucs&0xff)); }

inline bool operator==(WChar c1, WChar c2) { return c1.unicode() == c2.unicode(); }
inline bool operator!=(WChar c1, WChar c2) { return c1.unicode() != c2.unicode(); }
inline bool operator<=(WChar c1, WChar c2) { return c1.unicode() <= c2.unicode(); }
inline bool operator>=(WChar c1, WChar c2) { return c1.unicode() >= c2.unicode(); }
inline bool operator<(WChar c1, WChar c2) { return c1.unicode() < c2.unicode(); }
inline bool operator>(WChar c1, WChar c2) { return c1.unicode() > c2.unicode(); }

#endif // 
