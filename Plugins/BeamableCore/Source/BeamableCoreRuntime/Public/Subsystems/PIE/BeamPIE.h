// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/BeamRuntime.h"
#include "Subsystems/EngineSubsystem.h"
#include "Subsystems/Lobby/BeamLobbySubsystem.h"
#include "OnlineSubsystemTypes.h"
#include "PIE/BeamPIEConfig.h"

#include "BeamPIE.generated.h"

UCLASS(BlueprintType, Blueprintable)
class AMyServerBootGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override
	{
		// Use your orchestrator's SDK to get what the Lobby Id is from their "room" setup.
		// Whenever you detect a lobby was assigned to this server instance, you should call:
		//
		// 	const auto NewLobbyId = FGuid(LobbyFromOrchestrator);
		//     const auto Lobby = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		//     Lobby->CPP_RefreshLobbyDataOperation({}, FBeamOperationEventHandlerCode::CreateLambda([](FBeamOperationEvent Evt)
		//     {
		//     	   if (Evt.CompletedWithSuccess())
		//     	   { 
		//             // Once you have refreshed the lobby, if your server is properly initialized and ready to receive player connections, you should call
		//             Lobby->CPP_SetLobbyAsReadyForConnectionsOperation({}, NewLobbyId, {});
		//     	   }     	
		//     }), NewLobbyId);
	}

	virtual void PreLoginAsync(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FOnPreLoginCompleteDelegate& OnComplete) override
	{
		const auto Lobby = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		UE_LOG(LogTemp, Warning, TEXT("Pre-Login - Options:%s, Id:%s"), *Options, *UniqueId.ToString());
		//Lobby->CPP_AcceptUserIntoGameServerOperation()
		Super::PreLoginAsync(Options, Address, UniqueId, OnComplete);

		// TODO: We need to make sure this is set up correctly with a sufficiently large value. 
		// https://forums.unrealengine.com/t/where-to-set-connectiontimeout-value/378351/4


		// Beamable works with the default UniqueIds (basically, we do NOT use an OnlineSubsystem to validate the user)
		//   - Way too much noise on those systems.		
		// TODO: When you join the matchmaking queue, party or lobby, we add a property for each player (which is their ULocalPlayer::UniqueNetId)		
		// TODO: If you are using no OnlineSubsystem here in the server, we'll validate via an Option in the travel (LobbyId+AccessToken --- our AcceptUserIntoLobbyOperation will use that
		// token to verify that you are in-fact you and that you are in one of the lobbies this server manages) and just leave the UniqueId untouched.		
		// TODO: If you are using an OnlineSubsystem here in the server, we'll use the UniqueId to validate that the user coming in from Unreal ClientTravel is
		// actually allowed into the server (by comparing with the property in the lobby). This allows you to use whatever subsystem you want to generate the UniqueNetIds and it'll just work with Beamable.
		// But if you want to avoid OnlineSubsystems in servers, you can.

		// Checks if the SDK is initialized, if not --- wait until it is.
		// Then, checks if the provided lobby is in the list of KnownLobbies:
		//   - If it is, validate the user is in it.
		//   - If it isn't, fetch it and then accept the users into it.
		// It must also keep a map of GamerTag to FUniqueNetIdRepl so that we can easily have a way of getting the gamertag from any ULocalPlayer object
		// https://forums.unrealengine.com/t/how-to-pass-a-custom-uniqueid-into-prelogin-from-clienttravel/459527
		// These should be in the lobby itself.

		// Lobby->AcceptUserIntoGameServerOperation(Options, Address, UniqueId, FBeamOperationEventHandlerCode::CreateLambda([Options, Address, UniqueId, OnComplete](FBeamOperationEvent Evt)
		// {
		// 	// If successful, just forward control back to the engine
		// 	if (Evt.EventType == OET_SUCCESS)
		// 	{				
		// 		Super::PreLoginAsync(Options, Address, UniqueId, OnComplete);
		// 	}
		//
		// 	// If failed, deny entry into the server.
		// 	if (Evt.EventType == OET_ERROR)
		// 	{
		// 		OnComplete.ExecuteIfBound(Evt.EventCode);				
		// 	}			
		// }));
	}
};


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

	UPROPERTY()
	TMap<int32, FString> StartingMapNames;

	UPROPERTY()
	TMap<int32, FGuid> LobbyIds;

#if WITH_EDITOR
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
			this->ReloadConfig();
		}

#if WITH_EDITOR
		// Reload from config any changes made by our PIE Settings window + our editor extension dropdown.
		BeginPIEDelegate = FEditorDelegates::BeginPIE.AddLambda([this](bool)
		{
			StartingMapNames.Reset();
			this->ReloadConfig();
		});
#endif
	}

	virtual void Deinitialize() override
	{
		Super::Deinitialize();
#if WITH_EDITOR
		FEditorDelegates::PreBeginPIE.Remove(BeginPIEDelegate);
#endif
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
	 * @copydoc ManuallyInitializeSubsystemOperationWithUserData
	 */
	FBeamOperationHandle CPP_BeamInitPIEOperation(FUserSlot UserSlot, UObject* CallingContext, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		FBeamOperationHandle Op = RequestTracker->CPP_BeginOperation({}, CallingContext->GetName(), OnOperationEvent);
		BeamInitPIE(CallingContext, Op);
		return Op;
	}

	FBeamPIE_Settings const* GetSelectedPIESettings() const
	{
		return GetDefault<UBeamPIEConfig>()->AllSettings.FindByPredicate([this](FBeamPIE_Settings& S) { return S.SettingsId == GetDefault<UBeamPIEConfig>()->SelectedSettingsId; });
	}

	void BeamInitPIE(UObject* CallingContext, FBeamOperationHandle Op)
	{
		// If we don't have a selected setting, don't do anything.
		if (const auto Settings = GetSelectedPIESettings(); !Settings)
			return;

		if (CallingContext)
		{
			if (const auto World = CallingContext->GetWorld())
			{
				const auto WorldContext = GEngine->GetWorldContextFromWorld(World);
				if (WorldContext && WorldContext->WorldType == EWorldType::PIE)
				{
					// Find the name of the current map and compare
					const auto CurrMapName = UGameplayStatics::GetCurrentLevelName(World);
					UE_LOG(LogTemp, Warning, TEXT("PIE WORLD - Level: %s, Index: %d, IsServer: %d"), *CurrMapName, WorldContext->PIEInstance, WorldContext->RunAsDedicated);

					// We only run this once per-PIE-Instance-Session.
					if (!StartingMapNames.Contains(WorldContext->PIEInstance))
					{
						StartingMapNames.Add(WorldContext->PIEInstance, CurrMapName);
						if (const auto GI = World->GetGameInstance())
						{
							const auto Runtime = GI->GetSubsystem<UBeamRuntime>();
							FBeamRuntimeHandlerCode Started;
							Started.BindLambda([this, CallingContext, WorldContext, Op]()
							{
								BeamPreparePIE(WorldContext, Op);
							});

							Runtime->CPP_RegisterOnStarted_NoExecute(Started);
							Runtime->InitSDK({}, {});
						}
					}
					else
					{
						// This means we changed the level after we entered PIE -- these functions should NEVER do anything here.
					}
				}
			}
		}
	}


	void BeamPreparePIE(FWorldContext* WorldContext, FBeamOperationHandle Op)
	{
		// If we have a settings selected, let's set run some operations.
		if (const auto Setting = GetSelectedPIESettings())
		{
			// Let's wait until the local cache has files in it in accordance to what is configured in the Settings.

			// TODO: Read these from the Setting object instead.
			TArray<FBeamPIE_UserSlotHandle> PossibleHandles;
			const auto& RuntimeSlots = GetDefault<UBeamCoreSettings>()->RuntimeUserSlots;
			for (const auto& RuntimeSlot : RuntimeSlots)
			{
				PossibleHandles.Add({WorldContext->PIEInstance, FUserSlot{RuntimeSlot}});
			}

			// If we are in the server...
			if (WorldContext->RunAsDedicated)
			{
				// Try to create the lobby --- keep trying until it succeeds (allow failing until all the users are online).
			}
			// If we are in the client... 
			else
			{
				for (const auto& Handle : PossibleHandles)
				{
					const auto ExpectedGamerTag = Setting->AssignedUsers[Handle];
					if (const auto World = WorldContext->World())
					{
						if (const auto GI = World->GetGameInstance())
						{
							const auto Runtime = GI->GetSubsystem<UBeamRuntime>();

							// Set up a "retry until succeed here"
							const auto LoginLocalCacheHandler = FBeamOperationEventHandlerCode::CreateUFunction(
								this, GET_FUNCTION_NAME_CHECKED(UBeamPIE, PIEClientLoginHandler),
								Runtime, Handle, Op);
							Runtime->CPP_LoginFromCacheOperation(Handle.Slot, LoginLocalCacheHandler);
						}
					}
				}
				
				// When that is done, wait until the local client is aware that the player is in the fake lobby we created and the lobby information is known.
			}
		}
	}

	/**
	 * Keep trying to log in with local cache until that is done, login Local Cache with the expected users.	  
	 */
	UFUNCTION()
	void PIEClientLoginHandler(FBeamOperationEvent Evt, UBeamRuntime* Runtime, FBeamPIE_UserSlotHandle Handle, FBeamOperationHandle PrepareOp)
	{
		if (Evt.CompletedWithSuccess())
		{
			// Trigger sub-event on PrepareOp "PIE_ClientLoggedIn" (let's pass in the UserSlot data)
			// Set up a "wait until we are in the lobby operation".
		}

		if (Evt.CompletedWithError())
		{
			// If we fail, create a new handler and call the Login from Cache Operation again
			const auto LoginLocalCacheHandler = FBeamOperationEventHandlerCode::CreateUFunction(
				this, GET_FUNCTION_NAME_CHECKED(UBeamPIE, PIEClientLoginHandler),
				Runtime, Handle, PrepareOp);
			Runtime->CPP_LoginFromCacheOperation(Handle.Slot, LoginLocalCacheHandler);
		}
	}

	// Criar o server e as 4 instances de PIE
	// Cada Instancia de PIE precisa init + Login Local Cache
	// Quando td mundo tive logado, o server auto-magico precisa criar o lobby com td mundo dentro (isso só no caso de entrar no PIE na start scene do server ou de gameplay)

	// Na cena de gameplay o cara bota um "Beam PIE Init SDK" -> faz td ali em cima, init a sdk e, se for client, loga o local cache e, se for server, espera e cria o lobby.
	// Na cena de server boot:
	//   - O cara bota o "Init SDK"
	//   - Se for client, o "Beam PIE Client Setup"
	//   - Se for server, o "Beam PIE Server Setup"

	// "Beam PIE ____" should ONLY run when you're starting PIE in this map.

	// Init SDK should not do anything if already initialized and just call the given callback. 
};
