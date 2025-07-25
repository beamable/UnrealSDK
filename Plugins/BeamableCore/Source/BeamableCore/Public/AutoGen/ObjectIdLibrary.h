#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ObjectId.h"

#include "ObjectIdLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UObjectIdLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Json", DisplayName="ObjectId To JSON String")
	static FString ObjectIdToJsonString(const UObjectId* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make ObjectId", meta=(DefaultToSelf="Outer", AdvancedDisplay="Timestamp, CreationTime, Outer", NativeMakeFunc))
	static UObjectId* Make(FOptionalInt32 Timestamp, FOptionalDateTime CreationTime, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Break ObjectId", meta=(NativeBreakFunc))
	static void Break(const UObjectId* Serializable, FOptionalInt32& Timestamp, FOptionalDateTime& CreationTime);
};