
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateWithModifiersRequestArgs.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMutateWithModifiersRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("plantItemContentId"), PlantItemContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("plantItemInstanceId"), PlantItemInstanceId, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("modifierContentIds"), ModifierContentIds, Serializer);
}

void UMutateWithModifiersRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("plantItemContentId"), PlantItemContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("plantItemInstanceId"), PlantItemInstanceId, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("modifierContentIds"), ModifierContentIds, Serializer);		
}

void UMutateWithModifiersRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("plantItemContentId"), Bag, PlantItemContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("plantItemInstanceId"), Bag, PlantItemInstanceId);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("modifierContentIds"), Bag, ModifierContentIds, OuterOwner);
}



