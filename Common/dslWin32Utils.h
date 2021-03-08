#ifndef dslWin32UtilsH
#define dslWin32UtilsH
#include "dslObject.h"
#include <windows.h>

namespace dsl
{

DSL_COMMON string   getDLLVersion(const string& dllname);

                    //!Wide string to std::string
DSL_COMMON string 	ws2s(const std::wstring& s);
DSL_COMMON string 	getClipBoardText();
DSL_COMMON void 	sendToClipBoard(const string& str);
DSL_COMMON string   getTempPath();
DSL_COMMON string 	getSpecialFolder(int fldr);
DSL_COMMON string 	getKnownFolder(GUID folder, DWORD flags = 0);
DSL_COMMON string 	getLastWin32Error();

DSL_COMMON void 	MouseClick(int x, int y);
DSL_COMMON bool 	clickOnWindow(const string& winCaption, int localX, int localY);

}
#endif
