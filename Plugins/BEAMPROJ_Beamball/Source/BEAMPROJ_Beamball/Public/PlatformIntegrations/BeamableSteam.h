// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "steam/steam_api.h"

#include "BeamableSteam.generated.h"


/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API UBeamableSteam : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamableSteam* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamableSteam>(); }
	
	/**
	 * Exposes to blueprints ALL the information necessary to login with Steam.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="GetSteamData", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetSteamData(FString& SteamUserId, FString& SteamAuthToken, FString& Error)
	{
		ISteamUser* SteamAccount = SteamUser();
		if (!SteamAccount)
		{
			UE_LOG(LogTemp, Error, TEXT("Steam User is null. Check if the Steam SDK is initialized correctly and the game has valid settings."))
			Error = TEXT("Steam User is null. Check if the Steam SDK is initialized correctly and the game has valid settings.");
			return false;
		}

		uint32 TicketSize = 0;
		uint8 TicketBuffer[1024];
		HAuthTicket AuthTicket = SteamAccount->GetAuthSessionTicket(TicketBuffer, sizeof(TicketBuffer), &TicketSize, nullptr);

		if (AuthTicket == k_HAuthTicketInvalid || TicketSize <= 0)
		{
			// Handle the error case
			UE_LOG(LogTemp, Error, TEXT("Failed to get Steam auth session ticket"));
			Error = TEXT("Failed to get Steam auth session ticket");
			return false;
		}

		// Successfully obtained the session ticket		
		for (uint32 i = 0; i < TicketSize; i++)
		{
			SteamAuthToken += FString::Printf(TEXT("%02x"), TicketBuffer[i]);
		}

		SteamUserId = FString::Printf(TEXT("%llu"), SteamAccount->GetSteamID().ConvertToUint64());		
		return true;
	}	
	
};
