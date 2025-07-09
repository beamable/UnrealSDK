
#include "BeamableCore/Public/AutoGen/GetManifestsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetManifestsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetManifestsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoActorManifest*>, UBeamoActorManifest*>(TEXT("manifests"), &Manifests, Serializer);
}

void UGetManifestsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoActorManifest*>, UBeamoActorManifest*>(TEXT("manifests"), &Manifests, Serializer);		
}

void UGetManifestsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoActorManifest*>, UBeamoActorManifest*>("manifests", Bag, Manifests, OuterOwner);
}



