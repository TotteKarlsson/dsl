#ifndef dslTMemoLoggerH
#define dslTMemoLoggerH
#include <Vcl.StdCtrls.hpp>
#include <sstream>
#include "dslVCLCommonExporter.h"

//Minimalistic logger to a memo...
class VCLCOMMON TMemoLogger
{
    public:
                                    TMemoLogger(TMemo* aMemo);
        virtual                     ~TMemoLogger();
        std::ostringstream&         get();
        static bool                 mMemoIsEnabled;

    protected:
        std::ostringstream          mStream;
        TMemo*                      mMemo;
};

#define MLog() \
    TMemoLogger(infoMemo).get()
#endif
