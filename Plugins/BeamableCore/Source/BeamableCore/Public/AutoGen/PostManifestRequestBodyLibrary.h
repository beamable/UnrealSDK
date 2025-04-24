#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PostManifestRequestBody.h"

#include "PostManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPostManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="PostManifestRequestBody To JSON String")
	static FString PostManifestRequestBodyToJsonString(const UPostManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bAutoDeploy, Comments, StorageReferences, Outer", NativeMakeFunc))
	static UPostManifestRequestBody* Make(TArray<UServiceReference*> Manifest, FOptionalBool bAutoDeploy, FOptionalString Comments, FOptionalArrayOfServiceStorageReference StorageReferences, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break PostManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPostManifestRequestBody* Serializable, TArray<UServiceReference*>& Manifest, FOptionalBool& bAutoDeploy, FOptionalString& Comments, FOptionalArrayOfServiceStorageReference& StorageReferences);
};