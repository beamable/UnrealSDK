
#include "BeamableCore/Public/AutoGen/SearchExtendedResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void USearchExtendedResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USearchExtendedResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offset"), Offset, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("limit"), Limit, Serializer);
	UBeamJsonUtils::SerializeMap<FMapOfString>(TEXT("gamerStats"), GamerStats, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("total"), &Total, Serializer);
}

void USearchExtendedResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offset"), Offset, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("limit"), Limit, Serializer);
	UBeamJsonUtils::SerializeMap<FMapOfString>(TEXT("gamerStats"), GamerStats, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("total"), &Total, Serializer);		
}

void USearchExtendedResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("offset"), Bag, Offset);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("limit"), Bag, Limit);
	UBeamJsonUtils::DeserializeMap<FMapOfString>(TEXT("gamerStats"), Bag, GamerStats, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("total", Bag, Total, OuterOwner);
}



