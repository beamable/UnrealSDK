#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorNewGameRequestBody.h"

#include "CustomerActorNewGameRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorNewGameRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorNewGameRequestBody To JSON String")
	static FString CustomerActorNewGameRequestBodyToJsonString(const UCustomerActorNewGameRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorNewGameRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsHidden, Outer", NativeMakeFunc))
	static UCustomerActorNewGameRequestBody* Make(FString GameName, FOptionalBool bIsHidden, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorNewGameRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorNewGameRequestBody* Serializable, FString& GameName, FOptionalBool& bIsHidden);
};