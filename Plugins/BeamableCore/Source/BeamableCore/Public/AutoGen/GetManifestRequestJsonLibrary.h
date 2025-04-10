#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetManifestRequestJson.h"

#include "GetManifestRequestJsonLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestRequestJsonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetManifestRequestJson To JSON String")
	static FString GetManifestRequestJsonToJsonString(const UGetManifestRequestJson* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestRequestJson", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Uid, Outer", NativeMakeFunc))
	static UGetManifestRequestJson* Make(FOptionalBeamContentManifestId Id, FOptionalString Uid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetManifestRequestJson", meta=(NativeBreakFunc))
	static void Break(const UGetManifestRequestJson* Serializable, FOptionalBeamContentManifestId& Id, FOptionalString& Uid);
};