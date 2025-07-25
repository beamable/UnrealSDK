#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceComponent.h"

#include "BeamoV2ServiceComponentLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceComponentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceComponent To JSON String")
	static FString BeamoV2ServiceComponentToJsonString(const UBeamoV2ServiceComponent* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceComponent", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Outer", NativeMakeFunc))
	static UBeamoV2ServiceComponent* Make(FOptionalString Name, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceComponent", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceComponent* Serializable, FOptionalString& Name);
};