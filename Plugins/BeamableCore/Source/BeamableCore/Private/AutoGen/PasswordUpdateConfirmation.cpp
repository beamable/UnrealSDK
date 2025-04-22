
#include "BeamableCore/Public/AutoGen/PasswordUpdateConfirmation.h"
#include "Serialization/BeamJsonUtils.h"




void UPasswordUpdateConfirmation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("newPassword"), NewPassword, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
}

void UPasswordUpdateConfirmation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("newPassword"), NewPassword, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);		
}

void UPasswordUpdateConfirmation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("code")), Code);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("newPassword")), NewPassword);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
}



