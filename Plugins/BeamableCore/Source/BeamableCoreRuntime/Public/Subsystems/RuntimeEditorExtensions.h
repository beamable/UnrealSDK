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
};
