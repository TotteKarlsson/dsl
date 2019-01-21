#ifndef dslTogglerH
#define dslTogglerH
#include "dslObject.h"
#include <vector>
//---------------------------------------------------------------------------

namespace dsl
{
using std::vector;

class DSL_COMMON TogglerState
{
	public:
				TogglerState(const string& desc);
	string		mDescription;
};


class DSL_COMMON Toggler : public DSLObject
{
	public:
											Toggler();
		void					            insertState(const string& stateDescription);

		TogglerState 			            toggle();
		TogglerState						pokeNext();
		TogglerState						pokePrevious();
		TogglerState			            getCurrentState();
        bool                                isInState(const string& state);
        bool                                setState(const string& state);

	private:
		vector<TogglerState>	            mStates;
		vector<TogglerState>::iterator		mCurrentState;
};

}
#endif
