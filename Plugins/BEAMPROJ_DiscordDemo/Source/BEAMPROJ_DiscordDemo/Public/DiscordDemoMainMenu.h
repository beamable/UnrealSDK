// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiscordSubsystem.h"
#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "DiscordDemoMainMenu.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

UCLASS()
class BEAMPROJ_DISCORDDEMO_API UDiscordDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()
	UPROPERTY()
	UBeamUserSlots* UserSlots;
	FDelegateHandle OnBeamableReady;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInitialized;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
		UE_LOG(LogTemp, Display, TEXT("Initialize Discord Demo Main Menu"));
	}

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("DiscordDemo")); }

	UFUNCTION()
	void HandleDiscordInitialized(bool success, FDiscordUserData UserData, FString Error)
	{
		UE_LOG(LogTemp, Display, TEXT("Initialized Discord Demo Main Menu: %hhd"), success);
		if (!success)
		{
			return;
		}
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		UBeamRuntime* Runtime = GameInstance->GetSubsystem<UBeamRuntime>();
		FUserSlot TargetSlot = FUserSlot(TEXT("Player0"));
		FBeamRealmUser User;
		const bool userGrabbed = UserSlots->GetUserDataAtSlot(TargetSlot, User, this);
		if (!userGrabbed)
		{
			UE_LOG(LogTemp, Error, TEXT("DiscordDemo Main Menu, NO USER!"))
			return;
		}
		const auto AccountID = User.AccountId.AsString;
		const auto Namespace = TEXT("discord");
		const auto ServiceName = TEXT("DiscordSampleMs");
		
		const FBeamOperationEventHandlerCode LoginHandler = FBeamOperationEventHandlerCode::CreateLambda(
			[this](const FBeamOperationEvent& Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					UE_LOG(LogTemp,
						Warning,
						TEXT(
							"SteamDemoLogs [Federated Identity] Successfully SignedUp using federated identity!"
						));
					return;
				}
				UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, FAILED TO LOGIN: %s"), *Evt.EventData);
			});
		const auto OnSignUpWithDiscord = FBeamOperationEventHandlerCode::CreateLambda(
			[this, TargetSlot,Namespace,ServiceName,UserData,Runtime,LoginHandler](const FBeamOperationEvent& Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					UE_LOG(LogTemp,
					       Warning,
					       TEXT(
						       "[Federated Identity] Successfully SignedUp using federated identity!"
					       ));
					return;
				}
						// Error Handling
						if (Evt.EventData.Contains("EXTERNAL_IDENTITY_IN_USE"))
						{
					UE_LOG(LogTemp,
								Warning,
								TEXT(
									"[Federated Identity] %s User already associated with beamable account. Logging in instead."
								));
					Runtime->CPP_LoginExternalIdentityOperation(TargetSlot, ServiceName, Namespace,
					                                            UserData.OAuthToken, LoginHandler);
							
						}
						else
						{
							UE_LOG(LogTemp,Warning, TEXT("[Federated Identity] Failed To Sign Up. Reason=%s."),
												   *Evt.EventData);
						}
			});
		Runtime->CPP_AttachExternalIdentityOperation(TargetSlot, ServiceName, Namespace,
		                                             AccountID, UserData.OAuthToken,
		                                             OnSignUpWithDiscord);
	}

	UFUNCTION(BlueprintCallable)
	void InitBeam()
	{
		UE_LOG(LogTemp, Display, TEXT("Init Discord Demo Main Menu BEAM"));
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		UBeamRuntime* Runtime = GameInstance->GetSubsystem<UBeamRuntime>();

		OnBeamableReady = Runtime->CPP_RegisterOnReady(FRuntimeStateChangedHandlerCode::CreateLambda([this,Runtime]
		{
			UE_LOG(LogTemp, Display, TEXT("Init Discord Demo Main Menu BEAM"));
			OnInitialized.Broadcast();
			Runtime->CPP_UnregisterOnReady(OnBeamableReady);
		}));
	}


	UFUNCTION(BlueprintCallable)
	void InitializeDiscordDemo()
	{
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		UDiscordSubsystem* discordGameSystem = GameInstance->GetSubsystem<UDiscordSubsystem>();
		discordGameSystem->OnDiscordInitialized.BindUFunction(
			this, GET_FUNCTION_NAME_CHECKED(UDiscordDemoMainMenu, HandleDiscordInitialized));
		discordGameSystem->ManualInitialize();
	}
};
