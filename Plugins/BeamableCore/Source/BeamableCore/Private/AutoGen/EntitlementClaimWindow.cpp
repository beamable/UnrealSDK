
#include "BeamableCore/Public/AutoGen/EntitlementClaimWindow.h"

#include "Misc/DefaultValueHelper.h"



void UEntitlementClaimWindow::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("open"), Open, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("close"), Close, Serializer);
}

void UEntitlementClaimWindow::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("open"), Open, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("close"), Close, Serializer);		
}

void UEntitlementClaimWindow::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("open")), Open);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("close")), Close);
}



