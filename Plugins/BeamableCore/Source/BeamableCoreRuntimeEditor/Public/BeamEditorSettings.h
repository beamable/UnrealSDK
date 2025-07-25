// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBlueprint.h"
#include "AutoGen/Optionals/OptionalBeamPid.h"
#include "BeamBackend/SemanticTypes/BeamCid.h"
#include "BeamBackend/SemanticTypes/BeamPid.h"
#include "Subsystems/Content/BeamContentLocalView.h"
#include "BeamEditorSettings.generated.h"


USTRUCT(BlueprintType)
struct FBeamProjectRealmData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FBeamCid CID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FBeamPid PID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FOptionalBeamPid ParentPID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString ProjectName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString RealmName;

	UPROPERTY(BlueprintReadOnly, Transient, VisibleAnywhere)
	FString RealmSecret;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsDev = false;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsStaging = false;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsProduction = false;
};

USTRUCT(BlueprintType)
struct FBeamCustomerProjectData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString CustomerName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString CustomerAlias;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FBeamProjectRealmData> AllRealms;
};


/**
 * 
 */
UCLASS(Config=Editor, defaultconfig, meta=(DisplayName="Beamable Editor"))
class BEAMABLECORERUNTIMEEDITOR_API UBeamEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * @brief User-defined path to where LocalContentManifests (UDataTables) that are supposed to be included in the build are stored.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	TArray<FDirectoryPath> CookedManifestsPath;

	/**
	 * @brief User-defined path to where LocalContentManifests (UDataTables) that are NOT supposed to be included in the build are stored.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	bool bDisableInEngineEditing = false;

	/**
	 * @brief Users can customize how their various subclasses are rendered in the content manager.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	TMap<TSubclassOf<UBeamContentObject>, FBeamContentViewConfig> LocalContentViewConfigs;

	/**
	 * @brief Users can customize the status icons displayed in the content window.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	TMap<EBeamLocalContentStatus, TSoftObjectPtr<UTexture2D>> LocalContentStatusIcons;

	/**
	 * @brief Conflicted Status Icon
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	TSoftObjectPtr<UTexture2D> ConflictedStatusIcon;

	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category="UI/UX")
	TMap<FString, FLinearColor> OptionalTypePinColors;


	/* Soft path will be converted to content reference before use */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TSoftObjectPtr<UWidgetBlueprint> BeamableMainWindow;

	/* Path for dotnet that the Beam SDK CLI commands will use */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FString DotnetExecutablePath;
};
