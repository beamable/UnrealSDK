
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutationInput.h"

#include "Misc/DefaultValueHelper.h"



void UMutationInput::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemContentId"), ItemContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("quantity"), Quantity, Serializer);
}

void UMutationInput::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemContentId"), ItemContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("quantity"), Quantity, Serializer);		
}

void UMutationInput::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemContentId"), Bag, ItemContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("quantity"), Bag, Quantity);
}



