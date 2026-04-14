#pragma once
#include "Content/BeamContentObject.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"

#include "BeamContentLocalView.generated.h"

USTRUCT(BlueprintType)
struct FBeamContentHistoryContentEntryId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FBeamContentId ContentId;

	UPROPERTY(BlueprintReadOnly)
	FString ManifestUid;

	friend bool operator==(const FBeamContentHistoryContentEntryId& Lhs, const FBeamContentHistoryContentEntryId& RHS)
	{
		return Lhs.ContentId == RHS.ContentId && Lhs.ManifestUid == RHS.ManifestUid;
	}

	friend bool operator!=(const FBeamContentHistoryContentEntryId& Lhs, const FBeamContentHistoryContentEntryId& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamContentHistoryContentEntryId& Id) { return HashCombine(GetTypeHash(Id.ContentId), GetTypeHash(Id.ManifestUid)); }

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
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

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIMEEDITOR_API FBeamSnapshotContentEntry
{
	GENERATED_BODY()
	// TODO: UPROPERTY for whatever you need to display

	UPROPERTY(BlueprintReadOnly)
	FText Name;

	UPROPERTY(BlueprintReadOnly)
	EBeamLocalContentStatus CurrentStatus = EBeamLocalContentStatus::Beam_Invalid;
};



UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamSnapshotLocalView : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FText Name;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsSharedSnapshot;

	UPROPERTY(BlueprintReadOnly)
	bool bIsAutoSnapshot;

	UPROPERTY(BlueprintReadOnly)
	FText Author;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeStamp;

	UPROPERTY(BlueprintReadOnly)
	FText ManifestID;

	UPROPERTY(BlueprintReadOnly)
	FText Realm;

	UPROPERTY(BlueprintReadOnly)
	FText PID;

	UPROPERTY(BlueprintReadOnly)
	FString Path;

	UPROPERTY(BlueprintReadOnly)
	TArray<FBeamSnapshotContentEntry> Contents;
};

UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamContentHistoryEntryView : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString ManifestUid;

	UPROPERTY(BlueprintReadOnly)
	FDateTime PublishedDate;

	UPROPERTY(BlueprintReadOnly)
	FText PublishedBy;

	UPROPERTY(BlueprintReadOnly)
	FText PublishedByName;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> AffectedContentIds;
};

UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamContentHistoryChangelistEntryView : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString FullId;

	UPROPERTY(BlueprintReadOnly)
	FText Name;

	UPROPERTY(BlueprintReadOnly)
	FText TypeName;

	UPROPERTY(BlueprintReadOnly)
	FString OldVersion;

	UPROPERTY(BlueprintReadOnly)
	FString OldChecksum;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> OldTags;

	UPROPERTY(BlueprintReadOnly)
	FString NewVersion;

	UPROPERTY(BlueprintReadOnly)
	FString NewChecksum;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> NewTags;

	UPROPERTY(BlueprintReadOnly)
	FDateTime ChangeDate;

	UPROPERTY(BlueprintReadOnly)
	EBeamLocalContentStatus ChangeStatus;
	
	UPROPERTY(BlueprintReadOnly)
	FBeamContentHistoryContentEntryId HistoryEntryId;
};

UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamContentHistoryChangelistView : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString ManifestUid;

	UPROPERTY(BlueprintReadOnly)
	FDateTime PublishedDate;

	UPROPERTY(BlueprintReadOnly)
	FText PublishedBy;

	UPROPERTY(BlueprintReadOnly)
	FText PublishedByName;

	UPROPERTY(BlueprintReadOnly)
	TArray<UBeamContentHistoryChangelistEntryView*> Entries;
};