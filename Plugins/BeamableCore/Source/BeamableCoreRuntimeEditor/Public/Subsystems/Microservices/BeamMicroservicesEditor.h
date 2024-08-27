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
#include "Subsystems/CLI/Autogen/BeamCliServicesRunCommand.h"

#include "BeamMicroservicesEditor.generated.h"

UENUM(BlueprintType)
enum ELocalMicroserviceRunningMethod { Any, Stopped, RunningOnDocker, RunningStandalone };

UENUM(BlueprintType)
enum EBeamServiceType { MicroService, MicroStorage };

USTRUCT(BlueprintType)
struct FLocalMicroserviceData
{
	GENERATED_BODY()

	/**
	 * The id of the service.
	 */
	UPROPERTY(BlueprintReadOnly)
	FString BeamoId;

	/**
	 * If the service is part of any BeamServiceGroup, the group will show up here.
	 */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> ServiceGroups;

	/**
	 * The current local running state of the service. This only reflects the local running state of the service.
	 * If its running remotely or not, is not captured by this variable.
	 */
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ELocalMicroserviceRunningMethod> RunningState = {};

	/**
	 * If, when deploying services to the realm, you wish to turn this service on. 
	 */
	UPROPERTY(BlueprintReadOnly)
	bool bShouldEnableRemoteOnPublish = {};

	/**
	 * The list of routing keys currently available for you to configure your local editor to target.
	 * Routing keys uniquely identify a running local service in a realm.
	 *
	 * The "" (empty string) routing key means "route to the deployed service in the realm".
	 * Any other routing key value means "route to the locally running service that has this routing key".
	 *
	 * These are generated automatically from a hash of your MAC Address and a prefix so you don't have to worry about guaranteeing uniqueness.
	 */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> AvailableKeys;

	/**
	 * The currently selected routing key.
	 */
	UPROPERTY(BlueprintReadWrite, DisplayName="Routing Key")
	FString CurrentRoutingKey;
};

UCLASS(BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamMicroserviceLocalEditorView : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString BeamoId;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EBeamServiceType> ServiceType;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ELocalMicroserviceRunningMethod> RunningState = {};

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> ServiceGroups;
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

	virtual void OnReady() override;

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
	 * @brief Helper function to be used in custom blueprint nodes.
	 */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamMicroservicesEditor* GetSelf(const UObject* CallingContext);

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
	 * Gets a list of filtered services, by group name and running status.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Editor|Microservice", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetFilteredListOfServices(TArray<FString> IncludedGroupNames, TArray<FString> ExcludedGroupNames, TEnumAsByte<ELocalMicroserviceRunningMethod> RunningStatusFilter,
	                                  TArray<UBeamMicroserviceLocalEditorView*>& FilteredServices);
	/**
	 * @brief Opens the swagger document for the current running service. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Editor|Microservice", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool OpenSwaggerDocs(FString BeamoId);

	/**
	 * Whether or not the currently selected routing key for a particular service is valid right now or not.	  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Editor|Microservice", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsCurrentRoutingKeyValid(FString BeamoId);


	/**
	 * Whether or not the currently selected routing key for a particular service is valid right now or not.	  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Editor|Microservice", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool SetCurrentRoutingKey(FString BeamoId, FString Key);

protected:
	void DeployMicroservices(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds, const FBeamOperationHandle& Op) const;

	void RunHostMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op);
	void RunDockerMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op);

	void StopHostMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op);
	void StopDockerMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op);

	// This is how we actually keep Local Microservice State in sync
	void OnUpdateLocalStateReceived(const TArray<UBeamCliProjectPsStreamData*>& Stream, const TArray<long long>&, const FBeamOperationHandle&);

	// Helper functions
	void SplitByHostOrDocker(const TArray<FString>& BeamoIds, TArray<FString>& DockerBeamoIds, TArray<FString>& HostBeamoIds);
};
