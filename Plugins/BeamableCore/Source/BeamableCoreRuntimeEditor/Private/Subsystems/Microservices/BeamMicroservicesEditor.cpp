// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Microservices/BeamMicroservicesEditor.h"

#include "Subsystems/CLI/Autogen/BeamCliFederationListCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliFederationLocalKeyCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliFederationLocalSettingsSetIFederatedGameServerCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectOpenMongoCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectRunCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectStopCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliProjectStorageEraseCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServicesStopCommand.h"

TArray<UBeamCliLogEntry*> UBeamMicroserviceLocalEditorView::GetFilteredLogs(TArray<FString> VisibleLogTypes, FString TextFilter)
{
	TArray<UBeamCliLogEntry*> Entries;
	Entries.Reserve(Logs.Num());
	for (const auto& Log : Logs)
	{
		const auto bMatchesLogType = VisibleLogTypes.Contains(Log->LogLevel);
		const auto bMatchesTextFilter = TextFilter.IsEmpty() || Log->Message.Contains(TextFilter);

		if (bMatchesLogType && bMatchesTextFilter)
			Entries.Add(Log);
	}

	return Entries;
}

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

FBeamOperationHandle UBeamMicroservicesEditor::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	// Refresh the editor user's email as that is the name of the Local Target.
	FBeamRealmUser EditorUser;
	Editor->GetMainEditorSlot(EditorUser);
	LocalTarget = EditorUser.Email;

	const auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	// Get this machine's routing key
	const auto GetRoutingKeyCommand = NewObject<UBeamCliFederationLocalKeyCommand>(this);
	GetRoutingKeyCommand->OnStreamOutput = [this, Handler](const TArray<UBeamCliFederationLocalKeyStreamData*>& Stream, const TArray<int64>&, const FBeamOperationHandle&)
	{
		RequestTracker->TriggerOperationSuccess(Handler, TEXT(""));
		for (UBeamCliFederationLocalKeyStreamData* LocalKeyStreamData : Stream)
			LocalRoutingKey = LocalKeyStreamData->RoutingKey;

		// After we have the routing key for this user and machine, set up a long-running command to get updates from the CLI about the state of microservices running locally. 
		const auto ListenForStandaloneRunningServicesCommand = NewObject<UBeamCliProjectPsCommand>(this);
		ListenForStandaloneRunningServicesCommand->OnStreamOutput = [this](TArray<UBeamCliProjectPsStreamData*>& Stream, TArray<int64>& Ts, const FBeamOperationHandle& Op)
		{
			OnUpdateLocalStateReceived(Stream, Ts, Op);
		};
		const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
		Cli->RunCommand(ListenForStandaloneRunningServicesCommand, {TEXT("-w"), ReqProcess}, {});
	};
	Cli->RunCommandServer(GetRoutingKeyCommand, {}, Handler);

	return Handler;
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
			ServiceView->ServiceType = MicroserviceData.Value.ServiceType;

			MicroserviceData.Value.TargetsToRoutingKeys.GetKeys(ServiceView->AvailableTargets);
			ServiceView->LocalTarget = LocalTarget;
			ServiceView->SelectedTarget = MicroserviceData.Value.CurrentTarget;
			ServiceView->FederationData = TMap(MicroserviceData.Value.TargetsToFederations);
			ServiceView->Logs = MicroserviceData.Value.Logs;

			FilteredServices.Add(ServiceView);
		}
	}
	return true;
}

TArray<FString> UBeamMicroservicesEditor::GetServiceGroupFilterOptions() const
{
	TArray<FString> Options;
	for (const auto& MicroserviceData : LocalMicroserviceData)
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

	TArray<FString> Params;
	// Prepare the command and validate that you are not trying to open a swagger docs for a service that is not available
	const auto RoutingKey = LocalMicroservice->TargetsToRoutingKeys[LocalMicroservice->CurrentTarget];
	if (!RoutingKey.IsEmpty())
		Params.Append({BeamoId, TEXT("--routing-key"), RoutingKey});
	else
		Params.Append({BeamoId, TEXT("--routing-key"), TEXT("\"\"")});

	// Tell the portal we are opening this from unreal
	Params.Append({TEXT("--src-tool"), TEXT("unreal")});

	// Run the command
	const auto OpenSwaggerCommand = NewObject<UBeamCliProjectOpenSwaggerCommand>();
	Cli->RunCommandServer(OpenSwaggerCommand, Params, {});
	return true;
}

bool UBeamMicroservicesEditor::OpenMongoExpress(FString BeamoId)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	if (LocalMicroservice->ServiceType != MicroStorage)
	{
		UE_LOG(LogBeamMicroservices, Warning, TEXT("Service is not a Storage. BEAMO_ID=%s"), *BeamoId);
		return false;
	}

	TArray<FString> Params{BeamoId};

	// Run the command	
	const auto OpenMongoExpressCommand = NewObject<UBeamCliProjectOpenMongoCommand>();
	Cli->RunCommandServer(OpenMongoExpressCommand, Params, {});
	return true;
}

bool UBeamMicroservicesEditor::ClearMongoLocalData(FString BeamoId)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	if (LocalMicroservice->ServiceType != MicroStorage)
	{
		UE_LOG(LogBeamMicroservices, Warning, TEXT("Service is not a Storage. BEAMO_ID=%s"), *BeamoId);
		return false;
	}

	TArray<FString> Params{BeamoId};

	// Run the command	
	const auto OpenMongoExpressCommand = NewObject<UBeamCliProjectStorageEraseCommand>();
	Cli->RunCommandServer(OpenMongoExpressCommand, Params, {});
	return true;
}

bool UBeamMicroservicesEditor::ClearLogs(FString BeamoId)
{
	if (FLocalMicroserviceData* LocalMicroservice = LocalMicroserviceData.Find(BeamoId))
	{
		LocalMicroservice->Logs.Reset();
		OnLocalMicroserviceUpdate.Broadcast();
		return true;
	}
	return false;
}

bool UBeamMicroservicesEditor::IsCurrentRoutingKeyValid(FString BeamoId)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	if (!LocalMicroservice)
		return false;

	// For local targets, we only consider them valid if they are running OR if there are no valid realm target.
	const auto Target = LocalMicroservice->CurrentTarget;
	if (LocalTarget == Target)
	{
		const auto ExistsAndItsRunning = LocalMicroservice->TargetsToRoutingKeys.Contains(Target) && LocalMicroservice->RunningState != Stopped;
		const auto NoRealmDeployedExists = !LocalMicroservice->TargetsToRoutingKeys.Contains(TEXT("realm"));
		return ExistsAndItsRunning || NoRealmDeployedExists;
	}

	return LocalMicroservice->TargetsToRoutingKeys.Contains(Target);
}

bool UBeamMicroservicesEditor::SetCurrentRoutingKey(FString BeamoId, FString Target)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	if (!ensureAlwaysMsgf(LocalMicroservice, TEXT("BeamoId not found in local microservices data. BEAMO_ID=%s"), *BeamoId))
		return false;

	if (!ensureAlwaysMsgf(LocalMicroservice->TargetsToRoutingKeys.Contains(Target), TEXT("RoutingKey not found in list of avaialable routing keys. BEAMO_ID=%s, ROUTING_KEY=%s"), *BeamoId, *Target))
		return false;

	LocalMicroservice->CurrentTarget = Target;

	// Synchronize the routing key map for Standalone Game PIE.
	SetRoutingKeyMapAsAdditionalLaunchArgs();
	
	return true;
}

void UBeamMicroservicesEditor::SetRoutingKeyMapAsAdditionalLaunchArgs()
{
	const auto Params = GetDefault<ULevelEditorPlaySettings>()->AdditionalLaunchParameters;
	auto NewParams = FString(Params);

	const auto RoutingKeyMap = ConstructRoutingKeyMap();
	const auto StartIdx = Params.Find(TEXT("beamable-routing-key-map"));

	// We have it in the string, first we remove it 
	if (StartIdx != INDEX_NONE)
	{
		auto EndIdx = Params.Find(TEXT(" "), ESearchCase::IgnoreCase, ESearchDir::FromStart, StartIdx);
		if (EndIdx == INDEX_NONE) EndIdx = Params.Len();
		NewParams.RemoveAt(StartIdx, EndIdx - StartIdx);
	}

	// Then we add the most recent routing key map	
	NewParams.Append(FString::Printf(TEXT(" %s=%s"), TEXT("beamable-routing-key-map"), *RoutingKeyMap));

	// Set the new parameters
	GetMutableDefault<ULevelEditorPlaySettings>()->AdditionalLaunchParameters = NewParams;
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
		// There is only ONE case where this can be false: the case of "No service deployed in the realm AND no locally running service"
		if (MicroserviceData.Value.TargetsToRoutingKeys.Contains(SelectedTarget))
		{
			const auto RoutingKey = MicroserviceData.Value.TargetsToRoutingKeys[SelectedTarget];
			if (!RoutingKey.IsEmpty())
				RoutingKeyMapEntries.Add((TEXT("micro_") + BeamoId + TEXT(":") + RoutingKey));
		}
	}

	return FString::Join(RoutingKeyMapEntries, TEXT(","));
}


void UBeamMicroservicesEditor::OnUpdateLocalStateReceived(const TArray<UBeamCliProjectPsStreamData*>& Stream, const TArray<long long>&, const FBeamOperationHandle&)
{
	const UBeamCliProjectPsStreamData* ProjectStatusChange = Stream.Last();

	for (const auto& Service : ProjectStatusChange->Services)
	{
		const auto BeamoId = Service->Service;

		const auto ServiceType = Service->ServiceType.Contains("service") ? MicroService : MicroStorage;
		// Handle Microservice's being turned on.			
		if (!LocalMicroserviceData.Contains(Service->Service))
		{
			UE_LOG(LogBeamMicroservices, Display, TEXT("Detected microservice. Registering it with the editor. BEAMO_ID=%s"), *BeamoId);
			auto NewServiceDetected = FLocalMicroserviceData{
				BeamoId, ServiceType, Service->Groups,
				Stopped,
				false,
				{},
				{},
				{},
				{},
				// We keep up 5.000 log lines in the history.
				{}
			};
			NewServiceDetected.Logs.Reserve(5000);
			LocalMicroserviceData.Add(BeamoId, NewServiceDetected);
		}

		// Get a reference to the data so we can update it...
		FLocalMicroserviceData& MicroserviceData = LocalMicroserviceData.FindChecked(BeamoId);

		// Make sure the Groups are up-to-date
		MicroserviceData.ServiceGroups = Service->Groups;

		// Reset the targets so that we can always rebuild them from the latest information
		MicroserviceData.TargetsToRoutingKeys.Reset();
		MicroserviceData.TargetsToFederations.Reset();

		// Find out if the service is running and collect available routing keys
		for (const auto& AvailableRoute : Service->AvailableRoutes)
		{
			const auto RoutingKey = AvailableRoute->RoutingKey;

			// Let's get the federation data for this target.
			FLocalFederationPerTargetData TargetData;
			for (UFederationInstanceStreamData* Federation : AvailableRoute->Federations)
			{
				FLocalFederationIdData FederationIdData;
				FederationIdData.FederationId = Federation->FederationId;
				for (int i = 0; i < Federation->FederationTypes.Num(); ++i)
				{
					const auto FederationType = Federation->FederationTypes[i];
					const auto FederationLocalSettings = Federation->LocalSettings[i];

					FLocalFederationData FedData;
					FedData.Type = static_cast<EBeamFederationType>(StaticEnum<EBeamFederationType>()->GetValueByNameString("BEAM_" + FederationType, EGetByNameFlags::CheckAuthoredName));
					switch (FedData.Type)
					{
					case EBeamFederationType::BEAM_IFederatedGameServer:
						FedData.LocalSettings_FederatedGamerServer = NewObject<UBeamCliFederationLocalSettingsGetIFederatedGameServerStreamData>();
						FedData.LocalSettings_FederatedGamerServer->BeamDeserialize(FederationLocalSettings);
						break;
					default:
						break;
					}

					FederationIdData.Federations.Add(FedData);
				}

				TargetData.Federations.Add(FederationIdData);
			}

			// If we know there are no running instances of the service, we still want to display the local user's target on the list so that the user can configure it.					
			if (ServiceType == MicroService && !AvailableRoute->KnownToBeRunning)
			{
				MicroserviceData.RunningState = Stopped;

				// Keep track of the federation data for each selectable target.
				MicroserviceData.TargetsToRoutingKeys.Add(LocalTarget, RoutingKey);

				// Keep track of the federation data for each selectable target.
				TargetData.Target = LocalTarget;
				MicroserviceData.TargetsToFederations.Add(LocalTarget, TargetData);

				// Stop the tail log command if its there
				StopLogTail(&MicroserviceData);
			}
			// This is how we know if micro-storages are up and running.
			else if (ServiceType == MicroStorage && AvailableRoute->KnownToBeRunning)
			{
				MicroserviceData.RunningState = RunningOnDocker;
			}
			// This is how we know if a micro storage is not running (we don't get instances for them). 
			else if (ServiceType == MicroStorage && !AvailableRoute->KnownToBeRunning)
			{
				MicroserviceData.RunningState = Stopped;
			}

			// For each running instance with this routing key
			for (const auto& Instance : AvailableRoute->Instances)
			{
				// Empty email, means this instance is the "realm" instance.
				const auto Target = Instance->StartedByAccountEmail == TEXT("") ? TEXT("realm") : Instance->StartedByAccountEmail;
				MicroserviceData.TargetsToRoutingKeys.Add(Target, RoutingKey);

				// Keep track of the federation data for each selectable target.
				TargetData.Target = Target;
				MicroserviceData.TargetsToFederations.Add(Target, TargetData);

				// Let's keep track of the local-dev's state 
				if (Target == LocalTarget)
				{
					// The service is running on the host machine
					if (AvailableRoute->KnownToBeRunning && Instance->LatestHostEvent)
					{
						MicroserviceData.RunningState = RunningOnHost;
						SetupLogTail(&MicroserviceData);
					}

					// The service is running on docker
					else if (AvailableRoute->KnownToBeRunning && Instance->LatestDockerEvent)
					{
						MicroserviceData.RunningState = RunningOnDocker;
						SetupLogTail(&MicroserviceData);
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
			else MicroserviceData.CurrentTarget = LocalTarget;
		}
	}

	// Ensure that the additional launch args are up-to-date with the locally running services.
	SetRoutingKeyMapAsAdditionalLaunchArgs();
	OnLocalMicroserviceUpdate.Broadcast();
}

void UBeamMicroservicesEditor::SaveFederationProperties(FString ServiceId, FString FedId, FLocalFederationData Federation)
{
	auto Cmd = NewObject<UBeamCliFederationLocalSettingsSetIFederatedGameServerCommand>();
	TArray<FString> Params;
	Params.Add(TEXT("--beamo-id"));
	Params.Add(ServiceId);
	Params.Add(TEXT("--fed-id"));
	Params.Add(FedId);
	if (Federation.Type == EBeamFederationType::BEAM_IFederatedGameServer)
	{
		if (Federation.LocalSettings_FederatedGamerServer->ContentIds.Num())
		{
			FString ContentFilter = FString::Join(Federation.LocalSettings_FederatedGamerServer->ContentIds, TEXT(" "));
			Params.Add(TEXT("--content-ids"));
			Params.Add(ContentFilter);
		}
	}


	Cmd->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle& Op)
	{
		if (ResCode != 0)
			UE_LOG(LogBeamMicroservices, Display, TEXT("Found a problem saving this. Try using the CLI command to run it for more details."))
		else
			UE_LOG(LogBeamMicroservices, Display, TEXT("Successfully saved your local settings for this service."))
	};

	Cli->RunCommandServer(Cmd, Params, {});
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

	// Grab the logs for the service...
	Cmd->OnLogEntriesStreamOutput = [this, BeamoIds](UBeamCliLogEntry* Log, const int64, const FBeamOperationHandle& Op)
	{
		for (FString BeamoId : BeamoIds)
		{
			auto LoggingService = LocalMicroserviceData.Find(BeamoId);
			AppendToLogs(LoggingService, {Log});
		}
	};

	// Handle completing the operation
	Cmd->OnCompleted = [this, BeamoIds](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0) RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
		else RequestTracker->TriggerOperationError(Operation, FString::FromInt(ResultCode));
	};

	// Set up ids
	TArray<FString> Params = {TEXT("--detach"), TEXT("--emit-log-streams"), TEXT("--no-client-gen")};
	if (!BeamoIds.IsEmpty())
	{
		const auto Ids = FString::Printf(TEXT("--ids %s"), *FString::Join(BeamoIds, TEXT(" ")));
		Params.Add(Ids);
	}
	Params.Add(FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId()));

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
				const auto BeamoId = ProgressData->BeamoId;
				if (ensureAlwaysMsgf(LocalMicroserviceData.Contains(BeamoId), TEXT("You should never see this.")))
				{
					auto RunningService = LocalMicroserviceData.Find(BeamoId);
					RunningService->RunningState = RunningOnDocker;
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

void UBeamMicroservicesEditor::RunStorageObject(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op)
{
	//UBeamCLiProject	
}

void UBeamMicroservicesEditor::StopHostMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op)
{
	const auto Cmd = NewObject<UBeamCliProjectStopCommand>();

	// Stop the tail log command if it's there
	for (const auto& BeamoId : BeamoIds)
	{
		if (auto Service = LocalMicroserviceData.Find(BeamoId))
		{
			StopLogTail(Service);
		}
	}

	// Get the log output
	Cmd->OnLogEntriesStreamOutput = [this, BeamoIds](UBeamCliLogEntry* Entry, const int64&, const FBeamOperationHandle&)
	{
		for (FString BeamoId : BeamoIds)
		{
			auto Service = LocalMicroserviceData.Find(BeamoId);
			AppendToLogs(Service, {Entry});
		}
	};

	// Handle completing the operation
	Cmd->OnCompleted = [this, BeamoIds](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
		{
			for (const auto& BeamoId : BeamoIds)
			{
				if (ensureAlwaysMsgf(LocalMicroserviceData.Contains(BeamoId), TEXT("You should never see this.")))
				{
					auto Service = LocalMicroserviceData.Find(BeamoId);
					Service->RunningState = Stopped;
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
	Params.Add(TEXT("--emit-log-streams"));


	// Kick of command.
	Cli->RunCommandServer(Cmd, Params, Op);
}

void UBeamMicroservicesEditor::StopDockerMicroservices(const TArray<FString>& BeamoIds, const FBeamOperationHandle& Op)
{
	const auto Cmd = NewObject<UBeamCliServicesStopCommand>();

	// Stop the tail log command if it's there
	for (const auto& BeamoId : BeamoIds)
	{
		if (auto Service = LocalMicroserviceData.Find(BeamoId))
		{
			StopLogTail(Service);
		}
	}

	// Get the log output
	Cmd->OnLogEntriesStreamOutput = [this, BeamoIds](UBeamCliLogEntry* Entry, const int64&, const FBeamOperationHandle&)
	{
		for (FString BeamoId : BeamoIds)
		{
			auto Service = LocalMicroserviceData.Find(BeamoId);
			AppendToLogs(Service, {Entry});
		}
	};

	// Handle completing the operation
	Cmd->OnCompleted = [this, BeamoIds](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
		{
			for (const auto& BeamoId : BeamoIds)
			{
				if (ensureAlwaysMsgf(LocalMicroserviceData.Contains(BeamoId), TEXT("You should never see this.")))
				{
					auto Service = LocalMicroserviceData.Find(BeamoId);
					Service->RunningState = Stopped;
					Cli->StopCommand(Service->TailLogsCommand);
					Service->TailLogsCommand = nullptr;
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
	Params.Add(TEXT("--emit-log-streams"));


	// Kick of command.
	Cli->RunCommandServer(Cmd, Params, Op);
}


void UBeamMicroservicesEditor::SetupLogTail(FLocalMicroserviceData* RunningService)
{
	const auto BeamoId = RunningService->BeamoId;
	if (!RunningService->TailLogsCommand)
	{
		RunningService->TailLogsCommand = NewObject<UBeamCliProjectLogsCommand>();
		RunningService->TailLogsCommand->OnStreamOutput = [this, BeamoId](const TArray<UBeamCliProjectLogsStreamData*>& Arr, const TArray<int64>&, const FBeamOperationHandle&)
		{
			auto LoggingService = LocalMicroserviceData.Find(BeamoId);
			TArray<UBeamCliLogEntry*> Entries;
			for (const auto& LogStream : Arr)
			{
				UBeamCliLogEntry* Log = NewObject<UBeamCliLogEntry>();
				Log->LogLevel = LogStream->LogLevel;
				Log->Message = LogStream->Message;
				FDefaultValueHelper::ParseInt64(LogStream->TimeStamp, Log->Timestamp);

				Entries.Add(Log);
			}
			AppendToLogs(LoggingService, Entries);
		};
		const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
		Cli->RunCommand(RunningService->TailLogsCommand, {BeamoId, ReqProcess}, {});
	}
}

void UBeamMicroservicesEditor::AppendToLogs(FLocalMicroserviceData* RunningService, const TArray<UBeamCliLogEntry*>& Log)
{
	if (RunningService->Logs.Num() > 10000)
		RunningService->Logs.RemoveAt(0, Log.Num());

	RunningService->Logs.Append(Log);

	OnLocalMicroserviceUpdate.Broadcast();
}

void UBeamMicroservicesEditor::StopLogTail(FLocalMicroserviceData* RunningService)
{
	if (RunningService->TailLogsCommand)
	{
		Cli->StopCommand(RunningService->TailLogsCommand);
		RunningService->TailLogsCommand = nullptr;
	}
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
