// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamEditorContent.h"


#include "IContentBrowserSingleton.h"
#include "Content/BeamContentCache.h"
#include "Content/DownloadContentState.h"
#include "Misc/FileHelper.h"
#include "Settings/ProjectPackagingSettings.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliContentLocalManifestCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentPublishCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentPullCommand.h"

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
			ContentClassToContentTypeString.Add(*It,ContentTypeId);
		}
	}
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
	checkf(Cli->IsInstalled(), TEXT("Editor Subsystem %s - Content depends on the CLI. It was not found locally."),
	       *GetName());

	// For now, we just fetch all the manifests that exist.	
	return CPP_RefreshLocalManifestOperation({});
}

void UBeamEditorContent::GetLocalManifestIds(TArray<FString>& Keys) const
{
	TArray<FBeamContentManifestId> Ids;
	Keys.Reserve(LocalManifestCache.GetKeys(Ids));
	for (const auto& Id : Ids)
	{
		Keys.Add(Id.AsString);
	}
}

bool UBeamEditorContent::TryGetLocalManifestById(const FBeamContentManifestId& Id,
                                                 ULocalContentManifestStreamData*& Manifest)
{
	if (LocalManifestCache.Contains(Id))
	{
		Manifest = LocalManifestCache.FindChecked(Id);
		return true;
	}

	return false;
}

FBeamOperationHandle UBeamEditorContent::RefreshLocalManifests(FBeamOperationHandle Op)
{
	UBeamEditor* BeamEditor = UBeamEditor::GetSelf(this);

	BeamEditor->UpdateBeamableWindowMessage("Updating Local Content...",EMessageType::VE_Info);
	
	if (!Cli->IsInstalled())
		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), TEXT(""), {});
		
	// Ensure the CLI is installed
	checkf(Cli->IsInstalled(), TEXT("Editor Subsystem %s - Content depends on the CLI. It was not found locally."),
	       *GetName());

	const auto GetLocalManifestsCommand = NewObject<UBeamCliContentLocalManifestCommand>();
	GetLocalManifestsCommand->OnStreamOutput = [this](const TArray<UBeamCliContentLocalManifestStreamData*>& Data,
	                                                  const TArray<int64>&, const FBeamOperationHandle&)
	{
		for (const auto& D : Data)
			UpdateLocalManifestCache(D->Manifests);
	};
	GetLocalManifestsCommand->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle& OpHandle)
	{
		if (ResCode == 0) RequestTracker->TriggerOperationSuccess(OpHandle, {});
		else RequestTracker->TriggerOperationError(OpHandle, FString::Printf(TEXT("%d"), ResCode));
	};

	Cli->RunCommandServer(GetLocalManifestsCommand, {}, Op);
	return Op;
}

bool UBeamEditorContent::RefreshLocalManifests(FString& Err)
{
	FSlowTask* SlowTask = new FSlowTask(1, FText::FromString(TEXT("Reloading content...")));
	SlowTask->Initialize();
	SlowTask->MakeDialog();

	bool Res = false;
	const auto GetLocalManifestsCommand = NewObject<UBeamCliContentLocalManifestCommand>();
	GetLocalManifestsCommand->OnStreamOutput = [this](const TArray<UBeamCliContentLocalManifestStreamData*>& Data,
	                                                  const TArray<int64>&, const FBeamOperationHandle&)
	{
		for (const auto& D : Data)
			UpdateLocalManifestCache(D->Manifests);
	};
	GetLocalManifestsCommand->OnCompleted = [this, &Res, &Err, SlowTask](const int& ResCode, const FBeamOperationHandle&)
	{
		Res = ResCode == 0;
		Err = Res ? TEXT("") : TEXT("FAILED_REFRESH");
		SlowTask->Destroy();
		delete SlowTask;
	};

	Cli->RunCommandSync(GetLocalManifestsCommand, {});
	SlowTask->EnterProgressFrame();
	return Res;
}

bool UBeamEditorContent::PublishManifest(FBeamContentManifestId ContentManifestId, FString& Err)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();

	FSlowTask* SlowTask = new FSlowTask(1, FText::FromString(TEXT("Publishing Content...")));
	SlowTask->Initialize();
	SlowTask->MakeDialog();

	bool Res = false;
	UBeamCliContentPublishCommand* PublishCommand = NewObject<UBeamCliContentPublishCommand>();
	PublishCommand->OnStreamOutput = [this](const TArray<UBeamCliContentPublishStreamData*>& Data, const TArray<int64>&,
	                                        const FBeamOperationHandle&)
	{
		for (const auto& D : Data)
			UpdateLocalManifestCache(D->Manifests);
	};
	PublishCommand->OnCompleted = [this, &Res, &Err, SlowTask](const int& ResCode, const FBeamOperationHandle&)
	{
		Res = ResCode == 0;
		Err = Res ? TEXT("") : TEXT("FAILED_PUBLISH");
		SlowTask->Destroy();
		delete SlowTask;
	};
	Cli->RunCommandSync(PublishCommand, {FString::Printf(TEXT("--manifest-ids %s"), *ContentManifestId.AsString)});
	SlowTask->EnterProgressFrame();
	return Res;
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
			UpdateLocalManifestCache(D->Manifests);
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

void UBeamEditorContent::FindSubTypesOfContentType(const TArray<FString>& TypeNames,
                                                   TMap<FString, TArray<FString>>& OutMappings)
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
					OutMappings.Add(TypeName, Array);
				}
				OutMappings[TypeName].Add(CurrentId);
			}
		}
	}
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
		EBeamContentObjectSupportLevel SupportLevel;
		UBeamContentObject::GetClassForTypeId(ContentTypeStringToContentClass, ContentId.GetTypeId(), ObjectClass,
		                                      SupportLevel);

		// Create the object instance
		if (ObjectClass)
		{
			const auto FilePath = GetJsonBlobPath(ContentId.AsString, Manifest->ManifestId);
			FString FileContents;
			if (FFileHelper::LoadFileToString(FileContents, *FilePath))
			{
				const auto ContentObject = NewObject<UBeamContentObject>(Outer, ObjectClass);
				OutNewContentObject = ContentObject;
				OutNewContentObject->SupportLevel = SupportLevel;
				if (auto Bag = FJsonDataBag(); Bag.FromJson(*FileContents))
				{
					OutNewContentObject->Id = ContentId.AsString;
					OutNewContentObject->Version = (*Entry)->Hash;
					OutNewContentObject->Tags = (*Entry)->Tags;
					OutNewContentObject->ParsePropertiesJsonObject(Bag.JsonObject);
				}
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

bool UBeamEditorContent::GetOrCreateContent(const FBeamContentManifestId& ManifestId, const FString& ContentName,
                                            TSubclassOf<UBeamContentObject> ContentObjectSubType, TArray<FString> Tags,
                                            UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	ensure(!ContentName.IsEmpty());
	const auto ContentTypeString = GetMutableDefault<UBeamContentObject>(ContentObjectSubType)->
		BuildContentTypeString();
	const auto ContentId = FString::Format(TEXT("{0}.{1}"), {ContentTypeString, ContentName});

	if (!GetContentForEditing(ManifestId, ContentId, ContentObject, ErrMsg))
		return CreateNewContent(ManifestId, ContentName, ContentObjectSubType, Tags, ContentObject, ErrMsg);

	return true;
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
		                    ? FString::Format(TEXT("{0}.New_{1}_{2}"), {
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
			               ? FString::Format(TEXT("{0}.New_{1}_{2}"), {
				                                 ContentObject->BuildContentTypeString(), TypeName, RepeatedNameCount
			                                 })
			               : FString::Format(TEXT("{0}.{1}_{2}"), {
				                                 ContentObject->BuildContentTypeString(), ContentName, RepeatedNameCount
			                                 });
	}

	// Sets the ID and Tags based on the manifest row.
	ContentObject->Id = NewContentId;
	ContentObject->Tags.Append(Tags);

	FString JsonProperties;
	ContentObject->ToPropertiesJson(JsonProperties);

	const auto FilePath = GetJsonBlobPath(NewContentId, ManifestId);

	// Save the file into the ".beamable/content/manifestId/contentId.json" path.
	if (FFileHelper::SaveStringToFile(JsonProperties, *FilePath))
	{
		// Adds the editing object to the list of cached content objects (so that we don't need to keep deserializing it all the time).
		LoadedContentObjects.Add(ContentObject->Id, ContentObject);

		// Make a new Entry and add it to the current manifest (this makes it so that we don't have to call refresh
		const auto NewEntry = NewObject<ULocalContentManifestEntryStreamData>();
		NewEntry->FullId = NewContentId;
		NewEntry->Tags = Tags;
		NewEntry->Hash = ContentObject->CreatePropertiesHash();
		NewEntry->CurrentStatus = 0;
		NewEntry->TypeName = ContentObject->BuildContentTypeString();

		// Extract the name only from this
		int32 NameStartIdx;
		NewContentId.FindLastChar('.', NameStartIdx);
		NameStartIdx += 1;
		NewEntry->Name = NewContentId.RightChop(NameStartIdx);

		// Update the entries array.
		Entries.Add(NewEntry);
		LocalManifestCache.FindRef(ManifestId)->Entries = Entries;
	}
	else
	{
		ErrMsg = FString::Format(TEXT("Failed to save the content object {0}"), {NewContentId});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}
	ErrMsg.Empty();
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

bool UBeamEditorContent::SaveContentObject(const FBeamContentManifestId& ManifestId, UBeamContentObject* EditingObject,
                                           FString& ErrMsg)
{
	// Get the ID and properties for this 
	FString Id = EditingObject->Id;
	FString PropertiesJsonContent;
	EditingObject->ToPropertiesJson(PropertiesJsonContent);

	// Just save the properties json blob into the .beamable/content path 
	if (FFileHelper::SaveStringToFile(PropertiesJsonContent, *GetJsonBlobPath(Id, ManifestId)))
	{
		// Trigger a callback saying that a piece of content was modified
		if (OnContentSaved.IsBound()) OnContentSaved.Broadcast(ManifestId, Id);
		return true;
	}
	return false;
}

bool UBeamEditorContent::DeleteContentObject(const FBeamContentManifestId& ManifestId, FBeamContentId Id,
                                             FString& ErrMsg)
{
	const auto FilePath = GetJsonBlobPath(Id.AsString, ManifestId);
	IFileManager& FileManager = IFileManager::Get();
	const auto bDeleted = FileManager.Delete(*FilePath);

	if (bDeleted)
	{
		LoadedContentObjects.Remove(Id);
		if (auto ManifestPtr = LocalManifestCache.Find(ManifestId))
		{
			auto Manifest = *ManifestPtr;
			if (const auto Entry = *Manifest->Entries.FindByPredicate([Id](ULocalContentManifestEntryStreamData* E)
			{
			return E->FullId.Equals(Id.AsString);
			}))
			{
				if (Entry->CurrentStatus == EBeamLocalContentStatus::Beam_LocalContentCreated)
				{
					Manifest->Entries.Remove(Entry);
				}
			}
		}
	}
	else
	{
		ErrMsg = FString::Format(TEXT("Failed to save the content object {0}"), {Id.AsString});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}
	return true;
}

bool UBeamEditorContent::CreateNewContentInManifest(const FBeamContentManifestId& ManifestId,
                                                    const FString& ContentName, const int& ContentTypeIndex,
                                                    UBeamContentObject*& ContentObject,
                                                    TArray<FString> Tags, FString& ErrMsg)
{
	const TSubclassOf<UBeamContentObject> ContentObjectSubType = AllContentTypes[ContentTypeIndex];
	return CreateNewContent(ManifestId, ContentName, ContentObjectSubType, Tags, ContentObject, ErrMsg);
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

	const auto NewContentPath = GetJsonBlobPath(NewContentId.AsString, ManifestId);
	const auto bNewNameIsAvailable = !IFileManager::Get().FileExists(*NewContentPath);
	if (!bNewNameIsAvailable)
	{
		Err = FText::FromString(TEXT("The provided content id is already in use."));
		return false;
	}

	Obj->Id = NewId;
	FString SaveErr;
	if (!SaveContentObject(ManifestId, Obj, SaveErr))
	{
		Err = FText::FromString(SaveErr);
		return false;
	}

	FString DeleteErr;
	if (!DeleteContentObject(ManifestId, ContentId, DeleteErr))
	{
		Err = FText::FromString(DeleteErr);
		return false;
	}

	FString RefreshErr;
	if (!RefreshLocalManifests(RefreshErr))
	{
		Err = FText::FromString(RefreshErr);
		return false;
	}

	return true;
}

bool UBeamEditorContent::TryGetFilteredListOfContent(const FBeamContentManifestId ManifestId, const FString& NameFilter,
                                                     const FString& TypeFilter,
                                                     const TEnumAsByte<EBeamLocalContentStatus>& ContentStatusFilter,
                                                     TArray<UBeamContentLocalView*>& FoundLocalContent)
{
	if (!LocalManifestCache.Contains(ManifestId))
		return false;

	const auto manifest = LocalManifestCache[ManifestId];

	TArray<FString> Names;
	TArray<FString> Ids;
	TArray<FString> Types;
	TArray<UBeamContentObject*> ObjectsInManifest;
	TArray<EBeamLocalContentStatus> StatusesInManifest;
	auto Rows = manifest->Entries;

	for (const auto Row : Rows)
	{
		const auto bPassNameFilter = NameFilter.IsEmpty() || Row->Name.StartsWith(NameFilter);
		const auto bPassTypeFilter = TypeFilter.IsEmpty() || Row->TypeName.Equals(TypeFilter);
		const auto bPassStatusFilter = ContentStatusFilter == Beam_LocalContentAny || Row->CurrentStatus == static_cast<
			int64>(ContentStatusFilter);

		if (bPassNameFilter && bPassTypeFilter && bPassStatusFilter)
		{
			Ids.Add(Row->FullId);
			Names.Add(Row->Name);
			Types.Add(Row->TypeName);
			StatusesInManifest.Add(
				static_cast<EBeamLocalContentStatus>(StaticEnum<EBeamLocalContentStatus>()->GetValueByIndex(
					Row->CurrentStatus)));

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
	return DefaultBeamableProjectContentObjects / ManifestId.AsString / RowName + TEXT(".json");
}

FString UBeamEditorContent::GetManifestDataTableName(const FBeamContentManifestId Id)
{
	return TEXT("BCM_") + Id.AsString.Mid(0, 1).ToUpper() + Id.AsString.Mid(1, Id.AsString.Len() - 1);
}

FBeamContentManifestId UBeamEditorContent::GetManifestIdFromDataTable(const UDataTable* Table)
{
	FString Discard;
	FString Name;
	if (Table->GetName().Split("_", &Discard, &Name))
	{
		return FBeamContentManifestId{Name.Mid(0, 1).ToLower() + Name.Mid(1, Name.Len() - 1)};
	}
	return {};
}


void UBeamEditorContent::BakeManifest(FBeamContentManifestId Manifest)
{
	UBeamContentCache* Cache  = NewObject<UBeamContentCache>(this);
	
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
					
	const FString BakedContentPath =  FPaths::ProjectContentDir() + CoreSettings->BakedContentFolderName + "/" +
					CoreSettings->GlobalBakedContentFileName;

	TArray<uint8> SerializedData;
	FMemoryWriter Writer(SerializedData, true);
						
	Cache->SerializeToBinary(Writer,ContentTypeStringToContentClass,ContentClassToContentTypeString);

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
		for (FDirectoryPath &DirectoryPath : PackagingSettings->DirectoriesToAlwaysStageAsNonUFS)
		{
			if (DirectoryPath.Path == CoreSettings->BakedContentFolderName)
			{
				PathAlreadyAdded = true;
			}
		}
		if (!PathAlreadyAdded)
		{
			PackagingSettings->DirectoriesToAlwaysStageAsNonUFS.Add(FDirectoryPath{ CoreSettings->BakedContentFolderName });

			PackagingSettings->SaveConfig(CPF_Config, *PackagingSettings->GetDefaultConfigFilename());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to retrieve packaging settings."));
	}
}

FBeamOperationHandle UBeamEditorContent::RefreshLocalManifestOperation(FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetClass()->GetFName().ToString(),
	                                                   OnOperationEvent);
	RefreshLocalManifests(Handle);
	return Handle;
}

FBeamOperationHandle UBeamEditorContent::CPP_RefreshLocalManifestOperation(
	FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = RequestTracker->CPP_BeginOperation({Editor->GetMainEditorSlot()},
	                                                       GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshLocalManifests(Handle);
	return Handle;
}

void UBeamEditorContent::UpdateLocalManifestCache(const TArray<ULocalContentManifestStreamData*>& Data)
{
	for (const auto& d : Data)
	{
		ManifestIds.AddUnique(d->ManifestId);
		LocalManifestCache.Add(d->ManifestId, d);
		UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Found Manifest with Id %s"), *GetName(),
		       *d->ManifestId)
	}
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
