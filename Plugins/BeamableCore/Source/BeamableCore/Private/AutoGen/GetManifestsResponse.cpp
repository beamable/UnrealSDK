
#include "AutoGen/GetManifestsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetManifestsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetManifestsResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UManifestView*>(TEXT("manifests"), Manifests, Serializer);
}

void UGetManifestsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UManifestView*>(TEXT("manifests"), Manifests, Serializer);		
}

void UGetManifestsResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UManifestView*>(Bag->GetArrayField(TEXT("manifests")), Manifests, OuterOwner);
}