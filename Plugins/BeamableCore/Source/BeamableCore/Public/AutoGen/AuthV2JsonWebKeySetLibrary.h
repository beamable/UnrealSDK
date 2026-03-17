#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2JsonWebKeySet.h"

#include "AuthV2JsonWebKeySetLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2JsonWebKeySetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2JsonWebKeySet To JSON String")
	static FString AuthV2JsonWebKeySetToJsonString(const UAuthV2JsonWebKeySet* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2JsonWebKeySet", meta=(DefaultToSelf="Outer", AdvancedDisplay="Keys, Outer", NativeMakeFunc))
	static UAuthV2JsonWebKeySet* Make(FOptionalArrayOfAuthV2JsonWebKey Keys, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2JsonWebKeySet", meta=(NativeBreakFunc))
	static void Break(const UAuthV2JsonWebKeySet* Serializable, FOptionalArrayOfAuthV2JsonWebKey& Keys);
};