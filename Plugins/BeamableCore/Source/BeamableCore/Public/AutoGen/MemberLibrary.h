
#pragma once

#include "CoreMinimal.h"
#include "Member.h"

#include "MemberLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMemberLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Member To JSON String")
	static FString MemberToJsonString(const UMember* Serializable, const bool Pretty);		
};