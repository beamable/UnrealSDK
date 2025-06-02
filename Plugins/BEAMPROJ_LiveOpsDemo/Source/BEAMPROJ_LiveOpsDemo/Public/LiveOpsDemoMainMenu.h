// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamLevelSubsystem.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "AutoGen/SubSystems/BeamLiveOpsDemoMsApi.h"
#include "LiveOpsDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnReceiveTwoFactorChallenge, FUserSlot, UserSlot, FString, DecodedChallenge, UChallengeSolutionObject*, ChallengeSolution);

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
	FString GetSuiExternalIdentityName() const { return TEXT("SuiExternalIdentity"); }

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
	FDelegate_Simple OnLoginError;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnAttachError;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple ShowLoginScreen;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnSampleStatUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnReceiveTwoFactorChallenge OnReceiveTwoFactorChallenge;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInventoryItemsUpdated;

	UPROPERTY()
	UBeamLiveOpsDemoMSApi* LiveOpsMS;

	UPROPERTY()
	UBeamAccountsApi* AccountApi;

	UPROPERTY(BlueprintReadOnly)
	FString SuiWalletId;

	UPROPERTY(BlueprintReadOnly)
	FString SuiWalletIdExternal;

	UPROPERTY(BlueprintReadOnly)
	FBeamContentId BeamSuiCoinsId;
	UPROPERTY(BlueprintReadOnly)
	FBeamContentId StarSuiCoinsId;
	UPROPERTY(BlueprintReadOnly)
	FBeamContentId GoldSuiGameCoinsId;
	UPROPERTY(BlueprintReadOnly)
	FBeamContentId DarksaberSuiWeaponId;
	UPROPERTY(BlueprintReadOnly)
	FBeamContentId ShisuiSuiWeaponId;

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

		//Clean up when the user logout
		FUserStateChangedHandler UserClearedHandler;
		UserClearedHandler.BindDynamic(this, &ULiveOpsDemoMainMenu::OnBeamableUserCleared);
		Runtime->RegisterOnUserCleared(UserClearedHandler);

		// Bind a callback to the Inventory Subsystem so that 
		Inventory->OnInventoryRefreshedCode.AddUObject(this, &ULiveOpsDemoMainMenu::OnInventoryRefreshed);

		// Prepare some Ids that are relevant for this demo
		BeamSuiCoinsId = FBeamContentId{FString("currency.coin.beam")};
		StarSuiCoinsId = FBeamContentId{FString("currency.coin.star")};
		GoldSuiGameCoinsId = FBeamContentId{FString("currency.game_coin.gold")};
		DarksaberSuiWeaponId = FBeamContentId{FString("items.weapon.darksaber")};
		ShisuiSuiWeaponId = FBeamContentId{FString("items.weapon.shisui")};

		Runtime->CPP_LoginFromCacheOperation(OwnerUserSlot, FBeamOperationEventHandlerCode::CreateLambda([this](const FBeamOperationEvent& Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				UE_LOG(LogTemp, Display, TEXT("Login user from the cache."));
			}
			else
			{
				ShowLoginScreen.Broadcast();
			}
		}));
	}

	UFUNCTION(BlueprintCallable)
	void DoGuestLogin()
	{
		// Then, we sign in with a new guest account (or the second time around, this will sign in with whatever local credentials are cached)
		Runtime->CPP_LoginFrictionlessOperation(OwnerUserSlot, {});
	}

	UFUNCTION(BlueprintCallable)
	void DoIdentityLogin(FString WalletKey)
	{
		SuiWalletId = WalletKey;
		// Cache the SUIWallet to use in the two factor step
		const auto OnSuiIdentityHandler = FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				// Then, we can proceed with the sample flow
				OnLiveOpsDemoReady.Broadcast();
			}
			else
			{
				// Login error sent back to login menu
				OnLoginError.Broadcast();
			}
			// If successful, we will get the two factor challenge
			if (Evt.EventType == OET_SUCCESS)
			{
				UChallengeSolutionObject* ChallengeSolution = Cast<UChallengeSolutionObject>(Evt.EventData.GetInterface());

				FString ChallengeToken;
				FString _;
				// The challenge comes as a base 64 encoded with more information separated by "."
				ChallengeSolution->ChallengeToken.Split(TEXT("."), &ChallengeToken, &_);
				FString DecodedChallenge = GetBase64Decode(ChallengeToken);

				OnReceiveTwoFactorChallenge.Broadcast(OwnerUserSlot, DecodedChallenge, ChallengeSolution);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not login for identity! ERROR=%s"), *Evt.EventCode);
				OnLoginError.Broadcast();
			}
		});

		Runtime->CPP_LoginExternalIdentityOperation(OwnerUserSlot, GetSuiMicroserviceName(),
		                                            GetSuiIdentityName(),
		                                            SuiWalletId,
		                                            OnSuiIdentityHandler);
	}


	UFUNCTION(BlueprintCallable)
	void DoTwoFactorIdentityAttach(FString WalletKey)
	{
		SuiWalletIdExternal = WalletKey;
		// Cache the SUIWallet to use in the two factor step
		const auto OnSuiIdentityHandler = FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
		{
			// If successful, we will get the two factor challenge
			if (Evt.EventType == OET_SUCCESS)
			{
				UChallengeSolutionObject* ChallengeSolution = Cast<UChallengeSolutionObject>(Evt.EventData.GetInterface());

				FString ChallengeToken;
				FString _;
				// The challenge comes as a base 64 encoded with more information separated by "."
				ChallengeSolution->ChallengeToken.Split(TEXT("."), &ChallengeToken, &_);
				FString DecodedChallenge = GetBase64Decode(ChallengeToken);

				OnReceiveTwoFactorChallenge.Broadcast(OwnerUserSlot, DecodedChallenge, ChallengeSolution);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not attach for identity! ERROR=%s"), *Evt.EventCode);
				OnAttachError.Broadcast();
			}
		});

		Runtime->CPP_BeginAttachExternalIdentityTwoFactorOperation(OwnerUserSlot, GetSuiMicroserviceName(),
		                                                           GetSuiExternalIdentityName(),
		                                                           SuiWalletIdExternal,
		                                                           OnSuiIdentityHandler);
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

								// Then, we grant a bit of currency of each type for new users
								// These are client authoritative --- if these items were server authoritative, you could use a PlayerInit federation to grant these from microservice code.
								FBeamInventoryUpdateCommand Cmds;
								Inventory->BeginInventoryUpdate(OwnerUserSlot, Cmds, true);
								Inventory->PrepareAddCurrency(OwnerUserSlot, GoldSuiGameCoinsId, 1);
								Inventory->PrepareAddCurrency(OwnerUserSlot, StarSuiCoinsId, 2);
								Inventory->PrepareAddCurrency(OwnerUserSlot, BeamSuiCoinsId, 3);
								Inventory->PrepareCreateItem(OwnerUserSlot, DarksaberSuiWeaponId, {{"$itemLevel", "1"}});
								Inventory->PrepareCreateItem(OwnerUserSlot, ShisuiSuiWeaponId, {{"$itemLevel", "1"}});
								Inventory->CPP_CommitInventoryUpdateOperation(OwnerUserSlot, FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
								{
									// Then, we can proceed with the sample flow
									OnLiveOpsDemoReady.Broadcast();
								}));
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
						UE_LOG(LogTemp, Error, TEXT("Could not attach 2FA identity! ERROR=%s"), *Evt.EventCode);
						OnLiveOpsErrorConnecting.Broadcast();
					}
				});


				// Now that we have the handler defined, we ask the Beamable SDK to get the 2FA to our new account.
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
				OnLiveOpsDemoReady.Broadcast();
			}
		}
	}

	UFUNCTION()
	void OnBeamableUserCleared(const FUserSlot& UserSlot)
	{
		// On logout we clean up the SUI Wallet id
		SuiWalletId = "";
	}

	UFUNCTION(BlueprintCallable)
	void SendTwoFactorOperationHandler(FUserSlot UserSlot, UChallengeSolutionObject* ChallengeSolution)
	{
		const auto OnSuitIdentityFinishTwoFactorHandler = FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				// Then, we can proceed with the sample flow
				OnLiveOpsDemoReady.Broadcast();
			}
			else
			{
				// back to main content screen
				OnAttachError.Broadcast();
			}
		});

		// Now that we have the handler defined, we ask the Beamable SDK to attach the Sui identity to our new account.
		// This should run once per new user.
		Runtime->CPP_CommitAttachExternalIdentityTwoFactorOperation(UserSlot,
		                                                            GetSuiMicroserviceName(),
		                                                            GetSuiExternalIdentityName(),
		                                                            SuiWalletIdExternal,
		                                                            TEXT(""),
		                                                            ChallengeSolution,
		                                                            OnSuitIdentityFinishTwoFactorHandler);
	}

	FString GetBase64Decode(FString Base64String)
	{
		TArray<uint8> DecodedBytes;
		bool bSuccess = FBase64::Decode(Base64String, DecodedBytes);

		if (bSuccess)
		{
			// Convert the decoded bytes to a string
			FString DecodedString;
			for (uint8 Byte : DecodedBytes)
			{
				DecodedString += (TCHAR)Byte;
			}

			return DecodedString;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Base64 decoding failed!"));
		}

		return "";
	}

	UFUNCTION()
	void OnInventoryRefreshed(FBeamGamerTag GamerTag, FUserSlot UserSlot)
	{
		OnInventoryItemsUpdated.Broadcast();
	}


	UFUNCTION(BlueprintCallable)
	void GetInventoryData(int64& BeamSuiCoins, int64& StarSuiCoins, int64& GoldSuiGameCoins, TArray<FBeamItemState>& SampleItems)
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag, BeamSuiCoinsId, BeamSuiCoins);
			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag, StarSuiCoinsId, StarSuiCoins);
			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag, GoldSuiGameCoinsId, GoldSuiGameCoins);

			TArray<FBeamItemState> AllItems;
			Inventory->TryGetAllItemsByGamerTag(UserData.GamerTag, AllItems);

			const auto RelevantItemIds = TArray{DarksaberSuiWeaponId, ShisuiSuiWeaponId};
			for (auto ItemState : AllItems)
			{
				if (RelevantItemIds.ContainsByPredicate([ItemState](const FBeamContentId& RelevantItemId) { return ItemState.ContentId == RelevantItemId; }))
				{
					SampleItems.Add(ItemState);
				}
			}
		}
	}

	UFUNCTION(BlueprintCallable)
	void UpgradeItem(int64 ItemInstanceID)
	{
		TArray<FBeamItemState> AllItems;
		if (Inventory->TryGetAllItems(OwnerUserSlot, AllItems))
		{
			// Find the item with the given id.
			const auto ItemIdx = AllItems.Find(FBeamItemState{{}, ItemInstanceID});
			if (ItemIdx != INDEX_NONE)
			{
				FBeamItemState Item = AllItems[ItemIdx];

				// Increment the current item level
				const auto CurrLevelStr = Item.Properties.Find(TEXT("itemLevel"));
				if (CurrLevelStr)
				{
					int64 NewLevel;
					FDefaultValueHelper::ParseInt64(*CurrLevelStr, NewLevel);
					NewLevel += 1;
					Item.Properties[TEXT("itemLevel")] = FString::Printf(TEXT("%lld"), NewLevel);
				}

				// Modify the item
				FBeamInventoryUpdateCommand Cmds;
				Inventory->BeginInventoryUpdate(OwnerUserSlot, Cmds, true);
				Inventory->PrepareModifyItem(OwnerUserSlot, Item);
				Inventory->CPP_CommitInventoryUpdateOperation(OwnerUserSlot, FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
				{
					// Once the modification is done, update the UI.
					OnInventoryItemsUpdated.Broadcast();
				}));
			}
		}
	}
};
