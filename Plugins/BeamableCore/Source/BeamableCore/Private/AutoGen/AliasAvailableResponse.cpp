
#include "BeamableCore/Public/AutoGen/AliasAvailableResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAliasAvailableResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAliasAvailableResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("available"), bAvailable, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
}

void UAliasAvailableResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("available"), bAvailable, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);		
}

void UAliasAvailableResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("alias")), Alias);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("available")), bAvailable);
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("cid")), Cid, OuterOwner);
}



