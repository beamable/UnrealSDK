// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemTypes.h"
#include "AutoGen/SubSystems/BeamLobbyApi.h"
#include "AutoGen/SubSystems/BeamPlayerLobbyApi.h"
#include "AutoGen/SubSystems/Lobby/PutLobbiesRequest.h"
#include "AutoGen/SubSystems/PlayerLobby/ApiPlayerLobbyGetLobbiesByPlayerIdRequest.h"
#include "Subsystems/EngineSubsystem.h"
#include "BeamableCoreRuntime/Public/Runtime/BeamRuntime.h"
#include "BeamableCoreRuntime/Public/Subsystems/Lobby/BeamLobbySubsystem.h"
#include "BeamableCore/Public/PIE/BeamPIEConfig.h"
#include "BeamableCore/Public/RequestTracker/BeamRequestTracker.h"
#include "BeamableCore/Public/UserSlots/BeamUserSlots.h"
#include "Content/BeamContentTypes/BeamGameTypeContent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PIE/BeamPIE_Utilities.h"
#include "Subsystems/Content/BeamContentSubsystem.h"

#if WITH_EDITOR
#include "Subsystems/Microservices/BeamMicroservicesEditor.h"
#include "Subsystems/UserDeveloperManager/BeamUserDeveloperManagerEditor.h"
#endif


#include "BeamPIE.generated.h"


/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamPIE : public UEngineSubsystem
{
	GENERATED_BODY()

	friend class UBeamRuntime;

	static inline FBeamPIE_Settings DefaultSettingsPtr = {};

public:
	/**
	 * Fallback setting we use when there are no selected settings for the map.
	 * Essentially, it does nothing.
	 */
	static FBeamPIE_Settings const* DefaultSettings()
	{
		if (!DefaultSettingsPtr.IsDefaultSettings())
		{
			DefaultSettingsPtr = {};
			DefaultSettingsPtr.SettingsId = FBeamPIE_Settings::DefaultPieSettingsGuid;
			DefaultSettingsPtr.Name = TEXT("Default");
			DefaultSettingsPtr.AssignedUsers = {};
			DefaultSettingsPtr.AllowedMapNamePattern = TEXT("*");
			DefaultSettingsPtr.AllowedInMaps = {};
			DefaultSettingsPtr.FakeLobby = FBeamPIE_LobbySettings{
				false,
				false,
			};
		}
		return &DefaultSettingsPtr;
	}

	/**
	 * @brief Get the operation event id for a sub-event that is triggered whenever a user signs in during the @link BeamPreparePIE @endlink flow.
	 */
	UFUNCTION(BlueprintCallable)
	static inline FName GetOperationEventID_PIE_ClientLoggedIn() { return FName("ON_CLIENT_LOGGED_IN"); }

	UPROPERTY()
	UBeamUserSlots* UserSlots;

	UPROPERTY()
	UBeamBackend* Backend;

	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	/**
	 * Pointer to the currently selected settings.
	 * In the editor or separate-process-PIE-instances, this will always point to something inside @link UBeamPIEConfig::AllSettings @endlink OR to the @link DefaultSettings @endlink.
	 * In builds, this is always null.
	 */
	FBeamPIE_Settings const* SelectedSettings;

	/**
	 * This ensures that the init flow only runs once per PIE run (even if you circle back to the starting map).
	 */
	bool bInitBeamPIERequested = false;

	TMap<FBeamPIE_UserSlotHandle, FDelegateHandle> LobbyJoinedHandles;
	TMap<FBeamPIE_UserSlotHandle, FDelegateHandle> UserSlotAuthenticatedHandles;
	TMap<FBeamPIE_UserSlotHandle, FBeamGamerTag> ServerGamerTags;

	TMap<int32, FBeamOperationHandle> ClientDelayMapHandles;

	/**
	 * This is irrelevant on the client --- only matters in the server. 
	 */
	FString FakeLobbyId = "";

	/**
	 * This is irrelevant on the server -- only matters in the client.
	 * Keep the reference for the fake options 
	 */
	FString FakeOptions = "";

	FString const WaitRoomLevel = "L_Beamable_PIEWaitRoom";

	/**
	 * This is irrelevant on the client --- only matters in the server. 
	 */
	int32 PreLoginExpectingPieIndex;

	/**
	 * This is irrelevant on the client --- only matters in the server. 
	 */
	int32 PreLoginExpectingUserSlotInPieIndex;

#if WITH_EDITOR
	FDelegateHandle StartPIEHandler;
#endif

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);

		// Get other engine systems
		Backend = Collection.InitializeDependency<UBeamBackend>();
		UserSlots = Collection.InitializeDependency<UBeamUserSlots>();
		RequestTracker = Collection.InitializeDependency<UBeamRequestTracker>();

		// Set the default settings
		SelectedSettings = DefaultSettings();
		PreLoginExpectingPieIndex = 1; // Starts at one because all PIE clients are instances 1~X.
		PreLoginExpectingUserSlotInPieIndex = 0; // Starts at one because this indexes into UBeamCoreSettings::RuntimeUserSlots for each PreLoginExpectingPieIndex.
		bInitBeamPIERequested = false;
		ClientDelayMapHandles.Reset();

#if WITH_EDITOR

		// This runs only when in PIE "Play as Standalone" (or whenever you configure PIE multiplayer to run as a separate process.
		// This code forcibly loads the BeamPIE.ini file and then selects the appropriate settings (and apply relevant configurations).
		if (!GEngine->IsEditor())
		{
			// Then, we get the BeamPIEConfig and ensure it's values are loaded.
			const auto Config = GetMutableDefault<UBeamPIEConfig>();
			const auto CoreSettings = GetMutableDefault<UBeamCoreSettings>();
			UE_LOG(LogTemp, Warning, TEXT("Standalone - Default Load BeamPIE Config - Is Running Server Locally: %d, Local Server Port: %s, TargetRealm: %s, RoutingKeyMap: %s"),
			       Config->bIsRunningGameServerLocally,
			       *Config->CurrLocalServerPort,
			       *CoreSettings->TargetRealm.Pid.AsString,
			       *Config->CurrRoutingKeyMap);

			Config->LoadConfig();
			UE_LOG(LogTemp, Warning, TEXT("Standalone - Manual  Load BeamPIE Config - Is Running Server Locally: %d, Local Server Port: %s, TargetRealm: %s, RoutingKeyMap: %s"),
			       Config->bIsRunningGameServerLocally,
			       *Config->CurrLocalServerPort,
			       *CoreSettings->TargetRealm.Pid.AsString,
			       *Config->CurrRoutingKeyMap);

			// First, we parse out which PIE-instance this is from an argument that Unreal sends down to every separate-process-PIE.
			int _;
			if (!FBeamPIE_Utilities::GetPIEInstanceFromCommandLine(_))
			{
				UE_LOG(LogBeamEditor, Error, TEXT("Failed to read expected `GameUserSettingsINI` argument from separate-process-PIE-instance."));
				SelectedSettings = DefaultSettings();
			}

			// Then, we apply the realm secret and the routing key map
			Backend->RealmSecret = Config->CurrRealmSecret;
			Backend->SetRoutingKeyMap(Config->CurrRoutingKeyMap);

			const auto MapName = Config->CurrPIEMap;
			UE_LOG(LogTemp, Warning, TEXT("MAP NAME: %s"), *MapName);
			SelectedSettings = ChooseSelectedPIESettings(*MapName);
		}

		// This block of code sets up the in-editor state for this system --- this runs for when you are entering PIE with all instances `Running Under One Process`.
		// Regardless of whether we are Running Under One Process`, this runs before the PIE instances are open and therefore we can make modifications to parameters in ULevelEditorPlaySettings.
		// Today, we add a few arguments for when we run PIE on separate processes such that it can work with local microservices and BeamPIE.
		StartPIEHandler = FEditorDelegates::StartPIE.AddLambda([this](const bool)
		{
			// Reset all the internal state we use to initialize BeamPIE every time we go into play mode
			{
				bInitBeamPIERequested = false;
				FakeLobbyId.Empty();
				PreLoginExpectingPieIndex = 1; // Starts at one because all PIE clients are instances 1~X.
				PreLoginExpectingUserSlotInPieIndex = 0; // Starts at one because this indexes into UBeamCoreSettings::RuntimeUserSlots for each PreLoginExpectingPieIndex.}
				ClientDelayMapHandles.Reset();
			}

			// Get the editor world so we can figure out what map is currently open (and, therefore, the map through which we are entering PIE).
			UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
			if (!EditorWorld)
			{
				UE_LOG(LogBeamEditor, Error, TEXT("Could not find the editor world context!"));
				return;
			}

			// Select the settings based on our current map.
			const auto PIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			const auto TargetMapName = UWorld::RemovePIEPrefix(EditorWorld->GetMapName());
			SelectedSettings = PIE->ChooseSelectedPIESettings(TargetMapName);

			// If we found no settings, something went wrong. Still, we fallback to the default settings.
			if (!SelectedSettings)
			{
				UE_LOG(LogBeamEditor, Error, TEXT("No beam pie settings found for map %s! Falling back to default settings!"), *EditorWorld->GetMapName());
				SelectedSettings = DefaultSettings();
			}

			// Now, we do some setup regarding the parameters with which we'll be starting the PIE instances.
			if (auto PlaySettings = GetMutableDefault<ULevelEditorPlaySettings>())
			{
				// We start by asking the UBeamUserDeveloperManagerEditor to configure any mapped cached users in the `Saved/Beamable/UserSlots` directory.
				// This makes it so that, when we `LoginCached` as part of our `BeamInitPIE`, the mapped users will be the ones we are loading.
				// This may also clone the mapped users and use the clone depending on the settings. 
				{
					auto DeveloperUserSubsystem = GEditor->GetEditorSubsystem<UBeamUserDeveloperManagerEditor>();
					DeveloperUserSubsystem->TriggerOnPreBeginPIE(PlaySettings, SelectedSettings);
				}

				// Then, if we are creating a FakeLobby in which we'll test our dedicated server map, we can define that map as the ServerMapOverride.
				// This is useful when you want to have a few settings that will always start on a specific map (this means you don't have to manually configure that in UE's Advanced Networking tabs).				
				if (SelectedSettings->FakeLobby.bShouldAutoCreateLobby)
				{
					if (SelectedSettings->FakeLobby.bIsDedicatedServer)
					{
						// Set the Server Map name override defined in the lobby
						if (const auto OverrideProperty = PlaySettings->GetClass()->FindPropertyByName(TEXT("ServerMapNameOverride")))
						{
							if (const auto StrProperty = CastField<FStrProperty>(OverrideProperty))
							{
								if (SelectedSettings->FakeLobby.ServerStartMapOverride.IsValid())
								{
									FString SettingsMapName = SelectedSettings->FakeLobby.ServerStartMapOverride->GetMapName();
									const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(PlaySettings);
									StrProperty->SetPropertyValue(Val, SettingsMapName);
									UE_LOG(LogBeamEditor, Log, TEXT("Beam Editor - Pre-Begin PIE - Setting ServerMapNameOverride from BeamPIE Settings! SETTINGS=%s, MAP=%s"),
									       *SelectedSettings->Name, *SettingsMapName);
								}
							}
						}
					}
				}

				auto Config = GetMutableDefault<UBeamPIEConfig>();
				// Then, we update the BeamPIEConfig (the one inside `Saved/Config/WindowsEditor`) to reflect whether we are running game server locally (and its port).				
				// We do this because when launching as separate processes, we still want to know about this so we can correctly decide what to do at runtime.
				// Basically, 
				if (EPlayNetMode Mode; PlaySettings->GetPlayNetMode(Mode))
				{
					const auto bIsLaunchingLocalServer = Mode == PIE_Client || (PlaySettings->bLaunchSeparateServer && Mode == PIE_Standalone);
					Config->bIsRunningGameServerLocally = bIsLaunchingLocalServer;

					uint16 port;
					PlaySettings->GetServerPort(port);
					Config->CurrLocalServerPort = FString::FromInt(port);
					UE_LOG(LogBeamEditor, Log, TEXT("Beam Editor - Pre-Begin PIE - Configuring Settings Object from UE Settings - RUNNING_GAME_SERVER=%d, PORT=%u!"),
					       bIsLaunchingLocalServer, port);
				}

				// Finally, we ask the MicroserviceEditor subsystem to fill out the realm secret and the routing key map into the arguments 
				{
					auto MicroserviceEditorSubsystem = GEditor->GetEditorSubsystem<UBeamMicroservicesEditor>();
					Config->CurrRoutingKeyMap = MicroserviceEditorSubsystem->ConstructRoutingKeyMap();
					Config->CurrTargetRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;
					Config->CurrPIEMap = TargetMapName;

					auto EditorSubsystem = GEditor->GetEditorSubsystem<UBeamEditor>();
					FBeamCustomerProjectData ProjectData;
					FBeamProjectRealmData RealmData;
					if (EditorSubsystem->GetActiveProjectAndRealmData(ProjectData, RealmData))
					{
						Config->CurrRealmSecret = RealmData.RealmSecret;
					}

					Backend->RealmSecret = Config->CurrRealmSecret;
					Backend->SetRoutingKeyMap(Config->CurrRoutingKeyMap);
				}

				Config->Save();
			}
			else
			{
				UE_LOG(LogBeamEditor, Warning, TEXT("Beam Editor - Pre-Begin PIE - No Play Settings Found!"));
			}

			// Reset the state of this BeamPIE so we can coordinate the init flow.			
			LobbyJoinedHandles.Reset();
			UserSlotAuthenticatedHandles.Reset();
		});
#endif
	}

	virtual void Deinitialize() override
	{
		Super::Deinitialize();
#if WITH_EDITOR
		FEditorDelegates::StartPIE.Remove(StartPIEHandler);
#endif
	}

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamPIE* GetSelf(const UObject* CallingContext) { return GEngine->GetEngineSubsystem<UBeamPIE>(); }

	/**
	 * Get a mutable reference to the beam config for blueprint cache
	 */
	UFUNCTION(BlueprintCallable)
	void GetMutableBeamConfig(UBeamPIEConfig*& BeamConfig)
	{
		BeamConfig = GetMutableDefault<UBeamPIEConfig>();
	}

	/**
	 * Save a beam config passing a mutable reference
	 */
	UFUNCTION(BlueprintCallable)
	void SaveMutableBeamConfig(UBeamPIEConfig* BeamConfig)
	{
		BeamConfig->Save();
	}

	/**
	 * When integrating with a game server orchestrator SDK (Hathora, Agones, etc...), you only need to run them if you are NOT running a dedicated server locally.
	 * This function returns `true` only in those cases.
	 *
	 * This function is meant to be called in your dedicated server's start up flow in order to decide whether your orchestrator's SDK needs initialization or not.
	 * You can also call this in clients to avoid doing orchestrator work, if your it also has a Client SDK for whatever reason. 
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	bool RequiresGameServerOrchestratorSetup(const UObject* CallingContext)
	{
#if !WITH_EDITOR
		return true;
#endif

		const auto Settings = GetSelectedPIESettings();
		if (!Settings || Settings->IsDefaultSettings()) return true;

		// We only need to set up orchestrator if...		
		if (CallingContext)
		{
			// We are in a deployed dedicated server (not running from the editor), we won't need to set up the orchestrator's SDK.				
			if (!GetDefault<UBeamPIEConfig>()->bIsRunningGameServerLocally)
				return true;
		}

		return false;
	}


	FString GetExpectedClientPIEOptions(FString Options, UObject* CallingContext)
	{
#if !WITH_EDITOR
		return Options;
#endif

		const auto bHasGamerTag = UGameplayStatics::HasOption(Options, "BeamGamerTag_0");
		const auto bHasAccessToken = UGameplayStatics::HasOption(Options, "BeamAccessToken_0");
		const auto bHasRefreshToken = UGameplayStatics::HasOption(Options, "BeamRefreshToken_0");
		if (bHasGamerTag || bHasAccessToken || bHasRefreshToken)
			return Options;

		// If we are not using a PIE setting, we should not be doing anything here.
		const auto CurrSettings = GetSelectedPIESettings();
		if (!CurrSettings || CurrSettings->IsDefaultSettings())
			return Options;

		// Get the world
		const auto World = CallingContext->GetWorld();
		ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"));

		// Get the world context.
		const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
		ensureAlwaysMsgf(WorldContext, TEXT("You should never see this!"));

		const auto GI = World->GetGameInstance();
		ensureAlwaysMsgf(GI, TEXT("You should never see this!"));

		const auto Lobby = GI->GetSubsystem<UBeamLobbySubsystem>();

		const auto CurrPieIdx = PreLoginExpectingPieIndex;
		const auto CurrSlotIdx = PreLoginExpectingUserSlotInPieIndex;

		TArray<FUserSlot> OrderedSlots;
		for (const auto& Kvp : CurrSettings->AssignedUsers)
		{
			if (Kvp.Key.PIEIndex == CurrPieIdx)
			{
				OrderedSlots.Add(Kvp.Key.Slot);
			}
		}

		// Order the slots as we expect them to arrive
		const auto CoreSettings = GetDefault<UBeamCoreSettings>();
		OrderedSlots.StableSort([CoreSettings](FUserSlot A, FUserSlot B)
		{
			const auto IdxA = CoreSettings->RuntimeUserSlots.Find(A.Name);
			const auto IdxB = CoreSettings->RuntimeUserSlots.Find(A.Name);
			return IdxA < IdxB;
		});

		const auto ExpectedSlot = OrderedSlots[PreLoginExpectingUserSlotInPieIndex];
		FString NamespacedSlotId = UserSlots->GetNamespacedSlotId(ExpectedSlot, CurrPieIdx);

		FUserSlotAuthData SlotSerializedAuthData;
		FUserSlotAccountData SlotSerializedAccountData;
		const auto Ret = UserSlots->TryGetSavedUserDataAtNamespacedSlot(NamespacedSlotId, SlotSerializedAuthData, SlotSerializedAccountData);;

		FString NewOption = {};
		if (Ret != UBeamUserSlots::LoadSavedUserResult_Failed)
		{
			const auto AccessToken = SlotSerializedAuthData.AccessToken;
			const auto RefreshToken = SlotSerializedAuthData.RefreshToken;
			const auto ExpiresIn = SlotSerializedAuthData.ExpiresIn;
			const auto GamerTag = SlotSerializedAccountData.GamerTag;

			NewOption = Lobby->PrepareLoginOptionsFull(Options, AccessToken, RefreshToken, ExpiresIn, GamerTag, FString{});
			if (CurrSlotIdx == OrderedSlots.Num() - 1)
			{
				PreLoginExpectingUserSlotInPieIndex = 0;
				PreLoginExpectingPieIndex += 1;
			}
			else
			{
				PreLoginExpectingUserSlotInPieIndex += 1;
			}
		}
		else
		{
			ensureAlwaysMsgf(false,
			                 TEXT(
				                 "You should never see this! If you do, something went wrong with the BeamPIE initialization. Please reproduce this with `log LogBeamPIE Verbose` to see more details about what might be the problem."
			                 ));

			// We'll exit PIE with this error
			GI->GetEngine()->DeferredCommands.Add(TEXT("exit"));
		}

		return NewOption;
	}

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void BeamInitPIEGameplay(FString Options, UObject* CallingContext)
	{
		UWorld* World = CallingContext->GetWorld();
		auto GI = World->GetGameInstance();
		UBeamRuntime* BeamRuntime = GI->GetSubsystem<UBeamRuntime>();
		UBeamPIE* BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
		if (BeamRuntime->IsGameServer() && BeamPIE->FakeLobbyId.IsEmpty() && !bInitBeamPIERequested)
		{
			FakeOptions = Options;
			World->ServerTravel(WaitRoomLevel);
			UE_LOG(LogBeamEditor, Warning, TEXT("Beam Editor - Traveling!"));
		}
	}

	/**
	 * @brief Call this function if you want to initialize a subsystem that was set to manually initialize from the project settings.
	 * This function will initialize all the passed subsystems along with the user data
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle BeamPIEPrepareFakeLobbyOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandler OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		BeamPIEGamePlay(CallingContext, Op);
		return Op;
	}

	/**
	 * @copydoc BeamPIEPrepareFakeLobbyOperation
	 */
	FBeamOperationHandle CPP_BeamPIEPrepareFakeLobbyOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		BeamPIEGamePlay(CallingContext, Op);
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
		BeamInitPIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @copydoc BeamPreparePIEOperation
	 */
	FBeamOperationHandle CPP_BeamPreparePIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		BeamInitPIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @brief Call this function if you want run code AFTER the BeamPIE initialization has finished.
	 */
	FBeamOperationHandle CPP_WaitForBeamPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		WaitUntilInitPIE(CallingContext, Op);
		return Op;
	}


	void BeamInitPIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
#if !WITH_EDITOR
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
#endif

		// We only run this once per-PIE-Instance-Session (this is here since people might loop back around within a single PIE session --- in which case this should not run).
		bInitBeamPIERequested = true;

		ensureAlwaysMsgf(CallingContext, TEXT("You must provide a calling context to this function!"));

		// If we don't have a selected setting, don't do anything.
		const auto Settings = GetSelectedPIESettings();
		if (!Settings || Settings->IsDefaultSettings())
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		// Get the world
		const auto World = CallingContext->GetWorld();
		ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"));

		// Get the world context.
		const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
		ensureAlwaysMsgf(WorldContext, TEXT("You should never see this!"));

		const auto GI = World->GetGameInstance();
		ensureAlwaysMsgf(GI, TEXT("You should never see this!"));

		// Find the name of the current map and compare
		UE_LOG(LogBeamEditor, Log, TEXT("%s Initializing Beamable SDK"), *GetLogArgs(TEXT("Beam PIE Init"), WorldContext));

		// During BeamPIE, we enforce that the UniqueId is set as the Beamable UniqueId, if configured to do so.
		for (const auto& AssignedUser : Settings->AssignedUsers)
		{
			// When its running in a different process the 0 is the server
			// and also the first client index so for this case we have to subtract 1 from the index configuration
			if (AssignedUser.Key.PIEIndex == FBeamPIE_Utilities::GetPIEInstance(WorldContext))
			{
				const auto LpIdx = GetDefault<UBeamCoreSettings>()->RuntimeUserSlots.Find(AssignedUser.Key.Slot.Name);
				ULocalPlayer* Lp = GI->GetLocalPlayerByIndex(LpIdx);
				if (!Lp)
				{
					FString Err;
					Lp = GI->CreateLocalPlayer(LpIdx, Err, false);
				}

				if (GetDefault<UBeamRuntimeSettings>()->bUseBeamableGamerTagsAsUniqueNetIds)
				{
					UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Found Assigned User. Creating mapped local player. USER_SLOT=%s, PIE=%d"),
					       *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext), *AssignedUser.Key.Slot.Name, AssignedUser.Key.PIEIndex);

					const auto NamespacedSlotId = UserSlots->GetNamespacedSlotId(AssignedUser.Key.Slot, AssignedUser.Key.PIEIndex);

					FUserSlotAuthData OutAuthData;
					FUserSlotAccountData OutAccountData;
					const auto Ret = UserSlots->TryGetSavedUserDataAtNamespacedSlot(NamespacedSlotId, OutAuthData, OutAccountData);
					if (Ret != UBeamUserSlots::LoadSavedUserResult_Failed)
					{
						auto NetIdRef = FUniqueNetIdString::Create(OutAccountData.GamerTag.AsString, NAME_None);
						FUniqueNetIdRepl NetIdRepl(NetIdRef.Get());
						Lp->SetCachedUniqueNetId(NetIdRepl);
					}
				}
				else
				{
					// TODO: Allow users to define a hook operation that can initialize other things (steam, etc...) BEFORE we do this --- so that they can use that UniqueNetId instead.
					// For now, BeamPIE requires "bUseBeamableGamerTagsAsUniqueNetIds" to be "true".

					UE_BEAM_LOG(WorldContext, LogBeamEditor, Warning,
					            TEXT("If you are not using Beamable GamerTags as UniqueNetIds because you want to use something else as the UniqueId,"
						            " you need to either configure NetIds manually in the play settings OR"
						            " set up the AcceptUserIntoGameServer flow so we can keep the mapping between UniqueNetIds and GamerTags.\n"
						            "If you aren't using any other UniqueNetIds, we recommend you turn UBeamRuntimeSettings::bUseBeamableGamerTagsAsUniqueNetIds on in your Project Settings."))
				}
			}
		}

		const auto Runtime = GI->GetSubsystem<UBeamRuntime>();
		if (!Runtime->IsInitialized())
		{
			FBeamRuntimeHandlerCode Started;
			Started.BindLambda([this, WorldContext, Op]()
			{
				// Find the name of the current map and compare
				UE_BEAM_LOG(WorldContext, LogBeamEditor, Log, TEXT(" Beamable SDK Initialized"));
				BeamPreparePIE(WorldContext, Op);
			});

			Runtime->CPP_RegisterOnStarted_NoExecute(Started);
			Runtime->InitSDK({}, {});
		}
		else
		{
			// Find the name of the current map and compare
			UE_LOG(LogBeamEditor, Log, TEXT("%s Beamable SDK was Initialized. Preparing Instead"), *GetLogArgs(TEXT("Beam PIE Init"), WorldContext));
			BeamPreparePIE(WorldContext, Op);
		}
	}

	void BeamPreparePIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
#if !WITH_EDITOR
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
#endif

		ensureAlwaysMsgf(CallingContext, TEXT("You must provide a calling context to this function!"));

		// If we don't have a selected setting, don't do anything.
		const auto Settings = GetSelectedPIESettings();
		if (!Settings || Settings->IsDefaultSettings())
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		// Get the world
		const auto World = CallingContext->GetWorld();
		ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"));

		// Get the world context
		const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
		ensureAlwaysMsgf(WorldContext, TEXT("You should never see this!"));

		BeamPreparePIE(WorldContext, Op);
	}

	void BeamPreparePIE(FWorldContext* WorldContext, FBeamOperationHandle Op)
	{
#if !WITH_EDITOR
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
#endif

		// If we don't have a setting selected, we should just complete the operation (this happens in builds).
		const auto Settings = GetSelectedPIESettings();
		if (!Settings || Settings->IsDefaultSettings())
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		// If we are a client instance...
		if (!FBeamPIE_Utilities::IsRunningOnServer(WorldContext->World()))
		{
			// Start preparing the client instances.
			UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Starting Preparation."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));

			// Let's get the list of PIE+Slot combinations for which we have configured users.
			UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Building List of Assigned PIE Users"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
			TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles;

			for (const auto& AssignedUser : Settings->AssignedUsers)
			{
				// When its running in a different process the 0 is the server
				// and also the first client index so for this case we have to subtract 1 from the index configuration

				if (AssignedUser.Key.PIEIndex == FBeamPIE_Utilities::GetPIEInstance(WorldContext))
				{
					UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Found Assigned User. USER_SLOT=%s, PIE=%d"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext),
					       *AssignedUser.Key.Slot.Name, AssignedUser.Key.PIEIndex);
					PossibleSlotHandles.Add(AssignedUser.Key);
				}
			}

			// If no users are configured, we complete the operation here.
			if (PossibleSlotHandles.Num() == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("No User Configured for Slot Handles."));
				RequestTracker->TriggerOperationSuccess(Op,TEXT(""));
				return;
			}

			// Let's iterate over the users we expect and have them try to log in from cache.
			// This login will keep trying to log in from cache until it finds a user in the SLOT.
			// Our editor system NEEDS to guarantee that the user is the one we expect it to be
			// It does this by ALWAYS deleting the cached users of the configured PIE+Slot combinations before running the command to set those users up.				 
			for (const auto& CurrSlotHandle : PossibleSlotHandles)
			{
				// Get the world
				const auto World = WorldContext->World();
				ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"));

				// Get the game instance for that world
				const auto GI = World->GetGameInstance();
				ensureAlwaysMsgf(GI, TEXT("You should never see this!"));

				// Get the UBeamRuntime subsystem so that we can auto-magically log in with the cached user.
				// The cached user on the configured slots will eventually be there (because we tell the CLI to put them there).
				const auto Runtime = GI->GetSubsystem<UBeamRuntime>();
				const auto LoginLocalCacheHandler = FBeamOperationEventHandlerCode::CreateUFunction(
					this,
					GET_FUNCTION_NAME_CHECKED(UBeamPIE, PIEClientLoginHandler),
					Runtime,
					CurrSlotHandle,
					PossibleSlotHandles,
					Op);

				// Set up a "retry until succeed here"
				UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Logging in from Cache. USER_SLOT=%s, PIE=%d"),
				       *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext), *CurrSlotHandle.Slot.Name, CurrSlotHandle.PIEIndex);

				Runtime->CPP_LoginFromCacheOperation(CurrSlotHandle.Slot, LoginLocalCacheHandler);

				// This makes the lobby system initialize at the right
				// time for when the user has their own LocalPlayer implementation using
				// BeamPIE::GetGameLoginOptions.
				{
					FBeamRealmUser User;
					UserSlots->GetUserDataAtSlot(CurrSlotHandle.Slot, User, GI);
					auto LobbySubsystem = GI->GetSubsystem<UBeamLobbySubsystem>();
					LobbySubsystem->InitializeLobbyInfoForSlot(CurrSlotHandle.Slot, User);
				}
			}
		}
		// If we are in the server... 
		else
		{
			// If we are not configured to create a lobby, we complete the operation here.
			if (!Settings->FakeLobby.bShouldAutoCreateLobby)
			{
				RequestTracker->TriggerOperationSuccess(Op,TEXT(""));
				return;
			}

			// Get the world
			const auto World = WorldContext->World();
			ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"));

			// Get the game instance for that world
			const auto GI = World->GetGameInstance();
			ensureAlwaysMsgf(GI, TEXT("You should never see this!"));

			// Let's get the list of PIE+Slot combinations for which we have configured users.
			UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Building List of Assigned PIE Users"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
			TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles;
			for (const auto& AssignedUser : Settings->AssignedUsers)
			{
				UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Found Assigned User. USER_SLOT=%s, PIE=%d"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext),
				       *AssignedUser.Key.Slot.Name, AssignedUser.Key.PIEIndex);
				PossibleSlotHandles.Add(AssignedUser.Key);
			}

			// First, we'll need wait until the configured PIE users are all in the Saved/Beamable/UserSlot folder			
			UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Loading Users into BeamPIE slots."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
			// Let's try to load the user's from the Saved folder

			for (FBeamPIE_UserSlotHandle PossibleSlotHandle : PossibleSlotHandles)
			{
				const auto NamespacedSlot = UserSlots->GetNamespacedSlotId(PossibleSlotHandle.Slot.Name, PossibleSlotHandle.PIEIndex);

				UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Attempting to load data for Assigned User. USER_SLOT=%s, PIE=%d"),
				       *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext), *PossibleSlotHandle.Slot.Name, PossibleSlotHandle.PIEIndex);

				FUserSlotAuthData Auth;
				FUserSlotAccountData Account;
				const auto Res = UserSlots->TryGetSavedUserDataAtNamespacedSlot(NamespacedSlot, Auth, Account);
				const auto bDidLoad = Res != UBeamUserSlots::LoadSavedUserResult_Failed;
				if (bDidLoad)
				{
					UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Loaded data for Assigned User. USER_SLOT=%s, PIE=%d, GAMER_TAG=%s"),
					       *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext), *PossibleSlotHandle.Slot.Name, PossibleSlotHandle.PIEIndex, *Account.GamerTag.AsString);
					ServerGamerTags.Add(PossibleSlotHandle, Account.GamerTag);
				}
			}

			// If all the users are loaded (and we now know their gamertags)...
			UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Loaded data for All Assigned Users."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));

			UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Creating Fake Lobby for GameServer."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
			// Then, we call the make magical lobby endpoint until it succeeds passing in these users.					
			const auto API = GEngine->GetEngineSubsystem<UBeamLobbyApi>();
			const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

			ULobby* FakeLobby = NewObject<ULobby>();
			UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Preparing Fake Lobby"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
			const auto& FakeLobbySettings = Settings->FakeLobby;
			if (FakeLobbySettings.bIsDedicatedServer)
			{
				// Set up the game type
				FakeLobby->MatchType = FOptionalMatchType{NewObject<UMatchType>()};
				FakeLobby->MatchType.Val->Id = FOptionalBeamContentId{FakeLobbySettings.GameType};
				UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Preparing Fake Lobby - Setting GameType %s"),
				       *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext), *FakeLobbySettings.GameType.AsString);

				// Add the configured global data (with a flag that tells us that the lobby is coming from PIE).
				FakeLobby->Data = FOptionalMapOfString{TMap<FString, FString>{{UBeamLobbySubsystem::Reserved_Lobby_From_Editor_Play_Mode_Property, FString(TEXT("true"))}}};
				for (const auto& LobbyGlobalData : FakeLobbySettings.LobbyGlobalData)
				{
					FakeLobby->Data.Val.Add(LobbyGlobalData.Key, LobbyGlobalData.Value);
					UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Preparing Fake Lobby - Setting Global Data - Key=%s, Val=%s"),
					       *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext), *LobbyGlobalData.Key, *LobbyGlobalData.Value);
				}

				// Dedicated servers are always Null restriction
				FakeLobby->Restriction = FOptionalLobbyRestriction{EBeamLobbyRestriction::BEAM_Null};
				FakeLobby->Host = {};

				// Set up the players in the fake lobby.
				FakeLobby->Players = FOptionalArrayOfLobbyPlayer{{}};
				for (const auto& KVP : ServerGamerTags)
				{
					const auto& Handle = KVP.Key;
					const auto& GamerTag = KVP.Value;
					const auto bHasPlayerSettings = Settings->AssignedUsers.Contains(Handle);
					auto Tags = TArray<FBeamTag>();
					if (bHasPlayerSettings)
					{
						for (const auto& LobbyData : Settings->AssignedUsers[Handle].LobbyData)
							Tags.Add(FBeamTag{LobbyData.Key, LobbyData.Value});
					}

					// Set the properties we forward
					const auto LobbyPlayer = NewObject<ULobbyPlayer>();
					LobbyPlayer->PlayerId = FOptionalBeamGamerTag{GamerTag};
					LobbyPlayer->Joined = FOptionalDateTime{FDateTime::UtcNow()};
					LobbyPlayer->Tags = bHasPlayerSettings ? FOptionalArrayOfBeamTag{Tags} : FOptionalArrayOfBeamTag{};
					if (GetDefault<UBeamRuntimeSettings>()->bUseBeamableGamerTagsAsUniqueNetIds)
					{
						if (LobbyPlayer->Tags.IsSet) LobbyPlayer->Tags.Val.Add(FBeamTag{UBeamLobbySubsystem::Reserved_PlayerTag_UniqueNetId_Property, GamerTag.AsString});
						else LobbyPlayer->Tags = FOptionalArrayOfBeamTag{TArray{FBeamTag{UBeamLobbySubsystem::Reserved_PlayerTag_UniqueNetId_Property, GamerTag.AsString}}};
					}
					else
					{
						UE_BEAM_LOG(WorldContext, LogBeamEditor, Warning,
						            TEXT("If you are not using Beamable GamerTags as UniqueNetIds because you want to use something else as the UniqueId,"
							            " you need to either configure NetIds manually in the play settings OR"
							            " set up the AcceptUserIntoGameServer flow so we can keep the mapping between UniqueNetIds and GamerTags.\n"
							            "If you aren't using any other UniqueNetIds, we recommend you turn UBeamRuntimeSettings::bUseBeamableGamerTagsAsUniqueNetIds on in your Project Settings."))
					}

					FakeLobby->Players.Val.Add(LobbyPlayer);
					for (FBeamTag Tag : Tags)
					{
						UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Preparing Fake Lobby - Setting Player Data - GAMER_TAG=%s, Key=%s, Val=%s"),
						       *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext), *GamerTag.AsString, *Tag.Name.Val, *Tag.Value.Val);
					}
				}
			}
			else
			{
				RequestTracker->TriggerOperationError(Op, TEXT("UNSUPPORTED_LISTEN_SERVER"));
			}

			UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Trying to Create the Fake Lobby"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
			auto Req = NewObject<UPutLobbiesRequest>();
			Req->Body = FakeLobby;

			const auto CreateLobbyHandler = FOnPutLobbiesFullResponse::CreateUObject(this, &UBeamPIE::PIEServerCreateLobbyHandler, WorldContext, Req, PossibleSlotHandles, Op);
			FBeamRequestContext Ctx;
			API->CPP_PutLobbies(ServerSlot, Req, CreateLobbyHandler, Ctx, Op, WorldContext->World());
		}
	}

	void BeamPIEGamePlay(UObject* CallingContext, FBeamOperationHandle Op)
	{
		auto BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
		UWorld* World = CallingContext->GetWorld();
		auto GI = World->GetGameInstance();
		UBeamRuntime* BeamRuntime = GI->GetSubsystem<UBeamRuntime>();

		auto InitHandler = FBeamOperationEventHandlerCode::CreateLambda([CallingContext, this, BeamRuntime](const FBeamOperationEvent& Event)
		{
			if (BeamRuntime->IsGameServer())
			{
				const auto Config = GetMutableDefault<UBeamPIEConfig>();
				FString LevelToReload = Config->CurrPIEMap;
				if (!FakeOptions.IsEmpty())
				{
					LevelToReload += "?" + FakeOptions;
				}
				CallingContext->GetWorld()->ServerTravel(LevelToReload);
			}
		});

		BeamPIE->CPP_BeamPreparePIEOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), CallingContext, InitHandler);
	}

	void PIEServerCreateLobbyHandler(FPutLobbiesFullResponse Resp, FWorldContext* WorldContext, UPutLobbiesRequest* Req, TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles, FBeamOperationHandle PrepareOp)
	{
		if (!IsValidContext(WorldContext)) return;

		if (Resp.State == RS_Success)
		{
			UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Created Lobby."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));

			FakeLobbyId = Resp.SuccessData->LobbyId.Val;

			const auto LobbySubsystem = WorldContext->World()->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
			const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
			LobbySubsystem->RegisterLobbyWithServer(ServerSlot, FGuid{FakeLobbyId}, PrepareOp);
		}
		else
		{
			// If we fail, create a new handler and call the PutLobbies endpoint again
			// This is guaranteed to succeed eventually because all clients are logging into the game.
			FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this,WorldContext, PossibleSlotHandles, PrepareOp, Req](const float)
			{
				if (!IsValidContext(WorldContext)) return false;

				UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Failed to create lobby. Trying again."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));

				const auto CreateLobbyHandler = FOnPutLobbiesFullResponse::CreateUObject(this, &UBeamPIE::PIEServerCreateLobbyHandler, WorldContext, Req, PossibleSlotHandles, PrepareOp);
				FBeamRequestContext Ctx;

				const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
				const auto API = GEngine->GetEngineSubsystem<UBeamLobbyApi>();
				API->CPP_PutLobbies(ServerSlot, Req, CreateLobbyHandler, Ctx, PrepareOp, WorldContext->World());
				return false;
			}), 0.2f);
		}
	}

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

				UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Logged in from Cache. USER_SLOT=%s, PIE=%d"), *GetLogArgs(TEXT("Beam PIE Prepare"), GEngine->GetWorldContextFromWorld(Runtime->GetWorld())),
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
			// This is guaranteed to succeed eventually for all configured users because the UBeamUserDeveloperManagerEditor will eventually write to it.
			if (Evt.CompletedWithError())
			{
				UE_LOG(LogTemp, Warning, TEXT(" FAIL LOGIN HANDLER CALLED BY BEAM PIE"));
				RequestTracker->TriggerOperationError(PrepareOp, TEXT("FAILED_TO_LOGIN_WITH_SAVED_USER"));
			}
		}
	}

	void WaitUntilClientIsLoggedIn(UBeamRuntime* Runtime, TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles, FBeamOperationHandle Op)
	{
		const auto WorldContext = GEngine->GetWorldContextFromWorld(Runtime->GetWorld());
		const auto PieInstance = FBeamPIE_Utilities::GetPIEInstance(WorldContext);

		// Let's make sure all the users configured for this PIE instance are done logging in.
		auto bAreAllUsersAlreadyLoggedIn = true;
		for (const auto& CurrHandle : PossibleSlotHandles)
		{
			// We only care about the users in this PIE instance.
			if (CurrHandle.PIEIndex != PieInstance) continue;

			// If we are NOT already logged in...
			FBeamRealmUser UserData;
			if (!UserSlots->GetUserDataAtSlot(CurrHandle.Slot, UserData, Runtime))
			{
				// Set this as false
				bAreAllUsersAlreadyLoggedIn = false;

				// Set up a callback that will try to verify that we are all logged in whenever a user does log in.
				const auto UserLoggedInHandler = UserSlots->GlobalUserSlotAuthenticatedCodeHandler.AddLambda(
					[this, CurrHandle, Runtime, PieInstance, PossibleSlotHandles, Op]
				(const FUserSlot&, const FBeamRealmUser&, const FBeamOperationHandle&, const UObject*)
					{
						// Check to see if ALL slots managed by this PIE instance are already logged in.
						auto bAreAllSlotsInLoggedIn = true;
						for (const auto& SlotHandle : PossibleSlotHandles)
						{
							// We only care about the users in this PIE instance.
							if (SlotHandle.PIEIndex != PieInstance) continue;

							FBeamRealmUser _;
							bAreAllSlotsInLoggedIn &= UserSlots->GetUserDataAtSlot(SlotHandle.Slot, _, Runtime);
						}

						// If all slots in this instance are logged in, we are done and can complete the operation and remove this callback.
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
		const auto WorldContext = GEngine->GetWorldContextFromWorld(Runtime->GetWorld());
		const auto PieInstance = FBeamPIE_Utilities::GetPIEInstance(WorldContext);

		// For each of them, check if we already are 
		const auto LobbySystem = Runtime->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		auto bAreAllUsersAlreadyInTheLobby = true;
		for (const auto& Handle : PossibleSlotHandles)
		{
			// We only care about the users in this PIE instance.
			if (Handle.PIEIndex != PieInstance) continue;

			auto LobbyState = LobbySystem->GetCurrentSlotLobbyState(Handle.Slot);

			// If the user is NOT already in the lobby, let's set up a notification that will trigger when they see that they've joined it.
			ULobby* UserLobby = nullptr;
			if (!LobbySystem->TryGetCurrentLobby(Handle.Slot, UserLobby) || !UserLobby->Data.Val.Contains(UBeamLobbySubsystem::Reserved_Lobby_From_Editor_Play_Mode_Property))
			{
				UE_LOG(LogBeamEditor, Log, TEXT("%s Client - User is not in Lobby yet. Setting up the notification listener. USER_SLOT=%s, PIE=%d"), *GetLogArgs(TEXT("Beam PIE Prepare"),
					       GEngine->GetWorldContextFromWorld(Runtime->GetWorld())), *Handle.Slot.Name, Handle.PIEIndex);

				bAreAllUsersAlreadyInTheLobby = false;
				// Add a notification for when the player joins the lobby
				const auto LobbyJoinedHandle = LobbyState->OnLobbyJoinedCode.AddLambda(
					[this, PieInstance, Runtime, Handle, LobbySystem, LobbyState, PossibleSlotHandles, Op](const FUserSlot&, ULobby*, FLobbyUpdateNotificationMessage)
					{
						// Check to see if ALL slots managed by this PIE instance are already in the lobby.
						auto bAreAllSlotsInTheLobby = true;
						for (const auto& SlotHandle : PossibleSlotHandles)
						{
							// We only care about the users in this PIE instance.
							if (SlotHandle.PIEIndex != PieInstance) continue;

							ULobby* L = nullptr;
							const auto JoinedLobby = LobbySystem->TryGetCurrentLobby(SlotHandle.Slot, L) && L->Data.Val.Contains(UBeamLobbySubsystem::Reserved_Lobby_From_Editor_Play_Mode_Property);
							bAreAllSlotsInTheLobby &= JoinedLobby;
							if (JoinedLobby)
							{
								UE_LOG(LogBeamEditor, Log, TEXT("%s Client - User is joined Lobby. USER_SLOT=%s, PIE=%d, LOBBY=%s"), *GetLogArgs(TEXT("Beam PIE Prepare"),
									       GEngine->GetWorldContextFromWorld(Runtime->GetWorld())), *SlotHandle.Slot.Name, SlotHandle.PIEIndex, *L->LobbyId.Val);
							}
						}

						// If all slots in this instance are in the lobby, we are done and can complete the operation.
						if (bAreAllSlotsInTheLobby)
						{
							LobbyState->OnLobbyJoinedCode.Remove(LobbyJoinedHandles[Handle]);
							LobbyJoinedHandles.Remove(Handle);
							RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
						}
					});
				LobbyJoinedHandles.Add(Handle, LobbyJoinedHandle);
			}
			else
			{
				UE_LOG(LogBeamEditor, Log, TEXT("%s Client - User is already in Lobby. USER_SLOT=%s, PIE=%d, LOBBY=%s"), *GetLogArgs(TEXT("Beam PIE Prepare"),
					       GEngine->GetWorldContextFromWorld(Runtime->GetWorld())), *Handle.Slot.Name, Handle.PIEIndex, *UserLobby->LobbyId.Val);
			}
		}

		if (bAreAllUsersAlreadyInTheLobby)
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		}
	}


	void WaitUntilInitPIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
		// When running outside the editor, this is a no-op.
#if !WITH_EDITOR
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
#endif

		// When running in the editor/separate-process-PIE-instances... 
		if (CallingContext)
		{
			if (const auto World = CallingContext->GetWorld())
			{
				// If we don't have a selected setting, don't do anything.
				const auto Settings = GetSelectedPIESettings();
				if (!Settings || Settings->IsDefaultSettings())
				{
					RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
					return;
				}

				// Get the world context so that we can fill out the users we care about.
				if (const auto WorldContext = GEngine->GetWorldContextFromWorld(World))
				{
					// Let's wait until the local cache has files in it in accordance to what is configured in the Settings.
					TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles;
					for (const auto& AssignedUser : Settings->AssignedUsers)
					{
						if (AssignedUser.Key.PIEIndex == FBeamPIE_Utilities::GetPIEInstance(WorldContext) || FBeamPIE_Utilities::IsRunningOnServer(World))
						{
							PossibleSlotHandles.Add(AssignedUser.Key);
						}
					}

					// If we are running a server...
					if (FBeamPIE_Utilities::IsRunningOnServer(World))
					{
						// ... but we shouldn't create a lobby --- just complete the operation cause the server is ready.
						if (!Settings->FakeLobby.bShouldAutoCreateLobby)
						{
							RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
							return;
						}

						// The server is creating the lobby and, once its done it'll register the created lobby with itself.						
						// So... we wait for it and then trigger successfully.
						Async(EAsyncExecution::Thread, [this, Op, World, WorldContext, CallingContext]()
						{
							ULobby* FoundLobby;
							auto FoundLobbyInServer = World->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>()->TryGetLobbyById(FGuid{FakeLobbyId}, FoundLobby);
							while (IsValidContext(WorldContext) && !FoundLobbyInServer)
							{
								FPlatformProcess::Sleep(0.1f);
								if (IsValidContext(WorldContext))
								{
									if (const auto LobbySubsystem = World->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>())
										FoundLobbyInServer = LobbySubsystem->TryGetLobbyById(FGuid{FakeLobbyId}, FoundLobby);
								}
							}

							AsyncTask(ENamedThreads::GameThread, [this, Op, CallingContext]()
							{
								if (IsValidChecked(CallingContext))
								{
									RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
								}
							});
						});
					}
					// In the clients, Init PIE will wait until the user is in the lobby.
					else
					{
						const auto Runtime = World->GetGameInstance()->GetSubsystem<UBeamRuntime>();
						if (Settings->FakeLobby.bShouldAutoCreateLobby)
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

	/**
	 * Gets the currently selected setting (asserting its existence). 
	 */
	FBeamPIE_Settings const* GetSelectedPIESettings() const
	{
		// In the editor, this should never be null.
#if WITH_EDITOR
		ensureAlwaysMsgf(SelectedSettings, TEXT("This should never be null while in the editor."));
#endif
		return SelectedSettings;
	}

	/**
	 * Based on the given MapName, we choose the selected setting. If no setting is selected for this map, this function returns the @link DefaultSettings @endlink. 
	 */
	static FBeamPIE_Settings const* ChooseSelectedPIESettings(FString MapName)
	{
#if !WITH_EDITOR
		return nullptr;
#endif

		const auto Config = GetDefault<UBeamPIEConfig>();

		UE_LOG(LogTemp, Warning, TEXT("MAP NAME CHOOSE: %s"), *MapName);

		for (auto MapSelection : Config->PerMapSelection)
		{
			UE_LOG(LogTemp, Warning, TEXT("MAP KEY: %s"), *MapSelection.Key);
		}
		if (Config->PerMapSelection.Contains(MapName))
		{
			const auto Id = GetDefault<UBeamPIEConfig>()->PerMapSelection[MapName];
			return Config->AllSettings.FindByPredicate([Id](FBeamPIE_Settings& S) { return S.SettingsId == Id; });
		}

		// Guaranteed to exist from editor code.
		return DefaultSettings();
	}

	/**
	 * Checks if the FContext is valid
	 */
	bool IsValidContext(FWorldContext* Context)
	{
		return Context != nullptr && Context->WorldType != EWorldType::None;
	}

	/**
	 * Helper function for us to log things in this system with information about map and PIE instance.	  
	 */
	FString GetLogArgs(FString Header, FWorldContext* WorldContext)
	{
		if (IsValidContext(WorldContext) && WorldContext->World())
		{
			const auto CurrMapName = UWorld::RemovePIEPrefix(WorldContext->World()->GetMapName());
			return FString::Printf(TEXT("%s [Index: %d, Starting Map: %s, IsServer: %d, NetMode: %d] -"), *Header, FBeamPIE_Utilities::GetPIEInstance(WorldContext), *CurrMapName,
			                       FBeamPIE_Utilities::IsRunningOnServer(WorldContext->World()), WorldContext->World()->GetNetMode());
		}
		return TEXT("");
	}
};


namespace BeamPIE
{
	namespace GameInstance
	{
		BEAMABLECORERUNTIME_API inline void PreStartGameInstance(UGameInstance* This)
		{
#if !WITH_EDITOR
			return;
#endif
			UE_LOG(LogBeamRuntime, Warning, TEXT("PRE-INIT PLAY IN EDITOR --- Is Server: %d"), This->IsDedicatedServerInstance());
			auto BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			BeamPIE->bInitBeamPIERequested = true;
		}

		BEAMABLECORERUNTIME_API inline void StartGameInstance(UGameInstance* This)
		{
#if !WITH_EDITOR
			return;
#endif
			UE_LOG(LogBeamRuntime, Warning, TEXT("INIT PLAY IN EDITOR --- Is Server: %d"), This->IsDedicatedServerInstance());
			auto BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			BeamPIE->CPP_BeamPreparePIEOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), This->GetWorld(), {});
		}

		BEAMABLECORERUNTIME_API inline void StartPlayInEditorGameInstance(UGameInstance* This, ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
		{
#if !WITH_EDITOR
			return;
#endif
			UE_LOG(LogBeamRuntime, Warning, TEXT("INIT PLAY IN EDITOR (PIE) --- Is Server: %d"), This->IsDedicatedServerInstance());
			auto BeamPie = GEngine->GetEngineSubsystem<UBeamPIE>();
			BeamPie->CPP_BeamPreparePIEOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), This->GetWorld(), {});
		}

		BEAMABLECORERUNTIME_API inline bool DelayPendingNetGameTravel(UGameInstance* This)
		{
#if !WITH_EDITOR
			return false;
#endif

			auto CoreSettings = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
			auto BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();

			const auto PieInstanceIdx = FBeamPIE_Utilities::GetPIEInstance(This->GetWorldContext());
			if (!BeamPIE->ClientDelayMapHandles.Contains(PieInstanceIdx))
			{
				const auto Handle = BeamPIE->CPP_WaitForBeamPIEOperation(CoreSettings, This, {});
				BeamPIE->ClientDelayMapHandles.Add(PieInstanceIdx, Handle);
				return true;
			}

			const auto Handle = BeamPIE->ClientDelayMapHandles[PieInstanceIdx];
			auto ReqTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
			return ReqTracker->IsOperationActive(Handle);
		}
	}

	namespace Orchestrator
	{
		/**
	* There are two scenarios that matter for this (where this returns true):
	*  - In a Deployed Build with a single Lobby being managed per GameServer
	*    - The Lobby ID should be passed via command line or environment variable (you can use BeamMultiplayer::GetLobbyIdFromCLArgs for this). You should read it when this returns true.
	*
	*  - In a Deployed Build with a multiple Lobbies being managed per GameServer
	*    - Every time your Game Server Orchestrator assigns a Lobby to a server, their SDK should provide you a callback (or polling loop). You should set it up, when this returns true.
	*
	* This NEVER returns true if you are running your game server locally using PIE's game server.
	* 
	* When this returns true, you must:
	*  - Get the Lobby ID using your Orchestrator's SDK or our BeamMultiplayer::GetLobbyIdFromCLArgs utility (when passing it via CLArgs). 
	*  - Call BeamMultiplayer::RegisterLobbyWithServer and handle the operation's success/failure according to your game's needs. 
	*  
			// Setup Hathora, Agones, GameLyft, whatever you need to extract from your game server orchestrator's SDK, the Beamable Lobby Id your federation gave it.
			// Once you have the lobby
			
	 * @param CallingContext 
	 * @return 
	 */
		BEAMABLECORERUNTIME_API inline bool ShouldRegisterOrchestrator(const UObject* CallingContext)
		{
#if !WITH_EDITOR
			return true;
#endif
			const auto PIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			return PIE->RequiresGameServerOrchestratorSetup(CallingContext);
		}
	}

	namespace Authentication
	{
		BEAMABLECORERUNTIME_API inline FString GetExpectedClientPIEOptions(const AGameModeBase* GameMode, const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId)
		{
#if !WITH_EDITOR
			return Options;
#endif
			const auto PIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			return PIE->GetExpectedClientPIEOptions(Options, GameMode->GetWorld());
		}
	}
}
