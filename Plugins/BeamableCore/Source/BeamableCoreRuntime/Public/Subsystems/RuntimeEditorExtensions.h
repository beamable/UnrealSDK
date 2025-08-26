// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "Content/BeamContentObject.h"
#include "Content/BeamContentSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#if WITH_EDITOR
#include "Editor.h"
#include "Subsystems/Content/BeamEditorContent.h"
#endif

#include "RuntimeEditorExtensions.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamRuntimeEditorExtensions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Helper that gets a content object from the specified manifest.
	 * When called inside the editor but outside of PIE, will return the local content definition.
	 * In other cases, will try and fetch the content from the runtime Content Subsystem.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Content|Utils", meta=(DefaultToSelf="CallingContext"))
	static bool GetContentFromManifest(const FBeamContentManifestId& ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContentObject, UObject* CallingContext = nullptr)
	{
#if WITH_EDITOR
		if (!CallingContext->GetWorld()->GetGameInstance())
			return GEditor->GetEditorSubsystem<UBeamEditorContent>()->GetContent(ManifestId, ContentId, OutContentObject);
#endif

		return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>()->TryGetContentFromManifest(ManifestId, ContentId, OutContentObject);
	}

	/**
	 * Helper that gets a content object from the "global" Manifest.
	 * When called inside the editor but outside of PIE, will return the local content definition.
	 * In other cases, will try and fetch the content from the runtime Content Subsystem.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Content|Utils", meta=(DefaultToSelf="CallingContext"))
	static bool GetContent(FBeamContentId ContentId, UBeamContentObject*& OutContentObject, UObject* CallingContext = nullptr)
	{
		return GetContentFromManifest({"global"}, ContentId, OutContentObject, CallingContext);
	}

	/**
	 * Utility that will auto-cast @link FUniqueNetIdRepl @endlink to @link FBeamGamerTag @endlink when @link UBeamRuntimeSettings::bUseBeamableGamerTagsAsUniqueNetIds @endlink is true.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Convert UniqueNetId to GamerTag", CompactNodeTitle = "->", BlueprintAutocast), Category = "Beam|Lobby|Utils")
	static FBeamGamerTag Conv_UniqueNetIdReplToBeamGamerTag(const FUniqueNetIdRepl& UniqueNetId)
	{
		if (ensureAlwaysMsgf(GetDefault<UBeamRuntimeSettings>()->bUseBeamableGamerTagsAsUniqueNetIds, TEXT("This casting utility only works if you're using GamerTags as UniqueNetIds."
			                     "If not, please use the 'Local State - Lobby' nodes to convert it.")))
		{
			if (!UniqueNetId.IsValid()) return FBeamGamerTag{};

			const auto& UniqueNetIdAsStr = UniqueNetId.GetUniqueNetId()->ToString();
			return FBeamGamerTag{UniqueNetIdAsStr};
		}

		return FBeamGamerTag{};
	}
};
