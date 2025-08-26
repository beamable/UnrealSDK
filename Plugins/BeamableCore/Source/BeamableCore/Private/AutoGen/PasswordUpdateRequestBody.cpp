
#include "BeamableCore/Public/AutoGen/PasswordUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPasswordUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("codeType"), &CodeType, Serializer);
}

void UPasswordUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("codeType"), &CodeType, Serializer);		
}

void UPasswordUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("email"), Bag, Email);
	UBeamJsonUtils::DeserializeOptional<FString>("codeType", Bag, CodeType, OuterOwner);
}



