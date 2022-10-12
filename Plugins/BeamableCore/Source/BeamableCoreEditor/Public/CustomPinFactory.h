#pragma once


#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "SlateBasics.h"
#include "SRequestTypePin.h"
#include "SUserSlotPin.h"
#include "BeamCoreTypes.h"
#include "UserSlots/UserSlot.h"

class BEAMABLECOREEDITOR_API FCustomPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override
	{
		const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
		/*
		 * Check if pin is struct, and then check if that pin is of struct type we want to customize
		 */
		if (InPin->PinType.PinCategory == K2Schema->PC_Struct &&
			InPin->PinType.PinSubCategoryObject == FUserSlot::StaticStruct())
		{
			// and return our customized pin widget ;).
			return SNew(SUserSlotPin, InPin);
		}

		/*
		 * Check if pin is struct, and then check if that pin is of struct type we want to customize
		 */
		if (InPin->PinType.PinCategory == K2Schema->PC_Struct &&
			InPin->PinType.PinSubCategoryObject == FRequestType::StaticStruct())
		{
			// and return our customized pin widget ;).
			return SNew(SRequestTypePin, InPin);
		}

		return nullptr;
	}
};
