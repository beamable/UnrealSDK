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
	UPROPERTY(BlueprintReadOnly)
	UBeamContentObject* ContentObject;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EBeamLocalContentStatus> LocalStatus;

	UPROPERTY(BlueprintReadOnly)
	FText ContentFullId;

	UPROPERTY(BlueprintReadOnly)
	FText ContentTypeName;

	UPROPERTY(BlueprintReadOnly)
	FText ContentName;

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UBeamContentObject> ContentType;
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIMEEDITOR_API FBeamContentViewConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor BorderColor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftObjectPtr<UTexture2D> TypeForContentObject;
};
