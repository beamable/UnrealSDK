
#include "BeamableCore/Public/AutoGen/SaveTextRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USaveTextRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTextDefinition*>(TEXT("text"), Text, Serializer);
}

void USaveTextRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTextDefinition*>(TEXT("text"), Text, Serializer);		
}

void USaveTextRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UTextDefinition*>(Bag->GetArrayField(TEXT("text")), Text, OuterOwner);
}



