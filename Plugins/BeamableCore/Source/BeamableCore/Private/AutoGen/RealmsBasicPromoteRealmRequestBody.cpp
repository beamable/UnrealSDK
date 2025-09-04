
#include "BeamableCore/Public/AutoGen/RealmsBasicPromoteRealmRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URealmsBasicPromoteRealmRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourcePid"), &SourcePid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("promotions"), &Promotions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("contentManifestIds"), &ContentManifestIds, Serializer);
}

void URealmsBasicPromoteRealmRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourcePid"), &SourcePid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("promotions"), &Promotions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("contentManifestIds"), &ContentManifestIds, Serializer);		
}

void URealmsBasicPromoteRealmRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("sourcePid"), Bag, SourcePid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("promotions", Bag, Promotions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("contentManifestIds", Bag, ContentManifestIds, OuterOwner);
}



