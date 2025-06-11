#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetStatusResponse.h"

#include "GetStatusResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetStatusResponse To JSON String")
	static FString GetStatusResponseToJsonString(const UGetStatusResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetStatusResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="StorageStatuses, Outer", NativeMakeFunc))
	static UGetStatusResponse* Make(bool bIsCurrent, TArray<UServiceStatus*> Services, FOptionalArrayOfServiceStorageStatus StorageStatuses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetStatusResponse", meta=(NativeBreakFunc))
	static void Break(const UGetStatusResponse* Serializable, bool& bIsCurrent, TArray<UServiceStatus*>& Services, FOptionalArrayOfServiceStorageStatus& StorageStatuses);
};