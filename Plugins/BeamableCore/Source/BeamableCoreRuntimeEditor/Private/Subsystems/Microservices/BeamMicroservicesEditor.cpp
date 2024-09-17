// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Microservices/BeamMicroservicesEditor.h"

#include "Subsystems/CLI/Autogen/BeamCliFederationListCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectRunCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectStopCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServicesStopCommand.h"

void UBeamMicroservicesEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Cli = Collection.InitializeDependency<UBeamCli>();
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
			const auto BeamMicroserviceClientSubsystems = GEngine->GetEngineSubsystemArray<UBeamMicroserviceClientSubsystem>();
			for (UBeamMicroserviceClientSubsystem* ClientSubsystem : BeamMicroserviceClientSubsystems)
			{
				const auto IsLocal = LocalMicroserviceData.Contains(ClientSubsystem->MicroserviceName);
				if (IsLocal && LocalMicroserviceData.FindRef(ClientSubsystem->MicroserviceName).RunningState != Stopped)
				{
					ClientSubsystem->Prefix = FPlatformProcess::ComputerName();
					UE_LOG(LogBeamMicroservices, Display, TEXT("%s"), *ClientSubsystem->Prefix)
				}
				else
				{
					UE_LOG(LogBeamMicroservices, Error, TEXT("%s"), *ClientSubsystem->Prefix)
				}
			}
		});

		EndPIE = FEditorDelegates::EndPIE.AddLambda([](bool Cond)
		{
			const auto BeamMicroserviceClientSubsystems = GEngine->GetEngineSubsystemArray<UBeamMicroserviceClientSubsystem>();
			for (UBeamMicroserviceClientSubsystem* ClientSubsystem : BeamMicroserviceClientSubsystems)
			{
				ClientSubsystem->Prefix = TEXT("");
			}
		});

		// Set up a long-running command to get updates from the CLI about the state of microservices running locally. 
		const auto ListenForStandaloneRunningServicesCommand = NewObject<UBeamCliProjectPsCommand>(this);
		ListenForStandaloneRunningServicesCommand->OnStreamOutput = [this](const TArray<UBeamCliProjectPsStreamData*>& Stream, const TArray<int64>& Array, const FBeamOperationHandle& Op)
		{
			OnUpdateLocalStateReceived(Stream, Array, Op);
		};
		Cli->RunCommand(ListenForStandaloneRunningServicesCommand, {TEXT("-w")}, {});
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
			ServiceView->AvailableRoutingKeys = MicroserviceData.Value.AvailableKeys;
			ServiceView->SelectedRoutingKey = MicroserviceData.Value.CurrentRoutingKey;

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

	// Prepare the command and validate that you are not trying to open a swagger docs for a service that is not available
	TArray<FString> Params{BeamoId, TEXT("--routing-key"), LocalMicroservice->CurrentRoutingKey};
	if (!LocalMicroservice->AvailableKeys.Contains(LocalMicroservice->CurrentRoutingKey))
	{
		UE_LOG(LogBeamMicroservices, Warning, TEXT("Target RoutingKey for service is not available. BEAMO_ID=%s, ROUTING_KEY=%s"), *BeamoId, *LocalMicroservice->CurrentRoutingKey);
		return false;
	}

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

	return LocalMicroservice->AvailableKeys.Contains(LocalMicroservice->CurrentRoutingKey);
}

bool UBeamMicroservicesEditor::SetCurrentRoutingKey(FString BeamoId, FString Key)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	ensureAlwaysMsgf(!LocalMicroservice, TEXT("BeamoId not found in local microservices data. BEAMO_ID=%s"), *BeamoId);
	if (!LocalMicroservice)
		return false;

	ensureAlwaysMsgf(LocalMicroservice->AvailableKeys.Contains(LocalMicroservice->CurrentRoutingKey), TEXT("RoutingKey not found in list of avaialable routing keys. BEAMO_ID=%s, ROUTING_KEY=%s"),
	                 *BeamoId, *Key);
	if (!LocalMicroservice->AvailableKeys.Contains(LocalMicroservice->CurrentRoutingKey))
		return false;

	LocalMicroservice->CurrentRoutingKey = Key;
	return true;
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
				if (LocalMicroserviceData.Contains(BeamoId))
				{
					LocalMicroserviceData.Find(BeamoId)->RunningState = RunningStandalone;
				}
				else
				{
					LocalMicroserviceData.Add(BeamoId,
					                          FLocalMicroserviceData{
						                          BeamoId, {}, RunningStandalone, false
					                          });
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
		const auto Ids = FString::Printf(TEXT("--ids %s --detach"), *FString::Join(BeamoIds, TEXT(" ")));
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
				if (LocalMicroserviceData.Contains(ProgressData->BeamoId))
				{
					LocalMicroserviceData.Find(ProgressData->BeamoId)->RunningState = RunningOnDocker;
				}
				else
				{
					LocalMicroserviceData.Add(ProgressData->BeamoId,
					                          FLocalMicroserviceData{
						                          ProgressData->BeamoId, {}, RunningOnDocker, false
					                          });
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
				if (LocalMicroserviceData.Contains(BeamoId))
				{
					LocalMicroserviceData.Find(BeamoId)->RunningState = Stopped;
				}
				else
				{
					LocalMicroserviceData.Add(BeamoId, FLocalMicroserviceData{
						                          BeamoId, {},
						                          Stopped,
						                          false
					                          });
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
				if (LocalMicroserviceData.Contains(BeamoId))
				{
					LocalMicroserviceData.Find(BeamoId)->RunningState = Stopped;
				}
				else
				{
					LocalMicroserviceData.Add(BeamoId, FLocalMicroserviceData{
						                          BeamoId, {},
						                          Stopped,
						                          false
					                          });
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
		const auto BeamoId = ProjectStatusChange->Service;

		if (LocalMicroserviceData.Contains(ProjectStatusChange->Service))
		{
			if (ProjectStatusChange->IsRunning)
			{
				LocalMicroserviceData.Find(BeamoId)->RunningState = ProjectStatusChange->IsContainer ? RunningOnDocker : RunningStandalone;
			}
			else
			{
				LocalMicroserviceData.Find(BeamoId)->RunningState = Stopped;
			}
		}
		else
		{
			if (ProjectStatusChange->IsRunning)
			{
				LocalMicroserviceData.Add(ProjectStatusChange->Service, FLocalMicroserviceData{
					                          BeamoId, ProjectStatusChange->Groups,
					                          ProjectStatusChange->IsContainer ? RunningOnDocker : RunningStandalone,
					                          false, ProjectStatusChange->RoutingKeys,
				                          });
			}
			else
			{
				LocalMicroserviceData.Add(ProjectStatusChange->Service, FLocalMicroserviceData{
					                          BeamoId, ProjectStatusChange->Groups,
					                          Stopped,
					                          false, ProjectStatusChange->RoutingKeys,
				                          });
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
			if (LocalMicroservice.RunningState == RunningStandalone)
				HostBeamoIds.Add(BeamoId);
		}
	}
}
