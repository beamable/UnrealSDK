#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "ManifestDiffSummary.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UManifestDiffSummary : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest Uid", Category="Beam")
	FString ManifestUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created Date", Category="Beam")
	int64 CreatedDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Affected Content Ids", Category="Beam")
	TArray<FString> AffectedContentIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Published By Name", Category="Beam")
	FOptionalString PublishedByName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Published By", Category="Beam")
	FOptionalString PublishedBy = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};