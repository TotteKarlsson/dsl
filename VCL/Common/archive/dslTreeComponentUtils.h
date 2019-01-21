#ifndef dslTreeComponentUtilsH
#define dslTreeComponentUtilsH

#include <vcl.h>
#include <VCL.ComCtrls.hpp>
#include <string>

class mtkTreeItemBase;

using std::string;
void            __fastcall PACKAGE MoveUpTree(TTreeNode *item);
TTreeNode*      __fastcall PACKAGE FindTreeNodeBasedOnLabel(TTreeNodes* Tree, const String& Label);  // returns the node if found, nullptr otherwise
TTreeNode*      __fastcall PACKAGE FindTreeNodeBasedOnID(TTreeNodes *Tree,unsigned int ID);
TTreeNode*      __fastcall PACKAGE FindTreeFolderNodeBasedOnFullPath(TTreeNodes* Tree, const String& path);  // returns the node if found, nullptr otherwise
void            __fastcall PACKAGE AddCountToNode(TTreeNodes* tree);
bool            __fastcall PACKAGE StripParenCount(String& text);
bool            __fastcall PACKAGE AddToUndoRedoList(TTreeNodes * Tree, unsigned int ID, mtkTreeItemBase *info, int imageindex, bool deletedflag);
void            __fastcall PACKAGE ClearAll(TTreeNodes* tree);
void            __fastcall PACKAGE ClearDeletedItems(TTreeNodes* tree);
TTreeNode*      __fastcall PACKAGE DeleteNode(TTreeNode *node, bool displaymessage = true, bool soft = true, TTreeNodes * undolist = nullptr);
void            __fastcall PACKAGE UndeleteNode(TTreeNode *node);
unsigned int    __fastcall PACKAGE GetNewID();
#endif
