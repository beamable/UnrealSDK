#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ProtoError.h"

#include "BeamoV2ProtoErrorLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ProtoErrorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ProtoError To JSON String")
	static FString BeamoV2ProtoErrorToJsonString(const UBeamoV2ProtoError* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ProtoError", meta=(DefaultToSelf="Outer", AdvancedDisplay="Status, Error, Description, Outer", NativeMakeFunc))
	static UBeamoV2ProtoError* Make(FOptionalInt32 Status, FOptionalString Error, FOptionalString Description, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ProtoError", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ProtoError* Serializable, FOptionalInt32& Status, FOptionalString& Error, FOptionalString& Description);
};