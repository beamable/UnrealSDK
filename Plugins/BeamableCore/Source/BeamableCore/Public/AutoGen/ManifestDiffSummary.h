#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "ManifestDiffSummary.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UManifestDiffSummary : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest Uid", Category="Beam")
	FString ManifestUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Diff Url", Category="Beam")
	FString DiffUrl = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created Date", Category="Beam")
	int64 CreatedDate = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};