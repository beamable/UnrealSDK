
#include "BeamableCore/Public/AutoGen/ImportFriendsRequestBody.h"





void UImportFriendsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("source"), Source);
	Serializer->WriteValue(TEXT("token"), Token);
}

void UImportFriendsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("source"), Source);
	Serializer->WriteValue(TEXT("token"), Token);		
}

void UImportFriendsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Source = Bag->GetStringField(TEXT("source"));
	Token = Bag->GetStringField(TEXT("token"));
}



