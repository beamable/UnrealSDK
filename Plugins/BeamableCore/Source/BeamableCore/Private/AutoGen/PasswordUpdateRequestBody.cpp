
#include "BeamableCore/Public/AutoGen/PasswordUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPasswordUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("codeType"), &CodeType, Serializer);
}

void UPasswordUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("codeType"), &CodeType, Serializer);		
}

void UPasswordUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Email = Bag->GetStringField(TEXT("email"));
	UBeamJsonUtils::DeserializeOptional<FString>("codeType", Bag, CodeType, OuterOwner);
}



