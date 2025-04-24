#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MetadataView.h"

#include "MetadataViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMetadataViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="MetadataView To JSON String")
	static FString MetadataViewToJsonString(const UMetadataView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make MetadataView", meta=(DefaultToSelf="Outer", AdvancedDisplay="FreezeTime, CohortSettings, Permissions, MaxEntries, Expiration, Derivatives, Outer", NativeMakeFunc))
	static UMetadataView* Make(bool bCohorted, bool bFrozen, bool bPartitioned, FString ParentLeaderboard, FOptionalInt64 FreezeTime, FOptionalLeaderboardCohortSettings CohortSettings, FOptionalBeamClientPermission Permissions, FOptionalInt32 MaxEntries, FOptionalInt64 Expiration, FOptionalArrayOfString Derivatives, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break MetadataView", meta=(NativeBreakFunc))
	static void Break(const UMetadataView* Serializable, bool& bCohorted, bool& bFrozen, bool& bPartitioned, FString& ParentLeaderboard, FOptionalInt64& FreezeTime, FOptionalLeaderboardCohortSettings& CohortSettings, FOptionalBeamClientPermission& Permissions, FOptionalInt32& MaxEntries, FOptionalInt64& Expiration, FOptionalArrayOfString& Derivatives);
};