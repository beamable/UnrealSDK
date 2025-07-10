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

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceStorageStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsCurrent, bIsRunning, Id, StorageType, Outer", NativeMakeFunc))
	static UServiceStorageStatus* Make(FOptionalBool bIsCurrent, FOptionalBool bIsRunning, FOptionalString Id, FOptionalString StorageType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceStorageStatus", meta=(NativeBreakFunc))
	static void Break(const UServiceStorageStatus* Serializable, FOptionalBool& bIsCurrent, FOptionalBool& bIsRunning, FOptionalString& Id, FOptionalString& StorageType);
};