
#include "BeamableCore/Public/AutoGen/EmailUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UEmailUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("newEmail"), NewEmail, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("codeType"), &CodeType, Serializer);
}

void UEmailUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("newEmail"), NewEmail, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("codeType"), &CodeType, Serializer);		
}

void UEmailUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("newEmail")), NewEmail);
	UBeamJsonUtils::DeserializeOptional<FString>("codeType", Bag, CodeType, OuterOwner);
}



