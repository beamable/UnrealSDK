// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/BeamEditor.h"

#include "EditorUtilitySubsystem.h"
#include "AutoGen/Optionals/OptionalArrayOfBeamExternalIdentityLibrary.h"
#include "AutoGen/Optionals/OptionalStringLibrary.h"
#include "AutoGen/SubSystems/BeamAuthApi.h"
#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/BeamRealmsApi.h"
#include "Content/BeamContentTypes/BeamCurrencyContent.h"
#include "Content/BeamContentTypes/BeamItemContent.h"
#include "Content/BeamContentTypes/BeamGameTypeContent.h"
#include "Engine/NetworkSettings.h"

#include "Subsystems/BeamEditorSubsystem.h"
#include "Misc/MessageDialog.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliConfigCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliInitCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliLogoutCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliMeCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliOrgRealmsCommand.h"

const FBeamRealmHandle UBeamEditor::Signed_Out_Realm_Handle = FBeamRealmHandle{FString(""), FString("")};

UBeamEditor* UBeamEditor::GetSelf(const UObject* CallingContext)
{
	return GEditor->GetEditorSubsystem<UBeamEditor>();
}

void UBeamEditor::SetBeamableWindowMessage(UBeamableWindowMessage* message)
{
	this->WindowMessage = message;
}

void UBeamEditor::UpdateBeamableWindowMessage(FString Message, EMessageType typeOfMessage)
{
	if (this->WindowMessage == nullptr)
	{
		this->WindowMessage = NewObject<UBeamableWindowMessage>();
	}
	this->WindowMessage->MessageValue = Message;
	this->WindowMessage->MessageType = typeOfMessage;
}

void UBeamEditor::ClearBeamableWindowMessage()
{
	this->UpdateBeamableWindowMessage(FString(), EMessageType::VE_Info);
}

void UBeamEditor::OpenDocsPage(FDocsPageItem item)
{
	FString Docs = GetDefault<UBeamCoreSettings>()->BeamableEnvironment->DocsUrl;
	if (Docs.IsEmpty())
	{
		Docs = FString("https://beamable.github.io/UnrealSDK/");
	}
	if (!Docs.EndsWith("/"))
	{
		Docs += FString("/");
	}
	const FString FullUri = Docs + item.Path;
	FPlatformProcess::LaunchURL(*FullUri, nullptr, nullptr);
}

void UBeamEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogBeamEditor, Verbose, TEXT("Initializing BeamEditor Subsystem!"));

	// Set us up to track whether we are running PIE
	BeginPIEHandler = FEditorDelegates::BeginPIE.AddLambda([this](const bool)
	{
		bIsRunningPIE = true;
		if (OnEnteringPIE.IsBound())
			OnEnteringPIE.Broadcast();
	});

	EndPIEHandler = FEditorDelegates::EndPIE.AddLambda([this](const bool)
	{
		bIsRunningPIE = false;
		if (OnExitingPIE.IsBound())
			OnExitingPIE.Broadcast();
	});
	bIsRunningPIE = false;

	// Set us up to handle sign-in/out flows in editor as well as tracking multiple developer user slots.	
	UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
	RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();

	// Sets up handlers for us to keep track of whether we are authenticated into the editor	
	MainEditorSlotIdx = 0;

	// Set up a delayed call to initialize the Beamable Editor integration when the Unreal Editor is fully initialized. 
	EditorInitializedHandle = FEditorDelegates::OnEditorInitialized.AddLambda([](double)
	{
		const auto Bootstrapper = GetMutableDefault<UBeamEditorBootstrapper>();
		Bootstrapper->Run();
	});

	// Make sure we have a window message object...
	ClearBeamableWindowMessage();
}

void UBeamEditor::Deinitialize()
{
	UserSlots->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
	UserSlots->GlobalUserSlotClearedCodeHandler.Remove(UserSlotClearedHandler);	
	FEditorDelegates::BeginPIE.Remove(BeginPIEHandler);
	FEditorDelegates::EndPIE.Remove(EndPIEHandler);
	FEditorDelegates::OnEditorInitialized.Remove(EditorInitializedHandle);
}

void UBeamEditorBootstrapper::Run()
{
	Run_DelayedInitialize();
}

void UBeamEditorBootstrapper::Run_DelayedInitialize()
{
	const auto RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	const auto BeamEditor = GEditor->GetEditorSubsystem<UBeamEditor>();

	// This needs to be enabled as it'll make UE add its configured certificates to its HTTP/Websocket clients (which Beamable depends on).
	// This must be on, otherwise, you are risking this error happening in rare cases: "SSL certificate problem: unable to get local issuer certificate"
	// These rare cases happen due to the cert situation on the machine of whoever is running. Turning this on ensures that UE bundle along the necessary certificates
	// (or any inside the "ProjectRoot/Certificates" directory) along with the build.
	// More information here: https://forums.unrealengine.com/t/when-playing-in-the-editor-websocket-connection-successful-but-failed-when-playing-in-packaged-why/436199/18
	auto EngineNetworkSettings = GetMutableDefault<UNetworkSettings>();
	if (!EngineNetworkSettings->bVerifyPeer)
	{
		UE_LOG(LogBeamEditor, Display, TEXT("Enforcing VerifyPeer=true"));
		EngineNetworkSettings->bVerifyPeer = true;
		EngineNetworkSettings->SaveConfig(CPF_Config, *EngineNetworkSettings->GetDefaultConfigFilename());
	}

	/* INFO - Make sure our core settings and environment settings are correctly set up for our users.
	 * When this plugin gets added to the project, there are some default settings that we can pre-set for our users so that they don't have to do it.
	 * This is where we do that.
	 */
	auto CoreSettings = GetMutableDefault<UBeamCoreSettings>();
	if (CoreSettings->BeamableEnvironment.IsNull())
	{
		CoreSettings->BeamableEnvironment = FSoftObjectPath(TEXT("/Script/BeamableCore.BeamEnvironmentData'/BeamableCore/Environments/BeamProdEnv.BeamProdEnv'"));

		CoreSettings->BeamablePossibleEnvironments.AddDefaulted(3);
		CoreSettings->BeamablePossibleEnvironments[0] = FSoftObjectPath(TEXT("/Script/BeamableCore.BeamEnvironmentData'/BeamableCore/Environments/BeamProdEnv.BeamProdEnv'"));
		CoreSettings->BeamablePossibleEnvironments[1] = FSoftObjectPath(TEXT("/Script/BeamableCore.BeamEnvironmentData'/BeamableCore/Environments/BeamStagingEnv.BeamStagingEnv'"));
		CoreSettings->BeamablePossibleEnvironments[2] = FSoftObjectPath(TEXT("/Script/BeamableCore.BeamEnvironmentData'/BeamableCore/Environments/BeamDevEnv.BeamDevEnv'"));

		CoreSettings->SaveConfig(CPF_Config, *CoreSettings->GetDefaultConfigFilename());
	}

	// Set up the default Editor settings
	auto EditorSettings = GetMutableDefault<UBeamEditorSettings>();
	auto bEditorSettingsChanged = false;
	if (EditorSettings->BeamableMainWindow.IsNull())
	{
		EditorSettings->BeamableMainWindow = FSoftObjectPath(TEXT("/Script/Blutility.EditorUtilityWidgetBlueprint'/BeamableCore/Editor/EWBP_BeamableWindow.EWBP_BeamableWindow'"));
		bEditorSettingsChanged = true;
	}

	// Set up Status Icons
	if (EditorSettings->LocalContentStatusIcons.IsEmpty())
	{
		const auto CreatedIconPath = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Script/Engine.Texture2D'/BeamableCore/Editor/Icons/IconStatus_Added.IconStatus_Added'")));
		const auto DeletedIconPath = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Script/Engine.Texture2D'/BeamableCore/Editor/Icons/IconStatus_Deleted.IconStatus_Deleted'")));
		const auto ModifiedIconPath = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Script/Engine.Texture2D'/BeamableCore/Editor/Icons/IconStatus_Modified.IconStatus_Modified'")));
		const auto UpToDateIconPath = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Script/Engine.Texture2D'/BeamableCore/Editor/Icons/IconStatus_NC.IconStatus_NC'")));
		EditorSettings->LocalContentStatusIcons.Add(EBeamLocalContentStatus::Beam_LocalContentCreated, CreatedIconPath);
		EditorSettings->LocalContentStatusIcons.Add(EBeamLocalContentStatus::Beam_LocalContentDeleted, DeletedIconPath);
		EditorSettings->LocalContentStatusIcons.Add(EBeamLocalContentStatus::Beam_LocalContentModified, ModifiedIconPath);
		EditorSettings->LocalContentStatusIcons.Add(EBeamLocalContentStatus::Beam_LocalContentUpToDate, UpToDateIconPath);
		bEditorSettingsChanged = true;
	}
	// Set up the conflicted status icon
	if (!EditorSettings->ConflictedStatusIcon)
	{
		const auto ConflictedIconPath = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Script/Engine.Texture2D'/BeamableCore/Editor/Icons/IconLogs_WarningMsg.IconLogs_WarningMsg'")));
		EditorSettings->ConflictedStatusIcon = ConflictedIconPath;
		bEditorSettingsChanged = true;
	}

	// Set up Content Icons
	if (EditorSettings->LocalContentViewConfigs.IsEmpty())
	{
		const auto BeamableColor = FColor::FromHex(TEXT("9176BCFF"));

		FBeamContentViewConfig ItemConfig;
		ItemConfig.BorderColor = BeamableColor;
		ItemConfig.TypeForContentObject = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Script/Engine.Texture2D'/BeamableCore/Editor/Icons/IconBeam_Item.IconBeam_Item'")));

		FBeamContentViewConfig CurrencyConfig;
		CurrencyConfig.BorderColor = BeamableColor;
		CurrencyConfig.TypeForContentObject = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Script/Engine.Texture2D'/BeamableCore/Editor/Icons/IconBeam_Currency.IconBeam_Currency'")));

		FBeamContentViewConfig GameTypeConfig;
		GameTypeConfig.BorderColor = BeamableColor;
		GameTypeConfig.TypeForContentObject = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Script/Engine.Texture2D'/BeamableCore/Editor/Icons/IconBeam_GameType.IconBeam_GameType'")));

		EditorSettings->LocalContentViewConfigs.Add(UBeamItemContent::StaticClass(), ItemConfig);
		EditorSettings->LocalContentViewConfigs.Add(UBeamCurrencyContent::StaticClass(), CurrencyConfig);
		EditorSettings->LocalContentViewConfigs.Add(UBeamGameTypeContent::StaticClass(), GameTypeConfig);
		bEditorSettingsChanged = true;
	}

	if (bEditorSettingsChanged)
	{
		EditorSettings->SaveConfig(CPF_Config, *EditorSettings->GetDefaultConfigFilename());
	}
	
	const auto Subsystems = GEditor->GetEditorSubsystemArrayCopy<UBeamEditorSubsystem>();
	BeamEditor->InitializeAfterEditorReadyOps.Reset(Subsystems.Num());
	for (auto& Subsystem : Subsystems)
	{
		const auto Handle = Subsystem->InitializeWhenEditorReady();
		BeamEditor->InitializeAfterEditorReadyOps.Add(Handle);
	}

	const auto OnCompleteCode = FOnWaitCompleteCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditorBootstrapper, Run_TrySignIntoMainEditorSlot));
	BeamEditor->OnInitializedAfterEditorReadyWait = RequestTracker->CPP_WaitAll({}, BeamEditor->InitializeAfterEditorReadyOps, {}, OnCompleteCode);
}

void UBeamEditorBootstrapper::Run_TrySignIntoMainEditorSlot(FBeamWaitCompleteEvent Evt)
{
	const auto RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	TArray<FString> Errs;
	if (RequestTracker->IsWaitFailed(Evt, Errs))
	{
		for (FString Err : Errs)
		{
			UE_LOG(LogBeamEditor, Error, TEXT("Error initializing the Beamable SDK: %s"), *Err);
		}
		UE_LOG(LogBeamEditor, Error, TEXT("Please restart the editor to try again after fixing whatever issues the errors describe."));
		return;
	}

	// When the CLI is not installed, we DO NOT sign in the editor.
	// Instead, we just use the TargetRealm that is configured in the .ini file in this branch. 
	const auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	if (!Cli->IsInstalled())
	{
		// TODO: Check that the Target Realm is set, if not log a big error that says the target realm is not set and therefore no beamable feature will work at runtime.
		// Push out a notification that the CLI is not installed and therefore no beamable editor functionality will work (neither will local microservices).
		return;
	}

	const auto BeamEditor = GEditor->GetEditorSubsystem<UBeamEditor>();
	auto Op = RequestTracker->CPP_BeginOperation({}, BeamEditor->GetName(), FBeamOperationEventHandlerCode::CreateLambda([this, BeamEditor](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_ERROR)
		{
			BeamEditor->UpdateBeamableWindowMessage(TEXT("Auto sign in failed!"), EMessageType::VE_Error);

			// Clear the realm if any problems occur when automatically signing in using CLI data. 
			BeamEditor->SetActiveTargetRealmUnsafe(BeamEditor->Signed_Out_Realm_Handle);
			BeamEditor->UserSlots->ClearUserAtSlot(BeamEditor->GetMainEditorSlot(), USCR_FailedAuthentication, true);

			// Set the editor as ready
			BeamEditor->bEditorReady = true;
			return;
		}

		BeamEditor->UpdateBeamableWindowMessage(TEXT("Sign in successful!"), EMessageType::VE_Info);
		BeamEditor->bEditorReady = true;
	}));
	BeamEditor->SignInWithCliInfo(Op);
}


FUserSlot UBeamEditor::GetMainEditorSlot(FBeamRealmUser& UserData) const
{
	const auto MainSlot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	ensureAlwaysMsgf(UserSlots->GetUserDataAtSlot(MainSlot, UserData, nullptr),
	                 TEXT("No developer signed into the MainEditorDeveloper UserSlot! Please call UserSlot->SetAuthenticationData before this."));
	return MainSlot;
}

bool UBeamEditor::TryGetMainEditorSlot(FUserSlot& Slot, FBeamRealmUser& UserData)
{
	Slot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	return UserSlots->GetUserDataAtSlot(Slot, UserData, nullptr);
}

FUserSlot UBeamEditor::GetMainEditorSlot() const
{
	const auto MainSlot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	return MainSlot;
}

bool UBeamEditor::GetActiveProjectAndRealmData(FBeamCustomerProjectData& ProjectData, FBeamProjectRealmData& RealmData)
{
	ProjectData = CurrentProjectData;
	FUserSlot MainEditorSlot;
	FBeamRealmUser MainEditorDeveloper;
	if (TryGetMainEditorSlot(MainEditorSlot, MainEditorDeveloper))
	{
		for (const auto& R : CurrentProjectData.AllRealms)
		{
			if (R.PID.AsString == GetDefault<UBeamCoreSettings>()->TargetRealm.Pid.AsString)
			{
				RealmData = R;
				return true;
			}
		}
	}

	RealmData = FBeamProjectRealmData{};
	return false;
}

void UBeamEditor::SignOut()
{
	// When the CLI is not installed, we should not do anything. 
	const auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	if (!Cli->IsInstalled()) return;

	auto LogoutCmd = NewObject<UBeamCliLogoutCommand>();
	LogoutCmd->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			UserSlotClearedHandler = UserSlots->GlobalUserSlotClearedCodeHandler.AddUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, OnUserSlotCleared));
			UserSlots->ClearUserAtSlot(GetMainEditorSlot(), USCR_Manual, true);
		}
		else
		{
			// If we are not signed in, clear the target realm.
			UE_LOG(LogBeamEditor, Error, TEXT("Failed to sign out."))
			UpdateBeamableWindowMessage(TEXT("Failed to sign out."), EMessageType::VE_Error);
		}
	};
	Cli->RunCommandServer(LogoutCmd, {}, {});
}

void UBeamEditor::OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
{
	const auto SlotId = GetMainEditorSlot();
	if (Reason == USCR_Manual || Reason == USCR_FailedAuthentication)
	{
		if (UserSlot.Name.Equals(SlotId.Name))
		{
			// Remove the target realm configuration.
			SetActiveTargetRealmUnsafe(Signed_Out_Realm_Handle);

			// Invoke the sign out callback on all Editor Subsystems
			const auto Subsystems = GEditor->GetEditorSubsystemArrayCopy<UBeamEditorSubsystem>();
			for (auto& Subsystem : Subsystems)
			{
				Subsystem->OnSignOut();
			}

			// Clean up the callback.
			UserSlots->GlobalUserSlotClearedCodeHandler.Remove(UserSlotClearedHandler);
		}
	}
	else
	{
		if (UserSlot.Name.Equals(SlotId.Name))
		{
			UE_LOG(LogBeamEditor, Error, TEXT("You should not be seeing this. We should never log out of the editor if not for the two reasons in the above if-statement."))
		}
		else
		{
			UE_LOG(LogBeamEditor, Verbose, TEXT("Non-MainEditor UserSlot that was cleared so UBeamEditor doesn't care about it."))
		}
	}
}


FBeamOperationHandle UBeamEditor::SignInOperation(FString OrgName, FString Email, FString Password, const FBeamOperationEventHandler& OnOperationEvent)
{
	const auto Op = RequestTracker->BeginOperation({GetMainEditorSlot()}, GetName(), OnOperationEvent);
	SignIn(OrgName, Email, Password, Op);
	return Op;
}

FBeamOperationHandle UBeamEditor::CPP_SignInOperation(FString OrgName, FString Email, FString Password, const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	const auto Op = RequestTracker->CPP_BeginOperation({GetMainEditorSlot()}, GetName(), OnOperationEvent);
	SignIn(OrgName, Email, Password, Op);
	return Op;
}

FBeamOperationHandle UBeamEditor::SelectRealmOperation(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationEventHandler& OnOperationEvent)
{
	ensureAlwaysMsgf(!bIsRunningPIE, TEXT("Cannot change realm while in PIE!"));
	const auto Op = RequestTracker->BeginOperation({GetMainEditorSlot()}, GetName(), OnOperationEvent);
	SelectRealm(NewRealmHandle, Op);
	return Op;
}

FBeamOperationHandle UBeamEditor::CPP_SelectRealmOperation(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	ensureAlwaysMsgf(!bIsRunningPIE, TEXT("Cannot change realm while in PIE!"));
	const auto Op = RequestTracker->CPP_BeginOperation({GetMainEditorSlot()}, GetName(), OnOperationEvent);
	SelectRealm(NewRealmHandle, Op);
	return Op;
}

void UBeamEditor::SignIn(FString OrgName, FString Email, FString Password, const FBeamOperationHandle Op)
{
	// When the CLI is not installed, we should not do anything. 
	const auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	if (!Cli->IsInstalled())
	{
		RequestTracker->TriggerOperationError(Op, TEXT("Cli is not installed. Cannot sign into the Beamable Editor."));
		return;
	}

	// Stop all running CLI Commands so we can re-start it
	Cli->StopCli();

	// Call init with the proper parameters
	auto InitCommand = NewObject<UBeamCliInitCommand>();
	InitCommand->OnStreamOutput = [this](const TArray<UBeamCliInitStreamData*>& Stream, const TArray<long long>&, const FBeamOperationHandle&)
	{
		if (Stream.Num() > 0)
		{
			SetActiveTargetRealmUnsafe(FBeamRealmHandle{Stream[0]->Cid, Stream[0]->Pid});
		}
	};
	InitCommand->OnCompleted = [this, Op](const int& ResCode, const FBeamOperationHandle& CmdOp)
	{
		if (ResCode != 0)
		{
			UserSlots->ClearUserAtSlot(GetMainEditorSlot(), USCR_FailedAuthentication, true);
			SetActiveTargetRealmUnsafe(Signed_Out_Realm_Handle);
			RequestTracker->TriggerOperationError(CmdOp, TEXT("Failed to sign in."));
		}
		else
		{
			SignInWithCliInfo(Op);
		}
	};

	const auto Host = GEngine->GetEngineSubsystem<UBeamEnvironment>()->GetAPIUrl();
	Cli->RunCommand(InitCommand, {TEXT("--host"), Host, TEXT("-q"), TEXT("--cid"), OrgName, TEXT("--username"), Email, TEXT("--password"), Password}, Op);
}

void UBeamEditor::SignInWithCliInfo(const FBeamOperationHandle Op)
{
	// When the CLI is not installed, we should not do anything. 
	const auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	if (!Cli->IsInstalled())
	{
		FString ConfigJson;
		FString PathToConfigJson = FPaths::ProjectDir() / TEXT(".beamable") / TEXT("connection-configuration.json");
		if (FFileHelper::LoadFileToString(ConfigJson, *PathToConfigJson))
		{
			FJsonDataBag ConfigJsonBag;
			if (ConfigJsonBag.FromJson(ConfigJson))
			{
				const auto Cid = ConfigJsonBag.GetString(TEXT("cid"));
				const auto Pid = ConfigJsonBag.GetString(TEXT("pid"));

				GetMutableDefault<UBeamCoreSettings>()->TargetRealm.Cid.AsString = Cid;
				GetMutableDefault<UBeamCoreSettings>()->TargetRealm.Pid.AsString = Pid;
			}
			else
			{
				const auto Err = FString::Printf(
					TEXT("%s"),
					TEXT(
						"We found `.beamable/connection-configuration.json` file in your `.beamable` folder, but we couldn't parse it as JSON. When you don't have a CLI installed, you must have this file in your version control system so we know which realm you are targeting during PIE."));
				RequestTracker->TriggerOperationError(Op, Err);
			}
		}
		else
		{
			const auto Err = FString::Printf(
				TEXT("%s"),
				TEXT(
					"We did not find a `.beamable/connection-configuration.json` file in your `.beamable` folder. When you don't have a CLI installed, you must have this file in your version control system so we know which realm you are targeting during PIE."));
			RequestTracker->TriggerOperationError(Op, TEXT("Cli is not installed. Cannot sign into the Beamable Editor."));
		}

		return;
	}

	// Start the CLI server manually skipping the pre-warm 
	Cli->StartCliServer(true);

	// If the CLI is installed, we use it to get the data around the current organization
	const auto RealmsCommandOp = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	auto RealmsCommand = NewObject<UBeamCliOrgRealmsCommand>();
	RealmsCommand->OnStreamOutput = [this](const TArray<UBeamCliOrgRealmsStreamData*>& Stream, const TArray<long long>&, const FBeamOperationHandle&)
	{
		if (Stream.Num() > 0)
		{
			const auto Data = Stream[0];

			CurrentProjectData = {};
			CurrentProjectData.CustomerName = Data->CustomerAlias;
			CurrentProjectData.CustomerAlias = Data->CustomerAlias;

			TArray<FBeamProjectRealmData> RealmData = {};
			RealmData.Reserve(Data->VisibleRealms.Num());

			for (const auto R : Data->VisibleRealms)
			{
				FBeamProjectRealmData Realm;
				Realm.CID = R->Cid;
				Realm.PID = R->Pid;
				Realm.ParentPID = FOptionalBeamPid{R->ParentPid};
				Realm.ProjectName = R->ProjectName;
				Realm.RealmName = R->RealmName;
				Realm.RealmSecret = R->RealmSecret;
				Realm.bIsDev = R->IsDev;
				Realm.bIsStaging = R->IsStaging;
				Realm.bIsProduction = R->IsProduction;
				RealmData.Add(Realm);
			}
			CurrentProjectData.AllRealms = RealmData;
		}
	};
	RealmsCommand->OnCompleted = [this, RealmsCommandOp](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			RequestTracker->TriggerOperationError(RealmsCommandOp, TEXT("Failed to get realms data. Signing out. Please, ensure you are an developer or admin user and sign in again."));
		}
		else
		{
			RequestTracker->TriggerOperationSuccess(RealmsCommandOp, TEXT(""));
		}
	};
	Cli->RunCommandServer(RealmsCommand, {}, RealmsCommandOp);

	// If the CLI is installed, we use it to fetch the currently signed-in user and their realm.
	const auto MeCommandOp = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	auto MeCommand = NewObject<UBeamCliMeCommand>();
	MeCommand->OnStreamOutput = [this](const TArray<UBeamCliMeStreamData*>& Stream, const TArray<long long>&, const FBeamOperationHandle&)
	{
		if (Stream.Num() > 0)
		{
			const auto Data = Stream[0];

			// Get the editor slot
			const auto EditorSlot = GetMainEditorSlot();

			// Set the authentication data
			UserSlots->SetAuthenticationDataAtSlot(EditorSlot, Data->AccessToken, Data->RefreshToken, Data->TokenIssuedAt.ToUnixTimestamp(), Data->TokenExpiresIn,
			                                       FBeamCid{Data->TokenCid}, FBeamPid{Data->TokenPid}, this);
			// Set account id, email and gamertag
			UserSlots->SetAccountIdAtSlot(EditorSlot, FBeamAccountId{Data->Id}, this);
			UserSlots->SetEmailAtSlot(EditorSlot, Data->Email, this);
			UserSlots->SetGamerTagAtSlot(EditorSlot, {}, this);
			// Set external identities
			TArray<FBeamExternalIdentity> Identities;
			for (const auto External : Data->External)
			{
				FBeamExternalIdentity ExternalId;
				ExternalId.ProviderService = External->ProviderService;
				ExternalId.UserId = External->UserId;
				ExternalId.ProviderNamespace = External->ProviderNamespace;
				Identities.Add(ExternalId);
			}
			UserSlots->SetExternalIdsAtSlot(EditorSlot, Identities, this);
		}
	};
	MeCommand->OnCompleted = [this, MeCommandOp](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			RequestTracker->TriggerOperationError(MeCommandOp, TEXT("Failed to get data from signed in user. Signing out. Please sign in again."));
		}
		else
		{
			RequestTracker->TriggerOperationSuccess(MeCommandOp, TEXT(""));
		}
	};
	Cli->RunCommandServer(MeCommand, {}, MeCommandOp);

	// Wait for both commands to run and then set up the realm selection.
	RequestTracker->CPP_WaitAll({}, {RealmsCommandOp, MeCommandOp}, {}, FOnWaitCompleteCode::CreateLambda([this, Op](FBeamWaitCompleteEvent Evt)
	{
		TArray<FString> Errs;
		if (RequestTracker->IsWaitFailed(Evt, Errs))
		{
			RequestTracker->TriggerOperationError(Op, FString::Join(Errs, TEXT("\n")));
			return;
		}

		FBeamRealmUser EditorUser;
		UserSlots->GetUserDataAtSlot(GetMainEditorSlot(), EditorUser, this);
		SelectRealm(EditorUser.RealmHandle, Op);
	}));
}


void UBeamEditor::SelectRealm(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationHandle& Op)
{
	auto Message = NewObject<UBeamableWindowMessage>();
	Message->MessageType = EMessageType::VE_Info;
	Message->MessageValue = TEXT("Preparing to change Realms...");
	SetBeamableWindowMessage(Message);

	// Clear all PIE user slots
	UserSlots->DeleteUserSlotCacheForPIE();

	// Stops all running commands
	const auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	Cli->StopCli();

	auto Settings = GetMutableDefault<UBeamCoreSettings>();
	const auto LeavingRealm = Settings->TargetRealm;

	const auto Subsystems = GEditor->GetEditorSubsystemArrayCopy<UBeamEditorSubsystem>();
	PrepareForRealmChangeOps.Reset(Subsystems.Num());
	for (auto& Subsystem : Subsystems)
	{
		const auto Handle = Subsystem->PrepareForRealmChange(LeavingRealm, NewRealmHandle);
		PrepareForRealmChangeOps.Add(Handle);
	}
	const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamEditor::SelectRealm_OnReadyForChange, NewRealmHandle, Op);
	OnReadyForRealmChangeWait = RequestTracker->CPP_WaitAll({}, PrepareForRealmChangeOps, {}, OnCompleteCode);
}

void UBeamEditor::SelectRealm_OnReadyForChange(FBeamWaitCompleteEvent, FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op)
{
	auto Message = NewObject<UBeamableWindowMessage>();
	Message->MessageType = EMessageType::VE_Info;
	Message->MessageValue = TEXT("Changing Realms...");
	SetBeamableWindowMessage(Message);

	const auto ConfigSetCmd = NewObject<UBeamCliConfigCommand>();
	ConfigSetCmd->OnCompleted = [this, NewRealmHandle](const int& ResCode, const FBeamOperationHandle& CmdOp)
	{
		if (ResCode == 0)
		{
			// After the realm change we stop the CLI Server again so it gets re-started with the correctly set new CID/PID.
			const auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
			Cli->StopCli();

			// Make the Main Editor Slot and the editor itself point at the new realm	
			FBeamRealmUser UserData;
			const auto MainEditorSlot = GetMainEditorSlot(UserData);
			UserSlots->SetPIDAtSlot(MainEditorSlot, NewRealmHandle.Pid, this);
			SetActiveTargetRealmUnsafe(NewRealmHandle);

			// Sets the realm secret
			FBeamCustomerProjectData _;
			FBeamProjectRealmData RealmData;
			if (GetActiveProjectAndRealmData(_,RealmData))
			{
				GEngine->GetEngineSubsystem<UBeamBackend>()->RealmSecret = RealmData.RealmSecret;
			} 

			// Using the new Post endpoint that allows for Upsert to ensure that all Unreal games are using our custom notification pipeline instead of our legacy PubNub stuff.
			const auto UpdateConfigReq = UPostConfigRequest::Make(FOptionalArrayOfString{}, FOptionalMapOfString{{{TEXT("notification|publisher"), TEXT("beamable")}}}, GetTransientPackage(), {});
			const auto Handler = FOnPostConfigFullResponse::CreateLambda([this, CmdOp, NewRealmHandle](FPostConfigFullResponse PutResp)
			{
				if (PutResp.State == RS_Success)
				{
					const auto Subsystems = GEditor->GetEditorSubsystemArrayCopy<UBeamEditorSubsystem>();
					InitalizeFromRealmOps.Reset(Subsystems.Num());
					for (auto& Subsystem : Subsystems)
					{
						const auto Handle = Subsystem->InitializeRealm(NewRealmHandle);
						InitalizeFromRealmOps.Add(Handle);
					}
					const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamEditor::SelectRealm_OnRealmInitialized, NewRealmHandle, CmdOp);
					InitializeFromRealmsWait = RequestTracker->CPP_WaitAll({}, InitalizeFromRealmOps, {}, OnCompleteCode);
					return;
				}

				if (PutResp.State == RS_Retrying)
					return;

				RequestTracker->TriggerOperationError(CmdOp, PutResp.ErrorData.message);
			});
			FBeamRequestContext Ctx;
			GEngine->GetEngineSubsystem<UBeamRealmsApi>()->CPP_PostConfig(MainEditorSlot, UpdateConfigReq, Handler, Ctx, CmdOp, this);
		}
		else
		{
			RequestTracker->TriggerOperationError(CmdOp, FString::Printf(TEXT("CLI_ERROR. CODE=%d"), ResCode));
		}
	};

	// Invoke the "Set Local Config Override" command in the CLI with the new realm --- once its set, set the TargetRealm and the PID for the MainEditorUserSlot and only then continue making the get config request.
	const auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	const auto Params = TArray<FString>{TEXT("--cid"), NewRealmHandle.Cid.AsString, TEXT("--pid"), NewRealmHandle.Pid.AsString, TEXT("--set")};
	Cli->RunCommandServer(ConfigSetCmd, Params, Op);
}

void UBeamEditor::SelectRealm_OnRealmInitialized(FBeamWaitCompleteEvent, FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op)
{
	auto Message = NewObject<UBeamableWindowMessage>();
	Message->MessageType = EMessageType::VE_Info;
	Message->MessageValue = TEXT("Updating new Realm Local Data...");
	SetBeamableWindowMessage(Message);

	// Notify all systems that we have successfully initialized the realm
	const auto Subsystems = GEditor->GetEditorSubsystemArrayCopy<UBeamEditorSubsystem>();
	RealmInitializedOps.Reset(Subsystems.Num());
	for (auto& Subsystem : Subsystems)
	{
		const auto Handle = Subsystem->OnRealmInitialized(NewRealmHandle);
		RealmInitializedOps.Add(Handle);
	}
	const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamEditor::SelectRealm_OnSystemsReady, NewRealmHandle, Op);
	RealmInitializedWait = RequestTracker->CPP_WaitAll({}, RealmInitializedOps, {}, OnCompleteCode);
}

void UBeamEditor::SelectRealm_OnSystemsReady(FBeamWaitCompleteEvent, FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op)
{
	auto Message = NewObject<UBeamableWindowMessage>();
	Message->MessageType = EMessageType::VE_Info;
	Message->MessageValue = TEXT("Realm Changed!");
	SetBeamableWindowMessage(Message);

	const auto Subsystems = GEditor->GetEditorSubsystemArrayCopy<UBeamEditorSubsystem>();
	for (auto& Subsystem : Subsystems)
	{
		Subsystem->OnReady();
	}

	RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
}

void UBeamEditor::OpenPortalOnCurrentRealm()
{
	OpenPortal(EPortalPage::VE_Dashboard);
}

void UBeamEditor::OpenPortal(EPortalPage PortalPage)
{
	FUserSlot MainEditorSlot;
	FBeamRealmUser Data;
	if (TryGetMainEditorSlot(MainEditorSlot, Data))
	{
		FBeamCustomerProjectData Proj;
		FBeamProjectRealmData RealmData;
		GetActiveProjectAndRealmData(Proj, RealmData);

		const auto PortalUrl = GetDefault<UBeamCoreSettings>()->BeamableEnvironment->PortalUrl;
		const auto Cid = Data.RealmHandle.Cid.AsString;
		const auto ProductionPid = Proj.AllRealms.FindByPredicate([](FBeamProjectRealmData d) { return d.bIsProduction; })->PID.AsString;
		const auto CurrentPid = Data.RealmHandle.Pid.AsString;
		const auto RefreshToken = Data.AuthToken.RefreshToken;
		FString Page;
		TArray<FString> AdditionalQueryArgs = {};
		switch (PortalPage)
		{
		case EPortalPage::VE_Dashboard:
			Page = FString("dashboard");
			break;
		case EPortalPage::VE_Microservices:
			Page = FString("microservices");
			break;
		case EPortalPage::VE_PlayerSearch:
			Page = FString("players");
			break;
		case EPortalPage::VE_RealmConfig:
			Page = FString("realm-config");
			break;
		case EPortalPage::VE_Content:
			Page = FString("content");
			break;
		case EPortalPage::VE_Campaign:
			Page = FString("messaging");
			break;
		}

		const auto URL = FString::Format(TEXT("{0}/{1}/games/{2}/realms/{3}/{4}?refresh_token={5}{6}"),
		                                 {
			                                 PortalUrl,
			                                 Cid,
			                                 ProductionPid,
			                                 CurrentPid,
			                                 Page,
			                                 RefreshToken,
			                                 FString::Join(AdditionalQueryArgs, TEXT(""))
		                                 });

		FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);
	}
}

void UBeamEditor::SetActiveTargetRealmUnsafe(const FBeamRealmHandle& NewRealmHandle)
{
	auto Settings = GetMutableDefault<UBeamCoreSettings>();
	const auto LeavingRealm = Settings->TargetRealm;

	Settings->TargetRealm = NewRealmHandle;
	Settings->SaveConfig();
}

void UBeamEditor::ApplyCurrentSettingsToBuild()
{
	FBeamProjectRealmData RealmData;
	FBeamCustomerProjectData ProjectData;

	GetActiveProjectAndRealmData(ProjectData, RealmData);

	const auto ConfigSetCmd = NewObject<UBeamCliConfigCommand>();

	ConfigSetCmd->OnCompleted = [this, RealmData](const int& ResCode, const FBeamOperationHandle& CmdOp)
	{
		if (ResCode == 0)
		{
			// auto set = UEditorDialogLibrary::ShowMessage("Apply realm to build", "It will apply realm to build", EAppMsgType::YesNoCancel, "", EAppMsgCategory::Info);
			auto Settings = GetMutableDefault<UBeamCoreSettings>();
			Settings->TargetRealm = FBeamRealmHandle{
				RealmData.CID,
				RealmData.PID
			};
			Settings->TryUpdateDefaultConfigFile(*Settings->GetDefaultConfigFilename());

			// Notify other systems that
			if (OnAppliedSettingsToBuild.IsBound()) OnAppliedSettingsToBuild.Broadcast();
		}
		else
		{
			RequestTracker->TriggerOperationError(CmdOp, FString::Printf(TEXT("CLI_ERROR. CODE=%d"), ResCode));
		}
	};

	// Invoke the "Set Local Config Override" command in the CLI with the new realm
	const auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	const auto Params = TArray<FString>{TEXT("--cid"), RealmData.CID.AsString, TEXT("--pid"), RealmData.PID.AsString, TEXT("--set"), TEXT("--no-overrides")};
	Cli->RunCommandServer(ConfigSetCmd, Params, {});
}
