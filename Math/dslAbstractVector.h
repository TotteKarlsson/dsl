#ifndef dslAbstractVectorH
#define dslAbstractVectorH
#include "dslObject.h"
#include "dslUtils.h"
#include "dslMathExporter.h"

namespace dsl
{

using std::ostream;
using std::complex;

template <class T>
class dslAbstractVector : public DSLObject
{
    public:
		T*                                      vec; //Pointer to the array
                                                dslAbstractVector();
        virtual                                 ~dslAbstractVector() = 0;
        virtual T*                              operator()(void);
        T&                                      operator[](int index);
        T                                       Element(int i) const;
        T&                                      SetElement(int i);
        virtual int                             Size() const;
        virtual int                             Start() const;
        virtual int                             End() const {return mEndIndex;}
        virtual bool                            Resize(int newSize);
        virtual bool                            Create(int last);
        virtual bool                            Create(int first, int last);

	protected:
        bool                                    mIsArrayAllocated;
        int                                     mStartIndex;
        int                                     mEndIndex;
        bool                                    Allocate();
        T*                                      Allocate(int s, int last);
        void                                    DeAllocate();
        void                                    DeAllocate(T *v, int s);
};

ostream& operator<<(ostream &stream, dslAbstractVector< double > *out);
ostream& operator<<(ostream &stream, dslAbstractVector< double > &out);
ostream& operator<<(ostream &stream, dslAbstractVector< complex<double> > *out);
ostream& operator<<(ostream &stream, dslAbstractVector< complex<double> > &out);

template <class T>
dslAbstractVector<T>::dslAbstractVector()
{
    mIsArrayAllocated = false;
    mStartIndex = 0;
    mEndIndex = 0;
    vec = nullptr;
}

template <class T>
dslAbstractVector<T>::~dslAbstractVector(){}

template <class T>
inline T* dslAbstractVector<T>::operator()(void)
{
    return vec;
}

template <class T>
inline T& dslAbstractVector<T>::operator[](int index)
{
    /*** Access index ***/
    return *(vec + index);
}

template <class T>
T& dslAbstractVector<T>::SetElement(int i)
{
  return vec[i];
}

template <class T>
T dslAbstractVector<T>::Element(int i) const
{
    return vec[i];
}

//template <class T>
//T& dslAbstractVector<T>::Element(int i)
//{
//  return vec[i];
//}

template <class T>
inline int dslAbstractVector<T>::Size() const
{
    return (mEndIndex - mStartIndex) + 1;
}

template <class T>
inline int dslAbstractVector<T>::Start() const
{
    return mStartIndex;
}

template <class T>
bool dslAbstractVector<T>::Create(int last)
{
    if(mIsArrayAllocated == 1)
    {
        DeAllocate();
    }

    mStartIndex = 1;
    mEndIndex = last;
    return Allocate();
}

template <class T>
bool dslAbstractVector<T>::Create(int first, int last)
{
    if(mIsArrayAllocated == 1)
    {
        DeAllocate();
    }
    mStartIndex = first;
    mEndIndex = last;
    return Allocate();
}

template <class T>
bool dslAbstractVector<T>::Allocate()
{
    try
    {
        vec = new T[(mEndIndex -mStartIndex+2)];
        vec +=  (-mStartIndex+1);
        mIsArrayAllocated = true; //The array has been allocated memory succesfully
    }
    catch(...)
    {
        //    LogMessage("Could not allocate memory for a vector..");
        mIsArrayAllocated = false; //could not allocate the array
        return false;
    }
    return true;
}

template <class T>
T* dslAbstractVector<T>::Allocate(int s , int e)
{
    T *v;
    v = (T *) malloc((size_t) ((e - s +2)*sizeof(T)));
    if (!v)
    {
        return nullptr;
    }
    return  v-s+1;
}

template <class T>
void dslAbstractVector<T>::DeAllocate()
{
    if(mIsArrayAllocated)
    {
        vec += mStartIndex-1;
        delete[] vec;
        mIsArrayAllocated = false;
    }
}

template <class T>
void dslAbstractVector<T>::DeAllocate(T* v, int s)
{
    free((char*) (v+s-1));
}

template <class T>
bool dslAbstractVector<T>::Resize(int newSize)
{
    if(newSize == mEndIndex)
        return true;  // alrady the same size

    long oldSize = mEndIndex;
    T *tempvec =Allocate(1,oldSize);
    if(!tempvec)
    {
        return false;
    }
    for(long index = 1; index < mEndIndex + 1; index++)
    {
        tempvec[index] = vec[index];
    }

    DeAllocate();
    mEndIndex = newSize;
    if(!Allocate())
    {
        return false;
    }

    if(oldSize < newSize)
    {
        for(long index = 1; index < oldSize + 1; index++)
        {
            vec[index]=tempvec[index];
        }
    }

    if(oldSize > newSize)
    {
        for(long index = 1; index < newSize + 1; index++)
        {
            vec[index]=tempvec[index];
        }
    }
    DeAllocate(tempvec,1);
    return true;
}

}
#endif
