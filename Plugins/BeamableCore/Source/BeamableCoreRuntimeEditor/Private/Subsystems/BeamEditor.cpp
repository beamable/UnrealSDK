// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/BeamEditor.h"

#include "EditorUtilitySubsystem.h"
#include "AutoGen/Optionals/OptionalArrayOfBeamExternalIdentityLibrary.h"
#include "AutoGen/Optionals/OptionalStringLibrary.h"
#include "AutoGen/SubSystems/BeamAuthApi.h"
#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/BeamRealmsApi.h"

#include "Subsystems/BeamEditorSubsystem.h"

const FBeamRealmHandle UBeamEditor::Signed_Out_Realm_Handle = FBeamRealmHandle{TEXT(""), TEXT("")};

UBeamEditor* UBeamEditor::GetSelf(const UObject* CallingContext)
{
	return GEditor->GetEditorSubsystem<UBeamEditor>();
}

void UBeamEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("Initializing BeamEditor Subsystem!"));

	// Set us up to track whether or not we are running PIE
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

	// Sets up handlers for us to keep track of whether or not we are authenticated into the editor	
	MainEditorSlotIdx = 0;

	// Configure the bootstrapper to run so that the Init functions of BeamEditorSubsystems all get called after the editor environment is ready to go.
	const auto EditorUtilitySubsystem = Collection.InitializeDependency<UEditorUtilitySubsystem>();
	const auto DefaultBootstrapper = GetDefault<UBeamEditorBootstrapper>();
	const auto SoftPathToDefaultBoostrapper = FSoftObjectPath{DefaultBootstrapper->GetPathName()};
	if (!EditorUtilitySubsystem->StartupObjects.Contains(SoftPathToDefaultBoostrapper))
		EditorUtilitySubsystem->StartupObjects.Add(SoftPathToDefaultBoostrapper);	
}

void UBeamEditor::Deinitialize()
{
	UserSlots->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
	UserSlots->GlobalUserSlotClearedCodeHandler.Remove(UserSlotClearedHandler);
	FEditorDelegates::BeginPIE.Remove(BeginPIEHandler);
	FEditorDelegates::EndPIE.Remove(EndPIEHandler);
}

void UBeamEditorBootstrapper::Run()
{
	Run_DelayedInitialize();
}

void UBeamEditorBootstrapper::Run_DelayedInitialize()
{
	const auto RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	const auto BeamEditor = GEditor->GetEditorSubsystem<UBeamEditor>();

	/* INFO - Make sure our core settings and environment settings are correctly set up for our users.
	 * When this plugin gets added to the project, there are some default settings that we can pre-set for our users so that they don't have to do it.
	 * This is where we do that.
	 */
	auto CoreSettings = GetMutableDefault<UBeamCoreSettings>();
	if (CoreSettings->BeamableEnvironment.IsNull())
	{
		CoreSettings->BeamableEnvironment = FSoftObjectPath(TEXT("/Script/BeamableCore.BeamEnvironmentData'/BeamableCore/Environments/BeamProdEnv.BeamProdEnv'"));
		CoreSettings->SaveConfig(CPF_Config, *CoreSettings->GetDefaultConfigFilename());
	}

	auto EditorSettings = GetMutableDefault<UBeamEditorSettings>();
	if(EditorSettings->BeamableMainWindow.IsNull())
	{
		EditorSettings->BeamableMainWindow = FSoftObjectPath(TEXT("/Script/Blutility.EditorUtilityWidgetBlueprint'/BeamableCore/Editor/EWBP_BeamableWindow.EWBP_BeamableWindow'"));
		EditorSettings->SaveConfig(CPF_Config, *EditorSettings->GetDefaultConfigFilename());
	}

	const auto Subsystems = GEditor->GetEditorSubsystemArray<UBeamEditorSubsystem>();
	BeamEditor->InitializeAfterEditorReadyOps.Reset(Subsystems.Num());
	for (auto& Subsystem : Subsystems)
	{
		const auto Handle = Subsystem->InitializeWhenEditorReady();
		BeamEditor->InitializeAfterEditorReadyOps.Add(Handle);
	}

	BeamEditor->OnInitializedAfterEditorReadyChange = FOnWaitCompleteCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditorBootstrapper, Run_TrySignIntoMainEditorSlot));
	BeamEditor->OnInitializedAfterEditorReadyWait = RequestTracker->CPP_WaitAll({}, BeamEditor->InitializeAfterEditorReadyOps, {}, BeamEditor->OnInitializedAfterEditorReadyChange);
}

void UBeamEditorBootstrapper::Run_TrySignIntoMainEditorSlot()
{
	const auto BeamEditor = GEditor->GetEditorSubsystem<UBeamEditor>();
	const auto MainEditorSlot = BeamEditor->GetMainEditorSlot();
	// Tries to load the saved user at a specific slot.
	if (BeamEditor->UserSlots->TryLoadSavedUserAtSlot(MainEditorSlot, this))
	{
		FBeamRealmUser User;

		const auto _ = BeamEditor->GetMainEditorSlot(User);
		FBeamOperationEventHandler OperationEventHandler;
		OperationEventHandler.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditorBootstrapper, Run_EditorReady));
		const auto Op = BeamEditor->RequestTracker->BeginOperation({MainEditorSlot}, GetName(), OperationEventHandler);
		BeamEditor->UpdateSignedInUserData_OnUserSlotAuthenticated(MainEditorSlot, User, this, Op);
	}
	else
	{
		// If we are not signed in, clear the target realm.
		UE_LOG(LogBeamEditor, Display, TEXT("Not signed in so clearing target realm!"))

		BeamEditor->SetActiveTargetRealmUnsafe({});
		TArray<FUserSlot> SlotsStub;
		Run_EditorReady(SlotsStub, {});
	}
}

void UBeamEditorBootstrapper::Run_EditorReady(TArray<FUserSlot>& UserSlots, FBeamOperationEvent OperationEvent)
{
	const auto BeamEditor = GEditor->GetEditorSubsystem<UBeamEditor>();
	BeamEditor->bEditorReady = true;
}


FUserSlot UBeamEditor::GetMainEditorSlot(FBeamRealmUser& UserData) const
{
	const auto MainSlot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	ensureAlwaysMsgf(UserSlots->GetUserDataAtSlot(MainSlot, UserData), TEXT("No developer signed into the MainEditorDeveloper UserSlot! Please call UserSlot->SetAuthenticationData before this."));
	return MainSlot;
}

bool UBeamEditor::TryGetMainEditorSlot(FUserSlot& Slot, FBeamRealmUser& UserData)
{
	Slot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	return UserSlots->GetUserDataAtSlot(Slot, UserData);;
}

FUserSlot UBeamEditor::GetMainEditorSlot() const
{
	FBeamRealmUser UserData;
	const auto MainSlot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	UserSlots->GetUserDataAtSlot(MainSlot, UserData);
	return MainSlot;
}

bool UBeamEditor::GetActiveProjectAndRealmData(FBeamCustomerProjectData& ProjectData, FBeamProjectRealmData& RealmData)
{
	const auto EditorSettings = GetDefault<UBeamEditorSettings>();

	FUserSlot MainEditorSlot;
	FBeamRealmUser MainEditorDeveloper;
	if (TryGetMainEditorSlot(MainEditorSlot, MainEditorDeveloper))
	{
		if (const auto ProjectDataPtr = EditorSettings->PerSlotDeveloperProjectData.Find(MainEditorSlot.Name))
		{
			ProjectData = *ProjectDataPtr;

			const auto FoundData = ProjectData.AllRealms.FindByPredicate([MainEditorDeveloper](FBeamProjectRealmData d) { return d.PID == MainEditorDeveloper.RealmHandle.Pid; });
			ensureAlwaysMsgf(FoundData, TEXT("No developer signed into the MainEditorDeveloper UserSlot! Please sign-in."));

			if (FoundData)
				RealmData = *FoundData;
			return true;
		}
	}

	RealmData = FBeamProjectRealmData{};
	return false;
}

void UBeamEditor::SignOut()
{
	UserSlotClearedHandler = UserSlots->GlobalUserSlotClearedCodeHandler.AddUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, OnUserSlotCleared));
	UserSlots->ClearUserAtSlot(GetMainEditorSlot(), Manual, true);
}

void UBeamEditor::OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
{
	const auto SlotId = GetMainEditorSlot();
	if (Reason == Manual || Reason == FailedAuthentication)
	{
		if (UserSlot.Name.Equals(SlotId.Name))
		{
			// Remove the target realm configuration.
			SetActiveTargetRealmUnsafe(Signed_Out_Realm_Handle);

			// Clear project data associated with that slot.
			const auto EditorConfig = GetMutableDefault<UBeamEditorSettings>();
			EditorConfig->PerSlotDeveloperProjectData.Remove(SlotId.Name);

			// Invoke the sign out callback on all Editor Subsystems
			const auto Subsystems = GEditor->GetEditorSubsystemArray<UBeamEditorSubsystem>();
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

FBeamOperationHandle UBeamEditor::SignUpOperation(FString ProjectName, FString OrgName, FString Email, FString Password, FString Alias, const FBeamOperationEventHandler& OnOperationEvent)
{
	ensureAlwaysMsgf(!bIsRunningPIE, TEXT("Cannot change realm while in PIE!"));
	const auto Op = RequestTracker->BeginOperation({GetMainEditorSlot()}, GetName(), OnOperationEvent);
	SignUp(ProjectName, OrgName, Email, Password, Alias, Op);
	return Op;
}

FBeamOperationHandle UBeamEditor::CPP_SignUpOperation(FString ProjectName, FString OrgName, FString Email, FString Password, FString Alias, const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	ensureAlwaysMsgf(!bIsRunningPIE, TEXT("Cannot change realm while in PIE!"));
	const auto Op = RequestTracker->CPP_BeginOperation({GetMainEditorSlot()}, GetName(), OnOperationEvent);
	SignUp(ProjectName, OrgName, Email, Password, Alias, Op);
	return Op;
}

void UBeamEditor::SignUp(FString ProjectName, FString OrgName, FString Email, FString Password, FString Alias, const FBeamOperationHandle Op)
{
	const auto RealmsApi = GEngine->GetEngineSubsystem<UBeamRealmsApi>();

	const auto PostCustomerRequest = UPostCustomerRequest::Make(ProjectName, Email, Password, {}, FOptionalString{OrgName}, FOptionalString{Alias}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	const auto Handler = FOnPostCustomerFullResponse::CreateUObject(this, &UBeamEditor::SignUp_OnPostCustomer, Op, OrgName, Email, Password);
	RealmsApi->CPP_PostCustomer(PostCustomerRequest, Handler, Ctx, Op, this);
}

void UBeamEditor::SignUp_OnPostCustomer(const FPostCustomerFullResponse Response, const FBeamOperationHandle Op, const FString OrgName, const FString Email, const FString Password)
{
	if (Response.State == RS_Error)
	{
		FString Error;
		FJsonObjectConverter::UStructToJsonObjectString(Response.ErrorData, Error);
		RequestTracker->TriggerOperationError(Op, Error, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		SignIn(OrgName, Email, Password, Op);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditor::SignIn(FString OrgName, FString Email, FString Password, const FBeamOperationHandle Op)
{
	const auto RealmsApi = GEngine->GetEngineSubsystem<UBeamRealmsApi>();

	const auto CustomerAliasReq = UGetCustomerAliasAvailableRequest::Make(OrgName, GetTransientPackage(), {});
	CustomerAliasReq->Alias = OrgName;

	FBeamRequestContext Ctx;
	const auto Handler = FOnGetCustomerAliasAvailableFullResponse::CreateUObject(this, &UBeamEditor::SignIn_OnGetCustomerAliasAvailable, Op, Email, Password);
	RealmsApi->CPP_GetCustomerAliasAvailable(CustomerAliasReq, Handler, Ctx, Op, this);
}

void UBeamEditor::SignIn_OnGetCustomerAliasAvailable(const FGetCustomerAliasAvailableFullResponse Response, const FBeamOperationHandle Op, const FString Email, const FString Password)
{
	if (Response.State == RS_Error)
	{
		FString Error;
		FJsonObjectConverter::UStructToJsonObjectString(Response.ErrorData, Error);
		RequestTracker->TriggerOperationError(Op, Error, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		// If no CID was found for this alias... let the user know.
		if (!Response.SuccessData->bAvailable)
		{
			RequestTracker->TriggerOperationError(Op, TEXT("Organization not found. If you haven't created an account yet, please Sign Up instead."), Response.Context.RequestId);
			return;
		}

		// Update the target realm with just the CID and let the caller respond to this event.
		const auto Cid = Response.SuccessData->Cid;
		SetActiveTargetRealmUnsafe(FBeamRealmHandle{Cid});

		// Call authenticate with the rest of the information
		const auto AuthApi = GEngine->GetEngineSubsystem<UBeamAuthApi>();
		const auto AuthReq = NewObject<UAuthenticateRequest>();
		AuthReq->Body = NewObject<UTokenRequestWrapper>(AuthReq);
		AuthReq->Body->GrantType = TEXT("password");
		AuthReq->Body->bCustomerScoped = FOptionalBool(true);
		AuthReq->Body->Username = FOptionalString(Email);
		AuthReq->Body->Password = FOptionalString(Password);

		FBeamRequestContext AuthCtx;
		const auto Handler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamEditor::SignIn_OnAuthenticate, Op, Cid);
		AuthApi->CPP_Authenticate(AuthReq, Handler, AuthCtx, Op, this);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditor::SignIn_OnAuthenticate(const FAuthenticateFullResponse Response, const FBeamOperationHandle Op, const FBeamCid Cid)
{
	if (Response.State == RS_Error)
	{
		FString Error;
		FJsonObjectConverter::UStructToJsonObjectString(Response.ErrorData, Error);
		RequestTracker->TriggerOperationError(Op, Error, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		const auto AccessToken = Response.SuccessData->AccessToken.Val;
		const auto RefreshToken = Response.SuccessData->RefreshToken.Val;
		const auto ExpiresIn = Response.SuccessData->ExpiresIn;

		UpdateSignedInUserData(Op, Cid, AccessToken, RefreshToken, ExpiresIn);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}


void UBeamEditor::SelectRealm(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationHandle& Op)
{
	auto Settings = GetMutableDefault<UBeamCoreSettings>();
	const auto LeavingRealm = Settings->TargetRealm;

	const auto Subsystems = GEditor->GetEditorSubsystemArray<UBeamEditorSubsystem>();
	PrepareForRealmChangeOps.Reset(Subsystems.Num());
	for (auto& Subsystem : Subsystems)
	{
		const auto Handle = Subsystem->PrepareForRealmChange(LeavingRealm, NewRealmHandle);
		PrepareForRealmChangeOps.Add(Handle);
	}
	OnReadyForRealmChange = FOnWaitCompleteCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, SelectRealm_OnReadyForChange), NewRealmHandle, Op);
	OnReadyForRealmChangeWait = RequestTracker->CPP_WaitAll({}, PrepareForRealmChangeOps, {}, OnReadyForRealmChange);
}

void UBeamEditor::SelectRealm_OnReadyForChange(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
                                               const TArray<FBeamErrorResponse>&, FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op)
{
	// TODO: Expose error handling for BeamErrorResponses that happen in the PrepareRealmChange operations
	SetActiveTargetRealmUnsafe(NewRealmHandle);

	const auto Subsystems = GEditor->GetEditorSubsystemArray<UBeamEditorSubsystem>();

	InitalizeFromRealmOps.Reset(Subsystems.Num());
	for (auto& Subsystem : Subsystems)
	{
		const auto Handle = Subsystem->InitializeFromRealm(NewRealmHandle);
		InitalizeFromRealmOps.Add(Handle);
	}
	InitializedFromRealmHandler = FOnWaitCompleteCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, SelectRealm_OnSystemsReady), NewRealmHandle, Op);
	InitializeFromRealmsWait = RequestTracker->CPP_WaitAll({}, InitalizeFromRealmOps, {}, InitializedFromRealmHandler);
}

void UBeamEditor::SelectRealm_OnSystemsReady(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&,
                                             FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op) const
{
	// TODO: Expose error handling for BeamErrorResponses that happen in the InitializeFromRealm operations

	// We update the UserSlot info with the new PID.
	FBeamRealmUser UserData;
	const auto MainEditorSlot = GetMainEditorSlot(UserData);

	// Update the PID and change the slot
	UserSlots->SetPIDAtSlot(MainEditorSlot, NewRealmHandle.Pid, this);
	UserSlots->SaveSlot(MainEditorSlot, this);

	const auto Subsystems = GEditor->GetEditorSubsystemArray<UBeamEditorSubsystem>();
	for (auto& Subsystem : Subsystems)
	{
		Subsystem->OnRealmInitialized();
	}

	RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
}

void UBeamEditor::OpenPortalOnCurrentRealm()
{		
	FUserSlot      MainEditorSlot;
	FBeamRealmUser Data;
	if(TryGetMainEditorSlot(MainEditorSlot, Data))
	{
		FBeamCustomerProjectData Proj;
		FBeamProjectRealmData    RealmData;
		GetActiveProjectAndRealmData(Proj, RealmData);
			
		const auto PortalUrl = GetDefault<UBeamCoreSettings>()->BeamableEnvironment->PortalUrl;
		const auto Cid = Data.RealmHandle.Cid.AsString;
		const auto ProductionPid = Proj.AllRealms.FindByPredicate([](FBeamProjectRealmData d) { return !d.ParentPID.IsSet; })->PID.AsString; 
		const auto CurrentPid = Data.RealmHandle.Pid.AsString;
		const auto RefreshToken = Data.AuthToken.RefreshToken;
			
		const auto URL = FString::Format(TEXT("{0}/{1}/games/{2}/realms/{3}/dashboard?refresh_token={4}"),
		                                 { PortalUrl, Cid, ProductionPid, CurrentPid, RefreshToken });

		FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);
	}
}


void UBeamEditor::CacheProjectDataForUserSlot(FUserSlot UserSlot, UCustomerViewResponse* CustomerViewResponse) const
{
	// Gets all project data for the requesting user slot.				
	FBeamCustomerProjectData ProjectData;

	const auto CID = CustomerViewResponse->Customer->Cid;
	const auto CustomerName = ProjectData.CustomerName = CustomerViewResponse->Customer->Name;

	bool _;
	const auto CustomerAlias = ProjectData.CustomerAlias = UOptionalStringLibrary::GetOptionalValue(CustomerViewResponse->Customer->Alias, CustomerName, _);

	// Find the project with 0 children and get the project name from it...
	FString ProjectName;

	const auto RealmList = CustomerViewResponse->Customer->Projects;
	for (const auto& ProjectView : RealmList)
	{
		const auto PID = ProjectView->Pid;
		const auto ParentPid = ProjectView->Parent;
		const auto RealmName = ProjectView->ProjectName;
		const auto RealmSecret = ProjectView->Secret.Val;

		const auto IsRoot = !ProjectView->Parent.IsSet;

		FString ProjName, Discarded;
		if (IsRoot && RealmName.Split("-", &ProjName, &Discarded))
			ProjectName = ProjName;

		ProjectData.AllRealms.Add(FBeamProjectRealmData{CID, PID, ParentPid, ProjectName, RealmName, RealmSecret});
	}

	// Now that we've found the root project and it's name, let's update that data in each struct there.
	for (auto& Realm : ProjectData.AllRealms)
		Realm.ProjectName = ProjectName;


	// Finally, let's update the Editor/BP readonly data in the Editor Config for this slot.
	const auto SlotName = UserSlot.Name;
	auto EditorConfig = GetMutableDefault<UBeamEditorSettings>();
	if (EditorConfig->PerSlotDeveloperProjectData.Contains(SlotName))
	{
		EditorConfig->PerSlotDeveloperProjectData[SlotName] = ProjectData;
	}
	else
	{
		EditorConfig->PerSlotDeveloperProjectData.Add(SlotName, ProjectData);
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
	auto Settings = GetMutableDefault<UBeamCoreSettings>();
	Settings->SaveConfig(CPF_Config, *Settings->GetDefaultConfigFilename());
}


void UBeamEditor::UpdateSignedInUserData(const FBeamOperationHandle Op, const FBeamCid Cid, const FString AccessToken, const FString RefreshToken, const int64 ExpiresIn)
{
	const FBeamPid Pid{};
	UserSlots->SetAuthenticationDataAtSlot(GetMainEditorSlot(), AccessToken, RefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), ExpiresIn, Cid, Pid, this);

	const auto RealmsApi = GEngine->GetEngineSubsystem<UBeamRealmsApi>();
	const auto Req = UGetGamesRequest::Make(GetTransientPackage(), {});
	const auto Handler = FOnGetGamesFullResponse::CreateUObject(this, &UBeamEditor::UpdateSignedInUserData_OnGetRealms, Op, Cid);

	FBeamRequestContext Ctx;
	RealmsApi->CPP_GetGames(GetMainEditorSlot(), Req, Handler, Ctx, Op, this);
}

void UBeamEditor::UpdateSignedInUserData_OnGetRealms(const FGetGamesFullResponse Response, const FBeamOperationHandle Op, const FBeamCid Cid)
{
	if (Response.State == RS_Error)
	{
		FString Error;
		FJsonObjectConverter::UStructToJsonObjectString(Response.ErrorData, Error);
		RequestTracker->TriggerOperationError(Op, Error, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		const auto Games = Response.SuccessData->Projects;
		// If we only have 1 project (Root PID) associated with this customer, we sign in automatically.				
		if (Games.Num() > 0)
		{
			// We change the editor developer realm automatically to the default Root PID. 
			const auto Pid = Games[0]->Pid;
			SetActiveTargetRealmUnsafe(FBeamRealmHandle{Cid, Pid});


			UserSlots->SetPIDAtSlot(GetMainEditorSlot(), Pid);

			// Now, we need to get the admin me data so we can know all the projects/realms associated with this CID
			const auto AccountApi = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
			const auto Req = UGetAdminMeRequest::Make(GetTransientPackage(), {});
			const auto Handler = FOnGetAdminMeFullResponse::CreateUObject(this, &UBeamEditor::UpdateSignedInUserData_OnGetAdminMe, Op);

			FBeamRequestContext Ctx;
			AccountApi->CPP_GetAdminMe(GetMainEditorSlot(), Req, Handler, Ctx, Op, this);
		}
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditor::UpdateSignedInUserData_OnGetAdminMe(const FBeamFullResponse<UGetAdminMeRequest*, UAccountPortalView*> Response, const FBeamOperationHandle Op)
{
	if (Response.State == RS_Error)
	{
		FString Error;
		FJsonObjectConverter::UStructToJsonObjectString(Response.ErrorData, Error);
		RequestTracker->TriggerOperationError(Op, Error, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		const auto AccountId = Response.SuccessData->Id;
		bool HadEmail = false;
		const auto Email = UOptionalStringLibrary::GetOptionalValue(Response.SuccessData->Email, TEXT(""), HadEmail);
		bool HadExternalIds = false;
		const auto ExternalIds = UOptionalArrayOfBeamExternalIdentityLibrary::GetOptionalValue(Response.SuccessData->External, {}, HadExternalIds);

		const auto Slot = GetMainEditorSlot();
		UserSlots->SetEmailAtSlot(Slot, Email, this);
		UserSlots->SetAccountIdAtSlot(Slot, AccountId, this);
		UserSlots->SetExternalIdsAtSlot(Slot, ExternalIds, this);

		UserSlots->SaveSlot(Slot, this);

		// Set up a handler for the UserSlot Authentication callback --- pass in the operation handle here so that we can treat this callback as part of the operation. 
		UserSlotAuthenticatedHandler = UserSlots->GlobalUserSlotAuthenticatedCodeHandler
		                                        .AddUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, UpdateSignedInUserData_OnUserSlotAuthenticated), Op);

		// Triggers the authentication callbacks.
		UserSlots->TriggerUserAuthenticatedIntoSlot(Slot, this);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditor::UpdateSignedInUserData_OnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context, const FBeamOperationHandle Op)
{
	// If we authenticated into a developer slot, let's gather the customer and project data for that user slot and store it.
	const auto MainEditorSlot = GetMainEditorSlot();
	if (UserSlot.Name.Equals(MainEditorSlot.Name))
	{
		const auto GetCustomerRequest = UGetCustomerRequest::Make(GetTransientPackage(), {});
		const auto GetCustomerHandler = FOnGetCustomerFullResponse::CreateUObject(this, &UBeamEditor::UpdateSignedInUserData_OnFetchProjectDataForSlot, Op);
		FBeamRequestContext RequestContext;
		GEngine->GetEngineSubsystem<UBeamRealmsApi>()->CPP_GetCustomer(MainEditorSlot, GetCustomerRequest, GetCustomerHandler, RequestContext, Op);
	}
}

void UBeamEditor::UpdateSignedInUserData_OnFetchProjectDataForSlot(FGetCustomerFullResponse Response, FBeamOperationHandle Op)
{
	FBeamRealmUser MainEditorUserData;
	const auto UserSlot = GetMainEditorSlot(MainEditorUserData);
	switch (Response.State)
	{
	case RS_Success:
		{
			// Update the ProjectData for this user slot
			CacheProjectDataForUserSlot(UserSlot, Response.SuccessData);

			// Change the target realm to this new one.
			const auto Handler = FBeamOperationEventHandlerCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, UpdateSignedInUserData_OnRealmSelected), Op);
			CPP_SelectRealmOperation(MainEditorUserData.RealmHandle, Handler);

			break;
		}
	case RS_Error:
		{
			SignOut();
			break;
		}
	case RS_Cancelled: break;
	case RS_Retrying: break;
	default: ;
	}
}

void UBeamEditor::UpdateSignedInUserData_OnRealmSelected(const TArray<FUserSlot>&, FBeamOperationEvent, FBeamOperationHandle SignInOperation) const
{
	// If we are the main editor developer, we now have everything we need to create the editor flows.
	RequestTracker->TriggerOperationSuccess(SignInOperation, TEXT(""));

	// Remove the handler we set up as to avoid complications.
	UserSlots->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
}
