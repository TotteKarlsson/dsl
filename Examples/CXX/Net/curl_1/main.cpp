#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <string>
using namespace std;

// Define our struct for accepting LCs output
struct BufferStruct
{
    size_t size;
    char* buffer;
};

// This is the function we pass to LC, which writes the output to a BufferStruct
static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;

    struct BufferStruct* mem = (struct BufferStruct *) data;

    mem->buffer = (char *) realloc(mem->buffer, mem->size + realsize + 1);

    if(mem->buffer )
    {
        memcpy( &( mem->buffer[ mem->size ] ), ptr, realsize );
        mem->size += realsize;
        mem->buffer[ mem->size ] = 0;
    }
    return realsize;
}

int main()
{
    char* url = "http://www.moleculix.com/downloads/MoleculixDesktop/VERSION.txt";
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* myHandle;
    CURLcode result;                // We’ll store the result of CURL’s webpage retrieval, for simple error checking.
    struct BufferStruct output;     // Create an instance of out BufferStruct to accept LCs output
    output.buffer = nullptr;
    output.size = 0;
    myHandle = curl_easy_init();

    /* Notice the lack of major error checking, for brevity */
    curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); // Passing the function pointer to LC
    curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, (void *) &output);         // Passing our BufferStruct to LC

    curl_easy_setopt(myHandle, CURLOPT_URL, url);
    result = curl_easy_perform( myHandle );
    curl_easy_cleanup( myHandle );


    cout<<"Version is: "<<output.buffer;
    if(output.buffer )
    {
        free ( output.buffer );
    }

    printf("LibCurl rules!\n");
    return 0;
}

//
//
//#include <stdio.h>
//#include <curl/curl.h>
//#include <curl/easy.h>
//#include <string>
//
//#define CURL_STATICLIB
//size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
//{
//    size_t written;
//    written = fwrite(ptr, size, nmemb, stream);
//    return written;
//}
//
//using namespace std;
//int main(void)
//{
//    CURL *curl;
//    FILE *fp;
//    CURLcode res;
//    string url = "http://www.moleculix.com/downloads/MoleculixDesktop/VERSION.txt";
//    char outfilename[FILENAME_MAX] = "p:\\ver.txt";
//    curl = curl_easy_init();
//    if (curl)
//    {
//        fp = fopen(outfilename,"wb");
//        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
//        res = curl_easy_perform(curl);
//        curl_easy_cleanup(curl);
//        fclose(fp);
//    }
//
//    return 0;
//}

