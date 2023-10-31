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


#include "UObject/Object.h"

#include "BeamEditor.generated.h"


DECLARE_DELEGATE(FEditorStateChangedHandlerCode);
DECLARE_DYNAMIC_DELEGATE(FEditorStateChangedHandler);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEditorStateChangedEvent);

UCLASS(NotBlueprintable, NotBlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamEditorBootstrapper : public UObject
{
	GENERATED_BODY()

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
	void Run_TrySignIntoMainEditorSlot();

	/**
	 * @brief This runs after the SignIn operation the previous step resolves and simply flags the editor as ready. 
	 */
	UFUNCTION()
	void Run_EditorReady(TArray<FUserSlot>& UserSlots, FBeamOperationEvent OperationEvent);
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
	 * @brief When a realm change is requested, we notify all UBeamEditorSubsystems that exist so that they can prepare for the change.
	 * They return operation handles that we wait on. When done, we change the realm.
	 */
	TArray<FBeamOperationHandle> InitializeAfterEditorReadyOps = {};
	FBeamWaitHandle OnInitializedAfterEditorReadyWait;
	FOnWaitCompleteCode OnInitializedAfterEditorReadyChange;

	/**
	 * @brief When a realm change is requested, we notify all UBeamEditorSubsystems that exist so that they can prepare for the change.
	 * They return operation handles that we wait on. When done, we change the realm.
	 */
	TArray<FBeamOperationHandle> PrepareForRealmChangeOps = {};
	FBeamWaitHandle OnReadyForRealmChangeWait;
	FOnWaitCompleteCode OnReadyForRealmChange;

	/**
	 * @brief When we change the realm, we notify all UBeamEditorSubsystems that exist so that they can set up their internal state to be correct with the new realm.
	 * They return operation handles that we wait on. When ALL operations of ALL systems are done, we notify each system that the realm change was finished.
	 */
	TArray<FBeamOperationHandle> InitalizeFromRealmOps = {};
	FBeamWaitHandle InitializeFromRealmsWait;
	FOnWaitCompleteCode InitializedFromRealmHandler;

	/**
	 * @brief Registered to the global user-slot cleared callback from the user slot system so that we can clean up the editor environment if it was the MainEditorSlot that was cleared. 
	 */
	UFUNCTION()
	void OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context);

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

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnEnteringPIE;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnExitingPIE;


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
	 * @brief Gets the current authenticated MainEditorUser slot.
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

	/**
	 * @brief If you are not currently signed in, signs up a new Beamable customer and then signs into that customer's account.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	FBeamOperationHandle SignUpOperation(FString ProjectName, FString OrgName, FString Email, FString Password, FString Alias, const FBeamOperationEventHandler& OnOperationEvent);

	/**
	 * @brief If you are not currently signed in, signs up a new Beamable customer and then signs into that customer's account.
	 */
	FBeamOperationHandle CPP_SignUpOperation(FString ProjectName, FString OrgName, FString Email, FString Password, FString Alias, const FBeamOperationEventHandlerCode& OnOperationEvent);

	// Operation Implementations.
private:
	/**
	 * @brief Signs up a new customer as part of the given operation.
	 */
	void SignUp(FString ProjectName, FString OrgName, FString Email, FString Password, FString Alias, FBeamOperationHandle Op);

	/**
	 * @brief Callback for when the new customer is properly created. 
	 */
	void SignUp_OnPostCustomer(const FPostCustomerFullResponse Response, const FBeamOperationHandle Op, const FString OrgName, const FString Email, const FString Password);

	/**
	 * @brief Signs in as a part of the given operation. 
	 */
	void SignIn(FString OrgName, FString Email, FString Password, FBeamOperationHandle Op);

	/**
	 * @brief Callback for the resolution of customer alias step of the sign in operation.
	 */
	void SignIn_OnGetCustomerAliasAvailable(FGetCustomerAliasAvailableFullResponse Response, FBeamOperationHandle Op, FString Email, FString Password);

	/**
	 * @brief Callback for the authentication request in the sign in operation. 
	 */
	void SignIn_OnAuthenticate(FAuthenticateFullResponse Response, FBeamOperationHandle Op, FBeamCid Cid);
	/**
	 * @brief Callback for the GetGames (get all realms for the authenticated customer) in the sign in operation.  
	 */
	void UpdateSignedInUserData_OnGetRealms(FGetGamesFullResponse Response, FBeamOperationHandle Op, FBeamCid Cid);

	/**
	 * @brief Callback for the GetAdminMe callback which is the last step in the sign in operation. 
	 */
	void UpdateSignedInUserData_OnGetAdminMe(FBeamFullResponse<UGetAdminMeRequest*, UAccountPortalView*> Response, FBeamOperationHandle Op);

	/**
	 * @brief Callback to respond when the user slot becomes authenticated during the sign in flow.
	 */
	UFUNCTION()
	void UpdateSignedInUserData_OnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context, FBeamOperationHandle Op);

	/**
	 * @brief Callback to respond when we get the project data for the authenticated user during the sign in flow.
	 */
	void UpdateSignedInUserData_OnFetchProjectDataForSlot(FGetCustomerFullResponse Response, FBeamOperationHandle Op);

	UFUNCTION()
	/**
	 * @brief Callback to the Select Realm Operation that we are calling once we go through the sign-in flow. 
	 */
	void UpdateSignedInUserData_OnRealmSelected(const TArray<FUserSlot>& Slots, FBeamOperationEvent OperationEvent, FBeamOperationHandle SignInOperation) const;


	/**
	 * @brief Call to select a realm as a part of the given operation. 
	 */
	void SelectRealm(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationHandle& Op);

	/**
	 * @brief Callback for RealmWillChangeHandler. Takes an extra NewRealmHandle that is captured when we kick off the realm change flow. (See ChangeActiveRealm). 
	 */
	UFUNCTION()
	void SelectRealm_OnReadyForChange(const TArray<FBeamRequestContext>& Contexts, const TArray<TScriptInterface<IBeamBaseRequestInterface>>& Requests, const TArray<UObject*>& Responses,
	                                  const TArray<FBeamErrorResponse>& Errors, FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op);

	/**
	 * @brief Callback for RealmChangedHandler. (See ChangeActiveRealm and OnRealmWillChangeHandler).
	 */
	UFUNCTION()
	void SelectRealm_OnSystemsReady(const TArray<FBeamRequestContext>& Contexts, const TArray<TScriptInterface<IBeamBaseRequestInterface>>& Requests, const TArray<UObject*>& Responses,
	                                const TArray<FBeamErrorResponse>& Errors, FBeamRealmHandle NewRealmHandle, FBeamOperationHandle Op) const;

	/**
	 * @brief Opens the Beamable Portal, signed into the MainEditorUser's account, at the dashboard page. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void OpenPortalOnCurrentRealm();

	// Utility Functions
private:
	/**
	 * @brief Helper function that updates the local data of projects that a customer has and associates that with the given UserSlot.  
	 */
	void CacheProjectDataForUserSlot(FUserSlot UserSlot, UCustomerViewResponse* CustomerViewResponse) const;

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

	UFUNCTION(BlueprintCallable, Category="Beam")
	void UpdateSignedInUserData(FBeamOperationHandle Op, FBeamCid Cid, FString AccessToken, FString RefreshToken, int64 ExpiresIn);
};
