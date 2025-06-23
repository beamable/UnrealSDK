// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamEditorContent.h"

#include "EditorStyleSet.h"
#include "Content/BeamContentCache.h"
#include "Content/DownloadContentState.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Kismet/KismetStringLibrary.h"
#include "Misc/FileHelper.h"
#include "Serialization/ObjectWriter.h"
#include "Settings/ProjectPackagingSettings.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliContentLocalManifestCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentPsCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentPublishCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentPullCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentResolveCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentSaveCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentSyncCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentTagSetCommand.h"
#include "Widgets/Notifications/SNotificationList.h"

void UBeamEditorContent::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Display, TEXT("Initializing Beam Editor - Content System!"))

	ContentApi = GEngine->GetEngineSubsystem<UBeamContentApi>();
	Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	EditorAssetSubsystem = Collection.InitializeDependency<UEditorAssetSubsystem>();


	// Grab all existing ContentObject classes so we can present them as options in the editing UI and correctly parse them.
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UBeamContentObject::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			FName TypeName = It->GetFName();
			FString ContentTypeId = It->GetDefaultObject<UBeamContentObject>()->BuildContentTypeString();

			UE_LOG(LogTemp, Display, TEXT("Initializing Beam Editor Content System - TYPE=%s, TYPE_ID=%s"),
			       *TypeName.ToString(), *ContentTypeId);
			AllContentTypes.Add(*It);
			AllContentTypeNames.Add(MakeShared<FName>(TypeName));
			ContentTypeStringToContentClass.Add(ContentTypeId, *It);
			ContentClassToContentTypeString.Add(*It, ContentTypeId);
		}
	}
	AllContentTypes.Sort([](const UClass& A, const UClass& B)
	{
		FString ContentTypeIdA = A.GetDefaultObject<UBeamContentObject>()->BuildContentTypeString();
		FString ContentTypeIdB = B.GetDefaultObject<UBeamContentObject>()->BuildContentTypeString();
		return ContentTypeIdA.Compare(ContentTypeIdB) < 0;
	});
	AllContentTypeNames.Sort([](const TSharedPtr<FName>& A, const TSharedPtr<FName>& B)
	{
		return A.Get()->Compare(*B.Get()) < 0;
	});
}


void UBeamEditorContent::Deinitialize()
{
	Super::Deinitialize();
	FEditorDelegates::PreBeginPIE.Remove(OnWillEnterPIE);
}

FBeamOperationHandle UBeamEditorContent::InitializeWhenEditorReady()
{
	// We get the operation for this. 
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Initializing after Unreal Editor is ready"), *GetName())

	// By default, just return an empty completed operation
	const auto Op = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), {});

	// Ensure we are properly configured with at least one path for baked content.
	const auto EditorSettings = GetMutableDefault<UBeamEditorSettings>();

	// If we are initializing the Editor Settings
	if (EditorSettings->CookedManifestsPath.IsEmpty())
	{
		EditorSettings->CookedManifestsPath.Add(FDirectoryPath{DefaultBeamableCookedContentManifestsPath});
		// We save this out to the default editor configuration so that this default is always versioned (unless we save config with these parameters, changes to settings objects are local to this developer)
		EditorSettings->SaveConfig(CPF_Config, *EditorSettings->GetDefaultConfigFilename());
	}

	// Ensure that all directories in the cooked manifest paths array exist.
	for (const auto& CookedManifestsPath : EditorSettings->CookedManifestsPath)
	{
		if (!EditorAssetSubsystem->DoesDirectoryExist(CookedManifestsPath.Path))
		{
			EditorAssetSubsystem->MakeDirectory(CookedManifestsPath.Path);
		}
	}

	RequestTracker->TriggerOperationSuccess(Op, {});
	return Op;
}

FBeamOperationHandle UBeamEditorContent::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	// Ensure the CLI is installed
	if (!Cli->IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("Editor Subsystem %s - Content depends on the CLI. It was not found locally. This system is not guaranteed to work because of this."), *GetName());
		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}

	// Start up the PS command for the current realm
	const auto Op = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	RunPsCommand(Op);

	// For now, we just fetch all the manifests that exist.	
	return Op;
}

FBeamOperationHandle UBeamEditorContent::PublishManifestOperation(FBeamContentManifestId ManifestId, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Op = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), OnOperationEvent);
	PublishManifest(ManifestId, Op);
	return Op;
}

FBeamOperationHandle UBeamEditorContent::CPP_PublishManifestOperation(FBeamContentManifestId ManifestId, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Op = RequestTracker->CPP_BeginOperation({Editor->GetMainEditorSlot()}, GetName(), OnOperationEvent);
	PublishManifest(ManifestId, Op);
	return Op;
}

void UBeamEditorContent::GetLocalManifestIds(TArray<FBeamContentManifestId>& Keys) const
{
	Keys.Reserve(LocalManifestCache.Num());
	LocalManifestCache.GetKeys(Keys);
}

bool UBeamEditorContent::TryGetLocalManifestById(const FBeamContentManifestId& Id, ULocalContentManifestStreamData*& Manifest)
{
	if (LocalManifestCache.Contains(Id))
	{
		Manifest = LocalManifestCache.FindChecked(Id);
		return true;
	}

	return false;
}

void UBeamEditorContent::PublishManifest(FBeamContentManifestId ContentManifestId, FBeamOperationHandle Op)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();


	FSlowTask* SlowTask = new FSlowTask(1, FText::FromString(TEXT("Publishing Content...")));
	SlowTask->Initialize();
	SlowTask->MakeDialog();

	UBeamCliContentPublishCommand* PublishCommand = NewObject<UBeamCliContentPublishCommand>();
	PublishCommand->OnCompleted = [this, PublishCommand, SlowTask, Op](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		}
		else
		{
			const auto Err = NewObject<UBeamCliErrorData>();
			Err->Errors = TArray<FBeamCliError>{PublishCommand->Errors};
			const auto Str = Err->Errors[0].Message;
			RequestTracker->TriggerOperationErrorWithData(Op, Str, Err);
		}

		SlowTask->Destroy();
		delete SlowTask;
	};

	TArray<FString> Params;
	Params.Append({TEXT("--manifest-ids"), ContentManifestId.AsString});

	Cli->RunCommandServer(PublishCommand, Params, {});
	SlowTask->EnterProgressFrame();
}

bool UBeamEditorContent::DownloadManifest(FBeamContentManifestId ContentManifestId, FString& Err)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();

	FSlowTask* SlowTask = new FSlowTask(1, FText::FromString(TEXT("Downloading Content...")));
	SlowTask->Initialize();
	SlowTask->MakeDialog();

	bool Res = false;
	UBeamCliContentPullCommand* PullCommand = NewObject<UBeamCliContentPullCommand>();
	PullCommand->OnStreamOutput = [this](const TArray<UBeamCliContentPullStreamData*>& Data, const TArray<int64>&,
	                                     const FBeamOperationHandle&)
	{
		for (const auto& D : Data)
			RebuildLocalManifestCache(D->Manifests);
	};
	PullCommand->OnCompleted = [this, &Res, &Err, SlowTask](const int& ResCode, const FBeamOperationHandle&)
	{
		Res = ResCode == 0;
		Err = Res ? TEXT("") : TEXT("FAILED_DOWNLOAD");
		SlowTask->Destroy();
		delete SlowTask;
	};

	Cli->RunCommandSync(PullCommand, {FString::Printf(TEXT("--manifest-ids %s"), *ContentManifestId.AsString)});
	SlowTask->EnterProgressFrame();

	return Res;
}

bool UBeamEditorContent::ForceSyncContent(FBeamContentManifestId ContentManifestId, TArray<FBeamContentId> Ids)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();

	// Do nothing unless ids were specified
	if (Ids.Num() == 0)
		return true;


	UBeamCliContentSyncCommand* SyncCommand = NewObject<UBeamCliContentSyncCommand>();;
	SyncCommand->OnCompleted = [this, ContentManifestId, Ids](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			OnContentRevert.Broadcast(ContentManifestId, Ids);
		}
		else
		{
			OnContentRevertFailed.Broadcast(ContentManifestId, Ids);
		}
	};

	// Get all the Content Ids in the form "type.id1 type.id2".
	auto IdsStr = TArray<FString>{};
	for (FBeamContentId Id : Ids) IdsStr.Add(Id.AsString);
	auto IdsParam = Ids.Num() > 0 ? FString::Printf(TEXT("%s"), *FString::Join(IdsStr, TEXT(" "))) : TEXT("");

	// Build the CLI args
	TArray<FString> Params;
	Params.Append({TEXT("--manifest-ids"), ContentManifestId.AsString});
	Params.Append({TEXT("--filter"), IdsParam});
	Params.Append({TEXT("--filter-type"), TEXT("ExactIds")});
	Params.Append({TEXT("--sync-created")});
	Params.Append({TEXT("--sync-modified")});
	Params.Append({TEXT("--sync-conflicts")});
	Cli->RunCommandServer(SyncCommand, Params, {});

	return true;
}

bool UBeamEditorContent::ResolveConflict(FBeamContentManifestId ContentManifestId, TArray<FBeamContentId> Ids, bool bUseRealm)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();

	// Do nothing unless ids were specified
	if (Ids.Num() == 0)
		return true;


	UBeamCliContentResolveCommand* ResolveCommand = NewObject<UBeamCliContentResolveCommand>();;
	ResolveCommand->OnCompleted = [this, ContentManifestId, Ids](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			OnContentRevert.Broadcast(ContentManifestId, Ids);
		}
		else
		{
			OnContentRevertFailed.Broadcast(ContentManifestId, Ids);
		}
	};

	// Get all the Content Ids in the form "type.id1 type.id2".
	auto IdsStr = TArray<FString>{};
	for (FBeamContentId Id : Ids) IdsStr.Add(Id.AsString);
	auto IdsParam = Ids.Num() > 0 ? FString::Printf(TEXT("%s"), *FString::Join(IdsStr, TEXT(" "))) : TEXT("");

	// Build the CLI args
	TArray<FString> Params;
	Params.Append({TEXT("--manifest-ids"), ContentManifestId.AsString});
	Params.Append({TEXT("--filter"), IdsParam});
	Params.Append({TEXT("--filter-type"), TEXT("ExactIds")});
	Params.Append({TEXT("--use"), bUseRealm ? TEXT("realm") : TEXT("local")});
	Cli->RunCommandServer(ResolveCommand, Params, {});

	return true;
}

UClass* UBeamEditorContent::GetContentTypeByTypeId(FString TypeId)
{
	if (const auto ClassPtr = ContentTypeStringToContentClass.Find(TypeId))
		return *ClassPtr;

	return nullptr;
}

void UBeamEditorContent::FindSubTypesOfContentType(const TArray<FString>& TypeNames, TMap<FString, FArrayOfString>& OutMappings)
{
	for (const auto& Pair : ContentTypeStringToContentClass)
	{
		const FString CurrentId = Pair.Key;
		for (const auto& TypeName : TypeNames)
		{
			if (CurrentId.StartsWith(TypeName))
			{
				if (!OutMappings.Contains(TypeName))
				{
					TArray<FString> Array;
					OutMappings.Add(TypeName, FArrayOfString{Array});
				}
				OutMappings[TypeName].Values.Add(CurrentId);
			}
		}
	}

	for (TPair<FString, FArrayOfString> OutMapping : OutMappings)
		OutMapping.Value.Values.Sort();
}

bool UBeamEditorContent::CreateNewContent(const FBeamContentManifestId& ManifestId, const FString& ContentName,
                                          TSubclassOf<UBeamContentObject> ContentObjectSubType, TArray<FString> Tags,
                                          UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	ContentObject = NewObject<UBeamContentObject>(this, ContentObjectSubType.Get());

	// We add it to the object and to the local manifest.
	const auto TypeName = ContentObject->GetClass()->GetFName().ToString();

	auto RepeatedNameCount = 0;
	auto NewContentId = ContentName.IsEmpty()
		                    ? FString::Format(TEXT("{0}.{1}_{2}"), {
			                                      ContentObject->BuildContentTypeString(), TypeName, RepeatedNameCount
		                                      })
		                    : FString::Format(TEXT("{0}.{1}"), {ContentObject->BuildContentTypeString(), ContentName});

	auto Entries = LocalManifestCache.FindRef(ManifestId)->Entries;
	while (Entries.FindByPredicate([NewContentId](ULocalContentManifestEntryStreamData* Data)
	{
		return Data->FullId.Equals(NewContentId);
	}))
	{
		RepeatedNameCount += 1;
		NewContentId = ContentName.IsEmpty()
			               ? FString::Format(TEXT("{0}.{1}_{2}"), {
				                                 ContentObject->BuildContentTypeString(), TypeName, RepeatedNameCount
			                                 })
			               : FString::Format(TEXT("{0}.{1}_{2}"), {
				                                 ContentObject->BuildContentTypeString(), ContentName, RepeatedNameCount
			                                 });
	}

	// Sets the ID and Tags based on the manifest row.
	ContentObject->Id = NewContentId;
	ContentObject->Tags.Append(Tags);
	if (!SaveContentObject(ManifestId, ContentObject, "", false))
	{
		ErrMsg = FString::Format(TEXT("Failed to save the content object {0}"), {NewContentId});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}
	LoadedContentObjects.Add(ContentObject->Id, ContentObject);
	return true;
}

bool UBeamEditorContent::GetContent(const FBeamContentManifestId& ManifestId, FBeamContentId ContentId,
                                    UBeamContentObject*& ContentObject)
{
	FString Err;
	const auto bRes = GetContentForEditing(ManifestId, ContentId, ContentObject, Err);
	if (!bRes)
	{
		UE_LOG(LogTemp, Verbose, TEXT("Fallback Content Getter: Failed to find content with ID=%s from Manifest=%s."),
		       *ContentId.AsString, *ManifestId.AsString)
	}
	return bRes;
}

bool UBeamEditorContent::GetContentForEditing(const FBeamContentManifestId& ManifestId, FBeamContentId EditObjectId,
                                              UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	const auto EditingTable = LocalManifestCache.FindRef(ManifestId);
	if (!EditingTable)
	{
		ErrMsg = FString::Format(
			TEXT(
				"Trying to load a content object from a Manifest={0} that is not loaded. Ignore this during packaging."),
			{ManifestId.AsString});
		UE_LOG(LogBeamContent, Display, TEXT("%s"), *ErrMsg);
		return false;
	}

	const auto Entries = EditingTable->Entries;
	if (!Entries.FindByPredicate([EditObjectId](ULocalContentManifestEntryStreamData* data)
	{
		return data->FullId.Equals(EditObjectId.AsString);
	}))
	{
		ErrMsg = FString::Format(
			TEXT("Trying to load a content object that doesn't exist in this manifest. CONTENT_ID={0}"),
			{EditObjectId.AsString});
		UE_LOG(LogBeamContent, Verbose, TEXT("%s"), *ErrMsg);
		return false;
	}

	if (!TryLoadContentObject(ManifestId, EditObjectId, ContentObject))
	{
		ErrMsg = FString::Format(
			TEXT("Trying to load a content object that doesn't exist. CONTENT_ID={0}"), {EditObjectId.AsString});
		UE_LOG(LogBeamContent, Verbose, TEXT("%s"), *ErrMsg);
		return false;
	}

	ErrMsg.Empty();
	return true;
}

bool UBeamEditorContent::SaveContentObject(const FBeamContentManifestId& ManifestId,
                                           UBeamContentObject* EditingObject,
                                           FString PropertyName,
                                           bool bIgnoreReferenceManifest)
{
	// Get the ID and properties for this 
	FString Id = EditingObject->Id;
	FString PropertiesJsonContent;
	EditingObject->ToPropertiesJson(PropertiesJsonContent);

	// Tags are saved using a different command from the CLI - Check: ContentTagSetCommand
	if (!PropertyName.Equals("Tags"))
	{
		auto SaveCmd = NewObject<UBeamCliContentSaveCommand>();
		SaveCmd->OnCompleted = [this, ManifestId, Id](const int& ResCode, const FBeamOperationHandle&)
		{
			// Trigger a callback saying that a piece of content was modified
			if (ResCode == 0)
			{
				OnContentSaved.Broadcast(ManifestId, {Id});
			}
			else
			{
				OnContentSavedFailed.Broadcast(ManifestId, {Id});
			}
		};

		TArray<FString> Params;
		Params.Append({TEXT("--manifest-ids"), ManifestId.AsString});
		Params.Append({TEXT("--content-ids"), Id});
		Params.Append({TEXT("--content-properties"), FString::Printf(TEXT("%s"), *PropertiesJsonContent)});
		if (bIgnoreReferenceManifest)
			Params.Append({TEXT("--force")});

		Cli->RunCommandServer(SaveCmd, Params, {});
	}
	else
	{
		auto SetTagCmd = NewObject<UBeamCliContentTagSetCommand>();
		SetTagCmd->OnCompleted = [this, ManifestId, Id](const int& ResCode, const FBeamOperationHandle&)
		{
			// Trigger a callback saying that a piece of content was modified
			if (ResCode == 0)
			{
				OnContentSaved.Broadcast(ManifestId, {Id});
			}
			else
			{
				OnContentSavedFailed.Broadcast(ManifestId, {Id});
			}
		};


		TArray<FString> Params;
		Params.Append({FString::Printf(TEXT("\"%s\""), *UKismetStringLibrary::JoinStringArray(EditingObject->Tags, TEXT(",")))});
		Params.Append({TEXT("--manifest-ids"), ManifestId.AsString});
		Params.Append({TEXT("--filter"), Id});
		Params.Append({TEXT("--filter-type"), TEXT("ExactIds")});
		// If there's no tag in the field we pass the clear
		if (EditingObject->Tags.Num() == 0)
		{
			Params.Append({TEXT("--clear")});
		}


		Cli->RunCommandServer(SetTagCmd, Params, {});
	}

	return true;
}

bool UBeamEditorContent::DeleteContentObject(const FBeamContentManifestId& ManifestId, FBeamContentId Id,
                                             FString& ErrMsg)
{
	const auto Entries = LocalManifestCache[ManifestId]->Entries;
	if (const auto Entry = Entries.FindByPredicate([Id](ULocalContentManifestEntryStreamData* Data)
	{
		return Data->FullId.Equals(Id.AsString);
	}))
	{
		const auto FilePath = (*Entry)->JsonFilePath;
		IFileManager& FileManager = IFileManager::Get();
		const auto bDeleted = FileManager.Delete(*FilePath);
		if (bDeleted) return true;

		ErrMsg = FString::Format(TEXT("Failed to delete the content object {0}"), {Id.AsString});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}

	ErrMsg = FString::Format(TEXT("Failed to delete the content object {0}"), {Id.AsString});
	UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
	return false;
}

bool UBeamEditorContent::TryRenameContent(const FBeamContentManifestId& ManifestId, const FBeamContentId& ContentId,
                                          const FString& NewContentName, FText& Err)
{
	UBeamContentObject* Obj;
	const auto bContentFound = GetContent(ManifestId, ContentId, Obj);
	ensureAlways(bContentFound);

	if (!IsValidContentName(NewContentName, Err))
		return false;

	const FString ContentTypeString = Obj->BuildContentTypeString();
	const FString NewId = ContentTypeString + TEXT(".") + NewContentName;

	const FBeamContentId NewContentId = FBeamContentId{NewId};

	const auto OldContentPath = GetJsonBlobPath(ContentId.AsString, ManifestId);
	const auto NewContentPath = GetJsonBlobPath(NewContentId.AsString, ManifestId);
	const auto bNewNameIsAvailable = !IFileManager::Get().FileExists(*NewContentPath);
	if (!bNewNameIsAvailable)
	{
		Err = FText::FromString(TEXT("The provided content id is already in use."));
		return false;
	}

	if (!IFileManager::Get().Move(*NewContentPath, *OldContentPath))
	{
		Err = FText::FromString(TEXT("Failed renaming the file."));
		return true;
	}

	return true;
}

bool UBeamEditorContent::TryGetFilteredListOfContent(const FBeamContentManifestId ManifestId, const FString& NameFilter,
                                                     const FString& TypeFilter,
                                                     const EBeamLocalContentStatus& ContentStatusFilter,
                                                     TArray<UBeamContentLocalView*>& FoundLocalContent)
{
	if (!LocalManifestCache.Contains(ManifestId))
		return false;

	const auto manifest = LocalManifestCache[ManifestId];

	TArray<FString> Names;
	TArray<FString> Ids;
	TArray<FString> Types;
	TArray<bool> IsInConflicts;
	TArray<UBeamContentObject*> ObjectsInManifest;
	TArray<EBeamLocalContentStatus> StatusesInManifest;
	auto Rows = manifest->Entries;

	for (const auto Row : Rows)
	{
		const auto bPassNameFilter = NameFilter.IsEmpty() || Row->Name.Contains(NameFilter);
		const auto bPassTypeFilter = TypeFilter.IsEmpty() || (ContentTypeStringToContentClass.Contains(Row->TypeName) && ContentTypeStringToContentClass[Row->TypeName]->GetName().Contains(TypeFilter));
		const auto bPassStatusFilter = (static_cast<uint8>(Row->CurrentStatus) & static_cast<uint8>(ContentStatusFilter)) > 0;

		if (bPassNameFilter && bPassTypeFilter && bPassStatusFilter)
		{
			Ids.Add(Row->FullId);
			Names.Add(Row->Name);
			Types.Add(Row->TypeName);
			IsInConflicts.Add(Row->IsInConflict);
			StatusesInManifest.Add(static_cast<EBeamLocalContentStatus>(Row->CurrentStatus));

			UBeamContentObject* Obj = nullptr;
			FString Err;
			GetContent(ManifestId, Row->FullId, Obj);
			ObjectsInManifest.Add(Obj);
		}
	}

	// Convert them into the Local View
	for (int i = 0; i < ObjectsInManifest.Num(); ++i)
	{
		FoundLocalContent.Add(NewObject<UBeamContentLocalView>());
		FoundLocalContent[FoundLocalContent.Num() - 1]->ContentFullId = FText::FromString(Ids[i]);
		FoundLocalContent[FoundLocalContent.Num() - 1]->ContentName = FText::FromString(Names[i]);
		FoundLocalContent[FoundLocalContent.Num() - 1]->ContentTypeName = FText::FromString(Types[i]);
		FoundLocalContent[FoundLocalContent.Num() - 1]->LocalStatus = StatusesInManifest[i];
		FoundLocalContent[FoundLocalContent.Num() - 1]->ContentObject = ObjectsInManifest[i];
		FoundLocalContent[FoundLocalContent.Num() - 1]->bIsInConflict = IsInConflicts[i];
	}

	//Content needs to be sorted to as following : newly created content/modified/unmodified/deletions
	FoundLocalContent.Sort([](const UBeamContentLocalView& BeamContent1, const UBeamContentLocalView& BeamContent2)
	{
		if (BeamContent1.LocalStatus == BeamContent2.LocalStatus)
			return BeamContent1.ContentName.ToString() < BeamContent2.ContentName.ToString();
		else if (BeamContent1.LocalStatus == EBeamLocalContentStatus::Beam_LocalContentCreated)
			return true;
		else if (BeamContent1.LocalStatus == EBeamLocalContentStatus::Beam_LocalContentModified && BeamContent2.LocalStatus != EBeamLocalContentStatus::Beam_LocalContentCreated)
			return true;
		else if (BeamContent1.LocalStatus == EBeamLocalContentStatus::Beam_LocalContentUpToDate &&
			BeamContent2.LocalStatus != EBeamLocalContentStatus::Beam_LocalContentCreated && BeamContent2.LocalStatus != EBeamLocalContentStatus::Beam_LocalContentModified)
			return true;

		return false;
	});

	return true;
}

FString UBeamEditorContent::GetJsonBlobPath(FString RowName, FBeamContentManifestId ManifestId)
{
	return DefaultBeamableProjectContentObjects / GetDefault<UBeamCoreSettings>()->TargetRealm.Pid.AsString / ManifestId.AsString / RowName + TEXT(".json");
}


void UBeamEditorContent::BakeManifest(FBeamContentManifestId Manifest)
{
	UBeamContentCache* Cache = NewObject<UBeamContentCache>(this);

	Cache->ManifestId = Manifest;

	for (const auto& Entry : LocalManifestCache[Manifest]->Entries)
	{
		const auto Hash = Entry->Hash;
		const bool bNotInCache = !Cache->Hashes.Contains(Entry->FullId);
		const bool bInCacheButModified = Cache->Hashes.Contains(Entry->FullId) && !Cache->Hashes[Entry->FullId].Equals(Hash);
		if (bNotInCache || bInCacheButModified)
		{
			// Create a new BeamContentObject instance of each content Object
			UBeamContentObject* Content;
			LoadContentObjectInstance(LocalManifestCache[Manifest], Entry->FullId, Content, Cache);

			// Add it to the BCC_ BeamRuntimeContentCache.
			Cache->Cache.Add(Entry->FullId, Content);
			Cache->Hashes.Add(Entry->FullId, Hash);
		}
	}

	auto CoreSettings = GetMutableDefault<UBeamCoreSettings>();

	const FString BakedContentPath = FPaths::ProjectContentDir() + CoreSettings->BakedContentFolderName + "/" +
		CoreSettings->GlobalBakedContentFileName;

	TArray<uint8> SerializedData;
	FBeamMemoryWriter Writer(SerializedData, true);


	Cache->SerializeToBinary(Writer, ContentTypeStringToContentClass, ContentClassToContentTypeString);

	if (FFileHelper::SaveArrayToFile(SerializedData, *BakedContentPath))
	{
		UE_LOG(LogBeamContent, Log, TEXT("Saved new baked content."));
	}
	else
	{
		UE_LOG(LogBeamContent, Error, TEXT("Error while baking new content."));
	}

	//Add the baked folder to the project settings so that it doesnt get packaged in the .PAK and gets coppied as it is with the packaged game
	if (UProjectPackagingSettings* PackagingSettings = GetMutableDefault<UProjectPackagingSettings>())
	{
		bool PathAlreadyAdded = false;
		for (FDirectoryPath& DirectoryPath : PackagingSettings->DirectoriesToAlwaysStageAsNonUFS)
		{
			if (DirectoryPath.Path == CoreSettings->BakedContentFolderName)
			{
				PathAlreadyAdded = true;
			}
		}
		if (!PathAlreadyAdded)
		{
			PackagingSettings->DirectoriesToAlwaysStageAsNonUFS.Add(FDirectoryPath{CoreSettings->BakedContentFolderName});

			PackagingSettings->SaveConfig(CPF_Config, *PackagingSettings->GetDefaultConfigFilename());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to retrieve packaging settings."));
	}
}

void UBeamEditorContent::RebuildLocalManifestCache(const TArray<ULocalContentManifestStreamData*>& Data)
{
	for (const auto& d : Data)
	{
		ManifestIds.AddUnique(d->ManifestId);
		LocalManifestCache.Add(d->ManifestId, d);
		UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Found Manifest with Id %s"), *GetName(),
		       *d->ManifestId)
	}
}

void UBeamEditorContent::UpdateLocalManifestCache(ULocalContentManifestStreamData* ToUpdate, ULocalContentManifestStreamData* ToClear)
{
	const auto ManifestId = FBeamContentManifestId{ToUpdate->ManifestId};

	if (auto Existing = LocalManifestCache.FindOrAdd(ManifestId, ToUpdate))
	{
		// Let's start by removing all entries in the update/remove
		Existing->Entries.RemoveAll([ToUpdate, ToClear](const ULocalContentManifestEntryStreamData* ContentEntry)
		{
			bool bContainedInToUpdate = ToUpdate->Entries.ContainsByPredicate([&ContentEntry](const ULocalContentManifestEntryStreamData* E)
			{
				return ContentEntry->FullId == E->FullId;
			});

			bool bContainedInToClear = ToClear->Entries.ContainsByPredicate([&ContentEntry](const ULocalContentManifestEntryStreamData* E)
			{
				return ContentEntry->FullId == E->FullId;
			});
			return bContainedInToUpdate || bContainedInToClear;
		});

		// Then... we re-add the updated versions of the asset.
		for (const auto Entry : ToUpdate->Entries)
		{
			Existing->Entries.Add(DuplicateObject<ULocalContentManifestEntryStreamData>(Entry, GetTransientPackage()));
			if (LoadedContentObjects.Contains(Entry->FullId))
			{
				auto CachedObjInstance = LoadedContentObjects[Entry->FullId];
				const auto FilePath = Entry->JsonFilePath;
				FString FileContents;
				if (FFileHelper::LoadFileToString(FileContents, *FilePath))
				{
					CachedObjInstance->FromBasicJson(FileContents);
					CachedObjInstance->Id = Entry->FullId;
					CachedObjInstance->Version = Entry->Hash;
				}
			}
		}
	}
}

void UBeamEditorContent::RunPsCommand(FBeamOperationHandle FirstEventOp)
{
	auto WatchCommand = NewObject<UBeamCliContentPsCommand>();
	WatchCommand->OnStreamOutput = [this, FirstEventOp](TArray<UBeamCliContentPsStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
	{
		const auto Data = Stream.Last();
		if (Data->EventType == EVT_TYPE_FullRebuild)
		{
			RebuildLocalManifestCache(Data->RelevantManifestsAgainstLatest);
			RequestTracker->TriggerOperationSuccess(FirstEventOp, TEXT(""));
			OnContentFullRebuild.Broadcast();
		}

		if (Data->EventType == EVT_TYPE_RemotePublished)
		{
			UE_LOG(LogBeamContent, Display,
			       TEXT(
				       "Remote content publish detected. PUBLISHER=%s, CONTENT_ID=%s"
			       ), *Data->PublisherEmail,
			       *FString::Join(Data->SyncReports[0]->ConflictingContents, TEXT(", ")));


			// Bubble this up to the UI so we can add a UE UI-notification with relevant information.
			if (Data->SyncReports.Num() > 0)
			{
				const auto SyncReport = Data->SyncReports[0];

				const auto ConflictsDetectedOnIds = SyncReport->ConflictingContents;
				const auto AutoSyncedIds = SyncReport->AutoSynchedContents;
				const auto DeletedCreatedContentIds = SyncReport->DeletedCreatedContents;
				const auto ReferenceUpdatedIds = SyncReport->ReferenceUpdatedContents;

				const auto Title = FString(TEXT("[Beamable] Content Published to Realm - By ")) + Data->PublisherEmail;
				auto Body = FString(TEXT(""));

				if (ConflictsDetectedOnIds.Num() > 0)
				{
					Body += TEXT("Conflicts: \n");
					for (FString ConflictsDetectedOnId : ConflictsDetectedOnIds)
						Body += FString::Printf(TEXT("\t- %s\n"), *ConflictsDetectedOnId);
				}

				if (AutoSyncedIds.Num() > 0)
				{
					Body += TEXT("Downloaded Content: \n");
					for (FString AutoSyncedId : AutoSyncedIds)
						Body += FString::Printf(TEXT("\t- %s\n"), *AutoSyncedId);
				}

				if (DeletedCreatedContentIds.Num() > 0)
				{
					Body += TEXT("Deleted Content: \n");
					for (FString DeletedCreatedContentId : DeletedCreatedContentIds)
						Body += FString::Printf(TEXT("\t- %s\n"), *DeletedCreatedContentId);
				}

				// Create and send the notification
				FNotificationInfo Info{FText::FromString(Title)};
				Info.SubText = FText::FromString(Body);

				//Set a default expire duration and other parameters
				Info.ExpireDuration = 20.0f;
				Info.FadeOutDuration = 2.0f;
				Info.Image = ConflictsDetectedOnIds.Num() > 0 ? FAppStyle::GetBrush(TEXT("Icons.Warning")) : FAppStyle::GetBrush(TEXT("Icons.Success"));
				Info.ForWindow = FSlateApplication::Get().GetActiveTopLevelWindow();

				//And call Add Notification, this is pretty much it!
				FSlateNotificationManager::Get().AddNotification(Info);
			}


			RebuildLocalManifestCache(Data->RelevantManifestsAgainstLatest);
			OnContentRemotePublish.Broadcast();
		}

		if (Data->EventType == EVT_TYPE_ChangedContent)
		{
			const auto ManifestCount = Data->RelevantManifestsAgainstLatest.Num();
			for (int i = 0; i < ManifestCount; ++i)
			{
				const auto ToUpdate = Data->RelevantManifestsAgainstLatest[i];
				const auto ToRemove = Data->ToRemoveLocalEntries[i];
				UpdateLocalManifestCache(ToUpdate, ToRemove);
			}
			OnContentLocalChange.Broadcast();
		}
	};
	WatchCommand->OnCompleted = [this, WatchCommand, FirstEventOp](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			// If we completed without receiving the first event, we trigger an error of the first event.
			if (WatchCommand->Stream.Num() == 0) RequestTracker->TriggerOperationError(FirstEventOp, TEXT("Failed to fetch initial full-rebuild event"));

			const auto DuplicateCommand = DuplicateObject<UBeamCliContentPsCommand>(WatchCommand, GetTransientPackage());
			Cli->RunCommand(DuplicateCommand, {TEXT("-w")}, {});
		}
	};

	const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
	Cli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
}

bool UBeamEditorContent::IsValidContentName(const FString& ContentName, FText& Err)
{
	FString Errs = TEXT("Found Content Name Errors:\n");
	auto bIsValid = !ContentName.IsEmpty();

	const auto InvalidChars = TArray{TEXT(" "), TEXT(".")};
	for (const auto InvalidChar : InvalidChars)
	{
		const auto bContainsInvalidChar = ContentName.Contains(InvalidChar);
		bIsValid &= !bContainsInvalidChar;

		if (bContainsInvalidChar)
		{
			Errs += FString::Printf(TEXT("- Content cannot have the character [%s] in them."), InvalidChar);
		}
	}

	if (!bIsValid)
		Err = FText::FromString(Errs);
	return bIsValid;
}


UClass** UBeamEditorContent::FindContentTypeByName(FString TypeName)
{
	return AllContentTypes.FindByPredicate([TypeName](const UClass* Class)
	{
		return Class->GetFName().ToString().Equals(TypeName);
	});
}

UClass** UBeamEditorContent::FindContentTypeByTypeId(FString TypeId)
{
	return ContentTypeStringToContentClass.Find(TypeId);
}


bool UBeamEditorContent::TryLoadContentObject(const FBeamContentManifestId& OwnerManifest, FBeamContentId ContentId,
                                              UBeamContentObject*& OutLoadedContentObject)
{
	// Hit the cache first.
	if (LoadedContentObjects.Contains(ContentId))
	{
		OutLoadedContentObject = LoadedContentObjects.FindRef(ContentId);
		return true;
	}

	// Otherwise, find the UClass for the content type. Load the JSON and deserialize it into the UBeamContentObject.
	return LoadContentObjectInstance(LocalManifestCache[OwnerManifest], ContentId, OutLoadedContentObject,
	                                 GetTransientPackage());
}

bool UBeamEditorContent::LoadContentObjectInstance(const ULocalContentManifestStreamData* Manifest,
                                                   const FBeamContentId& ContentId,
                                                   UBeamContentObject*& OutNewContentObject, UObject* Outer)
{
	// Make sure the object exists in the manifest
	if (const auto Entry = Manifest->Entries.FindByPredicate([ContentId](ULocalContentManifestEntryStreamData* E)
	{
		return E->FullId.Equals(ContentId.AsString);
	}))
	{
		// Otherwise, find the UClass for the content type. Load the JSON and deserialize it into the UBeamContentObject.
		UClass* ObjectClass;
		TEnumAsByte<EBeamContentObjectSupportLevel> SupportLevel;
		UBeamContentObject::GetClassForTypeId(ContentTypeStringToContentClass, ContentId.GetTypeId(), ObjectClass, SupportLevel);

		// Create the object instance
		if (ObjectClass)
		{
			const auto FilePath = (*Entry)->JsonFilePath;
			FString FileContents;
			if (FFileHelper::LoadFileToString(FileContents, *FilePath))
			{
				const auto ContentObject = NewObject<UBeamContentObject>(Outer, ObjectClass);
				OutNewContentObject = ContentObject;
				OutNewContentObject->SupportLevel = SupportLevel;
				OutNewContentObject->FromBasicJson(FileContents);
				OutNewContentObject->Id = ContentId.AsString;
				OutNewContentObject->Version = (*Entry)->Hash;
				return true;
			}
		}
	}
	return false;
}

void UBeamEditorContent::GetContentTypeToIdMaps(TMap<FName, TArray<TSharedPtr<FName>>>& Map)
{
	for (const auto& LocalManifest : LocalManifestCache)
	{
		const auto Entries = LocalManifest.Value->Entries;
		for (const auto& Entry : Entries)
		{
			FBeamContentId ContentId{Entry->FullId};
			FString ContentTypeId = ContentId.GetTypeId();

			if (const auto ContentType = ContentTypeStringToContentClass.Find(ContentTypeId))
			{
				const auto TypeName = (*ContentType)->GetFName();
				if (!Map.Contains(TypeName))
					Map.Add(TypeName, {});

				if (!Map[TypeName].ContainsByPredicate([Entry](TSharedPtr<FName> N)
				{
					return N->ToString().Equals(Entry->FullId);
				}))
				{
					Map[TypeName].Add(MakeShareable(new FName(Entry->FullId)));
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Warning,
				       TEXT(
					       "Unreal UBeamContentObject implementation not found for content of given type. CONTENT_TYPE_ID=%s, CONTENT_ID=%s"
				       ), *ContentTypeId,
				       *ContentId.AsString);
			}
		}
	}
}

bool UBeamEditorContent::GetContentTypeFromId(FBeamContentId Id, FString& TypeName)
{
	const auto IdStr = Id.AsString;
	for (const auto& LocalManifest : LocalManifestCache)
	{
		const auto Entries = LocalManifest.Value->Entries;
		for (const auto& Entry : Entries)
		{
			if (Entry->FullId.Equals(Id.AsString))
			{
				if (const auto Type = FindContentTypeByTypeId(Id.GetTypeId()))
				{
					TypeName = (*Type)->GetFName().ToString();
					return true;
				}
			}
		}
	}
	TypeName = TEXT("");
	return false;
}
