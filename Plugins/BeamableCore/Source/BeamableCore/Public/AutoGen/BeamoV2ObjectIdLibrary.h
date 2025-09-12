#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ObjectId.h"

#include "BeamoV2ObjectIdLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ObjectIdLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ObjectId To JSON String")
	static FString BeamoV2ObjectIdToJsonString(const UBeamoV2ObjectId* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ObjectId", meta=(DefaultToSelf="Outer", AdvancedDisplay="Timestamp, CreationTime, Outer", NativeMakeFunc))
	static UBeamoV2ObjectId* Make(FOptionalInt32 Timestamp, FOptionalDateTime CreationTime, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ObjectId", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ObjectId* Serializable, FOptionalInt32& Timestamp, FOptionalDateTime& CreationTime);
};