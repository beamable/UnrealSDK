
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalLeaderboardCohortSettings.h"
#include "AutoGen/Optionals/OptionalClientPermission.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "MetadataView.generated.h"

UCLASS(BlueprintType)
class UMetadataView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Freeze Time")
	FOptionalInt64 FreezeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Derivatives")
	FOptionalArrayOfString Derivatives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent Leaderboard")
	FString ParentLeaderboard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort Settings")
	FOptionalLeaderboardCohortSettings CohortSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Permissions")
	FOptionalClientPermission Permissions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Frozen")
	bool bFrozen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Entries")
	FOptionalInt32 MaxEntries;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Partitioned")
	bool bPartitioned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Cohorted")
	bool bCohorted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expiration")
	FOptionalInt64 Expiration;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};