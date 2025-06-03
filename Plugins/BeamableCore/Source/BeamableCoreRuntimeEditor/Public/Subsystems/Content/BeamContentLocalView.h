#pragma once
#include "Content/BeamContentObject.h"

#include "BeamContentLocalView.generated.h"

UENUM(BlueprintType, Flags, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EBeamLocalContentStatus : uint8
{
	Beam_Invalid = 0 UMETA(Hidden),
	Beam_LocalContentCreated = 1 << 0,
	Beam_LocalContentDeleted = 1 << 1,
	Beam_LocalContentModified = 1 << 2,
	Beam_LocalContentUpToDate = 1 << 3,

	Beam_LocalContentAny = Beam_LocalContentCreated | Beam_LocalContentDeleted | Beam_LocalContentModified | Beam_LocalContentUpToDate, 
};
ENUM_CLASS_FLAGS(EBeamLocalContentStatus);

UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamContentLocalView : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UBeamContentObject* ContentObject;

	UPROPERTY(BlueprintReadOnly)
	EBeamLocalContentStatus LocalStatus;

	UPROPERTY(BlueprintReadOnly)
	FText ContentFullId;

	UPROPERTY(BlueprintReadOnly)
	FText ContentTypeName;

	UPROPERTY(BlueprintReadOnly)
	FText ContentName;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInConflict;
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIMEEDITOR_API FBeamContentViewConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor BorderColor = FLinearColor::Gray;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftObjectPtr<UTexture2D> TypeForContentObject;
};
