
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalLeaderboardCohortSettings.h"
#include "AutoGen/Optionals/OptionalClientPermission.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "LeaderboardCreateRequestBody.generated.h"

UCLASS(BlueprintType)
class ULeaderboardCreateRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Freeze Time")
	FOptionalInt64 FreezeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Derivatives")
	FOptionalArrayOfString Derivatives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Name")
	FOptionalString ScoreName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort Settings")
	FOptionalLeaderboardCohortSettings CohortSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Permissions")
	FOptionalClientPermission Permissions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Entries")
	FOptionalInt32 MaxEntries;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Partitioned")
	FOptionalBool bPartitioned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded")
	bool bSharded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Ttl")
	FOptionalInt64 Ttl;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};