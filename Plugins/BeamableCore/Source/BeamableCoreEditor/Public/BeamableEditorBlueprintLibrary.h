// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamEditorSettings.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidget.h"
#include "WidgetBlueprint.h"
#include "PropertyEditorClipboard.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"

#include "BeamableEditorBlueprintLibrary.generated.h"


UCLASS()
class BEAMABLECOREEDITOR_API UBeamableEditorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Beam|Editor")
	static UEditorUtilityWidget* StartEditorWidget(UWidgetBlueprint* Blueprint);

	UFUNCTION(BlueprintCallable, Category="Beam|Editor")
	static void GetRealmsForProject(const FBeamCustomerProjectData& ProjectData, const FString ProjectName, TArray<FBeamProjectRealmData>& ProjectRealms);	

	UFUNCTION(BlueprintCallable, Category="Beam|Editor")
	static bool GetRunningPIEWorld(UWorld*& PIEWorld);

	UFUNCTION(BlueprintCallable, Category="Beam|Editor")
	static void CopyToClipboard(FString Text);

	
	/**
	 * @brief Shows a UE notification with the given Title, Body and Icon.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AdvancedDisplay="ExpireDuration,FadeOutDuration"))
	static void ShowNotification(FString Title, FText Body, const FSlateBrush& Icon, float ExpireDuration = 20.0f, float FadeOutDuration = 2.0f);

};
