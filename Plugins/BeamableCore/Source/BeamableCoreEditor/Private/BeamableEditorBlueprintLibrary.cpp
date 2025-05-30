// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamableEditorBlueprintLibrary.h"

#include "BeamEditorSettings.h"
#include "BeamCoreSettings.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidget.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "LevelEditor.h"

void UBeamableEditorBlueprintLibrary::StartEditorWidget(UWidgetBlueprint* Blueprint)
{
	// INFO: See AssetTypeActions_EditorUtilityWidgetBlueprint.cpp (method ExecuteRun).
	if (Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
	{
		if (Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
		{
			if (UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint))
			{
				UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
				EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
			}
		}
	}
}


void UBeamableEditorBlueprintLibrary::GetRealmsForProject(const FBeamCustomerProjectData& CustomerProjectData, const FString ProjectName, TArray<FBeamProjectRealmData>& ProjectRealms)
{
	for (const auto& Realm : CustomerProjectData.AllRealms)
	{
		if (Realm.ProjectName == ProjectName)
			ProjectRealms.Add(Realm);
	}
}

bool UBeamableEditorBlueprintLibrary::GetRunningPIEWorld(UWorld*& PIEWorld)
{
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (WorldContext.WorldType == EWorldType::PIE)
		{
			PIEWorld = WorldContext.World();
			return true;
		}
	}
	PIEWorld = nullptr;
	return false;
}

void UBeamableEditorBlueprintLibrary::CopyToClipboard(FString Text)
{
	FPropertyEditorClipboard::ClipboardCopy(*Text);
}
