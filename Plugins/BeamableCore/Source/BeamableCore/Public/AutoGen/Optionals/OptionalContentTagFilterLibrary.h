#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalContentTagFilter.h"

#include "OptionalContentTagFilterLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalContentTagFilterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalContentTagFilter struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Make Optional ContentTagFilter", NativeMakeFunc))
	static FOptionalContentTagFilter MakeOptional(UContentTagFilter* Value);

	/**
	 * @brief Converts an UContentTagFilter* into an FOptionalContentTagFilter automatically.
	 * @param Value The UContentTagFilter* to convert.
	 * @return An optional with the ContentTagFilter set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta = (DisplayName="ContentTagFilter To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalContentTagFilter Conv_OptionalFromValue(UContentTagFilter* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalContentTagFilter& Optional, UContentTagFilter*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Get Optional's ContentTagFilter Value"))
	static UContentTagFilter* GetOptionalValue(const FOptionalContentTagFilter& Optional, UContentTagFilter* DefaultValue, bool& WasSet);

	
};
