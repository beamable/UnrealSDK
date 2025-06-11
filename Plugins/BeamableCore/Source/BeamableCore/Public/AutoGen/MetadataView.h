#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalLeaderboardCohortSettings.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamClientPermission.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"

#include "MetadataView.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UMetadataView : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Cohorted", Category="Beam")
	bool bCohorted = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Frozen", Category="Beam")
	bool bFrozen = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Partitioned", Category="Beam")
	bool bPartitioned = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent Leaderboard", Category="Beam")
	FString ParentLeaderboard = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Freeze Time", Category="Beam")
	FOptionalInt64 FreezeTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort Settings", Category="Beam")
	FOptionalLeaderboardCohortSettings CohortSettings = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Permissions", Category="Beam")
	FOptionalBeamClientPermission Permissions = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Entries", Category="Beam")
	FOptionalInt32 MaxEntries = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expiration", Category="Beam")
	FOptionalInt64 Expiration = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Derivatives", Category="Beam")
	FOptionalArrayOfString Derivatives = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};