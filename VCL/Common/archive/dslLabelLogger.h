#ifndef dslLabelLoggerH
#define dslLabelLoggerH
#include <Vcl.StdCtrls.hpp>
#include <sstream>
#include "dslObject.h"


//Minimalistic logger to a label.
class PACKAGE LabelLogger : public dsl::DSLObject
{
    protected:
        std::ostringstream          mStream;
        static TLabel*				mLogLabel;

    public:
                                    LabelLogger(TLabel* aLabel = nullptr);
        virtual                     ~LabelLogger();
        std::ostringstream&         Get();
};

#define LL \
    LabelLogger(logLabel).Get()

#define LLE \
    LabelLogger().Get()
#endif
