// Fill out your copyright notice in the Description page of Project Settings.


#include "Content/BeamContentObject.h"

#include "BeamCoreSettings.h"
#include "Misc/DefaultValueHelper.h"
#include "BeamLogging.h"
#include "GameplayTagContainer.h"
#include "Content/LocalContentManifestRow.h"
#include "Serialization/BeamArray.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamMap.h"
#include "Serialization/BeamOptional.h"
#include "Serialization/BeamSemanticType.h"

FString UBeamContentObject::GetTypeClassNameFromTypeTag(const FString& TypeTag)
{
	FStringView ViewOverTypeTag(TypeTag);
	int DashIdx;
	ViewOverTypeTag.FindChar('-', DashIdx);
	ViewOverTypeTag.RightChopInline(DashIdx + 1);
	ViewOverTypeTag.FindChar('-', DashIdx);
	ViewOverTypeTag.RightChopInline(DashIdx + 1);
	return FString(ViewOverTypeTag);
}


void UBeamContentObject::BuildContentDefinitionJsonObject(FJsonDomBuilder::FObject& OutContentDefinition)
{
	OutContentDefinition.Set("id", Id);

	const auto Hash = CreatePropertiesHash();
	OutContentDefinition.Set("checksum", Hash);

	auto TagsArray = FJsonDomBuilder::FArray{};
	for (const auto& Tag : Tags) TagsArray.Add(Tag);
	OutContentDefinition.Set("tags", TagsArray);

	auto PropertiesJson = FJsonDomBuilder::FObject{};
	BuildPropertiesJsonObject(PropertiesJson);
	OutContentDefinition.Set("properties", PropertiesJson);
}

FString UBeamContentObject::CreatePropertiesHash()
{
	FJsonDomBuilder::FObject Json;
	BuildPropertiesJsonObject(Json);

	const FString PropertiesJson = Json.ToString<TCondensedJsonPrintPolicy>();

	// UTF-8 Byte Array of the String
	const FTCHARToUTF8 StringConversion(*PropertiesJson);
	const FSHAHash     Sha1Hash = FSHA1::HashBuffer(StringConversion.Get(), StringConversion.Length());
	
	FString Hash = Sha1Hash.ToString();

	// We are doing this for legacy reasons (in our Unity SDK, we do the same) 
	Hash.ReplaceInline(TEXT("-"), TEXT(""));
	Hash.ToLowerInline();

	return Hash;
}

struct FGetContentTypeParams
{
	FString Result;
};

FString UBeamContentObject::BuildContentTypeString()
{
	FString TypeId;
	auto CurrClass = GetClass();
	TArray<UClass*> ContentClassHierarchy;
	while (CurrClass != UBeamContentObject::StaticClass())
	{
		ContentClassHierarchy.Add(CurrClass);
		CurrClass = CurrClass->GetSuperClass();
	}

	for (int i = ContentClassHierarchy.Num() - 1; i >= 0; --i)
	{
		const auto Iter = ContentClassHierarchy[i];
		const auto FunctionName = FName(FString::Format(TEXT("GetContentType_U{0}"), {Iter->GetName()}));
		const auto Function = Iter->FindFunctionByName(FunctionName);
		if (!Function)
			TypeId.Append(Iter->GetName().ToLower());
		else
		{
			FGetContentTypeParams Result;
			ProcessEvent(Function, &Result);
			TypeId.Append(Result.Result);
		}

		// We don't append '.' for the hierarchy's leaf.
		if (i != 0)
			TypeId.Append(".");
	}

	return TypeId;
}

// Add default functionality here for any IBeamContentObject functions that are not pure virtual.
void UBeamContentObject::ToBasicJson_Implementation(FString& Serialized)
{
	FJsonDomBuilder::FObject ContentObjJson;
	BuildBasicJsonObject(ContentObjJson);
	Serialized = ContentObjJson.ToString<TCondensedJsonPrintPolicy>();
}

void UBeamContentObject::FromBasicJson_Implementation(const FString& Json)
{
	auto Bag = FJsonDataBag();
	Bag.FromJson(Json);
	ParseBasicJsonObject(Bag.JsonObject);
}


void UBeamContentObject::ToPropertiesJson(FString& Serialized)
{
	FJsonDomBuilder::FObject ContentObjJson;
	BuildPropertiesJsonObject(ContentObjJson);
	Serialized = ContentObjJson.ToString<TCondensedJsonPrintPolicy>();
}

void UBeamContentObject::FromPropertiesJson(const FString& Json)
{
	auto Bag = FJsonDataBag();
	Bag.FromJson(Json);
	ParsePropertiesJsonObject(Bag.JsonObject);
}

void UBeamContentObject::BuildBasicJsonObject(FJsonDomBuilder::FObject& Output)
{
	Output.Set(TEXT("id"), Id);
	Output.Set(TEXT("version"), Version);

	FJsonDomBuilder::FObject Properties;
	BuildPropertiesJsonObject(Properties);

	Output.Set(TEXT("properties"), Properties);
}

void UBeamContentObject::BuildPropertiesJsonObject(FJsonDomBuilder::FObject& Properties)
{
	const auto SelfClass = GetClass();	
	for (TFieldIterator<FProperty> It(SelfClass); It; ++It)
	{
		FJsonDomBuilder::FObject CurrProp;
		FString CurrPropName = It->GetName();


		auto ShouldAddToJson = true;
		if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(*It))
		{
			const auto Val = SoftObjectProperty->ContainerPtrToValuePtr<FSoftObjectPtr>(this);
			if(Val->IsNull())
				CurrProp.Set("data", nullptr);
			else
				CurrProp.Set("data", Val->ToSoftObjectPath().ToString());
		}
		else if (const auto StructProperty = CastField<FStructProperty>(*It))
		{
			const auto ScriptStruct = StructProperty->Struct;
			if (ScriptStruct && ScriptStruct->IsChildOf(FBeamOptional::StaticStruct()))
			{
				const FBeamOptional* Data = StructProperty->ContainerPtrToValuePtr<FBeamOptional>(this);
				ShouldAddToJson = Data->IsSet;

				FProperty* ValueProp = nullptr;
				for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
				{
					const auto Name = OptIt->NamePrivate;
					ValueProp = !Name.IsEqual(TEXT("IsSet")) ? *OptIt : ValueProp;
				}

				if (const auto InnerOptionalSoftObjectProperty = CastField<FSoftObjectProperty>(ValueProp))
				{					
					const auto Val = InnerOptionalSoftObjectProperty->ContainerPtrToValuePtr<FSoftObjectPtr>(Data);
					if(Val->IsNull()) CurrProp.Set("data", nullptr);
					else CurrProp.Set("data", Val->ToSoftObjectPath().ToString());
				}
				else if (const auto InnerOptionalStructProperty = CastField<FStructProperty>(ValueProp))
				{
					const auto InnerOptionalStruct = InnerOptionalStructProperty->Struct;

					if (InnerOptionalStruct->IsChildOf(FBeamMap::StaticStruct()))
					{
						const FBeamMap* BeamMap = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamMap>(Data);
						FJsonDomBuilder::FObject SubMap;
						const FMapProperty* InnerMapProperty = nullptr;
						for (TFieldIterator<FProperty> OptIt(InnerOptionalStruct); OptIt; ++OptIt)
						{
							InnerMapProperty = CastField<FMapProperty>(*OptIt);
							if (InnerMapProperty) break;
						}

						SerializeMapProperty(CurrPropName, SubMap, InnerMapProperty, BeamMap);
						CurrProp.Set("data", SubMap);
					}
					else if (InnerOptionalStruct->IsChildOf(FBeamArray::StaticStruct()))
					{
						const FBeamArray* BeamArray = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamArray>(Data);
						FJsonDomBuilder::FArray SubArray;
						const FArrayProperty* InnerArrayProperty = nullptr;
						for (TFieldIterator<FProperty> OptIt(InnerOptionalStruct); OptIt; ++OptIt)
						{
							InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
							if (InnerArrayProperty) break;
						}

						SerializeArrayProperty(CurrPropName, SubArray, InnerArrayProperty, BeamArray);
						CurrProp.Set("data", SubArray);
					}
					else if (InnerOptionalStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
					{
						const FBeamJsonSerializableUStruct* BeamJsonSerializable = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamJsonSerializableUStruct>(Data);
						FString JsonBody;
						TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&JsonBody);
						BeamJsonSerializable->BeamSerialize(Serializer);
						Serializer->Close();

						auto Bag = FJsonDataBag{};
						Bag.FromJson(JsonBody);

						FJsonDomBuilder::FObject JsonObject;
						JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

						UE_LOG(LogBeamContent, Display, TEXT("FBeamOptional wrapping type %s Field %s=%s is a \n"), *InnerOptionalStruct->GetName(), *It->GetName(), *JsonBody);
						CurrProp.Set("data", JsonObject);
					}
					else if (InnerOptionalStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
					{
						const FBeamSemanticType* BeamSemantic = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(Data);
						const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
						CurrProp.Set("data", *UnderlyingString);
					}
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
						       *It->GetName())
					}
				}
				else if (const auto InnerOptionalUObjectProperty = CastField<FObjectProperty>(ValueProp))
				{
					const auto InnerOptionalClass = InnerOptionalUObjectProperty->PropertyClass;

					if (InnerOptionalClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
					{
						if(const IBeamJsonSerializableUObject* BeamJsonSerializable = Cast<IBeamJsonSerializableUObject>(InnerOptionalUObjectProperty->GetObjectPropertyValue(InnerOptionalUObjectProperty->ContainerPtrToValuePtr<void>(Data))))
						{
							FString                      JsonBody;
							TUnrealJsonSerializer        Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&JsonBody);
							BeamJsonSerializable->BeamSerialize(Serializer);
							Serializer->Close();

							auto Bag = FJsonDataBag{};
							Bag.FromJson(JsonBody);

							FJsonDomBuilder::FObject JsonObject;
							JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

							UE_LOG(LogBeamContent, Display, TEXT("FBeamOptional wrapping type %s Field %s=%s is a \n"), *InnerOptionalClass->GetName(), *It->GetName(), *JsonBody);
							CurrProp.Set("data", JsonObject);
						}
						else
						{
							CurrProp.Set("data", nullptr);							
						}
					}
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement IBeamJsonSerializableUObject. It cannot be in a content object unless it does.\n"),
						       *It->GetName())
					}
				}
				else if (const auto MapProperty = CastField<FMapProperty>(ValueProp))
				{
					FJsonDomBuilder::FObject MapJson;
					SerializeMapProperty(CurrPropName, MapJson, MapProperty, Data);
					CurrProp.Set("data", MapJson);
				}
				else if (const auto ArrayProperty = CastField<FArrayProperty>(ValueProp))
				{
					FJsonDomBuilder::FArray ArrayJson;
					SerializeArrayProperty(CurrPropName, ArrayJson, ArrayProperty, Data);
					CurrProp.Set("data", ArrayJson);
				}
				else if (const auto ClassProperty = CastField<FClassProperty>(ValueProp))
				{
					const auto Val = ClassProperty->ContainerPtrToValuePtr<UClass>(Data);
					CurrProp.Set("data", FSoftClassPath(static_cast<UClass*>(ClassProperty->GetPropertyValue(Val))).ToString());
				}
				else if (const auto TextProperty = CastField<FTextProperty>(ValueProp))
				{
					const auto Val = TextProperty->ContainerPtrToValuePtr<FText>(Data);
					CurrProp.Set("data", TextProperty->GetPropertyValue(Val).ToString());
				}
				else if (const auto NameProperty = CastField<FNameProperty>(ValueProp))
				{
					const auto Val = NameProperty->ContainerPtrToValuePtr<FName>(Data);
					CurrProp.Set("data", NameProperty->GetPropertyValue(Val).ToString());
				}
				else if (const auto StrProperty = CastField<FStrProperty>(ValueProp))
				{
					const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(Data);
					CurrProp.Set("data", StrProperty->GetPropertyValue(Val));
				}
				else if (const auto BoolProperty = CastField<FBoolProperty>(ValueProp))
				{
					const auto Val = BoolProperty->ContainerPtrToValuePtr<bool>(Data);
					CurrProp.Set("data", BoolProperty->GetPropertyValue(Val));
				}
				else if (const auto FloatProperty = CastField<FFloatProperty>(ValueProp))
				{
					const auto Val = FloatProperty->ContainerPtrToValuePtr<float>(Data);
					CurrProp.Set("data", FloatProperty->GetFloatingPointPropertyValue(Val));
				}
				else if (const auto DoubleProperty = CastField<FDoubleProperty>(ValueProp))
				{
					const auto Val = DoubleProperty->ContainerPtrToValuePtr<double>(Data);
					CurrProp.Set("data", DoubleProperty->GetFloatingPointPropertyValue(Val));
				}
				else if (const auto Int32Property = CastField<FIntProperty>(ValueProp))
				{
					const auto Val = Int32Property->ContainerPtrToValuePtr<int32>(Data);
					CurrProp.Set("data", Int32Property->GetSignedIntPropertyValue(Val));
				}
				else if (const auto Int64Property = CastField<FInt64Property>(ValueProp))
				{
					const auto Val = Int64Property->ContainerPtrToValuePtr<int64>(Data);
					CurrProp.Set("data", Int64Property->GetSignedIntPropertyValue(Val));
				}
				else if (const auto ByteProperty = CastField<FByteProperty>(ValueProp))
				{
					const auto Val = ByteProperty->ContainerPtrToValuePtr<uint8>(Data);
					CurrProp.Set("data", ByteProperty->GetUnsignedIntPropertyValue(Val));
				}
				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Optional Field %s's underlying Type (%s) is not supported by the Content serialization system.\n"), *It->GetName(),
					       *ValueProp->GetCPPType())
				}
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamMap::StaticStruct()))
			{
				const FBeamMap* Data = StructProperty->ContainerPtrToValuePtr<FBeamMap>(this);

				FMapProperty* MapProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
				{
					MapProperty = CastField<FMapProperty>(*OptIt);
					if (MapProperty) break;
				}

				FJsonDomBuilder::FObject MapJson;
				SerializeMapProperty(CurrPropName, MapJson, MapProperty, Data);
				CurrProp.Set("data", MapJson);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamArray::StaticStruct()))
			{
				const FBeamArray* Data = StructProperty->ContainerPtrToValuePtr<FBeamArray>(this);

				FArrayProperty* ArrayProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
				{
					ArrayProperty = CastField<FArrayProperty>(*OptIt);
					if (ArrayProperty) break;
				}

				FJsonDomBuilder::FArray ArrayJson;
				SerializeArrayProperty(CurrPropName, ArrayJson, ArrayProperty, Data);
				CurrProp.Set("data", ArrayJson);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FGameplayTag::StaticStruct()))
			{
				const FGameplayTag* UnrealGameplayTag = StructProperty->ContainerPtrToValuePtr<FGameplayTag>(this);
				const FString UnderlyingString = UnrealGameplayTag->ToString();
				CurrProp.Set("data", UnderlyingString);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
			{
				const FGameplayTagContainer* UnrealGameplayTag = StructProperty->ContainerPtrToValuePtr<FGameplayTagContainer>(this);
				const FString UnderlyingString = UnrealGameplayTag->ToString();
				CurrProp.Set("data", UnderlyingString);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
			{
				const FBeamSemanticType* BeamSemantic = StructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(this);
				const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
				CurrProp.Set("data", *UnderlyingString);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
			{
				const FBeamJsonSerializableUStruct* BeamJsonSerializable = StructProperty->ContainerPtrToValuePtr<FBeamJsonSerializableUStruct>(this);

				FString JsonBody;
				TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&JsonBody);
				BeamJsonSerializable->BeamSerialize(Serializer);
				Serializer->Close();

				auto Bag = FJsonDataBag{};
				Bag.FromJson(JsonBody);

				FJsonDomBuilder::FObject JsonObject;
				JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

				CurrProp.Set("data", JsonObject);
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is not supported by the Content serialization system.\n"), *It->GetName())
			}
		}
		else if (const auto MapProperty = CastField<FMapProperty>(*It))
		{
			FJsonDomBuilder::FObject MapJson;
			SerializeMapProperty(CurrPropName, MapJson, MapProperty, this);
			CurrProp.Set("data", MapJson);
		}
		else if (const auto ArrayProperty = CastField<FArrayProperty>(*It))
		{
			FJsonDomBuilder::FArray ArrayJson;
			SerializeArrayProperty(CurrPropName, ArrayJson, ArrayProperty, this);
			CurrProp.Set("data", ArrayJson);
		}
		else if (const auto ClassProperty = CastField<FClassProperty>(*It))
		{
			const auto Val = ClassProperty->ContainerPtrToValuePtr<UClass>(this);
			CurrProp.Set("data", FSoftClassPath(static_cast<UClass*>(ClassProperty->GetPropertyValue(Val))).ToString());
		}
		else if (const auto TextProperty = CastField<FTextProperty>(*It))
		{
			const auto Val = TextProperty->ContainerPtrToValuePtr<FText>(this);
			CurrProp.Set("data", TextProperty->GetPropertyValue(Val).ToString());
		}
		else if (const auto NameProperty = CastField<FNameProperty>(*It))
		{
			const auto Val = NameProperty->ContainerPtrToValuePtr<FName>(this);
			CurrProp.Set("data", NameProperty->GetPropertyValue(Val).ToString());
		}
		else if (const auto StrProperty = CastField<FStrProperty>(*It))
		{
			const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(this);
			CurrProp.Set("data", StrProperty->GetPropertyValue(Val));
		}
		else if (const auto BoolProperty = CastField<FBoolProperty>(*It))
		{
			const auto Val = BoolProperty->ContainerPtrToValuePtr<bool>(this);
			CurrProp.Set("data", BoolProperty->GetPropertyValue(Val));
		}
		else if (const auto FloatProperty = CastField<FFloatProperty>(*It))
		{
			const auto Val = FloatProperty->ContainerPtrToValuePtr<float>(this);
			CurrProp.Set("data", FloatProperty->GetFloatingPointPropertyValue(Val));
		}
		else if (const auto DoubleProperty = CastField<FDoubleProperty>(*It))
		{
			const auto Val = DoubleProperty->ContainerPtrToValuePtr<double>(this);
			CurrProp.Set("data", DoubleProperty->GetFloatingPointPropertyValue(Val));
		}
		else if (const auto Int32Property = CastField<FIntProperty>(*It))
		{
			const auto Val = Int32Property->ContainerPtrToValuePtr<int32>(this);
			CurrProp.Set("data", Int32Property->GetSignedIntPropertyValue(Val));
		}
		else if (const auto Int64Property = CastField<FInt64Property>(*It))
		{
			const auto Val = Int64Property->ContainerPtrToValuePtr<int64>(this);
			CurrProp.Set("data", Int64Property->GetSignedIntPropertyValue(Val));
		}
		else if (const auto ByteProperty = CastField<FByteProperty>(*It))
		{
			const auto Val = ByteProperty->ContainerPtrToValuePtr<uint8>(this);
			CurrProp.Set("data", ByteProperty->GetUnsignedIntPropertyValue(Val));
		}
		else if (const auto UObjectProperty = CastField<FObjectProperty>(*It))
		{
			const auto InnerOptionalClass = UObjectProperty->PropertyClass;
			if (InnerOptionalClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
			{
				const IBeamJsonSerializableUObject* BeamJsonSerializable = Cast<IBeamJsonSerializableUObject>(UObjectProperty->GetObjectPropertyValue(UObjectProperty->ContainerPtrToValuePtr<void>(this)));
				FString                      JsonBody;
				TUnrealJsonSerializer        Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&JsonBody);
				BeamJsonSerializable->BeamSerialize(Serializer);
				Serializer->Close();

				auto Bag = FJsonDataBag{};
				Bag.FromJson(JsonBody);

				FJsonDomBuilder::FObject JsonObject;
				JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });				
				CurrProp.Set("data", JsonObject);
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement IBeamJsonSerializableUObject. It cannot be in a content object unless it does.\n"),
					   *It->GetName())
			}
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *It->GetName(), *ArrayProperty->Inner->GetName())
		}

		// If we should not even add the property to the serialized content object (mostly for optional fields)
		if (ShouldAddToJson)
			Properties.Set(It->GetName(), CurrProp);
	}
}


void UBeamContentObject::ParseBasicJsonObject(const TSharedPtr<FJsonObject>& Object)
{
	Id = Object->GetStringField("id");
	Version = Object->GetStringField("version");

	const auto Properties = Object->GetObjectField("properties");
	ParsePropertiesJsonObject(Properties);
}

void UBeamContentObject::ParsePropertiesJsonObject(const TSharedPtr<FJsonObject>& JsonProperties)
{
	const auto SelfClass = GetClass();
	for (TFieldIterator<FProperty> It(SelfClass); It; ++It)
	{
		const FString PropName = It->GetName();
		if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(*It))
		{
			const auto Val = SoftObjectProperty->ContainerPtrToValuePtr<FSoftObjectPtr>(this);
			auto JsonVal = JsonProperties->GetObjectField(PropName)->GetStringField("data");
			if(JsonVal.IsEmpty() || JsonVal.Equals("null")) JsonVal = TEXT("None");
			SoftObjectProperty->SetPropertyValue(Val, FSoftObjectPtr(FSoftObjectPath(JsonVal)));
		}
		else if (const auto StructProperty = CastField<FStructProperty>(*It))
		{
			const auto ScriptStruct = StructProperty->Struct;
			if (ScriptStruct && ScriptStruct->IsChildOf(FBeamOptional::StaticStruct()))
			{
				const auto ExistsInJson = JsonProperties->HasField(PropName);
				if (!ExistsInJson)
				{
					StructProperty->InitializeValueInternal(StructProperty->ContainerPtrToValuePtr<void>(this));
					continue;
				}

				FProperty* OptionalValueProp = nullptr;
				for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
				{
					const auto Name = OptIt->NamePrivate;
					OptionalValueProp = !Name.IsEqual(TEXT("IsSet")) ? *OptIt : OptionalValueProp;
				}


				FBeamOptional* OptionalVal = StructProperty->ContainerPtrToValuePtr<FBeamOptional>(this);

				if (const auto InnerOptionalSoftObject = CastField<FSoftObjectProperty>(OptionalValueProp))
				{
					const auto Val = InnerOptionalSoftObject->ContainerPtrToValuePtr<FSoftObjectPtr>(OptionalVal);
					InnerOptionalSoftObject->SetPropertyValue(Val, FSoftObjectPtr(FSoftObjectPath(JsonProperties->GetObjectField(PropName)->GetStringField("data"))));
				}
				else if (const auto InnerOptionalStructProperty = CastField<FStructProperty>(OptionalValueProp))
				{
					const auto InnerOptionalStruct = InnerOptionalStructProperty->Struct;

					if (InnerOptionalStruct->IsChildOf(FBeamMap::StaticStruct()))
					{
						const auto BeamMapJson = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
						FBeamMap* BeamMap = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamMap>(OptionalVal);
						const FMapProperty* InnerMapProperty = nullptr;
						for (TFieldIterator<FProperty> OptIt(InnerOptionalStruct); OptIt; ++OptIt)
						{
							InnerMapProperty = CastField<FMapProperty>(*OptIt);
							if (InnerMapProperty) break;
						}
						ParseMapProperty(PropName, BeamMapJson, InnerMapProperty, BeamMap);
						OptionalVal->Set(BeamMap);
					}
					else if (InnerOptionalStruct->IsChildOf(FBeamArray::StaticStruct()))
					{
						const auto BeamArrayJson = JsonProperties->GetObjectField(PropName)->GetArrayField("data");
						FBeamArray* BeamArray = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamArray>(OptionalVal);
						const FArrayProperty* InnerArrayProperty = nullptr;
						for (TFieldIterator<FProperty> OptIt(InnerOptionalStruct); OptIt; ++OptIt)
						{
							InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
							if (InnerArrayProperty) break;
						}
						ParseArrayProperty(PropName, BeamArrayJson, InnerArrayProperty, BeamArray);
						OptionalVal->Set(BeamArray);
					}
					else if (InnerOptionalStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
					{
						const auto SubJsonSemantic = JsonProperties->GetObjectField(PropName)->GetStringField("data");
						FBeamSemanticType* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(OptionalVal);
						ValData->Set(&SubJsonSemantic, ValData->GetSerializationRepresentationName(0));
						OptionalVal->Set(ValData);
					}
					else if (InnerOptionalStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
					{
						const auto SubJsonSerializable = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
						FBeamJsonSerializableUStruct* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamJsonSerializableUStruct>(OptionalVal);
						ValData->BeamDeserializeProperties(SubJsonSerializable);
						OptionalVal->Set(ValData);
					}
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
						       *It->GetName())
					}
				}
				else if (const auto InnerOptionalUObjectProperty = CastField<FObjectProperty>(OptionalValueProp))
				{
					const auto InnerOptionalClass = InnerOptionalUObjectProperty->PropertyClass;

					if (InnerOptionalClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
					{
						const auto SubJsonSerializable = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
						const auto Val = InnerOptionalUObjectProperty->ContainerPtrToValuePtr<UObject*>(OptionalVal);
						*Val = NewObject<UObject>(this, InnerOptionalClass);
						IBeamJsonSerializableUObject* ValData = Cast<IBeamJsonSerializableUObject>(*Val);						
						ValData->BeamDeserializeProperties(SubJsonSerializable);
						OptionalVal->Set(Val);
					}
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
							   *It->GetName())
					}
				}
				else if (const auto MapProperty = CastField<FMapProperty>(OptionalValueProp))
				{
					const auto MapJson = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
					ParseMapProperty(PropName, MapJson, MapProperty, OptionalVal);
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto ArrayProperty = CastField<FArrayProperty>(OptionalValueProp))
				{
					const auto MapJson = JsonProperties->GetObjectField(PropName)->GetArrayField("data");
					ParseArrayProperty(PropName, MapJson, ArrayProperty, OptionalVal);
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto ClassProperty = CastField<FClassProperty>(OptionalValueProp))
				{
					const auto StrVal = JsonProperties->GetObjectField(PropName)->GetStringField("data");
					const auto Val = ClassProperty->ContainerPtrToValuePtr<UClass>(OptionalVal);
					ClassProperty->SetPropertyValue(Val, FSoftClassPath{StrVal}.ResolveClass());
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto TextProperty = CastField<FTextProperty>(OptionalValueProp))
				{
					const auto Val = TextProperty->ContainerPtrToValuePtr<FText>(OptionalVal);
					const auto StrVal = JsonProperties->GetObjectField(PropName)->GetStringField("data");
					TextProperty->SetPropertyValue(Val, FText::FromString(StrVal));
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto NameProperty = CastField<FNameProperty>(OptionalValueProp))
				{
					const auto Val = NameProperty->ContainerPtrToValuePtr<FName>(OptionalVal);
					NameProperty->SetPropertyValue(Val, FName(JsonProperties->GetObjectField(PropName)->GetStringField("data")));
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto StrProperty = CastField<FStrProperty>(OptionalValueProp))
				{
					const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(OptionalVal);
					StrProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetStringField("data"));
					OptionalVal->Set(OptionalVal->GetAddr());
				}				
				else if (const auto BoolProperty = CastField<FBoolProperty>(OptionalValueProp))
				{
					const auto Val = BoolProperty->ContainerPtrToValuePtr<bool>(OptionalVal);
					BoolProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetBoolField("data"));
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto FloatProperty = CastField<FFloatProperty>(OptionalValueProp))
				{
					const auto Val = FloatProperty->ContainerPtrToValuePtr<float>(OptionalVal);
					FloatProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetNumberField("data"));
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto DoubleProperty = CastField<FDoubleProperty>(OptionalValueProp))
				{
					const auto Val = DoubleProperty->ContainerPtrToValuePtr<double>(OptionalVal);
					DoubleProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetNumberField("data"));
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto Int32Property = CastField<FIntProperty>(OptionalValueProp))
				{
					const auto Val = Int32Property->ContainerPtrToValuePtr<int32>(OptionalVal);
					Int32Property->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetIntegerField("data"));
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto Int64Property = CastField<FInt64Property>(OptionalValueProp))
				{
					const auto Val = Int64Property->ContainerPtrToValuePtr<int64>(OptionalVal);
					Int64Property->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetIntegerField("data"));
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else if (const auto ByteProperty = CastField<FByteProperty>(OptionalValueProp))
				{
					const auto Val = ByteProperty->ContainerPtrToValuePtr<uint8>(OptionalVal);
					ByteProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetIntegerField("data"));
					OptionalVal->Set(OptionalVal->GetAddr());
				}
				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Optional Field %s's underlying Type (%s) is not supported by the Content serialization system.\n"), *It->GetName(),
					       *OptionalValueProp->GetCPPType())
				}
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamMap::StaticStruct()))
			{
				const auto BeamMapJson = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
				FBeamMap* BeamMap = StructProperty->ContainerPtrToValuePtr<FBeamMap>(this);
				const FMapProperty* InnerMapProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
				{
					InnerMapProperty = CastField<FMapProperty>(*OptIt);
					if (InnerMapProperty) break;
				}
				ParseMapProperty(PropName, BeamMapJson, InnerMapProperty, BeamMap);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamArray::StaticStruct()))
			{
				const auto BeamArrayJson = JsonProperties->GetObjectField(PropName)->GetArrayField("data");
				FBeamArray* BeamArray = StructProperty->ContainerPtrToValuePtr<FBeamArray>(this);
				const FArrayProperty* InnerArrayProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
				{
					InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
					if (InnerArrayProperty) break;
				}
				ParseArrayProperty(PropName, BeamArrayJson, InnerArrayProperty, BeamArray);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FGameplayTag::StaticStruct()))
			{
				const auto SubJsonSemantic = JsonProperties->GetObjectField(PropName)->GetStringField("data");
				FGameplayTag* ValData = StructProperty->ContainerPtrToValuePtr<FGameplayTag>(this);
				const auto bShouldError = GetDefault<UBeamCoreSettings>()->bErrorIfGameplayTagNotFound;
				*ValData = FGameplayTag::RequestGameplayTag(FName(SubJsonSemantic), !SubJsonSemantic.Equals(TEXT("None")) && bShouldError);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
			{
				const auto SubJsonSemantic = JsonProperties->GetObjectField(PropName)->GetStringField("data");
				FGameplayTagContainer* ValData = StructProperty->ContainerPtrToValuePtr<FGameplayTagContainer>(this);
				ValData->FromExportString(SubJsonSemantic);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
			{
				const auto SubJsonSemantic = JsonProperties->GetObjectField(PropName)->GetStringField("data");
				FBeamSemanticType* ValData = StructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(this);
				ValData->Set(&SubJsonSemantic, ValData->GetSerializationRepresentationName(0));
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
			{
				const auto SubJsonSerializable = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
				FBeamJsonSerializableUStruct* ValData = StructProperty->ContainerPtrToValuePtr<FBeamJsonSerializableUStruct>(this);
				ValData->BeamDeserializeProperties(SubJsonSerializable);
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is not supported by the Content serialization system.\n"), *It->GetName())
			}
		}
		else if (const auto MapProperty = CastField<FMapProperty>(*It))
		{
			const auto Map = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
			ParseMapProperty(PropName, Map, MapProperty, this);
		}
		else if (const auto ArrayProperty = CastField<FArrayProperty>(*It))
		{
			const auto Array = JsonProperties->GetObjectField(PropName)->GetArrayField("data");
			ParseArrayProperty(PropName, Array, ArrayProperty, this);
		}
		else if (const auto ClassProperty = CastField<FClassProperty>(*It))
		{
			const auto Val = ClassProperty->ContainerPtrToValuePtr<UClass>(this);
			const auto StrVal = JsonProperties->GetObjectField(PropName)->GetStringField("data");
			ClassProperty->SetPropertyValue(Val, FSoftClassPath{StrVal}.ResolveClass());
		}
		else if (const auto TextProperty = CastField<FTextProperty>(*It))
		{
			const auto Val = TextProperty->ContainerPtrToValuePtr<FText>(this);
			TextProperty->SetPropertyValue(Val, FText::FromString(JsonProperties->GetObjectField(PropName)->GetStringField("data")));
		}
		else if (const auto NameProperty = CastField<FNameProperty>(*It))
		{
			const auto Val = NameProperty->ContainerPtrToValuePtr<FName>(this);
			NameProperty->SetPropertyValue(Val, FName(JsonProperties->GetObjectField(PropName)->GetStringField("data")));
		}
		else if (const auto StrProperty = CastField<FStrProperty>(*It))
		{
			const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(this);
			StrProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetStringField("data"));
		}		
		else if (const auto BoolProperty = CastField<FBoolProperty>(*It))
		{
			const auto Val = BoolProperty->ContainerPtrToValuePtr<bool>(this);
			BoolProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetBoolField("data"));
		}
		else if (const auto FloatProperty = CastField<FFloatProperty>(*It))
		{
			const auto Val = FloatProperty->ContainerPtrToValuePtr<float>(this);
			FloatProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetNumberField("data"));
		}
		else if (const auto DoubleProperty = CastField<FDoubleProperty>(*It))
		{
			const auto Val = DoubleProperty->ContainerPtrToValuePtr<double>(this);
			DoubleProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetNumberField("data"));
		}
		else if (const auto Int32Property = CastField<FIntProperty>(*It))
		{
			const auto Val = Int32Property->ContainerPtrToValuePtr<int32>(this);
			Int32Property->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetIntegerField("data"));
		}
		else if (const auto Int64Property = CastField<FInt64Property>(*It))
		{
			const auto Val = Int64Property->ContainerPtrToValuePtr<int64>(this);
			Int64Property->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetIntegerField("data"));
		}
		else if (const auto ByteProperty = CastField<FByteProperty>(*It))
		{
			const auto Val = ByteProperty->ContainerPtrToValuePtr<uint8>(this);
			ByteProperty->SetPropertyValue(Val, JsonProperties->GetObjectField(PropName)->GetIntegerField("data"));
		}
		else if (const auto UObjectProperty = CastField<FObjectProperty>(*It))
		{
			const auto InnerOptionalClass = UObjectProperty->PropertyClass;
			if (InnerOptionalClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
			{
				const auto JsonObject = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
				UObject* Val = NewObject<UObject>(this, InnerOptionalClass);
				IBeamJsonSerializableUObject* ValData = Cast<IBeamJsonSerializableUObject>(Val);
				ValData->BeamDeserializeProperties(JsonObject);
				UObjectProperty->SetObjectPropertyValue(UObjectProperty->ContainerPtrToValuePtr<void>(this), Val);
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
					   *It->GetName())
			}
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *It->GetName(), *It->GetCPPType())
		}
	}
}


void UBeamContentObject::SerializeArrayProperty(FString PropName, FJsonDomBuilder::FArray& JsonArray,
                                                const FArrayProperty* const ArrayProperty, const void* ArrayOwner)
{
	if (CastField<FSoftObjectProperty>(ArrayProperty->Inner))
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
		FScriptArrayHelper ArrayHelper(ArrayProperty, Val);

		const auto ArrayNum = ArrayHelper.Num();
		for (auto i = 0; i < ArrayNum; i++)
		{
			if (ArrayHelper.IsValidIndex(i))
			{
				const FSoftObjectPtr* Data = reinterpret_cast<const FSoftObjectPtr*>(ArrayHelper.GetRawPtr(i));
				JsonArray.Add(Data->ToSoftObjectPath().ToString());
			}
		}
	}
	else if (const auto InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
	{
		const auto InnerArrayStruct = InnerStructProperty->Struct;

		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
		FScriptArrayHelper ArrayHelper(ArrayProperty, Val);

		if (InnerArrayStruct->IsChildOf(FBeamMap::StaticStruct()))
		{
			const FMapProperty* InnerMapProperty = nullptr;
			for (TFieldIterator<FProperty> OptIt(InnerArrayStruct); OptIt; ++OptIt)
			{
				InnerMapProperty = CastField<FMapProperty>(*OptIt);
				if (InnerMapProperty) break;
			}

			const auto ArrayNum = ArrayHelper.Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				if (ArrayHelper.IsValidIndex(i))
				{
					const FBeamMap* Data = reinterpret_cast<const FBeamMap*>(ArrayHelper.GetRawPtr(i));

					FJsonDomBuilder::FObject SubMap;
					SerializeMapProperty(PropName, SubMap, InnerMapProperty, Data);
					JsonArray.Add(SubMap);
				}
			}
		}
		else if (InnerArrayStruct->IsChildOf(FBeamArray::StaticStruct()))
		{
			const FArrayProperty* InnerArrayProperty = nullptr;
			for (TFieldIterator<FProperty> OptIt(InnerArrayStruct); OptIt; ++OptIt)
			{
				InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
				if (InnerArrayProperty) break;
			}

			const auto ArrayNum = ArrayHelper.Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				if (ArrayHelper.IsValidIndex(i))
				{
					const FBeamArray* Data = reinterpret_cast<const FBeamArray*>(ArrayHelper.GetRawPtr(i));

					FJsonDomBuilder::FArray SubArray;
					SerializeArrayProperty(PropName, SubArray, InnerArrayProperty, Data);
					JsonArray.Add(SubArray);
				}
			}
		}
		else if (InnerArrayStruct->IsChildOf(FGameplayTag::StaticStruct()))
		{
			const auto ArrayNum = ArrayHelper.Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				if (ArrayHelper.IsValidIndex(i))
				{
					const FGameplayTag* Data = reinterpret_cast<const FGameplayTag*>(ArrayHelper.GetRawPtr(i));
					const FString UnderlyingString = Data->ToString();
					JsonArray.Add(UnderlyingString);
				}
			}
		}
		else if (InnerArrayStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
		{
			const auto ArrayNum = ArrayHelper.Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				if (ArrayHelper.IsValidIndex(i))
				{
					const FGameplayTagContainer* Data = reinterpret_cast<const FGameplayTagContainer*>(ArrayHelper.GetRawPtr(i));
					const FString UnderlyingString = Data->ToString();
					JsonArray.Add(UnderlyingString);
				}
			}
		}
		else if (InnerArrayStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
		{
			const auto ArrayNum = ArrayHelper.Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				if (ArrayHelper.IsValidIndex(i))
				{
					const FBeamSemanticType* Data = reinterpret_cast<const FBeamSemanticType*>(ArrayHelper.GetRawPtr(i));
					const FString* UnderlyingString = static_cast<const FString*>(Data->GetAddr(0));
					JsonArray.Add(*UnderlyingString);
				}
			}
		}
		else if (InnerArrayStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
		{
			const auto ArrayNum = ArrayHelper.Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				if (ArrayHelper.IsValidIndex(i))
				{
					const FBeamJsonSerializableUStruct* Data = reinterpret_cast<const FBeamJsonSerializableUStruct*>(ArrayHelper.GetRawPtr(i));

					FString JsonBody;
					TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&JsonBody);
					Data->BeamSerialize(Serializer);
					Serializer->Close();

					auto Bag = FJsonDataBag{};
					Bag.FromJson(JsonBody);

					FJsonDomBuilder::FObject JsonObject;
					JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

					JsonArray.Add(JsonObject);
				}
			}
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
		}
	}
	else if (CastField<FClassProperty>(ArrayProperty->Inner))
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
		const auto ArrayNum = Val->Num();
		for (auto i = 0; i < ArrayNum; i++)
		{
			UClass** Data = (UClass**)(Val->GetData());
			JsonArray.Add(FSoftClassPath{*(Data + i)}.ToString());
		}
	}
	else if (CastField<FTextProperty>(ArrayProperty->Inner))
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
		const auto ArrayNum = Val->Num();
		for (auto i = 0; i < ArrayNum; i++)
		{
			const FText* Data = static_cast<const FText*>(Val->GetData());
			const FString DataStr = (Data + i)->ToString();
			JsonArray.Add(DataStr);
		}
	}
	else if (CastField<FNameProperty>(ArrayProperty->Inner))
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
		const auto ArrayNum = Val->Num();
		for (auto i = 0; i < ArrayNum; i++)
		{
			const FName* Data = static_cast<const FName*>(Val->GetData());
			const FString DataStr = (Data + i)->ToString();
			JsonArray.Add(DataStr);
		}
	}
	else if (CastField<FStrProperty>(ArrayProperty->Inner))
	{
		BuildArray<FString>(JsonArray, ArrayProperty, ArrayOwner);
	}
	else if (CastField<FBoolProperty>(ArrayProperty->Inner))
	{
		BuildArray<bool>(JsonArray, ArrayProperty, ArrayOwner);
	}
	else if (CastField<FFloatProperty>(ArrayProperty->Inner))
	{
		BuildArray<float>(JsonArray, ArrayProperty, ArrayOwner);
	}
	else if (CastField<FDoubleProperty>(ArrayProperty->Inner))
	{
		BuildArray<double>(JsonArray, ArrayProperty, ArrayOwner);
	}
	else if (CastField<FIntProperty>(ArrayProperty->Inner))
	{
		BuildArray<int32>(JsonArray, ArrayProperty, ArrayOwner);
	}
	else if (CastField<FInt64Property>(ArrayProperty->Inner))
	{
		BuildArray<int64>(JsonArray, ArrayProperty, ArrayOwner);
	}
	else if (CastField<FByteProperty>(ArrayProperty->Inner))
	{
		BuildArray<uint8>(JsonArray, ArrayProperty, ArrayOwner);
	}
	else
	{
		UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *PropName, *ArrayProperty->Inner->GetName())
	}
}

void UBeamContentObject::ParseArrayProperty(const FString& PropName, const TArray<TSharedPtr<FJsonValue>>& JsonArray, const FArrayProperty* ArrayProperty, const void* ArrayOwner)
{
	const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));

	// Make a helper and resize the array to the proper size.
	FScriptArrayHelper ArrayHelper(ArrayProperty, Val);
	ArrayHelper.Resize(JsonArray.Num());

	if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<FSoftObjectPtr*>(ArrayHelper.GetRawPtr(i));
			*ValData = FSoftObjectPath(JsonArray[i]->AsString());
		}
	}
	else if (const auto InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
	{
		const auto InnerArrayStruct = InnerStructProperty->Struct;
		if (InnerArrayStruct->IsChildOf(FBeamMap::StaticStruct()))
		{
			const FMapProperty* InnerMapProperty = nullptr;
			for (TFieldIterator<FProperty> OptIt(InnerArrayStruct); OptIt; ++OptIt)
			{
				InnerMapProperty = CastField<FMapProperty>(*OptIt);
				if (InnerMapProperty) break;
			}

			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto SubMap = JsonArray[i]->AsObject();
				ParseMapProperty(PropName, SubMap, InnerMapProperty, ArrayHelper.GetRawPtr(i));
			}
		}
		else if (InnerArrayStruct->IsChildOf(FBeamArray::StaticStruct()))
		{
			const FArrayProperty* InnerArrayProperty = nullptr;
			for (TFieldIterator<FProperty> OptIt(InnerArrayStruct); OptIt; ++OptIt)
			{
				InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
				if (InnerArrayProperty) break;
			}

			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto SubArray = JsonArray[i]->AsArray();
				ParseArrayProperty(PropName, SubArray, InnerArrayProperty, ArrayHelper.GetRawPtr(i));
			}
		}
		else if (InnerArrayStruct->IsChildOf(FGameplayTag::StaticStruct()))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				FGameplayTag* ValData = reinterpret_cast<FGameplayTag*>(ArrayHelper.GetRawPtr(i));
				const FString JsonStr = JsonArray[i]->AsString();
				const auto bShouldError = GetDefault<UBeamCoreSettings>()->bErrorIfGameplayTagNotFound;
				*ValData = FGameplayTag::RequestGameplayTag(FName(JsonStr), !JsonStr.Equals(TEXT("None")) && bShouldError);
			}
		}
		else if (InnerArrayStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				FGameplayTagContainer* ValData = reinterpret_cast<FGameplayTagContainer*>(ArrayHelper.GetRawPtr(i));
				const FString JsonStr = JsonArray[i]->AsString();
				ValData->FromExportString(JsonStr);
			}
		}
		else if (InnerArrayStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				FBeamSemanticType* ValData = reinterpret_cast<FBeamSemanticType*>(ArrayHelper.GetRawPtr(i));
				const FString JsonStr = JsonArray[i]->AsString();
				ValData->Set(&JsonStr, ValData->GetSerializationRepresentationName(0));
			}
		}
		else if (InnerArrayStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				FBeamJsonSerializableUStruct* ValData = reinterpret_cast<FBeamJsonSerializableUStruct*>(ArrayHelper.GetRawPtr(i));
				ValData->BeamDeserializeProperties(JsonArray[i]->AsObject());
			}
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
		}
	}
	else if (CastField<FClassProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<UClass**>(ArrayHelper.GetRawPtr(i));
			*ValData = FSoftClassPath{JsonArray[i]->AsString()}.ResolveClass();
		}
	}
	else if (CastField<FTextProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<FText*>(ArrayHelper.GetRawPtr(i));
			*ValData = FText::FromString(JsonArray[i]->AsString());
		}
	}
	else if (CastField<FNameProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<FName*>(ArrayHelper.GetRawPtr(i));
			*ValData = FName(JsonArray[i]->AsString());
		}
	}
	else if (CastField<FStrProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<FString*>(ArrayHelper.GetRawPtr(i));
			*ValData = JsonArray[i]->AsString();
		}
	}
	else if (CastField<FBoolProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<bool*>(ArrayHelper.GetRawPtr(i));
			*ValData = JsonArray[i]->AsString().Equals(TEXT("true"), ESearchCase::IgnoreCase);
		}
	}
	else if (CastField<FFloatProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<float*>(ArrayHelper.GetRawPtr(i));
			FDefaultValueHelper::ParseFloat(JsonArray[i]->AsString(), *ValData);
		}
	}
	else if (CastField<FDoubleProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<double*>(ArrayHelper.GetRawPtr(i));
			FDefaultValueHelper::ParseDouble(JsonArray[i]->AsString(), *ValData);
		}
	}
	else if (CastField<FIntProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<int32*>(ArrayHelper.GetRawPtr(i));
			FDefaultValueHelper::ParseInt(JsonArray[i]->AsString(), *ValData);
		}
	}
	else if (CastField<FInt64Property>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<int64*>(ArrayHelper.GetRawPtr(i));
			FDefaultValueHelper::ParseInt64(JsonArray[i]->AsString(), *ValData);
		}
	}
	else if (CastField<FByteProperty>(ArrayProperty->Inner))
	{
		for (int i = 0; i < JsonArray.Num(); ++i)
		{
			const auto ValData = reinterpret_cast<uint8*>(ArrayHelper.GetRawPtr(i));
			int32 Parsed;
			FDefaultValueHelper::ParseInt(JsonArray[i]->AsString(), Parsed);
			*ValData = static_cast<int8>(Parsed);
		}
	}
	else
	{
		UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *PropName, *ArrayProperty->Inner->GetName())
	}
}


void UBeamContentObject::SerializeMapProperty(FString PropName, FJsonDomBuilder::FObject& JsonMap, const FMapProperty* const MapProperty, const void* MapOwner)
{
	if (const auto StrKeyProperty = CastField<FStrProperty>(MapProperty->KeyProp))
	{
		const FScriptMap* Val = MapProperty->GetPropertyValuePtr(MapProperty->ContainerPtrToValuePtr<void>(MapOwner));
		FScriptMapHelper MapHelper(MapProperty, Val);

		if (CastField<FSoftObjectProperty>(MapProperty->ValueProp))
		{
			const auto MapNum = MapHelper.Num();
			for (auto i = 0; i < MapNum; i++)
			{
				if (MapHelper.IsValidIndex(i))
				{
					const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
					const FSoftObjectPtr* SoftObjectPtr = reinterpret_cast<const FSoftObjectPtr*>(MapHelper.GetValuePtr(i));
					JsonMap.Set(Key, SoftObjectPtr->ToSoftObjectPath().ToString());
				}
			}
		}
		else if (const auto InnerStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
		{
			const auto InnerMapStruct = InnerStructProperty->Struct;
			if (InnerMapStruct->IsChildOf(FBeamMap::StaticStruct()))
			{
				const FMapProperty* InnerMapProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(InnerMapStruct); OptIt; ++OptIt)
				{
					InnerMapProperty = CastField<FMapProperty>(*OptIt);
					if (InnerMapProperty) break;
				}

				const auto MapNum = MapHelper.Num();
				for (auto i = 0; i < MapNum; i++)
				{
					if (MapHelper.IsValidIndex(i))
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamMap* Data = reinterpret_cast<const FBeamMap*>(MapHelper.GetValuePtr(i));

						FJsonDomBuilder::FObject SubMap;
						SerializeMapProperty(PropName, SubMap, InnerMapProperty, Data);
						JsonMap.Set(Key, SubMap);
					}
				}
			}
			else if (InnerMapStruct->IsChildOf(FBeamArray::StaticStruct()))
			{
				const FArrayProperty* InnerArrayProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(InnerMapStruct); OptIt; ++OptIt)
				{
					InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
					if (InnerArrayProperty) break;
				}

				const auto MapNum = MapHelper.Num();
				for (auto i = 0; i < MapNum; i++)
				{
					if (MapHelper.IsValidIndex(i))
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamArray* Data = reinterpret_cast<const FBeamArray*>(MapHelper.GetValuePtr(i));

						FJsonDomBuilder::FArray SubArray;

						SerializeArrayProperty(PropName, SubArray, InnerArrayProperty, Data);
						JsonMap.Set(Key, SubArray);
					}
				}
			}
			else if (InnerMapStruct->IsChildOf(FGameplayTag::StaticStruct()))
			{
				const auto MapNum = MapHelper.Num();
				for (auto i = 0; i < MapNum; i++)
				{
					if (MapHelper.IsValidIndex(i))
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FGameplayTag* UnrealGameplayTag = reinterpret_cast<const FGameplayTag*>(MapHelper.GetValuePtr(i));
						const FString UnderlyingString = UnrealGameplayTag->ToString();
						JsonMap.Set(Key, UnderlyingString);
					}
				}
			}
			else if (InnerMapStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
			{
				const auto MapNum = MapHelper.Num();
				for (auto i = 0; i < MapNum; i++)
				{
					if (MapHelper.IsValidIndex(i))
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FGameplayTagContainer* UnrealGameplayTag = reinterpret_cast<const FGameplayTagContainer*>(MapHelper.GetValuePtr(i));
						const FString UnderlyingString = UnrealGameplayTag->ToString();
						JsonMap.Set(Key, UnderlyingString);
					}
				}
			}
			else if (InnerMapStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
			{
				const auto MapNum = MapHelper.Num();
				for (auto i = 0; i < MapNum; i++)
				{
					if (MapHelper.IsValidIndex(i))
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamSemanticType* BeamSemantic = reinterpret_cast<const FBeamSemanticType*>(MapHelper.GetValuePtr(i));
						const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
						JsonMap.Set(Key, *UnderlyingString);
					}
				}
			}
			else if (InnerMapStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
			{
				const auto MapNum = MapHelper.Num();
				for (auto i = 0; i < MapNum; i++)
				{
					if (MapHelper.IsValidIndex(i))
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamJsonSerializableUStruct* Data = reinterpret_cast<const FBeamJsonSerializableUStruct*>(MapHelper.GetValuePtr(i));

						FString JsonObject;
						TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&JsonObject);
						Data->BeamSerialize(Serializer);
						Serializer->Close();

						JsonMap.Set(Key, JsonObject);
						UE_LOG(LogBeamContent, Display, TEXT("TArray<%s> Field %s[%d]=%s is a \n"), *InnerMapStruct->GetName(), *PropName, i, *JsonObject);
					}
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
			}
		}
		else if (CastField<FClassProperty>(MapProperty->ValueProp))
		{
			const auto MapNum = MapHelper.Num();
			for (auto i = 0; i < MapNum; i++)
			{
				if (MapHelper.IsValidIndex(i))
				{
					const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
					const UClass** Data = reinterpret_cast<const UClass**>(MapHelper.GetValuePtr(i));

					JsonMap.Set(Key, FSoftClassPath(*Data).ToString());
				}
			}
		}
		else if (CastField<FTextProperty>(MapProperty->ValueProp))
		{
			const auto MapNum = MapHelper.Num();
			for (auto i = 0; i < MapNum; i++)
			{
				if (MapHelper.IsValidIndex(i))
				{
					const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
					const FText* Data = reinterpret_cast<const FText*>(MapHelper.GetValuePtr(i));

					JsonMap.Set(Key, (*Data).ToString());
				}
			}
		}
		else if (CastField<FNameProperty>(MapProperty->ValueProp))
		{
			const auto MapNum = MapHelper.Num();
			for (auto i = 0; i < MapNum; i++)
			{
				if (MapHelper.IsValidIndex(i))
				{
					const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
					const FName* Data = reinterpret_cast<const FName*>(MapHelper.GetValuePtr(i));

					JsonMap.Set(Key, (*Data).ToString());
				}
			}
		}
		else if (CastField<FStrProperty>(MapProperty->ValueProp))
		{
			BuildMap<FString>(StrKeyProperty, JsonMap, MapHelper);
		}
		else if (CastField<FBoolProperty>(MapProperty->ValueProp))
		{
			BuildMap<bool>(StrKeyProperty, JsonMap, MapHelper);
		}
		else if (CastField<FFloatProperty>(MapProperty->ValueProp))
		{
			BuildMap<float>(StrKeyProperty, JsonMap, MapHelper);
		}
		else if (CastField<FDoubleProperty>(MapProperty->ValueProp))
		{
			BuildMap<double>(StrKeyProperty, JsonMap, MapHelper);
		}
		else if (CastField<FIntProperty>(MapProperty->ValueProp))
		{
			BuildMap<int32>(StrKeyProperty, JsonMap, MapHelper);
		}
		else if (CastField<FInt64Property>(MapProperty->ValueProp))
		{
			BuildMap<int64>(StrKeyProperty, JsonMap, MapHelper);
		}
		else if (CastField<FByteProperty>(MapProperty->ValueProp))
		{
			BuildMap<uint8>(StrKeyProperty, JsonMap, MapHelper);
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *PropName, *MapProperty->ValueProp->GetName())
		}
	}
	else
	{
		UE_LOG(LogBeamContent, Error, TEXT("Content Serialization does not support maps with non-FString keys.\n"))
	}
}

void UBeamContentObject::ParseMapProperty(const FString& PropName, const TSharedPtr<FJsonObject>& JsonMap, const FMapProperty* MapProperty, void* MapOwner)
{
	if (const auto StrKeyProperty = CastField<FStrProperty>(MapProperty->KeyProp))
	{
		const FScriptMap* Val = MapProperty->GetPropertyValuePtr(MapProperty->ContainerPtrToValuePtr<void>(MapOwner));
		FScriptMapHelper MapHelper(MapProperty, Val);

		if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto Key = Value.Key;

				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();
				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Key;

				FSoftObjectPtr* ValData = reinterpret_cast<FSoftObjectPtr*>(MapHelper.GetValuePtr(LastEntryIdx));
				*ValData = FSoftObjectPtr(FSoftObjectPath(Value.Value->AsString()));
			}
		}
		else if (const auto InnerStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
		{
			const auto InnerMapStruct = InnerStructProperty->Struct;
			if (InnerMapStruct->IsChildOf(FBeamMap::StaticStruct()))
			{
				const FMapProperty* InnerMapProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(InnerMapStruct); OptIt; ++OptIt)
				{
					InnerMapProperty = CastField<FMapProperty>(*OptIt);
					if (InnerMapProperty) break;
				}

				for (const auto& Value : JsonMap->Values)
				{
					const auto Key = Value.Key;

					const auto SubMap = Value.Value->AsObject();
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Key;

					ParseMapProperty(Key, SubMap, InnerMapProperty, MapHelper.GetValuePtr(LastEntryIdx));
				}
			}
			else if (InnerMapStruct->IsChildOf(FBeamArray::StaticStruct()))
			{
				const FArrayProperty* InnerArrayProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(InnerMapStruct); OptIt; ++OptIt)
				{
					InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
					if (InnerArrayProperty) break;
				}

				for (const auto& Value : JsonMap->Values)
				{
					const auto Key = Value.Key;

					const auto SubMap = Value.Value->AsArray();
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Key;

					ParseArrayProperty(Key, SubMap, InnerArrayProperty, MapHelper.GetValuePtr(LastEntryIdx));
				}
			}
			else if (InnerMapStruct->IsChildOf(FGameplayTag::StaticStruct()))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto Key = Value.Key;

					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Key;

					FGameplayTag* ValData = reinterpret_cast<FGameplayTag*>(MapHelper.GetValuePtr(LastEntryIdx));
					const FString JsonStr = Value.Value->AsString();
					const auto bShouldError = GetDefault<UBeamCoreSettings>()->bErrorIfGameplayTagNotFound;
					*ValData = FGameplayTag::RequestGameplayTag(FName(JsonStr), !JsonStr.Equals(TEXT("None")) && bShouldError);
				}
			}
			else if (InnerMapStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto Key = Value.Key;

					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Key;

					FGameplayTagContainer* ValData = reinterpret_cast<FGameplayTagContainer*>(MapHelper.GetValuePtr(LastEntryIdx));
					const FString JsonStr = Value.Value->AsString();
					ValData->FromExportString(JsonStr);
				}
			}
			else if (InnerMapStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto Key = Value.Key;

					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Key;

					FBeamSemanticType* ValData = reinterpret_cast<FBeamSemanticType*>(MapHelper.GetValuePtr(LastEntryIdx));
					const FString JsonStr = Value.Value->AsString();
					ValData->Set(&JsonStr, ValData->GetSerializationRepresentationName(0));
				}
			}
			else if (InnerMapStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto Key = Value.Key;

					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();
					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Key;

					FBeamJsonSerializableUStruct* ValData = reinterpret_cast<FBeamJsonSerializableUStruct*>(MapHelper.GetValuePtr(LastEntryIdx));
					ValData->BeamDeserializeProperties(Value.Value->AsObject());
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
			}
		}
		else if (CastField<FClassProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<UClass**>(MapHelper.GetValuePtr(LastEntryIdx));
				*ValData = FSoftClassPath{Value.Value->AsString()}.ResolveClass();
			}
		}
		else if (CastField<FTextProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<FText*>(MapHelper.GetValuePtr(LastEntryIdx));
				*ValData = FText::FromString(Value.Value->AsString());
			}
		}
		else if (CastField<FNameProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<FName*>(MapHelper.GetValuePtr(LastEntryIdx));
				*ValData = FName(Value.Value->AsString());
			}
		}
		else if (CastField<FStrProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<FString*>(MapHelper.GetValuePtr(LastEntryIdx));
				*ValData = Value.Value->AsString();
			}
		}
		else if (CastField<FBoolProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<bool*>(MapHelper.GetValuePtr(LastEntryIdx));
				*ValData = Value.Value->AsString().Equals(TEXT("true"), ESearchCase::IgnoreCase);
			}
		}
		else if (CastField<FFloatProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<float*>(MapHelper.GetValuePtr(LastEntryIdx));
				FDefaultValueHelper::ParseFloat(Value.Value->AsString(), *ValData);
			}
		}
		else if (CastField<FDoubleProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<double*>(MapHelper.GetValuePtr(LastEntryIdx));
				FDefaultValueHelper::ParseDouble(Value.Value->AsString(), *ValData);
			}
		}
		else if (CastField<FIntProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<int32*>(MapHelper.GetValuePtr(LastEntryIdx));
				FDefaultValueHelper::ParseInt(Value.Value->AsString(), *ValData);
			}
		}
		else if (CastField<FInt64Property>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<int64*>(MapHelper.GetValuePtr(LastEntryIdx));
				FDefaultValueHelper::ParseInt64(Value.Value->AsString(), *ValData);
			}
		}
		else if (CastField<FByteProperty>(MapProperty->ValueProp))
		{
			for (const auto& Value : JsonMap->Values)
			{
				const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

				auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
				*KeyData = Value.Key;

				auto ValData = reinterpret_cast<uint8*>(MapHelper.GetValuePtr(LastEntryIdx));
				int32 Parsed;
				FDefaultValueHelper::ParseInt(Value.Value->AsString(), Parsed);
				*ValData = static_cast<int8>(Parsed);
			}
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *PropName, *MapProperty->ValueProp->GetName())
		}

		// Must be called to have a valid map according to UE doc.
		MapHelper.Rehash();
	}
	else
	{
		UE_LOG(LogBeamContent, Error, TEXT("Content Serialization does not support maps with non-FString keys.\n"))
	}
}
