// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/BeamEditor.h"

#include "BeamEditorSettings.h"
#include "BeamableEditorBlueprintLibrary.h"
#include "BeamCoreSettings.h"
#include "AutoGen/Optionals/OptionalStringLibrary.h"
#include "AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamBackend/BeamBackend.h"
#include "UserSlots/UserSlot.h"

class UBeamCoreSettings;

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
	Backend = GEngine->GetEngineSubsystem<UBeamBackend>();
	UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();

	MainEditorSlotIdx = 0;
	UserSlotAuthenticatedHandler = UserSlots->GlobalUserSlotAuthenticatedCodeHandler.AddLambda([this]
	(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
		{
			// If we authenticated into a developer slot, let's gather the customer and project data for that user slot and store it.
			const auto EditorConfig = GetDefault<UBeamCoreSettings>();
			const auto SlotId = EditorConfig->DeveloperUserSlots[MainEditorSlotIdx];
			if (UserSlot.Name.Equals(SlotId))
			{
				const FEditorStateChangedHandler Handler;
				FetchProjectDataForSlot(UserSlot, Handler);
				ChangeActiveTargetRealm(BeamRealmUser.RealmHandle);
			}
		});

	// Sets up handlers for us to keep track of whether or not we are authenticated into the editor
	UserSlotClearedHandler = UserSlots->GlobalUserSlotClearedCodeHandler.AddLambda([this]
	(const EUserSlotClearedReason Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
		{
			// If we cleared the main developer user slot, we are no longer ready.
			const auto bWasReady = bIsMainEditorDeveloperReady;
			const auto CoreConfig = GetMutableDefault<UBeamCoreSettings>();
			const auto EditorConfig = GetMutableDefault<UBeamEditorSettings>();
			const auto SlotId = CoreConfig->DeveloperUserSlots[MainEditorSlotIdx];
			if (UserSlot.Name.Equals(SlotId))
			{
				EditorConfig->PerSlotDeveloperProjectData.Remove(SlotId);
				bIsMainEditorDeveloperReady = false;
				ChangeActiveTargetRealm(FBeamRealmHandle{TEXT(""), TEXT("")});
				OnMainDeveloperReadyChanged.Broadcast(bIsMainEditorDeveloperReady, bWasReady);
			}
		});

	// Tries to load the saved user at a specific slot.
	UserSlots->TryLoadSavedUserAtSlot(GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx], this);
}

void UBeamEditor::Deinitialize()
{
	UserSlots->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
	UserSlots->GlobalUserSlotClearedCodeHandler.Remove(UserSlotClearedHandler);
	FEditorDelegates::BeginPIE.Remove(BeginPIEHandler);
	FEditorDelegates::EndPIE.Remove(EndPIEHandler);
}

FUserSlot UBeamEditor::GetActiveMainEditorDeveloper(FBeamRealmUser& UserData) const
{
	const auto MainSlot = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots[MainEditorSlotIdx];
	ensureAlwaysMsgf(UserSlots->GetUserDataAtSlot(MainSlot, UserData), TEXT("No developer signed into the MainEditorDeveloper UserSlot! Please call UserSlot->SetAuthenticationData before this."));
	return MainSlot;
}

void UBeamEditor::GetActiveProjectAndRealmData(FBeamCustomerProjectData& ProjectData, FBeamProjectRealmData& RealmData) const
{
	const auto EditorSettings = GetDefault<UBeamEditorSettings>();

	FBeamRealmUser MainEditorDeveloper;
	const auto MainEditorSlot = GetActiveMainEditorDeveloper(MainEditorDeveloper);

	ProjectData = EditorSettings->PerSlotDeveloperProjectData.FindChecked(MainEditorSlot.Name);
	const auto FoundData = ProjectData.AllRealms.FindByPredicate([MainEditorDeveloper](FBeamProjectRealmData d) { return d.PID == MainEditorDeveloper.RealmHandle.Pid; });
	ensureAlwaysMsgf(FoundData, TEXT("No developer signed into the MainEditorDeveloper UserSlot! Please sign-in."));

	if (FoundData)
		RealmData = *FoundData;
}


void UBeamEditor::FetchProjectDataForSlot(FUserSlot SlotId, const FEditorStateChangedHandler& Handler)
{
	ensureAlwaysMsgf(SlotId.Name.Contains(TEXT("Developer")), TEXT("Can't get project information for slot ID as it is not a developer slot making the request. SLOT_ID=%s"), *SlotId.Name);

	FBeamRealmUser User;
	const auto IsSignedIn = UserSlots->GetUserDataAtSlot(SlotId, User, this);
	ensureAlwaysMsgf(IsSignedIn, TEXT("The given slot is not authenticated. Please sign-in/up before calling this. SLOT_ID=%s"), *SlotId.Name);

	const auto GetCustomerRequest = UGetCustomerRequest::Make(GetTransientPackage());
	const auto GetCustomerHandler = FOnGetCustomerFullResponse::CreateLambda([Handler, this, SlotId](FGetCustomerFullResponse Response)
	{
		switch (Response.State)
		{
		case Success:
			{
				// Gets all project data for the requesting user slot.				
				FBeamCustomerProjectData ProjectData;

				const auto CID = FString::Printf(TEXT("%lld"), Response.SuccessData->Customer->Cid);
				const auto CustomerName = ProjectData.CustomerName = Response.SuccessData->Customer->Name;

				bool _;
				const auto CustomerAlias = ProjectData.CustomerAlias = UOptionalStringLibrary::GetOptionalValue(Response.SuccessData->Customer->Alias, CustomerName, _);

				// Find the project with 0 children and get the project name from it...
				FString ProjectName;

				const auto RealmList = Response.SuccessData->Customer->Projects;
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
				const auto SlotName = Response.Context.UserSlot.Name;
				auto CoreConfig = GetMutableDefault<UBeamCoreSettings>();
				auto EditorConfig = GetMutableDefault<UBeamEditorSettings>();
				if (EditorConfig->PerSlotDeveloperProjectData.Contains(SlotName))
				{
					EditorConfig->PerSlotDeveloperProjectData[SlotName] = ProjectData;
				}
				else
				{
					EditorConfig->PerSlotDeveloperProjectData.Add(SlotName, ProjectData);
				}

				// If we are the main editor developer, we now have everything we need to create the editor flows.
				if (SlotId == CoreConfig->DeveloperUserSlots[MainEditorSlotIdx])
				{
					const auto bWasReady = bIsMainEditorDeveloperReady;
					bIsMainEditorDeveloperReady = true;
					OnMainDeveloperReadyChanged.Broadcast(bIsMainEditorDeveloperReady, bWasReady);
				}

				// We call the given handler always if it's bound
				if (Handler.IsBound())
					Handler.Execute();

				break;
			}
		case Error:
			{
				break;
			}
		case Cancelled: break;
		case Retrying: break;
		default: ;
		}
	});
	FBeamRequestContext RequestContext;
	GEngine->GetEngineSubsystem<UBeamRealmsApi>()->CPP_GetCustomer(SlotId, GetCustomerRequest, GetCustomerHandler, RequestContext);
}

void UBeamEditor::ChangeActiveTargetRealm(const FBeamRealmHandle& NewRealmHandle)
{
	UWorld* _ = nullptr;
	ensureAlwaysMsgf(!bIsRunningPIE, TEXT("Cannot change realm while in PIE!"));

	auto Settings = GetMutableDefault<UBeamCoreSettings>();
	Settings->TargetRealm = NewRealmHandle;
	Settings->SaveConfig();
}

void UBeamEditor::ChangeMainEditorDeveloperRealm(const FBeamRealmHandle& NewRealmHandle)
{
	ChangeActiveTargetRealm(NewRealmHandle);

	// We update the UserSlot info with the new PID.
	FBeamRealmUser UserData;
	const auto MainEditorSlot = GetActiveMainEditorDeveloper(UserData);

	// Update the PID and change the slot
	UserSlots->SetPIDAtSlot(MainEditorSlot, NewRealmHandle.Pid, this);
	UserSlots->SaveSlot(MainEditorSlot, this);
}


void UBeamEditor::SignOut()
{
	const auto EditorConfig = GetDefault<UBeamCoreSettings>();
	const auto SlotId = EditorConfig->DeveloperUserSlots[MainEditorSlotIdx];

	UserSlots->ClearUserAtSlot(SlotId, Manual, true);
}
