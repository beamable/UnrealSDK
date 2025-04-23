
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UpgradeItemRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UUpgradeItemRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userID"), UserID, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstaceID"), ItemInstaceID, Serializer);
}

void UUpgradeItemRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userID"), UserID, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstaceID"), ItemInstaceID, Serializer);		
}

void UUpgradeItemRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("userID")), UserID);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("itemInstaceID")), ItemInstaceID);
}



