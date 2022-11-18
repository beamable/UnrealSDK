// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Json/Public/Serialization/JsonSerializerMacros.h"
#include "Subsystems/EngineSubsystem.h"
#include "BeamEnvironment.generated.h"

USTRUCT(BlueprintType)
struct FBeamPackageVersion
{
	GENERATED_BODY()

	const static FString PREVIEW_STRING;
	const static FString RC_STRING;
	const static FString NIGHTLY_STRING;

	const static int UNASSIGNED_VALUE;
	const static char VERSION_SEPARATOR;
	const static char PREVIEW_SEPARATOR;


	UPROPERTY(EditAnywhere)
	int Major = UNASSIGNED_VALUE;
	UPROPERTY(EditAnywhere)
	int Minor = UNASSIGNED_VALUE;
	UPROPERTY(EditAnywhere)
	int Patch = UNASSIGNED_VALUE;
	UPROPERTY(EditAnywhere)
	int RC = UNASSIGNED_VALUE;

	UPROPERTY(EditAnywhere)
	int64 NightlyTime = UNASSIGNED_VALUE;

	UPROPERTY(EditAnywhere)
	bool bIsPreview = false;

	FORCEINLINE bool IsReleaseCandidate() const { return RC > UNASSIGNED_VALUE; }
	FORCEINLINE bool IsNightly() const { return NightlyTime > UNASSIGNED_VALUE; }

	FBeamPackageVersion();

	FBeamPackageVersion(int major, int minor, int patch, int rc = -1, long nightlyTime = -1, bool isPreview = false);

	explicit FBeamPackageVersion(const FString& VersionString);

	FORCEINLINE bool Equals(const FBeamPackageVersion Other) const;

	FORCEINLINE bool operator<(const FBeamPackageVersion& BeamPackageVersion) const;

	FORCEINLINE bool operator>(const FBeamPackageVersion& BeamPackageVersion) const;

	FORCEINLINE bool operator==(const FBeamPackageVersion& BeamPackageVersion) const;

	FORCEINLINE bool operator !=(const FBeamPackageVersion& BeamPackageVersion) const;

	FORCEINLINE bool operator <=(const FBeamPackageVersion& BeamPackageVersion) const;

	FORCEINLINE bool operator >=(const FBeamPackageVersion& BeamPackageVersion) const;

	FString ToString() const;

	static FBeamPackageVersion FromString(FString SemanticVersion);
};


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamEnvironmentData : public UDataAsset, public FJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Environment;
	UPROPERTY(EditAnywhere)
	FString APIUrl;
	UPROPERTY(EditAnywhere)
	FString PortalUrl;
	UPROPERTY(EditAnywhere)
	FString BeamMongoExpressUrl;
	UPROPERTY(EditAnywhere)
	FString SDKVersion;
	UPROPERTY(EditAnywhere)
	FString DockerRegistryUrl;

	UPROPERTY(EditAnywhere)
	FBeamPackageVersion Version;

	virtual void Serialize(FJsonSerializerBase& Serializer, bool bFlatObject) override;
};


/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamEnvironment : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	/** Load the serialized  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;


	UBeamEnvironmentData* Data;

	UFUNCTION()
	FString GetAPIUrl();
};
