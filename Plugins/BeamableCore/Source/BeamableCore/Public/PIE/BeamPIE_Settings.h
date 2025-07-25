#pragma once
#include "BeamPIE_LobbySettings.h"
#include "BeamPIE_UserSlotHandle.h"
#include "FBeamPIE_PerUserSetting.h"

#include "BeamPIE_Settings.generated.h"

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
	FString AllowedMapNamePattern = TEXT("*");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowedClasses="/Script/Engine.World"))
	TArray<TSoftObjectPtr<UWorld>> AllowedInMaps;

	// Lobby
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamPIE_LobbySettings FakeLobby;
	
	
	bool IsDefaultSettings() const { return SettingsId == DefaultPieSettingsGuid; }
};

FORCEINLINE uint32 GetTypeHash(const FBeamPIE_Settings& Context) { return GetTypeHash(Context.SettingsId); }

