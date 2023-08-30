// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "DataTableEditorUtils.h"
#include "LocalContentManifestEditor.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "AutoGen/SubSystems/BeamContentApi.h"
#include "Content/BeamContentObject.h"
#include "Content/LocalContentManifestRow.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/EditorAssetSubsystem.h"
#include "UObject/SavePackage.h"
#include "Factories/DataTableFactory.h"
#include "GameDelegates.h"
#include "BeamEditorContent.generated.h"

#define LOCTEXT_NAMESPACE "FBeamEditorContent"

class IDataTableEditor;


UCLASS(BlueprintType)
class UContentPublishState : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FManifestChangeSet CurrentChangeSet;

	UPROPERTY()
	TMap<FString, UBaseContentReference*> References;
};

UCLASS(BlueprintType)
class UContentDownloadState : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FBeamOperationHandle CurrentDownloadHandle;

	UPROPERTY()
	FManifestChangeSet RemoteToLocalDiff;

	UPROPERTY()
	UContentBasicManifest* RemoteManifest;
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamEditorContent : public UBeamEditorSubsystem, public FDataTableEditorUtils::FDataTableEditorManager::ListenerType
{
	GENERATED_BODY()

	friend class ULocalContentManifestEditorState;

	UPROPERTY()
	UBeamContentApi* ContentApi;

	UPROPERTY()
	TArray<FBeamContentManifestId> ManifestIds;

	FDelegateHandle LocalContentManifestDataTableHandler;

	UPROPERTY()
	TMap<FBeamContentManifestId, ULocalContentManifestEditorState*> EditorStates;
	UPROPERTY()
	TMap<FBeamContentManifestId, UDataTable*> LocalManifests;
	UPROPERTY()
	TMap<FBeamContentManifestId, UContentPublishState*> WorkingPublishStates;
	UPROPERTY()
	TMap<FBeamContentManifestId, UContentDownloadState*> WorkingDownloadStates;


	UPROPERTY()
	TMap<FBeamContentId, UBeamContentObject*> LoadedContentObjects;

	TArray<TSharedPtr<FName>> AllContentTypeNames;

	UPROPERTY()
	UEditorAssetSubsystem* EditorAssetSubsystem;
	UPROPERTY()
	UAssetEditorSubsystem* AssetEditorSubsystem;
	FAssetToolsModule* AssetToolsModule;
	FContentBrowserModule* ContentBrowserModule;
	
	FDelegateHandle OnWillEnterPIE;

public:
	inline static const FString DefaultBeamableContentPath = FString(TEXT("/Game")) / TEXT("Beamable") /
		TEXT("Content");
	inline static const FString DefaultBeamableContentManifestsPath = DefaultBeamableContentPath / TEXT("Manifests");
	inline static const FString DefaultBeamableCookedContentManifestsPath = DefaultBeamableContentManifestsPath /
		TEXT("Cooked");
	inline static const FString DefaultBeamableUncookedContentManifestsPath = DefaultBeamableContentManifestsPath /
		TEXT("Uncooked");

	inline static const FString DefaultBeamableProjectPath = FPaths::ProjectDir() / TEXT(".beamable");
	inline static const FString DefaultBeamableProjectContentObjects = DefaultBeamableProjectPath / TEXT("Content");

	inline static const FString Global_Manifest_Name = TEXT("global");
	inline static const FBeamContentManifestId Global_Manifest = FBeamContentManifestId(Global_Manifest_Name);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<UClass*> AllContentTypes;


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual FBeamOperationHandle InitializeWhenEditorReady() override;
	virtual FBeamOperationHandle InitializeFromRealm(FBeamRealmHandle NewRealm) override;

	UFUNCTION(BlueprintCallable, Category="Beam")
	void GetLocalManifestIds(TArray<FString>& Keys) const;

	UFUNCTION(BlueprintCallable, Category="Beam", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLocalManifestById(const FBeamContentManifestId& Id, UDataTable*& Manifest);


	UClass** FindContentTypeByName(FString TypeName);

	bool TryLoadContentObject(const FBeamContentManifestId& OwnerManifest, FBeamContentId ContentId, FString TypeName, UBeamContentObject*& OutLoadedContentObject);

	bool InstantiateContentObject(const UDataTable* Manifest, const FBeamContentId& ContentId, UBeamContentObject*& OutNewContentObject, UObject* Outer);

	void GetContentTypeToIdMaps(TMap<FName, TArray<TSharedPtr<FName>>>& Map);
	bool GetContentTypeFromId(FBeamContentId Id, FString& TypeName);


	void SynchronizeRemoteManifestWithLocalManifest(const FBeamContentManifestId Id, const UContentBasicManifest* RemoteManifest, UDataTable* LocalManifest, FEditorStateChangedHandlerCode OnSuccess,
	                                                FEditorStateChangedHandlerCode OnError);


	/** Implementation of FDataTableEditorManager::ListenerType --- needed to respond to selection and table data modifications */
	virtual void PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType) override;

	virtual void PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType) override;


	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetOrCreateContent(const FBeamContentManifestId& ManifestId, const FString& ContentName, TSubclassOf<UBeamContentObject> ContentObjectSubType, UBeamContentObject*& ContentObject, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool CreateNewContent(const FBeamContentManifestId& ManifestId, const FString& ContentName, TSubclassOf<UBeamContentObject> ContentObjectSubType, UBeamContentObject*& ContentObject, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetContent(const FBeamContentManifestId& ManifestId, FBeamContentId ContentId, UBeamContentObject*& ContentObject);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetContentForEditing(const FBeamContentManifestId& ManifestId, FBeamContentId EditObjectId, UBeamContentObject*& ContentObject, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool SaveContentObject(const FBeamContentManifestId& ManifestId, UBeamContentObject* EditingObject, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool CreateNewContentInManifest(const FBeamContentManifestId& ManifestId, const FString& ContentName, const int& ContentTypeIndex, UBeamContentObject*& ContentObject, FString& ErrMsg);

	static FString GetJsonBlobPath(FString RowName, FBeamContentManifestId ManifestId);
	static FString GetManifestDataTableName(FBeamContentManifestId Id);
	static FBeamContentManifestId GetManifestIdFromDataTable(const UDataTable* Table);

	UFUNCTION(BlueprintCallable)
	void BakeManifest(UDataTable* LocalManifest, UBeamContentCache* Cache);

private:
	FBeamOperationHandle EnsureGlobalManifest();
	void EnsureGlobalManifest_OnGetManifests(FBasicContentGetManifestsFullResponse Response, const FBeamOperationHandle Op);
	void EnsureGlobalManifest_OnPostManifest(FBasicContentPostManifestFullResponse Response, const FBeamOperationHandle Op);

	FBeamOperationHandle PublishManifest(FBeamContentManifestId ContentManifestId, FBeamOperationEventHandler Handler);
	void PublishManifest_OnGetManifest(FBasicContentGetManifestFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId);
	void PublishManifest_OnPostContent(FPostContentFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId);
	void PublishManifest_OnPostManifest(FBasicContentPostManifestFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId) const;


	FBeamOperationHandle DownloadManifest(FBeamContentManifestId ContentManifestId, FBeamOperationEventHandlerCode Handler);
	void DownloadManifest_OnGetManifest(FBasicContentGetManifestFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ManifestId);
	void DownloadManifest_ApplyUserInput(FBeamContentManifestId ManifestId, bool AcceptCurrentChanges);

	static void BuildChangeSetForManifest(TArray<UBaseContentReference*> LocalReferences, TArray<UBaseContentReference*> RemoteReferences, FManifestChangeSet& ChangeSet);
	static FString MakePublishKey(const UBaseContentReference* Ref, FString Visibility = {});


	void HandleAssetOpenedInEditor(UObject* Object, IAssetEditorInstance* AssetEditor);

	/**
	 * @brief Compares and finds the manifest ID for the data table instance that is being modified --- if it cannot find it among the loaded manifests, we return false.
	 */
	bool GetChangingManifest(const UDataTable* Changed, FBeamContentManifestId& ManifestId, UDataTable*& EditingTable) const;
};

#undef LOCTEXT_NAMESPACE
