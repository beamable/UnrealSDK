
#include "BeamableCore/Public/AutoGen/InventoryUpdateResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UInventoryUpdateResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UInventoryUpdateResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("data"), Data, Serializer);
	UBeamJsonUtils::SerializeOptional<UInventoryUpdateDelta*>(TEXT("deltas"), &Deltas, Serializer);
}

void UInventoryUpdateResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("data"), Data, Serializer);
	UBeamJsonUtils::SerializeOptional<UInventoryUpdateDelta*>(TEXT("deltas"), &Deltas, Serializer);		
}

void UInventoryUpdateResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("result"), Bag, Result);
	UBeamJsonUtils::DeserializeMap<FString>(TEXT("data"), Bag, Data, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UInventoryUpdateDelta*>("deltas", Bag, Deltas, OuterOwner);
}



