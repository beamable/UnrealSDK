// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "DataTableEditorUtils.h"
#include "LocalContentManifestEditor.h"
#include "SNameComboBox.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "AutoGen/SubSystems/BeamContentApi.h"
#include "Content/BeamContentObject.h"
#include "Content/LocalContentManifestRow.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/EditorAssetSubsystem.h"
#include "UObject/SavePackage.h"
#include "BeamEditorContent.generated.h"

#define LOCTEXT_NAMESPACE "FBeamEditorContent"

class IDataTableEditor;


UCLASS(BlueprintType)
class UContentPublishState : public UObject
{
	GENERATED_BODY()

public:
	FManifestChangeSet CurrentChangeSet;
	TMap<FString, UBaseContentReference*> References;
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMABLECOREEDITOR_API UBeamEditorContent : public UBeamEditorSubsystem
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
	TMap<FBeamContentId, UBeamContentObject*> LoadedContentObjects;

	TArray<TSharedPtr<FName>> AllContentTypeNames;
	TArray<UClass*> AllContentTypes;

	UPROPERTY()
	UEditorAssetSubsystem* EditorAssetSubsystem;
	UPROPERTY()
	UAssetEditorSubsystem* AssetEditorSubsystem;
	FAssetToolsModule* AssetToolsModule;
	FContentBrowserModule* ContentBrowserModule;

public:
	inline static const FString DefaultBeamableContentPath = FString(TEXT("/Game")) / TEXT("Beamable") / TEXT("Content");
	inline static const FString DefaultBeamableContentManifestsPath = DefaultBeamableContentPath / TEXT("Manifests");
	inline static const FString DefaultBeamableCookedContentManifestsPath = DefaultBeamableContentManifestsPath / TEXT("Cooked");
	inline static const FString DefaultBeamableUncookedContentManifestsPath = DefaultBeamableContentManifestsPath / TEXT("Uncooked");

	inline static const FString DefaultBeamableProjectPath = FPaths::ProjectDir() / TEXT(".beamable");
	inline static const FString DefaultBeamableProjectContentObjects = DefaultBeamableProjectPath / TEXT("Content");

	inline static const FString Global_Manifest_Name = TEXT("global");
	inline static const FBeamContentManifestId Global_Manifest = FBeamContentManifestId(Global_Manifest_Name);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual FBeamOperationHandle InitializeWhenEditorReady() override;
	virtual FBeamOperationHandle InitializeFromRealm(FBeamRealmHandle NewRealm) override;

	UClass** FindContentTypeByName(FString TypeName);

	bool TryLoadContentObject(const FBeamContentManifestId& OwnerManifest, const FBeamContentId& ContentId, FString TypeName, UBeamContentObject*& OutLoadedContentObject);

private:
	FBeamOperationHandle EnsureGlobalManifest();
	void EnsureGlobalManifest_OnGetManifests(FBasicContentGetManifestsFullResponse Response, const FBeamOperationHandle Op);
	void EnsureGlobalManifest_OnPostManifest(FBasicContentPostManifestFullResponse Response, const FBeamOperationHandle Op);

	FBeamOperationHandle PublishManifest(FBeamContentManifestId ContentManifestId, FBeamOperationEventHandler Handler);
	void PublishManifest_OnGetManifest(FBasicContentGetManifestFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId);
	void PublishManifest_OnPostContent(FPostContentFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId);
	void PublishManifest_OnPostManifest(FBasicContentPostManifestFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId) const;

	static void BuildChangeSetForManifest(TArray<UBaseContentReference*> LocalReferences, TArray<UBaseContentReference*> RemoteReferences, FManifestChangeSet& ChangeSet);
	static FString MakePublishKey(const UBaseContentReference* Ref, FString Visibility = {});


	void HandleAssetOpenedInEditor(UObject* Object, IAssetEditorInstance* AssetEditor);
};

#undef LOCTEXT_NAMESPACE
