
#include "BeamableCore/Public/AutoGen/BeamoV2GetManifestsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2GetManifestsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2GetManifestsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2Manifest*>, UBeamoV2Manifest*>(TEXT("manifests"), &Manifests, Serializer);
}

void UBeamoV2GetManifestsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2Manifest*>, UBeamoV2Manifest*>(TEXT("manifests"), &Manifests, Serializer);		
}

void UBeamoV2GetManifestsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2Manifest*>, UBeamoV2Manifest*>("manifests", Bag, Manifests, OuterOwner);
}



