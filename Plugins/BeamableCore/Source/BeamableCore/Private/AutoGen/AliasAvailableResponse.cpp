
#include "AutoGen/AliasAvailableResponse.h"

#include "Misc/DefaultValueHelper.h"


void UAliasAvailableResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAliasAvailableResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("alias"), Alias);
	Serializer->WriteValue(TEXT("available"), bAvailable);
	Serializer->WriteValue(TEXT("cid"), Cid);
}

void UAliasAvailableResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("alias"), Alias);
	Serializer->WriteValue(TEXT("available"), bAvailable);
	Serializer->WriteValue(TEXT("cid"), Cid);		
}

void UAliasAvailableResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Alias = Bag->GetStringField(TEXT("alias"));
	bAvailable = Bag->GetBoolField(TEXT("available"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("cid")), Cid);
}