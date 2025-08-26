
#include "BeamableCore/Public/AutoGen/RealmsBasicAliasAvailableResponse.h"
#include "Serialization/BeamJsonUtils.h"



void URealmsBasicAliasAvailableResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmsBasicAliasAvailableResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("available"), bAvailable, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
}

void URealmsBasicAliasAvailableResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("available"), bAvailable, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);		
}

void URealmsBasicAliasAvailableResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("alias"), Bag, Alias);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("available"), Bag, bAvailable);
	UBeamJsonUtils::DeserializeSemanticType<int64>(TEXT("cid"), Bag, Cid, OuterOwner);
}



