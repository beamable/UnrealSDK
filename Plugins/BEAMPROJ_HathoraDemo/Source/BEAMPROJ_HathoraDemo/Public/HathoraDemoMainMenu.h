// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HathoraSDK.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/PlatformApplicationMisc.h"

#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "Subsystems/Friends/BeamFriendsSubsystem.h"
#include "Subsystems/Lobby/BeamLobbySubsystem.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"
#include "Subsystems/Party/BeamPartySubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"


#include "HathoraDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegate_LoginComplete, bool, Success, const FString&, Error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);


/**
 * 
 */
UCLASS()
class BEAMPROJ_HATHORADEMO_API UHathoraDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamRuntime* Runtime;
	UPROPERTY()
	UBeamStatsSubsystem* Stats;
	UPROPERTY()
	UBeamPartySubsystem* Party;

	FDelegateHandle OnBeamableStarted;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayToGameStart = 30.0f;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Hathora Demo Main Menu"));

		const auto GI = GetWorld()->GetGameInstance();
		if (!GI || GI->IsDedicatedServerInstance()) return;

		UE_LOG(LogTemp, Warning, TEXT("Setting OnBeamStarted"));
		Runtime = GI->GetSubsystem<UBeamRuntime>();
		Party = GI->GetSubsystem<UBeamPartySubsystem>();
		Stats = GI->GetSubsystem<UBeamStatsSubsystem>();
	}

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("HathoraDemo")); }

public:

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UHathoraDemoMainMenu* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetSubsystem<UHathoraDemoMainMenu>(); }
	
	UFUNCTION(BlueprintCallable)
	void CopyText(FString Text)
	{
		FPlatformApplicationMisc::ClipboardCopy(*Text);
	}


	/**
	 * Check if the friend invited the user slot to a party
	 */
	UFUNCTION(BlueprintCallable)
	bool IsFriendInvitedToParty(FUserSlot UserSlot, FBeamGamerTag FriendId)
	{
		return DoIsFriendInvitedToParty(UserSlot, FriendId);
	}

	UFUNCTION(BlueprintCallable)
	void GetOwnerUserProfileData(FString& Id, FString& Email, FString& Alias, FString& DisplayName)
	{
		if (!Runtime) return;

		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamRealmUser UserData;
		const auto LoggedInUser = Runtime->TryGetSlotUserData(UserSlot, UserData);
		if (LoggedInUser)
		{
			Id = UserData.GamerTag.AsString;
			Email = UserData.Email;

			Stats->TryGetStat(UserSlot, Client, Public, TEXT("alias"), Alias);
			Stats->TryGetStat(UserSlot, Client, Public, TEXT("displayName"), DisplayName);
		}
	}

	/**
	 * Uses the Hathora SDK to compute pings between this client and hathora's several server regions. Stores the result in a Client Public stat. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle UpdateHathoraPingsOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		HathoraPingsOperation(UserSlot, Handle);
		return Handle;
	}

	/**
	 * @copydoc UpdateHathoraPingsOperation
	 */
	FBeamOperationHandle CPP_UpdateHathoraPingsOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		HathoraPingsOperation(UserSlot, Handle);
		return Handle;
	}

protected:
	bool DoIsFriendInvitedToParty(FUserSlot UserSlot, FBeamGamerTag FriendId)
	{
		TArray<FBeamPartyInviteState> Invites;
		if (!Party->TryGetUserInvitesState(UserSlot, Invites))
		{
			return false;
		}

		for (FBeamPartyInviteState Invite : Invites)
		{
			if (Invite.Sender == FriendId)
			{
				return true;
			}
		}
		return false;
	}


	void HathoraPingsOperation(FUserSlot UserSlot, FBeamOperationHandle Op)
	{
		FBeamRealmUser PlayerAccount;
		if (Runtime->TryGetSlotUserData(UserSlot, PlayerAccount))
		{
			FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateLambda([this, UserSlot, Op](const FHathoraRegionPings& Result)
			{
				const FString PingsJson = ConvertHathoraRegionPingsToJson(Result);

				TMap<FString, FString> StatsMap;
				StatsMap.Add("hathora_demo.pings", PingsJson);

				UBeamStatUpdateCommand* Command;
				if (Stats->TryCreateUpdateCommand(UserSlot, StatsMap, Command))
				{
					FBeamOperationEventHandlerCode Handler;
					Handler.BindLambda([this, Op](FBeamOperationEvent Evt)
					{
						UE_LOG(LogTemp, Display, TEXT("Updated Hathora Pings"));

						if (Evt.EventType == OET_SUCCESS)
						{
							UE_LOG(LogTemp, Display, TEXT("Updated Hathora Pings"));
							Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
						}
						else
						{
							UE_LOG(LogTemp, Display, TEXT("Failed to update Hathora Pings"));
							Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
						}
					});

					Stats->CPP_CommitStatsOperation(UserSlot, Handler);
				}
				else
				{
					UE_LOG(LogTemp, Display, TEXT("Failed to update Hathora Pings"));
					Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
				}
			}));
		}
		else
		{
			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});			
		}
	}

	FString ConvertHathoraRegionPingsToJson(const FHathoraRegionPings& RegionPings)
	{
		// Create a new JSON object
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		// For each pair in the Pings map, add it to the JSON object
		for (const auto& Pair : RegionPings.Pings)
		{
			JsonObject->SetNumberField(Pair.Key, Pair.Value);
		}

		// Serialize the JSON object to a string
		FString OutputString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
		{
			return OutputString;
		}

		return TEXT("{}");
	}
};
