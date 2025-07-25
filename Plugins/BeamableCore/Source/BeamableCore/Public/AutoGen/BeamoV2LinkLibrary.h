#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2Link.h"

#include "BeamoV2LinkLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2LinkLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2Link To JSON String")
	static FString BeamoV2LinkToJsonString(const UBeamoV2Link* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2Link", meta=(DefaultToSelf="Outer", AdvancedDisplay="Href, Rel, Outer", NativeMakeFunc))
	static UBeamoV2Link* Make(FOptionalString Href, FOptionalString Rel, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2Link", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2Link* Serializable, FOptionalString& Href, FOptionalString& Rel);
};