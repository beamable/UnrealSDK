
#include "BeamableCore/Public/AutoGen/EmailUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UEmailUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("newEmail"), NewEmail);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("codeType"), &CodeType, Serializer);
}

void UEmailUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("newEmail"), NewEmail);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("codeType"), &CodeType, Serializer);		
}

void UEmailUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	NewEmail = Bag->GetStringField(TEXT("newEmail"));
	UBeamJsonUtils::DeserializeOptional<FString>("codeType", Bag, CodeType, OuterOwner);
}



