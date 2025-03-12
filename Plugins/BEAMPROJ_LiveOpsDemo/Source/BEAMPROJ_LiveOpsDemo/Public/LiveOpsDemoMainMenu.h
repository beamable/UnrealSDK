// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamLevelSubsystem.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "AutoGen/SubSystems/BeamLiveOpsDemoMsApi.h"
#include "LiveOpsDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

/**
 * 
 */
UCLASS()
class BEAMPROJ_LIVEOPSDEMO_API ULiveOpsDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	FDelegateHandle OnBeamableReadyHandle;

	FString GetSuiMicroserviceName() const { return TEXT("SuiFederation"); }
	FString GetSuiIdentityName() const { return TEXT("SuiIdentity"); }

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("LiveOpsDemo")); }

public:
	UPROPERTY()
	UBeamRuntime* Runtime;

	UPROPERTY()
	UBeamStatsSubsystem* Stats;

	UPROPERTY()
	UBeamInventorySubsystem* Inventory;


	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnLiveOpsDemoReady;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnLiveOpsErrorConnecting;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnSampleStatUpdated;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInventoryItemsUpdated;

	UPROPERTY()
	UBeamLiveOpsDemoMSApi* LiveOpsMS;

	UPROPERTY()
	UBeamAccountsApi* AccountApi;

	UPROPERTY(BlueprintReadOnly)
	FString SuiWalletId;

	FUserSlot OwnerUserSlot;
	int64 CurrentSampleStatValue = 1;

protected:
	virtual void Deinitialize() override
	{
		Super::Deinitialize();
	}

	virtual void OnWorldBeginPlay(UWorld& InWorld) override
	{
		const auto GI = InWorld.GetGameInstance();

		// Cache all GameInstance Subsystems we'll need.
		Runtime = GI->GetSubsystem<UBeamRuntime>();
		Stats = GI->GetSubsystem<UBeamStatsSubsystem>();
		Inventory = GI->GetSubsystem<UBeamInventorySubsystem>();
		LiveOpsMS = GEngine->GetEngineSubsystem<UBeamLiveOpsDemoMSApi>();
		AccountApi = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

		// Cache the OwnerUserSlot that'll hold the user for this demo
		OwnerUserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		// Initialize the SDK
		FBeamRuntimeHandler OnSdkInitHandler;
		FRuntimeError OnSdkInitErrorHandler;
		OnSdkInitHandler.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMainMenu, OnBeamableReady));
		Runtime->InitSDK(OnSdkInitHandler, OnSdkInitErrorHandler);
	}

	UFUNCTION()
	void OnBeamableReady()
	{
		// Now that the SDK is initialized, let's log in with the Sui Wallet.

		// We start by binding a callback that will run when the user successfully signs in.
		FUserStateChangedHandler UserReadyHandler;
		UserReadyHandler.BindDynamic(this, &ULiveOpsDemoMainMenu::OnBeamableUserReady);
		Runtime->RegisterOnUserReady(UserReadyHandler);

		// Then, we sign in with a new guest account (or the second time around, this will sign in with whatever local credentials are cached)
		Runtime->CPP_LoginFrictionlessOperation(OwnerUserSlot, {});

		// Bind a callback to the Inventory Subsystem so that 
		Inventory->OnInventoryRefreshedCode.AddUObject(this, &ULiveOpsDemoMainMenu::OnInventoryRefreshed);
	}

	UFUNCTION(BlueprintCallable)
	bool IsLinkedWithSuiWallet() const { return !SuiWalletId.IsEmpty(); }

	UFUNCTION()
	void OnBeamableUserReady(const FUserSlot& UserSlot)
	{
		// First, let's get the logged in user's data 
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			// Now that the guest account is ready, we check if we are already associated with a Sui Identity			
			for (FBeamExternalIdentity ExternalIdentity : UserData.ExternalIdentities)
			{
				if (ExternalIdentity.ProviderNamespace == GetSuiIdentityName())
				{
					SuiWalletId = ExternalIdentity.UserId;
				}
			}

			// If we are NOT linked with the wallet, it means this account isn't linked with a Sui Wallet yet so we need to attach a Sui Identity to this account. 
			if (!IsLinkedWithSuiWallet())
			{
				// First, let's declare a handler for what we'll do AFTER we have attached the account.
				const auto OnSuiIdentityAttachedHandler = FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
				{
					// If successful, we'll get the WalletId. 
					if (Evt.EventType == OET_SUCCESS)
					{
						// Then, we make a GetMe request to get the updated account data containing the auto-created wallet id.

						// We start by declaring the handler of what we'll do once we get the user data containing the auto-created wallet id.
						FBeamRequestContext RequestContext;
						const auto GetMeHandler = FOnBasicAccountsGetMeFullResponse::CreateLambda([this](FBasicAccountsGetMeFullResponse Resp)
						{
							if (Resp.State == RS_Success)
							{
								// Because the wallet is auto-created, the external identity isn't known by this client until we called GetMe.
								// So... now we need to update the local client's in-memory RealmUser's list of external identities.
								const auto ExternalIdentities = Resp.SuccessData->External;
								if (ExternalIdentities.IsSet)
								{
									// Loop through all external ids attached to this account and find the Sui one.
									// When we do, store the identity containing the UserId it in the local array and update the SuiWalletId. 
									for (const FBeamExternalIdentity& Val : ExternalIdentities.Val)
									{
										if (Val.ProviderService == GetSuiMicroserviceName() && Val.ProviderNamespace == GetSuiIdentityName())
										{
											FBeamRealmUser User;
											if (Runtime->UserSlotSystem->GetUserDataAtSlot(OwnerUserSlot, User, this))
											{
												// Cache the Wallet Id here so our UI can easily access it for the "Open Wallet" button.
												SuiWalletId = Val.UserId;

												// Update the local state with the auto-created id.
												User.ExternalIdentities.AddUnique(Val);
												Runtime->UserSlotSystem->SetExternalIdsAtSlot(OwnerUserSlot, User.ExternalIdentities, this);
												Runtime->UserSlotSystem->SaveSlot(OwnerUserSlot, this);
											}
										}
									}
								}

								// Then, we can proceed with the sample flow
								OnLiveOpsDemoReady.Broadcast();
							}
							else
							{
								UE_LOG(LogTemp, Error, TEXT("Failed to fetch user! ERROR=%s"), *Resp.ErrorData.message);
								OnLiveOpsErrorConnecting.Broadcast();
							}
						});

						// Then we make the request.
						const auto GetMeReq = UBasicAccountsGetMeRequest::Make(GetTransientPackage(), {});
						AccountApi->CPP_GetMe(OwnerUserSlot, GetMeReq, GetMeHandler, RequestContext, {}, this);
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Could not attach identity! ERROR=%s"), *Evt.EventCode);
						OnLiveOpsErrorConnecting.Broadcast();
					}
				});

				// Now that we have the handler defined, we ask the Beamable SDK to attach the Sui identity to our new account.
				// This should run once per new user.
				Runtime->CPP_AttachExternalIdentityOperation(OwnerUserSlot,
				                                             GetSuiMicroserviceName(),
				                                             GetSuiIdentityName(),
				                                             TEXT(""),
				                                             TEXT(""),
				                                             OnSuiIdentityAttachedHandler);
			}
			// If we already have an Sui Wallet associated with our account
			// To create new accounts when interacting with this sample in PIE, hit the Reset PIE Users button in the Beamable Window. 
			else
			{
				// Then, we can proceed with the sample flow
				OnLiveOpsDemoReady.Broadcast();
			}			
		}
	}

	UFUNCTION()
	void OnInventoryRefreshed(FBeamGamerTag GamerTag, FUserSlot UserSlot)
	{
		OnInventoryItemsUpdated.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void GetInventoryData(int64& GemsCount, int64& CoinsCount, TArray<FBeamItemState>& SampleItems)
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			FString GemsID = "currency.gems";
			FString CoinsID = "currency.coins";

			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag, GemsID, GemsCount);
			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag, CoinsID, CoinsCount);

			TArray<FBeamItemState> AllItems;
			Inventory->TryGetAllItemsByGamerTag(UserData.GamerTag, AllItems);

			for (auto ItemState : AllItems)
			{
				if (ItemState.ContentId.AsString == "items.sample_item")
				{
					SampleItems.Add(ItemState);
				}
			}
		}
	}

	UFUNCTION(BlueprintCallable)
	void IncrementSampleStat()
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			TMap<FString, FString> Empty;
			ULiveOpsDemoMSIncrementStatRequest* Request =
				ULiveOpsDemoMSIncrementStatRequest::Make(UserData.GamerTag.AsLong, this, Empty);

			const auto Handler = FOnLiveOpsDemoMSIncrementStatFullResponse::CreateLambda(
				[this,UserData](FBeamFullResponse<ULiveOpsDemoMSIncrementStatRequest*, ULiveOpsDemoMSIncrementStatResponse*> Resp)
				{
					if (Resp.SuccessData)
					{
						CurrentSampleStatValue++;
						OnSampleStatUpdated.Broadcast();
					}
				});
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_IncrementStat(UserSlot, Request, Handler, Ctx, {}, this);
		}
	}

	UFUNCTION(BlueprintCallable)
	int64 GetSampleStat()
	{
		return CurrentSampleStatValue;
	}

	UFUNCTION(BlueprintCallable)
	void UpgradeItem(int64 ItemInstanceID)
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			TMap<FString, FString> Empty;
			ULiveOpsDemoMSUpgradeItemRequest* Request =
				ULiveOpsDemoMSUpgradeItemRequest::Make(UserData.GamerTag.AsLong, ItemInstanceID, this, Empty);

			const auto Handler = FOnLiveOpsDemoMSUpgradeItemFullResponse::CreateLambda(
				[this,UserData](FBeamFullResponse<ULiveOpsDemoMSUpgradeItemRequest*, ULiveOpsDemoMSUpgradeItemResponse*> Resp)
				{
					if (Resp.SuccessData)
					{
						OnInventoryItemsUpdated.Broadcast();
					}
				});
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_UpgradeItem(UserSlot, Request, Handler, Ctx, {}, this);
		}
	}
};
