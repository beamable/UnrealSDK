
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

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardCreateRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded", Category="Beam")
	bool bSharded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Partitioned", Category="Beam")
	FOptionalBool bPartitioned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Freeze Time", Category="Beam")
	FOptionalInt64 FreezeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Name", Category="Beam")
	FOptionalString ScoreName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort Settings", Category="Beam")
	FOptionalLeaderboardCohortSettings CohortSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Permissions", Category="Beam")
	FOptionalClientPermission Permissions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Entries", Category="Beam")
	FOptionalInt32 MaxEntries;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Ttl", Category="Beam")
	FOptionalInt64 Ttl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Derivatives", Category="Beam")
	FOptionalArrayOfString Derivatives;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};