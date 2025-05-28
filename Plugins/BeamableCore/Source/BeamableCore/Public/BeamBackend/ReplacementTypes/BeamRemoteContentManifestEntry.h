#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Enums/BeamContentType.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamRemoteContentManifestEntry.generated.h"

USTRUCT(BlueprintType, Category="Beam")
struct BEAMABLECORE_API FBeamRemoteContentManifestEntry : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Uri", Category="Beam")
	FString Uri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FString Version = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FBeamContentId ContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EBeamContentType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	TArray<FString> Tags = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("uri"), Uri);
		Serializer->WriteValue(TEXT("version"), Version);
		UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
		Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
		UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("uri"), Uri);
		Serializer->WriteValue(TEXT("version"), Version);
		UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
		Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
		UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Uri = Bag->GetStringField(TEXT("uri"));
		Version = Bag->GetStringField(TEXT("version"));
		UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("contentId")), ContentId, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("tags")), Tags, OuterOwner);
	}
};
