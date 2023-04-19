
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
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UReferenceSuperset*>(Bag->GetArrayField(TEXT("references")), References, OuterOwner);
}



