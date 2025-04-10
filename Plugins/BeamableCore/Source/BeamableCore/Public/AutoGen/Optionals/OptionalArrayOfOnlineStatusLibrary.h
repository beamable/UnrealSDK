#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfOnlineStatus.h"

#include "OptionalArrayOfOnlineStatusLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfOnlineStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfOnlineStatus struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UOnlineStatus*>", NativeMakeFunc))
	static FOptionalArrayOfOnlineStatus MakeOptional(TArray<UOnlineStatus*> Value);

	/**
	 * @brief Converts an TArray<UOnlineStatus*> into an FOptionalArrayOfOnlineStatus automatically.
	 * @param Value The TArray<UOnlineStatus*> to convert.
	 * @return An optional with the TArray<UOnlineStatus*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Optionals", meta = (DisplayName="TArray<UOnlineStatus*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfOnlineStatus Conv_OptionalFromValue(TArray<UOnlineStatus*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Presence|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfOnlineStatus& Optional, TArray<UOnlineStatus*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UOnlineStatus*> Value"))
	static TArray<UOnlineStatus*> GetOptionalValue(const FOptionalArrayOfOnlineStatus& Optional, TArray<UOnlineStatus*> DefaultValue, bool& WasSet);

	
};
