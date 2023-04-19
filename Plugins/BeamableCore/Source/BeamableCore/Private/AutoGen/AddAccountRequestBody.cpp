
#include "BeamableCore/Public/AutoGen/AddAccountRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAddAccountRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("role"), &Role, Serializer);
}

void UAddAccountRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("role"), &Role, Serializer);		
}

void UAddAccountRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Email = Bag->GetStringField(TEXT("email"));
	UBeamJsonUtils::DeserializeOptional<FString>("role", Bag, Role, OuterOwner);
}



