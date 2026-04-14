// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Serialization/JsonSerializerMacros.h"
#include "Subsystems/EngineSubsystem.h"
#include "BeamEnvironment.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamEnvironmentData : public UDataAsset, public FJsonSerializable
{
	GENERATED_BODY()

public:
	using UDataAsset::Serialize; // Bring Serialize from UDataAsset into scope
	using FJsonSerializable::Serialize; // Bring Serialize from FJsonSerializable into scope

	UFUNCTION(CallInEditor, Category="Actions")
	void RefreshBackendDataAsset();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int SortOrder = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Environment;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString APIUrl;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString PortalUrl;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString BeamMongoExpressUrl;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString DockerRegistryUrl;


	virtual void Serialize(FJsonSerializerBase& Serializer, bool bFlatObject) override;
};

DECLARE_DELEGATE_OneParam(FOnRefreshAsset, UBeamEnvironmentData*);

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamEnvironment : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	FOnRefreshAsset OnRefreshBackendAsset;

	/** Load the serialized  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

	UPROPERTY()
	UBeamEnvironmentData* Data;

	UFUNCTION()
	FString GetAPIUrl();

	UFUNCTION()
	bool RefreshEnvData();

	UFUNCTION()
	void PullRoutesConfig(UBeamEnvironmentData* EnvData);
};
