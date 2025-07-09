
#include "BeamableCore/Public/AutoGen/BeamoActorManifestChecksum.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoActorManifestChecksum::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoActorManifestChecksum::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("createdAt"), &CreatedAt, Serializer);
}

void UBeamoActorManifestChecksum::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("createdAt"), &CreatedAt, Serializer);		
}

void UBeamoActorManifestChecksum::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("createdAt", Bag, CreatedAt, OuterOwner);
}



