// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamEditorSettings.h"

#include "UserSlots/BeamUserSlots.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "AutoGen/SubSystems/Accounts/GetAdminMeRequest.h"
#include "AutoGen/SubSystems/Auth/AuthenticateRequest.h"
#include "AutoGen/SubSystems/Realms/GetCustomerAliasAvailableRequest.h"
#include "AutoGen/SubSystems/Realms/GetCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetGamesRequest.h"
#include "AutoGen/SubSystems/Realms/PostCustomerRequest.h"
#include "EditorSubsystem.h"

#include "UObject/Object.h"

#include "BeamEditor.generated.h"

class UBeamCliMeStreamData;

UENUM(BlueprintType)
enum class EMessageType : uint8
{
	VE_Info UMETA(DisplayName="Info"),
	VE_Warning UMETA(DisplayName="Warning"),
	VE_Error UMETA(DisplayName="Error"),
};


UENUM(BlueprintType)
enum class EPortalPage : uint8
{
	VE_Dashboard UMETA(DisplayName="Dashboard"),
	VE_Microservices UMETA(DisplayName="Microservices"),
	VE_PlayerSearch UMETA(DisplayName="PlayerSearch"),
	VE_RealmConfig UMETA(DisplayName="RealmConfig"),
	VE_Content UMETA(DisplayName="Content"),
	VE_Campaign UMETA(DisplayName="Campaign"),
};

USTRUCT(BlueprintType)
struct FDocsPageItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Beam")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Beam")
	FString Path;

	bool operator==(const FDocsPageItem& Other) const
	{
		return Id == Other.Id && Path == Other.Path;
	}
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEditorMessageClickedEvent);

UCLASS(Blueprintable)
class UBeamableWindowMessage : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category="Beam")
	EMessageType MessageType;
	UPROPERTY(BlueprintReadWrite, Category="Beam")
	FString MessageValue;
	UPROPERTY(BlueprintAssignable)
	FEditorMessageClickedEvent OnClickEvent;

	UFUNCTION(BlueprintCallable, Category="Beam")
	void HandleClick()
	{
		this->OnClickEvent.Broadcast();
	}

	UFUNCTION(BlueprintPure, Category="Beam")
	FText GetText() const
	{
		return FText::FromString(this->MessageValue);
	}

	UFUNCTION(BlueprintPure, Category="Beam")
	void GetIcon(FSlateBrush& Out) const
	{
		if (this->MessageValue.IsEmpty())
		{
			Out = *FAppStyle::Get().GetBrush(TEXT("Sequencer.Empty"));
			Out.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 0.0f, 0.0f));
			return;
		}
		switch (this->MessageType)
		{
		case EMessageType::VE_Info:
			Out = *FAppStyle::Get().GetBrush(TEXT("Icons.Info"));
			Out.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case EMessageType::VE_Warning:
			Out = *FAppStyle::Get().GetBrush(TEXT("Icons.Warning"));
			Out.TintColor = FSlateColor(FLinearColor(0.9f, 0.8f, 0.0f, 1.0f));
			break;
		case EMessageType::VE_Error:
			Out = *FAppStyle::Get().GetBrush(TEXT("Icons.Error"));
			Out.TintColor = FSlateColor(FLinearColor(1.0f, 0.1f, 0.1f, 1.0f));
			break;
		}
	}
};


DECLARE_DELEGATE(FEditorStateChangedHandlerCode);
DECLARE_DYNAMIC_DELEGATE(FEditorStateChangedHandler);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEditorStateChangedEvent);

UCLASS(NotBlueprintable, NotBlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamEditorBootstrapper : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief Called when the editor finishes starting up.
	 */
	UFUNCTION()
	void Run();

	/**
	 * @brief In order to guarantee all Editor Subsystems have been properly Instantiated (via UE's Subsystem injection stuff), we delay a tick when starting Beamable's editor environment.
	 * This solves some other problems such as Asset loading inconsistencies we've found around reading/mutating Default UObjects (mainly settings).
	 *
	 * Also, some of our editor systems require talking to Beamable's servers (or other async operations) for proper initialization.
	 * We need to ensure all of these have completed across all services before moving on to the next step of our editor initialization (which is trying to sign in).
	 */
	UFUNCTION()
	void Run_DelayedInitialize();

	/**
	 * @brief After we have a guarantee that our services are up, we try to sign in to whichever account is saved in the MainEditor user slot
	 * This is index 0 of the Editor user slots configured in BeamableCoreSettings.
	 *
	 * This is a partially async process: if we are already signed in, we have to go grab some project data to make sure it is up to date.
	 * After that we also ensure that we are pointed at the realm store for that user slot.
	 *
	 * Once updated and the realm selected, all BeamEditorSubsystems have the opportunity to run some async operations (in parallel).
	 * We wait for all of these to finish before flagging the editor as ready.
	 *
	 * Our BeamableWindowUI and other AssetEditor extensions wait for this flag to be true before allowing functionality to be accessed in editor.
	 */
	UFUNCTION()
	void Run_TrySignIntoMainEditorSlot(FBeamWaitCompleteEvent Evt);
};

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamEditor : public UEditorSubsystem
{
	GENERATED_BODY()

	friend class UBeamEditorBootstrapper;

	static const FBeamRealmHandle Signed_Out_Realm_Handle;

	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;


	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when a user slot is authenticated.
	 */
	FDelegateHandle UserSlotAuthenticatedHandler;

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when a user slot is cleared.
	 */
	FDelegateHandle UserSlotClearedHandler;

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when we enter PIE mode (mostly just trigger a callback).
	 */
	FDelegateHandle BeginPIEHandler;

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when we exit PIE mode (mostly just trigger a callback).
	 */
	FDelegateHandle EndPIEHandler;

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when the editor is fully initialized (kick off the Beamable Editor Integration initialization flow).
	 */
	FDelegateHandle EditorInitializedHandle;

	/**
	 * @brief When a realm change is requested, we notify all UBeamEditorSubsystems that exist so that they can prepare for the change.
	 * They return operation handles that we wait on. When done, we change the realm.
	 */
	TArray<FBeamOperationHandle> InitializeAfterEditorReadyOps = {};
	FBeamWaitHandle OnInitializedAfterEditorReadyWait;

	/**
	 * @brief When a realm change is requested, we notify all UBeamEditorSubsystems that exist so that they can prepare for the change.
	 * They return operation handles that we wait on. When done, we change the realm.
	 */
	TArray<FBeamOperationHandle> PrepareForRealmChangeOps = {};
	FBeamWaitHandle OnReadyForRealmChangeWait;

	/**
	 * @brief When we change the realm, we notify all UBeamEditorSubsystems that exist so that they can set up their internal state to be correct with the new realm.
	 * They return operation handles that we wait on. When ALL operations of ALL systems are done, we notify each system that the realm change was finished.
	 */
	TArray<FBeamOperationHandle> InitalizeFromRealmOps = {};
	FBeamWaitHandle InitializeFromRealmsWait;

	/**
	 * @brief When we change the realm, we notify all UBeamEditorSubsystems that exist so that they can set up their internal state to be correct with the new realm.
	 * They return operation handles that we wait on. When ALL operations of ALL systems are done, we notify each system that the realm change was finished.
	 */
	TArray<FBeamOperationHandle> RealmInitializedOps = {};
	FBeamWaitHandle RealmInitializedWait;

	/**
	 * @brief Registered to the global user-slot cleared callback from the user slot system so that we can clean up the editor environment if it was the MainEditorSlot that was cleared. 
	 */
	UFUNCTION()
	void OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot,
	                       const FBeamRealmUser& BeamRealmUser, const UObject* Context);

	// Callbacks and public utilities
public:
	/**
	 * @brief Index into UBeamableCoreEditorConfig's DeveloperSlots that defines the "main editor slot". This is the one the windows consider as the main developer currently
	 * interacting with the project.
	 */
	UPROPERTY()
	int32 MainEditorSlotIdx;

	UPROPERTY()
	UBeamUserSlots* UserSlots;

	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	bool bIsRunningPIE;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	bool bEditorReady;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	UBeamableWindowMessage* WindowMessage;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnEnteringPIE;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnExitingPIE;

	UPROPERTY(BlueprintReadOnly)
	FBeamCustomerProjectData CurrentProjectData;

	// This will list all the docs pages in the Unreal - (NOT IN USE)
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TArray<FDocsPageItem> DocsPages;
	/**
	 * Called whenever apply to build is pressed. Only use this to bind things that we can't call directly (from other modules).
	 */
	FEditorStateChangedEvent OnAppliedSettingsToBuild;


	/**
	 * @brief Gets the current authenticated MainEditorUser slot and it's data.
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	FUserSlot GetMainEditorSlot(FBeamRealmUser& UserData) const;

	/**
	 * @brief Gets the current authenticated MainEditorUser slot and it's data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetMainEditorSlot(FUserSlot& Slot, FBeamRealmUser& UserData);

	/**
	 * @brief Gets the MainEditorUser slot.
	 */
	FUserSlot GetMainEditorSlot() const;

	/**
	 * @brief Gets the project and realm data structures for the currently authenticated MainEditorUser slot; if the data is there already.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetActiveProjectAndRealmData(FBeamCustomerProjectData& ProjectData, FBeamProjectRealmData& RealmData);


	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="OnOperationEvent"))
	void SignOut();

	/**
	 * @brief Helper function to be used in custom blueprint nodes.
	 */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamEditor* GetSelf(const UObject* CallingContext);

	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="OnOperationEvent"))
	void SetBeamableWindowMessage(UBeamableWindowMessage* message);


	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="OnOperationEvent"))
	void UpdateBeamableWindowMessage(FString Message, EMessageType typeOfMessage);

	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="OnOperationEvent"))
	void ClearBeamableWindowMessage();

	UFUNCTION(BlueprintCallable, Category="Beam")
	void OpenDocsPage(FDocsPageItem item);

	// Operations
public:
	/**
	 * @brief Signs in to the beamable editor.	  
	 * @return The OperationHandle for the sign in operation. 
	 */
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="OnOperationEvent"))
	FBeamOperationHandle SignInOperation(FString OrgName, FString Email, FString Password, const FBeamOperationEventHandler& OnOperationEvent);

	/**
	 * @brief Signs in to the beamable editor.	  
	 * @return The OperationHandle for the sign in operation. 
	 */
	FBeamOperationHandle CPP_SignInOperation(FString OrgName, FString Email, FString Password, const FBeamOperationEventHandlerCode& OnOperationEvent);

	/**
	 * @brief Change the current target realm to a new target realm.
	 * Invokes two global callbacks (on every existing UBeamableEditorSubsystem): first a OnRealmCleanup and then a OnRealmInitialize(). 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	FBeamOperationHandle SelectRealmOperation(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationEventHandler& OnOperationEvent);

	/**
	* @brief Change the current target realm to a new target realm.
	 * Invokes two global callbacks (on every existing UBeamableEditorSubsystem): first a OnRealmCleanup and then a OnRealmInitialize(). 
	 */
	FBeamOperationHandle CPP_SelectRealmOperation(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationEventHandlerCode& OnOperationEvent);

	// Operation Implementations.
private:
	/**
	 * @brief Signs in as a part of the given operation. 
	 */
	void SignIn(FString OrgName, FString Email, FString Password, FBeamOperationHandle Op);

	/**
	 * @brief Signs automatically using the current CLI info. 
	 */
	void SignInWithCliInfo(FBeamOperationHandle Op);

	/**
	 * @brief Call to select a realm as a part of the given operation. 
	 */
	void SelectRealm(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationHandle& Op);

	/**
	 * @brief Callback for RealmWillChangeHandler. Takes an extra NewRealmHandle that is captured when we kick off the realm change flow. (See ChangeActiveRealm). 
	 */
	void SelectRealm_OnReadyForChange(FBeamWaitCompleteEvent Evt, FBeamRealmHandle NewRealmHandle,
	                                  FBeamOperationHandle Op);

	/**
	 * @brief Callback for RealmChangedHandler. (See ChangeActiveRealm and OnRealmWillChangeHandler).
	 */
	void SelectRealm_OnRealmInitialized(FBeamWaitCompleteEvent Evt, FBeamRealmHandle NewRealmHandle,
	                                    FBeamOperationHandle Op);

	/**
	 * Callback for after OnRealmInitialized. 
	 */
	void SelectRealm_OnSystemsReady(FBeamWaitCompleteEvent Evt, FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op);

	/**
	 * @brief Opens the Beamable Portal, signed into the MainEditorUser's account, at the dashboard page. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void OpenPortalOnCurrentRealm();

	/**
	 * @brief Opens the Beamable Portal, signed into the MainEditorUser's account, at the selected page. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void OpenPortal(EPortalPage page);

	// Utility Functions
private:
	/**
	 * @brief Used to set the active target realm without notifying all BeamEditorSubsystems --- this is not an async "Operation". It'll change it immediately.
	 * Don't use this unless you know what you are doing.	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void SetActiveTargetRealmUnsafe(const FBeamRealmHandle& NewRealmHandle);


	/**
	 * @brief Use this to apply all the current settings in saved (TargetRealm, mainly) to the project's actual DefaultEngine.ini file.
	 * Normally, we save TargetRealm per-developer (it stays in your local Saved/Config/Engine.ini file); once this get's called, this is applied.
	 *
	 * The use case for this is to keep each branches' build settings correctly stored in version control while developers to move between realms locally without having to worry about not commiting
	 * the DefaultEngine.ini file (the one in Config/DefaultEngine.ini). 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void ApplyCurrentSettingsToBuild();
};
