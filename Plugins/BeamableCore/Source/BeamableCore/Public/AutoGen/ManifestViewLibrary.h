#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ManifestView.h"

#include "ManifestViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UManifestViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ManifestView To JSON String")
	static FString ManifestViewToJsonString(const UManifestView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ManifestView", meta=(DefaultToSelf="Outer", AdvancedDisplay="CreatedByAccountId, Comments, StorageReference, Outer", NativeMakeFunc))
	static UManifestView* Make(FString Id, FString Checksum, int64 Created, TArray<UServiceReference*> Manifest, FOptionalInt64 CreatedByAccountId, FOptionalString Comments, FOptionalArrayOfServiceStorageReference StorageReference, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ManifestView", meta=(NativeBreakFunc))
	static void Break(const UManifestView* Serializable, FString& Id, FString& Checksum, int64& Created, TArray<UServiceReference*>& Manifest, FOptionalInt64& CreatedByAccountId, FOptionalString& Comments, FOptionalArrayOfServiceStorageReference& StorageReference);
};