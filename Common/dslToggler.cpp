#pragma hdrstop
#include "dslToggler.h"


namespace dsl
{
    typedef unsigned int uint;

TogglerState::TogglerState(const string& desc)
:
mDescription(desc)
{}

Toggler::Toggler(){}

bool Toggler::isInState(const string& state)
{
    return (state == getCurrentState().mDescription) ? true : false;
}

void Toggler::insertState(const string& stateDescription)
{
	mStates.push_back(TogglerState(stateDescription));
	mCurrentState = mStates.begin();
}

TogglerState Toggler::pokePrevious()
{
	vector<TogglerState>::iterator poker = mCurrentState;

	if(poker == mStates.begin())
	{
		poker = mStates.end() -1;
	}
	return *(poker);
}

TogglerState Toggler::pokeNext()
{
	vector<TogglerState>::iterator poker = mCurrentState;
	poker++;
	if(poker == mStates.end())
	{
		poker = mStates.begin();
	}
	return *(poker);
}

TogglerState Toggler::toggle()
{
	mCurrentState++;
	if(mCurrentState == mStates.end())
	{
		mCurrentState = mStates.begin();
	}
	return *mCurrentState;
}

bool Toggler::setState(const string& state)
{
    uint stateNr = 0;
    if(state == mCurrentState->mDescription)
    {
        return true;
    }
    else
    {
        do
        {
            toggle();

            if(state == mCurrentState->mDescription)
            {
                return true;
            }
            stateNr++;
        }while(stateNr < mStates.size());
    }
    return false;
}

TogglerState Toggler::getCurrentState()
{
	return *mCurrentState;
}

}
