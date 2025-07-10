#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StringStringKeyValuePair.h"

#include "StringStringKeyValuePairLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStringStringKeyValuePairLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="StringStringKeyValuePair To JSON String")
	static FString StringStringKeyValuePairToJsonString(const UStringStringKeyValuePair* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make StringStringKeyValuePair", meta=(DefaultToSelf="Outer", AdvancedDisplay="Key, Value, Outer", NativeMakeFunc))
	static UStringStringKeyValuePair* Make(FOptionalString Key, FOptionalString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break StringStringKeyValuePair", meta=(NativeBreakFunc))
	static void Break(const UStringStringKeyValuePair* Serializable, FOptionalString& Key, FOptionalString& Value);
};