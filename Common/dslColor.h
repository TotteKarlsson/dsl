#ifndef dslColorH
#define dslColorH
#include "dslObject.h"
#include "dslCommonExporter.h"
#include "dslConstants.h"
#include "dslProperty.h"

namespace dsl
{

enum COLOR
{
    Black,
    White,
    Red,
    Green,
    SpringGreen,
    MediumSeaGreen,
    Blue,
    SkyBlue,
    Pink,
    Yellow,
    Grey,
    Brown,
    Purple,
    Cyan,
    Orange,
    Salmon,
    Violet,
    Undefined
};

//Class representing ONE color at a time
//Observe, only a few color enums are defined while RGB's can take any values

//use 0-255 range
class DSL_COMMON Color : public DSLObject
{
      public:
                                        Color(int r = 0, int g = 0, int b = 0);
                                        Color(COLOR);
        virtual                         ~Color();
        void                            setRGB(int r, int g, int b);
//        void                            setRGB(COLOR color);
        int*                            getRGB();
        double*                         getDoubleRGB();
        COLOR                           getColor();
        const int                       operator[](int index) const;
        int&                            operator[](int index);

        string                          getTypeName() const;

    private:
        int                             mRGB[3];
        COLOR                           mColor;
        void                            toRGB(COLOR color);
};

DSL_COMMON COLOR                      toColor(const string& s);
DSL_COMMON int*                       toRGB(COLOR clr);
DSL_COMMON string                     toString(const Color& c);


template<>
inline Property<Color>::operator Color () const
{
    return (*mValue);
}

template<> inline
string Property<Color>::getValueAsString() const
{
    return "";
}

template<> inline
bool Property<Color>::write(IniFile* iniFile, const string& section)
{
    return false;
}

template<> inline
bool Property<Color>::read(IniFile* iniFile, const string& section)
{
    return false;
}

template<> inline
bool Property<Color>::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
string Property<Color>::getTypeName() const
{
    return "color";
}

template<> inline
ObjectType Property<Color>::getPropertyType()
{
    return otColor;
}


}
#endif
