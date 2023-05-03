// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/MonitoredProcess.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "BeamCli.generated.h"

class UBeamCliCommand;
/**
 * 
 */
UCLASS()
class BEAMABLECOREEDITOR_API UBeamCli : public UBeamEditorSubsystem
{
	GENERATED_BODY()

protected:
	virtual FBeamOperationHandle InitializeWhenEditorReady() override;

	virtual void OnRealmInitialized() override;

	bool bInstalled;

	UPROPERTY()
	TArray<UBeamCliCommand*> RunningProcesses;

	
	TUniquePtr<FMonitoredProcess> CliProcess;

public:
	UFUNCTION(BlueprintCallable, Category="Beam")
	void InitCommand();
};
