
#include "BeamableCore/Public/AutoGen/AliasAvailableResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAliasAvailableResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAliasAvailableResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("alias"), Alias);
	Serializer->WriteValue(TEXT("available"), bAvailable);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
}

void UAliasAvailableResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("alias"), Alias);
	Serializer->WriteValue(TEXT("available"), bAvailable);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);		
}

void UAliasAvailableResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Alias = Bag->GetStringField(TEXT("alias"));
	bAvailable = Bag->GetBoolField(TEXT("available"));
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("cid")), Cid, OuterOwner);
}



