#pragma once


#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "SlateBasics.h"
#include "RequestTypePin.h"
#include "UserSlotPin.h"
#include "BeamCoreTypes.h"
#include "GraphNodeBaseBeam.h"
#include "UserSlots/UserSlot.h"
#include "WaitHandleNodes/K2BeamNode_WaitAll.h"

struct BEAMABLECOREEDITOR_API FBeamableCoreGraphNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* InNode) const override
	{
		if (InNode->GetClass()->HasMetaData("BeamFlow"))
		{			
			return SNew(SGraphNodeBaseBeam, InNode);
		}

		return nullptr;
	}
};


struct BEAMABLECOREEDITOR_API FBeamableCorePinFactory : public FGraphPanelPinFactory
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
