// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamSteamDemoApi.h"
#include "steam/steam_api.h"

#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "SteamDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegate_LoginComplete, bool, Success, const FString&, Error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

BEAMPROJ_STEAMDEMO_API DECLARE_LOG_CATEGORY_EXTERN(LogSteamDemo, Log, All);
inline DEFINE_LOG_CATEGORY(LogSteamDemo);


/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJ_STEAMDEMO_API USteamDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamUserSlots* UserSlots;

	UPROPERTY()
	UBeamSteamDemoApi* SteamMs;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
		UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
		SteamMs = GEngine->GetEngineSubsystem<UBeamSteamDemoApi>();
	}

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("SteamDemo")); }

public:
	/**
	 * Exposes to blueprints ALL the information necessary to login with Steam.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="GetSteamData", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetSteamData(FString& SteamMicroserviceId, FString& SteamFederationId, FString& SteamUserId, FString& SteamAuthToken, FString& Error)
	{
		ISteamUser* SteamAccount = SteamUser();
		if (!SteamAccount)
		{
			UE_LOG(LogSteamDemo, Error, TEXT("Steam User is null. Check if the Steam SDK is initialized correctly and the game has valid settings."))
			Error = TEXT("Steam User is null. Check if the Steam SDK is initialized correctly and the game has valid settings.");
			return false;
		}

		uint32 TicketSize = 0;
		uint8 TicketBuffer[1024];
		HAuthTicket AuthTicket = SteamAccount->GetAuthSessionTicket(TicketBuffer, sizeof(TicketBuffer), &TicketSize, nullptr);

		if (AuthTicket == k_HAuthTicketInvalid || TicketSize <= 0)
		{
			// Handle the error case
			UE_LOG(LogSteamDemo, Error, TEXT("Failed to get Steam auth session ticket"));
			Error = TEXT("Failed to get Steam auth session ticket");
			return false;
		}

		// Successfully obtained the session ticket		
		for (uint32 i = 0; i < TicketSize; i++)
		{
			SteamAuthToken += FString::Printf(TEXT("%02x"), TicketBuffer[i]);
		}

		SteamMicroserviceId = SteamMs->GetMicroserviceName();
		SteamFederationId = TEXT("steam");
		SteamUserId = FString::Printf(TEXT("%llu"), SteamAccount->GetSteamID().ConvertToUint64());
		return true;
	}
};
