#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateOtelViewRequestBody.h"

#include "UpdateOtelViewRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateOtelViewRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Json", DisplayName="UpdateOtelViewRequestBody To JSON String")
	static FString UpdateOtelViewRequestBodyToJsonString(const UUpdateOtelViewRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make UpdateOtelViewRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsFavorite, bIsPublic, Name, Query, Outer", NativeMakeFunc))
	static UUpdateOtelViewRequestBody* Make(FOptionalBool bIsFavorite, FOptionalBool bIsPublic, FOptionalString Name, FOptionalString Query, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Break UpdateOtelViewRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUpdateOtelViewRequestBody* Serializable, FOptionalBool& bIsFavorite, FOptionalBool& bIsPublic, FOptionalString& Name, FOptionalString& Query);
};