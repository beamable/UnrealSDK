// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystemUtils.h"
#include "steam/steam_api.h"

#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "SteamDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FDelegate_LoginComplete, bool, Success, const FString&, Error );

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FDelegate_Simple );
/**
 * 
 */
UCLASS()
class BEAMPROJ_STEAMDEMO_API USteamDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	IOnlineSubsystem* OnlineSubsystem;
	IOnlineIdentityPtr IdentityInterface;
	IOnlineSessionPtr SessionInterface;
	IOnlineStatsPtr StatsInterface;

	FDelegateHandle OnBeamableStarted;
public:
	UPROPERTY( BlueprintAssignable )
	FDelegate_LoginComplete OnLoginCompleteDelegate;

	UPROPERTY( BlueprintAssignable )
	FDelegate_Simple OnInitialized;

protected:
	virtual void Initialize( FSubsystemCollectionBase& Collection ) override
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
	}
	virtual FString GetSpecificLevelName() const override { return FString(TEXT("SteamDemo")); }
	
	UFUNCTION(BlueprintCallable)
	void InitializeSteamDemo()
	{
		const TSharedPtr<const FUniqueNetId> netID = UGameplayStatics::GetGameInstance(GetWorld())->GetFirstGamePlayer()->GetPreferredUniqueNetId().GetUniqueNetId();
		const FString UniqueNetId = netID->ToString();
		UE_LOG(LogTemp, Warning, TEXT("Steam Init Start, GetUniqueNetId: %s"),*UniqueNetId);

		if (SteamUser())
		{
			uint32 TicketSize = 0;
			uint8 TicketBuffer[1024];

			HAuthTicket AuthTicket = SteamUser()->GetAuthSessionTicket(TicketBuffer, sizeof(TicketBuffer), &TicketSize);

			if (AuthTicket != k_HAuthTicketInvalid && TicketSize > 0)
			{
				// Successfully obtained the session ticket
				FString TicketHex;
				for (uint32 i = 0; i < TicketSize; i++)
				{
					TicketHex += FString::Printf(TEXT("%02x"), TicketBuffer[i]);
				}
				UE_LOG(LogTemp, Warning, TEXT("Steam User HEX Auth ticket: %s"),*TicketHex);
			}
			else
			{
				// Handle the error case
				UE_LOG(LogTemp, Error, TEXT("Failed to get Steam auth session ticket"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("NOT A STEAM USER"))
		}
	}
	
	UFUNCTION(BlueprintCallable)
	bool IsLoggedIn()
	{
		if (!IdentityInterface) return false;

		const ELoginStatus::Type LoginStatus = IdentityInterface->GetLoginStatus(0);
		return LoginStatus == ELoginStatus::Type::LoggedIn;
	}
};
