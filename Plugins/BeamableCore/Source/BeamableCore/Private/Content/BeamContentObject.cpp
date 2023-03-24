// Fill out your copyright notice in the Description page of Project Settings.


#include "Content/BeamContentObject.h"

#include "Misc/DefaultValueHelper.h"
#include "BeamLogging.h"
#include "AutoGen/ContentDefinition.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
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

	const auto Hash = CreatePropertiesMD5Hash();
	OutContentDefinition.Set("checksum", Hash);

	auto TagsArray = FJsonDomBuilder::FArray{};
	for (const auto& Tag : Tags) TagsArray.Add(Tag);
	OutContentDefinition.Set("tags", TagsArray);

	auto PropertiesJson = FJsonDomBuilder::FObject{};
	BuildPropertiesJsonObject(PropertiesJson);
	OutContentDefinition.Set("properties", PropertiesJson);
}

FString UBeamContentObject::CreatePropertiesMD5Hash()
{
	FJsonDomBuilder::FObject Json;
	BuildPropertiesJsonObject(Json);

	const FString PropertiesJson = Json.ToString<TCondensedJsonPrintPolicy>();

	FString Hash = FMD5::HashAnsiString(*PropertiesJson);

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
					CurrProp.Set("data", InnerOptionalSoftObjectProperty->GetID().ToString());
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
					else if (InnerOptionalStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
					{
						const FBeamSemanticType* BeamSemantic = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(Data);
						const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
						CurrProp.Set("data", *UnderlyingString);
					}
					else if (InnerOptionalStruct->IsChildOf(FBeamJsonSerializable::StaticStruct()))
					{
						const FBeamJsonSerializable* BeamJsonSerializable = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamJsonSerializable>(Data);
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
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
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
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
			{
				const FBeamSemanticType* BeamSemantic = StructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(this);
				const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
				CurrProp.Set("data", *UnderlyingString);
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamJsonSerializable::StaticStruct()))
			{
				const FBeamJsonSerializable* BeamJsonSerializable = StructProperty->ContainerPtrToValuePtr<FBeamJsonSerializable>(this);

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
			SoftObjectProperty->SetPropertyValue(Val, FSoftObjectPtr(FSoftObjectPath(JsonProperties->GetObjectField(PropName)->GetStringField("data"))));
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
					else if (InnerOptionalStruct->IsChildOf(FBeamJsonSerializable::StaticStruct()))
					{
						const auto SubJsonSerializable = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
						FBeamJsonSerializable* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamJsonSerializable>(OptionalVal);
						ValData->BeamDeserializeProperties(SubJsonSerializable);
						OptionalVal->Set(ValData);
					}
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
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
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
			{
				const auto SubJsonSemantic = JsonProperties->GetObjectField(PropName)->GetStringField("data");
				FBeamSemanticType* ValData = StructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(this);
				ValData->Set(&SubJsonSemantic, ValData->GetSerializationRepresentationName(0));
			}
			else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamJsonSerializable::StaticStruct()))
			{
				const auto SubJsonSerializable = JsonProperties->GetObjectField(PropName)->GetObjectField("data");
				FBeamJsonSerializable* ValData = StructProperty->ContainerPtrToValuePtr<FBeamJsonSerializable>(this);
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
		else if (InnerArrayStruct->IsChildOf(FBeamJsonSerializable::StaticStruct()))
		{
			const auto ArrayNum = ArrayHelper.Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				if (ArrayHelper.IsValidIndex(i))
				{
					const FBeamJsonSerializable* Data = reinterpret_cast<const FBeamJsonSerializable*>(ArrayHelper.GetRawPtr(i));

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
		else if (InnerArrayStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				FBeamSemanticType* ValData = reinterpret_cast<FBeamSemanticType*>(ArrayHelper.GetRawPtr(i));
				const FString JsonStr = JsonArray[i]->AsString();
				ValData->Set(&JsonStr, ValData->GetSerializationRepresentationName(0));
			}
		}
		else if (InnerArrayStruct->IsChildOf(FBeamJsonSerializable::StaticStruct()))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				FBeamJsonSerializable* ValData = reinterpret_cast<FBeamJsonSerializable*>(ArrayHelper.GetRawPtr(i));
				ValData->BeamDeserializeProperties(JsonArray[i]->AsObject());
			}
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
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
			else if (InnerMapStruct->IsChildOf(FBeamJsonSerializable::StaticStruct()))
			{
				const auto MapNum = MapHelper.Num();
				for (auto i = 0; i < MapNum; i++)
				{
					if (MapHelper.IsValidIndex(i))
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamJsonSerializable* Data = reinterpret_cast<const FBeamJsonSerializable*>(MapHelper.GetValuePtr(i));

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
			else if (InnerMapStruct->IsChildOf(FBeamJsonSerializable::StaticStruct()))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto Key = Value.Key;

					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();
					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Key;

					FBeamJsonSerializable* ValData = reinterpret_cast<FBeamJsonSerializable*>(MapHelper.GetValuePtr(LastEntryIdx));
					ValData->BeamDeserializeProperties(Value.Value->AsObject());
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
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
