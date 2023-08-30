#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateParty.h"

#include "UpdatePartyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdatePartyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UpdateParty To JSON String")
	static FString UpdatePartyToJsonString(const UUpdateParty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UpdateParty", meta=(DefaultToSelf="Outer", AdvancedDisplay="Restriction, MaxSize, Outer", NativeMakeFunc))
	static UUpdateParty* Make(FOptionalString Restriction, FOptionalInt32 MaxSize, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UpdateParty", meta=(NativeBreakFunc))
	static void Break(const UUpdateParty* Serializable, FOptionalString& Restriction, FOptionalInt32& MaxSize);
};