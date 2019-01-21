#pragma hdrstop
#include <stdio.h>
#include <string.h>
#include "dslGetOptions.h"
#include "dslConstants.h"

//---------------------------------------------------------------------------

namespace dsl
{

char    *optarg;        	// global argument pointer
int        optind = 0;     	// global argv index

int getOptions(int argc, char *argv[], char *optstring)
{
    static char *next = nullptr;
    if (optind == 0)
        next = nullptr;

    optarg = nullptr;

    if (next == nullptr || *next == wchar_t('\0'))
    {
        if (optind == 0)
            optind++;
        if (optind >= argc || argv[optind][0] != wchar_t('-') || argv[optind][1] == wchar_t('\0'))
        {
            optarg = nullptr;
            if (optind < argc)
                optarg = argv[optind];
            return EOF;
        }
        if (strcmp(argv[optind], ("--")) == 0)
        {
            optind++;
            optarg = nullptr;
            if (optind < argc)
                optarg = argv[optind];
            return EOF;
        }
        next = argv[optind];
        next++;        // skip past -
        optind++;
    }

    char c = *next++;
    char *cp = strchr(optstring, c);

    if (cp == nullptr || c == wchar_t(':'))
        return wchar_t('?');

    cp++;
    if (*cp == wchar_t(':'))
    {
        if (*next != wchar_t('\0'))
        {
            optarg = next;
            next = nullptr;
        }
        else if (optind < argc)
        {
            optarg = argv[optind];
            optind++;
        }
        else
        {
            return wchar_t('?');
        }
    }
    return c;
}

}