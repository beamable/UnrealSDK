// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "AutoGen/SubSystems/BeamContentApi.h"
#include "Content/BeamContentObject.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/SaveGame.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "UObject/Object.h"
#include "UObject/ObjectSaveContext.h"
#include "BeamContentSubsystem.generated.h"

class UBeamContentObject;
class UBeamContentApi;

UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamRuntimeContentCache : public UObject
{
	GENERATED_BODY()

	friend class UBeamContentSubsystem;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FBeamContentManifestId ManifestId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamContentId, UBeamContentObject*> Cache;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamContentId, FString> Hashes;
};

UCLASS()
class BEAMABLECORERUNTIME_API ULocalCachedContentSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, SaveGame)
	UBeamRuntimeContentCache* SavedCache;
};


UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamContentSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamContentApi* ContentApi;

	UPROPERTY()
	TMap<FBeamContentManifestId, UBeamRuntimeContentCache*> LiveContent;

	UPROPERTY()
	TMap<FBeamContentManifestId, UBeamRuntimeContentCache*> BakedContent;

	UPROPERTY()
	TArray<UClass*> AllContentTypes;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * For every cooked content manifest tries to load either a local cache from the latest downloaded content (of previous runs) OR falls back to the cooked content with the build. 
	 */
	virtual FBeamOperationHandle InitializeWhenUnrealReady() override;

	/**
	 * If it's the first time this callback is being called (by our automatic auth flows for the owner UserSlot), we pull the latest 'global' manifest (default one) and cache it in-memory (and in a local file).
	 */
	virtual FBeamOperationHandle OnUserSignedIn(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsFirstAuth) override;

private:
	/**
	 * Given a Client CSV (contains public content only) and its id, we make requests to the URLs where the actual content JSON is stored.
	 * Run OnSuccess if all downloads succeed. OnError, otherwise.
	 */
	void DownloadLiveContentObjectsData(const FBeamContentManifestId Id, const UClientManifestCsvResponse* PublicRemoteManifest, FSimpleDelegate OnSuccess, FSimpleDelegate OnError);

public:
	/**
	 * Tries to get a UBeamContentObject with the given Id from the 'global' (default) manifest.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetContent(FBeamContentId ContentId, UBeamContentObject*& OutContent);

	/**
	 * Tries to get a UBeamContentObject with the given Id from the manifest with the given Id.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContent);

	/**
	 * Tries to get a UBeamContentObject with the given Id from the 'global' (default) manifest. This will always return the most recent baked content (either the cooked one or a downloaded and saved one). 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetBakedContent(FBeamContentId ContentId, UBeamContentObject*& OutContent);

	/**
	* Tries to get a UBeamContentObject with the given Id from the manifest with the given Id. This will always return the most recent baked content (either the cooked one or a downloaded and saved one).
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetBakedContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContent);

	/**
	 * Tries to get a UBeamContentObject with the given Id from the 'global' (default) manifest.
	 * CPP helper that casts to the content type the caller expects that the object with the given ContentId to be.
	 */
	template <typename TContentType>
	bool TryGetContentOfType(FBeamContentId ContentId, TContentType*& OutContent)
	{
		return TryGetContentOfTypeFromManifest<TContentType>(FBeamContentManifestId{"global"}, ContentId, OutContent);
	}

	/**
	 * Tries to get a UBeamContentObject with the given Id from the manifest with the given Id.
	 * CPP helper that casts to the content type the caller expects that the object with the given ContentId to be.
	 */
	template <typename TContentType>
	bool TryGetContentOfTypeFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, TContentType*& OutContent)
	{
		static_assert(TIsDerivedFrom<TContentType, UBeamContentObject>::Value, "TContentType must be a UBeamContentObject.");
		UBeamContentObject* Obj;
		const bool bFound = TryGetContentFromManifest(ManifestId, ContentId, Obj);
		OutContent = Cast<TContentType>(Obj);
		return bFound;
	}
};
