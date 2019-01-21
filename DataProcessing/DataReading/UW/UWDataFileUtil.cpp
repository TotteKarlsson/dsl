
#pragma hdrstop
// this code was written by Jim Gladden (dsl did some changes)
/*
 * UWDataFileUtil.c
 *
 *
 * The data file format is the following:
 *
 *      The data file is a binary file.
 *
 *      There are several sections in the data file as defined below.
 *      Each section begins with a leader composed of two 32 bit words:
 *              (number_of_bytes, section_type)
 *
 *      After each leader, the contents of the section are written to
 *      the data file.
 *
 *      The sections may be written in any order.
 *
 */


#include <time.h>
#include "string.h"
#include "UWDataFileUtil.h"

/*........ Local function prototypes ....................*/
static int         swapint(int in);
static double     swapdouble(double in);
static int         get_leader( FILE *data_file, int *size_ptr );
static int         find_section( FILE *data_file, int section_type, int dsn );

/*........ Functions ...........................*/
char* get_pulse_program( FILE *data_file, int *number_of_bytes )
{
    char * ptr;
    int bytes;

    bytes = find_section(data_file, PULSE_PROGRAM_SECTION, 0);
    if (bytes < 1) {
        fprintf(stderr, "\nError - failed to find pulse program section.\n");
        return (char*)0;

    }

    if ( (ptr = (char*) malloc(bytes)) == nullptr ) {
        fprintf(stderr, "\nError allocating space to read pulse program.\n");
        return (char*)0;
    }

    if ( (signed int)fread(ptr, sizeof(char), bytes, data_file) < bytes ) {
        fprintf(stderr,"\nError reading pulse program section.\n");
        return (char*)0;
    }

    *number_of_bytes = bytes;
    return ptr;
}

char* get_symbol_table(FILE *data_file, int *number_of_bytes )
{
    char * ptr;
    int bytes;

    bytes = find_section(data_file, SYMBOL_TABLE_SECTION, 0);
    if (bytes < 1) {
        fprintf(stderr, "\nError - failed to find symbol table section.\n");
        return (char*)0;

    }

    if ( (ptr =(char*) malloc(bytes)) == nullptr ) {
        fprintf(stderr, "\nError allocating space to read symbol table.\n");
        return (char*)0;
    }

    if ( (signed int)fread(ptr, sizeof(char), bytes, data_file) < bytes ) {
        fprintf(stderr,"\nError reading symbol table section.\n");
        return (char*)0;
    }

    *number_of_bytes = bytes;
    return ptr;
}

char* get_comments(FILE *data_file, int *number_of_bytes)
{
    char * ptr;
    int bytes;

    bytes = find_section(data_file, COMMENTS_SECTION, 0);
    if (bytes < 1) {
        fprintf(stderr, "\nError - failed to find comments section.\n");
        return (char*)0;

    }

    if ( (ptr =(char*) malloc(bytes)) == nullptr ) {
        fprintf(stderr, "\nError allocating space to read comments section.\n");
        return (char*)0;
    }

    if ( (signed int)fread(ptr, sizeof(char), bytes, data_file) < bytes ) {
        fprintf(stderr,"\nError reading comments section.\n");
        return (char*)0;
    }

    *number_of_bytes = bytes;
    return ptr;
}

//For MSVisual
//Original
//char * get_pp_name( std::FILE *data_file, int *number_of_bytes )
char* get_pp_name(FILE *data_file, int *number_of_bytes )
{
    char * ptr;
    int bytes;

    bytes = find_section(data_file, PP_NAME_SECTION, 0);
    if (bytes < 1) {
        fprintf(stderr, "\nError - failed to pp name section.\n");
        return (char*)0;

    }

    if ( (ptr =(char*) malloc(bytes + 1)) == nullptr ) {
        fprintf(stderr, "\nError allocating space to read pp name section.\n");
        return (char*)0;
    }

    if ( (signed int)fread(ptr, sizeof(char), bytes, data_file) < bytes ) {
        fprintf(stderr,"\nError reading pp name section.\n");
        return (char*)0;
    }

    ptr[bytes] = 0;

    *number_of_bytes = bytes;
    return ptr;
}


COMPLEX_INT* get_data( FILE *data_file, int *number_of_bytes, int section_number )
{
    COMPLEX_INT * ptr;
    int bytes, i;

    bytes = find_section(data_file, DATA_SECTION, section_number);
    if (bytes < 1) {
        //fprintf(stderr, "\nError - failed to find data section.\n");
        return (COMPLEX_INT*)0;
    }

    if ( (ptr =(complex_int_tag*) malloc(bytes)) == nullptr ) {
        fprintf(stderr, "\nError allocating space to data section.\n");
        return (COMPLEX_INT*)0;
    }

    if ( (signed int)fread(ptr, sizeof(char), bytes, data_file) < bytes ) {
        fprintf(stderr,"\nError reading data section.\n");
        return (COMPLEX_INT*)0;
    }

    for (i = 0; i < (bytes/(int)sizeof(COMPLEX_INT)); ++i) {
        ptr[i].real = swapint(ptr[i].real);
        ptr[i].imag = swapint(ptr[i].imag);
    }
    
    *number_of_bytes = bytes;
    return ptr;
}

GLOBAL_SYMBOLS* get_global_symbols(FILE *data_file, int *number_of_bytes)
{
    GLOBAL_SYMBOLS* ptr;
    int bytes;

    bytes = find_section(data_file, GLOBAL_SYMBOLS_SECTION, 0);
    if (bytes < 1) {
        fprintf(stderr, "\nError - failed to find global symbols section.\n");
        return (GLOBAL_SYMBOLS*)0;

    }

    if ( (ptr =(global_symbols_tag*) malloc(bytes)) == nullptr ) {
        fprintf(stderr, "\nError allocating space to read global symbols section.\n");
        return (GLOBAL_SYMBOLS*)0;
    }

    if ( (signed int)fread(ptr, sizeof(char), bytes, data_file) < bytes ) {
        fprintf(stderr,"\nError global symbols section.\n");
        return (GLOBAL_SYMBOLS*)0;
    }

    ptr->sw = swapdouble(ptr->sw);
    ptr->sf1 = swapdouble(ptr->sf1);
    ptr->sf2 = swapdouble(ptr->sf2);
    ptr->sf3 = swapdouble(ptr->sf3);
    ptr->size = swapdouble(ptr->size);
    ptr->scans = swapdouble(ptr->scans);
    ptr->experiment = swapdouble(ptr->experiment);

    *number_of_bytes = bytes;
    return ptr;
}

char* get_time( FILE *data_file, int *number_of_bytes )
{
    char * ptr;
    int bytes;
    time_t then;

    bytes = find_section(data_file, TIME_SECTION, 0);
    if (bytes < 1) {
        fprintf(stderr, "\nError - failed to find time section.\n");
        return (char*)0;

    }

    if ( (signed int)fread(&then, sizeof(char), bytes, data_file) < bytes ) {
        fprintf(stderr,"\nError reading time section.\n");
        return (char*)0;
    }

    if ( (ptr =(char*) malloc(100)) == nullptr ) {
        fprintf(stderr, "\nError allocating space to transalate time section.\n");
        return (char*)0;
    }

    then = swapint(then);

    strftime(ptr, 100, "%H:%M:%S %A %b %d, %Y", localtime(&then));

    *number_of_bytes = strlen(ptr);
    return ptr;
}

/*...............Local Functions................*/


/*
 * Read the section leader, fill in the size and return the section type.
 * Argument 'size_ptr' returns the number of bytes in the section.
 */
static int get_leader(FILE *data_file, int *size_ptr)
{
    int section_type;

    if ( fread(size_ptr, sizeof(int), 1, data_file) < 1 )
    {
        if ( feof(data_file) != 0 )
            return uw_EOF;
        else {
            printf("\nError reading leader size.\n");
            return uwERROR;
        }
    }

    *size_ptr = swapint(* size_ptr);

    if ( fread(&section_type, sizeof(int), 1, data_file) < 1 )
    {
        printf("\nError reading leader type.\n");
        return uwERROR;
    }

    return swapint(section_type);
}


/*
 * Position the file pointer to point to the first section of the desired type
 * and return the size.  If a DATA_SECTION is requested then the 'dsn' argument
 * specifies which section in a file with multiple data sections.
 */
static int find_section( FILE *data_file, int section_type, int dsn )
{
    int temp_type, num_bytes, current_dsn = 0;

/*    Position to the beginning of the file */
    if ( fseek( data_file, 0L, SEEK_SET) != 0 ) {
        fprintf(stderr,"\nError with fseek:  SEEK_SET.\n");
        return uwERROR;
    }

/*    Loop until we find the write section */
    for( ; ; ) {
        temp_type = get_leader(data_file, &num_bytes);

         if (temp_type == uw_EOF) {
            printf("\nSection type %d not found.", section_type );
            return uwERROR;
        } else if (temp_type == uwERROR) {
            printf("\nError searching for section type %d.",
                     section_type );
            return uwERROR;

        }

/*        Is this the requested type of section section? */
        if ( section_type == temp_type ) {

/*            If the request was for a data section then it has to be the right
            one.  Otherwise just bump the section count and keep looking. */
            if ( section_type == DATA_SECTION ) {
                if (dsn == current_dsn) {
                    return num_bytes;
                } else {
                    ++current_dsn;
                }
            } else {
                return num_bytes;
            }
        }


/*        Skip to the next section */
           if ( fseek( data_file, num_bytes, SEEK_CUR) != 0 ) {
            fprintf(stderr,"\nError with fseek:  SEEK_CUR.\n");
            return uwERROR;
        }
    }

//dsl changed.. below is unreachable code. Commented that out
//    printf("\nSection type %d not found.", section_type );
//    return uwERROR;
}

/*
 * Functions to swap the bytes for converting endian type.
 */
static int swapint(int in)
{
    int out;

    *(((char *) &out) + 0) = *(((char *) &in) + 3);
    *(((char *) &out) + 1) = *(((char *) &in) + 2);
    *(((char *) &out) + 2) = *(((char *) &in) + 1);
    *(((char *) &out) + 3) = *(((char *) &in) + 0);

    return out;
}

static double swapdouble(double in)
{
    double out;

    *(((char *) &out) + 0) = *(((char *) &in) + 7);
    *(((char *) &out) + 1) = *(((char *) &in) + 6);
    *(((char *) &out) + 2) = *(((char *) &in) + 5);
    *(((char *) &out) + 3) = *(((char *) &in) + 4);
    *(((char *) &out) + 4) = *(((char *) &in) + 3);
    *(((char *) &out) + 5) = *(((char *) &in) + 2);
    *(((char *) &out) + 6) = *(((char *) &in) + 1);
    *(((char *) &out) + 7) = *(((char *) &in) + 0);

    return out;
}
