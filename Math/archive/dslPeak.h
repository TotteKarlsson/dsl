#ifndef dslPeakH
#define dslPeakH
#include "Common/dslDSLObject.h"
#include "dslMathExporter.h"
#include "dslPoint.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_MATH Peak : public DSLObject
{
	public:
                                        Peak(Point origin, Point width) : mAmplitude(1){}
                                       ~Peak(){}
        string                          getLabel(){return mLabel;}
        void                            setLabel(const string& lbl){mLabel = lbl;}
        virtual double                  z(double x, double y) = 0;
        virtual void                    setAmplitude(double a = 0){mAmplitude = a;}
        virtual double                  getAmplitude(){return mAmplitude;}
        virtual void                    setOrigin(double x = 0, double y =0, double z = 0);
        virtual Point                   getOrigin(){return mOrigin;}
        virtual void                    setWidth(double x = 0, double y = 0, double z = 0);
        virtual Point                   getWidth(){return mWidth;}

	protected:
        double                          mAmplitude;
        string                          mLabel;
        Point                           mOrigin;        //The center of the peak
        Point                           mWidth;         //Width of peak
};

}
#endif
