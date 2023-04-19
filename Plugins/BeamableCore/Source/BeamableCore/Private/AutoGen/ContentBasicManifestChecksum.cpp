
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
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("createdAt"), CreatedAt);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
}

void UContentBasicManifestChecksum::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("createdAt"), CreatedAt);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);		
}

void UContentBasicManifestChecksum::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	Checksum = Bag->GetStringField(TEXT("checksum"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("createdAt")), CreatedAt);
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
}



