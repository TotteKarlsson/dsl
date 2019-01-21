#ifndef dslAxesH
#define dslAxesH
#include "dslVector.h"
#include "DataExporter.h"

namespace dsl
{

using std::string;
class MTK_DATA mtkAxes : public mtkVector<double>
{
    public:
                                                    mtkAxes(int Size = 1);
                                                    ~mtkAxes();

		mtkAxes&                                    operator = (const mtkAxes &rightVec);

        void                                        Fill();
		void                                        ReFill();
		int                                         GetAxisIndexAtAxisValue(double AxisValue);
        double                                      GetIncrement();
        void                                        SetOffset(double Value);
        double                                      GetOffset();
        void                                        SetIncrement(double Value);
        double                                      GetMax();
        double                                      GetMin();
        void                                        SetNormalized();
        void                                        SetAxis(double mOffset, double incrementValue);
        void                                        SetAxis(mtkAxes* NewAxis);
        mtkAxes*                                    GetAxis()                    {return this;}
        void                                        SetSW(double Value)    {mSW = Value;}
        double                                      GetSW()                        {return mSW;}
        void                                        SetLabel(const char *Text);
        string                                      GetLabel()                    {return mLabel;}
        void                                        Cut(int Start, int End);

        /*** Output Functions ***/
        void                                        SaveToFile(const char* fileName);

        /*** Diverse ***/
        void                                        Update();
        bool                                        IsEvenlySpaced(){return mIsEvenlySpaced;}

        //Friends
        MTK_DATA friend std::ostream&               operator<<(std::ostream &stream, mtkAxes &out);

    protected:
        bool                                        mIsEvenlySpaced;
        string                                      mLabel;
        double                                      mIncrement;
        double                                      mOffset;
        double                                      mSW;
};

}
#endif
