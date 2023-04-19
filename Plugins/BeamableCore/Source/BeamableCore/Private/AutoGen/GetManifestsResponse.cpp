
#include "BeamableCore/Public/AutoGen/GetManifestsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetManifestsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetManifestsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UContentBasicManifest*>(TEXT("manifests"), Manifests, Serializer);
}

void UGetManifestsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UContentBasicManifest*>(TEXT("manifests"), Manifests, Serializer);		
}

void UGetManifestsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UContentBasicManifest*>(Bag->GetArrayField(TEXT("manifests")), Manifests, OuterOwner);
}



