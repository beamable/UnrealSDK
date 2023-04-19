
#include "BeamableCore/Public/AutoGen/PromoteRealmRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPromoteRealmRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourcePid"), &SourcePid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("promotions"), &Promotions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("contentManifestIds"), &ContentManifestIds, Serializer);
}

void UPromoteRealmRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourcePid"), &SourcePid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("promotions"), &Promotions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("contentManifestIds"), &ContentManifestIds, Serializer);		
}

void UPromoteRealmRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("sourcePid")), SourcePid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("promotions", Bag, Promotions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("contentManifestIds", Bag, ContentManifestIds, OuterOwner);
}



