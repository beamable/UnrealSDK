#pragma once

#include "IDetailCustomization.h"
#include "IPropertyTypeCustomization.h"
#include "BeamFlow/K2BeamNode_EventRegister.h"

class UK2BeamNode_EventUnregister;

class UK2BeamEventUnregisterCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	void GenerateHiddenDelegateCheckboxes(IDetailLayoutBuilder& DetailBuilder, UK2BeamNode_EventUnregister* Node);
};
