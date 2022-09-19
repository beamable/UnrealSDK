#include "Misc/AutomationTest.h"
#include "BeamJsonUtils.h"


BEGIN_DEFINE_SPEC(FBeamJsonUtilsSpec, "BeamableUnreal.BeamJsonUtils", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
END_DEFINE_SPEC(FBeamJsonUtilsSpec)

void FBeamJsonUtilsSpec::Define()
{
	Describe("FBeamJsonUtils - Serialization", [this]()
	{
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
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);
			JsonSerializer->WriteObjectStart();
			FBeamJsonUtils::SerializeOptional<int>(TEXT("a"), &OptionalInt, JsonSerializer);
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
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);
			JsonSerializer->WriteObjectStart();
			FBeamJsonUtils::SerializeOptional<int>(TEXT("a"), &OptionalInt, JsonSerializer);
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

		It("should output a regular JSON Field (Optional FBeamJsonSerializable with Value)", [this]()
		{
			struct FTest : FBeamJsonSerializable
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
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);
			JsonSerializer->WriteObjectStart();
			FBeamJsonUtils::SerializeOptional<FTest>(TEXT("a1"), &OptionalTest, JsonSerializer);
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
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);
				JsonSerializer->WriteObjectStart();
				FBeamJsonUtils::SerializeOptional<TArray<int>, int>(TEXT("a"), &OptionalInt, JsonSerializer);
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

			// Test array with BeamJsonSerializable
			{
				struct FTest : FBeamJsonSerializable
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
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);
				JsonSerializer->WriteObjectStart();
				FBeamJsonUtils::SerializeOptional<TArray<FTest>, FTest>(TEXT("a1"), &OptionalTest, JsonSerializer);
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
		});

		It("should output a serialized JSON Array of primitives", [this]()
		{
			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);

			TArray<int> a;
			a.Add(1);
			a.Add(-1);
			a.Add(0);
			JsonSerializer->WriteObjectStart();
			FBeamJsonUtils::SerializeArray<int>(TEXT("a"), a, JsonSerializer);
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

		It("should output a serialized JSON Array of FBeamJsonSerializable", [this]()
		{
			struct FTest : FBeamJsonSerializable
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
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);

			TArray<FTest> array;
			array.Add(FTest{0, TEXT("b1")});
			array.Add(FTest{1, TEXT("b2")});
			JsonSerializer->WriteObjectStart();
			FBeamJsonUtils::SerializeArray<FTest>(TEXT("array"), array, JsonSerializer);
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
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);

				TMap<FString, int> map;
				map.Add("a1", 0);
				map.Add("a2", -1);
				map.Add("a3", 1);
				JsonSerializer->WriteObjectStart();
				FBeamJsonUtils::SerializeMap<int>(TEXT("map"), map, JsonSerializer);
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
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);

				TMap<FString, FString> map;
				map.Add("a1", "b1");
				map.Add("a2", "b2");
				map.Add("a3", "b3");
				JsonSerializer->WriteObjectStart();
				FBeamJsonUtils::SerializeMap<FString>(TEXT("map"), map, JsonSerializer);
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
		});

		It("should output a serialized JSON Map of FBeamJsonSerializable", [this]()
		{
			struct FTest : FBeamJsonSerializable
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
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);

			TMap<FString, FTest> Map;
			Map.Add("a1", FTest{0, TEXT("b1")});
			Map.Add("a2", FTest{1, TEXT("b2")});
			JsonSerializer->WriteObjectStart();
			FBeamJsonUtils::SerializeMap<FTest>(TEXT("map"), Map, JsonSerializer);
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
			struct FTest : FBeamJsonSerializable
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
					FBeamJsonUtils::SerializeArray<int>(TEXT("c"), c, Serializer);
				}
			};

			FString OutJson;
			TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);

			TArray<int> c1, c2;
			c1.Add(1);
			c1.Add(2);
			c2.Add(-1);
			c2.Add(-2);

			TMap<FString, FTest> Map;
			Map.Add("a1", FTest{0, TEXT("b1"), c1});
			Map.Add("a2", FTest{1, TEXT("b2"), c2});
			JsonSerializer->WriteObjectStart();
			FBeamJsonUtils::SerializeMap<FTest>(TEXT("map"), Map, JsonSerializer);
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

		It("should output a serialized JSON Map of TArray<T>", [this]()
		{
			{
				FString OutJson;
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);

				TMap<FString, TArray<int>> Map;
				Map.Add("a1", TArray<int>{0, 1});
				Map.Add("a2", TArray<int>{0, -1});
				JsonSerializer->WriteObjectStart();
				FBeamJsonUtils::SerializeMap<TArray<int>, int>(TEXT("map"), Map, JsonSerializer);
				JsonSerializer->WriteObjectEnd();
				JsonSerializer->Close();


				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": {
						"a1": [ 0, 1 ],
						"a2": [ 0, -1 ]
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, TArray<T>>, where T = primitive, Serialized Correctly", OutJson, Expected);
			}
			{
				struct FTest : public FBeamJsonSerializable
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
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&OutJson);

				// TMap<FString, TArray<FTest>> Map;
				// Map.Add("a", TArray<FTest>{FTest{0, TEXT("a1")}, FTest{1, TEXT("a2")}});
				// Map.Add("b", TArray<FTest>{FTest{0, TEXT("b1")}, FTest{1, TEXT("b2")}});
				// JsonSerializer->WriteObjectStart();
				// FBeamJsonUtils::SerializeMap<TArray<FTest>, FTest>(TEXT("map"), Map, JsonSerializer);
				// JsonSerializer->WriteObjectEnd();
				// JsonSerializer->Close();

				// Get a condensed string so we can easily compare with the condensed string we generate.
				const FString ExpectedTemp =
					TEXT(R"({
					"map": {
						"a": [{
							"a" : 0,
							"b": "a1"
						},
						{
							"a" : 1,
							"b": "a2"
						}],
						"b":[{
							"a": 0,
							"b": "b1"
						},
						{
							"a": 1,
							"b": "b2"
						}]
					}
				})");
				FJsonDataBag ExpectedBag;
				ExpectedBag.FromJson(ExpectedTemp);
				const FString Expected = ExpectedBag.ToJson(false);

				TestEqual("TMap<FString, TArray<T>>, where T = FBeamJsonSerializable, Serialized Correctly", OutJson, Expected);
			}
		});
	});


	Describe("FBeamJsonUtils - Deserialization", [this]()
	{
		It("should deserialize a blank JSON Object as an Optional Primitive without Set Value", [this]()
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

			struct FTest : FBeamJsonSerializable
			{
				FTestOptionalInt a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					FBeamJsonUtils::DeserializeOptional<int>("a", Bag, a);
				}
			};

			// Get a condensed string so we can easily compare with the condensed string we generate.
			const FString JsonInput =
				TEXT(R"({ })");

			FTest Test;
			Test.BeamDeserialize(JsonInput);

			TestTrue("Optional was deserialized as default value", Test.a.Val == 0);
			TestFalse("Optional was deserialized with IsSet == false", Test.a.IsSet);
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

			struct FTest : FBeamJsonSerializable
			{
				FTestOptionalInt a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					FBeamJsonUtils::DeserializeOptional<int>("a", Bag, a);
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
		});

		It("should deserialize a JSON Object as an Optional FBeamJsonSerializable with Set Value", [this]()
		{
			struct FTestData : FBeamJsonSerializable
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
					a = Bag->GetIntegerField("a");
					b = Bag->GetStringField("b");
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

			struct FTest : FBeamJsonSerializable
			{
				FTestOptional a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					FBeamJsonUtils::DeserializeOptional<FTestData>("a", Bag, a);
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

				struct FTest : FBeamJsonSerializable
				{
					FOptionalArrayInt a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						FBeamJsonUtils::DeserializeOptional<TArray<int>, int>("a", Bag, a);
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

			// Test deserialize optional TArray<FBeamJsonSerializable>
			{
				struct FTestData : FBeamJsonSerializable
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
						a = Bag->GetIntegerField("a");
						b = Bag->GetStringField("b");
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

				struct FTest : FBeamJsonSerializable
				{
					FTestOptional a;

					virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
					{
						FBeamJsonUtils::DeserializeOptional<TArray<FTestData>, FTestData>("a", Bag, a);
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

		It("should deserialize a JSON Array as an TArray<> of primitives", [this]()
		{
			struct FTest : FBeamJsonSerializable
			{
				TArray<int> a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					FBeamJsonUtils::DeserializeArray<int>(Bag->GetArrayField(TEXT("a")), a);
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
		});

		It("should deserialize a JSON Array as an TArray<> of FBeamJsonSerializable", [this]()
		{
			struct FTestData : FBeamJsonSerializable
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
					a = Bag->GetIntegerField("a");
					b = Bag->GetStringField("b");
				}
			};

			struct FTest : FBeamJsonSerializable
			{
				TArray<FTestData> a;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					FBeamJsonUtils::DeserializeArray<FTestData>(Bag->GetArrayField(TEXT("a")), a);
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

		It("should deserialize a JSON Array as an TMap<FString,> of primitives", [this]()
		{
			struct FTest : FBeamJsonSerializable
			{
				TMap<FString, int> a;
				TMap<FString, FString> b;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					FBeamJsonUtils::DeserializeMap<int>(Bag->GetObjectField(TEXT("a")), a);
					FBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("b")), b);
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
		});

		It("should deserialize a JSON Array as an TMap<FString,> of FBeamJsonSerializable", [this]()
		{
			struct FTestData : FBeamJsonSerializable
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
					FBeamJsonUtils::DeserializeArray<int>(Bag->GetArrayField(TEXT("c")), c);
				}
			};

			struct FTest : FBeamJsonSerializable
			{
				TMap<FString, int> a;
				TMap<FString, FString> b;
				TMap<FString, FTestData> c;
				TMap<FString, TArray<int>> d;

				virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
				{
					FBeamJsonUtils::DeserializeMap<int>(Bag->GetObjectField(TEXT("a")), a);
					FBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("b")), b);
					FBeamJsonUtils::DeserializeMap<FTestData>(Bag->GetObjectField(TEXT("c")), c);
					FBeamJsonUtils::DeserializeMap<TArray<int>, int>(Bag->GetObjectField(TEXT("d")), d);
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
					"d": {
						"array" : [0, 1],
						"array2" : [0, -1]	
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

			TestTrue("Deserialized TMap<FString, TArray<>> map correctly", TestOut.d.FindRef("array")[0] == 0);
			TestTrue("Deserialized TMap<FString, TArray<>> map correctly", TestOut.d.FindRef("array")[1] == 1);
			TestTrue("Deserialized TMap<FString, TArray<>> map correctly", TestOut.d.FindRef("array2")[0] == 0);
			TestTrue("Deserialized TMap<FString, TArray<>> map correctly", TestOut.d.FindRef("array2")[1] == -1);
		});
	});
}
