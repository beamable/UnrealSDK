
#include "BeamableCore/Public/AutoGen/PasswordUpdateConfirmation.h"
#include "Serialization/BeamJsonUtils.h"




void UPasswordUpdateConfirmation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("code"), Code);
	Serializer->WriteValue(TEXT("newPassword"), NewPassword);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
}

void UPasswordUpdateConfirmation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("code"), Code);
	Serializer->WriteValue(TEXT("newPassword"), NewPassword);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);		
}

void UPasswordUpdateConfirmation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Code = Bag->GetStringField(TEXT("code"));
	NewPassword = Bag->GetStringField(TEXT("newPassword"));
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
}



