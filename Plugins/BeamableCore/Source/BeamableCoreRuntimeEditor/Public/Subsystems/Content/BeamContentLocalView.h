#pragma once
#include "Content/BeamContentObject.h"

#include "BeamContentLocalView.generated.h"

UENUM(BlueprintType)
enum EBeamLocalContentStatus
{
	Beam_LocalContentCreated = 0,
	Beam_LocalContentDeleted = 1,
	Beam_LocalContentModified = 2,
	Beam_LocalContentUpToDate = 3,

	Beam_LocalContentAny = 4, 
};

UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamContentLocalView : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly,Category="Beam")
	UBeamContentObject* ContentObject;

	UPROPERTY(BlueprintReadOnly,Category="Beam")
	TEnumAsByte<EBeamLocalContentStatus> LocalStatus;

	UPROPERTY(BlueprintReadOnly,Category="Beam")
	FText ContentFullId;

	UPROPERTY(BlueprintReadOnly,Category="Beam")
	FText ContentTypeName;

	UPROPERTY(BlueprintReadOnly,Category="Beam")
	FText ContentName;
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIMEEDITOR_API FBeamContentViewConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	FLinearColor BorderColor = FLinearColor::Gray;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TSoftObjectPtr<UTexture2D> TypeForContentObject;
};
