#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetManifestHistoryRequestBody.h"

#include "GetManifestHistoryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestHistoryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetManifestHistoryRequestBody To JSON String")
	static FString GetManifestHistoryRequestBodyToJsonString(const UGetManifestHistoryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestHistoryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Limit, Outer", NativeMakeFunc))
	static UGetManifestHistoryRequestBody* Make(FOptionalBeamContentManifestId Id, FOptionalInt32 Limit, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetManifestHistoryRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetManifestHistoryRequestBody* Serializable, FOptionalBeamContentManifestId& Id, FOptionalInt32& Limit);
};