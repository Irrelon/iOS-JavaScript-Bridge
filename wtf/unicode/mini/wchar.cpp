
#include "wchar.h"
#include "wunicodetables_p.h"

#define FLAG(x) (1 << (x))

bool WChar::isSpace() const
{
    if(ucs >= 9 && ucs <=13)
        return true;
    const int test = FLAG(Separator_Space) |
                     FLAG(Separator_Line) |
                     FLAG(Separator_Paragraph);
    return FLAG(wGetProp(ucs)->category) & test;
}

WChar::Category WChar::category(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return WChar::NoCategory;
    return (WChar::Category) wGetProp(ucs4)->category;
}

WChar::Category WChar::category(ushort ucs2)
{
    return (WChar::Category) wGetProp(ucs2)->category;
}


WChar::Direction WChar::direction() const
{
    return (WChar::Direction) wGetProp(ucs)->direction;
}

WChar::Direction WChar::direction(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return WChar::DirL;
    return (WChar::Direction) wGetProp(ucs4)->direction;
}

WChar::Direction WChar::direction(ushort ucs2)
{
    return (WChar::Direction) wGetProp(ucs2)->direction;
}


WChar WChar::toLower() const
{
    const WUnicodeTables::Properties *p = wGetProp(ucs);
    if (!p->lowerCaseSpecial)
        return ucs + p->lowerCaseDiff;
    return ucs;
}

uint WChar::toLower(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return ucs4;
    const WUnicodeTables::Properties *p = wGetProp(ucs4);
    if (!p->lowerCaseSpecial)
        return ucs4 + p->lowerCaseDiff;
    return ucs4;
}

ushort WChar::toLower(ushort ucs2)
{
    const WUnicodeTables::Properties *p = wGetProp(ucs2);
    if (!p->lowerCaseSpecial)
        return ucs2 + p->lowerCaseDiff;
    return ucs2;
}


WChar WChar::toUpper() const
{
    const WUnicodeTables::Properties *p = wGetProp(ucs);
    if (!p->upperCaseSpecial)
        return ucs + p->upperCaseDiff;
    return ucs;
}

uint WChar::toUpper(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return ucs4;
    const WUnicodeTables::Properties *p = wGetProp(ucs4);
    if (!p->upperCaseSpecial)
        return ucs4 + p->upperCaseDiff;
    return ucs4;
}

static inline uint foldCase(const ushort *ch, const ushort *start)
{
    uint c = *ch;
    if (WChar(c).isLowSurrogate() && ch > start && WChar(*(ch - 1)).isHighSurrogate())
        c = WChar::surrogateToUcs4(*(ch - 1), c);
    return *ch + wGetProp(c)->caseFoldDiff;
}

static inline uint foldCase(uint ch, uint &last)
{
    uint c = ch;
    if (WChar(c).isLowSurrogate() && WChar(last).isHighSurrogate())
        c = WChar::surrogateToUcs4(last, c);
    last = ch;
    return ch + wGetProp(c)->caseFoldDiff;
}

static inline ushort foldCase(ushort ch)
{
    return ch + wGetProp(ch)->caseFoldDiff;
}

WChar WChar::toCaseFolded() const
{
    return ucs + wGetProp(ucs)->caseFoldDiff;
}

uint WChar::toCaseFolded(uint ucs4)
{
    if (ucs4 > UNICODE_LAST_CODEPOINT)
        return ucs4;
    return ucs4 + wGetProp(ucs4)->caseFoldDiff;
}

ushort WChar::toCaseFolded(ushort ucs2)
{
    return ucs2 + wGetProp(ucs2)->caseFoldDiff;
}
