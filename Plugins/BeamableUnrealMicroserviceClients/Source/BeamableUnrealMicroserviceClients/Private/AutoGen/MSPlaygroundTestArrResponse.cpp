
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundTestArrResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UMSPlaygroundTestArrResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<TArray<int32>>(ResponseContent, Value, OuterOwner);
}

void UMSPlaygroundTestArrResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<>(TEXT("Value"), Value, Serializer);
}

void UMSPlaygroundTestArrResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<>(TEXT("Value"), Value, Serializer);		
}

void UMSPlaygroundTestArrResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<>(TEXT("Value"), Bag, Value, OuterOwner);
}



