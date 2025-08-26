
#include "BeamableCore/Public/AutoGen/ContentBasicManifestChecksum.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UContentBasicManifestChecksum::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UContentBasicManifestChecksum::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdAt"), CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uid"), &Uid, Serializer);
}

void UContentBasicManifestChecksum::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdAt"), CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uid"), &Uid, Serializer);		
}

void UContentBasicManifestChecksum::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("id"), Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("createdAt"), Bag, CreatedAt);
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("uid", Bag, Uid, OuterOwner);
}



