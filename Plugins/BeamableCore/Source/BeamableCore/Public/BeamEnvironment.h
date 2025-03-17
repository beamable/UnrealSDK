// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Serialization/JsonSerializerMacros.h"
#include "Subsystems/EngineSubsystem.h"
#include "BeamEnvironment.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPackageVersion
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

	bool IsReleaseCandidate() const { return RC > UNASSIGNED_VALUE; }
	bool IsNightly() const { return NightlyTime > UNASSIGNED_VALUE; }

	FBeamPackageVersion();

	FBeamPackageVersion(int major, int minor, int patch, int rc = -1, long nightlyTime = -1, bool isPreview = false);

	explicit FBeamPackageVersion(const FString& VersionString);

	bool Equals(const FBeamPackageVersion Other) const;

	bool operator<(const FBeamPackageVersion& BeamPackageVersion) const;

	bool operator>(const FBeamPackageVersion& BeamPackageVersion) const;

	bool operator==(const FBeamPackageVersion& BeamPackageVersion) const;

	bool operator !=(const FBeamPackageVersion& BeamPackageVersion) const;

	bool operator <=(const FBeamPackageVersion& BeamPackageVersion) const;

	bool operator >=(const FBeamPackageVersion& BeamPackageVersion) const;

	FString ToString() const;

	static FBeamPackageVersion FromString(FString SemanticVersion);

	friend FArchive& operator<<(FArchive& Ar, FBeamPackageVersion& D)
	{
		Ar.SerializeBits(&D.Major, sizeof(D.Major) * 8);
		Ar.SerializeBits(&D.Minor, sizeof(D.Minor) * 8);
		Ar.SerializeBits(&D.Patch, sizeof(D.Patch) * 8);
		Ar.SerializeBits(&D.RC, sizeof(D.RC) * 8);
		Ar.SerializeBits(&D.NightlyTime, sizeof(D.NightlyTime) * 8);
		if (Ar.IsSaving())
		{
			uint32 Preview = D.bIsPreview ? 1 : 0;
			Ar.SerializeInt(Preview, 1);
		}
		else
		{
			uint32 Preview;
			Ar.SerializeInt(Preview, 1);
			D.bIsPreview = Preview == 1;
		}
		return Ar;
	}
};


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamEnvironmentData : public UDataAsset, public FJsonSerializable
{
	GENERATED_BODY()

public:
	using UDataAsset::Serialize; // Bring Serialize from UDataAsset into scope
	using FJsonSerializable::Serialize; // Bring Serialize from FJsonSerializable into scope

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
	FString DocsUrl;

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


	UPROPERTY()
	UBeamEnvironmentData* Data;

	UFUNCTION()
	FString GetAPIUrl();
};
