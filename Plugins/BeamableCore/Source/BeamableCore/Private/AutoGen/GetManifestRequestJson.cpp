
#include "BeamableCore/Public/AutoGen/GetManifestRequestJson.h"
#include "Serialization/BeamJsonUtils.h"




void UGetManifestRequestJson::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);
}

void UGetManifestRequestJson::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);		
}

void UGetManifestRequestJson::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamContentManifestId, FString>("id", Bag, Id, OuterOwner);
}



