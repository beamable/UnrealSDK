// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/UserDeveloperManager/BeamUserDeveloperManagerEditor.h"

#include <string>

#include "PIE/BeamPIEConfig.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserBatchCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerPsCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerRemoveUserCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerSaveUserCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerUpdateInfoCommand.h"


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

	BeamUserSlots->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
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


void UBeamUserDeveloperManagerEditor::TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& BeamOperationHandle, const UObject* Context)
{
	if (Context)
	{
		const auto WorldContext = GEngine->GetWorldContextFromWorld(Context->GetWorld());
		if (WorldContext && WorldContext->WorldType == EWorldType::PIE)
		{
			TArray<FBeamRealmUser> RealmUsers = {BeamRealmUser};

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
			SaveUserCommand->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle& Handler)
			{
				if (ResCode == 0)
				{
					RequestTracker->TriggerOperationSuccess(Handler, TEXT(""));
				}
				else
				{
					RequestTracker->TriggerOperationError(Handler, TEXT(""));
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

			auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

			BeamCli->RunCommandServer(SaveUserCommand, args, Handler);
		}
	}
}

void UBeamUserDeveloperManagerEditor::TriggerOnPreBeginPIE(const FBeamPIE_Settings* Settings)
{
	TMap<FBeamGamerTag, int32> TemplateAmount;
	for (auto AssignedUserKeyPair : Settings->AssignedUsers)
	{
		auto UserSlotHandle = AssignedUserKeyPair.Key;
		if (FBeamGamerTag GamerTag = AssignedUserKeyPair.Value; TemplateAmount.Contains(GamerTag))
		{
			TemplateAmount[GamerTag]++;
		}
		else
		{
			TemplateAmount.Add(GamerTag, 1);
		}
	}

	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	UBeamCliDeveloperUserManagerCreateUserBatchCommand* CreateUserBatchCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserBatchCommand>();

	CreateUserBatchCommand->OnStreamOutput = [this, Settings](const TArray<UBeamCliDeveloperUserManagerCreateUserBatchStreamData*>& Stream, const TArray<int64>&,
	                                                          const FBeamOperationHandle&)
	{
		auto Data = Stream.Last();

		TMap<long, TArray<UDeveloperUserDataStreamData*>> CreatedUserMap;

		for (UDeveloperUserDataStreamData* CreatedUser : Data->CreatedUsers)
		{
			if (CreatedUserMap.Contains(CreatedUser->TemplateGamerTag))
			{
				CreatedUserMap[CreatedUser->TemplateGamerTag].Add(CreatedUser);
			}
			else
			{
				CreatedUserMap.Add(CreatedUser->TemplateGamerTag, {CreatedUser});
			}
		}

		for (auto AssignedUserKeyPair : Settings->AssignedUsers)
		{
			auto CreatedUser = CreatedUserMap[AssignedUserKeyPair.Value.AsLong][0];

			BeamUserSlots->SaveSlot(AssignedUserKeyPair.Key.Slot, AssignedUserKeyPair.Key.PIEIndex,
			                        CreatedUser->GamerTag,
			                        CreatedUser->AccessToken,
			                        CreatedUser->RefreshToken,
			                        FDateTime::UtcNow().ToUnixTimestamp(),
			                        CreatedUser->ExpiresIn,
			                        CreatedUser->Cid,
			                        CreatedUser->Pid);

			CreatedUserMap[AssignedUserKeyPair.Value.AsLong].Remove(CreatedUser);
		}
	};
	CreateUserBatchCommand->OnCompleted = [this, Handler](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			RequestTracker->TriggerOperationError(Handler, TEXT(""));
		}
	};

	TArray<FString> GamerTags;
	TArray<FString> AmountList;

	for (auto TemplateGamerTagAmountKeyPair : TemplateAmount)
	{
		GamerTags.Add(TemplateGamerTagAmountKeyPair.Key.AsString);
		AmountList.Add(std::to_string(TemplateGamerTagAmountKeyPair.Value).data());
	}

	auto args = {
		FString::Printf(TEXT("--templates-list %s"), *FString::Join(GamerTags, TEXT(" "))),
		FString::Printf(TEXT("--amount-list %s"), *FString::Join(AmountList, TEXT(" "))),
		FString::Printf(TEXT("--rolling-buffer-size %d"), 10),
	};

	BeamCli->RunCommandServer(CreateUserBatchCommand, args, Handler);
}

void UBeamUserDeveloperManagerEditor::GetUsersWithFilter(FString NameFilter, FString TagFilter, TArray<UDeveloperUserDataStreamData*>& AllUsers)
{
	AllUsers.Empty();
	TArray<UDeveloperUserDataStreamData*> Result;
	for (auto DeveloperUser : LocalUserDeveloperCache)
	{
		Result.Add(DeveloperUser.Value);
	}

	if (NameFilter != TEXT(""))
	{
		Result.RemoveAll([NameFilter](UDeveloperUserDataStreamData* Data)
		{
			return !Data->Alias.Contains(NameFilter) && !FString::Printf(TEXT("%llu"), Data->GamerTag).Contains(NameFilter);
		});
	}

	if (TagFilter != TEXT(""))
	{
		TArray<FString> Tags;
		TagFilter.ParseIntoArray(Tags, TEXT(","));
		Result.RemoveAll([Tags](UDeveloperUserDataStreamData* Data)
		{
			bool ContainsAll = true;
			for (auto FilterTag : Tags)
			{
				FilterTag.TrimStartAndEndInline();

				bool Contains = false;
				for (auto Tag : Data->Tags)
				{
					Contains |= Tag.Contains(FilterTag);
				}
				ContainsAll &= Contains;
			}

			return !ContainsAll;
		});
	}

	Result.Sort([](const UDeveloperUserDataStreamData& A, const UDeveloperUserDataStreamData& B)
	{
		if (A.DeveloperUserType != B.DeveloperUserType)
		{
			return A.DeveloperUserType > B.DeveloperUserType;
		}

		return A.GamerTag > B.GamerTag;
	});

	AllUsers = Result;
}

void UBeamUserDeveloperManagerEditor::DeleteUser(FBeamGamerTag GamerTag)
{
	UBeamCliDeveloperUserManagerRemoveUserCommand* RemoveCommand = NewObject<UBeamCliDeveloperUserManagerRemoveUserCommand>();

	RemoveCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerRemoveUserStreamData*>& Stream, const TArray<int64>&,
	                                       const FBeamOperationHandle&)
	{
	};
	RemoveCommand->OnCompleted = [this](const int&, const FBeamOperationHandle&)
	{
	};

	auto args = {
		FString::Printf(TEXT("--gamer-tag \"%s\""), *GamerTag.AsString),
	};

	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	BeamCli->RunCommandServer(RemoveCommand, args, Handler);
}


void UBeamUserDeveloperManagerEditor::CopyTemplateToNewUserOperation(FBeamGamerTag TemplateGamerTag, EBeamDeveloperUserType DeveloperUserType, FBeamOperationEventHandler OperationEventHandle)
{
	auto OperationHandler = RequestTracker->BeginOperation({}, GetName(), OperationEventHandle);
	UBeamCliDeveloperUserManagerCreateUserCommand* CreateUserCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserCommand>();

	CreateUserCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerCreateUserStreamData*>& Stream, const TArray<int64>&,
	                                           const FBeamOperationHandle&)
	{
	};
	CreateUserCommand->OnCompleted = [this, OperationHandler](const int& Res, const FBeamOperationHandle&)
	{
		if (Res == 0)
		{
			RequestTracker->TriggerOperationSuccess(OperationHandler, TEXT(""));
		}
		else
		{
			RequestTracker->TriggerOperationError(OperationHandler, TEXT(""));
		}
	};

	auto args = {
		FString::Printf(TEXT("--template \"%s\""), *TemplateGamerTag.AsString),
		FString::Printf(TEXT("--alias \"%s\""), TEXT("")),
		FString::Printf(TEXT("--description \"%s\""), TEXT("")),
		FString::Printf(TEXT("--user-type %d"), DeveloperUserType),
	};

	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	BeamCli->RunCommandServer(CreateUserCommand, args, Handler);
}

void UBeamUserDeveloperManagerEditor::UpdateDeveloperUserInfo(FBeamGamerTag GamerTag, FString Alias, FString Description, TArray<FString> Tags)
{
	UBeamCliDeveloperUserManagerUpdateInfoCommand* UpdateInfoCommand = NewObject<UBeamCliDeveloperUserManagerUpdateInfoCommand>();

	UpdateInfoCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerUpdateInfoStreamData*>& Stream, const TArray<int64>&,
	                                           const FBeamOperationHandle&)
	{
	};
	UpdateInfoCommand->OnCompleted = [this](const int&, const FBeamOperationHandle&)
	{
	};

	FString TagsStr = "";

	for (auto tag : Tags)
	{
		TagsStr += FString::Printf(TEXT("--tags \"%s\" "), *tag);
	}

	auto args = {
		FString::Printf(TEXT("--gamer-tag \"%s\""), *GamerTag.AsString),
		FString::Printf(TEXT("--alias \"%s\""), *Alias),
		FString::Printf(TEXT("--description \"%s\""), *Description),
		FString::Printf(TEXT("%s"), *TagsStr),
	};


	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	BeamCli->RunCommandServer(UpdateInfoCommand, args, Handler);
}

void UBeamUserDeveloperManagerEditor::RunPsCommand(FBeamOperationHandle OperationHandle)
{
	auto WatchCommand = NewObject<UBeamCliDeveloperUserManagerPsCommand>();
	WatchCommand->OnStreamOutput = [this, OperationHandle](TArray<UBeamCliDeveloperUserManagerPsStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
	{
		const auto Data = Stream.Last();
		if (Data->EventType == EVT_TYPE_FullRebuild)
		{
			RebuildLocalDeveloperUserCache(Data->DeveloperUserReport->UpdatedUsers);
			if (RequestTracker->IsOperationActive(OperationHandle))
			{
				RequestTracker->TriggerOperationSuccess(OperationHandle, TEXT(""));
			}
			OnDeveloperUserInfoFullRebuild.Broadcast();
		}

		if (Data->EventType == EVT_TYPE_ChangedUserInfo)
		{
			UpdateLocalDeveloperUserCache(Data->DeveloperUserReport->UpdatedUsers, Data->DeveloperUserReport->DeletedUsers);

			OnDeveloperUserInfoChange.Broadcast();
		}
	};
	WatchCommand->OnCompleted = [this, WatchCommand, OperationHandle](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			// If we completed without receiving the first event, we trigger an error of the first event.
			if (WatchCommand->Stream.Num() == 0) RequestTracker->TriggerOperationError(OperationHandle, TEXT("Failed to fetch initial full-rebuild event"));

			const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
			BeamCli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
		}
	};

	const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
	BeamCli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
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
