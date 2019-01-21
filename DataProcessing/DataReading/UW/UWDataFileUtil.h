#ifndef UWDataFileUtilH
#define UWDataFileUtilH

// this code was written by Jim Gladden (mtk did some changes)
/*
 * UWDataFileUtil.h
 *
 *
 * The data file format is the following:
 *
 *    The data file is a binary file.
 *
 *     There are up to 7 sections in the data file as defined below.
 *    Each section begins with a leader composed of two words:
 *        (number_of_bytes, section_type)
 *
 *    After each leader, the contents of the section are written to
 *    the data file.
 *
 *    The sections may be written in any order.
 *
 *    NB_    The contents of the time section is of type time_t.
 *        See the time(2) man page.
 *
 */

/*........    Includes    ....................*/
#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include "DataExporter.h"

/*........    Defines    ....................*/
#define uw_EOF (-1)
#define uwERROR (-2)

/* Define the different sections in the data file */
enum {
    END_OF_FILE,
    TIME_SECTION,
    SYMBOL_TABLE_SECTION,
    PULSE_PROGRAM_SECTION,
    COMMENTS_SECTION,
    GLOBAL_SYMBOLS_SECTION,
    DATA_SECTION,
    TERMINATION_STATUS_SECTION,
    USER_SECTION,
    PP_NAME_SECTION
};

/*........ Typedefs ....................*/
typedef struct global_symbols_tag {
    double sw;
    double sf1;
    double sf2;
    double sf3;
    double size;
    double scans;
    double experiment;
} GLOBAL_SYMBOLS;

typedef struct complex_int_tag {
    int real;
    int imag;
} COMPLEX_INT;

/*........ Function Declarations ....................*/
char*             MTK_DATA get_pulse_program(FILE *data_file, int *number_of_bytes);
char*             MTK_DATA get_symbol_table(FILE *data_file, int *number_of_bytes);
char*             MTK_DATA get_comments(FILE *data_file, int *number_of_bytes);
char*             MTK_DATA get_pp_name(FILE *data_file, int *number_of_bytes);
COMPLEX_INT*     MTK_DATA get_data(FILE *data_file, int *number_of_bytes, int section_number);
GLOBAL_SYMBOLS* MTK_DATA get_global_symbols(FILE *data_file, int *number_of_bytes);
char*             MTK_DATA get_time(FILE *data_file, int *number_of_bytes);

#endif
