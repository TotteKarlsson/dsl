#ifndef dslConstantsH
#define dslConstantsH
#include "dslCommonExporter.h"
#include <string>

//---------------------------------------------------------------------------

#if __cplusplus <= 199711L
  #define nullptr NULL
#endif

namespace dsl
{

using std::string;
typedef unsigned int uint;

//using namespace std;
DSL_COMMON extern const string gEmptyString;
DSL_COMMON extern const string gCommaSpace;
DSL_COMMON extern const string gUndefinedString;
DSL_COMMON extern const string gNoneString;
DSL_COMMON extern const string gPluginFolder;
DSL_COMMON extern const string gLocalHost;

DSL_COMMON extern const char   gPathSeparator;
DSL_COMMON extern const char   gTab;
DSL_COMMON extern const char   gEOL;
DSL_COMMON extern const char   gComma;
DSL_COMMON extern const char*  gDoubleFormat;
DSL_COMMON extern const char*  gIntFormat;

DSL_COMMON extern const double gMagicAngle;
DSL_COMMON extern const double gHBar;
DSL_COMMON extern const double gMynot;
DSL_COMMON extern const double gGammaCarbon;

//DSLEpsiolon is a arbitrary small number where we define a double being zero
DSL_COMMON extern const double gDSLEpsilon;

DSL_COMMON extern const double gPi;
DSL_COMMON extern const double gTwoPi;
DSL_COMMON extern const double gPiBy2;
DSL_COMMON extern const double gPiBy4;

/////////////////////////////////////////////////////////////////////////////////////////////
enum DATA_FORMAT {  dfMoleculix, dfInteger, dfDouble, dfComplex,
                    dfFree,
                    dfCMX,
                    dfVAX_ASCII,
                    dfSimpson,
                    dfMXQET,
                    dfUW,
                    dfSpinVision,
                    dfWinSpin,
                    dfFELIX,
                    dfXYZ,
                    dfMolecule,
                    dfPDB,
                    dfCML,
                    dfText,
                    dfNone,  //Questionable..
                    dfUnknown,
};

enum CASE_SENSITIVITY {csCaseSensitive, csCaseInsensitive};
enum DIMENSION {Dim1 = 0, Dim2, Dim3};

enum FILE_FORMAT {ffASCII, ffBINARY, ffUnkown};
enum FILEINOUT {mtkIn=0, mtkOut};
enum IMAGEFORMAT {mtkJPEG = 0, mtkPNM, mtkPS, mtkBMP, mtkTIFF};
enum DATA_DIMENSION {rowDimension, colDimension};//current dimensions
enum DATAPROJECTION {rowProjection, colProjection};//current projections
enum FRAMETRANSFORMATION {PASToCrystal, PASToRotor, PASToLab, CrystalToRotor, CrystalToLab, RotorToLab};

enum RFCHANNEL {HChannel, CChannel, NChannel, PChannel};
enum POWDERTYPE {singleXtal, randomOrientations, gridOrientations, orientationsFromFile, unknownType};

//Rendering, visual enums
enum SHOWDATAPART {sdpReal = 0, sdpImag, sdpMag, sdpAll}; //Bits..
enum IconSize {SIZE_16x16, SIZE_24x24, SIZE_32x32};
}
#endif
