#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceDependencyReference.h"

#include "ServiceDependencyReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceDependencyReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServiceDependencyReference To JSON String")
	static FString ServiceDependencyReferenceToJsonString(const UServiceDependencyReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServiceDependencyReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServiceDependencyReference* Make(FString Id, FString StorageType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServiceDependencyReference", meta=(NativeBreakFunc))
	static void Break(const UServiceDependencyReference* Serializable, FString& Id, FString& StorageType);
};