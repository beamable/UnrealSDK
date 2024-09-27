// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Microservices/BeamMicroservicesEditor.h"

#include "Subsystems/CLI/Autogen/BeamCliFederationListCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliFederationLocalKeyCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectRunCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectStopCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServicesStopCommand.h"

void UBeamMicroservicesEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Cli = Collection.InitializeDependency<UBeamCli>();
	Backend = GEngine->GetEngineSubsystem<UBeamBackend>();
}

void UBeamMicroservicesEditor::Deinitialize()
{
	Super::Deinitialize();
	FEditorDelegates::BeginPIE.Remove(BeginPIE);
	FEditorDelegates::EndPIE.Remove(EndPIE);
}

void UBeamMicroservicesEditor::OnReady()
{
	Super::OnReady();
	if (Cli->IsInstalled())
	{
		BeginPIE = FEditorDelegates::BeginPIE.AddLambda([this](bool Cond)
		{
			const auto RoutingKeyMap = ConstructRoutingKeyMap();
			Backend->SetRoutingKeyMap(RoutingKeyMap);
			UE_LOG(LogBeamMicroservices, Display, TEXT("Preparing PIE with Routing Key: %s"), *RoutingKeyMap);
		});

		EndPIE = FEditorDelegates::EndPIE.AddLambda([this](bool Cond)
		{
			Backend->SetRoutingKeyMap(TEXT(""));
		});

		// Get this machine's routing key
		const auto GetRoutingKeyCommand = NewObject<UBeamCliFederationLocalKeyCommand>(this);
		GetRoutingKeyCommand->OnStreamOutput = [this](const TArray<UBeamCliFederationLocalKeyStreamData*>& Stream, const TArray<int64>&, const FBeamOperationHandle&)
		{
			for (UBeamCliFederationLocalKeyStreamData* LocalKeyStreamData : Stream)
				LocalRoutingKey = LocalKeyStreamData->RoutingKey;

			// After we have the routing key for this user and machine, set up a long-running command to get updates from the CLI about the state of microservices running locally. 
			const auto ListenForStandaloneRunningServicesCommand = NewObject<UBeamCliProjectPsCommand>(this);
			ListenForStandaloneRunningServicesCommand->OnStreamOutput = [this](const TArray<UBeamCliProjectPsStreamData*>& Stream, const TArray<int64>& Array, const FBeamOperationHandle& Op)
			{
				OnUpdateLocalStateReceived(Stream, Array, Op);
			};
			Cli->RunCommand(ListenForStandaloneRunningServicesCommand, {TEXT("-w")}, {});
		};
		Cli->RunCommandServer(GetRoutingKeyCommand, {}, {});
	}
}

UBeamMicroservicesEditor* UBeamMicroservicesEditor::GetSelf(const UObject* CallingContext)
{
	return GEditor->GetEditorSubsystem<UBeamMicroservicesEditor>();
}

FBeamOperationHandle UBeamMicroservicesEditor::DeployRemoteMicroservicesOperation(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds,
                                                                                  const FBeamOperationEventHandler& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->BeginOperation({Slot}, GetName(), OnOperationEvent);
	DeployMicroservices(EnableBeamoIds, DisableBeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::CPP_DeployRemoteMicroservicesOperation(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds,
                                                                                      const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->CPP_BeginOperation({Slot}, GetName(), OnOperationEvent);
	DeployMicroservices(EnableBeamoIds, DisableBeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::RunLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandler& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->BeginOperation({Slot}, GetName(), OnOperationEvent);
	RunHostMicroservices(BeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::CPP_RunLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->CPP_BeginOperation({Slot}, GetName(), OnOperationEvent);
	RunHostMicroservices(BeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::StopLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandler& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->BeginOperation({Slot}, GetName(), OnOperationEvent);
	StopHostMicroservices(BeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::CPP_StopLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->CPP_BeginOperation({Slot}, GetName(), OnOperationEvent);
	StopHostMicroservices(BeamoIds, Handle);
	return Handle;
}


bool UBeamMicroservicesEditor::TryGetFilteredListOfServices(TArray<FString> IncludedGroupNames, TArray<FString> ExcludedGroupNames, TEnumAsByte<ELocalMicroserviceRunningMethod> RunningStatusFilter,
                                                            TArray<UBeamMicroserviceLocalEditorView*>& FilteredServices)
{
	for (TTuple<FString, FLocalMicroserviceData> MicroserviceData : LocalMicroserviceData)
	{
		// If we don't pass in any included group filters, we want to default to including.
		auto bMatchIncludedGroupName = IncludedGroupNames.IsEmpty();
		for (FString GroupName : IncludedGroupNames)
			bMatchIncludedGroupName |= MicroserviceData.Value.ServiceGroups.Contains(GroupName) || IncludedGroupNames.Contains(TEXT("All"));

		// If we don't pass in any excluded group filters, we want to default to including.
		auto bMatchExcludedGroupName = ExcludedGroupNames.IsEmpty();
		for (FString GroupName : ExcludedGroupNames)
			bMatchExcludedGroupName &= !MicroserviceData.Value.ServiceGroups.Contains(GroupName);

		// If status filter is Any OR it matches the current status filter, we include it.
		auto bMatchRunningStatus = RunningStatusFilter == Any;
		bMatchRunningStatus |= MicroserviceData.Value.RunningState == RunningStatusFilter;

		// If we match the filters, make a view object for this.
		const auto bMatchFilters = bMatchIncludedGroupName && bMatchExcludedGroupName && bMatchRunningStatus;
		if (bMatchFilters)
		{
			auto ServiceView = NewObject<UBeamMicroserviceLocalEditorView>();
			ServiceView->BeamoId = MicroserviceData.Key;
			ServiceView->RunningState = MicroserviceData.Value.RunningState;
			ServiceView->ServiceGroups = MicroserviceData.Value.ServiceGroups;
			ServiceView->ServiceType = MicroService;
			MicroserviceData.Value.TargetsToRoutingKeys.GetKeys(ServiceView->AvailableTargets);
			ServiceView->SelectedTarget = MicroserviceData.Value.CurrentTarget;

			FilteredServices.Add(ServiceView);
		}
	}
	return true;
}

TArray<FString> UBeamMicroservicesEditor::GetServiceGroupFilterOptions() const
{
	TArray<FString> Options;
	for (const auto MicroserviceData : LocalMicroserviceData)
	{
		const auto Groups = MicroserviceData.Value.ServiceGroups;
		for (FString Group : Groups)
			Options.AddUnique(Group);
	}

	Options.Insert(TEXT("All"), 0);
	return Options;
}

bool UBeamMicroservicesEditor::OpenSwaggerDocs(FString BeamoId)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	if (!IsCurrentRoutingKeyValid(BeamoId))
	{
		UE_LOG(LogBeamMicroservices, Warning, TEXT("Target for service is not available. BEAMO_ID=%s, ROUTING_KEY=%s"), *BeamoId, *LocalMicroservice->CurrentTarget);
		return false;
	}

	// Prepare the command and validate that you are not trying to open a swagger docs for a service that is not available
	const auto RoutingKey = LocalMicroservice->TargetsToRoutingKeys[LocalMicroservice->CurrentTarget];
	TArray<FString> Params{BeamoId, TEXT("--routing-key"), RoutingKey};

	// Run the command
	const auto OpenSwaggerCommand = NewObject<UBeamCliProjectOpenSwaggerCommand>();
	Cli->RunCommandServer(OpenSwaggerCommand, Params, {});
	return true;
}

bool UBeamMicroservicesEditor::IsCurrentRoutingKeyValid(FString BeamoId)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	if (!LocalMicroservice)
		return false;

	return LocalMicroservice->TargetsToRoutingKeys.Contains(LocalMicroservice->CurrentTarget);
}

bool UBeamMicroservicesEditor::SetCurrentRoutingKey(FString BeamoId, FString Key)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	if (!ensureAlwaysMsgf(LocalMicroservice, TEXT("BeamoId not found in local microservices data. BEAMO_ID=%s"), *BeamoId))
		return false;

	if (!ensureAlwaysMsgf(LocalMicroservice->TargetsToRoutingKeys.Contains(Key), TEXT("RoutingKey not found in list of avaialable routing keys. BEAMO_ID=%s, ROUTING_KEY=%s"), *BeamoId, *Key))
		return false;

	LocalMicroservice->CurrentTarget = Key;
	return true;
}

FString UBeamMicroservicesEditor::ConstructRoutingKeyMap()
{
	TArray<FString> RoutingKeyMapEntries;
	for (const auto& MicroserviceData : LocalMicroserviceData)
	{
		const auto BeamoId = MicroserviceData.Key;
		if (!IsCurrentRoutingKeyValid(BeamoId))
		{
			UE_LOG(LogBeamMicroservices, Error, TEXT("Selected Target is not Valid. SERVICE=%s, TARGET=%s"), *BeamoId, *MicroserviceData.Value.CurrentTarget);
			continue;
		}

		const auto SelectedTarget = MicroserviceData.Value.CurrentTarget;
		const auto RoutingKey = MicroserviceData.Value.TargetsToRoutingKeys[SelectedTarget];
		if (!RoutingKey.IsEmpty())
			RoutingKeyMapEntries.Add(TEXT("micro_") + BeamoId + TEXT(":") + RoutingKey);
	}

	return FString::Join(RoutingKeyMapEntries, TEXT(","));
}


void UBeamMicroservicesEditor::DeployMicroservices(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds, const FBeamOperationHandle& Op) const
{
	const auto ServicesDeploy = NewObject<UBeamCliServicesDeployCommand>();
	ServicesDeploy->OnStreamOutput = [](const TArray<UBeamCliServicesDeployStreamData*>& Result,
	                                    const TArray<long long>&, const FBeamOperationHandle&)
	{
	};


	ServicesDeploy->OnRemoteProgressStreamOutput = [this](
		const TArray<UBeamCliServicesDeployRemoteProgressStreamData*>& Progress, const TArray<long long>&,
		const FBeamOperationHandle& Operation)
		{
			UE_LOG(LogBeamMicroservices, Display, TEXT("%s"), *Progress.Last()->BeamoId);
			RequestTracker->TriggerOperationEvent(Operation, OET_SUCCESS, FName("MICROSERVICE_REMOTE_DEPLOY_UPDATE"), Progress.Last()->BeamoId);
		};

	// Handle completing the operation
	ServicesDeploy->OnCompleted = [this](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
			RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
		else
			RequestTracker->TriggerOperationError(Operation, FString::FromInt(ResultCode));
	};

	// Prepare params to run the command with
	TArray<FString> Params{};
	if (!EnableBeamoIds.IsEmpty())
	{
		const auto Ids = FString::Printf(TEXT("--enable %s"), *FString::Join(EnableBeamoIds, TEXT(" ")));
		Params.Add(Ids);
	}
	if (!DisableBeamoIds.IsEmpty())
	{
		const auto Ids = FString::Printf(TEXT("--disable %s"), *FString::Join(DisableBeamoIds, TEXT(" ")));
		Params.Add(Ids);
	}
	// Kick of command.
	Cli->RunCommandServer(ServicesDeploy, Params, Op);
}

void UBeamMicroservicesEditor::RunHostMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op)
{
	const auto Cmd = NewObject<UBeamCliProjectRunCommand>();

	// Handle completing the operation
	Cmd->OnCompleted = [this, BeamoIds](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
		{
			for (FString BeamoId : BeamoIds)
			{
				if (ensureAlwaysMsgf(LocalMicroserviceData.Contains(BeamoId), TEXT("You should never see this.")))
				{
					LocalMicroserviceData.Find(BeamoId)->RunningState = RunningOnHost;
				}
			}
			RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
		}
		else
			RequestTracker->TriggerOperationError(Operation, FString::FromInt(ResultCode));
	};

	// Set up ids
	TArray<FString> Params = {};
	if (!BeamoIds.IsEmpty())
	{
		const auto Ids = FString::Printf(TEXT("--ids %s"), *FString::Join(BeamoIds, TEXT(" ")));
		Params.Add(Ids);
	}

	// Kick of command.
	Cli->RunCommandServer(Cmd, Params, Op);
}

void UBeamMicroservicesEditor::RunDockerMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op)
{
	const auto ServicesDeploy = NewObject<UBeamCliServicesRunCommand>();
	ServicesDeploy->OnStreamOutput = [](const TArray<UBeamCliServicesRunStreamData*>& Result, const TArray<long long>&, const FBeamOperationHandle&)
	{
		UE_LOG(LogBeamMicroservices, Display, TEXT("%s"), Result.Last()->Success ? TEXT("success") : TEXT("failure"));
	};

	ServicesDeploy->OnLocalProgressStreamOutput = [this](
		const TArray<UBeamCliServicesRunLocalProgressStreamData*>& Progress, const TArray<long long>&,
		const FBeamOperationHandle&)
		{
			const auto ProgressData = Progress.Last();

			// Update the local state of microservice data
			if (FMath::IsNearlyEqual(ProgressData->LocalDeployProgress, 100.0))
			{
				if (ensureAlwaysMsgf(LocalMicroserviceData.Contains(ProgressData->BeamoId), TEXT("You should never see this.")))
				{
					LocalMicroserviceData.Find(ProgressData->BeamoId)->RunningState = RunningOnDocker;
				}
			}
		};

	// Handle completing the operation
	ServicesDeploy->OnCompleted = [this](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
			RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
		else
			RequestTracker->TriggerOperationError(Operation, FString::FromInt(ResultCode));
	};


	// Set up ids
	TArray<FString> Params = {};
	if (!BeamoIds.IsEmpty())
	{
		const auto Ids = FString::Printf(TEXT("--ids %s"), *FString::Join(BeamoIds, TEXT(" ")));
		Params.Add(Ids);
	}

	// Kick of command.
	Cli->RunCommandServer(ServicesDeploy, Params, Op);
}

void UBeamMicroservicesEditor::StopHostMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op)
{
	const auto Cmd = NewObject<UBeamCliProjectStopCommand>();

	// Handle completing the operation
	Cmd->OnCompleted = [this, BeamoIds](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
		{
			for (const auto& BeamoId : BeamoIds)
			{
				if (ensureAlwaysMsgf(LocalMicroserviceData.Contains(BeamoId), TEXT("You should never see this.")))
				{
					LocalMicroserviceData.Find(BeamoId)->RunningState = Stopped;
				}
			}
			RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
		}
		else
			RequestTracker->TriggerOperationError(Operation, FString::FromInt(ResultCode));
	};


	// We expect you to always pass in the list of ids.
	checkf(!BeamoIds.IsEmpty(), TEXT("You should always specify ids when calling stop."))

	TArray<FString> Params = {};

	// Set up ids
	const auto Ids = FString::Printf(TEXT("--ids %s"), *FString::Join(BeamoIds, TEXT(" ")));
	Params.Add(Ids);


	// Kick of command.
	Cli->RunCommandServer(Cmd, Params, Op);
}

void UBeamMicroservicesEditor::StopDockerMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op)
{
	const auto ServicesDeploy = NewObject<UBeamCliServicesStopCommand>();

	// Handle completing the operation
	ServicesDeploy->OnCompleted = [this, BeamoIds](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
		{
			for (const auto& BeamoId : BeamoIds)
			{
				if (ensureAlwaysMsgf(LocalMicroserviceData.Contains(BeamoId), TEXT("You should never see this.")))
				{
					LocalMicroserviceData.Find(BeamoId)->RunningState = Stopped;
				}
			}
			RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
		}
		else
			RequestTracker->TriggerOperationError(Operation, FString::FromInt(ResultCode));
	};


	// We expect you to always pass in the list of ids.
	ensureAlwaysMsgf(!BeamoIds.IsEmpty(), TEXT("You should always specify ids when calling stop."));

	TArray<FString> Params = {};

	//Add container as the argument
	Params.Add(TEXT("container"));

	// Set up ids
	const auto Ids = FString::Printf(TEXT("--ids %s"), *FString::Join(BeamoIds, TEXT(" ")));
	Params.Add(Ids);


	// Kick of command.
	Cli->RunCommandServer(ServicesDeploy, Params, Op);
}

void UBeamMicroservicesEditor::OnUpdateLocalStateReceived(const TArray<UBeamCliProjectPsStreamData*>& Stream, const TArray<long long>&, const FBeamOperationHandle&)
{
	for (const UBeamCliProjectPsStreamData* ProjectStatusChange : Stream)
	{
		for (const auto& Service : ProjectStatusChange->Services)
		{
			const auto BeamoId = Service->Service;

			if (!LocalMicroserviceData.Contains(Service->Service))
			{
				UE_LOG(LogBeamMicroservices, Display, TEXT("Detected microservice. Registering it with the editor. BEAMO_ID=%s"), *BeamoId);
				LocalMicroserviceData.Add(BeamoId, FLocalMicroserviceData{
					                          BeamoId, Service->Groups,
					                          Stopped,
					                          false,
					                          {},
					                          {}
				                          });
			}

			// Get a reference to the data so we can update it...
			FLocalMicroserviceData& MicroserviceData = LocalMicroserviceData.FindChecked(BeamoId);

			// Make sure the Groups are up-to-date
			MicroserviceData.ServiceGroups = Service->Groups;

			// Reset the targets so that we can always rebuild them from the latest information
			MicroserviceData.TargetsToRoutingKeys.Reset();

			// Find out if the service is running and collect available routing keys
			for (const auto& AvailableRoute : Service->AvailableRoutes)
			{
				const auto RoutingKey = AvailableRoute->RoutingKey;

				for (const auto& Instance : AvailableRoute->Instances)
				{
					// Empty email, means this instance is the "realm" instance.
					if (Instance->StartedByAccountEmail == TEXT(""))
					{
						// We add the routing key
						MicroserviceData.TargetsToRoutingKeys.Add(TEXT("realm"), RoutingKey);
					}
					else
					{
						// Add the routing key
						MicroserviceData.TargetsToRoutingKeys.Add(Instance->StartedByAccountEmail, RoutingKey);

						// The service is running on the host machine
						if (Instance->LatestHostEvent)
						{
							MicroserviceData.RunningState = RunningOnHost;
						}

						// The service is running on docker
						if (Instance->LatestDockerEvent)
						{
							MicroserviceData.RunningState = RunningOnDocker;
						}

						// If the service is the LocalService, change the target for that service to be the one for this service instance.
						if (RoutingKey == LocalRoutingKey)
						{
							MicroserviceData.CurrentTarget = Instance->StartedByAccountEmail;
						}
					}
				}
			}

			if (!IsCurrentRoutingKeyValid(BeamoId))
			{
				if (MicroserviceData.TargetsToRoutingKeys.Contains(TEXT("realm"))) MicroserviceData.CurrentTarget = "realm";
				else MicroserviceData.CurrentTarget = "";
			}
		}
	}

	OnLocalMicroserviceUpdate.Broadcast();
}

void UBeamMicroservicesEditor::SplitByHostOrDocker(const TArray<FString>& BeamoIds, TArray<FString>& DockerBeamoIds, TArray<FString>& HostBeamoIds)
{
	for (FString BeamoId : BeamoIds)
	{
		if (LocalMicroserviceData.Contains(BeamoId))
		{
			const auto LocalMicroservice = LocalMicroserviceData.FindRef(BeamoId);
			if (LocalMicroservice.RunningState == RunningOnDocker)
				DockerBeamoIds.Add(BeamoId);
			if (LocalMicroservice.RunningState == RunningOnHost)
				HostBeamoIds.Add(BeamoId);
		}
	}
}
