#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetGroupsRequestBody.h"

#include "GetGroupsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetGroupsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="GetGroupsRequestBody To JSON String")
	static FString GetGroupsRequestBodyToJsonString(const UGetGroupsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetGroupsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Max, Focus, Cycle, From, ContentId, Outer", NativeMakeFunc))
	static UGetGroupsRequestBody* Make(FString TournamentId, FOptionalInt32 Max, FOptionalInt64 Focus, FOptionalInt32 Cycle, FOptionalInt32 From, FOptionalString ContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break GetGroupsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetGroupsRequestBody* Serializable, FString& TournamentId, FOptionalInt32& Max, FOptionalInt64& Focus, FOptionalInt32& Cycle, FOptionalInt32& From, FOptionalString& ContentId);
};