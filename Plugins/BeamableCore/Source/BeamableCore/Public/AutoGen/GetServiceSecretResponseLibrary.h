#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetServiceSecretResponse.h"

#include "GetServiceSecretResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetServiceSecretResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetServiceSecretResponse To JSON String")
	static FString GetServiceSecretResponseToJsonString(const UGetServiceSecretResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetServiceSecretResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Secret, Outer", NativeMakeFunc))
	static UGetServiceSecretResponse* Make(FOptionalString Secret, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetServiceSecretResponse", meta=(NativeBreakFunc))
	static void Break(const UGetServiceSecretResponse* Serializable, FOptionalString& Secret);
};