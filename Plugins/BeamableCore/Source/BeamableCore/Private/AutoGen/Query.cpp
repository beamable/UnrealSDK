
#include "BeamableCore/Public/AutoGen/Query.h"




void UQuery::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("queryId"), QueryId);
}

void UQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("queryId"), QueryId);		
}

void UQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	QueryId = Bag->GetStringField(TEXT("queryId"));
}



