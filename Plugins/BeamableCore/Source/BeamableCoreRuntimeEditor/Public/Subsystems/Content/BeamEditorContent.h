// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "AutoGen/SubSystems/BeamContentApi.h"
#include "Content/BeamContentObject.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/EditorAssetSubsystem.h"
#include "AutoGen/Arrays/ArrayOfString.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/StreamData/LocalContentManifestStreamData.h"
#include "BeamEditorContent.generated.h"

#define LOCTEXT_NAMESPACE "FBeamEditorContent"

class IDataTableEditor;

DECLARE_MULTICAST_DELEGATE_TwoParams(FBeamContentModified, FBeamContentManifestId, TArray<FBeamContentId>);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamEditorContent : public UBeamEditorSubsystem
{
	GENERATED_BODY()

	friend class ULocalContentManifestEditorState;
	friend class SBeamContentIdPin;
	friend class FBeamContentIdCustomization;

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

	/**
	 * The engine integration is expected to discard all their in-memory state about content and rebuild it with the information in this event.
	 */
	inline static const int32 EVT_TYPE_FullRebuild = 0;

	/**
	* The engine integration is expected to discard all their in-memory state about what the local content is in relation to the latest published manifest of this realm.
	* It should not discard the state against the reference manifest (latest pulled manifest / local "head").
	*
	* Only <see cref="IsReferenceHeadInRealm"/> and <see cref="RelevantManifestsAgainstLatest"/> is correctly computed here.
	*/
	inline static const int32 EVT_TYPE_RemotePublished = 1;

	/**
	 * The engine integration is expected to use <see cref="ToRemoveLocalEntries"/> to update it's in-memory state regarding our reference manifest.
	 */
	inline static const int32 EVT_TYPE_ChangedContent = 2;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<UClass*> AllContentTypes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, UClass*> ContentTypeStringToContentClass;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<UClass*, FString> ContentClassToContentTypeString;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnContentFullRebuild;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnContentRemotePublish;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnContentLocalChange;

	/**
	 * This is invoked whenever a content is saved. 
	 */
	FBeamContentModified OnContentSaved;

	/**
	 * This is invoked whenever a content is saved. 
	 */
	FBeamContentModified OnContentSavedFailed;

	/**
	 * This is invoked whenever a content is saved. 
	 */
	FBeamContentModified OnContentRevert;

	/**
	 * This is invoked whenever a content is saved. 
	 */
	FBeamContentModified OnContentRevertFailed;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual FBeamOperationHandle InitializeWhenEditorReady() override;
	virtual FBeamOperationHandle OnRealmInitialized(FBeamRealmHandle NewRealm) override;

	/**
	 * @brief Publishes the manifest with the given id to the current TargetRealm. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle PublishManifestOperation(FBeamContentManifestId ManifestId, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc PublishManifestOperation
	 */
	FBeamOperationHandle CPP_PublishManifestOperation(FBeamContentManifestId ManifestId, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * Gets you a list of all locally tracked @link FBeamContentManifestId @endlink  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void GetLocalManifestIds(TArray<FBeamContentManifestId>& Keys) const;

	/**
	 * Gets you the currently stored @link ULocalContentManifestStreamData @endlink for the given @link FBeamContentManifestId @endlink
	 *
	 * This is the in-memory representation of the manifest and its the type the CLI spits out for us in the @link UBeamCliContentPsCommand @endlink .
	 *
	 * This returns false if the given Id is not currently being tracked.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLocalManifestById(const FBeamContentManifestId& Id, ULocalContentManifestStreamData*& Manifest);

	/**
	 *  Gets the UClass representing a content type with the given type id string.
	 *
	 *  Returns "null", if no valid UBeamContentObject sub-class exists locally for the given type id. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	UClass* GetContentTypeByTypeId(FString TypeId);

	/**
	 *  For each of the given TypeId strings, return an array of other TypeId strings for every child content object.
	 *
	 *  In other words, if you pass in "items" as the TypeName, you'll get a map with an "items"=>{"items", "items.some_item_subtype"}. 
	 */
	UFUNCTION(BlueprintCallable)
	void FindSubTypesOfContentType(const TArray<FString>& TypeNames, TMap<FString, FArrayOfString>& OutMappings);

	/**
	 *  Creates a new local content file inside the ".beamable/content" folder.
	 *
	 *  This uses the CLI to do so and is a non-blocking command.
	 *  The created file entry will NOT be available until the next invocation of @link OnContentLocalChange @endlink. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool CreateNewContent(const FBeamContentManifestId& ManifestId, const FString& ContentName, TSubclassOf<UBeamContentObject> ContentObjectSubType, TArray<FString> Tags,
	                      UBeamContentObject*& ContentObject, FString& ErrMsg);

	/**
	 * Tries to get the in-memory deserialized @link UBeamContentObject @endlink instance for the given manifest/content id pair.
	 *
	 * Returns false if it fails to find the object in the manifest. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetContent(const FBeamContentManifestId& ManifestId, FBeamContentId ContentId, UBeamContentObject*& ContentObject);

	/**
	 * @copybrief GetContent
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetContentForEditing(const FBeamContentManifestId& ManifestId, FBeamContentId EditObjectId, UBeamContentObject*& ContentObject, FString& ErrMsg);

	/**
	 * Re-serializes the properties of the object and then asks the CLI to save it.
	 *
	 *  This uses the CLI to do so and is a non-blocking command.
	 *  The modified file's in-memory representation is available immediately after this function call BUT the @link OnContentLocalChange @endlink still fires a little after this returns.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool SaveContentObject(const FBeamContentManifestId& ManifestId, UBeamContentObject* EditingObject, FString PropertyName, bool bIgnoreReferenceManifest = true);

	/**
	 *  Deletes the local file inside the ".beamable/content" folder representing the local content.
	 *
	 *  This DOES NOT use the CLI to do this.
	 *  The deleted file entry shows up on the next invocation of @link OnContentLocalChange @endlink. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool DeleteContentObject(const FBeamContentManifestId& ManifestId, FBeamContentId Id, FString& ErrMsg);

	/**
	 * Rename the content file on disk (change the content id).
	 *
	 *  This DOES NOT use the CLI to do this.
	 *  The "create+deletion" file entries representing the rename shows up on the next invocation of @link OnContentLocalChange @endlink. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryRenameContent(const FBeamContentManifestId& ManifestId, const FBeamContentId& ContentId, const FString& NewContentName, FText& Err);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetFilteredListOfContent(const FBeamContentManifestId ManifestId, const FString& NameFilter, const FString& TypeFilter, const EBeamLocalContentStatus& ContentStatusFilter,
	                                 TArray<UBeamContentLocalView*>& FoundLocalContent);

	static FString GetJsonBlobPath(FString RowName, FBeamContentManifestId ManifestId);

	UFUNCTION(BlueprintCallable)
	void BakeManifest(FBeamContentManifestId Manifest);

	/**
	 * @brief Downloads the remote manifest and content objects to the local cache. This destroys all local changes. 
	 */
	void PublishManifest(FBeamContentManifestId ContentManifestId, FBeamOperationHandle Op);

	/**
	 * @brief Downloads the remote manifest and content objects to the local cache. This destroys all local changes. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool DownloadManifest(FBeamContentManifestId ContentManifestId, FString& Err);

	/**
	 * @brief Downloads the remote manifest and content objects to the local cache. This destroys all local changes. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool ForceSyncContent(FBeamContentManifestId ContentManifestId, TArray<FBeamContentId> Ids);

	/**
	 * @brief Resolve a detected conflict by either downloading from the realm OR accepting that your modifications will override the realm's values. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool ResolveConflict(FBeamContentManifestId ContentManifestId, TArray<FBeamContentId> Ids, bool bUseRealm);

	/**
	 * Checks if the given ContentName is a valid content name. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Content|Utils", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsValidContentName(const FString& ContentName, FText& Err);

	/**
	 * Fills the map with each content id for each content type. It respects the hierarchy. 
	 */	
	[[deprecated("We'll replace this function with a better version of it in the next release (versions that returns FBeamContentId from TSubclassOf<UBeamContentObject>) --- this function will become private.")]]
	void GetContentTypeToIdMaps(TMap<FName, TArray<TSharedPtr<FName>>>& Map);
	
private:
	void RebuildLocalManifestCache(const TArray<ULocalContentManifestStreamData*>& Data);
	void UpdateLocalManifestCache(ULocalContentManifestStreamData* ToUpdate, ULocalContentManifestStreamData* ToClear);

	void RunPsCommand(FBeamOperationHandle FirstEventOp);

	UClass** FindContentTypeByName(FString TypeName);
	UClass** FindContentTypeByTypeId(FString TypeId);


	bool TryLoadContentObject(const FBeamContentManifestId& OwnerManifest, FBeamContentId ContentId, UBeamContentObject*& OutLoadedContentObject);

	bool LoadContentObjectInstance(const ULocalContentManifestStreamData* Manifest, const FBeamContentId& ContentId, UBeamContentObject*& OutNewContentObject, UObject* Outer);


	bool GetContentTypeFromId(FBeamContentId Id, FString& TypeName);
};

#undef LOCTEXT_NAMESPACE
