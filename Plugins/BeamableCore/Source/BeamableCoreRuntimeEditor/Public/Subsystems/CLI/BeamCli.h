// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "Misc/MonitoredProcess.h"
#include "RequestTracker/BeamOperation.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "BeamCli.generated.h"

class UBeamCliServerServeCommand;
class UBeamCliCommand;

USTRUCT(BlueprintType)
struct FBeamCliError : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY()
	FString Message = {};
	UPROPERTY()
	FString Invocation = {};
	UPROPERTY()
	int32 ExitCode = {};
	UPROPERTY()
	FString TypeName = {};
	UPROPERTY()
	FString FullTypeName = {};
	UPROPERTY()
	FString StackTrace = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

USTRUCT(BlueprintType)
struct FBeamEnqueuedCliCommand
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamCliCommand* CliCommand;

	UPROPERTY()
	TArray<FString> Params;

	UPROPERTY()
	FBeamOperationHandle Op;

	FBeamEnqueuedCliCommand(): CliCommand(nullptr)
	{
	}

	FBeamEnqueuedCliCommand(UBeamCliCommand* CliCommand, TArray<FString> Params, FBeamOperationHandle Op)
		: CliCommand(CliCommand),
		  Params(Params),
		  Op(Op)
	{
	}
};

/**
 * Class that we use whenever we want to expose a set of CLI errors that happen as part of a command invocation to Blueprint-land.
 * See our "content publish" logic for a usage example.
 */
UCLASS(BlueprintType)
class UBeamCliErrorData : public UObject, public IBeamOperationEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FBeamCliError> Errors;
};

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIMEEDITOR_API UBeamCli : public UBeamEditorSubsystem
{
	GENERATED_BODY()

protected:
	virtual FBeamOperationHandle InitializeWhenEditorReady() override;

	virtual FBeamOperationHandle InitializeRealm(FBeamRealmHandle NewRealm) override;

	FOptionalBool bInstalled;

	UPROPERTY()
	TArray<UBeamCliCommand*> RunningProcesses;

	UPROPERTY()
	TArray<FBeamEnqueuedCliCommand> EnqueuedProcesses;

	TUniquePtr<FMonitoredProcess> IsInstalledProcess;

	/**
	 * Stores the current location of the CLI process running in server mode.
	 * This will be empty when no process is running.
	 * When it is empty, RunCommandServer attempts to boot the server up again before anything.  
	 */
	FString CurrentCliServerUri;

	

public:

	void StartCliServer(bool bSkipPrewarm);
	
	/**
	 * @brief Just a helper function to kick off a command.
	 * UBeamCliCommands run on a separate process and have a thread in this process watching them.
	 * Whenever stream messages from the other process arrive on this "watch" thread, we dispatch them to the GameThread via AsyncTask.
	 * This means you can run arbitrary code (including UI code) out of the functions in commands.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Params,Op"))
	void RunCommand(UBeamCliCommand* Command, const TArray<FString>& Params, const FBeamOperationHandle& Op);


	/**
	 * This will kick a command via our long-running CLI process (in server mode). Always prefer to use this over RunCommand and RunCommandSync unless you can't.
	 * Cannot be used for long-running commands (such as ProjectPs).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Params,Op"))
	void RunCommandServer(UBeamCliCommand* Command, const TArray<FString>& Params, const FBeamOperationHandle& Op);

	/**
	 * @brief Just a helper function to run a command synchronously.
	 * This is useful in cases where you don't want to or can't run it asynchronously. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Params"))
	void RunCommandSync(UBeamCliCommand* Command, const TArray<FString>& Params);


	/**
	 * @brief Stops a long-running command. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void StopCommand(UBeamCliCommand* Command);

	/**
	 * @brief Stops all commands that are running and then stops the CLI server itself.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void StopCli();

	/**
	 * @brief Whether or not the CLI is installed on this machine. We check for all editor integrations that require the CLI to work. 
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	bool IsInstalled() const { return bInstalled.IsSet && bInstalled.Val; }

	/**
	 * @brief Gets the correct CLI installation to use. 
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	FString GetPathToCli() const;

	/**
	 * Invoked when a command is done so we can cleanup.
	 */
	void OnCommandCompleted(UBeamCliCommand* Command);
};
