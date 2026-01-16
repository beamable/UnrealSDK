#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdatePartyTags.h"

#include "UpdatePartyTagsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdatePartyTagsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Json", DisplayName="UpdatePartyTags To JSON String")
	static FString UpdatePartyTagsToJsonString(const UUpdatePartyTags* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Make UpdatePartyTags", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, MemberTags, Outer", NativeMakeFunc))
	static UUpdatePartyTags* Make(FOptionalString PlayerId, FOptionalArrayOfBeamTag MemberTags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Break UpdatePartyTags", meta=(NativeBreakFunc))
	static void Break(const UUpdatePartyTags* Serializable, FOptionalString& PlayerId, FOptionalArrayOfBeamTag& MemberTags);
};