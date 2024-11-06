
#include "BeamableCore/Public/AutoGen/CreateElevatedAccountRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCreateElevatedAccountRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("role"), &Role, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("initProperties"), &InitProperties, Serializer);
}

void UCreateElevatedAccountRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("role"), &Role, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("initProperties"), &InitProperties, Serializer);		
}

void UCreateElevatedAccountRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Email = Bag->GetStringField(TEXT("email"));
	UBeamJsonUtils::DeserializeOptional<FString>("role", Bag, Role, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("initProperties", Bag, InitProperties, OuterOwner);
}



