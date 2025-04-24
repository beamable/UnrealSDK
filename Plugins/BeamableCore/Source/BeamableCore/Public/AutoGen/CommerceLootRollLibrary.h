#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CommerceLootRoll.h"

#include "CommerceLootRollLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCommerceLootRollLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="CommerceLootRoll To JSON String")
	static FString CommerceLootRollToJsonString(const UCommerceLootRoll* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make CommerceLootRoll", meta=(DefaultToSelf="Outer", AdvancedDisplay="ExternalTables, Outer", NativeMakeFunc))
	static UCommerceLootRoll* Make(bool bPreroll, FOptionalArrayOfString ExternalTables, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break CommerceLootRoll", meta=(NativeBreakFunc))
	static void Break(const UCommerceLootRoll* Serializable, bool& bPreroll, FOptionalArrayOfString& ExternalTables);
};