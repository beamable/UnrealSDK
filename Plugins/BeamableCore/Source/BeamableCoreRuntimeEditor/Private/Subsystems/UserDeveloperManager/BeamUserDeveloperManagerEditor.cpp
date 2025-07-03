// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/UserDeveloperManager/BeamUserDeveloperManagerEditor.h"

#include <string>

#include "PIE/BeamPIEConfig.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserBatchCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerPsCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerSaveUserCommand.h"


void UBeamUserDeveloperManagerEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	BeamUserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();

	BeamCli = GEditor->GetEditorSubsystem<UBeamCli>();

	UserSlotAuthenticatedHandler = BeamUserSlots->GlobalUserSlotAuthenticatedCodeHandler.AddUObject(this, &UBeamUserDeveloperManagerEditor::TriggerOnUserSlotAuthenticated);

	PreBeginPieHandler = FEditorDelegates::PreBeginPIE.AddUObject(this, &UBeamUserDeveloperManagerEditor::TriggerOnPreBeginPie);
	BeginPieHandler = FEditorDelegates::BeginPIE.AddUObject(this, &UBeamUserDeveloperManagerEditor::TriggerOnBeginPie);
	FEditorDelegates::StartPIE.AddLambda([](const bool IsSimulating)
	{
		UE_LOG(LogTemp, Display, TEXT("Trigger start pie"));
	});
}

void UBeamUserDeveloperManagerEditor::Deinitialize()
{
	Super::Deinitialize();
	FEditorDelegates::PreBeginPIE.Remove(PreBeginPieHandler);
	FEditorDelegates::BeginPIE.Remove(BeginPieHandler);
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
			if (RequestTracker->IsOperationActive(FirstEventOp))
			{
				RequestTracker->TriggerOperationSuccess(FirstEventOp, TEXT(""));
			}
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

			const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
			BeamCli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
		}
	};

	const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
	BeamCli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
}


void UBeamUserDeveloperManagerEditor::CreateDeveloperUser(const FBeamOperationHandle& BeamOperationHandle, FString alias, FString decription)
{
	UBeamCliDeveloperUserManagerCreateUserCommand* CreateUserCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserCommand>();
	CreateUserCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerCreateUserStreamData*>& Data, const TArray<int64>&,
	                                           const FBeamOperationHandle&)
	{
	};
	CreateUserCommand->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle&)
	{
	};

	auto args = {
		FString::Printf(TEXT("--alias %s"), *alias),
		FString::Printf(TEXT("--description %s"), *decription),
	};
	BeamCli->RunCommandServer(CreateUserCommand, args, BeamOperationHandle);
}

void UBeamUserDeveloperManagerEditor::CreateTemporaryDeveloperUser(TMap<FBeamGamerTag, int32> TemplateGamerTagAmount, const FBeamOperationHandle& BeamOperationHandle, TFunction<void(
	                                                                   TArray<UBeamCliDeveloperUserManagerCreateUserBatchStreamData*>& StreamData, TArray<int64>&
	                                                                   Timestamps, const FBeamOperationHandle& Op)> OnResult)
{
	UBeamCliDeveloperUserManagerCreateUserBatchCommand* CreateUserBatchCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserBatchCommand>();

	CreateUserBatchCommand->OnStreamOutput = OnResult;
	CreateUserBatchCommand->OnCompleted = [this, BeamOperationHandle](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			RequestTracker->TriggerOperationError(BeamOperationHandle, TEXT(""));
		}
	};

	TArray<FString> Identifiers;
	TArray<FString> AmountList;

	for (auto TemplateGamerTagAmountKeyPair : TemplateGamerTagAmount)
	{
		Identifiers.Add(TemplateGamerTagAmountKeyPair.Key.AsString);
		AmountList.Add(std::to_string(TemplateGamerTagAmountKeyPair.Value).data());
	}

	auto args = {
		FString::Printf(TEXT("--templates-list %s"), *FString::Join(Identifiers, TEXT(" "))),
		FString::Printf(TEXT("--amount-list %s"), *FString::Join(AmountList, TEXT(" "))),
		FString::Printf(TEXT("--rolling-buffer-size %d"), 10),
	};
	BeamCli->RunCommandServer(CreateUserBatchCommand, args, BeamOperationHandle);
}

void UBeamUserDeveloperManagerEditor::CaptureUser(TArray<FBeamRealmUser> RealmUsers, const FBeamOperationHandle& BeamOperationHandle)
{
	UBeamCliDeveloperUserManagerSaveUserCommand* SaveUserCommand = NewObject<UBeamCliDeveloperUserManagerSaveUserCommand>();
	SaveUserCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerSaveUserStreamData*>& Stream, const TArray<int64>&,
	                                         const FBeamOperationHandle&)
	{
		auto Data = Stream.Last();
		for (auto SavedUser : Data->SavedUsers)
		{
			UE_LOG(LogTemp, Display, TEXT("Saved user %lld"), SavedUser->GamerTag);
		}
	};
	SaveUserCommand->OnCompleted = [this, BeamOperationHandle](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			RequestTracker->TriggerOperationSuccess(BeamOperationHandle, TEXT(""));
		}
		else
		{
			RequestTracker->TriggerOperationError(BeamOperationHandle, TEXT(""));
		}
	};

	TArray<FString> AccessToken;
	TArray<FString> RefreshToken;
	TArray<FString> Pid;
	TArray<FString> Cid;
	TArray<FString> GamerTag;


	for (auto RealmUser : RealmUsers)
	{
		AccessToken.Add(RealmUser.AuthToken.AccessToken);
		RefreshToken.Add(RealmUser.AuthToken.RefreshToken);
		Pid.Add(RealmUser.RealmHandle.Pid.AsString);
		Cid.Add(RealmUser.RealmHandle.Cid.AsString);
		GamerTag.Add(RealmUser.GamerTag.AsString);
	}

	auto args = {
		FString::Printf(TEXT("--access-token %s"), *FString::Join(AccessToken, TEXT(" "))),
		FString::Printf(TEXT("--refresh-token %s"), *FString::Join(RefreshToken, TEXT(" "))),
		FString::Printf(TEXT("--pid %s"), *FString::Join(Pid, TEXT(" "))),
		FString::Printf(TEXT("--cid %s"), *FString::Join(Cid, TEXT(" "))),
		FString::Printf(TEXT("--gamer-tag %s"), *FString::Join(GamerTag, TEXT(" "))),
	};
	BeamCli->RunCommandServer(SaveUserCommand, args, BeamOperationHandle);
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

void UBeamUserDeveloperManagerEditor::UpdateLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> ToUpdate, TArray<int64> ToRemove)
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

	for (const auto& GamerTag : ToRemove)
	{
		if (LocalUserDeveloperCache.Contains(GamerTag))
		{
			LocalUserDeveloperCache.Remove(GamerTag);
		}
	}
}

void UBeamUserDeveloperManagerEditor::TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& BeamOperationHandle, const UObject* Context)
{
	if (Context)
	{
		const auto WorldContext = GEngine->GetWorldContextFromWorld(Context->GetWorld());
		if (WorldContext && WorldContext->WorldType == EWorldType::PIE)
		{
			auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});
			CaptureUser({BeamRealmUser}, Handler);
		}
	}
}

void UBeamUserDeveloperManagerEditor::TriggerOnPreBeginPie(const bool IsSimulating)
{
	auto BeamPIESettings = GetDefault<UBeamPIEConfig>()->AllSettings.FindByPredicate([this](FBeamPIE_Settings& S) { return S.SettingsId == GetDefault<UBeamPIEConfig>()->SelectedSettingsId; });

	const auto PlaySettings = GetDefault<ULevelEditorPlaySettings>();
	if (PlaySettings)
	{
		UE_LOG(LogTemp, Log, TEXT("Pre-Begin - Separate Server %d!"), PlaySettings->bLaunchSeparateServer ? 1 : 0);
		UE_LOG(LogTemp, Log, TEXT("Pre-Begin - Separate Server Launch Params %s!"), *PlaySettings->AdditionalServerLaunchParameters);

		int32 clientCount;
		PlaySettings->GetPlayNumberOfClients(clientCount);
		UE_LOG(LogTemp, Log, TEXT("Pre-Begin - Client Count %d!"), clientCount);

		uint16 port;
		PlaySettings->GetServerPort(port);
		FString MapName;
		PlaySettings->GetServerMapNameOverride(MapName);
		UE_LOG(LogTemp, Log, TEXT("Pre-Begin - Server Port %u!"), port);
		UE_LOG(LogTemp, Log, TEXT("Pre-Begin - Separate MapName %s!"), *MapName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Pre-Begin - No Params!"));
	}

	FBeamPIE_Settings FakeSettings = {};

	FakeSettings.AssignedUsers.Add(FBeamPIE_UserSlotHandle{0, FUserSlot("Test")}, FBeamGamerTag("1895013317660673"));
	FakeSettings.AssignedUsers.Add(FBeamPIE_UserSlotHandle{1, FUserSlot("Test")}, FBeamGamerTag("1895013271097349"));
	FakeSettings.AssignedUsers.Add(FBeamPIE_UserSlotHandle{2, FUserSlot("Test")}, FBeamGamerTag("1895013271097349"));
	FakeSettings.AssignedUsers.Add(FBeamPIE_UserSlotHandle{3, FUserSlot("Test")}, FBeamGamerTag("1895013271097349"));

	TMap<FBeamGamerTag, int32> TemplateAmount;
	for (auto AssignedUserKeyPair : FakeSettings.AssignedUsers)
	{
		auto UserSlotHandle = AssignedUserKeyPair.Key;
		FBeamGamerTag GamerTag = AssignedUserKeyPair.Value;
		if (TemplateAmount.Contains(GamerTag))
		{
			TemplateAmount[GamerTag]++;
		}
		else
		{
			TemplateAmount.Add(GamerTag, 1);
		}
	}

	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	CreateTemporaryDeveloperUser(TemplateAmount, Handler, [this, FakeSettings](const TArray<UBeamCliDeveloperUserManagerCreateUserBatchStreamData*>& Stream, const TArray<int64>&,
	                                                                           const FBeamOperationHandle&)
	{
		auto Data = Stream.Last();
		TMap<long, TArray<UDeveloperUserDataStreamData*>> CreatedUserMap;
		for (UDeveloperUserDataStreamData* CreatedUser : Data->CreatedUsers)
		{
			if (CreatedUserMap.Contains(CreatedUser->TemplatedGamerTag))
			{
				CreatedUserMap[CreatedUser->TemplatedGamerTag].Add(CreatedUser);
			}
			else
			{
				CreatedUserMap.Add(CreatedUser->TemplatedGamerTag, {CreatedUser});
			}
		}
		for (auto AssignedUserKeyPair : FakeSettings.AssignedUsers)
		{
			auto CreatedUser = CreatedUserMap[AssignedUserKeyPair.Value.AsLong][0];
			// Get namespacedid 
			BeamUserSlots->SetAuthenticationDataAtSlot(AssignedUserKeyPair.Key.Slot, CreatedUser->AccessToken, CreatedUser->RefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), CreatedUser->ExpiresIn, CreatedUser->Cid,
			                                           CreatedUser->Pid, nullptr);
			BeamUserSlots->SetGamerTagAtSlot(AssignedUserKeyPair.Key.Slot, CreatedUser->GamerTag, nullptr);
			BeamUserSlots->SaveSlot(AssignedUserKeyPair.Key.Slot, nullptr);

			CreatedUserMap[AssignedUserKeyPair.Value.AsLong].Remove(CreatedUser);
		}
	});

	UE_LOG(LogTemp, Display, TEXT("TriggerOnPreBeginPie called"));
}

void UBeamUserDeveloperManagerEditor::TriggerOnBeginPie(bool IsSimulating)
{
	UE_LOG(LogTemp, Display, TEXT("TriggerOnBeginPie called"));
}
