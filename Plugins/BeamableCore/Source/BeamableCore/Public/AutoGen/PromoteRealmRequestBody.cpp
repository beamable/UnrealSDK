
#include "AutoGen/PromoteRealmRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void UPromoteRealmRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourcePid"), SourcePid);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("promotions"), &Promotions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("contentManifestIds"), &ContentManifestIds, Serializer);
}

void UPromoteRealmRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourcePid"), SourcePid);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("promotions"), &Promotions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("contentManifestIds"), &ContentManifestIds, Serializer);		
}

void UPromoteRealmRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	SourcePid = Bag->GetStringField(TEXT("sourcePid"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("promotions", Bag, Promotions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("contentManifestIds", Bag, ContentManifestIds, OuterOwner);
}