#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalContextInfo.h"

#include "OptionalContextInfoLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalContextInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalContextInfo struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Make Optional ContextInfo", NativeMakeFunc))
	static FOptionalContextInfo MakeOptional(UContextInfo* Value);

	/**
	 * @brief Converts an UContextInfo* into an FOptionalContextInfo automatically.
	 * @param Value The UContextInfo* to convert.
	 * @return An optional with the ContextInfo set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta = (DisplayName="ContextInfo To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalContextInfo Conv_OptionalFromValue(UContextInfo* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalContextInfo& Optional, UContextInfo*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Get Optional's ContextInfo Value"))
	static UContextInfo* GetOptionalValue(const FOptionalContextInfo& Optional, UContextInfo* DefaultValue, bool& WasSet);

	
};
