#ifndef dslPointSetH
#define dslPointSetH
#include <string>
#include <vector>
#include "dslObject.h"
#include "dslMathExporter.h"
#include "dslPoint.h"

namespace dsl
{

using std::vector;
using std::string;

class DSL_MATH PointSet  : public DSLObject
{
	public:
                                                    PointSet(int NrOfPts = 0);
                                                    ~PointSet();
                                                    PointSet(const PointSet &In);

        PointSet&                                   operator=(const PointSet& rhs);
        void                                        clear();

        void                                        setNumberOfPoints(unsigned int nroftriplets);
        size_t                                      size() const ;
        size_t                                      count() const ;


        void                                        setPoint(int index, const Point& Point);

        void                                        insertNextPoint(const Point& Point);
        void                                        insertNextPoint(double X, double Y, double Z);

        void                                        setPoint(int index, double X, double Y, double Z);

        const Point&                                getPoint(int index) const;
        Point&                                      getPoint(int index);

        Point&                                      operator[](unsigned int i);
        const Point&                                operator[](unsigned int i) const;

        void                                        getPointSetFromFile(string &FileName);
        void                                        addPointSetFromFile(string &FileName);
        void                                        writePointSetToFile(string &FIleName);

	private:
        vector<Point>                               mPointSet;

};

typedef PointSet Points;

template<> inline
string Property<PointSet>::getValueAsString() const
{
    return "";
}

template<> inline
bool Property<PointSet>::write(IniFile* iniFile, const string& section)
{
    return false;
}

template<> inline
bool Property<PointSet>::read(IniFile* iniFile, const string& section)
{
    return false;
}

template<> inline
bool Property<PointSet>::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
string Property<PointSet>::getTypeName() const
{
    return "pointSet";
}

template<> inline
string getTypeAsString<PointSet>(const PointSet& obj)
{
    return "pointSet";
}

DSL_MATH string toString(const PointSet& ps);


}
#endif
