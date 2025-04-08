
#include "BeamableCore/Public/AutoGen/EntitlementClaimWindow.h"

#include "Misc/DefaultValueHelper.h"



void UEntitlementClaimWindow::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("open"), Open);
	Serializer->WriteValue(TEXT("close"), Close);
}

void UEntitlementClaimWindow::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("open"), Open);
	Serializer->WriteValue(TEXT("close"), Close);		
}

void UEntitlementClaimWindow::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("open")), Open);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("close")), Close);
}



