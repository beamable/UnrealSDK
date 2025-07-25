
#include "BeamableCore/Public/AutoGen/ImportFriendsRequestBody.h"





void UImportFriendsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("source"), Source, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
}

void UImportFriendsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("source"), Source, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);		
}

void UImportFriendsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("source"), Bag, Source);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("token"), Bag, Token);
}



