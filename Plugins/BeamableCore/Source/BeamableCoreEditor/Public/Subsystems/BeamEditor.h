// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamEditorSettings.h"
#include "BeamBackend/BeamBackend.h"
#include "UObject/Object.h"

#include "BeamEditor.generated.h"

DECLARE_DYNAMIC_DELEGATE(FEditorStateChangedHandler);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEditorStateChangedEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMainDeveloperReadyStateChanged, bool, bIsReady, bool, bWasReady);

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECOREEDITOR_API UBeamEditor : public UEditorSubsystem
{
	GENERATED_BODY()

	
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

public:
	/**
	 * @brief Index into UBeamableCoreEditorConfig's DeveloperSlots that defines the "main editor slot". This is the one the windows consider as the main developer currently
	 * interacting with the project.
	 */
	UPROPERTY()
	int32 MainEditorSlotIdx;
	
	UPROPERTY()
	UBeamBackend* Backend;
	
	UPROPERTY()
	UBeamUserSlots* UserSlots;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	bool bIsMainEditorDeveloperReady;
	
	UPROPERTY(BlueprintReadOnly, Category="Beam")
    bool bIsRunningPIE;	

	UFUNCTION(BlueprintPure, Category="Beam")
	FUserSlot GetActiveMainEditorDeveloper(FBeamRealmUser& UserData) const;

	UFUNCTION(BlueprintPure, Category="Beam")
	void GetActiveProjectAndRealmData(FBeamCustomerProjectData& ProjectData, FBeamProjectRealmData& RealmData) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="SlotId, Handler"))
	void FetchProjectDataForSlot(FUserSlot SlotId, const FEditorStateChangedHandler& Handler);

	UFUNCTION(BlueprintCallable, Category="Beam")
	void ChangeActiveTargetRealm(const FBeamRealmHandle& NewRealmHandle);

	UFUNCTION(BlueprintCallable, Category="Beam")
	void ChangeMainEditorDeveloperRealm(const FBeamRealmHandle& NewRealmHandle);

	UFUNCTION(BlueprintCallable, Category="Beam")
	void SignOut();
	
	UPROPERTY(BlueprintAssignable, Category="Beam")
	FMainDeveloperReadyStateChanged OnMainDeveloperReadyChanged;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnEnteringPIE;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnExitingPIE;
	
};


