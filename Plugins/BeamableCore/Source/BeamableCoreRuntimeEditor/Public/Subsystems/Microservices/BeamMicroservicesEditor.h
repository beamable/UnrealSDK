// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RequestTracker/BeamOperation.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/BeamEditorSubsystem.h"

#include "BeamLogging.h"
#include "BeamBackend/BeamMicroserviceClientSubsystem.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectPsCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServicesPsCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectOpenSwaggerCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServicesDeployCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServicesResetCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServicesRunCommand.h"

#include "BeamMicroservicesEditor.generated.h"

UENUM(BlueprintType)
enum ELocalMicroserviceRunningMethod { Stopped, RunningOnDocker, RunningStandalone };

USTRUCT(BlueprintType)
struct FLocalMicroserviceData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString BeamoId;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ELocalMicroserviceRunningMethod> RunningState = {};

	UPROPERTY(BlueprintReadOnly)
	bool bShouldEnableRemoteOnPublish = {};
};

USTRUCT(BlueprintType)
struct FRemoteMicroserviceData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString BeamoId;

	UPROPERTY(BlueprintReadOnly)
	bool bIsEnabled = {};
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMicroserviceStateChange);

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamMicroservicesEditor : public UBeamEditorSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamCli* Cli;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void OnRealmInitialized() override;

	FDelegateHandle BeginPIE;
	FDelegateHandle EndPIE;

public:
	/**
	 * @brief Called whenever we update the LocalMicroserviceData dictionary. UI can bind itself to this to update itself. 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnMicroserviceStateChange OnLocalMicroserviceUpdate;

	/**
	 * @brief Current local state of LocalMicroservices according to the editor. UI should always build itself from the data here whenever it changes.
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FLocalMicroserviceData> LocalMicroserviceData;

	/**
	 * @brief Current local state of RemoteMicroservices (the ones running in your current realm). UI should always build itself from the data here whenever it changes.
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FRemoteMicroserviceData> RemoteMicroserviceData;

	/**
	 * @brief Helper function to be used in custom blueprint nodes.
	 */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamMicroservicesEditor* GetSelf(const UObject* CallingContext);

	/**
	 * @brief Updates the RemoteMicroserviceData with state from the current realm. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Editor|Microservice")
	FBeamOperationHandle UpdateRemoteMicroserviceStateOperation(const FBeamOperationEventHandler& OnOperationEvent);

	/**
	 * @brief Updates the RemoteMicroserviceData with state from the current realm. 
	 */
	FBeamOperationHandle CPP_UpdateRemoteMicroserviceStateOperation(const FBeamOperationEventHandlerCode& OnOperationEvent);

	/**
	 * @brief Builds and deploys the current Microservice project to the current realm. After this succeeds, calling the UpdateRemoteMicroserviceStateOperation will fetch the state of the deployed microservices.  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Editor|Microservice", meta=(AutoCreateRefTerm="EnableBeamoIds,DisableBeamoIds"))
	FBeamOperationHandle DeployRemoteMicroservicesOperation(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds, const FBeamOperationEventHandler& OnOperationEvent);

	/**
	 * @brief Builds and deploys the current Microservice project to the current realm. After this succeeds, calling the UpdateRemoteMicroserviceStateOperation will fetch the state of the deployed microservices.  
	 */
	FBeamOperationHandle CPP_DeployRemoteMicroservicesOperation(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds, const FBeamOperationEventHandlerCode& OnOperationEvent);

	/**
	 * @brief Builds and runs the current Microservice project(s) locally, in Docker.  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Editor|Microservice", meta=(AutoCreateRefTerm="BeamoIds"))
	FBeamOperationHandle RunLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandler& OnOperationEvent);

	/**
	 * @brief Builds and runs the current Microservice project(s) locally, in Docker.  
	 */
	FBeamOperationHandle CPP_RunLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandlerCode& OnOperationEvent);


	/**
	 * @brief If a LocalMicroservice is running in Docker, calling this passing in it's BeamoId will kill the container running it.  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Editor|Microservice")
	FBeamOperationHandle StopLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandler& OnOperationEvent);

	/**
	 * @brief If a LocalMicroservice is running in Docker, calling this passing in it's BeamoId will kill the container running it.  
	 */
	FBeamOperationHandle CPP_StopLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandlerCode& OnOperationEvent);

	/**
	 * @brief Opens the swagger document for the current running service. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Editor|Microservice")
	bool OpenSwaggerDocs(FString BeamoId, bool bIsRemote);

protected:
	void UpdateRemoteMicroserviceState(const TFunction<void(const int& ResCode, const FBeamOperationHandle& Op)>& OnComplete, const FBeamOperationHandle& Op);
	void EnsureExistingServices();
	void DeployMicroservices(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds, const FBeamOperationHandle& Op) const;
	void RunDockerMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op);
	void StopDockerMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op);

	// This is how we actually keep Local Microservice State in sync
	void OnUpdateLocalStateReceived(const TArray<FBeamCliProjectPsStreamData>& Stream, const TArray<long long>&, const FBeamOperationHandle&);
};
