
#include "BeamableCore/Public/AutoGen/MailQueryResponse.h"

#include "Misc/DefaultValueHelper.h"


void UMailQueryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMailQueryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("unreadCount"), UnreadCount);
}

void UMailQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("unreadCount"), UnreadCount);		
}

void UMailQueryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("unreadCount")), UnreadCount);
}



