#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OtelView.h"

#include "OtelViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOtelViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Json", DisplayName="OtelView To JSON String")
	static FString OtelViewToJsonString(const UOtelView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make OtelView", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsFavorite, bIsPublic, Id, Outer", NativeMakeFunc))
	static UOtelView* Make(FString PlayerId, FString Name, FString Query, FOptionalBool bIsFavorite, FOptionalBool bIsPublic, FOptionalObjectId Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Break OtelView", meta=(NativeBreakFunc))
	static void Break(const UOtelView* Serializable, FString& PlayerId, FString& Name, FString& Query, FOptionalBool& bIsFavorite, FOptionalBool& bIsPublic, FOptionalObjectId& Id);
};