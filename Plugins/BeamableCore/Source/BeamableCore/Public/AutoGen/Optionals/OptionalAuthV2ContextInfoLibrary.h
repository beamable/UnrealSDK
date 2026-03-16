#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAuthV2ContextInfo.h"

#include "OptionalAuthV2ContextInfoLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalAuthV2ContextInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalAuthV2ContextInfo struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Make Optional AuthV2ContextInfo", NativeMakeFunc))
	static FOptionalAuthV2ContextInfo MakeOptional(UAuthV2ContextInfo* Value);

	/**
	 * @brief Converts an UAuthV2ContextInfo* into an FOptionalAuthV2ContextInfo automatically.
	 * @param Value The UAuthV2ContextInfo* to convert.
	 * @return An optional with the AuthV2ContextInfo set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta = (DisplayName="AuthV2ContextInfo To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalAuthV2ContextInfo Conv_OptionalFromValue(UAuthV2ContextInfo* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalAuthV2ContextInfo& Optional, UAuthV2ContextInfo*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Get Optional's AuthV2ContextInfo Value"))
	static UAuthV2ContextInfo* GetOptionalValue(const FOptionalAuthV2ContextInfo& Optional, UAuthV2ContextInfo* DefaultValue, bool& WasSet);

	
};
