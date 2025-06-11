// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamEditor.h"
#include "BeamBackend/BeamRealmHandle.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "UObject/Object.h"
#include "BeamEditorSubsystem.generated.h"

class UBeamEditor;
class UBeamRequestTracker;

/**
 * 
 */
UCLASS(Abstract, NotBlueprintType, Blueprintable)
class BEAMABLECORERUNTIMEEDITOR_API UBeamEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

protected:
	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;


	UPROPERTY()
	UBeamEditor* Editor;

	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

public:
	UFUNCTION(Category="Beam")
	virtual FBeamOperationHandle InitializeWhenEditorReady();

	UFUNCTION(Category="Beam")
	virtual FBeamOperationHandle PrepareForRealmChange(FBeamRealmHandle CurrRealm, FBeamRealmHandle NewRealm);

	UFUNCTION(Category="Beam")
	virtual FBeamOperationHandle InitializeRealm(FBeamRealmHandle NewRealm);

	UFUNCTION(Category="Beam")
	virtual FBeamOperationHandle OnRealmInitialized(FBeamRealmHandle NewRealm);

	UFUNCTION(Category="Beam")
	virtual void OnReady();

	UFUNCTION(Category="Beam")
	virtual void OnSignOut();
};
