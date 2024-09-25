#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/PostManifestRequestBody.h"

#include "PostManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPostManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PostManifestRequestBody To JSON String")
	static FString PostManifestRequestBodyToJsonString(const UPostManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PostManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bAutoDeploy, Comments, StorageReferences, Outer", NativeMakeFunc))
	static UPostManifestRequestBody* Make(TArray<UServiceReference*> Manifest, FOptionalBool bAutoDeploy, FOptionalString Comments, FOptionalArrayOfServiceStorageReference StorageReferences, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PostManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPostManifestRequestBody* Serializable, TArray<UServiceReference*>& Manifest, FOptionalBool& bAutoDeploy, FOptionalString& Comments, FOptionalArrayOfServiceStorageReference& StorageReferences);
};