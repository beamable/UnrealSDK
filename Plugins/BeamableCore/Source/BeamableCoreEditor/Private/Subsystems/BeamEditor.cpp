// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/BeamEditor.h"

#include "EditorUtilitySubsystem.h"
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
	GEditor->GetEditorWorldContext().World()->GetTimerManager().SetTimerForNextTick(this, &UBeamEditorBootstrapper::Run_DelayedInitialize);
}

void UBeamEditorBootstrapper::Run_DelayedInitialize()
{
	const auto RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	const auto BeamEditor = GEditor->GetEditorSubsystem<UBeamEditor>();

	auto Settings = GetMutableDefault<UBeamCoreSettings>();
	const auto LeavingRealm = Settings->TargetRealm;

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
		const auto Op = BeamEditor->RequestTracker->BeginOperation({MainEditorSlot}, GetName(), {});
		BeamEditor->SignIn_OnUserSlotAuthenticated(MainEditorSlot, User, this, Op);
	}
}


FUserSlot UBeamEditor::GetMainEditorSlot(FBeamRealmUser& UserData) const
{
	const auto MainSlot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	ensureAlwaysMsgf(UserSlots->GetUserDataAtSlot(MainSlot, UserData), TEXT("No developer signed into the MainEditorDeveloper UserSlot! Please call UserSlot->SetAuthenticationData before this."));
	return MainSlot;
}

FUserSlot UBeamEditor::GetMainEditorSlot() const
{
	FBeamRealmUser UserData;
	const auto MainSlot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	UserSlots->GetUserDataAtSlot(MainSlot, UserData);
	return MainSlot;
}

FBeamOperationHandle UBeamEditor::SignIn(FString OrgName, FString Email, FString Password, const FBeamOperationEventHandler& OnOperationEvent)
{
	const auto Op = RequestTracker->BeginOperation({GetMainEditorSlot()}, GetName(), OnOperationEvent);

	const auto RealmsApi = GEngine->GetEngineSubsystem<UBeamRealmsApi>();

	const auto CustomerAliasReq = UGetCustomerAliasAvailableRequest::Make(OrgName, GetTransientPackage());
	CustomerAliasReq->Alias = OrgName;

	FBeamRequestContext Ctx;
	const auto Handler = FOnGetCustomerAliasAvailableFullResponse::CreateUObject(this, &UBeamEditor::SignIn_OnGetCustomerAliasAvailable, Op, Email, Password);
	RealmsApi->CPP_GetCustomerAliasAvailable(CustomerAliasReq, Handler, Ctx, Op, this);

	return Op;
}

void UBeamEditor::SignIn_OnGetCustomerAliasAvailable(const FGetCustomerAliasAvailableFullResponse Response, const FBeamOperationHandle Op, const FString Email, const FString Password)
{
	if (Response.State == Error)
	{
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
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
	if (Response.State == Error)
	{
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
	{
		const auto AccessToken = Response.SuccessData->AccessToken.Val;
		const auto RefreshToken = Response.SuccessData->RefreshToken.Val;
		const auto ExpiresIn = Response.SuccessData->ExpiresIn;

		const FBeamPid Pid{};
		UserSlots->SetAuthenticationDataAtSlot(GetMainEditorSlot(), AccessToken, RefreshToken, ExpiresIn, Cid, Pid, this);

		const auto RealmsApi = GEngine->GetEngineSubsystem<UBeamRealmsApi>();
		const auto Req = UGetGamesRequest::Make(GetTransientPackage());
		const auto Handler = FOnGetGamesFullResponse::CreateUObject(this, &UBeamEditor::SignIn_OnGetRealms, Op, Cid);

		FBeamRequestContext Ctx;
		RealmsApi->CPP_GetGames(GetMainEditorSlot(), Req, Handler, Ctx, Op, this);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditor::SignIn_OnGetRealms(const FGetGamesFullResponse Response, const FBeamOperationHandle Op, const FBeamCid Cid)
{
	if (Response.State == Error)
	{
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
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
			const auto Req = UGetAdminMeRequest::Make(GetTransientPackage());
			const auto Handler = FOnGetAdminMeFullResponse::CreateUObject(this, &UBeamEditor::SignIn_OnGetAdminMe, Op);

			FBeamRequestContext Ctx;
			AccountApi->CPP_GetAdminMe(GetMainEditorSlot(), Req, Handler, Ctx, Op, this);
		}
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditor::SignIn_OnGetAdminMe(const FBeamFullResponse<UGetAdminMeRequest*, UAccountPortalView*> Response, const FBeamOperationHandle Op)
{
	if (Response.State == Error)
	{
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
	{
		const auto AccountId = Response.SuccessData->Id;
		bool HadEmail = false;
		const auto Email = UOptionalStringLibrary::GetOptionalValue(Response.SuccessData->Email, TEXT(""), HadEmail);

		const auto Slot = GetMainEditorSlot();
		UserSlots->SetEmailAtSlot(Slot, Email, this);
		UserSlots->SetAccountIdAtSlot(Slot, AccountId, this);

		UserSlots->SaveSlot(Slot, this);

		// Set up a handler for the UserSlot Authentication callback --- pass in the operation handle here so that we can treat this callback as part of the operation. 
		UserSlotAuthenticatedHandler = UserSlots->GlobalUserSlotAuthenticatedCodeHandler
		                                        .AddUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, SignIn_OnUserSlotAuthenticated), Op);

		// Triggers the authentication callbacks.
		UserSlots->TriggerUserAuthenticatedIntoSlot(Slot, this);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditor::SignIn_OnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context, const FBeamOperationHandle Op)
{
	// If we authenticated into a developer slot, let's gather the customer and project data for that user slot and store it.
	const auto MainEditorSlot = GetMainEditorSlot();
	if (UserSlot.Name.Equals(MainEditorSlot.Name))
	{
		const auto GetCustomerRequest = UGetCustomerRequest::Make(GetTransientPackage());
		const auto GetCustomerHandler = FOnGetCustomerFullResponse::CreateUObject(this, &UBeamEditor::SignIn_OnFetchProjectDataForSlot, Op);
		FBeamRequestContext RequestContext;
		GEngine->GetEngineSubsystem<UBeamRealmsApi>()->CPP_GetCustomer(MainEditorSlot, GetCustomerRequest, GetCustomerHandler, RequestContext, Op);
	}
}


void UBeamEditor::SignIn_OnFetchProjectDataForSlot(FGetCustomerFullResponse Response, FBeamOperationHandle Op)
{
	FBeamRealmUser MainEditorUserData;
	const auto UserSlot = GetMainEditorSlot(MainEditorUserData);
	switch (Response.State)
	{
	case Success:
		{
			// Update the ProjectData for this user slot
			CacheProjectDataForUserSlot(UserSlot, Response.SuccessData);

			// Change the target realm to this new one.
			SelectRealm(MainEditorUserData.RealmHandle, {});

			// If we are the main editor developer, we now have everything we need to create the editor flows.
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""), Response.Context.RequestId);

			// Remove the handler we set up as to avoid complications.
			UserSlots->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
			break;
		}
	case Error:
		{
			SignOut();
			break;
		}
	case Cancelled: break;
	case Retrying: break;
	default: ;
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


bool UBeamEditor::GetActiveProjectAndRealmData(FBeamCustomerProjectData& ProjectData, FBeamProjectRealmData& RealmData)
{
	const auto EditorSettings = GetDefault<UBeamEditorSettings>();

	FBeamRealmUser MainEditorDeveloper;
	const auto MainEditorSlot = GetMainEditorSlot(MainEditorDeveloper);

	if (const auto ProjectDataPtr = EditorSettings->PerSlotDeveloperProjectData.Find(MainEditorSlot.Name))
	{
		ProjectData = *ProjectDataPtr;

		const auto FoundData = ProjectData.AllRealms.FindByPredicate([MainEditorDeveloper](FBeamProjectRealmData d) { return d.PID == MainEditorDeveloper.RealmHandle.Pid; });
		ensureAlwaysMsgf(FoundData, TEXT("No developer signed into the MainEditorDeveloper UserSlot! Please sign-in."));

		if (FoundData)
			RealmData = *FoundData;
		return true;
	}

	RealmData = FBeamProjectRealmData{};
	return false;
}

void UBeamEditor::SetActiveTargetRealmUnsafe(const FBeamRealmHandle& NewRealmHandle) const
{
	auto Settings = GetMutableDefault<UBeamCoreSettings>();
	const auto LeavingRealm = Settings->TargetRealm;

	Settings->TargetRealm = NewRealmHandle;
	Settings->SaveConfig();
}

FBeamOperationHandle UBeamEditor::SelectRealm(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationEventHandler& OnOperationEvent)
{
	ensureAlwaysMsgf(!bIsRunningPIE, TEXT("Cannot change realm while in PIE!"));

	const auto Op = RequestTracker->BeginOperation({GetMainEditorSlot()}, GetName(), OnOperationEvent);

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

	return Op;
}

void UBeamEditor::SelectRealm_OnReadyForChange(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
                                               const TArray<FBeamErrorResponse>&, FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op)
{
	auto Settings = GetMutableDefault<UBeamCoreSettings>();

	Settings->TargetRealm = NewRealmHandle;
	Settings->SaveConfig();

	const auto Subsystems = GEditor->GetEditorSubsystemArray<UBeamEditorSubsystem>();

	InitalizeFromRealmOps.Reset(Subsystems.Num());
	for (auto& Subsystem : Subsystems)
	{
		const auto Handle = Subsystem->InitializeFromRealm(Settings->TargetRealm);
		InitalizeFromRealmOps.Add(Handle);
	}
	InitializedFromRealmHandler = FOnWaitCompleteCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, SelectRealm_OnSystemsReady), Op);
	InitializeFromRealmsWait = RequestTracker->CPP_WaitAll({}, InitalizeFromRealmOps, {}, InitializedFromRealmHandler);
}

void UBeamEditor::SelectRealm_OnSystemsReady(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&,
                                             FBeamOperationHandle Op) const
{
	const auto Subsystems = GEditor->GetEditorSubsystemArray<UBeamEditorSubsystem>();
	for (auto& Subsystem : Subsystems)
	{
		Subsystem->OnRealmInitialized();
	}

	RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
}


void UBeamEditor::ChangeMainEditorDeveloperRealm(const FBeamRealmHandle& NewRealmHandle, const FEditorStateChangedHandler& Handler)
{
	if (NewRealmHandle == GetDefault<UBeamCoreSettings>()->TargetRealm)
		return;

	const auto Op = SelectRealm(NewRealmHandle, {});

	const FOnWaitCompleteCode OnOperationComplete = FOnWaitCompleteCode::CreateLambda(
		[this, NewRealmHandle, Handler](const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&)
		{
			// We update the UserSlot info with the new PID.
			FBeamRealmUser UserData;
			const auto MainEditorSlot = GetMainEditorSlot(UserData);

			// Update the PID and change the slot
			UserSlots->SetPIDAtSlot(MainEditorSlot, NewRealmHandle.Pid, this);
			UserSlots->SaveSlot(MainEditorSlot, this);

			const auto _ = Handler.ExecuteIfBound();
		});
	RequestTracker->CPP_WaitAll({}, {Op}, {}, OnOperationComplete);
}

void UBeamEditor::SignOut()
{
	UserSlotClearedHandler = UserSlots->GlobalUserSlotClearedCodeHandler.AddUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamEditor, OnUserSlotCleared));
	UserSlots->ClearUserAtSlot(GetMainEditorSlot(), Manual, true);
}


void UBeamEditor::OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context) const
{
	const auto SlotId = GetMainEditorSlot();
	if (Reason == Manual || Reason == FailedAutomaticAuthentication)
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
