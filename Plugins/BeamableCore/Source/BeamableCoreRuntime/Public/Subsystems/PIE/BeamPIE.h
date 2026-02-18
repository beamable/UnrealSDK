// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemTypes.h"
#include "AutoGen/SubSystems/BeamLobbyApi.h"
#include "AutoGen/SubSystems/BeamPlayerLobbyApi.h"
#include "AutoGen/SubSystems/BeamPresenceApi.h"
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
#include "Subsystems/Party/BeamPartySubsystem.h"

#if WITH_EDITOR
#include "Subsystems/Microservices/BeamMicroservicesEditor.h"
#include "Subsystems/UserDeveloperManager/BeamUserDeveloperManagerEditor.h"
#endif


#include "BeamPIE.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamPartyPlayerRuntimeSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPartyLeader = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GamerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> PartyTags = {};
};

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORERUNTIME_API UBeamPIEProgressionStep : public UObject, public IBeamOperationEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString StepName;

	static UBeamPIEProgressionStep* CreateProgressionStep(FString StepName)
	{
		auto ProgressionStep = NewObject<UBeamPIEProgressionStep>();
		ProgressionStep->StepName = StepName;
		return ProgressionStep;
	}

	static UBeamPIEProgressionStep* CreateLoginStep()
	{
		auto ProgressionStep = NewObject<UBeamPIEProgressionStep>();
		ProgressionStep->StepName = "Login with Client!";
		return ProgressionStep;
	}

	static UBeamPIEProgressionStep* CreateEnteringInLobbyStep()
	{
		auto ProgressionStep = NewObject<UBeamPIEProgressionStep>();
		ProgressionStep->StepName = "Joining Lobby!";
		return ProgressionStep;
	}

	static UBeamPIEProgressionStep* CreateWaitingForServerStep()
	{
		auto ProgressionStep = NewObject<UBeamPIEProgressionStep>();
		ProgressionStep->StepName = "Waiting for the Server!";
		return ProgressionStep;
	}
};

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamPIE : public UEngineSubsystem
{
	GENERATED_BODY()

	friend class UBeamRuntime;

	const static inline FString WaitRoomLevel = TEXT("L_Beamable_PIEWaitRoom");

	static inline FBeamPIE_Settings DefaultSettingsPtr = {};

	TMap<FBeamPIE_UserSlotHandle, FDelegateHandle> LobbyJoinedHandles;
	TMap<FBeamPIE_UserSlotHandle, FDelegateHandle> UserSlotAuthenticatedHandles;
	TMap<FBeamPIE_UserSlotHandle, FBeamGamerTag> ServerGamerTags;

	TMap<int32, FBeamOperationHandle> ClientDelayMapHandles;
	TMap<int32, FDelegateHandle> PieClientInitSDKHandles;

	/**
	 * Basically, this allows us to know that a custom game instance implementation is being used to bootstrap Beamable.
	 * We need to know this so we can correctly guarantee that Easy/Advanced implementations of BeamPIE don't conflict.
	 * Ie.: Try to initialize more than once.
	 */
	bool bCustomGameInstanceGuard = false;

	/**
	 * This is irrelevant on the server -- only matters in the client.
	 * Keep the reference for the fake options 
	 */
	FString FakeOptions = "";

	/**
	 * This is irrelevant on the client --- only matters in the server. 
	 */
	FString FakeLobbyId = "";

	/**
	 * This is irrelevant on the client --- only matters in the server. 
	 */
	int32 PreLoginExpectingPieIndex;

	/**
	 * This is irrelevant on the client --- only matters in the server. 
	 */
	int32 PreLoginExpectingUserSlotInPieIndex;


#if WITH_EDITOR
	/**
	 * Stored handle to the delegate we register to run with FEditorDelegates::StartPIE.
	 */
	FDelegateHandle StartPIEHandler;
#endif

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
	 * @brief Get the operation event id for a sub-event that is triggered whenever a user signs in during the @link PreparePIE_ApplySelectedSettings @endlink flow.
	 */
	UFUNCTION(BlueprintCallable)
	static inline FName GetOperationEventID_PIE_ClientLoggedIn() { return FName("ON_CLIENT_LOGGED_IN"); }

	/**
	 * @brief Get the operation event id for a sub-event that is triggered whenever the user advance a step in the PIE proccess.
	 */
	UFUNCTION(BlueprintCallable)
	static inline FName GetOperationEventID_PIE_ProgressionStep() { return FName("PROGRESSION_PIE_STEP"); }

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

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);

		// Get other engine systems
		Backend = Collection.InitializeDependency<UBeamBackend>();
		UserSlots = Collection.InitializeDependency<UBeamUserSlots>();
		RequestTracker = Collection.InitializeDependency<UBeamRequestTracker>();

		// Set the default settings (this is important for standalone/separate process PIE modes) 
		SelectedSettings = DefaultSettings();
		PreLoginExpectingPieIndex = 1; // Starts at one because all PIE clients are instances 1~X.
		PreLoginExpectingUserSlotInPieIndex = 0; // Starts at one because this indexes into UBeamCoreSettings::RuntimeUserSlots for each PreLoginExpectingPieIndex.
		bCustomGameInstanceGuard = false;
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
			CoreSettings->TargetRealm = Config->CurrTargetRealm;

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
				bCustomGameInstanceGuard = false;
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
				// We do this like this because it's the easiest way to get information from PIE parameters into Standalone/Separate Process PIE instances. 
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

				// We end by asking the UBeamUserDeveloperManagerEditor to configure any mapped cached users in the `Saved/Beamable/UserSlots` directory.
				// This makes it so that, when we `LoginCached` as part of our `BeamInitPIE`, the mapped users will be the ones we are loading.
				// This may also clone the mapped users and use the clone depending on the settings. 
				{
					auto DeveloperUserSubsystem = GEditor->GetEditorSubsystem<UBeamUserDeveloperManagerEditor>();
					DeveloperUserSubsystem->TriggerOnPreBeginPIE(PlaySettings, SelectedSettings);
				}
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
	 * This enables BeamPIE for any gameplay level where you put this as the Level Blueprint's BeginPlay function.  
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Easy Enable - Gameplay", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="InitWhenServerBuild,OnStarted,OnStartedFailedHandler,CallingContext"))
	void EasyEnableBeamPIE_Gameplay(FString Options, bool InitWhenServerBuild,
	                                UPARAM(DisplayName="Server Build - On Started")
	                                FBeamRuntimeHandler OnStarted,
	                                UPARAM(DisplayName="Server Build - On Started Failed")
	                                FRuntimeError OnStartedFailedHandler,
	                                UObject* CallingContext)
	{
#if WITH_EDITOR
		// If we don't have a selected setting while in the editor, don't do anything.
		// Outside the editor and in game servers, this node acts like a BeamInit node.
		const auto Settings = GetSelectedPIESettings();
		if (!Settings || Settings->IsDefaultSettings()) return;
#endif

		// Get the world
		const auto World = CallingContext->GetWorld();
		if (!ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!"))) return;

		// Get the world context.
		const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
		if (!ensureAlwaysMsgf(WorldContext, TEXT("You should never see this!"))) return;

		const auto GI = World->GetGameInstance();
		if (!ensureAlwaysMsgf(GI, TEXT("You should never see this!"))) return;

		// Get the runtime and, when this is a server build, this node is equivalent to a UBeamRuntime::InitSDK.
		UBeamRuntime* BeamRuntime = GI->GetSubsystem<UBeamRuntime>();
#if !WITH_EDITOR
		if (BeamRuntime->IsGameServer() && InitWhenServerBuild)
		{
			UE_LOG(LogTemp, Warning, TEXT("Initializing Beamable from Easy BeamPIE!"));
			BeamRuntime->InitSDK(OnStarted, OnStartedFailedHandler);
		}
		return;
#else
		UBeamPIE* BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
		if (BeamRuntime->IsGameServer() && BeamPIE->FakeLobbyId.IsEmpty() && !bCustomGameInstanceGuard)
		{
			FakeOptions = Options;
			World->ServerTravel(WaitRoomLevel);
		}
#endif
	}

	/**
 * @brief Call this function if you want to initialize a subsystem that was set to manually initialize from the project settings.
 * This function will initialize all the passed subsystems along with the user data
 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle PrepareThenTravelToPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandler OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), FBeamOperationEventHandlerCode::CreateLambda([=, this](const FBeamOperationEvent& Event)
		{
			TravelBackToStarterLevel(CallingContext);
			OnOperationEvent.ExecuteIfBound(Event);
		}));
		PrepareThenTravelToPIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @copydoc PrepareThenTravelToPIEOperation
	 */
	FBeamOperationHandle CPP_PrepareThenTravelToPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), FBeamOperationEventHandlerCode::CreateLambda([=, this](const FBeamOperationEvent& Event)
		{
			TravelBackToStarterLevel(CallingContext);
			OnOperationEvent.ExecuteIfBound(Event);
		}));
		PrepareThenTravelToPIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @brief Call this function if you want to initialize a subsystem that was set to manually initialize from the project settings.
	 * This function will initialize all the passed subsystems along with the user data
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle PreparePIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandler OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		PreparePIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @copydoc PreparePIEOperation
	 */
	FBeamOperationHandle CPP_PreparePIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		PreparePIE(CallingContext, Op);
		return Op;
	}

	/**
	 * @brief Call this function if you want run code AFTER the BeamPIE initialization has finished.
	 *
	 * Once this succeeds, you have the guarantee that:
	 *   - In the server, the server has already registered itself with the fake lobby.
	 *   - In the client, that the clients are already in the fake lobby. If no fake lobby is being set up, than the guarantee is that they are logged in.
	 */
	FBeamOperationHandle CPP_WaitForBeamPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		WaitUntilInitPIE(CallingContext, Op);
		return Op;
	}

	/**
	 * Operation logic that is called by our waiting room (used by the Easy Beam PIE flow) --- it will run the PreparePIE operation and, when its done,
	 * server travel with all the connected players, into the map on which you originally entered PIE.
	 */
	void PrepareThenTravelToPIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
#if !WITH_EDITOR
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
#else
		// If we don't have a selected setting, don't do anything.
		const auto Settings = GetSelectedPIESettings();
		if (!Settings || Settings->IsDefaultSettings())
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		// Get the world
		const auto World = CallingContext->GetWorld();
		if (!ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!")))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_WORLD_FOR_BEAM_PIE"));
			return;
		}

		// Get the world context.
		const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
		if (!ensureAlwaysMsgf(WorldContext, TEXT("You should never see this!")))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_WORLD_CONTEXT_FOR_BEAM_PIE"));
			return;
		}

		const auto GI = World->GetGameInstance();
		if (!ensureAlwaysMsgf(GI, TEXT("You should never see this!")))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_GAME_INSTANCE_OR_BEAM_PIE"));
			return;
		}

		PreparePIE(CallingContext, Op);
#endif
	}

	/**
	 *  Prepare PIE for a operation
	 */
	void PreparePIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
		if (!bCustomGameInstanceGuard) PreparePIE_EnsureInit(CallingContext, Op);
		else WaitUntilInitPIE(CallingContext, Op);
	}

	/**
	 *  Travel Back
	 */
	void TravelBackToStarterLevel(UObject* CallingContext)
	{
		const auto GI = CallingContext->GetWorld()->GetGameInstance();

		UBeamRuntime* BeamRuntime = GI->GetSubsystem<UBeamRuntime>();

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
	}

	/**
	 * This function guarantees that the Beamable SDK is initialized before attempting to apply the settings.
	 * It also does some configuring of each client's LocalPlayers based on the settings. 
	 */
	void PreparePIE_EnsureInit(UObject* CallingContext, FBeamOperationHandle Op)
	{
#if !WITH_EDITOR
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
#else
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
		if (!ensureAlwaysMsgf(World, TEXT("You must provide a calling context with a valid World to this function!")))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_WORLD_FOR_BEAM_PIE"));
			return;
		}

		// Get the world context.
		const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
		if (!ensureAlwaysMsgf(WorldContext, TEXT("You should never see this!")))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_WORLD_CONTEXT_FOR_BEAM_PIE"));
			return;
		}

		const auto GI = World->GetGameInstance();
		if (!ensureAlwaysMsgf(GI, TEXT("You should never see this!")))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_GAME_INSTANCE_OR_BEAM_PIE"));
			return;
		}

		// Find the name of the current map and compare
		UE_LOG(LogBeamEditor, Log, TEXT("%s Checking if need Initialization of Beamable SDK"), *GetLogArgs(TEXT("Beam PIE Init"), WorldContext));

		// During BeamPIE, we enforce that the UniqueId is set as the Beamable UniqueId, if configured to do so.
		const auto Runtime = GI->GetSubsystem<UBeamRuntime>();
		if (Runtime->IsClient())
		{
			for (const auto& AssignedUser : Settings->AssignedUsers)
			{
				// Only iterate over users that are for this PIE Instance.
				if (AssignedUser.Key.PIEIndex == FBeamPIE_Utilities::GetPIEInstance(WorldContext))
				{
					const auto LpIdx = GetDefault<UBeamCoreSettings>()->RuntimeUserSlots.Find(AssignedUser.Key.Slot.Name);
					ULocalPlayer* Lp = GI->GetLocalPlayerByIndex(LpIdx);
					if (!Lp)
					{
						FString Err;
						Lp = GI->CreateLocalPlayer(LpIdx, Err, false);
					}

					if (GetDefault<UBeamRuntimeSettings>()->bEnableGameplayFrameworkIntegration)
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

						UE_BEAM_LOG_PIE(WorldContext, LogBeamEditor, Warning,
						                TEXT("If you are not using Beamable GamerTags as UniqueNetIds because you want to use something else as the UniqueId,"
							                " you need to either configure NetIds manually in the play settings OR"
							                " set up the AcceptUserIntoGameServer flow so we can keep the mapping between UniqueNetIds and GamerTags.\n"
							                "If you aren't using any other UniqueNetIds, we recommend you turn UBeamRuntimeSettings::bUseBeamableGamerTagsAsUniqueNetIds on in your Project Settings."))
					}
				}
			}
		}

		if (!Runtime->IsInitialized())
		{
			FBeamRuntimeHandlerCode Started;
			Started.BindLambda([this, WorldContext, Op, Runtime]()
			{
				if (!IsValidContext(WorldContext)) return;

				// Find the name of the current map and compare
				UE_BEAM_LOG_PIE(WorldContext, LogBeamEditor, Log, TEXT("Beamable SDK Initialized"));
				PreparePIE_ApplySelectedSettings(WorldContext, Op);

				// Clean up the OnStarted handle that triggers PIE things...
				const auto& DelHandle = PieClientInitSDKHandles.FindAndRemoveChecked(FBeamPIE_Utilities::GetPIEInstance(WorldContext));
				Runtime->CPP_UnregisterOnStarted(DelHandle);
			});

			// Store the initialization handle so we can remove it after we are done.
			const auto& DelHandle = Runtime->CPP_RegisterOnStarted(Started);
			PieClientInitSDKHandles.Add(FBeamPIE_Utilities::GetPIEInstance(WorldContext), DelHandle);


			// If we are not already initializing it, trigger the initialization
			if (!Runtime->IsInitializing())
			{
				Runtime->InitSDK({}, {});
				UE_LOG(LogBeamEditor, Log, TEXT("%s Initializing Beamable SDK"), *GetLogArgs(TEXT("Beam PIE Init"), WorldContext));
			}
		}
		else
		{
			// Find the name of the current map and compare
			UE_LOG(LogBeamEditor, Log, TEXT("%s Beamable SDK was Initialized. Preparing Instead"), *GetLogArgs(TEXT("Beam PIE Init"), WorldContext));
			PreparePIE_ApplySelectedSettings(WorldContext, Op);
		}
#endif
	}

	void AutoCreateParty(FWorldContext* WorldContext, FBeamPIE_Settings const* const Settings, FBeamOperationHandle Operation)
	{
		const auto API = GEngine->GetEngineSubsystem<UBeamPartyApi>();
		const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		TMap<FBeamPIE_UserSlotHandle, FBeamPIE_PerUserSetting> PartyUsersMap;
		GetAllPartyUsersMap(*Settings, PartyUsersMap);

		// Create TMap with PartyId as key and party runtime settings as value
		TMap<FString, TArray<FBeamPartyPlayerRuntimeSettings>> PartyPlayersRuntimeMap;

		for (const auto& PlayerSetting : PartyUsersMap)
		{
			const FBeamPIE_UserSlotHandle& UserSlotHandle = PlayerSetting.Key;
			const FBeamPIE_PlayerPartySettings& PartyPlayerSettings = PlayerSetting.Value.PartySettings;

			// Get the GamerTag from ServerGamerTags
			FBeamGamerTag GamerTag;
			if (ServerGamerTags.Find(UserSlotHandle))
			{
				GamerTag = ServerGamerTags[UserSlotHandle];
			}

			// Create runtime settings
			FBeamPartyPlayerRuntimeSettings RuntimeSettings;
			RuntimeSettings.bIsPartyLeader = PartyPlayerSettings.bIsPartyLeader;
			RuntimeSettings.GamerTag = GamerTag.AsString;
			RuntimeSettings.PartyTags = PartyPlayerSettings.PartyTags;

			if (PartyPlayersRuntimeMap.Contains(PartyPlayerSettings.PartyId))
			{
				PartyPlayersRuntimeMap[PartyPlayerSettings.PartyId].Add(RuntimeSettings);
			}
			else
			{
				// Add to map with PartyId as key
				PartyPlayersRuntimeMap.Add(PartyPlayerSettings.PartyId, {RuntimeSettings});
			}
		}

		if (PartyPlayersRuntimeMap.Num() == 0)
		{
			RequestTracker->TriggerOperationError(Operation, TEXT("No Parties to Create"));
		}

		// Create a TArray to hold all party requests
		TArray<UPutPartiesRequest*> PartyRequests;

		// Iterate through each party in PartyPlayersRuntimeMap
		for (const auto& PartyEntry : PartyPlayersRuntimeMap)
		{
			const FString& PartyId = PartyEntry.Key;
			const TArray<FBeamPartyPlayerRuntimeSettings>& PartyPlayers = PartyEntry.Value;

			// Create a new request for this party
			UPutPartiesRequest* Req = NewObject<UPutPartiesRequest>();
			Req->Body = NewObject<UParty>();

			// Find the leader and build the members array
			TArray<FBeamGamerTag> Members;
			FBeamGamerTag LeaderTag;
			bool bLeaderFound = false;

			for (const auto& PlayerSettings : PartyPlayers)
			{
				FBeamGamerTag GamerTag = FBeamGamerTag(PlayerSettings.GamerTag);
				Members.Add(GamerTag);

				if (PlayerSettings.bIsPartyLeader && !bLeaderFound)
				{
					LeaderTag = GamerTag;
					bLeaderFound = true;
				}
			}

			// Set the leader
			if (bLeaderFound)
			{
				Req->Body->Leader = FOptionalBeamGamerTag(LeaderTag);
			}

			// Set the members
			Req->Body->Members = FOptionalArrayOfBeamGamerTag(Members);

			// Set max size (optional - defaulting to number of members if not specified)
			Req->Body->MaxSize = FOptionalInt32(Members.Num());

			// Build MembersTags map
			TMap<FString, UTagList*> MembersTags;
			for (const auto& PlayerSettings : PartyPlayers)
			{
				if (PlayerSettings.PartyTags.Num() > 0)
				{
					UTagList* TagList = NewObject<UTagList>();
					TArray<FBeamTag> Tags;

					for (const auto& TagPair : PlayerSettings.PartyTags)
					{
						Tags.Add(FBeamTag(TagPair.Key, TagPair.Value));
					}

					TagList->Tags = FOptionalArrayOfBeamTag(Tags);
					MembersTags.Add(PlayerSettings.GamerTag, TagList);
				}
			}

			if (MembersTags.Num() > 0)
			{
				Req->Body->MembersTags = FOptionalMapOfTagList(MembersTags);
			}
			Req->Body->Restriction = FOptionalString("Unrestricted");
			// Add the request to the array
			PartyRequests.Add(Req);
		}

		TArray<FBeamOperationHandle> PartyOperations;
		for (auto PartyRequest : PartyRequests)
		{
			FBeamOperationHandle PartyOperation = RequestTracker->CPP_BeginOperation({ServerSlot}, GetName(), {});

			PartyOperations.Add(PartyOperation);

			FBeamRequestContext PartyContext;
			API->CPP_PutParties(ServerSlot, PartyRequest, FOnPutPartiesFullResponse::CreateLambda([this, WorldContext, PartyOperation](const FPutPartiesFullResponse& Event)
			{
				if (!IsValidContext(WorldContext)) return;

				if (Event.State == RS_Success)
				{
					UE_LOG(LogBeamEditor, Log, TEXT("%s Server - All Parties Created."), *GetLogArgs(TEXT("Party Created"), WorldContext));
					RequestTracker->TriggerOperationSuccess(PartyOperation, TEXT(""));
				}
				else
				{
					UE_LOG(LogBeamEditor, Error, TEXT("%s Server - Fail to create party"), *GetLogArgs(TEXT("Party Created Fail"), WorldContext));
					RequestTracker->TriggerOperationError(PartyOperation, Event.ErrorData.message);
				}
			}), PartyContext, PartyOperation, WorldContext->World());
		}

		RequestTracker->CPP_WaitAll({}, PartyOperations, {}, FOnWaitCompleteCode::CreateLambda([this, Operation](const FBeamWaitCompleteEvent& Event)
		{
			FString ErrorMessage = "";
			for (auto Error : Event.Errors)
			{
				if (!Error.error.IsEmpty())
				{
					ErrorMessage += Error.message + "\n";
				}
			}
			if (!ErrorMessage.IsEmpty())
			{
				for (auto Error : Event.Errors)
				{
					ErrorMessage += Error.message + "\n";
				}
				UE_LOG(LogTemp, Warning, TEXT("Some Party Creation Operations failed during BeamPIE Server Preparation."));

				RequestTracker->TriggerOperationError(Operation, ErrorMessage);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("All Party Creation Operations succeeded during BeamPIE Server Preparation."));
				RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
			}
		}));
	}

	UFUNCTION(BlueprintCallable)
	void GetAllPartyUsersMap(FBeamPIE_Settings Settings, TMap<FBeamPIE_UserSlotHandle, FBeamPIE_PerUserSetting>& PartyUsersMap)
	{
		for (auto AssignedUser : Settings.AssignedUsers)
		{
			if (IsPartySet(AssignedUser.Value.PartySettings))
			{
				PartyUsersMap.Add(AssignedUser.Key, AssignedUser.Value);
			}
		}
	}

	UFUNCTION(BlueprintCallable)
	void ValidateTeamUsersMap(FBeamPIE_Settings Settings, TMap<FBeamPIE_UserSlotHandle, FString>& PartyTeamMap)
	{
		TMap<FBeamPIE_UserSlotHandle, FBeamPIE_PerUserSetting> PartyUsers;
		GetAllPartyUsersMap(Settings, PartyUsers);

		TArray<FBeamPIE_UserSlotHandle> LeaderHandles;
		for (auto LeaderUser : PartyUsers)
		{
			if (LeaderUser.Value.PartySettings.bIsPartyLeader)
			{
				for (auto AssignedUser : Settings.AssignedUsers)
				{
					if (AssignedUser.Key == LeaderUser.Key)
					{
						continue;
					}
					if (AssignedUser.Value.PartySettings.PartyId == LeaderUser.Value.PartySettings.PartyId)
					{
						PartyTeamMap.Add(AssignedUser.Key, LeaderUser.Value.Team);
					}
				}
			}
		}
	}

	bool ShouldCreateParty(FBeamPIE_Settings const* const Settings)
	{
		for (auto AssignedUser : Settings->AssignedUsers)
		{
			if (!AssignedUser.Value.PartySettings.PartyId.IsEmpty())
			{
				return true;
			}
		}
		return false;
	}

	bool IsPartySet(FBeamPIE_PlayerPartySettings PartySettings)
	{
		return !PartySettings.PartyId.IsEmpty();
	}

	void GetLobbyTeams(FBeamPIE_Settings const* const Settings, UBeamGameTypeContent* GameTypeContent, TMap<FBeamPIE_UserSlotHandle, FString>& TeamToPlayerHandlesMap)
	{
		// Build party groupings if party settings are enabled
		TMap<FString, TArray<FBeamPIE_UserSlotHandle>> PartyGroups;
		// Initialize team tracking structures
		TMap<FString, int32> TeamCurrentCount;
		TArray<FString> TeamNames;

		for (const FBeamMatchmakingTeamsRule& Team : GameTypeContent->Teams)
		{
			TeamNames.Add(Team.Name);
			TeamCurrentCount.Add(Team.Name, 0);
		}

		if (ShouldCreateParty(Settings))
		{
			TMap<FBeamPIE_UserSlotHandle, FBeamPIE_PerUserSetting> PartyUsersMap;
			GetAllPartyUsersMap(*Settings, PartyUsersMap);

			for (const auto& PlayerSetting : PartyUsersMap)
			{
				// If the team is set we ignore the party for team assignment
				if (!PlayerSetting.Value.Team.IsEmpty() && TeamNames.Contains(PlayerSetting.Value.Team))
				{
					continue;
				}
				const FBeamPIE_UserSlotHandle& UserSlotHandle = PlayerSetting.Key;
				const FBeamPIE_PlayerPartySettings& PartyPlayerSettings = PlayerSetting.Value.PartySettings;

				if (PartyGroups.Contains(PartyPlayerSettings.PartyId))
				{
					PartyGroups[PartyPlayerSettings.PartyId].Add(UserSlotHandle);
				}
				else
				{
					PartyGroups.Add(PartyPlayerSettings.PartyId, {UserSlotHandle});
				}
			}
		}


		// Assign party members to teams
		for (const auto& PartyGroup : PartyGroups)
		{
			const TArray<FBeamPIE_UserSlotHandle>& PartyMembers = PartyGroup.Value;

			// Find team with least players (ignoring MaxPlayers)
			FString BestTeam;
			int32 LeastPlayers = INT32_MAX;

			for (const FString& TeamName : TeamNames)
			{
				if (TeamCurrentCount[TeamName] < LeastPlayers)
				{
					LeastPlayers = TeamCurrentCount[TeamName];
					BestTeam = TeamName;
				}
			}

			// Assign all party members to the same team
			if (!BestTeam.IsEmpty())
			{
				for (const FBeamPIE_UserSlotHandle& Member : PartyMembers)
				{
					TeamToPlayerHandlesMap.Add(Member, BestTeam);
					TeamCurrentCount[BestTeam]++;
				}
			}
		}

		// Collect non-party players
		TArray<FBeamPIE_UserSlotHandle> NonPartyPlayers;
		for (const auto& KVP : ServerGamerTags)
		{
			const FBeamPIE_UserSlotHandle& UserHandle = KVP.Key;

			// Check if player is not in any party
			if (!TeamToPlayerHandlesMap.Contains(UserHandle))
			{
				NonPartyPlayers.Add(UserHandle);
			}
		}

		// Distribute non-party players alternately across teams with available slots
		int32 CurrentTeamIndex = 0;
		for (const FBeamPIE_UserSlotHandle& Player : NonPartyPlayers)
		{
			if (TeamNames.Num() > 0)
			{
				auto BeamPie_PerUserSetting = Settings->AssignedUsers[Player];
				if (!BeamPie_PerUserSetting.Team.IsEmpty() && TeamNames.Contains(BeamPie_PerUserSetting.Team))
				{
					TeamToPlayerHandlesMap.Add(Player, BeamPie_PerUserSetting.Team);
					TeamCurrentCount[BeamPie_PerUserSetting.Team]++;
					continue;
				}
				// Find next team with available slots
				bool bFoundTeam = false;
				int32 TeamsChecked = 0;

				while (TeamsChecked < TeamNames.Num())
				{
					CurrentTeamIndex = (CurrentTeamIndex + 1) % TeamNames.Num();
					const FString& CandidateTeam = TeamNames[CurrentTeamIndex];

					// Check if this team has room based on MaxPlayers rule
					const FBeamMatchmakingTeamsRule* TeamRule = GameTypeContent->Teams.FindByPredicate(
						[&CandidateTeam](const FBeamMatchmakingTeamsRule& Rule) { return Rule.Name == CandidateTeam; }
					);

					if (TeamRule && TeamCurrentCount[CandidateTeam] < TeamRule->MaxPlayers)
					{
						TeamToPlayerHandlesMap.Add(Player, CandidateTeam);
						TeamCurrentCount[CandidateTeam]++;
						bFoundTeam = true;
						break;
					}

					TeamsChecked++;
				}

				if (!bFoundTeam)
				{
					UE_LOG(LogBeamEditor, Warning, TEXT("Could not assign player - all teams are full"));
				}
			}
		}
	}

	void AutoCreateLobby(FWorldContext* WorldContext, FBeamPIE_Settings const* const Settings, const FUserSlot ServerSlot, FBeamOperationHandle Operation)
	{
		UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Creating Fake Lobby for GameServer."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
		// Then, we call the make magical lobby endpoint until it succeeds passing in these users.					
		const auto API = GEngine->GetEngineSubsystem<UBeamLobbyApi>();

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

			UBeamContentObject* ContentObject;
			WorldContext->World()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>()->TryGetContent(Settings->FakeLobby.GameType, ContentObject);

			UBeamGameTypeContent* GameTypeContent = static_cast<UBeamGameTypeContent*>(ContentObject);


			TMap<FBeamPIE_UserSlotHandle, FString> PlayerPartyTeamsMap;

			GetLobbyTeams(Settings, GameTypeContent, PlayerPartyTeamsMap);

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
				if (Settings->AssignedUsers.Contains(Handle))
				{
					if (IsPartySet(Settings->AssignedUsers[Handle].PartySettings))
					{
						for (const auto& LobbyData : Settings->AssignedUsers[Handle].PartySettings.PartyTags)
							Tags.Add(FBeamTag{LobbyData.Key, LobbyData.Value});
					}
				}

				// Set the properties we forward
				const auto LobbyPlayer = NewObject<ULobbyPlayer>();
				LobbyPlayer->PlayerId = FOptionalBeamGamerTag{GamerTag};
				LobbyPlayer->Joined = FOptionalDateTime{FDateTime::UtcNow()};
				LobbyPlayer->Tags = bHasPlayerSettings ? FOptionalArrayOfBeamTag{Tags} : FOptionalArrayOfBeamTag{};
				if (GetDefault<UBeamRuntimeSettings>()->bEnableGameplayFrameworkIntegration)
				{
					if (LobbyPlayer->Tags.IsSet) LobbyPlayer->Tags.Val.Add(FBeamTag{UBeamLobbySubsystem::Reserved_PlayerTag_UniqueNetId_Property, GamerTag.AsString});
					else LobbyPlayer->Tags = FOptionalArrayOfBeamTag{TArray{FBeamTag{UBeamLobbySubsystem::Reserved_PlayerTag_UniqueNetId_Property, GamerTag.AsString}}};
				}
				else
				{
					UE_BEAM_LOG_PIE(WorldContext, LogBeamEditor, Warning,
					                TEXT("If you are not using Beamable GamerTags as UniqueNetIds because you want to use something else as the UniqueId,"
						                " you need to either configure NetIds manually in the play settings OR"
						                " set up the AcceptUserIntoGameServer flow so we can keep the mapping between UniqueNetIds and GamerTags.\n"
						                "If you aren't using any other UniqueNetIds, we recommend you turn UBeamRuntimeSettings::bUseBeamableGamerTagsAsUniqueNetIds on in your Project Settings."))
				}


				if (GameTypeContent && GameTypeContent->Teams.Num() > 0 && PlayerPartyTeamsMap.Contains(Handle))
				{
					if (LobbyPlayer->Tags.IsSet) LobbyPlayer->Tags.Val.Add(FBeamTag{UBeamLobbySubsystem::Reserved_PlayerTag_Team_Property, PlayerPartyTeamsMap[Handle]});
					else LobbyPlayer->Tags = FOptionalArrayOfBeamTag{TArray{FBeamTag{UBeamLobbySubsystem::Reserved_PlayerTag_Team_Property, PlayerPartyTeamsMap[Handle]}}};
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
			RequestTracker->TriggerOperationError(Operation, TEXT("UNSUPPORTED_LISTEN_SERVER"));
			return;
		}

		UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Trying to Create the Fake Lobby"), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));
		auto Req = NewObject<UPutLobbiesRequest>();
		Req->Body = FakeLobby;

		const auto CreateLobbyHandler = FOnPutLobbiesFullResponse::CreateUObject(this, &UBeamPIE::PreparePIE_Server_CreateLobbyHandler, WorldContext, Req, Operation);
		FBeamRequestContext Ctx;
		API->CPP_PutLobbies(ServerSlot, Req, CreateLobbyHandler, Ctx, Operation, WorldContext->World());
	}

	void PreparePIE_LoadAllAssignedUsers(FWorldContext* WorldContext, FBeamPIE_Settings const* const Settings)
	{
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
	}

	/**
	 * This function uses the currently selected settings and then do what it needs to do to provide its semantics. 
	 */
	void PreparePIE_ApplySelectedSettings(FWorldContext* WorldContext, FBeamOperationHandle Op)
	{
#if !WITH_EDITOR
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
#else
		// If we don't have a setting selected, we should just complete the operation (this happens in builds).
		const auto Settings = GetSelectedPIESettings();
		if (!Settings || Settings->IsDefaultSettings())
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		// Verifies the world context, world and game instance (necessary cause UE will just kill these things when you stop PIE)		
		if (!ensureAlwaysMsgf(WorldContext && WorldContext->World(), TEXT("You should never see this!")))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_WORLD_CONTEXT_FOR_BEAM_PIE"));
			return;
		}

		const auto GI = WorldContext->World()->GetGameInstance();
		if (!ensureAlwaysMsgf(GI, TEXT("You should never see this!")))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_GAME_INSTANCE_OR_BEAM_PIE"));
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
				// Only iterate over users that are assigned to this PIE instance.
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

				// Get the UBeamRuntime subsystem so that we can auto-magically log in with the cached user.
				// The cached user on the configured slots will eventually be there (because we tell the CLI to put them there).
				const auto Runtime = GI->GetSubsystem<UBeamRuntime>();
				const auto LoginLocalCacheHandler = FBeamOperationEventHandlerCode::CreateUFunction(
					this,
					GET_FUNCTION_NAME_CHECKED(UBeamPIE, PreparePIE_Client_LoginHandler),
					Runtime,
					CurrSlotHandle,
					PossibleSlotHandles,
					Op);

				// Set up a "retry until succeed here"
				UE_LOG(LogBeamEditor, Log, TEXT("%s Client - Logging in from Cache. USER_SLOT=%s, PIE=%d"),
				       *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext), *CurrSlotHandle.Slot.Name, CurrSlotHandle.PIEIndex);

				RequestTracker->TriggerOperationEventWithData(Op, OET_SUCCESS, GetOperationEventID_PIE_ProgressionStep(), TEXT(""), UBeamPIEProgressionStep::CreateLoginStep());

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
			PreparePIE_LoadAllAssignedUsers(WorldContext, Settings);

			const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

			auto PresenceOperation = RequestTracker->CPP_BeginOperation({}, GetName(), FBeamOperationEventHandlerCode::CreateLambda([this, WorldContext, Settings, ServerSlot, Op](const FBeamOperationEvent& Event)
			{
				if (Event.EventType != OET_SUCCESS)
				{
					RequestTracker->TriggerOperationError(Op, Event.EventCode);
					return;
				}
				// If have to create both Party and Lobby, we chain the operations.
				if (ShouldCreateParty(Settings) && Settings->FakeLobby.bShouldAutoCreateLobby)
				{
					auto PartyAutoCreationOperation = RequestTracker->CPP_BeginOperation({}, GetName(), FBeamOperationEventHandlerCode::CreateLambda(
						                                                                     [this, WorldContext, Settings, ServerSlot, Op](const FBeamOperationEvent& Event)
						                                                                     {
							                                                                     if (Event.EventType != OET_SUCCESS)
							                                                                     {
								                                                                     RequestTracker->TriggerOperationError(Op, Event.EventCode);
								                                                                     WorldContext->World()->GetGameInstance()->GetEngine()->DeferredCommands.Add(TEXT("exit"));
								                                                                     return;
							                                                                     }
							                                                                     auto LobbyAutoCreationOperation = RequestTracker->CPP_BeginOperation(
								                                                                     {}, GetName(), FBeamOperationEventHandlerCode::CreateLambda([this, Op](const FBeamOperationEvent& Event)
								                                                                     {
									                                                                     if (Event.EventType == OET_SUCCESS)
									                                                                     {
										                                                                     RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
									                                                                     }
									                                                                     else
									                                                                     {
										                                                                     RequestTracker->TriggerOperationError(Op, Event.EventCode);
									                                                                     }
								                                                                     }));
							                                                                     AutoCreateLobby(WorldContext, Settings, ServerSlot, LobbyAutoCreationOperation);
						                                                                     }));
					AutoCreateParty(WorldContext, Settings, PartyAutoCreationOperation);
					return;
				}

				// If we are creating only the lobby
				if (Settings->FakeLobby.bShouldAutoCreateLobby)
				{
					auto LobbyAutoCreationOperation = RequestTracker->CPP_BeginOperation({}, GetName(), FBeamOperationEventHandlerCode::CreateLambda([this, Op](const FBeamOperationEvent& Event)
					{
						if (Event.EventType != OET_SUCCESS)
						{
							RequestTracker->TriggerOperationError(Op, Event.EventCode);
						}
						else
						{
							RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
						}
					}));
					AutoCreateLobby(WorldContext, Settings, ServerSlot, LobbyAutoCreationOperation);
				}
			}));
			// Check the presence for all players in the settings before continue with party and lobby creation.
			const auto PresenceAPI = GEngine->GetEngineSubsystem<UBeamPresenceApi>();
			UPostQueryRequest* PresenceRequest = NewObject<UPostQueryRequest>();

			TArray<FString> GamerTags;

			for (auto ServerGamerTag : ServerGamerTags)
			{
				GamerTags.Add(ServerGamerTag.Value.AsString);
			}

			PresenceRequest->Body = NewObject<UOnlineStatusQuery>();
			PresenceRequest->Body->PlayerIds = FOptionalArrayOfString(GamerTags);

			const auto PresenceHandler = FOnPostQueryFullResponse::CreateUObject(this, &UBeamPIE::CheckPIE_OnlinePlayersHandler, WorldContext, PresenceRequest, PresenceOperation);

			FBeamRequestContext PresenceContext;
			PresenceAPI->CPP_PostQuery(ServerSlot, PresenceRequest, PresenceHandler, PresenceContext, {}, WorldContext->World());
		}
#endif
	}

	TArray<FBeamTag> GetBeamTags(TMap<FString, FString> InMap)
	{
		TArray<FBeamTag> OutTags;
		for (const auto& KVP : InMap)
		{
			OutTags.Add(FBeamTag{KVP.Key, KVP.Value});
		}
		return OutTags;
	}

	/**
	 * Keep trying to log in with local cache until that is done, login Local Cache with the expected users.	  
	 */
	UFUNCTION()
	void PreparePIE_Client_LoginHandler(FBeamOperationEvent Evt, UBeamRuntime* Runtime, FBeamPIE_UserSlotHandle CurrSlotHandle, TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles, FBeamOperationHandle PrepareOp)
	{
		auto WorldContext = GEngine->GetWorldContextFromWorld(Runtime->GetWorld());

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

	void CheckPIE_OnlinePlayersHandler(FPostQueryFullResponse Response, FWorldContext* WorldContext, UPostQueryRequest* Request, FBeamOperationHandle Operation)
	{
		if (!IsValidContext(WorldContext)) return;

		bool bIsAllPlayersOnline = true;

		if (Response.State == RS_Success)
		{
			if (Response.SuccessData->PlayersStatus.IsSet)
			{
				for (auto PlayerStatus : Response.SuccessData->PlayersStatus.Val)
				{
					if (!PlayerStatus->bOnline.Val)
					{
						bIsAllPlayersOnline = false;
						break;
					}
				}
			}
			else
			{
				bIsAllPlayersOnline = false;
			}
			if (bIsAllPlayersOnline)
			{
				RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Waiting for all players to be online in Beam PIE Server Preparation."));
			}
		}

		if (Response.State != RS_Success || !bIsAllPlayersOnline)
		{
			// If we fail, create a new handler and call the PutLobbies endpoint again
			// This is guaranteed to succeed eventually because all clients are logging into the game.
			FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this,WorldContext, Request, Operation](const float)
			{
				if (!IsValidContext(WorldContext)) return false;

				const auto PresenceAPI = GEngine->GetEngineSubsystem<UBeamPresenceApi>();
				const auto PresenceHandler = FOnPostQueryFullResponse::CreateUObject(this, &UBeamPIE::CheckPIE_OnlinePlayersHandler, WorldContext, Request, Operation);
				const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

				FBeamRequestContext Ctx;

				PresenceAPI->CPP_PostQuery(ServerSlot, Request, PresenceHandler, Ctx, {}, WorldContext->World());
				return false;
			}), 0.2f);
		}
	}

	/**
	 * Keep trying to create a lobby until that is done. Since we expect all players to 	  
	 */
	void PreparePIE_Server_CreateLobbyHandler(FPutLobbiesFullResponse Resp, FWorldContext* WorldContext, UPutLobbiesRequest* Req, FBeamOperationHandle PrepareOp)
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
			FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this,WorldContext, PrepareOp, Req](const float)
			{
				if (!IsValidContext(WorldContext)) return false;

				UE_LOG(LogBeamEditor, Log, TEXT("%s Server - Failed to create lobby. Trying again."), *GetLogArgs(TEXT("Beam PIE Prepare"), WorldContext));

				const auto CreateLobbyHandler = FOnPutLobbiesFullResponse::CreateUObject(this, &UBeamPIE::PreparePIE_Server_CreateLobbyHandler, WorldContext, Req, PrepareOp);
				FBeamRequestContext Ctx;

				const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
				const auto API = GEngine->GetEngineSubsystem<UBeamLobbyApi>();
				API->CPP_PutLobbies(ServerSlot, Req, CreateLobbyHandler, Ctx, PrepareOp, WorldContext->World());
				return false;
			}), 0.2f);
		}
	}

	/**
	 * When integrating with a game server orchestrator SDK (Hathora, Agones, etc...), you only need to run them
	 * if you are NOT running a dedicated server locally.
	 *
	 * This function is meant to be called in your dedicated server's start up flow (typically in a GameMode's BeginPlay) in order to decide whether your orchestrator's SDK needs initialization or not.
	 * You can also call this in clients to avoid doing orchestrator work, if your it also has a Client SDK for whatever reason.
	 *
	 * Outside the PIE environment, this always return true. During PIE, this only returns true if UE's PIE configurations are NOT creating a local server for you.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	bool PreparePIE_Advanced_RequiresGameServerOrchestratorSetup(const UObject* CallingContext)
	{
#if !WITH_EDITOR
		return true;
#else
		const auto Settings = GetSelectedPIESettings();
		if (!Settings || Settings->IsDefaultSettings()) return true;

		// We are in a deployed dedicated server (not running from the editor), we won't need to set up the orchestrator's SDK.
		return !GetDefault<UBeamPIEConfig>()->bIsRunningGameServerLocally;
#endif
	}

	/**
	 *  When implementing server authentication via a AGameMode::PreLoginAsync, this is used to keep BeamPIE working.
	 *  This works be cause, PIE clients are guaranteed to be initialized and attempt to connect IN ORDER.
	 *
	 *  This makes it so that, on the server, BeamPIE can keep track of which "Options" string each connection attempt would've contained and then apply them to it. 
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FString PreparePIE_Advanced_GetExpectedClientPIEOptions(FString Options, UObject* CallingContext)
	{
#if !WITH_EDITOR
		return Options;
#else

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

#endif
	}

	/**
	 * When setting up the advanced flow, we need this function to be called before we actually prepare PIE so that it disables the Easy Mode Beam PIE from running.
	 * This is mostly just to not have to ask people to remove the node from their level blueprints. 
	 */
	void PreparePIE_Advanced_NotifyCustomGameInstanceGuard(bool state)
	{
#if WITH_EDITOR
		bCustomGameInstanceGuard = state;
#endif
	}

	/**
	 * Once a PIE client successfully connects to the booting server, it'll wait until this returns FALSE before actually travelling to the server's map.
	 *
	 * This is important because we can then tell it to wait until the Prepare PIE process is fully done.
	 * Unfortunately, Unreal doesn't provide a similar thing for "before it attempts to connect to the server", but this works well enough in most cases.
	 */
	bool PreparePIE_Advanced_DelayPendingNetGameTravel(UGameInstance* This)
	{
#if !WITH_EDITOR
		return false;
#else
		auto CoreSettings = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		const auto PieInstanceIdx = FBeamPIE_Utilities::GetPIEInstance(This->GetWorldContext());
		if (!ClientDelayMapHandles.Contains(PieInstanceIdx))
		{
			const auto Handle = CPP_WaitForBeamPIEOperation(CoreSettings, This, {});
			ClientDelayMapHandles.Add(PieInstanceIdx, Handle);
			return true;
		}

		const auto Handle = ClientDelayMapHandles[PieInstanceIdx];
		auto ReqTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
		return ReqTracker->IsOperationActive(Handle);
#endif
	}

private:
	/**
	 * @brief Operation logic that:
	 *  - On the client, will until they are logged in AND, if the current settings specify it, until they are aware they are in the lobby.
	 *  - On the server, this waits until the lobby is created.
	 */
	void WaitUntilInitPIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
		// When running outside the editor, this is a no-op.
#if !WITH_EDITOR
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
#else
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
						// On clients, only iterate over users for those clients. On the server, collect all the users.
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

						ULobby* FoundLobby;
						auto FoundLobbyInServer = World->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>()->TryGetLobbyById(FGuid{FakeLobbyId}, FoundLobby);
						if (!FoundLobbyInServer)
						{
							FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this,WorldContext, Op](const float)
							{
								if (!IsValidContext(WorldContext)) return false;
								ULobby* FoundLobby;
								if (WorldContext->World()->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>()->TryGetLobbyById(FGuid{FakeLobbyId}, FoundLobby))
								{
									RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
									return false;
								}
								return true;
							}), 0.2f);
						}
						else
						{
							RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
						}
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
#endif
	}

	/**
	 * @copybrief WaitUntilInitPIE
	 */
	void WaitUntilClientIsLoggedIn(UBeamRuntime* Runtime, TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles, FBeamOperationHandle Op)
	{
		RequestTracker->TriggerOperationEventWithData(Op,
		                                              OET_SUCCESS,
		                                              GetOperationEventID_PIE_ProgressionStep(),
		                                              TEXT(""),
		                                              UBeamPIEProgressionStep::CreateWaitingForServerStep());

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
			if (!Runtime->GetSlotConnectivity(CurrHandle.Slot)->bIsUserReady)
			{
				// Set this as false
				bAreAllUsersAlreadyLoggedIn = false;
			}
		}

		if (bAreAllUsersAlreadyLoggedIn)
		{
			UE_BEAM_LOG_PIE(WorldContext, LogBeamEditor, Log, TEXT("Completed Wait until all Login Operation right away"));
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		}
		else
		{
			FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this,PieInstance, WorldContext, Op, PossibleSlotHandles, Runtime](const float)
			{
				if (!IsValidContext(WorldContext)) return false;
				// Let's make sure all the users configured for this PIE instance are done logging in.
				auto bAreAllUsersAlreadyLoggedIn = true;
				for (const auto& CurrHandle : PossibleSlotHandles)
				{
					// We only care about the users in this PIE instance.
					if (CurrHandle.PIEIndex != PieInstance) continue;

					// If we are NOT already logged in...
					FBeamRealmUser UserData;
					if (!Runtime->GetSlotConnectivity(CurrHandle.Slot)->bIsUserReady)
					{
						// Set this as false
						bAreAllUsersAlreadyLoggedIn = false;
					}
				}

				if (bAreAllUsersAlreadyLoggedIn)
				{
					RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
					return false;
				}
				return true;
			}), 0.2f);
		}
	}

	/**
	 * @copybrief WaitUntilInitPIE
	 */
	void WaitUntilClientIsInLobby(UBeamRuntime* Runtime, TArray<FBeamPIE_UserSlotHandle> PossibleSlotHandles, FBeamOperationHandle Op)
	{
		RequestTracker->TriggerOperationEventWithData(Op, OET_SUCCESS, GetOperationEventID_PIE_ProgressionStep(), TEXT(""), UBeamPIEProgressionStep::CreateEnteringInLobbyStep());

		const auto WorldContext = GEngine->GetWorldContextFromWorld(Runtime->GetWorld());
		const auto PieInstance = FBeamPIE_Utilities::GetPIEInstance(WorldContext);

		// For each of them, check if we already are 
		const auto LobbySystem = Runtime->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		auto bAreAllUsersAlreadyInTheLobby = true;
		for (const auto& Handle : PossibleSlotHandles)
		{
			// We only care about the users in this PIE instance.
			if (Handle.PIEIndex != PieInstance) continue;

			// If the user is NOT already in the lobby, let's set up a notification that will trigger when they see that they've joined it.
			ULobby* UserLobby = nullptr;
			if (!LobbySystem->TryGetCurrentLobby(Handle.Slot, UserLobby) || !UserLobby->Data.Val.Contains(UBeamLobbySubsystem::Reserved_Lobby_From_Editor_Play_Mode_Property))
			{
				UE_LOG(LogBeamEditor, Log, TEXT("%s Client - User is not in Lobby yet. Setting up the notification listener. USER_SLOT=%s, PIE=%d"), *GetLogArgs(TEXT("Beam PIE Prepare"),
					       GEngine->GetWorldContextFromWorld(Runtime->GetWorld())), *Handle.Slot.Name, Handle.PIEIndex);

				bAreAllUsersAlreadyInTheLobby = false;
				// Add a ticker function to check if the user is inside a lobby
				FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([=, this](const float)
				{
					if (!IsValidContext(WorldContext)) return false;

					auto bAreAllUsersInTheLobby = true;
					for (const auto& CurrHandle : PossibleSlotHandles)
					{
						// We only care about the users in this PIE instance.
						if (CurrHandle.PIEIndex != PieInstance) continue;

						ULobby* Lobby;
						if (!LobbySystem->TryGetCurrentLobby(CurrHandle.Slot, Lobby))
						{
							// Set this as false
							bAreAllUsersInTheLobby = false;
						}
						else
						{
							UE_LOG(LogBeamEditor, Log, TEXT("%s Client - User is joined Lobby. USER_SLOT=%s, PIE=%d, LOBBY=%s"), *GetLogArgs(TEXT("Beam PIE Prepare"),
								       GEngine->GetWorldContextFromWorld(Runtime->GetWorld())), *Handle.Slot.Name, Handle.PIEIndex, *Lobby->LobbyId.Val);
						}
					}

					if (bAreAllUsersInTheLobby)
					{
						RequestTracker->TriggerOperationEventWithData(Op, OET_SUCCESS, GetOperationEventID_PIE_ProgressionStep(), TEXT(""), UBeamPIEProgressionStep::CreateWaitingForServerStep());

						RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
						return false;
					}
					return true;
				}), 0.2f);
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


	/*

 _   _ _   _ _ _ _   _           
| | | | |_(_) (_) |_(_) ___  ___ 
| | | | __| | | | __| |/ _ \/ __|
| |_| | |_| | | | |_| |  __/\__ \
 \___/ \__|_|_|_|\__|_|\___||___/

	 */

public:
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
#else
		// If Beam PIE is disabled we just return the default settings which means disabled.
		if (!GetDefault<UBeamCoreSettings>()->bEnableBeamPIE) return DefaultSettings();

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
#endif
	}

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

private:
	/**
	 * Checks if the FContext is valid
	 */
	bool IsValidContext(FWorldContext* Context)
	{
		bool bIsValid = Context != nullptr && Context->WorldType != EWorldType::None && Context->World();
		if (!bIsValid)
		{
			UE_LOG(LogBeamEditor, Warning, TEXT("This delegate called was made during terminated PIE Session"));
		}
		return bIsValid;
	}

	/**
	 * Helper function for us to log things in this system with information about map and PIE instance.	  
	 */
	FString GetLogArgs(FString Header, FWorldContext* WorldContext)
	{
		if (IsValidContext(WorldContext))
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
		/**
		 * Must be called BEFORE Super::StartGameInstance() inside custom UGameInstance implementations. 
		 */
		BEAMABLECORERUNTIME_API inline void PreStartGameInstance(UGameInstance* This)
		{
#if !WITH_EDITOR
			return;
#else
			UE_LOG(LogBeamRuntime, Warning, TEXT("PRE-INIT PLAY IN EDITOR --- Is Server: %d"), This->IsDedicatedServerInstance());
			auto BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			BeamPIE->PreparePIE_Advanced_NotifyCustomGameInstanceGuard(true);
#endif
		}

		/**
		 * Must be called AFTER Super::StartGameInstance() inside custom UGameInstance implementations. 
		 */
		BEAMABLECORERUNTIME_API inline void StartGameInstance(UGameInstance* This)
		{
#if !WITH_EDITOR
			return;
#else

			UE_LOG(LogBeamRuntime, Warning, TEXT("INIT PLAY IN EDITOR --- Is Server: %d"), This->IsDedicatedServerInstance());
			auto BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			BeamPIE->PreparePIE_Advanced_NotifyCustomGameInstanceGuard(false);
			BeamPIE->CPP_PreparePIEOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), This->GetWorld(), {});
			BeamPIE->PreparePIE_Advanced_NotifyCustomGameInstanceGuard(true);
#endif
		}

#if WITH_EDITOR
		/**
		 * Must be called BEFORE Super::StartPlayInEditorGameInstance() inside custom UGameInstance implementations.
		 * Remember to wrap your @link UGameInstance::StartPlayInEditorGameInstance @endlink implementation in WITH_EDITOR directives.
		 */
		BEAMABLECORERUNTIME_API inline void StartPlayInEditorGameInstance(UGameInstance* This, ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
		{
			UE_LOG(LogBeamRuntime, Warning, TEXT("INIT PLAY IN EDITOR (PIE) --- Is Server: %d, PIE_Instance: %d"), This->IsDedicatedServerInstance(), This->GetWorldContext()->PIEInstance);
			auto BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			BeamPIE->PreparePIE_Advanced_NotifyCustomGameInstanceGuard(false);
			BeamPIE->CPP_PreparePIEOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), This->GetWorld(), {});
			BeamPIE->PreparePIE_Advanced_NotifyCustomGameInstanceGuard(true);
		}
#endif

		/**
		 * Returns true only AFTER the SDK has been initialized and all local players on this client have logged in. 
		 * Must be returned from @link UGameInstance::DelayPendingNetGameTravel @endlink (or composited with other custom conditions your game might have). 
		 */
		BEAMABLECORERUNTIME_API inline bool DelayPendingNetGameTravel(UGameInstance* This)
		{
#if !WITH_EDITOR
			return false;
#else
			auto BeamPIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			return BeamPIE->PreparePIE_Advanced_DelayPendingNetGameTravel(This);
#endif
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
#else
			const auto PIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			return PIE->PreparePIE_Advanced_RequiresGameServerOrchestratorSetup(CallingContext);
#endif
		}
	}

	namespace Authentication
	{
		/**
		 * This leverages PIE's property of starting clients in-order (and attempting to connect them to the server in order),
		 * to guarantee the Options being passed when your PIE clients start mirror what would be passed in a real PreLoginAsync call.
		 *
		 * This enables you to test the PreLoginAsync in PIE correctly (as in, Beamable's @link UBeamLobbySubsystem::CPP_AcceptUserIntoGameServerOperation @endlink runs the same logic in both PIE and builds).
		 */
		BEAMABLECORERUNTIME_API inline FString GetExpectedClientPIEOptions(const AGameModeBase* GameMode, const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId)
		{
#if !WITH_EDITOR
			return Options;
#else
			const auto PIE = GEngine->GetEngineSubsystem<UBeamPIE>();
			return PIE->PreparePIE_Advanced_GetExpectedClientPIEOptions(Options, GameMode->GetWorld());
#endif
		}
	}
}
