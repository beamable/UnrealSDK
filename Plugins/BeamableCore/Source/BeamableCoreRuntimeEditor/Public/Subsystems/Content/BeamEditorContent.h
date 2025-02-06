// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "DataTableEditorUtils.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "AutoGen/SubSystems/BeamContentApi.h"
#include "Content/BeamContentObject.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/EditorAssetSubsystem.h"
#include "UObject/SavePackage.h"
#include "Factories/DataTableFactory.h"
#include "GameDelegates.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/StreamData/LocalContentManifestStreamData.h"
#include "BeamEditorContent.generated.h"

#define LOCTEXT_NAMESPACE "FBeamEditorContent"

class IDataTableEditor;

DECLARE_MULTICAST_DELEGATE_TwoParams(FBeamContentModified, FBeamContentManifestId, FBeamContentId);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamEditorContent : public UBeamEditorSubsystem
{
	GENERATED_BODY()

	friend class ULocalContentManifestEditorState;

	UPROPERTY()
	UBeamContentApi* ContentApi;

	UPROPERTY()
	UBeamCli* Cli;

	UPROPERTY()
	TArray<FBeamContentManifestId> ManifestIds;

	UPROPERTY()
	TMap<FBeamContentManifestId, ULocalContentManifestStreamData*> LocalManifestCache;

	UPROPERTY()
	TMap<FBeamContentId, UBeamContentObject*> LoadedContentObjects;

	TArray<TSharedPtr<FName>> AllContentTypeNames;

	UPROPERTY()
	UEditorAssetSubsystem* EditorAssetSubsystem;


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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, UClass*> ContentTypeStringToContentClass;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<UClass*, FString> ContentClassToContentTypeString;
	
	/**
	 * This is invoked whenever a content is saved. 
	 */
	FBeamContentModified OnContentSaved;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual FBeamOperationHandle InitializeWhenEditorReady() override;
	virtual FBeamOperationHandle OnRealmInitialized(FBeamRealmHandle NewRealm) override;

	UFUNCTION(BlueprintCallable, Category="Beam")
	void GetLocalManifestIds(TArray<FString>& Keys) const;

	UFUNCTION(BlueprintCallable, Category="Beam", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLocalManifestById(const FBeamContentManifestId& Id, ULocalContentManifestStreamData*& Manifest);

	UClass** FindContentTypeByName(FString TypeName);
	UClass** FindContentTypeByTypeId(FString TypeId);

	void FindSubTypesOfContentType(const TArray<FString>& TypeNames, TMap<FString, TArray<FString>>& OutMappings);

	bool TryLoadContentObject(const FBeamContentManifestId& OwnerManifest, FBeamContentId ContentId, UBeamContentObject*& OutLoadedContentObject);

	bool LoadContentObjectInstance(const ULocalContentManifestStreamData* Manifest, const FBeamContentId& ContentId, UBeamContentObject*& OutNewContentObject, UObject* Outer);

	void GetContentTypeToIdMaps(TMap<FName, TArray<TSharedPtr<FName>>>& Map);
	bool GetContentTypeFromId(FBeamContentId Id, FString& TypeName);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetOrCreateContent(const FBeamContentManifestId& ManifestId, const FString& ContentName, TSubclassOf<UBeamContentObject> ContentObjectSubType, TArray<FString> Tags,
	                        UBeamContentObject*& ContentObject, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool CreateNewContent(const FBeamContentManifestId& ManifestId, const FString& ContentName, TSubclassOf<UBeamContentObject> ContentObjectSubType, TArray<FString> Tags,
	                      UBeamContentObject*& ContentObject, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetContent(const FBeamContentManifestId& ManifestId, FBeamContentId ContentId, UBeamContentObject*& ContentObject);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetContentForEditing(const FBeamContentManifestId& ManifestId, FBeamContentId EditObjectId, UBeamContentObject*& ContentObject, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool SaveContentObject(const FBeamContentManifestId& ManifestId, UBeamContentObject* EditingObject, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool DeleteContentObject(const FBeamContentManifestId& ManifestId, FBeamContentId Id, FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool CreateNewContentInManifest(const FBeamContentManifestId& ManifestId, const FString& ContentName, const int& ContentTypeIndex, UBeamContentObject*& ContentObject, TArray<FString> Tags,
	                                FString& ErrMsg);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryRenameContent(const FBeamContentManifestId& ManifestId, const FBeamContentId& ContentId, const FString& NewContentName, FText& Err);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetFilteredListOfContent(const FBeamContentManifestId ManifestId, const FString& NameFilter, const FString& TypeFilter, const TEnumAsByte<EBeamLocalContentStatus>& ContentStatusFilter,
	                                 TArray<UBeamContentLocalView*>& FoundLocalContent);

	static FString GetJsonBlobPath(FString RowName, FBeamContentManifestId ManifestId);
	static FString GetManifestDataTableName(FBeamContentManifestId Id);
	static FBeamContentManifestId GetManifestIdFromDataTable(const UDataTable* Table);

	UFUNCTION(BlueprintCallable)
	void BakeManifest(FBeamContentManifestId Manifest);

	/**
	 * @brief Downloads the remote manifest and content objects to the local cache. This destroys all local changes. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle RefreshLocalManifestOperation(FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc RefreshLocalManifestOperation
	 */
	FBeamOperationHandle CPP_RefreshLocalManifestOperation(FBeamOperationEventHandlerCode OnOperationEvent);


	/**
	 * @brief Downloads the remote manifest and content objects to the local cache. This destroys all local changes. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool PublishManifest(FBeamContentManifestId ContentManifestId, FString& Err);

	/**
	 * @brief Downloads the remote manifest and content objects to the local cache. This destroys all local changes. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool DownloadManifest(FBeamContentManifestId ContentManifestId, FString& Err);

	/**
	 * @brief Fetches the local content manifest from the CLI synchronously. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool RefreshLocalManifests(FString& Err);

	/**
	 * Checks if the given ContentName is a valid content name. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Content", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsValidContentName(const FString& ContentName, FText& Err);

private:
	FBeamOperationHandle RefreshLocalManifests(FBeamOperationHandle Op);

	void UpdateLocalManifestCache(const TArray<ULocalContentManifestStreamData*>& Data);
};

#undef LOCTEXT_NAMESPACE
