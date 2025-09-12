#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PropertyFilterDTO.h"

#include "PropertyFilterDTOLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPropertyFilterDTOLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="PropertyFilterDTO To JSON String")
	static FString PropertyFilterDTOToJsonString(const UPropertyFilterDTO* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make PropertyFilterDTO", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPropertyFilterDTO* Make(FString Key, UPredicateDTO* Predicate, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break PropertyFilterDTO", meta=(NativeBreakFunc))
	static void Break(const UPropertyFilterDTO* Serializable, FString& Key, UPredicateDTO*& Predicate);
};