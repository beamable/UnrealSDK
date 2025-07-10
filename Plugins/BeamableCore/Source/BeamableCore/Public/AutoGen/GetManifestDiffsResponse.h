#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ManifestDiffSummary.h"

#include "GetManifestDiffsResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGetManifestDiffsResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has More", Category="Beam")
	bool bHasMore = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest Id", Category="Beam")
	FString ManifestId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Total Count", Category="Beam")
	int32 TotalCount = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Diffs", Category="Beam")
	TArray<UManifestDiffSummary*> Diffs = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};