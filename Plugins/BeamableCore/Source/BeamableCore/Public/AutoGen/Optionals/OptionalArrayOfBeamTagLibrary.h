#pragma once

#include "CoreMinimal.h"
<<<<<<<< HEAD:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/Optionals/OptionalSessionUserLibrary.h
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSessionUser.h"

#include "OptionalSessionUserLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalSessionUserLibrary : public UBlueprintFunctionLibrary
========
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamTag.h"

#include "OptionalArrayOfBeamTagLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamTagLibrary : public UBlueprintFunctionLibrary
>>>>>>>> main:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamTagLibrary.h
{
	GENERATED_BODY()
public:	

	/**
<<<<<<<< HEAD:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/Optionals/OptionalSessionUserLibrary.h
	* @brief Constructs an FOptionalSessionUser struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional SessionUser", NativeMakeFunc))
	static FOptionalSessionUser MakeOptional(USessionUser* Value);

	/**
	 * @brief Converts an USessionUser* into an FOptionalSessionUser automatically.
	 * @param Value The USessionUser* to convert.
	 * @return An optional with the SessionUser set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - SessionUser To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalSessionUser Conv_OptionalFromValue(USessionUser* Value);
========
	* @brief Constructs an FOptionalArrayOfBeamTag struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional TArray<FBeamTag>", NativeMakeFunc))
	static FOptionalArrayOfBeamTag MakeOptional(TArray<FBeamTag> Value);

	/**
	 * @brief Converts an TArray<FBeamTag> into an FOptionalArrayOfBeamTag automatically.
	 * @param Value The TArray<FBeamTag> to convert.
	 * @return An optional with the TArray<FBeamTag> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - TArray<FBeamTag> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamTag Conv_OptionalFromValue(TArray<FBeamTag> Value);
>>>>>>>> main:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamTagLibrary.h
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Beam - Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
<<<<<<<< HEAD:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/Optionals/OptionalSessionUserLibrary.h
	static bool HasValue(const FOptionalSessionUser& Optional, USessionUser*& Value);
========
	static bool HasValue(const FOptionalArrayOfBeamTag& Optional, TArray<FBeamTag>& Value);
>>>>>>>> main:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamTagLibrary.h

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
<<<<<<<< HEAD:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/Optionals/OptionalSessionUserLibrary.h
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's SessionUser Value"))
	static USessionUser* GetOptionalValue(const FOptionalSessionUser& Optional, USessionUser* DefaultValue, bool& WasSet);
========
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's TArray<FBeamTag> Value"))
	static TArray<FBeamTag> GetOptionalValue(const FOptionalArrayOfBeamTag& Optional, TArray<FBeamTag> DefaultValue, bool& WasSet);
>>>>>>>> main:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamTagLibrary.h

	
};
