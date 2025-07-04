// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "BeamableCoreRuntime/Public/Runtime/BeamRuntime.h"
#include "BeamableCoreRuntime/Public/Subsystems/Lobby/BeamLobbySubsystem.h"
#include "BeamableCore/Public/PIE/BeamPIEConfig.h"
#include "BeamableCore/Public/RequestTracker/BeamRequestTracker.h"
#include "BeamableCore/Public/UserSlots/BeamUserSlots.h"
#include "Subsystems/UserDeveloperManager/BeamUserDeveloperManagerEditor.h"


#include "BeamPIE.generated.h"

// UCLASS(BlueprintType, Blueprintable)
// class AMyServerBootGameMode : public AGameModeBase
// {
// 	GENERATED_BODY()
//
// public:
// 	virtual void BeginPlay() override
// 	{
// 		// Use your orchestrator's SDK to get what the Lobby Id is from their "room" setup.
// 		// Whenever you detect a lobby was assigned to this server instance, you should call:
// 		//
// 		// 	const auto NewLobbyId = FGuid(LobbyFromOrchestrator);
// 		//     const auto Lobby = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
// 		//     Lobby->CPP_RefreshLobbyDataOperation({}, FBeamOperationEventHandlerCode::CreateLambda([](FBeamOperationEvent Evt)
// 		//     {
// 		//     	   if (Evt.CompletedWithSuccess())
// 		//     	   { 
// 		//             // Once you have refreshed the lobby, if your server is properly initialized and ready to receive player connections, you should call
// 		//             Lobby->CPP_SetLobbyAsReadyForConnectionsOperation({}, NewLobbyId, {});
// 		//     	   }     	
// 		//     }), NewLobbyId);
// 	}
//
// 	virtual void PreLoginAsync(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FOnPreLoginCompleteDelegate& OnComplete) override
// 	{
// 		const auto Lobby = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
// 		UE_LOG(LogTemp, Warning, TEXT("Pre-Login - Options:%s, Id:%s"), *Options, *UniqueId.ToString());
// 		// Lobby->CPP_AcceptUserIntoGameServerOperation()
// 		Super::PreLoginAsync(Options, Address, UniqueId, OnComplete);
//
// 		// TODO: We need to make sure this is set up correctly with a sufficiently large value. 
// 		// https://forums.unrealengine.com/t/where-to-set-connectiontimeout-value/378351/4
//
//
// 		// Beamable works with the default UniqueIds (basically, we do NOT use an OnlineSubsystem to validate the user)
// 		//   - Way too much noise on those systems.		
// 		// TODO: When you join the matchmaking queue, party or lobby, we add a property for each player (which is their ULocalPlayer::UniqueNetId)		
// 		// TODO: If you are using no OnlineSubsystem here in the server, we'll validate via an Option in the travel (LobbyId+AccessToken --- our AcceptUserIntoLobbyOperation will use that
// 		// token to verify that you are in-fact you and that you are in one of the lobbies this server manages) and just leave the UniqueId untouched.		
// 		// TODO: If you are using an OnlineSubsystem here in the server, we'll use the UniqueId to validate that the user coming in from Unreal ClientTravel is
// 		// actually allowed into the server (by comparing with the property in the lobby). This allows you to use whatever subsystem you want to generate the UniqueNetIds and it'll just work with Beamable.
// 		// But if you want to avoid OnlineSubsystems in servers, you can.
//
// 		// Checks if the SDK is initialized, if not --- wait until it is.
// 		// Then, checks if the provided lobby is in the list of KnownLobbies:
// 		//   - If it is, validate the user is in it.
// 		//   - If it isn't, fetch it and then accept the users into it.
// 		// It must also keep a map of GamerTag to FUniqueNetIdRepl so that we can easily have a way of getting the gamertag from any ULocalPlayer object
// 		// https://forums.unrealengine.com/t/how-to-pass-a-custom-uniqueid-into-prelogin-from-clienttravel/459527
// 		// These should be in the lobby itself.
//
// 		// Lobby->AcceptUserIntoGameServerOperation(Options, Address, UniqueId, FBeamOperationEventHandlerCode::CreateLambda([Options, Address, UniqueId, OnComplete](FBeamOperationEvent Evt)
// 		// {
// 		// 	// If successful, just forward control back to the engine
// 		// 	if (Evt.EventType == OET_SUCCESS)
// 		// 	{				
// 		// 		Super::PreLoginAsync(Options, Address, UniqueId, OnComplete);
// 		// 	}
// 		//
// 		// 	// If failed, deny entry into the server.
// 		// 	if (Evt.EventType == OET_ERROR)
// 		// 	{
// 		// 		OnComplete.ExecuteIfBound(Evt.EventCode);				
// 		// 	}			
// 		// }));
// 	}
// };


/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamPIE : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBeamUserSlots* UserSlots;

	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	int32 InstanceOverride;

	FBeamPIE_Settings const* SelectedSettings;
	bool bFinishedSetup;

	TMap<FBeamPIE_UserSlotHandle, FDelegateHandle> LobbyJoinedHandles;
	TMap<FBeamPIE_UserSlotHandle, FDelegateHandle> UserSlotAuthenticatedHandles;

#if WITH_EDITOR
	FDelegateHandle StartPIEHandler;
	FDelegateHandle BeginPIEDelegate;
#endif


	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		// Get other engine systems
		UserSlots = Collection.InitializeDependency<UBeamUserSlots>();
		RequestTracker = Collection.InitializeDependency<UBeamRequestTracker>();

		// Reload the config.
		if (!GEngine->IsEditor())
		{
			FCoreUObjectDelegates::PreLoadMap.AddLambda([this](FString MapName)
			{
				FString GameUserSettingIni;
				if (FParse::Value(FCommandLine::Get(), TEXT("GameUserSettingsINI="), GameUserSettingIni, false))
				{
					auto InstanceStr = GameUserSettingIni.Replace(TEXT("PIEGameUserSettings"), TEXT(""));
		
					if (!FDefaultValueHelper::ParseInt(InstanceStr, InstanceOverride))
					{
						UE_LOG(LogTemp, Error, TEXT("Error on parse the override instance for the STR: %s"), *InstanceStr);
					}
				}
				UE_LOG(LogTemp, Warning, TEXT("Standalone - Reading BeamPIE Config"))

				const auto Config = GetMutableDefault<UBeamPIEConfig>();
				UE_LOG(LogTemp, Warning, TEXT("Standalone - Default Load BeamPIE Config - Is Running Server Locally: %d, Local Server Port: %s"),
					   Config->bIsRunningGameServerLocally,
					   *Config->CurrLocalServerPort);

				Config->LoadConfig(UBeamPIEConfig::StaticClass(), TEXT("BeamPIE"));
				UE_LOG(LogTemp, Warning, TEXT("Standalone - Manual  Load BeamPIE Config - Is Running Server Locally: %d, Local Server Port: %s"),
					   Config->bIsRunningGameServerLocally,
					   *Config->CurrLocalServerPort);

				bFinishedSetup = false;

				SelectedSettings = ChooseSelectedPIESettings(UWorld::RemovePIEPrefix(MapName));
			});
		
		}

#if WITH_EDITOR
		// Set up the Start PIE handler that integrates our settings with Unreal's Play Settings
		StartPIEHandler = FEditorDelegates::StartPIE.AddLambda([this](const bool)
		{
			UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
			if (!EditorWorld)
			{
				UE_LOG(LogBeamEditor, Error, TEXT("Could not find the editor world context!"));
				return;
			}
			const auto PIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			SelectedSettings = PIE->ChooseSelectedPIESettings(UWorld::RemovePIEPrefix(EditorWorld->GetMapName()));

			if (!SelectedSettings)
			{
				UE_LOG(LogBeamEditor, Verbose, TEXT("No beam pie settings found!"));
				return;
			}

			auto DeveloperUserSubsystem = GEditor->GetEditorSubsystem<UBeamUserDeveloperManagerEditor>();

			DeveloperUserSubsystem->TriggerOnPreBeginPIE(SelectedSettings);

			if (auto PlaySettings = GetMutableDefault<ULevelEditorPlaySettings>())
			{
				if (SelectedSettings->FakeLobby.bShouldAutoCreateLobby)
				{
					if (SelectedSettings->FakeLobby.bIsDedicatedServer)
					{
						// Set the Server Map name override defined in the lobby
						if (const auto OverrideProperty = PlaySettings->GetClass()->FindPropertyByName(TEXT("ServerMapNameOverride")))
						{
							if (const auto StrProperty = CastField<FStrProperty>(OverrideProperty))
							{
								FString SettingsMapName = SelectedSettings->FakeLobby.ServerStartMapOverride;
								const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(PlaySettings);
								StrProperty->SetPropertyValue(Val, SettingsMapName);
								UE_LOG(LogBeamEditor, Log, TEXT("Beam Editor - Pre-Begin PIE - Setting ServerMapNameOverride from BeamPIE Settings! SETTINGS=%s, MAP=%s"),
								       *SelectedSettings->Name, *SettingsMapName);
							}
						}
					}
				}

				// Update the UBeamPIEConfig with data from the PlaySettings
				// We do this because when launching as separate processes, we still want to know about this stuff so we can correctly decide what to do at runtime. 
				if (EPlayNetMode Mode; PlaySettings->GetPlayNetMode(Mode))
				{
					const auto bIsLaunchingLocalServer = Mode == PIE_Client || (PlaySettings->bLaunchSeparateServer && Mode == PIE_Standalone);
					auto Config = GetMutableDefault<UBeamPIEConfig>();
					Config->bIsRunningGameServerLocally = bIsLaunchingLocalServer;

					uint16 port;
					PlaySettings->GetServerPort(port);
					Config->CurrLocalServerPort = FString::FromInt(port);
					Config->Save();

					UE_LOG(LogBeamEditor, Log, TEXT("Beam Editor - Pre-Begin PIE - Configuring Settings Object from UE Settings - RUNNING_GAME_SERVER=%d, PORT=%u!"),
					       bIsLaunchingLocalServer, port);
				}
			}
			else
			{
				UE_LOG(LogBeamEditor, Warning, TEXT("Beam Editor - Pre-Begin PIE - No Play Settings Found!"));
			}
		});

		// Reload from config any changes made by our PIE Settings window + our editor extension dropdown.
		BeginPIEDelegate = FEditorDelegates::BeginPIE.AddLambda([this](bool)
		{
			UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
			if (!EditorWorld)
			{
				UE_LOG(LogBeamEditor, Error, TEXT("Could not find the editor world context!"));
				return;
			}
			bFinishedSetup = false;
		});
#endif
	}

	virtual void Deinitialize() override
	{
		Super::Deinitialize();
#if WITH_EDITOR
		FEditorDelegates::StartPIE.Remove(StartPIEHandler);
		FEditorDelegates::PreBeginPIE.Remove(BeginPIEDelegate);
#endif
	}

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamPIE* GetSelf(const UObject* CallingContext) { return GEngine->GetEngineSubsystem<UBeamPIE>(); }

	/**
	* When integrating with a game server orchestrator SDK (Hathora, Agones, etc...), you only need to run them if you are NOT running a dedicated server locally.
	* Call this ONLY inside your Game Server's GameMode. 	
	*/
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	bool RequiresGameServerOrchestratorSetup(UObject* CallingContext)
	{
#if !WITH_EDITOR
		return true;
#endif

		const auto Setting = GetSelectedPIESettings();
		if (!Setting) return true;

		// We only need to set up orchestrator if...		
		if (CallingContext)
		{
			if (const auto World = CallingContext->GetWorld())
			{
				// We are in a deployed dedicated server (not running from the editor), we won't need to set up the orchestrator's SDK.
				const auto bIsInDedicatedServer = World->IsNetMode(NM_DedicatedServer);
				if (bIsInDedicatedServer && !GetDefault<UBeamPIEConfig>()->bIsRunningGameServerLocally)
					return true;
			}
		}

		return false;
	}

	/**
	 * @brief Call this function if you want to initialize a subsystem that was set to manually initialize from the project settings.
	 * This function will initialize all the passed subsystems along with the user data
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle BeamInitPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandler OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		BeamInitPIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @copydoc BeamInitPIEOperation
	 */
	FBeamOperationHandle CPP_BeamInitPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		BeamInitPIE(CallingContext, Op);
		return Op;
	}

	/**
		 * @brief Call this function if you want to initialize a subsystem that was set to manually initialize from the project settings.
		 * This function will initialize all the passed subsystems along with the user data
		 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle BeamPreparePIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandler OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		BeamPreparePIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @copydoc BeamInitPIEOperation
	 */
	FBeamOperationHandle CPP_BeamPreparePIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		BeamPreparePIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @brief Call this function if you want run code AFTER the BeamPIE initialization has finished.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle WaitForBeamPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandler OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		WaitUntilInitPIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @copydoc WaitForBeamPIEOperation
	 */
	FBeamOperationHandle CPP_WaitForBeamPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		WaitUntilInitPIE(CallingContext, Op);
		return Op;
	}


	FBeamPIE_Settings const* GetSelectedPIESettings() const { return SelectedSettings; }

	FBeamPIE_Settings const* ChooseSelectedPIESettings(FString MapName) const
	{
#if !WITH_EDITOR
		return nullptr;
#endif

		const auto Config = GetDefault<UBeamPIEConfig>();
	
		if (Config->PerMapSelection.Contains(MapName))
		{
			const auto Id = GetDefault<UBeamPIEConfig>()->PerMapSelection[MapName];
			return Config->AllSettings.FindByPredicate([Id](FBeamPIE_Settings& S) { return S.SettingsId == Id; });
		}

		// Guaranteed to exist from editor code.
		return &GetDefault<UBeamPIEConfig>()->AllSettings[0];
	}

	FString GetLogArgs(FString Header, FWorldContext* WorldContext)
	{
		const auto CurrMapName = UWorld::RemovePIEPrefix(WorldContext->World()->GetMapName());
		return FString::Printf(TEXT("%s [Index: %d, Starting Map: %s, IsServer: %d] -"), *Header, GetPIEInstance(WorldContext), *CurrMapName, WorldContext->World()->GetNetMode() < NM_Client);
	}

	int32 GetPIEInstance(FWorldContext* WorldContext)
	{
		if (WorldContext->PIEInstance == -1)
		{
			return InstanceOverride;
		}
		return WorldContext->PIEInstance;
	}
	
	void BeamInitPIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
		ensureAlwaysMsgf(CallingContext, TEXT("You must provide a calling context to this function!"));

		// If we don't have a selected setting, don't do anything.
		const auto Settings = GetSelectedPIESettings();
		if (!Settings)
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		// Get the world
		const auto World = CallingContext->GetWorld();
		ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"));

		// Get the world context and verify that it is a PIE world.
		const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
		ensureAlwaysMsgf(WorldContext, TEXT("You should never see this!"));


		// We only run this once per-PIE-Instance-Session (this is here since people might loop back around within a single PIE session --- in which case this should not run).
		if (!bFinishedSetup)
		{
			const auto GI = World->GetGameInstance();
			ensureAlwaysMsgf(GI, TEXT("You should never see this!"));

			// Find the name of the current map and compare
			UE_LOG(LogBeamEditor, Log, TEXT("%s Initializing Beamable SDK"), *GetLogArgs(TEXT("Beam PIE Init"), WorldContext));

			const auto Runtime = GI->GetSubsystem<UBeamRuntime>();
			FBeamRuntimeHandlerCode Started;
			Started.BindLambda([this, WorldContext, Op]()
			{
				// Find the name of the current map and compare
				UE_LOG(LogBeamEditor, Log, TEXT("%s Beamable SDK Initialized"), *GetLogArgs(TEXT("Beam PIE Init"), WorldContext));
				BeamPreparePIE(WorldContext, Op);
			});

			Runtime->CPP_RegisterOnStarted_NoExecute(Started);
			Runtime->InitSDK({}, {});
		}
	}


	void BeamPreparePIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
		ensureAlwaysMsgf(CallingContext, TEXT("You must provide a calling context to this function!"));

		// If we don't have a selected setting, don't do anything.
		const auto Settings = GetSelectedPIESettings();
		if (!Settings)
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		// Get the world
		const auto World = CallingContext->GetWorld();
		ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"));

		// Get the world context and verify that it is a PIE world.
		const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
		ensureAlwaysMsgf(WorldContext, TEXT("You should never see this!"));

		BeamPreparePIE(WorldContext, Op);
	}

	void BeamPreparePIE(FWorldContext* WorldContext, FBeamOperationHandle Op)
	{
		// If we don't have a setting selected, we should just complete the operation (this happens in builds).
		const auto Setting = GetSelectedPIESettings();
		if (!Setting)
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		// Let's get the list of PIE+Slot combinations for which we have configured users.
		UE_LOG(LogBeamEditor, Log, TEXT("%s Building List of Assigned PIE Users"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
		TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles;
		for (const auto& AssignedUser : Setting->AssignedUsers)
		{
			if (AssignedUser.Key.PIEIndex == GetPIEInstance(WorldContext) || WorldContext->RunAsDedicated)
			{
				UE_LOG(LogBeamEditor, Log, TEXT("%s Found Assigned User. USER_SLOT=%s, PIE=%d"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext),
				       *AssignedUser.Key.Slot.Name, AssignedUser.Key.PIEIndex);
				PossibleSlotHandles.Add(AssignedUser.Key);
			}
		}

		// If we are in the server...
		if (WorldContext->World()->GetNetMode() < NM_Client)
		{
			// Try to create the lobby with these users in it --- keep trying until it succeeds (allow failing until all the users are online).
			// Then, when the lobby is created:				
			// IsDoneMap.Add(Kvp.Key.PIEIndex, false);
		}
		// If we are in the client... 
		else
		{
			UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Starting Preparation."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
			// Let's iterate over the users we expect and have them try to log in from cache.
			// This login will keep trying to log in from cache until it finds a user in the SLOT.
			// Our editor system NEEDS to guarantee that the user is the one we expect it to be
			// It does this by ALWAYS deleting the cached users of the configured PIE+Slot combinations before running the command to set those users up.				 
			for (const auto& CurrSlotHandle : PossibleSlotHandles)
			{
				const auto ExpectedGamerTag = Setting->AssignedUsers[CurrSlotHandle];

				const auto World = WorldContext->World();
				ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"));

				const auto GI = World->GetGameInstance();
				ensureAlwaysMsgf(GI, TEXT("You should never see this!"));

				// Set up a "retry until succeed here"
				UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Logging in from Cache. USER_SLOT=%s, PIE=%d"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext),
				       *CurrSlotHandle.Slot.Name, CurrSlotHandle.PIEIndex);

				const auto Runtime = GI->GetSubsystem<UBeamRuntime>();
				const auto LoginLocalCacheHandler = FBeamOperationEventHandlerCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamPIE, PIEClientLoginHandler),
				                                                                                    Runtime, CurrSlotHandle, PossibleSlotHandles, Op);
				Runtime->CPP_LoginFromCacheOperation(CurrSlotHandle.Slot, LoginLocalCacheHandler);
			}
		}
	}

	/**
	 * @brief Get the operation event id for the 2FA auth subevent
	 */
	UFUNCTION(BlueprintCallable)
	static inline FName GetOperationEventID_PIE_ClientLoggedIn() { return FName("ON_CLIENT_LOGGED_IN"); }

	/**
	 * Keep trying to log in with local cache until that is done, login Local Cache with the expected users.	  
	 */
	UFUNCTION()
	void PIEClientLoginHandler(FBeamOperationEvent Evt, UBeamRuntime* Runtime, FBeamPIE_UserSlotHandle CurrSlotHandle, TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles, FBeamOperationHandle PrepareOp)
	{
		if (const auto Setting = GetSelectedPIESettings())
		{
			if (Evt.CompletedWithSuccess())
			{
				// Trigger sub-event on PrepareOp "PIE_ClientLoggedIn" (let's pass in the UserSlot data)
				RequestTracker->TriggerOperationEvent(PrepareOp, OET_SUCCESS, GetOperationEventID_PIE_ClientLoggedIn(), TEXT(""));

				UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Logging in from Cache. USER_SLOT=%s, PIE=%d"), *GetLogArgs(TEXT("Beam PIE Prepare"), GEngine->GetWorldContextFromWorld(Runtime->GetWorld())),
				       *CurrSlotHandle.Slot.Name, CurrSlotHandle.PIEIndex);

				// If we are creating the fake lobby, set up a "wait until we are in the lobby operation" that will complete the PrepareOp when it finishes.
				if (Setting->FakeLobby.bShouldAutoCreateLobby)
				{
					WaitUntilClientIsInLobby(Runtime, PossibleSlotHandles, PrepareOp);
				}
				// Otherwise, check if all the users managed by this PIE instance are logged in and then complete the PrepareOp.
				else
				{
					WaitUntilClientIsLoggedIn(Runtime, PossibleSlotHandles, PrepareOp);
				}
			}

			// If we fail, create a new handler and call the Login from Cache Operation again
			// This is guaranteed to succeed eventually for all configured users.
			if (Evt.CompletedWithError())
			{
				FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([Runtime, CurrSlotHandle, this, PossibleSlotHandles, PrepareOp](const float)
				{
					const auto LoginLocalCacheHandler = FBeamOperationEventHandlerCode::CreateUFunction(
						this, GET_FUNCTION_NAME_CHECKED(UBeamPIE, PIEClientLoginHandler),
						Runtime, CurrSlotHandle, PossibleSlotHandles, PrepareOp);
					Runtime->CPP_LoginFromCacheOperation(CurrSlotHandle.Slot, LoginLocalCacheHandler);
					return false;
				}), 0.5f);
			}
		}
	}

	inline static const FString Reserved_LobbyFromPIE_Property = TEXT("__beam_lobby_from_pie_settings__");

	void WaitUntilClientIsLoggedIn(UBeamRuntime* Runtime, TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles, FBeamOperationHandle Op)
	{
		auto bAreAllUsersAlreadyLoggedIn = true;
		for (const auto& CurrHandle : PossibleSlotHandles)
		{
			FBeamRealmUser UserData;
			if (!UserSlots->GetUserDataAtSlot(CurrHandle.Slot, UserData, Runtime))
			{
				bAreAllUsersAlreadyLoggedIn = false;
				const auto UserLoggedInHandler = UserSlots->GlobalUserSlotAuthenticatedCodeHandler.AddLambda(
					[this, CurrHandle, Runtime, PossibleSlotHandles, Op]
				(const FUserSlot&, const FBeamRealmUser&, const FBeamOperationHandle&, const UObject*)
					{
						// Check to see if ALL slots managed by this PIE instance are already logged in.
						auto bAreAllSlotsInLoggedIn = true;
						for (const auto& SlotHandle : PossibleSlotHandles)
						{
							FBeamRealmUser _;
							bAreAllSlotsInLoggedIn &= UserSlots->GetUserDataAtSlot(SlotHandle.Slot, _, Runtime);
						}

						// If all slots in this instance are logged in, we are done and can complete the operation.
						if (bAreAllSlotsInLoggedIn)
						{
							UserSlots->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandles[CurrHandle]);
							UserSlotAuthenticatedHandles.Remove(CurrHandle);
							RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
						}
					});
				UserSlotAuthenticatedHandles.Add(CurrHandle, UserLoggedInHandler);
			}
		}

		if (bAreAllUsersAlreadyLoggedIn)
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		}
	}

	void WaitUntilClientIsInLobby(UBeamRuntime* Runtime, TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles, FBeamOperationHandle Op)
	{
		// For each of them, check if we already are 
		const auto LobbySystem = Runtime->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		WaitUntilClientIsLoggedIn(Runtime, PossibleSlotHandles, Op);
		return;
		// auto bAreAllUsersAlreadyInTheLobby = true;
		// for (const auto& Handle : PossibleSlotHandles)
		// {
		// 	auto LobbyState = LobbySystem->GetCurrentSlotLobbyState(Handle.Slot);
		//
		// 	// If the user is NOT already in the lobby, let's set up a notification that will trigger when they see that they've joined it.
		// 	ULobby* _ = nullptr;
		// 	if (!LobbySystem->TryGetCurrentLobby(Handle.Slot, _) && _->Data.Val.Contains(UBeamLobbySubsystem::Reserved_Lobby_From_Editor_Play_Mode_Property))
		// 	{
		// 		bAreAllUsersAlreadyInTheLobby = false;
		// 		// Add a notification for when the player joins the lobby
		// 		const auto LobbyJoinedHandle = LobbyState->OnLobbyJoinedCode.AddLambda([this, Handle, LobbySystem, LobbyState, PossibleSlotHandles, Op](const FUserSlot&, ULobby*, FLobbyUpdateNotificationMessage)
		// 		{
		// 			// Check to see if ALL slots managed by this PIE instance are already in the lobby.
		// 			auto bAreAllSlotsInTheLobby = true;
		// 			for (const auto& SlotHandle : PossibleSlotHandles)
		// 			{
		// 				ULobby* L = nullptr;
		// 				bAreAllSlotsInTheLobby &= LobbySystem->TryGetCurrentLobby(SlotHandle.Slot, L) && L->Data.Val.Contains(UBeamLobbySubsystem::Reserved_Lobby_From_Editor_Play_Mode_Property);
		// 			}
		//
		// 			// If all slots in this instance are in the lobby, we are done and can complete the operation.
		// 			if (bAreAllSlotsInTheLobby)
		// 			{
		// 				LobbyState->OnLobbyJoinedCode.Remove(LobbyJoinedHandles[Handle]);
		// 				LobbyJoinedHandles.Remove(Handle);
		// 				RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		// 			}
		// 		});
		// 		LobbyJoinedHandles.Add(Handle, LobbyJoinedHandle);
		// 	}
		// }
		//
		// if (bAreAllUsersAlreadyInTheLobby)
		// {
		// 	RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		// }
	}


	void WaitUntilInitPIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
		if (CallingContext)
		{
			if (const auto World = CallingContext->GetWorld())
			{
				// If we don't have a selected setting, don't do anything.
				const auto Setting = GetSelectedPIESettings();
				if (!Setting)
					return;

				const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
				if (WorldContext && WorldContext->WorldType == EWorldType::PIE)
				{
					// Let's wait until the local cache has files in it in accordance to what is configured in the Settings.
					TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles;
					for (const auto& AssignedUser : Setting->AssignedUsers)
					{
						if (AssignedUser.Key.PIEIndex == GetPIEInstance(WorldContext) || WorldContext->RunAsDedicated)
						{
							PossibleSlotHandles.Add(AssignedUser.Key);
						}
					}

					if (WorldContext->RunAsDedicated)
					{
						if (!Setting->FakeLobby.bShouldAutoCreateLobby)
							RequestTracker->TriggerOperationSuccess(Op, TEXT(""));

						// TODO: Wait for Lobby to be set as "Ready"
					}
					// In the clients, Init PIE will wait until the user is in the lobby.
					else
					{
						const auto Runtime = World->GetGameInstance()->GetSubsystem<UBeamRuntime>();
						if (Setting->FakeLobby.bShouldAutoCreateLobby)
						{
							WaitUntilClientIsInLobby(Runtime, PossibleSlotHandles, Op);
						}
						else
						{
							WaitUntilClientIsLoggedIn(Runtime, PossibleSlotHandles, Op);
						}
					}
				}
			}
		}
	}
};
