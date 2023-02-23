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


#include "UObject/Object.h"

#include "BeamEditor.generated.h"


DECLARE_DYNAMIC_DELEGATE(FEditorStateChangedHandler);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEditorStateChangedEvent);

UCLASS(NotBlueprintable, NotBlueprintType)
class BEAMABLECOREEDITOR_API UBeamEditorBootstrapper : public UObject
{
	GENERATED_BODY()

	UFUNCTION()
	void Run_TrySignIntoMainEditorSlot();


	UFUNCTION()
	void Run_DelayedInitialize();
	
	/**
	 * @brief Called when the editor finishes starting up.
	 */
	UFUNCTION()
	void Run();
};

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECOREEDITOR_API UBeamEditor : public UEditorSubsystem
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
	                                const TArray<FBeamErrorResponse>& Errors, FBeamOperationHandle Op) const;

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
	void SignIn_OnGetRealms(FGetGamesFullResponse Response, FBeamOperationHandle Op, FBeamCid Cid);

	/**
	 * @brief Callback for the GetAdminMe callback which is the last step in the sign in operation. 
	 */
	void SignIn_OnGetAdminMe(FBeamFullResponse<UGetAdminMeRequest*, UAccountPortalView*> Response, FBeamOperationHandle Op);


	/**
	 * @brief Callback to respond when the user slot becomes authenticated during the sign in flow.
	 */
	UFUNCTION()
	void SignIn_OnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context, FBeamOperationHandle Op);

	/**
	 * @brief Callback to respond when we get the project data for the authenticated user during the sign in flow.
	 */
	void SignIn_OnFetchProjectDataForSlot(FGetCustomerFullResponse Response, FBeamOperationHandle Op);

	/**
	 * @brief Helper function that updates the local data of projects that a customer has and associates that with the given UserSlot.  
	 */
	void CacheProjectDataForUserSlot(FUserSlot UserSlot, UCustomerViewResponse* CustomerViewResponse) const;


	/**
	 * @brief Used to set the active target realm without notifying all BeamEditorSubsystems --- this is not an async "Operation". It'll change it immediately.
	 * Don't use this unless you know what you are doing.	 
	 */
	void SetActiveTargetRealmUnsafe(const FBeamRealmHandle& NewRealmHandle) const;

public:
	/**
	 * @brief Helper function to be used in custom blueprint nodes.
	 */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamEditor* GetSelf(const UObject* CallingContext);

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


	/**
	 * @brief Registered to the global user-slot cleared callback from the user slot system so that we can clean up the editor environment if it was the MainEditorSlot that was cleared. 
	 */
	UFUNCTION()
	void OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context) const;


	/**
	 * @brief Gets the current authenticated MainEditorUser slot and it's data.
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	FUserSlot GetMainEditorSlot(FBeamRealmUser& UserData) const;

	/**
	 * @brief Gets the current authenticated MainEditorUser slot.
	 */
	FUserSlot GetMainEditorSlot() const;

	/**
	 * @brief Signs in to the beamable editor. Triggers 4 SubEvents before triggering success:
	 *  SubEvent - 0: Operation Completed successfully. User is now fully signed in. 
	 *  SubEvent - 1: 
	 * @param OrgName 
	 * @param Email 
	 * @param Password 
	 * @param OnOperationEvent 
	 * @return The OperationHandle for the sign in operation. 
	 */
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="OnOperationEvent"))
	FBeamOperationHandle SignIn(FString OrgName, FString Email, FString Password, const FBeamOperationEventHandler& OnOperationEvent);

	/**
	 * @brief Gets the project and realm data structures for the currently authenticated MainEditorUser slot; if the data is there already.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetActiveProjectAndRealmData(FBeamCustomerProjectData& ProjectData, FBeamProjectRealmData& RealmData);

	/**
	 * @brief Change the current target realm to a new target realm.
	 * Invokes two global callbacks (on every existing UBeamableEditorSubsystem): first a OnRealmCleanup and then a OnRealmInitialize(). 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	FBeamOperationHandle SelectRealm(const FBeamRealmHandle& NewRealmHandle, const FBeamOperationEventHandler& OnOperationEvent);

	/**
	 * @brief Changes the target realm via the MainEditorDeveloper. This is a no-op if the realm handle is the same as the current TargetRealm. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Handler"))
	void ChangeMainEditorDeveloperRealm(const FBeamRealmHandle& NewRealmHandle, const FEditorStateChangedHandler& Handler);

	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="OnOperationEvent"))
	void SignOut();

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnEnteringPIE;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnExitingPIE;
};
