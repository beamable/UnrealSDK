#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCustomerActorCustomer.h"

#include "OptionalArrayOfCustomerActorCustomerLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfCustomerActorCustomerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfCustomerActorCustomer struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UCustomerActorCustomer*>", NativeMakeFunc))
	static FOptionalArrayOfCustomerActorCustomer MakeOptional(TArray<UCustomerActorCustomer*> Value);

	/**
	 * @brief Converts an TArray<UCustomerActorCustomer*> into an FOptionalArrayOfCustomerActorCustomer automatically.
	 * @param Value The TArray<UCustomerActorCustomer*> to convert.
	 * @return An optional with the TArray<UCustomerActorCustomer*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Optionals", meta = (DisplayName="TArray<UCustomerActorCustomer*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfCustomerActorCustomer Conv_OptionalFromValue(TArray<UCustomerActorCustomer*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Customer|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfCustomerActorCustomer& Optional, TArray<UCustomerActorCustomer*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UCustomerActorCustomer*> Value"))
	static TArray<UCustomerActorCustomer*> GetOptionalValue(const FOptionalArrayOfCustomerActorCustomer& Optional, TArray<UCustomerActorCustomer*> DefaultValue, bool& WasSet);

	
};
