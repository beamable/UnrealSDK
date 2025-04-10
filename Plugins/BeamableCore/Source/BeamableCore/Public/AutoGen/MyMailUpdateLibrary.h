#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MyMailUpdate.h"

#include "MyMailUpdateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMyMailUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="MyMailUpdate To JSON String")
	static FString MyMailUpdateToJsonString(const UMyMailUpdate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make MyMailUpdate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMyMailUpdate* Make(int64 Id, UUpdateMailRequestBody* Update, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break MyMailUpdate", meta=(NativeBreakFunc))
	static void Break(const UMyMailUpdate* Serializable, int64& Id, UUpdateMailRequestBody*& Update);
};