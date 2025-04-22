
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UContentBasicManifest::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UContentBasicManifest::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<UBaseContentReference*>(TEXT("references"), References, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("publisherAccountId"), &PublisherAccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uid"), &Uid, Serializer);
}

void UContentBasicManifest::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<UBaseContentReference*>(TEXT("references"), References, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("publisherAccountId"), &PublisherAccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uid"), &Uid, Serializer);		
}

void UContentBasicManifest::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("checksum")), Checksum);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeArray<UBaseContentReference*>(Bag->GetArrayField(TEXT("references")), References, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("publisherAccountId", Bag, PublisherAccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("uid", Bag, Uid, OuterOwner);
}



