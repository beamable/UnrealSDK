
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UClientManifestJsonResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UClientManifestJsonResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamRemoteContentManifestEntry>(TEXT("entries"), Entries, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uid"), &Uid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("publisherAccountId"), &PublisherAccountId, Serializer);
}

void UClientManifestJsonResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamRemoteContentManifestEntry>(TEXT("entries"), Entries, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uid"), &Uid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("publisherAccountId"), &PublisherAccountId, Serializer);		
}

void UClientManifestJsonResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FBeamRemoteContentManifestEntry>(Bag->GetArrayField(TEXT("entries")), Entries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("uid", Bag, Uid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("publisherAccountId", Bag, PublisherAccountId, OuterOwner);
}



