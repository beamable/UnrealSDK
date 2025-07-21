#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2StringStringKeyValuePair.h"

#include "BeamoV2StringStringKeyValuePairLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2StringStringKeyValuePairLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2StringStringKeyValuePair To JSON String")
	static FString BeamoV2StringStringKeyValuePairToJsonString(const UBeamoV2StringStringKeyValuePair* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2StringStringKeyValuePair", meta=(DefaultToSelf="Outer", AdvancedDisplay="Key, Value, Outer", NativeMakeFunc))
	static UBeamoV2StringStringKeyValuePair* Make(FOptionalString Key, FOptionalString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2StringStringKeyValuePair", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2StringStringKeyValuePair* Serializable, FOptionalString& Key, FOptionalString& Value);
};