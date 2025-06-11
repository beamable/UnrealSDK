#include <AutoGen/Enums/BeamContentType.h>
#include <AutoGen/Optionals/OptionalDateTime.h>

#include "BeamJsonUtilsMocks.h"

#include "Misc/AutomationTest.h"
#include "Serialization/BeamJsonUtils.h"
#include "AutoGen/Optionals/OptionalMapOfArrayOfCurrencyProperty.h"
#include "BeamBackend/SemanticTypes/BeamCid.h"


BEGIN_DEFINE_SPEC(FBeamJsonUtilsSpec, "BeamableUnreal.BeamJsonUtils", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext)
END_DEFINE_SPEC(FBeamJsonUtilsSpec)


void FBeamJsonUtilsSpec::Define()
{
	struct FTestInt : FBeamJsonSerializableUStruct
	{
		int a;

		virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
		{
			Serializer->WriteValue("a", a);
		}

		virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
		{
			Serializer->WriteValue("a", a);
		}

		virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
		{
			a = Bag->GetIntegerField(TEXT("a"));
		}
	};


	struct FBeamArrayOfInt : FBeamArray
	{
		TArray<int> Values;

		FBeamArrayOfInt() = default;

		FBeamArrayOfInt(const TArray<int>& Values)
			: Values(Values)
		{
		}

		virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeArray<int>(Values, Serializer);
		}

		virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeArray<int>(Values, Serializer);
		}

		virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
		{
			UBeamJsonUtils::DeserializeArray<int>(Elements, Values);
		}
	};
	struct FBeamArrayOfDateTime : FBeamArray
	{
		TArray<FDateTime> Values;

		FBeamArrayOfDateTime() = default;

		FBeamArrayOfDateTime(const TArray<FDateTime>& Values)
			: Values(Values)
		{
		}

		virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeArray<FDateTime>(Values, Serializer);
		}

		virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeArray<FDateTime>(Values, Serializer);
		}

		virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
		{
			UBeamJsonUtils::DeserializeArray<FDateTime>(Elements, Values);
		}
	};
	struct FBeamArrayOfBeamCid : public FBeamArray
	{
		TArray<FBeamCid> Values;

		FBeamArrayOfBeamCid() = default;

		FBeamArrayOfBeamCid(const TArray<FBeamCid>& Values)
			: Values(Values)
		{
		}

		virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeArray<FBeamCid, int64>(Values, Serializer);
		}

		virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeArray<FBeamCid, int64>(Values, Serializer);
		}

		virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
		{
			UBeamJsonUtils::DeserializeArray<FBeamCid, int64>(Elements, Values);
		}
	};


	struct FBeamMapOfInt : public FBeamMap
	{
		TMap<FString, int> Values;

		FBeamMapOfInt() = default;

		FBeamMapOfInt(const TMap<FString, int>& Values)
			: Values(Values)
		{
		}

		virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeMap<int>(Values, Serializer);
		}

		virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeMap<int>(Values, Serializer);
		}

		virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override
		{
			UBeamJsonUtils::DeserializeMap<int>(Elements, Values);
		}
	};

	struct FBeamMapOfBeamCid : public FBeamMap
	{
		TMap<FString, FBeamCid> Values;

		FBeamMapOfBeamCid() = default;

		FBeamMapOfBeamCid(const TMap<FString, FBeamCid>& Values)
			: Values(Values)
		{
		}

		virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeMap<FBeamCid, int64>(Values, Serializer);
		}

		virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeMap<FBeamCid, int64>(Values, Serializer);
		}

		virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override
		{
			UBeamJsonUtils::DeserializeMap<FBeamCid, int64>(Elements, Values);
		}
	};

	struct FBeamJsonBlob : public FBeamJsonSerializableUStruct
	{
		TSharedPtr<FJsonObject> Blob;

		FBeamJsonBlob() = default;

		FBeamJsonBlob(const TSharedPtr<FJsonObject>& Blob) : Blob(Blob)
		{
		}

		virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeJsonObject(TEXT("blob"), Blob, Serializer);
		}

		virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
		{
			UBeamJsonUtils::SerializeJsonObject(TEXT("blob"), Blob, Serializer);
		}

		virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
		{
			UBeamJsonUtils::DeserializeJsonObject(TEXT("blob"), Bag, Blob, OuterOwner);
		}
	};

	Describe("FBeamJsonUtils - Serialization", [this]()
	{
		It("should output a JSON Object representing the struct implementing BeamJsonSerializable", [this]()
		{
			int Val = 5;
			FTestInt Int{};
			Int.a = Val;

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			UBeamJsonUtils::SerializeUStruct<FTestInt>(Int, JsonSerializer);
			JsonSerializer->Close();

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({ "a" : 5 })");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("Serialization output is not correct", OutJson, Expected);
		});

		It("should output a JSON Object representing a FOptionalDateTime serialization", [this]()
		{
			// The date that will be used to reference 
			FString DateTimeStr = "2016-10-30T12:00:00.000Z";

			// Parse the date from STR to a DateTime
			FDateTime DateTime;
			FDateTime::ParseIso8601(*DateTimeStr, DateTime);

			// Creating the Optional DateTime 
			FOptionalDateTime OptDateTime = FOptionalDateTime(DateTime);
			//Serializing the OptionalDateTime
			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			JsonSerializer->WriteObjectStart();
			UBeamJsonUtils::SerializeOptional<FDateTime>("date", &OptDateTime, JsonSerializer);
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();

			// Creating the JSON to compare.
			const FString ExpectedJson =
				"{\"date\":\"" + DateTimeStr + "\"}";

			TestEqual(DateTime.ToIso8601(), OutJson, ExpectedJson);
		});

		It("should output a JSON Object representing a FDateTime serialization", [this]()
		{
			// The date that will be used to reference 
			FString DateTimeStr = "2016-10-30T12:00:00.000Z";

			// Parse the date from STR to a DateTime
			FDateTime DateTime;
			FDateTime::ParseIso8601(*DateTimeStr, DateTime);

			//Serializing the DateTime
			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			JsonSerializer->WriteObjectStart();
			JsonSerializer->WriteValue(TEXT("date"), DateTime.ToIso8601());
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();

			// Creating the JSON to compare.
			const FString ExpectedJson =
				"{\"date\":\"" + DateTimeStr + "\"}";

			TestEqual(DateTime.ToIso8601(), OutJson, ExpectedJson);
		});

		It("should output a blank JSON Object (Optional Primitive without Set Value)", [this]()
		{
			struct FTestOptionalInt : FBeamOptional
			{
				int Val = 0;

				virtual const void* GetAddr() const override { return &Val; }

				virtual void Set(const void* Data) override
				{
					Val = *static_cast<const int*>(Data);
					IsSet = true;
				}
			};

			int Val = 5;
			FTestOptionalInt OptionalInt{};
			FBeamOptional::Set<int>(&OptionalInt, &Val);
			FBeamOptional::Reset<int>(&OptionalInt);

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			JsonSerializer->WriteObjectStart();
			UBeamJsonUtils::SerializeOptional<int>(TEXT("a"), &OptionalInt, JsonSerializer);
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();


			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({ })");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("Int Optional Skipped since it isn't set", OutJson, Expected);
		});

		It("should output a regular JSON Field (UObject with primitive)", [this]()
		{
			UMockIntJsonSerializable* asd = NewObject<UMockIntJsonSerializable>();
			asd->OuterOwner = GetTransientPackage();
			asd->a = 5;

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			UBeamJsonUtils::SerializeUObject(asd, JsonSerializer);
			JsonSerializer->Close();

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({
					"a": 5
				})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("Primitive UObject serialized correctly", OutJson, Expected);
		});

		It("should output a regular JSON Field (UObject with nested UObjects)", [this]()
		{
			UMockNestedJsonSerializable* asd = NewObject<UMockNestedJsonSerializable>();
			asd->OuterOwner = GetTransientPackage();
			asd->a = TArray{NewObject<UMockIntJsonSerializable>(), NewObject<UMockIntJsonSerializable>()};
			asd->a[0]->a = 1;
			asd->a[1]->a = 2;

			asd->b = NewObject<UMockIntJsonSerializable>();
			asd->b->a = 3;

			asd->c = TMap<FString, UMockIntJsonSerializable*>{
				{FString("c1"), NewObject<UMockIntJsonSerializable>()},
				{FString("c2"), NewObject<UMockIntJsonSerializable>()}
			};
			asd->c.FindRef("c1")->a = 4;
			asd->c.FindRef("c2")->a = 5;

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			UBeamJsonUtils::SerializeUObject(asd, JsonSerializer);
			JsonSerializer->Close();

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({
						"a":[{
							"a" : 1
						},
						{
							"a": 2
						}],
						"b": {
							"a" : 3
						},
						"c": {
							"c1": {
								"a": 4
							},
							"c2": {
								"a": 5
							}
						}
					})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("Nested UObjects serialized correctly", OutJson, Expected);
		});

		It("should output a regular JSON Field (Optional Primitive with Value)", [this]()
		{
			struct FTestOptionalInt : FBeamOptional
			{
				int Val = 0;

				virtual const void* GetAddr() const override { return &Val; }

				virtual void Set(const void* Data) override
				{
					Val = *static_cast<const int*>(Data);
					IsSet = true;
				}
			};

			int Val = 5;
			FTestOptionalInt OptionalInt{};
			FBeamOptional::Set<int>(&OptionalInt, &Val);

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			JsonSerializer->WriteObjectStart();
			UBeamJsonUtils::SerializeOptional<int>(TEXT("a"), &OptionalInt, JsonSerializer);
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();


			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({
					"a": 5
				})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("Int Optional serialized correctly", OutJson, Expected);
		});

		It("should output a regular JSON Field (Optional SemanticType with Value)", [this]()
		{
			FBeamCid Val = FBeamCid{12341234};
			FOptionalMockNestedSemanticType Optional{};
			FBeamOptional::Set<FBeamCid>(&Optional, &Val);

			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("cid"), &Optional, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"cid": "12341234"
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("FBeamSemanticType Optional serialized correctly", OutJson, Expected);
			}

			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeOptional<FBeamCid, int64>(TEXT("cid"), &Optional, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"cid": 12341234
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("FBeamSemanticType Optional serialized correctly", OutJson, Expected);
			}
		});

		It("should serialize correctly a enum", [this]()
		{
			EBeamContentType Val = EBeamContentType::BEAM_content;

			auto Result = UBeamJsonUtils::EnumToSerializationName(Val);
			FString ExpectedResult = "content";

			TestEqual("Enum Optional serialized correctly", Result, ExpectedResult);
		});
		
		It("should deserialize a int correctly into a enum", [this]()
		{
			EBeamContentType ExpectedResult = EBeamContentType::BEAM_content;
		
			auto Result = UBeamJsonUtils::SerializationIndexToEnum<EBeamContentType>(0);
		
			TestEqual("Enum deserialize correctly", Result, ExpectedResult);
		});
		
		It("should deserialize a string correctly into a enum", [this]()
		{
			EBeamContentType ExpectedResult = EBeamContentType::BEAM_content;
		
			auto Result = UBeamJsonUtils::SerializationNameToEnum<EBeamContentType>("content");
		
			TestEqual("Enum deserialized correctly", Result, ExpectedResult);
		});



		It("should output a regular JSON Field (Optional FBeamJsonSerializable with Value)", [this]()
		{
			struct FTest : FBeamJsonSerializableUStruct
			{
				int a;
				FString b;

				FTest(int A, const FString& B)
					: a(A),
					  b(B)
				{
				}

				virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
				{
					Serializer->WriteValue(TEXT("a"), a);
					Serializer->WriteValue(TEXT("b"), b);
				}
			};

			struct FTestOptional : FBeamOptional
			{
				FTest Val;

				FTestOptional(): Val(FTest{0, TEXT("")})
				{
					IsSet = false;
				}

				virtual const void* GetAddr() const override { return &Val; }

				virtual void Set(const void* Data) override
				{
					Val = *static_cast<const FTest*>(Data);
					IsSet = true;
				}
			};

			FTest Val = FTest{1, TEXT("b")};
			FTestOptional OptionalTest;
			FBeamOptional::Set<FTest>(&OptionalTest, &Val);

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			JsonSerializer->WriteObjectStart();
			UBeamJsonUtils::SerializeOptional<FTest>(TEXT("a1"), &OptionalTest, JsonSerializer);
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();


			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({
					"a1": {
						"a": 1,
						"b": "b"
					}
				})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("FBeamSerializable Optional serialized correctly", OutJson, Expected);
		});

		It("should output a regular JSON Field (Optional TArray with Value)", [this]()
		{
			// Test array with primitive
			{
				struct FOptionalArrayInt : FBeamOptional
				{
					TArray<int> Val;

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TArray<int>*>(Data);
						IsSet = true;
					}
				};

				TArray<int> Array;
				Array.Add(1);
				Array.Add(-1);
				Array.Add(0);
				FOptionalArrayInt OptionalInt{};
				FBeamOptional::Set<TArray<int>>(&OptionalInt, &Array);

				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeOptional<TArray<int>, int>(TEXT("a"), &OptionalInt, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"a": [1, -1, 0]
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("Optional Array of Int serialized correctly", OutJson, Expected);
			}
			// Test array with date time
			{
				struct FOptionalArrayDateTime : FBeamOptional
				{
					TArray<FDateTime> Val;

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TArray<FDateTime>*>(Data);
						IsSet = true;
					}
				};

				TArray<FDateTime> Array;
				FDateTime ExpectedDate = FDateTime::Now();
				Array.Add(ExpectedDate);
				Array.Add(ExpectedDate);
				Array.Add(ExpectedDate);
				FOptionalArrayDateTime OptionalDate{};
				FBeamOptional::Set<TArray<FDateTime>>(&OptionalDate, &Array);

				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeOptional<TArray<FDateTime>, FDateTime>(TEXT("a"), &OptionalDate, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString Expected = "{\"a\":[\"" + ExpectedDate.ToIso8601() + "\",\"" + ExpectedDate.ToIso8601() + "\",\"" + ExpectedDate.ToIso8601() + "\"]}";

				TestEqual("Optional Array of FDateTime serialized correctly", OutJson, Expected);
			}
			// Test array with BeamJsonSerializable
			{
				struct FTest : FBeamJsonSerializableUStruct
				{
					int a;
					FString b;

					FTest(int A, const FString& B)
						: a(A),
						  b(B)
					{
					}

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						Serializer->WriteValue(TEXT("a"), a);
						Serializer->WriteValue(TEXT("b"), b);
					}
				};

				struct FTestArrayOptional : FBeamOptional
				{
					TArray<FTest> Val;

					FTestArrayOptional() { IsSet = false; }

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TArray<FTest>*>(Data);
						IsSet = true;
					}
				};

				TArray<FTest> Array;
				Array.Add(FTest{1, TEXT("b1")});
				Array.Add(FTest{2, TEXT("b2")});
				FTestArrayOptional OptionalTest;
				FBeamOptional::Set<TArray<FTest>>(&OptionalTest, &Array);

				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeOptional<TArray<FTest>, FTest>(TEXT("a1"), &OptionalTest, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"a1": [{
						"a": 1,
						"b": "b1"
					},
					{
						"a": 2,
						"b": "b2"
					}]
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("Optional Array of FBeamSerializable serialized correctly", OutJson, Expected);
			}

			// Test array with BeamSemanticType
			{
				struct FTestArrayOptional : FBeamOptional
				{
					TArray<FBeamCid> Val;

					FTestArrayOptional() { IsSet = false; }

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TArray<FBeamCid>*>(Data);
						IsSet = true;
					}
				};

				TArray<FBeamCid> Array;
				Array.Add(FBeamCid{1});
				Array.Add(FBeamCid{2});
				FTestArrayOptional OptionalTest;
				FBeamOptional::Set<TArray<FBeamCid>>(&OptionalTest, &Array);

				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeOptional<TArray<FBeamCid>, FBeamCid, int64>(TEXT("cids"), &OptionalTest, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"cids": [1, 2]
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("Optional Array of FBeamSerializable serialized correctly", OutJson, Expected);
			}
		});

		It("should output a serialized raw JSON Array of primitives", [this]()
		{
			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

			TArray<int> a;
			a.Add(1);
			a.Add(-1);
			a.Add(0);
			const FBeamArrayOfInt BeamArray = a;
			BeamArray.BeamSerialize(JsonSerializer);
			JsonSerializer->Close();

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString Expected = TEXT(R"([1,-1,0])");
			TestEqual("Int-Array serialized correctly", OutJson, Expected);
		});

		It("should output a serialized raw JSON Array of FOptionalDateTime", [this]()
		{
			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			FDateTime ReferenceDate = FDateTime::Now();
			TArray<FDateTime> a;
			a.Add(ReferenceDate);
			a.Add(ReferenceDate);
			a.Add(ReferenceDate);
			const FBeamArrayOfDateTime BeamArray = a;
			BeamArray.BeamSerialize(JsonSerializer);
			JsonSerializer->Close();

			FString ExpectedDateItem = "\"" + ReferenceDate.ToIso8601() + "\"";
			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString Expected = TEXT("["+ExpectedDateItem+","+ExpectedDateItem+","+ExpectedDateItem+"]");
			TestEqual("JSON result", OutJson, Expected);
		});

		It("should output a serialized raw JSON Object of primitives", [this]()
		{
			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

			TMap<FString, int> a;
			a.Add("a", 1);
			a.Add("b", -1);
			a.Add("c", 0);
			const FBeamMapOfInt BeamMap = a;
			BeamMap.BeamSerialize(JsonSerializer);
			JsonSerializer->Close();

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({"a":1,"b":-1,"c":0})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("Int-Array serialized correctly", OutJson, Expected);
		});

		It("should output a serialized JSON Object with an Array of primitives", [this]()
		{
			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

			TArray<int> a;
			a.Add(1);
			a.Add(-1);
			a.Add(0);
			JsonSerializer->WriteObjectStart();
			UBeamJsonUtils::SerializeArray<int>(TEXT("a"), a, JsonSerializer);
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();


			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({
					"a": [ 1, -1, 0 ]
				})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("Int-Array serialized correctly", OutJson, Expected);

			// TODO: Add other primitives (but really shouldn't be necessary)
		});

		It("should output a serialized JSON Object with an Array of FBeamJsonSerializable", [this]()
		{
			struct FTest : FBeamJsonSerializableUStruct
			{
				int a;
				FString b;

				FTest(int A, const FString& B)
					: a(A),
					  b(B)
				{
				}

				virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
				{
					Serializer->WriteValue(TEXT("a"), a);
					Serializer->WriteValue(TEXT("b"), b);
				}
			};

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

			TArray<FTest> array;
			array.Add(FTest{0, TEXT("b1")});
			array.Add(FTest{1, TEXT("b2")});
			JsonSerializer->WriteObjectStart();
			UBeamJsonUtils::SerializeArray<FTest>(TEXT("array"), array, JsonSerializer);
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();


			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({
					"array": [
				{
					"a": 0,
					"b": "b1"
				},
				{
					"a": 1,
					"b": "b2"
				}]
				})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("TArray<FBeamJsonSerializable> Serialized Correctly", OutJson, Expected);
		});

		It("should output a serialized JSON Map", [this]()
		{
			// TMap<FString, int>
			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

				TMap<FString, int> map;
				map.Add("a1", 0);
				map.Add("a2", -1);
				map.Add("a3", 1);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeMap<int>(TEXT("map"), map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": 
					{
						"a1": 0,
						"a2": -1,
						"a3": 1
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, T>, where T = int type, serialized correctly", OutJson, Expected);
			}
			// TMap<FString, FString>
			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

				TMap<FString, FString> map;
				map.Add("a1", "b1");
				map.Add("a2", "b2");
				map.Add("a3", "b3");
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeMap<FString>(TEXT("map"), map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": 
					{
						"a1": "b1",
						"a2": "b2",
						"a3": "b3"
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, T>, where T = FString type, serialized correctly", OutJson, Expected);
			}

			// TMap<FString, FBeamCid>
			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

				TMap<FString, FBeamCid> map;
				map.Add("a1", 0);
				map.Add("a2", -1);
				map.Add("a3", 1);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeMap<FBeamCid, int64>(TEXT("map"), map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": 
					{
						"a1": 0,
						"a2": -1,
						"a3": 1
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, T>, where T = BeamSemanticType, serialized correctly", OutJson, Expected);
			}

			// TMap<FString, FDateTime>
			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

				TMap<FString, FDateTime> map;
				FDateTime Now = FDateTime::Now();
				map.Add("a1", Now);
				map.Add("a2", Now);
				map.Add("a3", Now);
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeMap<FDateTime>(TEXT("map"), map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();

				FString ExpectedDate = Now.ToIso8601();

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					FString::Printf(TEXT(R"({"map":{
						"a1": "%s",
						"a2": "%s",
						"a3": "%s"
					}
				})"), *ExpectedDate, *ExpectedDate, *ExpectedDate);
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, T>, where T = FDateTime, serialized correctly", OutJson, Expected);
			}
		});

		It("should output a serialized JSON Map of FBeamJsonSerializable", [this]()
		{
			struct FTest : FBeamJsonSerializableUStruct
			{
				int a;
				FString b;

				FTest(int A, const FString& B)
					: a(A),
					  b(B)
				{
				}

				virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
				{
					Serializer->WriteValue(TEXT("a"), a);
					Serializer->WriteValue(TEXT("b"), b);
				}
			};

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

			TMap<FString, FTest> Map;
			Map.Add("a1", FTest{0, TEXT("b1")});
			Map.Add("a2", FTest{1, TEXT("b2")});
			JsonSerializer->WriteObjectStart();
			UBeamJsonUtils::SerializeMap<FTest>(TEXT("map"), Map, JsonSerializer);
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();


			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({
					"map": {
						"a1": {
							"a" : 0,
							"b": "b1"
						},
						"a2":{
							"a": 1,
							"b": "b2"
						}
					}
				})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("TMap<FString, FBeamJsonSerializable> Serialized Correctly", OutJson, Expected);
		});

		It("should output a serialized JSON Map of FBeamJsonSerializable with an Array in it", [this]()
		{
			struct FTest : FBeamJsonSerializableUStruct
			{
				int a;
				FString b;
				TArray<int> c;

				FTest(int A, const FString& B, const TArray<int>& C)
					: a(A),
					  b(B),
					  c(C)
				{
				}

				virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
				{
					Serializer->WriteValue(TEXT("a"), a);
					Serializer->WriteValue(TEXT("b"), b);
					UBeamJsonUtils::SerializeArray<int>(TEXT("c"), c, Serializer);
				}
			};

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

			TArray<int> c1, c2;
			c1.Add(1);
			c1.Add(2);
			c2.Add(-1);
			c2.Add(-2);

			TMap<FString, FTest> Map;
			Map.Add("a1", FTest{0, TEXT("b1"), c1});
			Map.Add("a2", FTest{1, TEXT("b2"), c2});
			JsonSerializer->WriteObjectStart();
			UBeamJsonUtils::SerializeMap<FTest>(TEXT("map"), Map, JsonSerializer);
			JsonSerializer->WriteObjectEnd();
			JsonSerializer->Close();


			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp =
				TEXT(R"({
					"map": {
						"a1": {
							"a" : 0,
							"b": "b1",
							"c": [ 1, 2 ]
						},
						"a2":{
							"a": 1,
							"b": "b2",
							"c": [ -1, -2 ]
						}
					}
				})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("TMap<FString, FBeamJsonSerializable> with an internal TArray<int> Serialized Correctly", OutJson, Expected);
		});

		It("should output a serialized JSON Map of FBeamArrayOf___ (primitive & semantic type)", [this]()
		{
			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

				TMap<FString, FBeamArrayOfInt> Map;
				Map.Add("a", FBeamArrayOfInt(TArray<int>{0, 10}));
				Map.Add("b", FBeamArrayOfInt(TArray<int>{0, 20}));
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeMap<FBeamArrayOfInt>(TEXT("map"), Map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": {
						"a": [0, 10],
						"b": [0, 20]
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, FBeamArrayOfPrimitiveType> Serialized Correctly", OutJson, Expected);
			}

			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

				TMap<FString, FBeamArrayOfBeamCid> Map;
				Map.Add("a", FBeamArrayOfBeamCid(TArray<FBeamCid>{0, 10}));
				Map.Add("b", FBeamArrayOfBeamCid(TArray<FBeamCid>{0, 20}));
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeMap<FBeamArrayOfBeamCid>(TEXT("map"), Map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": {
						"a": [0, 10],
						"b": [0, 20]
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, FBeamArrayOfSemanticType> Serialized Correctly", OutJson, Expected);
			}
		});

		It("should output a serialized JSON Map of FBeamMapOf___ (primitive & semantic type)", [this]()
		{
			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

				TMap<FString, FBeamMapOfInt> Map;
				Map.Add("a", FBeamMapOfInt(TMap<FString, int>{{TEXT("a"), 0}, {TEXT("b"), 10}}));
				Map.Add("b", FBeamMapOfInt(TMap<FString, int>{{TEXT("a"), 0}, {TEXT("b"), 20}}));
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeMap<FBeamMapOfInt>(TEXT("map"), Map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": {
						"a": {
							"a": 0,
							"b": 10
						},
						"b": {
							"a": 0,
							"b": 20
						}
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, FBeamMapOfPrimitiveType> Serialized Correctly", OutJson, Expected);
			}

			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);

				TMap<FString, FBeamMapOfBeamCid> Map;
				Map.Add("a", FBeamMapOfBeamCid(TMap<FString, FBeamCid>{{TEXT("a"), 0}, {TEXT("b"), 10}}));
				Map.Add("b", FBeamMapOfBeamCid(TMap<FString, FBeamCid>{{TEXT("a"), 0}, {TEXT("b"), 20}}));
				JsonSerializer->WriteObjectStart();
				UBeamJsonUtils::SerializeMap<FBeamMapOfBeamCid>(TEXT("map"), Map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": {
						"a": {
							"a": 0,
							"b": 10
						},
						"b": {
							"a": 0,
							"b": 20
						}
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, FBeamMapOfSemanticType> Serialized Correctly", OutJson, Expected);
			}
		});

		It("should output a JSON Object with an arbitrary JSON-blob in it", [this]()
		{
			FJsonDataBag Bag;
			if (!Bag.FromJson(TEXT(R"({ "arbitraryBool": false, "arbitraryString": "string", "arbitraryNumber": 0 })")))
			{
				TestTrue(TEXT("Should never see this... means the string above isn't valid"), false);
			}

			FBeamJsonBlob Blob{};
			Blob.Blob = Bag.JsonObject;

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJson);
			UBeamJsonUtils::SerializeUStruct<FBeamJsonBlob>(Blob, JsonSerializer);
			JsonSerializer->Close();

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString ExpectedTemp = TEXT(R"({"blob":{"arbitraryBool":false,"arbitraryString":"string","arbitraryNumber":0}})");
			FJsonDataBag ExpectedBag;
			ExpectedBag.FromJson(ExpectedTemp);
			const FString Expected = ExpectedBag.ToJson(false);

			TestEqual("Serialization output is not correct", OutJson, Expected);
		});
	});


	Describe("FBeamJsonUtils - Deserialization", [this]()
	{
		It("should deserialize a JSON Object as a struct implementing BeamJsonSerializable", [this]()
		{
			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"({
						"a": 5
					})");

			FTestInt Test{};
			Test.BeamDeserialize(JsonInput);

			TestTrue("Struct Properties were deserialized correctly", Test.a == 5);
		});

		It("should deserialize a JSON Object as FOptionalDateTime", [this]()
		{
			struct FTestOptionalDateTime : FBeamJsonSerializableUStruct
			{
				FOptionalDateTime date;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeOptional<FDateTime>("date", Bag, date);
				}
			};
			// Get a mock json with a date time
			const FString JsonInput =
				TEXT(R"({
							"date": "2016-10-30T12:00:00.000Z"
						})");
			FDateTime ExpectedDate;
			FDateTime::ParseIso8601(TEXT("2016-10-30T12:00:00.000Z"), ExpectedDate);
			FTestOptionalDateTime Test{};
			Test.BeamDeserialize(JsonInput);

			TestEqual("date", Test.date.Val, ExpectedDate);
		});

		It("should deserialize a JSON Object as FDateTime", [this]()
		{
			struct FTestDateTime : FBeamJsonSerializableUStruct
			{
				FDateTime date;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					FDateTime::ParseIso8601(*Bag->GetStringField(TEXT("date")), date);
				}
			};
			// Get a mock json with a date time
			const FString JsonInput =
				TEXT(R"({
							"date": "2016-10-30T12:00:00.000Z"
						})");
			FDateTime ExpectedDate;
			FDateTime::ParseIso8601(TEXT("2016-10-30T12:00:00.000Z"), ExpectedDate);
			FTestDateTime Test{};
			Test.BeamDeserialize(JsonInput);

			TestEqual("date", Test.date, ExpectedDate);
		});

		It("should deserialize a JSON Object as a UObject with nested properties", [this]()
		{
			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"({
						"a":[{
							"a" : 1
						},
						{
							"a": 2
						}],
						"b": {
							"a" : 3
						},
						"c": {
							"c1": {
								"a": 4
							},
							"c2": {
								"a": 5
							}
						}
					})");

			UMockNestedJsonSerializable* Test = NewObject<UMockNestedJsonSerializable>(GetTransientPackage());
			Test->OuterOwner = Test->GetOuter();
			Test->BeamDeserialize(JsonInput);

			TestTrue("UObject Properties were deserialized correctly", Test->a[0]->a == 1);
			TestTrue("UObject Properties were deserialized correctly", Test->a[1]->a == 2);
			TestTrue("UObject Properties were deserialized correctly", Test->b->a == 3);
			TestTrue("UObject Properties were deserialized correctly", Test->c.FindChecked("c1")->a == 4);
			TestTrue("UObject Properties were deserialized correctly", Test->c.FindChecked("c2")->a == 5);
		});

		It("should deserialize a JSON Object as an Optional UObject with nested properties", [this]()
		{
			struct FTest : FBeamJsonSerializableUStruct
			{
				FOptionalMockNestedJsonSerializable opt;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeOptional<UMockNestedJsonSerializable*>("opt", Bag, opt, OuterOwner);
				}
			};

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"({
					"opt":{
						"a":[{
							"a" : 1
						},
						{
							"a": 2
						}],
						"b": {
							"a" : 3
						},
						"c": {
							"c1": {
								"a": 4
							},
							"c2": {
								"a": 5
							}
						}
					}
				})");

			FTest Test;
			Test.OuterOwner = GetTransientPackage();
			Test.BeamDeserialize(JsonInput);

			TestTrue("UObject Properties were deserialized correctly", Test.opt.Val->a[0]->a == 1);
			TestTrue("UObject Properties were deserialized correctly", Test.opt.Val->a[1]->a == 2);
			TestTrue("UObject Properties were deserialized correctly", Test.opt.Val->b->a == 3);
			TestTrue("UObject Properties were deserialized correctly", Test.opt.Val->c.FindChecked("c1")->a == 4);
			TestTrue("UObject Properties were deserialized correctly", Test.opt.Val->c.FindChecked("c2")->a == 5);
		});

		It("should deserialize a blank JSON Object as an Optional Primitive without Set Value", [this]()
		{
			struct FTestOptionalInt : FBeamOptional
			{
				int Val = 0;

				virtual const void* GetAddr() const override { return &Val; }

				virtual void Set(const void* Data) override
				{
					Val = *((int*)Data);
					IsSet = true;
				}
			};

			struct FTest : FBeamJsonSerializableUStruct
			{
				FTestOptionalInt a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeOptional<int>("a", Bag, a);
				}
			};

			struct FTestOptionalBeamCid : FBeamOptional
			{
				FBeamCid Val = 0;

				virtual const void* GetAddr() const override { return &Val; }

				virtual void Set(const void* Data) override
				{
					Val = *((FBeamCid*)Data);
					IsSet = true;
				}
			};

			struct FTestBeamCid : FBeamJsonSerializableUStruct
			{
				FTestOptionalBeamCid a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeOptional<FBeamCid, int64>("a", Bag, a);
				}
			};

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"({ })");

			FTest Test;
			Test.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized as default value", Test.a.Val == 0);
			TestFalse("Optional was deserialized with IsSet == false", Test.a.IsSet);

			FTestBeamCid Test2;
			Test2.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized as default value", Test2.a.Val.AsLong == -1);
			TestFalse("Optional was deserialized with IsSet == false", Test2.a.IsSet);
		});

		It("should deserialize a JSON Object as an Optional Primitive with Set Value", [this]()
		{
			struct FTestOptionalInt : FBeamOptional
			{
				int Val = 0;

				virtual const void* GetAddr() const override { return &Val; }

				virtual void Set(const void* Data) override
				{
					Val = *static_cast<const int*>(Data);
					IsSet = true;
				}
			};

			struct FTest : FBeamJsonSerializableUStruct
			{
				FTestOptionalInt a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeOptional<int>("a", Bag, a);
				}
			};

			struct FTestOptionalBeamCid : FBeamOptional
			{
				FBeamCid Val = 0;

				virtual const void* GetAddr() const override { return &Val; }

				virtual void Set(const void* Data) override
				{
					Val = *((FBeamCid*)Data);
					IsSet = true;
				}
			};

			struct FTestBeamCid : FBeamJsonSerializableUStruct
			{
				FTestOptionalBeamCid a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeOptional<FBeamCid, int64>("a", Bag, a);
				}
			};


			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"({
					"a": 2
				})");

			FTest Test;
			Test.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized with correct value", Test.a.Val == 2);
			TestTrue("Optional was deserialized with IsSet == true", Test.a.IsSet);

			FTestBeamCid Test2;
			Test2.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized with correct value", Test2.a.Val.AsLong == 2);
			TestTrue("Optional was deserialized with IsSet == true", Test2.a.IsSet);
		});

		It("should deserialize a JSON Object as an Optional FBeamJsonSerializable with Set Value", [this]()
		{
			struct FTestData : FBeamJsonSerializableUStruct
			{
				int a;
				FString b;

				FTestData() : a(0), b(TEXT(""))
				{
				}

				FTestData(int A, const FString& B)
					: a(A),
					  b(B)
				{
				}

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					a = Bag->GetIntegerField(TEXT("a"));
					b = Bag->GetStringField(TEXT("b"));
				}
			};

			struct FTestOptional : FBeamOptional
			{
				FTestData Val;

				FTestOptional(): Val(FTestData{0, TEXT("")})
				{
					IsSet = false;
				}

				virtual const void* GetAddr() const override { return &Val; }

				virtual void Set(const void* Data) override
				{
					Val = *static_cast<const FTestData*>(Data);
					IsSet = true;
				}
			};

			struct FTest : FBeamJsonSerializableUStruct
			{
				FTestOptional a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeOptional<FTestData>("a", Bag, a);
				}
			};

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"({
					"a": {
						"a" : 1,
						"b" : "Test"
					}
				})");

			FTest Test;
			Test.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized with correct integer value", Test.a.Val.a == 1);
			TestTrue("Optional was deserialized with correct string value", Test.a.Val.b == TEXT("Test"));
			TestTrue("Optional was deserialized with IsSet == true", Test.a.IsSet);
		});

		It("should deserialize a JSON Object as an Optional TArray<> with Set Value", [this]()
		{
			// Test deserialize optional TArray<int>
			{
				struct FOptionalArrayInt : FBeamOptional
				{
					TArray<int> Val;

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TArray<int>*>(Data);
						IsSet = true;
					}
				};

				struct FTest : FBeamJsonSerializableUStruct
				{
					FOptionalArrayInt a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeOptional<TArray<int>, int>("a", Bag, a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					TEXT(R"({
					"a": [0, 1, -1]
				})");

				FTest Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct value at idx 0", Test.a.Val[0] == 0);
				TestTrue("Optional was deserialized with correct value at idx 1", Test.a.Val[1] == 1);
				TestTrue("Optional was deserialized with correct value at idx 2", Test.a.Val[2] == -1);
				TestTrue("Optional was deserialized with IsSet == true", Test.a.IsSet);
			}
			// Test deserialize optional TArray<FDateTime>
			{
				struct FOptionalArrayDateTime : FBeamOptional
				{
					TArray<FDateTime> Val;

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TArray<FDateTime>*>(Data);
						IsSet = true;
					}
				};

				struct FTest : FBeamJsonSerializableUStruct
				{
					FOptionalArrayDateTime a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeOptional<TArray<FDateTime>, FDateTime>("a", Bag, a);
					}
				};
				FDateTime ExpectedDate = FDateTime::Now();
				// Get a condensed string so we can easily compare with the condensed string we generate.
				FString JsonInput =
					"{\"a\": [\"" + ExpectedDate.ToIso8601() + "\", \"" + ExpectedDate.ToIso8601() + "\", \"" + ExpectedDate.ToIso8601() + "\"]}";

				FTest Test2;
				Test2.BeamDeserialize(JsonInput);

				TestTrue("Optional date was deserialized with correct value at idx 0", Test2.a.Val[0] == ExpectedDate);
				TestTrue("Optional date was deserialized with correct value at idx 1", Test2.a.Val[1] == ExpectedDate);
				TestTrue("Optional date was deserialized with correct value at idx 2", Test2.a.Val[2] == ExpectedDate);
				TestTrue("Optional was deserialized with IsSet == true", Test2.a.IsSet);
			}
			// Test deserialize optional TArray<FBeamSemanticType>
			{
				struct FOptionalArrayBeamCid : FBeamOptional
				{
					TArray<FBeamCid> Val;

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TArray<FBeamCid>*>(Data);
						IsSet = true;
					}
				};

				struct FTestBeamCid : FBeamJsonSerializableUStruct
				{
					FOptionalArrayBeamCid a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeOptional<TArray<FBeamCid>, FBeamCid, int64>("a", Bag, a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					TEXT(R"({
					"a": [0, 1, -1]
				})");

				FTestBeamCid Test2;
				Test2.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct value at idx 0", Test2.a.Val[0].AsLong == 0);
				TestTrue("Optional was deserialized with correct value at idx 1", Test2.a.Val[1].AsLong == 1);
				TestTrue("Optional was deserialized with correct value at idx 2", Test2.a.Val[2].AsLong == -1);
				TestTrue("Optional was deserialized with IsSet == true", Test2.a.IsSet);
			}

			// Test deserialize optional TArray<FBeamJsonSerializable>
			{
				struct FTestData : FBeamJsonSerializableUStruct
				{
					int a;
					FString b;

					FTestData() : a(0), b(TEXT(""))
					{
					}

					FTestData(int A, const FString& B)
						: a(A),
						  b(B)
					{
					}

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						a = Bag->GetIntegerField(TEXT("a"));
						b = Bag->GetStringField(TEXT("b"));
					}
				};

				struct FTestOptional : FBeamOptional
				{
					TArray<FTestData> Val;

					FTestOptional()
					{
						IsSet = false;
					}

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TArray<FTestData>*>(Data);
						IsSet = true;
					}
				};

				struct FTest : FBeamJsonSerializableUStruct
				{
					FTestOptional a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeOptional<TArray<FTestData>, FTestData>("a", Bag, a);
					}
				};

				// The json we are deserializing
				const FString JsonInput =
					TEXT(R"({
					"a": [{
						"a" : 1,
						"b" : "Test"
					},
					{
						"a" : 2,
						"b" : "Test"
					}]
				})");

				FTest Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct integer value", Test.a.Val[0].a == 1);
				TestTrue("Optional was deserialized with correct string value", Test.a.Val[0].b == TEXT("Test"));

				TestTrue("Optional was deserialized with correct integer value", Test.a.Val[1].a == 2);
				TestTrue("Optional was deserialized with correct string value", Test.a.Val[1].b == TEXT("Test"));

				TestTrue("Optional was deserialized with IsSet == true", Test.a.IsSet);
			}
		});

		It("should deserialize a JSON Object as an Optional TMap<FString,> with Set Value", [this]()
		{
			// Test deserialize optional TArray<int>
			{
				struct FOptionalMapOfInt : FBeamOptional
				{
					TMap<FString, int> Val;

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TMap<FString, int>*>(Data);
						IsSet = true;
					}
				};

				struct FTest : FBeamJsonSerializableUStruct
				{
					FOptionalMapOfInt a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeOptional<TMap<FString, int>, int>("a", Bag, a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					TEXT(R"({
					"a": {
						"a1": 1,
						"a2": 2,
						"a3": 3
					}
				})");

				FTest Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct value at idx 0", Test.a.Val.FindChecked("a1") == 1);
				TestTrue("Optional was deserialized with correct value at idx 1", Test.a.Val.FindChecked("a2") == 2);
				TestTrue("Optional was deserialized with correct value at idx 2", Test.a.Val.FindChecked("a3") == 3);
				TestTrue("Optional was deserialized with IsSet == true", Test.a.IsSet);
			}
			// Test deserialize optional TMap<FDateTime>
			{
				struct FOptionalMapOfDateTime : FBeamOptional
				{
					TMap<FString, FDateTime> Val;

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TMap<FString, FDateTime>*>(Data);
						IsSet = true;
					}
				};

				struct FTest : FBeamJsonSerializableUStruct
				{
					FOptionalMapOfDateTime a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeOptional<TMap<FString, FDateTime>, FDateTime>("a", Bag, a);
					}
				};

				FDateTime Now = FDateTime::Now();

				FString DateSTR = Now.ToIso8601();
				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					FString::Printf(TEXT(R"({
					"a": {
						"a1": "%s",
						"a2": "%s",
						"a3": "%s"
					}
				})"), *DateSTR, *DateSTR, *DateSTR);

				FTest Test;
				Test.BeamDeserialize(JsonInput);

				TestEqual("Optional was deserialized with correct value at idx 0", Test.a.Val.FindChecked("a1"), Now);
				TestEqual("Optional was deserialized with correct value at idx 1", Test.a.Val.FindChecked("a2"), Now);
				TestEqual("Optional was deserialized with correct value at idx 2", Test.a.Val.FindChecked("a3"), Now);
				TestTrue("Optional was deserialized with IsSet == true", Test.a.IsSet);
			}
			// Test deserialize optional TArray<FBeamSemanticType>
			{
				struct FOptionalMapOfBeamCid : FBeamOptional
				{
					TMap<FString, FBeamCid> Val;

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TMap<FString, FBeamCid>*>(Data);
						IsSet = true;
					}
				};

				struct FTest : FBeamJsonSerializableUStruct
				{
					FOptionalMapOfBeamCid a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeOptional<TMap<FString, FBeamCid>, FBeamCid, int64>("a", Bag, a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					TEXT(R"({
					"a": {
						"a1": 1,
						"a2": 2,
						"a3": 3
					}
				})");

				FTest Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct value at idx 0", Test.a.Val.FindChecked("a1").AsLong == 1);
				TestTrue("Optional was deserialized with correct value at idx 1", Test.a.Val.FindChecked("a2").AsLong == 2);
				TestTrue("Optional was deserialized with correct value at idx 2", Test.a.Val.FindChecked("a3").AsLong == 3);
				TestTrue("Optional was deserialized with IsSet == true", Test.a.IsSet);
			}

			// Test deserialize optional TArray<FBeamJsonSerializable>
			{
				struct FTestData : FBeamJsonSerializableUStruct
				{
					int a;
					FString b;

					FTestData() : a(0), b(TEXT(""))
					{
					}

					FTestData(int A, const FString& B)
						: a(A),
						  b(B)
					{
					}

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						a = Bag->GetIntegerField(TEXT("a"));
						b = Bag->GetStringField(TEXT("b"));
					}
				};

				struct FTestOptional : FBeamOptional
				{
					TMap<FString, FTestData> Val;

					FTestOptional()
					{
						IsSet = false;
					}

					virtual const void* GetAddr() const override { return &Val; }

					virtual void Set(const void* Data) override
					{
						Val = *static_cast<const TMap<FString, FTestData>*>(Data);
						IsSet = true;
					}
				};

				struct FTest : FBeamJsonSerializableUStruct
				{
					FTestOptional a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeOptional<TMap<FString, FTestData>, FTestData>("a", Bag, a);
					}
				};

				// The json we are deserializing
				const FString JsonInput =
					TEXT(R"({
					"a": {
						"a1":{
							"a" : 1,
							"b" : "Test1"
						},
						"a2": {
							"a" : -1,
							"b" : "Test2"
						}
					}
				})");

				FTest Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct integer value", Test.a.Val.FindChecked("a1").a == 1);
				TestTrue("Optional was deserialized with correct string value", Test.a.Val.FindChecked("a1").b == TEXT("Test1"));

				TestTrue("Optional was deserialized with correct integer value", Test.a.Val.FindChecked("a2").a == -1);
				TestTrue("Optional was deserialized with correct string value", Test.a.Val.FindChecked("a2").b == TEXT("Test2"));

				TestTrue("Optional was deserialized with IsSet == true", Test.a.IsSet);
			}
		});

		It("should deserialize a JSON Array as an FBeamArrayOf____ (primitives & semantic types)", [this]()
		{
			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"([0, 1, -1])");

			FBeamArrayOfInt Test;
			Test.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized with correct value at idx 0", Test.Values[0] == 0);
			TestTrue("Optional was deserialized with correct value at idx 1", Test.Values[1] == 1);
			TestTrue("Optional was deserialized with correct value at idx 2", Test.Values[2] == -1);

			FBeamArrayOfBeamCid Test2;
			Test2.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized with correct value at idx 0", Test2.Values[0].AsLong == 0);
			TestTrue("Optional was deserialized with correct value at idx 1", Test2.Values[1].AsLong == 1);
			TestTrue("Optional was deserialized with correct value at idx 2", Test2.Values[2].AsLong == -1);
		});

		It("should deserialize a JSON Array as an FBeamArrayOf____ (nested primitives & semantic types)", [this]()
		{
			{
				struct FBeamArrayOfString : public FBeamArray
				{
					TArray<FString> Values;

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeArray<FString>(Values, Serializer);
					}

					virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeArray<FString>(Values, Serializer);
					}

					virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
					{
						UBeamJsonUtils::DeserializeArray<FString>(Elements, Values);
					}
				};

				struct FBeamArrayOfArrayOfString : public FBeamArray
				{
					TArray<FBeamArrayOfString> Values;

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeArray<FBeamArrayOfString>(Values, Serializer);
					}

					virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeArray<FBeamArrayOfString>(Values, Serializer);
					}

					virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
					{
						UBeamJsonUtils::DeserializeArray<FBeamArrayOfString>(Elements, Values);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					TEXT(R"([["1"], ["2", "2"], ["3", "3", "3"]])");

				FBeamArrayOfArrayOfString Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct value at idx 0", Test.Values[0].Values[0] == TEXT("1"));
				TestTrue("Optional was deserialized with correct value at idx 1", Test.Values[1].Values[1] == TEXT("2"));
				TestTrue("Optional was deserialized with correct value at idx 2", Test.Values[2].Values[2] == TEXT("3"));
			}

			{
				struct FBeamArrayOfArrayOfBeamCid : public FBeamArray
				{
					TArray<FBeamArrayOfBeamCid> Values;

					virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
					{
						UBeamJsonUtils::DeserializeArray<FBeamArrayOfBeamCid>(Elements, Values);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					TEXT(R"([["1"], ["2", "2"], ["3", "3", "3"]])");

				FBeamArrayOfArrayOfBeamCid Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct value at idx 0", Test.Values[0].Values[0].AsString.Equals(TEXT("1")));
				TestTrue("Optional was deserialized with correct value at idx 1", Test.Values[1].Values[1].AsString.Equals(TEXT("2")));
				TestTrue("Optional was deserialized with correct value at idx 2", Test.Values[2].Values[2].AsString.Equals(TEXT("3")));
			}
		});

		It("should deserialize a JSON Object as an FBeamMapOf____ (primitives & semantic types)", [this]()
		{
			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"({ "a1" : 0, "a2": 1, "a3": -1})");

			FBeamMapOfInt Test;
			Test.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized with correct value at idx 0", Test.Values.FindChecked("a1") == 0);
			TestTrue("Optional was deserialized with correct value at idx 1", Test.Values.FindChecked("a2") == 1);
			TestTrue("Optional was deserialized with correct value at idx 2", Test.Values.FindChecked("a3") == -1);

			FBeamMapOfBeamCid Test2;
			Test2.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized with correct value at idx 0", Test2.Values.FindChecked("a1").AsLong == 0);
			TestTrue("Optional was deserialized with correct value at idx 1", Test2.Values.FindChecked("a2").AsLong == 1);
			TestTrue("Optional was deserialized with correct value at idx 2", Test2.Values.FindChecked("a3").AsLong == -1);
		});

		It("should deserialize a JSON Object as an FBeamMapOf____ (nested primitives & semantic types)", [this]()
		{
			{
				struct FBeamMapOfString : public FBeamMap
				{
					TMap<FString, FString> Values;

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FString>(Values, Serializer);
					}

					virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FString>(Values, Serializer);
					}

					virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override
					{
						UBeamJsonUtils::DeserializeMap<FString>(Elements, Values);
					}
				};

				struct FBeamMapOfMapOfString : public FBeamMap
				{
					TMap<FString, FBeamMapOfString> Values;

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FBeamMapOfString>(Values, Serializer);
					}

					virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FBeamMapOfString>(Values, Serializer);
					}

					virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override
					{
						UBeamJsonUtils::DeserializeMap<FBeamMapOfString>(Elements, Values);
					}
				};


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					TEXT(R"({
						"a1" : { "a": "0" },
						"a2": { "a": "1" },
						"a3": { "a": "-1" }
					})");

				FBeamMapOfMapOfString Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct value at idx 0", Test.Values.FindChecked("a1").Values.FindChecked("a") == TEXT("0"));
				TestTrue("Optional was deserialized with correct value at idx 1", Test.Values.FindChecked("a2").Values.FindChecked("a") == TEXT("1"));
				TestTrue("Optional was deserialized with correct value at idx 2", Test.Values.FindChecked("a3").Values.FindChecked("a") == TEXT("-1"));
			}

			{
				struct FBeamMapOfMapOfBeamCid : public FBeamMap
				{
					TMap<FString, FBeamMapOfBeamCid> Values;

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FBeamMapOfBeamCid>(Values, Serializer);
					}

					virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FBeamMapOfBeamCid>(Values, Serializer);
					}

					virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override
					{
						UBeamJsonUtils::DeserializeMap<FBeamMapOfBeamCid>(Elements, Values);
					}
				};


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonInput =
					TEXT(R"({
						"a1" : { "a": "0" },
						"a2": { "a": "1" },
						"a3": { "a": "2" }
					})");

				FBeamMapOfMapOfBeamCid Test;
				Test.BeamDeserialize(JsonInput);

				TestTrue("Optional was deserialized with correct value at idx 0", Test.Values.FindChecked("a1").Values.FindChecked("a").AsString.Equals(TEXT("0")));
				TestTrue("Optional was deserialized with correct value at idx 1", Test.Values.FindChecked("a2").Values.FindChecked("a").AsString.Equals(TEXT("1")));
				TestTrue("Optional was deserialized with correct value at idx 2", Test.Values.FindChecked("a3").Values.FindChecked("a").AsString.Equals(TEXT("2")));
			}
		});

		It("should deserialize a JSON Array as an TArray<> of primitives or semantic types", [this]()
		{
			struct FTest : FBeamJsonSerializableUStruct
			{
				TArray<int> a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeArray<int>(Bag->GetArrayField(TEXT("a")), a);
				}
			};

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonString =
				TEXT(R"({
					"a": [ 1, -1, 0 ]
				})");
			FTest TestOut;
			TestOut.BeamDeserialize(JsonString);

			TestTrue("Deserialized idx 0 of Int-Array correctly", TestOut.a[0] == 1);
			TestTrue("Deserialized idx 1 of Int-Array correctly", TestOut.a[1] == -1);
			TestTrue("Deserialized idx 2 of Int-Array correctly", TestOut.a[2] == 0);

			struct FTestBeamCid : FBeamJsonSerializableUStruct
			{
				TArray<FBeamCid> a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeArray<FBeamCid, int64>(Bag->GetArrayField(TEXT("a")), a);
				}
			};

			FTestBeamCid TestOut2;
			TestOut2.BeamDeserialize(JsonString);

			TestTrue("Deserialized idx 0 of Int-Array correctly", TestOut2.a[0].AsLong == 1);
			TestTrue("Deserialized idx 1 of Int-Array correctly", TestOut2.a[1].AsLong == -1);
			TestTrue("Deserialized idx 2 of Int-Array correctly", TestOut2.a[2].AsLong == 0);
		});

		It("should deserialize a JSON Array as an TArray<> of FBeamJsonSerializable", [this]()
		{
			struct FTestData : FBeamJsonSerializableUStruct
			{
				int a;
				FString b;

				FTestData() = default;

				FTestData(int A, const FString& B)
					: a(A),
					  b(B)
				{
				}

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					a = Bag->GetIntegerField(TEXT("a"));
					b = Bag->GetStringField(TEXT("b"));
				}
			};

			struct FTest : FBeamJsonSerializableUStruct
			{
				TArray<FTestData> a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeArray<FTestData>(Bag->GetArrayField(TEXT("a")), a);
				}
			};

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonString =
				TEXT(R"({
					"a": [{
							"a" : 1,
							"b" : "Test"
						},{
							"a" : 2,
							"b" : "Test"
						}]
				})");
			FTest TestOut;
			TestOut.BeamDeserialize(JsonString);

			TestTrue("Deserialized idx 0 of Array correctly", TestOut.a[0].a == 1);
			TestTrue("Deserialized idx 0 of Array correctly", TestOut.a[0].b == TEXT("Test"));
			TestTrue("Deserialized idx 1 of Array correctly", TestOut.a[1].a == 2);
			TestTrue("Deserialized idx 1 of Array correctly", TestOut.a[1].b == TEXT("Test"));
		});

		It("should deserialize a JSON Array as an TArray<> of FBeamArrayOf____", [this]()
		{
			// Test with wrapped array of primitives
			{
				struct FBeamArrayOfInt : public FBeamArray
				{
					TArray<int> Values;

					virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
					{
						UBeamJsonUtils::DeserializeArray<int>(Elements, Values);
					}
				};


				struct FTest : FBeamJsonSerializableUStruct
				{
					TArray<FBeamArrayOfInt> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeArray<FBeamArrayOfInt>(Bag->GetArrayField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": [[1], [2]]
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized idx 0 of Array correctly", TestOut.a[0].Values[0] == 1);
				TestTrue("Deserialized idx 1 of Array correctly", TestOut.a[1].Values[0] == 2);
			}

			// Test with wrapped array of semantic types
			{
				struct FTest : FBeamJsonSerializableUStruct
				{
					TArray<FBeamArrayOfBeamCid> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeArray<FBeamArrayOfBeamCid>(Bag->GetArrayField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": [[1], [2]]
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized idx 0 of Array correctly", TestOut.a[0].Values[0].AsLong == 1);
				TestTrue("Deserialized idx 1 of Array correctly", TestOut.a[1].Values[0].AsLong == 2);
			}

			// Test with wrapped array of non-primitives
			{
				struct FTestData : public FBeamJsonSerializableUStruct
				{
					int a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						a = Bag->GetIntegerField(TEXT("a"));
					}
				};

				struct FBeamArrayOfTestData : public FBeamArray
				{
					TArray<FTestData> Values;

					virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
					{
						UBeamJsonUtils::DeserializeArray<FTestData>(Elements, Values);
					}
				};


				struct FTest : FBeamJsonSerializableUStruct
				{
					TArray<FBeamArrayOfTestData> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeArray<FBeamArrayOfTestData>(Bag->GetArrayField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": [
							[{
								"a": 1
							}],
							[{
								"a": 2
							}]
						]
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized idx 0 of Array correctly", TestOut.a[0].Values[0].a == 1);
				TestTrue("Deserialized idx 1 of Array correctly", TestOut.a[1].Values[0].a == 2);
			}
		});

		It("should deserialize a JSON Array as an TArray<> of FBeamMapOf____", [this]()
		{
			// Test with wrapped array of primitives
			{
				struct FTest : FBeamJsonSerializableUStruct
				{
					TArray<FBeamMapOfInt> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeArray<FBeamMapOfInt>(Bag->GetArrayField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": [{"a1": 1}, {"a2": 2}]
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized idx 0 of Array correctly", TestOut.a[0].Values.FindChecked("a1") == 1);
				TestTrue("Deserialized idx 1 of Array correctly", TestOut.a[1].Values.FindChecked("a2") == 2);
			}

			// Test with wrapped array of semantic types
			{
				struct FTest : FBeamJsonSerializableUStruct
				{
					TArray<FBeamMapOfBeamCid> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeArray<FBeamMapOfBeamCid>(Bag->GetArrayField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": [{"a1": 1}, {"a2": 2}]
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized idx 0 of Array correctly", TestOut.a[0].Values.FindChecked("a1").AsLong == 1);
				TestTrue("Deserialized idx 1 of Array correctly", TestOut.a[1].Values.FindChecked("a2").AsLong == 2);
			}

			// Test with wrapped array of non-primitives
			{
				struct FTestData : public FBeamJsonSerializableUStruct
				{
					int a;

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						Serializer->WriteValue("a", a);
					}

					virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
					{
						Serializer->WriteValue("a", a);
					}

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						a = Bag->GetIntegerField(TEXT("a"));
					}
				};

				struct FBeamMapOfTestData : public FBeamMap
				{
					TMap<FString, FTestData> Values;

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FTestData>(Values, Serializer);
					}

					virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FTestData>(Values, Serializer);
					}

					virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override
					{
						UBeamJsonUtils::DeserializeMap<FTestData>(Elements, Values);
					}
				};


				struct FTest : FBeamJsonSerializableUStruct
				{
					TArray<FBeamMapOfTestData> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeArray<FBeamMapOfTestData>(Bag->GetArrayField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": [
							{
								"a1":
								{
									"a": 1
								}
							},
							{
								"a2":
								{
									"a": 2
								}
							}						
						]
					})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized idx 0 of Array correctly", TestOut.a[0].Values.FindChecked("a1").a == 1);
				TestTrue("Deserialized idx 1 of Array correctly", TestOut.a[1].Values.FindChecked("a2").a == 2);
			}
		});

		It("should deserialize a JSON Object as an TMap<FString,> of primitives or semantic types", [this]()
		{
			struct FTest : FBeamJsonSerializableUStruct
			{
				TMap<FString, int> a;
				TMap<FString, FString> b;
				TMap<FString, FBeamCid> c;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					UBeamJsonUtils::DeserializeMap<int>(Bag->GetObjectField(TEXT("a")), a);
					UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("b")), b);
					UBeamJsonUtils::DeserializeMap<FBeamCid, int64>(Bag->GetObjectField(TEXT("c")), c);
				}
			};

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonString =
				TEXT(R"({
					"a": 
					{
						"a1": 0,
						"a2": -1,
						"a3": 1
					},
					"b": {
						"a1": "b1",
						"a2": "b2",
						"a3": "b3"
					},
					"c": {
						"a1": 0,
						"a2": -1,
						"a3": 1
					}
				})");
			FTest TestOut;
			TestOut.BeamDeserialize(JsonString);

			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a1") == 0);
			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a2") == -1);
			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a3") == 1);
			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.b.FindRef("a1") == TEXT("b1"));
			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.b.FindRef("a2") == TEXT("b2"));
			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.b.FindRef("a3") == TEXT("b3"));
			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.c.FindRef("a1").AsLong == 0);
			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.c.FindRef("a2").AsLong == -1);
			TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.c.FindRef("a3").AsLong == 1);
		});

		It("should deserialize a JSON Object as an TMap<FString,> of FBeamArrayOf____", [this]()
		{
			// Test primitives
			{
				struct FTest : FBeamJsonSerializableUStruct
				{
					TMap<FString, FBeamArrayOfInt> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeMap<FBeamArrayOfInt>(Bag->GetObjectField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": 
					{
						"a1": [0],
						"a2": [-1],
						"a3": [1]
					}
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a1").Values[0] == 0);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a2").Values[0] == -1);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a3").Values[0] == 1);
			}

			// Test semantic types
			{
				struct FTest : FBeamJsonSerializableUStruct
				{
					TMap<FString, FBeamArrayOfBeamCid> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeMap<FBeamArrayOfBeamCid>(Bag->GetObjectField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": 
					{
						"a1": [0],
						"a2": [-1],
						"a3": [1]
					}
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a1").Values[0].AsLong == 0);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a2").Values[0].AsLong == -1);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a3").Values[0].AsLong == 1);
			}

			// Test with non-primitives
			{
				struct FBeamArrayOfTestData : public FBeamArray
				{
					TArray<FTestInt> Values;

					virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override
					{
						UBeamJsonUtils::DeserializeArray<FTestInt>(Elements, Values);
					}
				};

				struct FTest : public FBeamJsonSerializableUStruct
				{
					TMap<FString, FBeamArrayOfTestData> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeMap<FBeamArrayOfTestData>(Bag->GetObjectField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": 
					{
						"a1": [{
							"a": 0
						}],
						"a2": [{
							"a": -1
						}],
						"a3": [{
							"a": 1
						}]
					}
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a1").Values[0].a == 0);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a2").Values[0].a == -1);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a3").Values[0].a == 1);
			}
		});

		It("should deserialize a JSON Object as an TMap<FString,> of FBeamMapOf____", [this]()
		{
			// Test primitives
			{
				struct FTestMapOfInt : FBeamJsonSerializableUStruct
				{
					TMap<FString, FBeamMapOfInt> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeMap<FBeamMapOfInt>(Bag->GetObjectField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": 
					{
						"a1": { "a" : 0 },
						"a2": { "a" : -1 },
						"a3": { "a" : 1 }
					}
				})");
				FTestMapOfInt TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a1").Values.FindChecked("a") == 0);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a2").Values.FindChecked("a") == -1);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a3").Values.FindChecked("a") == 1);
			}

			// Test semantic types
			{
				struct FTestMapOfInt : FBeamJsonSerializableUStruct
				{
					TMap<FString, FBeamMapOfBeamCid> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeMap<FBeamMapOfBeamCid>(Bag->GetObjectField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": 
					{
						"a1": { "a" : 0 },
						"a2": { "a" : -1 },
						"a3": { "a" : 1 }
					}
				})");
				FTestMapOfInt TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a1").Values.FindChecked("a").AsLong == 0);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a2").Values.FindChecked("a").AsLong == -1);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a3").Values.FindChecked("a").AsLong == 1);
			}

			// Test with non-primitives
			{
				struct FBeamMapOfTestInt : public FBeamMap
				{
					TMap<FString, FTestInt> Values;

					virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FTestInt>(Values, Serializer);
					}

					virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
					{
						UBeamJsonUtils::SerializeMap<FTestInt>(Values, Serializer);
					}

					virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override
					{
						UBeamJsonUtils::DeserializeMap<FTestInt>(Elements, Values);
					}
				};

				struct FTestMapOfTestInt : public FBeamJsonSerializableUStruct
				{
					TMap<FString, FBeamMapOfTestInt> a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeMap<FBeamMapOfTestInt>(Bag->GetObjectField(TEXT("a")), a);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": 
					{
						"a1": {
							"a":
							{
								"a": 0
							}
						},
						"a2": {
							"a":
							{
								"a": -1
							}
						},
						"a3": {
							"a":
							{
								"a": 1
							}
						}
					}
				})");
				FTestMapOfTestInt TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindChecked("a1").Values.FindChecked("a").a == 0);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindChecked("a2").Values.FindChecked("a").a == -1);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindChecked("a3").Values.FindChecked("a").a == 1);
			}
		});

		It("should deserialize a JSON Object as an TMap<FString,> of FBeamJsonSerializable", [this]()
		{
			// Test with non-primitives
			{
				struct FTestData : FBeamJsonSerializableUStruct
				{
					int a;
					FString b;
					TArray<int> c;

					FTestData() = default;

					FTestData(int A, const FString& B)
						: a(A),
						  b(B)
					{
					}

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						a = Bag->GetIntegerField(TEXT("a"));
						b = Bag->GetStringField(TEXT("b"));
						UBeamJsonUtils::DeserializeArray<int>(Bag->GetArrayField(TEXT("c")), c);
					}
				};

				struct FTest : FBeamJsonSerializableUStruct
				{
					TMap<FString, int> a;
					TMap<FString, FString> b;
					TMap<FString, FTestData> c;
					TMap<FString, FBeamCid> d;


					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						UBeamJsonUtils::DeserializeMap<int>(Bag->GetObjectField(TEXT("a")), a);
						UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("b")), b);
						UBeamJsonUtils::DeserializeMap<FTestData>(Bag->GetObjectField(TEXT("c")), c);
						UBeamJsonUtils::DeserializeMap<FBeamCid, int64>(Bag->GetObjectField(TEXT("d")), d);
					}
				};

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString JsonString =
					TEXT(R"({
					"a": 
					{
						"a1": 0,
						"a2": -1,
						"a3": 1
					},
					"b": {
						"a1": "b1",
						"a2": "b2",
						"a3": "b3"
					},
					"c": {
						"obj":{
							"a": 0,
							"b": "Test",
							"c": [0, 1]
						}
					},
					"d": 
					{
						"a1": 0,
						"a2": -1,
						"a3": 1
					}	
				})");
				FTest TestOut;
				TestOut.BeamDeserialize(JsonString);

				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a1") == 0);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a2") == -1);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.a.FindRef("a3") == 1);

				TestTrue("Deserialized TMap<FString, FString> map correctly", TestOut.b.FindRef("a1") == TEXT("b1"));
				TestTrue("Deserialized TMap<FString, FString> map correctly", TestOut.b.FindRef("a2") == TEXT("b2"));
				TestTrue("Deserialized TMap<FString, FString> map correctly", TestOut.b.FindRef("a3") == TEXT("b3"));

				TestTrue("Deserialized TMap<FString, FBeamJsonSerializable> map correctly", TestOut.c.FindRef("obj").a == 0);
				TestTrue("Deserialized TMap<FString, FBeamJsonSerializable> map correctly", TestOut.c.FindRef("obj").b == TEXT("Test"));
				TestTrue("Deserialized TMap<FString, FBeamJsonSerializable> map correctly", TestOut.c.FindRef("obj").c[0] == 0);
				TestTrue("Deserialized TMap<FString, FBeamJsonSerializable> map correctly", TestOut.c.FindRef("obj").c[1] == 1);

				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.d.FindRef("a1").AsLong == 0);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.d.FindRef("a2").AsLong == -1);
				TestTrue("Deserialized TMap<FString, int> map correctly", TestOut.d.FindRef("a3").AsLong == 1);
			}
		});

		It("should deserialize a JSON Object containing an arbitrary Json-blob (FJsonObject) in it ", [this]()
		{
			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput = TEXT(R"({"blob":{"arbitraryBool":true,"arbitraryString":"string","arbitraryNumber":1}})");

			FBeamJsonBlob Test{};
			Test.BeamDeserialize(JsonInput);

			TestTrue("Struct Properties were deserialized correctly", Test.Blob->GetBoolField(TEXT("arbitraryBool")) == true);
			TestTrue("Struct Properties were deserialized correctly", Test.Blob->GetStringField(TEXT("arbitraryString")) == FString(TEXT("string")));
			TestTrue("Struct Properties were deserialized correctly", Test.Blob->GetNumberField(TEXT("arbitraryNumber")) == 1);
		});
	});
}
