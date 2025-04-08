#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceDependencyReference.h"

#include "ServiceDependencyReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceDependencyReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="ServiceDependencyReference To JSON String")
	static FString ServiceDependencyReferenceToJsonString(const UServiceDependencyReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make ServiceDependencyReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServiceDependencyReference* Make(FString Id, FString StorageType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break ServiceDependencyReference", meta=(NativeBreakFunc))
	static void Break(const UServiceDependencyReference* Serializable, FString& Id, FString& StorageType);
};