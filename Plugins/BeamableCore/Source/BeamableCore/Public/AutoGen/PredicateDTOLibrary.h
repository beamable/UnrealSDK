#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PredicateDTO.h"

#include "PredicateDTOLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPredicateDTOLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="PredicateDTO To JSON String")
	static FString PredicateDTOToJsonString(const UPredicateDTO* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make PredicateDTO", meta=(DefaultToSelf="Outer", AdvancedDisplay="As, bCaseInsensitive, bIncludeLower, bIncludeUpper, Lower, Upper, Substr, Value, Values, Outer", NativeMakeFunc))
	static UPredicateDTO* Make(FString Kind, FOptionalString As, FOptionalBool bCaseInsensitive, FOptionalBool bIncludeLower, FOptionalBool bIncludeUpper, FOptionalString Lower, FOptionalString Upper, FOptionalString Substr, FOptionalString Value, FOptionalArrayOfString Values, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break PredicateDTO", meta=(NativeBreakFunc))
	static void Break(const UPredicateDTO* Serializable, FString& Kind, FOptionalString& As, FOptionalBool& bCaseInsensitive, FOptionalBool& bIncludeLower, FOptionalBool& bIncludeUpper, FOptionalString& Lower, FOptionalString& Upper, FOptionalString& Substr, FOptionalString& Value, FOptionalArrayOfString& Values);
};