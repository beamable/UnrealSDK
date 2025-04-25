#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetSkusReq.h"

#include "GetSkusReqLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetSkusReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="GetSkusReq To JSON String")
	static FString GetSkusReqToJsonString(const UGetSkusReq* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make GetSkusReq", meta=(DefaultToSelf="Outer", AdvancedDisplay="Version, Outer", NativeMakeFunc))
	static UGetSkusReq* Make(FOptionalInt64 Version, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break GetSkusReq", meta=(NativeBreakFunc))
	static void Break(const UGetSkusReq* Serializable, FOptionalInt64& Version);
};