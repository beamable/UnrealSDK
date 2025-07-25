#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceStorageStatus.h"

#include "ServiceStorageStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceStorageStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceStorageStatus To JSON String")
	static FString ServiceStorageStatusToJsonString(const UServiceStorageStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceStorageStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServiceStorageStatus* Make(bool bIsCurrent, bool bIsRunning, FString Id, FString StorageType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceStorageStatus", meta=(NativeBreakFunc))
	static void Break(const UServiceStorageStatus* Serializable, bool& bIsCurrent, bool& bIsRunning, FString& Id, FString& StorageType);
};