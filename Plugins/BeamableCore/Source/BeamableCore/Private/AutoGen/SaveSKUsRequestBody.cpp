
#include "BeamableCore/Public/AutoGen/SaveSKUsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USaveSKUsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USKU*>(TEXT("definitions"), Definitions, Serializer);
}

void USaveSKUsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USKU*>(TEXT("definitions"), Definitions, Serializer);		
}

void USaveSKUsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<USKU*>(Bag->GetArrayField(TEXT("definitions")), Definitions, OuterOwner);
}



