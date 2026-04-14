#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2ProtoError.h"

#include "AuthV2ProtoErrorLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2ProtoErrorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2ProtoError To JSON String")
	static FString AuthV2ProtoErrorToJsonString(const UAuthV2ProtoError* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2ProtoError", meta=(DefaultToSelf="Outer", AdvancedDisplay="Status, Error, Description, Outer", NativeMakeFunc))
	static UAuthV2ProtoError* Make(FOptionalInt32 Status, FOptionalString Error, FOptionalString Description, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2ProtoError", meta=(NativeBreakFunc))
	static void Break(const UAuthV2ProtoError* Serializable, FOptionalInt32& Status, FOptionalString& Error, FOptionalString& Description);
};