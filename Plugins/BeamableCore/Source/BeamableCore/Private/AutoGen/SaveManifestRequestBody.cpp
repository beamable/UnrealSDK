
#include "BeamableCore/Public/AutoGen/SaveManifestRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USaveManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeArray<UReferenceSuperset*>(TEXT("references"), References, Serializer);
}

void USaveManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeArray<UReferenceSuperset*>(TEXT("references"), References, Serializer);		
}

void USaveManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("id"), Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UReferenceSuperset*>(TEXT("references"), Bag, References, OuterOwner);
}



