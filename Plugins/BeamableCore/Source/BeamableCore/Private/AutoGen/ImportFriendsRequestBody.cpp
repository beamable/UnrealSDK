
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("source")), Source);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("token")), Token);
}



