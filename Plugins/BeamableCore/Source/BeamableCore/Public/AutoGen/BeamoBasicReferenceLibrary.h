#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoBasicReference.h"

#include "BeamoBasicReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoBasicReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoBasicReference To JSON String")
	static FString BeamoBasicReferenceToJsonString(const UBeamoBasicReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoBasicReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoBasicReference* Make(bool bArchived, bool bArm, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoBasicReference", meta=(NativeBreakFunc))
	static void Break(const UBeamoBasicReference* Serializable, bool& bArchived, bool& bArm);
};