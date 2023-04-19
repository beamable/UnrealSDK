
#include "BeamableCore/Public/AutoGen/SaveContentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USaveContentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UContentDefinition*>(TEXT("content"), Content, Serializer);
}

void USaveContentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UContentDefinition*>(TEXT("content"), Content, Serializer);		
}

void USaveContentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UContentDefinition*>(Bag->GetArrayField(TEXT("content")), Content, OuterOwner);
}



