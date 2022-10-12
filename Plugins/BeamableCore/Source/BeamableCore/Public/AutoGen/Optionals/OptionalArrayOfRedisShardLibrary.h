

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfRedisShard.h"

#include "OptionalArrayOfRedisShardLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfRedisShardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfRedisShard MakeOptionalArrayOfRedisShard(TArray<URedisShard*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<URedisShard*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfRedisShard Conv_OptionalArrayOfRedisShardFromValue(TArray<URedisShard*> Value);
};
