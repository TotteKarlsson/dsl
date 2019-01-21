#ifndef TFileSelectionFrameH
#define TFileSelectionFrameH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include "dslProperty.h"
#include <System.Actions.hpp>
//#include <System.Actions.hpp>
#include <list>
#include "DuneComponents.h"

using std::list;
using std::pair;
using std::string;
using std::vector;
class mtkFileSystemItem;
//---------------------------------------------------------------------------
class PACKAGE TFileSelectionFrame : public TFrame
{
__published:    // IDE-managed Components
    TPanel *MainPanel;
    TImageList *ImageListTreeViewIcons;
    TToolBar *FSToolBar;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TToolButton *ToolButton7;
    TTreeView *TreeViewUndo;
    TTreeView *TreeViewRedo;
    TPopupMenu *FTPopup;
    TActionList *FTActionList;
    TAction *ActionNodeAddFile;
    TAction *DeleteFileA;
    TAction *ActionNodeModify;
    TAction *ActionFileOpen;
    TAction *ActionNodeMoveUp;
    TAction *ActionNodeMoveDown;
    TAction *ActionNodeFindLabel;
    TAction *ActionNodeAddData;
    TAction *ActionNodeFindID;
    TAction *ActionNodeDeleteSoft;
    TAction *ActionEditUndo;
    TAction *ActionEditRedo;
    TAction *ActionFileClear;
    TAction *ActionEditRefresh;
    TAction *ActionTreeExpand;
    TAction *ActionTreeCollapse;
    TTreeView *TreeView1;
    TAction *ReScanDataFolderA;
    TAction *RefreshFolder;
    TToolButton *ToolButton1;
    TMenuItem *Delete1;
    void __fastcall ActionNodeModifyExecute(TObject *Sender);
    void __fastcall TreeView1Click(TObject *Sender);
    void __fastcall ActionFileClearExecute(TObject *Sender);
    void __fastcall ActionNodeAddFileExecute(TObject *Sender);
    void __fastcall DeleteFileAExecute(TObject *Sender);
    void __fastcall ActionNodeMoveUpExecute(TObject *Sender);
    void __fastcall ActionNodeMoveDownExecute(TObject *Sender);
    void __fastcall ActionNodeFindLabelExecute(TObject *Sender);
    void __fastcall ActionNodeDeleteSoftExecute(TObject *Sender);
    void __fastcall ActionTreeExpandExecute(TObject *Sender);
    void __fastcall ActionTreeCollapseExecute(TObject *Sender);
    void __fastcall ActionEditUndoExecute(TObject *Sender);
    void __fastcall ActionEditRedoExecute(TObject *Sender);
    void __fastcall ActionEditRefreshExecute(TObject *Sender);
    void __fastcall ReScanDataFolderAExecute(TObject *Sender);
    void __fastcall RefreshFolderExecute(TObject *Sender);
    void __fastcall TreeView1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
    void __fastcall TreeView1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall TreeView1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
//    void __fastcall TreeView1DblClick(TObject *Sender);
//    void __fastcall FrameDblClick(TObject *Sender);

    private:
        list<std::string>                              mExcludeDirs;
        TTreeNode*                                     mNodeToRemember;
        vector< pair<string, string > >                mFileRootAndExtentions;

        bool                        __fastcall         ScanDataFolder(const string& path, const string& extensions);
        void                        __fastcall         FindFilesInDirectory(const string &directory, const string& Extension, TTreeNode* parent);
        TTreeNode*                  __fastcall         AddFolder(const string& folder, const string& parentPath, TTreeNode* parent = nullptr, const bool& isRoot = false);
        TTreeNode*                  __fastcall         AddFile(const string& file, const string& parentPath, TTreeNode* parent);
        void                        __fastcall         ReflectNodeLabel(TTreeNode* node);
        bool                        __fastcall         InExcludeList(const string& fldr);
        void                        __fastcall         SetupNode(TTreeNode* tempNode, mtkFileSystemItem* fInfo);
        void                        __fastcall         RemoveFileItems(TTreeNode* aNode);

    public:
        TMemo*                                         mAMemo;
                                    __fastcall         TFileSelectionFrame(TComponent* Owner);
        virtual                     __fastcall         ~TFileSelectionFrame();

        void                        __fastcall         ClearTree();
        void                        __fastcall         CreateTree();
        TTreeNode*                  __fastcall         InTree(const string& fName, TTreeNode* parentFolder);
        bool                        __fastcall         MonitorFolder(const string& fldr, const string& extensions);
        bool                        __fastcall         RemoveMonitoredFolders();
        TTreeNode*                  __fastcall         GetSelected();
        string                      __fastcall         GetSelectedFileInTree();
        mtkFileSystemItem*          __fastcall         GetSelectedFileSystemTreeItem();
};

extern PACKAGE TFileSelectionFrame *FileSelectionFrame;
#endif
