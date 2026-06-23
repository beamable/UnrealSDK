
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantResult.h"

#include "Misc/DefaultValueHelper.h"


void UPlantResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPlantResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("plantedAtUtcSeconds"), PlantedAtUtcSeconds, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
}

void UPlantResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("plantedAtUtcSeconds"), PlantedAtUtcSeconds, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);		
}

void UPlantResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("plantedAtUtcSeconds"), Bag, PlantedAtUtcSeconds);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
}



