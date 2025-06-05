// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "JsonDomBuilder.h"

#include "BeamContentObject.generated.h"

class UContentDefinition;
struct FLocalContentManifestRow;

UENUM(BlueprintType)
enum EBeamContentObjectSupportLevel : uint8
{
	FullSupport = 0,
	PartialSupport = 1,
	NoSupport = 2,
};

/**
 * This is the base class for all Beamable ContentObjects. This different serialization modes for different use cases:
 * - BasicJson: Mostly used for printing out the contents of the object. Only serializes Id, Version and UPROPERTIES.
 * - ContentDefinitionJson: Used in the publish flow and makes use of a specific format required for publishing.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class BEAMABLECORE_API UBeamContentObject : public UObject
{
	GENERATED_BODY()


	/**
	 * This list of fields are ignored when iterating through the properties of the content object to build its data.
	 * This enables us to expose these fields in blueprint and serialize them normally as UObjects (for UBeamContentCache), while correctly skipping them when serializing/deserializing content json
	 * objects. See BuildPropertiesJsonObject and ParsePropertiesJsonObject for more details.
	 */
	inline static TArray<FString> FieldsExcludedFromContentJsonSerialization = {"Id", "Version", "Tags", "Created", "LastChanged", "SupportLevel"};

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString Id;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString Version;
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Tags;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FDateTime Created;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FDateTime LastChanged;

	/**
	 * This is "true" for instances of content objects that we download BUT cannot find a type in this client into which we can deserialize them. 
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TEnumAsByte<EBeamContentObjectSupportLevel> SupportLevel = FullSupport;

	/**
	 * @brief Generates a ContentDefinitionJsonObject. This is used during the publish flow. 
	 */
	virtual void BuildContentDefinitionJsonObject(FJsonDomBuilder::FObject& OutContentDefinition);

	/**
	 * @brief Generates an SHA-1 Hash of the ContentObject's subclass properties (serialized in a condensed way and with fields sorted by name).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	FString CreatePropertiesHash();

	/**
	 * @brief Generates a serialized string (in basic format) for this content object.	 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Beam")
	void ToBasicJson(FString& Serialized);
	virtual void ToBasicJson_Implementation(FString& Serialized);

	/**
	 * @brief Parses a serialized string (in basic format) for this content object.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Beam")
	void FromBasicJson(const FString& Json);
	virtual void FromBasicJson_Implementation(const FString& Json);


	void ToPropertiesJson(FString& Serialized);
	void FromPropertiesJson(const FString& Json);

	/**
	 * @brief Builds the basic content object serialized object. 
	 */
	virtual void BuildBasicJsonObject(FJsonDomBuilder::FObject& Output);

	/**
	 * @brief Parses the basic content object serialized object.
	 */
	virtual void ParseBasicJsonObject(const TSharedPtr<FJsonObject>& Object);

	/**
	 * @brief Serializes the UPROPERTIES of this content object.
	 */
	virtual void BuildPropertiesJsonObject(FJsonDomBuilder::FObject& Properties);

	/**
	 * @brief Deserializes the UPROPERTIES of this content object.
	 */
	virtual void ParsePropertiesJsonObject(const TSharedPtr<FJsonObject>& JsonProperties);

	/**
	 * @brief Walks up the ContentObject class hierarchy and creates a '.'-separated string from the top-most type to the current one.
	 * This is leveraged by the Beamable backend for various things (for legacy reasons). 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	FString BuildContentTypeString();

public:
	/**
	 * UTILITIES FOR PARSING/SERIALIZING JSON PROPERTIES VIA REFLECTION. 
	 */


	/**
	 * @brief Serializes a TArray into a FJsonDomBuilder::FArray.
	 * @param PropName The property's name.
	 * @param JsonArray The Json Array for us to fill.
	 * @param ArrayProperty The FArrayProperty for the TArray field we want to access.
	 * @param ArrayOwner Ptr to the struct/object that owns the TArray UProperty.
	 */
	void SerializeArrayProperty(FString PropName, FJsonDomBuilder::FArray& JsonArray, const FArrayProperty* const ArrayProperty, const void* ArrayOwner);

	/**
	 * @brief Deserializes a TArray from a FJsonDomBuilder::FArray.
	 * @param PropName The property's name.
	 * @param JsonArray The Json Array for us to parse.
	 * @param ArrayProperty The FArrayProperty for the TArray field we want to write to.
	 * @param ArrayOwner Ptr to the struct/object that owns the TArray UProperty.
	 */
	void ParseArrayProperty(const FString& PropName, const TArray<TSharedPtr<FJsonValue>>& JsonArray, const FArrayProperty* ArrayProperty, const void* ArrayOwner);

	/**
	 * @brief Serializes a TMap<FString,> into a FJsonDomBuilder::FObject.
	 * @param PropName The property's name.
	 * @param JsonMap The Json Map for us to fill.
	 * @param MapProperty The FMapProperty for the TMap<FString,> field we want to access.
	 * @param MapOwner Ptr to the struct/object that owns the TMap<FString,> UProperty.
	 */
	void SerializeMapProperty(FString PropName, FJsonDomBuilder::FObject& JsonMap, const FMapProperty* const MapProperty, const void* MapOwner);

	/**
	 * @brief Deserializes a TMap<FString,> from a FJsonDomBuilder::FObject.
	 * @param PropName The property's name.
	 * @param JsonMap The Json Map for us to parse.
	 * @param MapProperty The FMapProperty for the TMap<FString,> field we want to access.
	 * @param MapOwner Ptr to the struct/object that owns the TMap<FString,> UProperty.
	 */
	void ParseMapProperty(const FString& PropName, const TSharedPtr<FJsonObject>& JsonMap, const FMapProperty* MapProperty, void* MapOwner);

	template <typename TInner>
	static void BuildArray(FJsonDomBuilder::FArray& ArrayToFill, const FArrayProperty* const ArrayProperty, const void* ArrayOwner)
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));

		const auto ArrayNum = Val->Num();
		for (auto i = 0; i < ArrayNum; i++)
		{
			const TInner* Data = static_cast<const TInner*>(Val->GetData());
			ArrayToFill.Add(*(Data + i));
		}
	}

	template <typename TInner>
	static void BuildMap(FStrProperty* const StrKeyProperty, FJsonDomBuilder::FObject JsonMap, FScriptMapHelper MapHelper)
	{		
		for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
		{
			const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
			const TInner* Data = reinterpret_cast<const TInner*>(MapHelper.GetValuePtr(i));

			JsonMap.Set(Key, *Data);
		}
	}

public:
	// STATIC UTILITIES

	/**
	 * Find the lowest UClass we have the code for that matches the type id string of this content object; if none is found, return a UBeamContentObject instance.
	 * For example, with TypeID='items.my_item_type.my_item_sub_type':
	 * - If we have the code for UMyItemSubType, we'll return an instance of it (with a FullySupported state flag).
	 * - If we don't have the code for UMyItemSubType but do have the code for UMyItemType, we'll return an instance for it (with a PartiallySupported state flag).
	 * - If we have the code ONLY for UBeamItemContent (which we are guaranteed to have), we'll return an instance for it (with a PartiallySupported state flag).
	 * For fully custom hierarchies, for example, with TypeID='my_custom_content.my_sub_content':
	 * - If we have the code for UMySubContent, we'll return an instance of it (with a FullySupported state flag).
	 * - If we don't have the code for UMySubContent but do have the code for UMyCustomContent, we'll return an instance for it (with a PartiallySupported state flag).
	 * - If we don't have the code for UMySubContent nor for UMyCustomContent, we'll return an instance of UBeamContentObject for it (with a Unsupported state flag).
	 * This process guarantees that if you ever fetch content that you don't have the full source code to interpret it, you'll have the closest possible match.
	 * Use-cases for this are:
	 * - Content authored within Unity or Web interfaces that was pushed to the realm to be used by Microservices but Unreal does not yet support it.
	 * - A developer working on the primary 'dev' realm pushing content whose source only exists on his local machine will not break other developers experience.
	 *   They simply won't be able to access the properties on the new subclasses.
	 *   
	 * @param ContentTypeToContentClass This should always be a mapping, like ContentTypeStringToContentClass, that maps content type strings to their respective UClasses. 
	 * @param ContentTypeId The type id of a particular content object (this is the object's id without the last component).
	 * @param OutObject The UBeamContentObject instance that is correct.
	 */
	UFUNCTION(BlueprintCallable)
	static void NewFromTypeId(const TMap<FString, UClass*>& ContentTypeToContentClass, const FString& ContentTypeId, UBeamContentObject*& OutObject);

	/**
	 * See @link NewFromTypeId @endlink .
	 */
	UFUNCTION(BlueprintCallable)
	static void GetClassForTypeId(const TMap<FString, UClass*>& ContentTypeToContentClass, const FString& ContentTypeId, UClass*& OutObjectClass, TEnumAsByte<EBeamContentObjectSupportLevel>& OutSupportLevel);
};


#define DEFINE_CONTENT_TYPE_NAME(ClassName, TypeName) \
inline void ClassName::GetContentType_##ClassName(FString& Result){ Result = TEXT(TypeName); }
