// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Serialization/JsonSerializerMacros.h"
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


	UPROPERTY(EditAnywhere,Category="Beam")
	int Major = UNASSIGNED_VALUE;
	UPROPERTY(EditAnywhere,Category="Beam")
	int Minor = UNASSIGNED_VALUE;
	UPROPERTY(EditAnywhere,Category="Beam")
	int Patch = UNASSIGNED_VALUE;
	UPROPERTY(EditAnywhere,Category="Beam")
	int RC = UNASSIGNED_VALUE;

	UPROPERTY(EditAnywhere,Category="Beam")
	int64 NightlyTime = UNASSIGNED_VALUE;

	UPROPERTY(EditAnywhere,Category="Beam")
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
	
	using UDataAsset::Serialize; // Bring Serialize from UDataAsset into scope
	using FJsonSerializable::Serialize; // Bring Serialize from FJsonSerializable into scope
	
	UPROPERTY(EditAnywhere,Category="Beam")
	FString Environment;
	UPROPERTY(EditAnywhere,Category="Beam")
	FString APIUrl;
	UPROPERTY(EditAnywhere,Category="Beam")
	FString PortalUrl;
	UPROPERTY(EditAnywhere,Category="Beam")
	FString BeamMongoExpressUrl;
	UPROPERTY(EditAnywhere,Category="Beam")
	FString SDKVersion;
	UPROPERTY(EditAnywhere,Category="Beam")
	FString DockerRegistryUrl;

	UPROPERTY(EditAnywhere,Category="Beam")
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


	UPROPERTY()
	UBeamEnvironmentData* Data;

	UFUNCTION()
	FString GetAPIUrl();
};
