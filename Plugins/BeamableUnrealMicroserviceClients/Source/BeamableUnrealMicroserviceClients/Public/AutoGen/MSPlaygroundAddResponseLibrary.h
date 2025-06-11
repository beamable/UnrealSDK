#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundAddResponse.h"

#include "MSPlaygroundAddResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMSPlaygroundAddResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Json", DisplayName="MSPlaygroundAddResponse To JSON String")
	static FString MSPlaygroundAddResponseToJsonString(const UMSPlaygroundAddResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Make MSPlaygroundAddResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMSPlaygroundAddResponse* Make(int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Break MSPlaygroundAddResponse", meta=(NativeBreakFunc))
	static void Break(const UMSPlaygroundAddResponse* Serializable, int32& Value);
};