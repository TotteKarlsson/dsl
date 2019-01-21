#ifndef dslTPluginManagerH
#define dslTPluginManagerH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <ActnMan.hpp>
#include <ActnList.hpp>
#include <ActnCtrls.hpp>
#include <ActnMenus.hpp>
#include <vector>
#include "dslPlugin.h"
#include "dslComponentsPackageDefs.h"
#include "dslConstants.h"
#include "dslStringList.h"
#include "dslPluginManager.h"

using std::vector;
using dsl::IconSize;
using dsl::Plugin;
using dsl::StringList;
//---------------------------------------------------------------------------
typedef Plugin* (*DLLPROCADDRESS)(HWND);
typedef void __fastcall (__closure *StartLoadEvent)		(TObject* Sender,   String PluginName, bool &AllowLoad);
typedef void __fastcall (__closure *FinishedLoadEvent)	(TObject* Sender, 	String PluginName, HICON PluginGlyph);
typedef void __fastcall (__closure *UpdateVisualEvent)	(TObject* Sender);

class PACKAGE TPluginManager : public TComponent
{
	__published:
		__property String 				PluginExtension      = {read=getPluginExtension, 		write=setPluginExtension};
		__property FinishedLoadEvent 	OnFinishedLoading    = {read=FOnFinishedLoadEvent,      write=FOnFinishedLoadEvent};
		__property UpdateVisualEvent 	OnUpdateVisual       = {read=FOnUpdateVisualEvent,      write=FOnUpdateVisualEvent};
		__property String 				Version              = {read=getPluginManagerVersion,   write=setPluginManagerVersion};
		__property String 				PluginFolder         = {read=getPluginFolder,           write=setPluginFolder};
		__property StartLoadEvent 		OnStartLoading       = {read=FOnStartLoadEvent,         write=FOnStartLoadEvent};
//		__property TActionManager* 		ActionManager        = {read=GetActionManager,          write=SetActionManager};
		__property String 				Caption              = {read=getCaption,                write=setCaption};
		__property int 					GroupIndex           = {read=getGroupIndex,             write=setGroupIndex};
		__property TStatusBar* 			StatusBar		  	 = {read=getStatusBar,    			write=setStatusBar};

	public:
                                                //!Low level plugin manager
        dsl::PluginManager                 	 	mPM;

									__fastcall 	TPluginManager(TComponent* Owner);
		virtual						__fastcall 	~TPluginManager();
		int									 	getNumberOfPlugins(){return mPM.getNumberOfPlugins();}
		void								 	setup();					//!Initial setup of the manager

		virtual Plugin* 			           	getPlugin(const string& pluginName);
		virtual Plugin*    			            getPlugin(int i);
		Plugin* 					            loadPlugin(const string& fName);
		int 						            loadPlugins();
		bool						            unLoadPlugin(int index);
		bool						            unLoadPlugin(const string& plugin);
		bool						            unLoadAllPlugins();

		StringList					            getLoadedPluginsNames();
		StringList					            getLoadedPluginLibsFileNames();
		string 						            getLastLoadedPluginName();
		void						            unLoadPluginGroups();

		void						            setupMainMenuActionList(IconSize size);
		void						            setupToolBarActionList(IconSize size);
		bool 						            setupActionLists();

		TActionList*				            getMainMenuActionList(){return mMainMenuActionList;}
		TActionList*				            getToolBarActionList(){return mToolBarActionList;}
		string 						            getMainMenuCategory(int index);
		StringList					            getMainMenuCategories(){return mMainMenuCategories;}

		__property Plugin* 		Plugins[int Index] 	= {read=getPlugin};

	protected:
		int 						          	FGroupIndex;
		FinishedLoadEvent 			            FOnFinishedLoadEvent;
		StartLoadEvent 				            FOnStartLoadEvent;
		UpdateVisualEvent 			            FOnUpdateVisualEvent;
		String                    	            FCaption;
		String                    	            FPluginExtension;
		String                    	            FPluginFolder;
		String                   	            FPluginManagerVersion;
		TApplication*                           FApplication;

                                                //! UI stuff
		TMenuItem*					            mTopMenuItem;
		TActionList*				            mMainMenuActionList;
		TActionList*				            mToolBarActionList;
		TStatusBar*        	                    FStatusBar;				//Assign to plugins

		TCustomImageList*			            mMainMenuIcons;			//!16x16 icons
		TCustomImageList*			            mToolBarIcons;        	//!24x24 icons

		StringList					            mMainMenuCategories;	//!Holds main menu action categories
		string								    getPluginPath();

										    	// MAIN MENU STUFF
		void 						            setIconListSize(IconSize iconSize, TCustomImageList* imageList);
		bool						            addMainMenuCategory(const string& category);
		int 						            getPluginCount();
		virtual void               __fastcall   setGroupIndex(int index){FGroupIndex = index;}
		virtual int                __fastcall   getGroupIndex(){return FGroupIndex;}

                                                // Misc
		virtual void               __fastcall   setPluginExtension(String value);
		virtual String             __fastcall   getPluginExtension(){return FPluginExtension;}
		virtual String             __fastcall   getPluginFolder(){return FPluginFolder;}
		virtual void               __fastcall   setPluginFolder(String aFolder){FPluginFolder =  aFolder;}
		String                     __fastcall   getPluginManagerVersion(){return FPluginManagerVersion;}
		void                       __fastcall   setPluginManagerVersion(String aVersion){FPluginManagerVersion = aVersion;}

                                                // Events
		virtual void                            fireStartLoadEvent(String PluginName, bool & CanLoad);
		virtual void                            fireFinishedLoadEvent(String PluginName,	HICON PluginGlyph);

									            // MENU
		virtual String             __fastcall   getCaption(){return FCaption;}
		virtual void               __fastcall   setCaption(String aCaption){FCaption = aCaption;}
		bool						            checkPluginDirectory();

									            // STATUS BAR
		virtual TStatusBar* 	   __fastcall	getStatusBar(){return FStatusBar;}
		virtual void               __fastcall   setStatusBar(TStatusBar* aBar){FStatusBar = aBar;}
};
#endif
