//---------------------------------------------------------------------------
#ifndef dslProcessInfoH
#define dslProcessInfoH
//---------------------------------------------------------------------------
#include <string>
#include <Forms.hpp>
#include <windows.h>
#include "dslObject.h"
#include "VCLCommonExporter.h"
using std::string;

bool VCL_COMMON TerminateProcess(const int& pid);

class VCL_COMMON mtkProcessInfo : dsl::DSLObject
{
    private:
        DWORD mProcessID;
        DWORD mParentProcessID;
        DWORD mStartedThreads;
        LONG  mThreadBasePriority;
        string mProgramName;

    public:
        mtkProcessInfo()
        {}
        void    SetProcessID(const int& id){mProcessID = id;}
        DWORD   GetProcessID() const {return mProcessID;}
        void    SetParentProcessID(const int& id){mParentProcessID = id;}
        void    SetProgramName(const string& name){mProgramName = name;}
        string  GetProgramName() const {return mProgramName;}

        bool    Terminate();
        bool    ShutDown();
           bool     operator == (const mtkProcessInfo &x)const{return x.mProcessID == mProcessID;}
};

template < class Type>
class Compare
{
public:
    virtual int equal(const Type &, const Type&)const=0;
    virtual int greaterThan(const Type &, const Type&)const = 0;
};

class ProcessNameCompare : public Compare<mtkProcessInfo>
{
public:
    virtual int equal(const mtkProcessInfo &x, const mtkProcessInfo&y)const
        {return x.GetProgramName() == y.GetProgramName();}

    virtual int greaterThan(const mtkProcessInfo &x, const mtkProcessInfo&y)const
        {return x.GetProgramName() > y.GetProgramName();}
};

class ProcessIdCompare :public Compare<mtkProcessInfo>
{
public:
    virtual int equal(const mtkProcessInfo &x, const mtkProcessInfo&y)const
        {return x.GetProcessID() == y.GetProcessID();}
    virtual int greaterThan(const mtkProcessInfo &x, const mtkProcessInfo&y)const
        {return x.GetProcessID() > y.GetProcessID();}
};


#endif
