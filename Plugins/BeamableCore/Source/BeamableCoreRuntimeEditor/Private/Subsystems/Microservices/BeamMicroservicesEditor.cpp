﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Microservices/BeamMicroservicesEditor.h"

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

void UBeamMicroservicesEditor::OnRealmInitialized()
{
	Super::OnRealmInitialized();
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

		// Let's make sure we know of all Microservices that exist when the editor opens (creating microservices requires an editor restart).		
		EnsureExistingServices();

		// Set up a long-running command to get updates from the CLI about the state of microservices running locally. 
		const auto ListenForStandaloneRunningServicesCommand = NewObject<UBeamCliProjectPsCommand>(this);
		ListenForStandaloneRunningServicesCommand->OnStreamOutput = [this](const TArray<UBeamCliProjectPsStreamData*>& Stream, const TArray<long long>& Array, const FBeamOperationHandle& Op)
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

FBeamOperationHandle UBeamMicroservicesEditor::UpdateRemoteMicroserviceStateOperation(const FBeamOperationEventHandler& OnOperationEvent)
{
	const auto Slot            = Editor->GetMainEditorSlot();
	const auto Handle          = RequestTracker->BeginOperation({Slot}, GetName(), OnOperationEvent);
	const auto CompleteHandler = [this](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
			RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
		else
			RequestTracker->TriggerOperationError(Operation, FString::FromInt(ResultCode));
	};
	UpdateRemoteMicroserviceState(CompleteHandler, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::CPP_UpdateRemoteMicroserviceStateOperation(const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	const auto Slot            = Editor->GetMainEditorSlot();
	const auto Handle          = RequestTracker->CPP_BeginOperation({Slot}, GetName(), OnOperationEvent);
	const auto CompleteHandler = [this](const int& ResultCode, const FBeamOperationHandle& Operation)
	{
		if (ResultCode == 0)
			RequestTracker->TriggerOperationSuccess(Operation, TEXT(""));
		else
			RequestTracker->TriggerOperationError(Operation, FString::FromInt(ResultCode));
	};
	UpdateRemoteMicroserviceState(CompleteHandler, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::DeployRemoteMicroservicesOperation(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds, const FBeamOperationEventHandler& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->BeginOperation({Slot}, GetName(), OnOperationEvent);
	DeployMicroservices(EnableBeamoIds, DisableBeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::CPP_DeployRemoteMicroservicesOperation(const TArray<FString>& EnableBeamoIds, const TArray<FString>& DisableBeamoIds, const FBeamOperationEventHandlerCode& OnOperationEvent)
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
	RunDockerMicroservices(BeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::CPP_RunLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->CPP_BeginOperation({Slot}, GetName(), OnOperationEvent);
	RunDockerMicroservices(BeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::StopLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandler& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->BeginOperation({Slot}, GetName(), OnOperationEvent);
	StopDockerMicroservices(BeamoIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMicroservicesEditor::CPP_StopLocalMicroservicesOperation(const TArray<FString>& BeamoIds, const FBeamOperationEventHandlerCode& OnOperationEvent)
{
	const auto Slot = Editor->GetMainEditorSlot();
	const auto Handle = RequestTracker->CPP_BeginOperation({Slot}, GetName(), OnOperationEvent);
	StopDockerMicroservices(BeamoIds, Handle);
	return Handle;
}

bool UBeamMicroservicesEditor::OpenSwaggerDocs(FString BeamoId, bool bIsRemote)
{
	const auto LocalMicroservice = LocalMicroserviceData.Find(BeamoId);
	const auto bIsLocalRunning = LocalMicroservice && LocalMicroservice->RunningState != Stopped;

	const auto RemoteMicroservice = RemoteMicroserviceData.Find(BeamoId);
	const auto bIsRemoteRunning = RemoteMicroservice && RemoteMicroservice->bIsEnabled;

	// Prepare the command and validate that you are not trying to open a swagger docs for a service that is not available
	TArray<FString> Params{BeamoId};
	if (bIsRemote)
	{
		if (!bIsRemoteRunning)
		{
			UE_LOG(LogBeamMicroservices, Warning, TEXT("Service %s is not running remotely, but you are trying to open it's remote swagger docs."), *BeamoId);
			return false;
		}
		Params.Add(TEXT("--remote"));
	}
	else
	{
		if (!bIsLocalRunning)
		{
			UE_LOG(LogBeamMicroservices, Warning, TEXT("Service %s is not running locally, but you are trying to open it's local swagger docs."), *BeamoId);
			return false;
		}
	}

	// Run the command
	if (bIsLocalRunning || bIsRemoteRunning)
	{
		const auto OpenSwaggerCommand = NewObject<UBeamCliProjectOpenSwaggerCommand>();
		Cli->RunCommandServer(OpenSwaggerCommand, Params, {});
	}

	return true;
}

void UBeamMicroservicesEditor::UpdateRemoteMicroserviceState(const TFunction<void(const int& ResCode, const FBeamOperationHandle& Op)>& OnComplete, const FBeamOperationHandle& Op)
{
	const auto ServicesPs = NewObject<UBeamCliServicesPsCommand>();
	ServicesPs->OnStreamOutput = [this](const TArray<UBeamCliServicesPsStreamData*>& Data, const TArray<long long>&,
	                                    const FBeamOperationHandle&)
	{
		const auto ServicesStateData = Data.Last();
		const auto Count = ServicesStateData->BeamoIds.Num();
		for (int i = 0; i < Count; ++i)
		{
			const auto BeamoId = ServicesStateData->BeamoIds[i];
			const auto bShouldEnableRemoteOnPublish = ServicesStateData->ShouldBeEnabledOnRemote[i];


			const auto RemoteServiceData = FRemoteMicroserviceData{
				BeamoId,
				bShouldEnableRemoteOnPublish
			};

			if (RemoteMicroserviceData.Contains(BeamoId))
				RemoteMicroserviceData[BeamoId] = RemoteServiceData;
			else
				RemoteMicroserviceData.Add(BeamoId, RemoteServiceData);
		}
	};

	// Handle completing the operation
	ServicesPs->OnCompleted = OnComplete;

	// Prepare params to run the command with
	TArray<FString> Params;
	Params.Add("--remote");

	// Kick of command.
	Cli->RunCommandServer(ServicesPs, Params, Op);
}

void UBeamMicroservicesEditor::EnsureExistingServices()
{
	const auto ServicesPs = NewObject<UBeamCliServicesPsCommand>();
	ServicesPs->OnStreamOutput = [this](const TArray<UBeamCliServicesPsStreamData*>& Data, const TArray<long long>&, const FBeamOperationHandle&)
	{
		const auto ServicesStateData = Data.Last();
		const auto Count = ServicesStateData->BeamoIds.Num();
		for (int i = 0; i < Count; ++i)
		{
			const auto BeamoId = ServicesStateData->BeamoIds[i];
			const auto bShouldEnableRemoteOnPublish = ServicesStateData->ShouldBeEnabledOnRemote[i];

			const auto RemoteServiceData = FLocalMicroserviceData{
				BeamoId,
				Stopped,
				bShouldEnableRemoteOnPublish
			};

			if (!LocalMicroserviceData.Contains(BeamoId))
				LocalMicroserviceData.Add(BeamoId, RemoteServiceData);
		}
	};

	// Handle completing the operation
	ServicesPs->OnCompleted = [ServicesPs](const int&, const FBeamOperationHandle&)
	{
	};

	// Run this synchronously.
	Cli->RunCommandServer(ServicesPs, {}, {});
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
						                          ProgressData->BeamoId, RunningOnDocker, false
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
												  BeamoId,
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
	const auto ProjectStatusChange = Stream.Last();
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
				                          BeamoId,
				                          ProjectStatusChange->IsContainer ? RunningOnDocker : RunningStandalone,
				                          false
			                          });
		}
		else
		{
			LocalMicroserviceData.Add(ProjectStatusChange->Service, FLocalMicroserviceData{
				                          BeamoId,
				                          Stopped,
				                          false
			                          });
		}
	}

	OnLocalMicroserviceUpdate.Broadcast();
}
