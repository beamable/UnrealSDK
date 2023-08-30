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
class BEAMABLECORERUNTIMEEDITOR_API UBeamCli : public UBeamEditorSubsystem
{
	GENERATED_BODY()

protected:
	virtual FBeamOperationHandle InitializeWhenEditorReady() override;

	virtual void OnRealmInitialized() override;

	bool bInstalled;

	UPROPERTY()
	TArray<UBeamCliCommand*> RunningProcesses;

	TUniquePtr<FMonitoredProcess> IsInstalledCliProcess;

public:
	/**
	 * @brief Just a helper function to kick off a command.
	 * UBeamCliCommands run on a separate process and have a thread in this process watching them.
	 * Whenever stream messages from the other process arrive on this "watch" thread, we dispatch them to the GameThread via AsyncTask.
	 * This means you can run arbitrary code (including UI code) out of the functions in commands.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Params,Op"))
	void RunCommand(UBeamCliCommand* Command, const TArray<FString>& Params, const FBeamOperationHandle& Op);

	/**
	 * @brief Just a helper function to run a command synchronously.
	 * This is useful in cases where you don't want to or can't run it asynchronously. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Params"))
	void RunCommandSync(UBeamCliCommand* Command, const TArray<FString>& Params);

	/**
	 * @brief Whether or not the CLI is installed on this machine. We check for all editor integrations that require the CLI to work. 
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	bool IsInstalled() const { return bInstalled; }
};
