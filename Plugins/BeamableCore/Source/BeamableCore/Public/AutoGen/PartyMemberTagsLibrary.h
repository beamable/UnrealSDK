#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PartyMemberTags.h"

#include "PartyMemberTagsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPartyMemberTagsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Json", DisplayName="PartyMemberTags To JSON String")
	static FString PartyMemberTagsToJsonString(const UPartyMemberTags* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Make PartyMemberTags", meta=(DefaultToSelf="Outer", AdvancedDisplay="MemberTags, Outer", NativeMakeFunc))
	static UPartyMemberTags* Make(FOptionalArrayOfBeamTag MemberTags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Break PartyMemberTags", meta=(NativeBreakFunc))
	static void Break(const UPartyMemberTags* Serializable, FOptionalArrayOfBeamTag& MemberTags);
};