
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UClientManifestJsonResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UClientManifestJsonResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamRemoteContentManifestEntry>(TEXT("entries"), Items, Serializer);
}

void UClientManifestJsonResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamRemoteContentManifestEntry>(TEXT("entries"), Items, Serializer);		
}

void UClientManifestJsonResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FBeamRemoteContentManifestEntry>(Bag->GetArrayField(TEXT("entries")), Items, OuterOwner);
}



