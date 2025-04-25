#pragma once

#include "IDetailCustomization.h"
#include "IPropertyTypeCustomization.h"
#include "BeamFlow/K2BeamNode_EventRegister.h"

class UK2BeamEventRegisterCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	void GenerateDelegateCheckboxes(IDetailLayoutBuilder& DetailBuilder, UK2BeamNode_EventRegister* Node);
};
