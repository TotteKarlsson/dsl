#ifndef dslWin32UtilsH
#define dslWin32UtilsH
#include "dslObject.h"

namespace dsl
{
                    //!Wide string to std::string
DSL_COMMON string 	ws2s(const std::wstring& s);
DSL_COMMON string 	getClipBoardText();
DSL_COMMON void 	sendToClipBoard(const string& str);
DSL_COMMON string 	getSpecialFolder(int fldr);
DSL_COMMON string 	getLastWin32Error();

DSL_COMMON void 	MouseClick(int x, int y);
DSL_COMMON bool 	clickOnWindow(const string& winCaption, int localX, int localY);

}
#endif
