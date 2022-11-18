// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamableEditorBlueprintLibrary.h"

#include "BeamEditorSettings.h"
#include "BeamCoreSettings.h"
#include "EditorUtilityWidget.h"
#include "LevelEditor.h"

void UBeamableEditorBlueprintLibrary::StartWidget(UWidgetBlueprint* Blueprint)
{
	if (Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
	{
		const UEditorUtilityWidget* CDO = Cast<UEditorUtilityWidget>(Blueprint->GeneratedClass->GetDefaultObject());		
		if (CDO->ShouldAutoRunDefaultAction())
		{
			// This is an instant-run blueprint, just execute it
			UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(), Blueprint->GeneratedClass);
			Instance->ExecuteDefaultAction();
		}
		else
		{
			const auto RegistrationName = FName(*(Blueprint->GetPathName() + TEXT("_ActiveTab")));
			auto DisplayName = FText::FromString(Blueprint->GetName());
			const auto& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
			const auto LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			auto NewDockTab = LevelEditorTabManager->TryInvokeTab(RegistrationName);			
		}
	}
}


FString UBeamableEditorBlueprintLibrary::GetCidFromInt(int64 Cid)
{
	return FString::Printf(TEXT("%llu"), Cid);
}

void UBeamableEditorBlueprintLibrary::GetRealmsForProject(const FBeamCustomerProjectData& CustomerProjectData, const FString ProjectName, TArray<FBeamProjectRealmData>& ProjectRealms)
{
	for (const auto& Realm : CustomerProjectData.AllRealms)
	{
		if(Realm.ProjectName == ProjectName)
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


