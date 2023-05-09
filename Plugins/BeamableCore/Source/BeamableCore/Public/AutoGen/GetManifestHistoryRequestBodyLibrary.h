#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetManifestHistoryRequestBody.h"

#include "GetManifestHistoryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestHistoryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetManifestHistoryRequestBody To JSON String")
	static FString GetManifestHistoryRequestBodyToJsonString(const UGetManifestHistoryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetManifestHistoryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Limit, Outer", NativeMakeFunc))
	static UGetManifestHistoryRequestBody* Make(FOptionalBeamContentManifestId Id, FOptionalInt32 Limit, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetManifestHistoryRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetManifestHistoryRequestBody* Serializable, FOptionalBeamContentManifestId& Id, FOptionalInt32& Limit);
};