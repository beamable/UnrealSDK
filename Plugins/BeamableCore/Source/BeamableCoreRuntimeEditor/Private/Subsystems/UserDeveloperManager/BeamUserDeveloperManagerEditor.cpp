// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/UserDeveloperManager/BeamUserDeveloperManagerEditor.h"

#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerPsCommand.h"


void UBeamUserDeveloperManagerEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	BeamUserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
	BeamCli = GEditor->GetEditorSubsystem<UBeamCli>();

	UserSlotAuthenticatedHandler = BeamUserSlots->GlobalUserSlotAuthenticatedCodeHandler.AddUObject(this, &UBeamUserDeveloperManagerEditor::TriggerOnUserSlotAuthenticated);
}

void UBeamUserDeveloperManagerEditor::Deinitialize()
{
	Super::Deinitialize();
}

FBeamOperationHandle UBeamUserDeveloperManagerEditor::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	if (!BeamCli->IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("Editor Subsystem %s - Content depends on the CLI. It was not found locally. This system is not guaranteed to work because of this."), *GetName());
		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}

	// Start up the PS command for the current realm
	const auto Op = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	RunPsCommand(Op);

	return Op;
}

void UBeamUserDeveloperManagerEditor::RunPsCommand(FBeamOperationHandle FirstEventOp)
{
	auto WatchCommand = NewObject<UBeamCliDeveloperUserManagerPsCommand>();
	WatchCommand->OnStreamOutput = [this, FirstEventOp](TArray<UBeamCliDeveloperUserManagerPsStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
	{
		const auto Data = Stream.Last();
		if (Data->EventType == EVT_TYPE_FullRebuild)
		{
			RebuildLocalDeveloperUserCache(Data->ToUpdate);

			RequestTracker->TriggerOperationSuccess(FirstEventOp, TEXT(""));
			OnDeveloperUserInfoFullRebuild.Broadcast();
		}

		if (Data->EventType == EVT_TYPE_ChangedUserInfo)
		{
			UpdateLocalDeveloperUserCache(Data->ToUpdate, Data->ToRemove);

			OnDeveloperUserInfoChange.Broadcast();
		}
	};
	WatchCommand->OnCompleted = [this, WatchCommand, FirstEventOp](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			// If we completed without receiving the first event, we trigger an error of the first event.
			if (WatchCommand->Stream.Num() == 0) RequestTracker->TriggerOperationError(FirstEventOp, TEXT("Failed to fetch initial full-rebuild event"));

			const auto DuplicateCommand = DuplicateObject<UBeamCliDeveloperUserManagerPsCommand>(WatchCommand, GetTransientPackage());
			BeamCli->RunCommand(DuplicateCommand, {TEXT("-w")}, {});
		}
	};

	const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
	BeamCli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
}


void UBeamUserDeveloperManagerEditor::CreateDeveloperUser(const FBeamOperationHandle& BeamOperationHandle, FString alias, FString decription)
{
	UBeamCliDeveloperUserManagerCreateUserCommand* PullCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserCommand>();
	PullCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerCreateUserStreamData*>& Data, const TArray<int64>&,
	                                     const FBeamOperationHandle&)
	{
	};
	PullCommand->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle&)
	{
	};
	
	auto args = {
		FString::Printf(TEXT("--alias %s"), *alias),
		FString::Printf(TEXT("--description %s"), *decription),
	};
	BeamCli->RunCommandServer(PullCommand, args, BeamOperationHandle);
}

void UBeamUserDeveloperManagerEditor::CreateTemporaryDeveloperUser(FString TemplateGamerTag, const FBeamOperationHandle& BeamOperationHandle)
{
	UBeamCliDeveloperUserManagerCreateUserCommand* PullCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserCommand>();
	PullCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerCreateUserStreamData*>& Data, const TArray<int64>&,
										 const FBeamOperationHandle&)
	{
		
	};
	PullCommand->OnCompleted = [this, BeamOperationHandle](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			RequestTracker->TriggerOperationSuccess(BeamOperationHandle, TEXT(""));
		}else
		{
			RequestTracker->TriggerOperationError(BeamOperationHandle, TEXT(""));
		}
	};
	
	auto args = {
		FString::Printf(TEXT("--template %s"), *TemplateGamerTag),
	};
	BeamCli->RunCommandServer(PullCommand, args, BeamOperationHandle);
}

void UBeamUserDeveloperManagerEditor::GetAllUsers(TArray<UDeveloperUserDataStreamData*>& AllUsers)
{
	AllUsers.Empty();

	for (auto DeveloperUser : LocalUserDeveloperCache)
	{
		AllUsers.Add(DeveloperUser.Value);
	}
}


void UBeamUserDeveloperManagerEditor::RebuildLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> AllEntries)
{
	LocalUserDeveloperCache.Reset();

	for (const auto& Entry : AllEntries)
	{
		LocalUserDeveloperCache.Add(Entry->GamerTag, Entry);
	}
}

void UBeamUserDeveloperManagerEditor::UpdateLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> ToUpdate, TArray<UDeveloperUserDataStreamData*> ToRemove)
{
	for (const auto& Entry : ToUpdate)
	{
		if (LocalUserDeveloperCache.Contains(Entry->GamerTag))
		{
			LocalUserDeveloperCache[Entry->GamerTag] = Entry;
		}
		else
		{
			LocalUserDeveloperCache.Add(Entry->GamerTag, Entry);
		}
	}

	for (const auto& Entry : ToRemove)
	{
		if (LocalUserDeveloperCache.Contains(Entry->GamerTag))
		{
			LocalUserDeveloperCache.Remove(Entry->GamerTag);
		}
	}
}

void UBeamUserDeveloperManagerEditor::TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& BeamOperationHandle, const UObject* Context)
{
	// Login Guest -> Ser capturado -> copiar o state do target pro user -> copiar pro saved -> login cached
	// Get the user and use it to create a temporary user using the CLI

	if (Context)
	{
		const auto WorldContext = GEngine->GetWorldContextFromWorld(Context->GetWorld());
		if (WorldContext && WorldContext->WorldType == EWorldType::PIE)
		{
			if( !CapturedUsers.Contains(WorldContext->PIEInstance) ){
				CapturedUsers.Add( WorldContext->PIEInstance , {BeamRealmUser});
			}else{
				CapturedUsers[WorldContext->PIEInstance].Add( BeamRealmUser);
			}
		}
	}

}
