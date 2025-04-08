#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetCatalogReq.h"

#include "GetCatalogReqLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetCatalogReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="GetCatalogReq To JSON String")
	static FString GetCatalogReqToJsonString(const UGetCatalogReq* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make GetCatalogReq", meta=(DefaultToSelf="Outer", AdvancedDisplay="Version, Outer", NativeMakeFunc))
	static UGetCatalogReq* Make(FOptionalInt64 Version, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break GetCatalogReq", meta=(NativeBreakFunc))
	static void Break(const UGetCatalogReq* Serializable, FOptionalInt64& Version);
};