#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MicroserviceSecretResponse.h"

#include "MicroserviceSecretResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMicroserviceSecretResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="MicroserviceSecretResponse To JSON String")
	static FString MicroserviceSecretResponseToJsonString(const UMicroserviceSecretResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make MicroserviceSecretResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMicroserviceSecretResponse* Make(FString Secret, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break MicroserviceSecretResponse", meta=(NativeBreakFunc))
	static void Break(const UMicroserviceSecretResponse* Serializable, FString& Secret);
};