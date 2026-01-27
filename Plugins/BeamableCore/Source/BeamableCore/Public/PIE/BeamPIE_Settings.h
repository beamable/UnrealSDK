#pragma once
#include "BeamPIE_LobbySettings.h"
#include "BeamPIE_UserSlotHandle.h"
#include "FBeamPIE_PerUserSetting.h"

#include "BeamPIE_Settings.generated.h"


USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPartyPlayerSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPartyLeader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PartyId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> PartyTags = {};
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPartySettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldAutoCreateParty = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateParty", EditConditionHides))
	int32 MaxPartySize = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateParty", EditConditionHides))
	int PartyRestriction = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShouldAutoCreateParty", EditConditionHides))
	TMap<FBeamPIE_UserSlotHandle, FBeamPartyPlayerSettings> PlayerSettingsMap = {};
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPIE_Settings
{
	static inline const FGuid DefaultPieSettingsGuid = FGuid::NewDeterministicGuid(TEXT("__BEAM_DEFAULT_PIE_SETTING__"));

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid SettingsId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FBeamPIE_UserSlotHandle, FBeamPIE_PerUserSetting> AssignedUsers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AllowedMapNamePattern = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowedClasses="/Script/Engine.World"))
	TArray<TSoftObjectPtr<UWorld>> AllowedInMaps;

	// Lobby
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamPIE_LobbySettings FakeLobby;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamPartySettings PartySettings = {};

	bool IsDefaultSettings() const { return SettingsId == DefaultPieSettingsGuid; }
};

FORCEINLINE uint32 GetTypeHash(const FBeamPIE_Settings& Context) { return GetTypeHash(Context.SettingsId); }
