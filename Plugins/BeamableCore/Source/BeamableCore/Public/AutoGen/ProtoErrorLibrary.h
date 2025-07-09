#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ProtoError.h"

#include "ProtoErrorLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UProtoErrorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ProtoError To JSON String")
	static FString ProtoErrorToJsonString(const UProtoError* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ProtoError", meta=(DefaultToSelf="Outer", AdvancedDisplay="Status, Error, Description, Outer", NativeMakeFunc))
	static UProtoError* Make(FOptionalInt32 Status, FOptionalString Error, FOptionalString Description, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ProtoError", meta=(NativeBreakFunc))
	static void Break(const UProtoError* Serializable, FOptionalInt32& Status, FOptionalString& Error, FOptionalString& Description);
};