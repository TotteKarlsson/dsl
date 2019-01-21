#pragma hdrstop
#include "dslGetRemoteTextFileDataThread.h"
#include <curl/curl.h>
#include <curl/easy.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace dsl
{

// Define our struct for accepting LCs output
struct RemoteData
{
    size_t  mSize;
    char*   mBuffer;
};

// This is the function we pass to LC, which writes the output to a RemoteData
static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    struct RemoteData* remoteData = (struct RemoteData *) data;
    remoteData->mBuffer = (char *) realloc(remoteData->mBuffer, remoteData->mSize + realsize + 1);

    if(remoteData->mBuffer )
    {
        memcpy( &( remoteData->mBuffer[ remoteData->mSize ] ), ptr, realsize );
        remoteData->mSize += realsize;
        remoteData->mBuffer[ remoteData->mSize ] = 0;
    }
    return realsize;
}

GetRemoteTextFileDataThread::GetRemoteTextFileDataThread(const string& url)
:
mCallBackFunction(nullptr),
mURL(url),
mRemoteTextData("")
{}

void GetRemoteTextFileDataThread::setURL(const string& url)
{
    mURL = url;
}

void GetRemoteTextFileDataThread::assignCallBack(TGetRemoteTextFileDataThreadCallBack cb)
{
    mCallBackFunction = cb;
}

void GetRemoteTextFileDataThread::run()
{
    if(mIsRunning)
    {
        //Log a warning..
        return;
    }

    mIsFinished = false;
    mIsRunning = true;

    curl_global_init(CURL_GLOBAL_ALL);

    struct RemoteData output;     // Create an instance of out RemoteData to accept LCs output
    output.mBuffer = nullptr;
    output.mSize = 0;
    CURL* myHandle = curl_easy_init();

    curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);     // Passing the function pointer to LC
    curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, (void *) &output);            // Passing our RemoteData to LC

    //Set remote URL
    curl_easy_setopt(myHandle, CURLOPT_URL, mURL.c_str());
    CURLcode result = curl_easy_perform(myHandle);
    curl_easy_cleanup(myHandle);

    mErrorData = curl_easy_strerror(result);
    if(output.mBuffer)
    {
        mRemoteTextData = output.mBuffer;
        free(output.mBuffer);
    }

    if(mCallBackFunction)
    {
        mCallBackFunction(mRemoteTextData);
    }

    mIsRunning = false;
    mIsFinished = true;
}

string GetRemoteTextFileDataThread::getErrorData()
{
    return mErrorData;
}

}

