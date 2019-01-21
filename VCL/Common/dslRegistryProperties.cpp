#pragma hdrstop
#include <Registry.hpp>
#include "dslVCLUtils.h"
#include "dslRegistryProperties.h"
#include "dslLogger.h"
#include "dslColor.h"
#pragma package(smart_init)

namespace dsl
{

TRegistryProperties::TRegistryProperties(const string& registryRoot, const string& section)
:
Properties(section),
mRegistryRoot(registryRoot)
{}

TRegistryProperties::~TRegistryProperties()
{}

bool TRegistryProperties::doesSectionExist()
{
	std::auto_ptr<TRegIniFile> reg(new TRegIniFile(mRegistryRoot.c_str()));
	return reg->KeyExists( vclstr(joinPath(mRegistryRoot, mSectionName)) );
}

bool TRegistryProperties::read()
{
	std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));
	Property<bool>*     boolProp;
	Property<int>*      intProp;
	Property<Color>*    colorProp;
   	Property<string>*   stringProp;
	for(unsigned int i = 0; i < mProperties.size(); i++)
	{
		BaseProperty *para = mProperties[i];
		if(para)
		{
			ObjectType ot = para->getPropertyType();
			switch(ot)
			{
				case otBool:
					boolProp = dynamic_cast< Property<bool>* >(para);
					if(boolProp)
					{
						(*boolProp) = Registry->ReadBool(mSectionName.c_str(), para->getLabel().c_str(), boolProp->getDefaultValue());
					}
				break;

				case otInt:
					intProp = dynamic_cast< Property<int>* >(para);
					if(intProp)
					{
						(*intProp) = Registry->ReadInteger(mSectionName.c_str(), para->getLabel().c_str(), intProp->getDefaultValue());
					}
				break;

				case otColor:
					colorProp = dynamic_cast< Property<Color>* >(para);
					if(colorProp)
					{
						TColor theColor = (TColor) Registry->ReadInteger(mSectionName.c_str(), para->getLabel().c_str(), *( colorProp->getDefaultValue().getRGB()));

						DWORD  L = ColorToRGB(theColor);
						BYTE rgb[3] = { GetRValue(L), GetGValue(L), GetBValue(L) };

						(*colorProp).setValue(Color(rgb[0],rgb[1],rgb[2]));
					}
				break;

				case otStdString:
					stringProp = dynamic_cast< Property<string>* >(para);
					if(stringProp)
					{
                        string d = stringProp->getDefaultValue();
						String s =  Registry->ReadString(mSectionName.c_str(), para->getLabel().c_str(), d.c_str());
						(*stringProp).setValue(stdstr(s));
					}
				break;

				default:
					Log(lError) <<"Parameter "<<para->getLabel()<<" is not yet setup for reading";
				break;
			}
		}
	}
	return true;
}


bool TRegistryProperties::write()
{
    Log(lDebug3)<<"Writing registry section: "<<mSectionName;

    //Open the registry
    std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));

	Property<bool>*     boolProp;
	Property<int>*      intProp;
	Property<Color>*    colorProp;
   	Property<string>*   stringProp;

    for(unsigned int i = 0; i < mProperties.size(); i++)
    {
		BaseProperty *para = mProperties[i];
		if(!para)
		{
            continue;
        }
        ObjectType ot = para->getPropertyType();
        switch(ot)
        {
            case otBool:
                boolProp = dynamic_cast< Property<bool>* >(para);
                if(boolProp)
                {
                    //Writing a bool
                    Registry->WriteBool(mSectionName.c_str(), boolProp->getLabel().c_str(), boolProp->getValue());
                }
            break;

            case otInt:
                intProp = dynamic_cast<Property<int>*>(mProperties[i]);
                if(intProp)
                {
                    //Writing a color
                    int c = intProp->getValue();
                    Registry->WriteInteger(mSectionName.c_str(), intProp->getLabel().c_str(), c);
                }
            break;

            case otColor:
                colorProp = dynamic_cast<Property<Color>*>(mProperties[i]);
                if(colorProp)
                {
                    //Writing a color
                    Color cl = colorProp->getValue();
                    TColor aColor((TColor) RGB(cl[0], cl[1], cl[2]));
                    Registry->WriteInteger(mSectionName.c_str(), colorProp->getLabel().c_str(), aColor);
                }
            break;

            case otStdString:
                stringProp = dynamic_cast< Property<std::string>* >(mProperties[i]);
                if(stringProp)
                {
                    //Writing a string
                    string s = stringProp->getValue();
                    Registry->WriteString(mSectionName.c_str(), stringProp->getLabel().c_str(), s.c_str());
                }
            break;
        }
    }
    return true;
}

}

