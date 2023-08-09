#pragma once


#include "BeamK2.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "SlateBasics.h"
#include "Pins/RequestTypePin.h"
#include "Pins/UserSlotPin.h"
#include "GraphNodes/GraphNodeBaseBeam.h"
#include "BeamFlow/K2BeamNode_BeamFlow.h"

#include "UserSlots/UserSlot.h"
#include "BeamBackend/RequestType.h"
#include "Pins/BeamContentIdPin.h"
#include "Pins/OptionalTypePin.h"

struct BEAMABLECOREEDITOR_API FBeamableCoreGraphNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* InNode) const override
	{
		if (Cast<UK2BeamNode_BeamFlow>(InNode) || InNode->GetClass()->HasMetaData(BeamK2::MD_BeamFlowNode))
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
			InPin->PinType.PinSubCategoryObject == FBeamContentId::StaticStruct())
		{
			// and return our customized pin widget ;).
			return SNew(SBeamContentIdPin, InPin);
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

		/*
		 * Check if pin is struct, and then check if that pin is of struct type we want to customize
		 */
		if (InPin->PinType.PinCategory == K2Schema->PC_Struct)
		{
			if (const auto S = Cast<UScriptStruct>(InPin->PinType.PinSubCategoryObject))
			{
				if (S->HasMetaData(BeamK2::MD_BeamOptionalType))
				{
					return SNew(SOptionalTypePin, InPin);
				}
			}
		}

		return nullptr;
	}
};
