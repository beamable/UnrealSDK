
#include "BeamableCore/Public/AutoGen/SaveBinaryRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USaveBinaryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UBinaryDefinition*>(TEXT("binary"), Binary, Serializer);
}

void USaveBinaryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UBinaryDefinition*>(TEXT("binary"), Binary, Serializer);		
}

void USaveBinaryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UBinaryDefinition*>(Bag->GetArrayField(TEXT("binary")), Binary, OuterOwner);
}



