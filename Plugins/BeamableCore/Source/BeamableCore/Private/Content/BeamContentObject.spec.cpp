#include "BeamContentObject.spec.h"

#include "GameplayTagsManager.h"
#include "Content/MockBeamContentObject.h"
#include "Misc/AutomationTest.h"


// We register these tags here to ensure they always exists so that we can Unit-Test our serialization/deserialization code against them.
struct FMockBeamContentObjectGameplayTags final : FGameplayTagNativeAdder
{
	FMockBeamContentObjectGameplayTags() = default;

	virtual ~FMockBeamContentObjectGameplayTags()
	{
	}

	FGameplayTag TestTag1;
	FGameplayTag TestTag2;

	virtual void AddTags() override
	{
		UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		TestTag1 = Manager.AddNativeGameplayTag(TEXT("BeamableCore.Test.MockGameplayTag"));
		TestTag2 = Manager.AddNativeGameplayTag(TEXT("BeamableCore.Test.MockGameplayTag2"));
	}


	FORCEINLINE static const FGameplayTagNativeAdder& Get()
	{
		return StaticInstance;
	}

	static FMockBeamContentObjectGameplayTags StaticInstance;
};

FMockBeamContentObjectGameplayTags FMockBeamContentObjectGameplayTags::StaticInstance;

void FBeamContentObjectSpec::Define()
{
	FString TestId = TEXT("mockcontentobject.content1");
	FString TestLinkId = TEXT("mockcontentobject.content2");
	FString TestVersion = TEXT("1");
	FString TestBeamCid = TEXT("111111111");
	FString TestStringText = TEXT("I'm a String Text");
	FString TestTableId = TEXT("/BeamableCore/Tests/BEAM_TEST_TABLE.BEAM_TEST_TABLE");
	FString TestTableKey = TEXT("BEAM_TEST_KEY");
	FString TestTableText = TEXT("BEAM_ST₢") + TestTableId + TEXT("₢") + TestTableKey;
	FString TestValueA = TEXT("1");
	FString TestValueB = TEXT("2");
	FString TestSoftObjPath = TEXT("/BeamableCore/Editor/Icons/BeamLogo.BeamLogo");
	FString TestVectorObj = TEXT("{ \"x\": 1.0, \"y\": 1.0, \"z\": 1.0 }");
	FString TestIntVectorObj = TEXT("{ \"x\": 1, \"y\": 1, \"z\": 1 }");
	FString TestColorObj = TEXT("{ \"a\": 255, \"b\": 0, \"g\": 0, \"r\": 0 }");
	FString TestLinearColorObj = TEXT("{ \"a\": 1, \"b\": 0, \"g\": 0, \"r\": 0 }");
	int32 TestValueAInt = 1;
	int32 TestValueBInt = 2;
	FString TestGameplayTagA = TEXT("BeamableCore.Test.MockGameplayTag");
	FString TestGameplayTagB = TEXT("BeamableCore.Test.MockGameplayTag2");

	FString TestUnrealClassA = TEXT("/Script/AlembicLibrary.AbcImportSettings");
	FString TestUnrealClassB = TEXT("/Script/AlembicLibrary.AbcAssetImportData");

	FString FullObject = TEXT(R"({
  "id": "₢Id₢",
  "version": "₢Version₢",
  "properties": {
    "Value": {
      "data": ₢ValueA₢
    },
    "BeamCid": {
      "data": "₢BeamCid₢"
    },
	"StringText": {
      "data": "₢StringText₢"
	},
	"StringTextArray": {
      "data": [
		"₢StringText₢",
		"₢StringText₢"
	  ]
	},
	"StringTextMap": {
      "data": {
		"a": "₢StringText₢"
	  }
	},
	"TableText": {
      "data": "₢TableText₢"
	},
	"TableTextArray": {
      "data": [
		"₢TableText₢",
		"₢TableText₢"
	  ]
	},
	"TableTextMap": {
      "data": {
		"a": "₢TableText₢"
	  }
	},
	"UnrealVector": {
	  "data": ₢UnrealVector₢	
	},
	"VectorsArray": {
      "data": [
        ₢UnrealVector₢,
		₢UnrealVector₢
      ]
    },
	"VectorsMap": {
      "data": {
        "a": ₢UnrealVector₢,
		"b": ₢UnrealVector₢
      }
    },
	"UnrealIntVector": {
	  "data": ₢UnrealIntVector₢	
	},
	"IntVectorsArray": {
      "data": [
        ₢UnrealIntVector₢,
		₢UnrealIntVector₢
      ]
    },
	"IntVectorsMap": {
      "data": {
        "a": ₢UnrealIntVector₢,
		"b": ₢UnrealIntVector₢
      }
    },
	"UnrealColor": {
	  "data": ₢UnrealColor₢	
	},
	"ColorsArray": {
      "data": [
        ₢UnrealColor₢,
		₢UnrealColor₢
      ]
    },
	"ColorsMap": {
      "data": {
        "a": ₢UnrealColor₢,
		"b": ₢UnrealColor₢
      }
    },
	"UnrealLinearColor": {
	  "data": ₢UnrealLinearColor₢	
	},
	"LinearColorsArray": {
      "data": [
        ₢UnrealLinearColor₢,
		₢UnrealLinearColor₢
      ]
    },
	"LinearColorsMap": {
      "data": {
        "a": ₢UnrealLinearColor₢,
		"b": ₢UnrealLinearColor₢
      }
    },
	"UnrealGameplayTag": {
	  "data": "₢UnrealGameplayTagA₢"	
	},
	"GameplayTagsArray": {
      "data": [
        "₢UnrealGameplayTagA₢",
		"₢UnrealGameplayTagB₢"
      ]
    },
	"GameplayTagsMap": {
      "data": {
        "a": "₢UnrealGameplayTagA₢",
		"b": "₢UnrealGameplayTagB₢"
      }
    },
	"ArrayOfU8": {
      "data": [
        ₢ValueA₢,
        ₢ValueB₢
      ]
    },
	"ArrayOfString": {
      "data": [
        "₢ValueA₢",
        "₢ValueB₢"
      ]
    },
    "ArrayOfBeamCid": {
      "data": [
        "₢BeamCid₢"
      ]
    },
	"MapOfU8": {
      "data": {
        "a": ₢ValueA₢
      }
    },
	"MapOfString": {
      "data": {
        "a": "₢ValueA₢"
      }
    },
    "MapOfBeamCid": {
      "data": {
        "a": "₢BeamCid₢"
      }
    },    
    "BeamArrayOfString": {
      "data": ["₢ValueA₢"]
    },
    "BeamMapOfString": {
      "data": {
		"a" : "₢ValueA₢"
		}
    },
    "ArrayOfArrayOfString": {
      "data": [
        [
          "₢ValueA₢",
          "₢ValueB₢"
        ]
      ]
    },
    "ArrayOfMapOfString": {
      "data": [
        {
          "a": "₢ValueA₢"
        },
        {
          "a": "₢ValueB₢"
        }
      ]
    },
    "MapOfArrayOfString": {
      "data": {
        "a": [
          "₢ValueA₢",
          "₢ValueB₢"
        ]
      }
    },
    "MapOfMapOfString": {
      "data": {
        "a": {
          "a": "₢ValueA₢"
        }
      }
    },
    "BeamOptionalBool": {
      "data": false
    },
    "BeamOptionalArrayOfInt32": {
      "data": [
        ₢ValueA₢,
        ₢ValueB₢
      ]
    },
    "BeamOptionalMapOfInt64": {
      "data": {
        "a": ₢ValueA₢
      }
    },
    "BeamOptionalBeamCid": {
      "data": "₢BeamCid₢"
    },
    "BeamOptionalArrayOfBeamPid": {
      "data": [
        "₢BeamCid₢"
      ]
    },
	"UnrealSoftObjRef":{ 
		"data": "₢SoftObjPath₢"
	},
	"UnrealClass": {
      "data": "₢UnrealClassA₢"
    },
    "UnrealClassArray": {
      "data": [
        "₢UnrealClassA₢",
        "₢UnrealClassB₢"
      ]
    },
    "UnrealClassMap": {
      "data": {
        "a": "₢UnrealClassA₢",
        "b": "₢UnrealClassB₢"
      }
    },
	"TestLink":{
	  "$link": "₢UnrealLinkId₢"	
	}
  }
})");

	FString WithoutOptionals = TEXT(R"({
  "id": "₢Id₢",
  "version": "₢Version₢",
  "properties": {
    "Value": {
      "data": ₢ValueA₢
    },
    "BeamCid": {
      "data": "₢BeamCid₢"
    },
	"StringText": {
      "data": "₢StringText₢"
	},
	"StringTextArray": {
      "data": [
		"₢StringText₢",
		"₢StringText₢"
	  ]
	},
	"StringTextMap": {
      "data": {
		"a": "₢StringText₢"
	  }
	},
	"TableText": {
      "data": "TableText₢"
	},
	"TableTextArray": {
      "data": [
		"₢TableText₢",
		"₢TableText₢"
	  ]
	},
	"TableTextMap": {
      "data": {
		"a": "₢TableText₢"
	  }
	},
	"UnrealVector": {
	  "data": ₢UnrealVector₢	
	},
	"VectorsArray": {
      "data": [
        ₢UnrealVector₢,
		₢UnrealVector₢
      ]
    },
	"VectorsMap": {
      "data": {
        "a": ₢UnrealVector₢,
		"b": ₢UnrealVector₢
      }
    },
	"UnrealIntVector": {
	  "data": ₢UnrealIntVector₢	
	},
	"IntVectorsArray": {
      "data": [
        ₢UnrealIntVector₢,
		₢UnrealIntVector₢
      ]
    },
	"IntVectorsMap": {
      "data": {
        "a": ₢UnrealIntVector₢,
		"b": ₢UnrealIntVector₢
      }
    },
	"UnrealColor": {
	  "data": ₢UnrealColor₢	
	},
	"ColorsArray": {
      "data": [
        ₢UnrealColor₢,
		₢UnrealColor₢
      ]
    },
	"ColorsMap": {
      "data": {
        "a": ₢UnrealColor₢,
		"b": ₢UnrealColor₢
      }
    },
	"UnrealLinearColor": {
	  "data": ₢UnrealLinearColor₢	
	},
	"LinearColorsArray": {
      "data": [
        ₢UnrealLinearColor₢,
		₢UnrealLinearColor₢
      ]
    },
	"LinearColorsMap": {
      "data": {
        "a": ₢UnrealLinearColor₢,
		"b": ₢UnrealLinearColor₢
      }
    },
	"UnrealGameplayTag": {
	  "data": "₢UnrealGameplayTagA₢"	
	},
	"GameplayTagsArray": {
      "data": [
        "₢UnrealGameplayTagA₢",
		"₢UnrealGameplayTagB₢"
      ]
    },
	"GameplayTagsMap": {
      "data": {
        "a": "₢UnrealGameplayTagA₢",
		"b": "₢UnrealGameplayTagB₢"
      }
    },
	"ArrayOfU8": {
      "data": [
        ₢ValueA₢,
        ₢ValueB₢
      ]
    },
	"ArrayOfString": {
      "data": [
        "₢ValueA₢",
        "₢ValueB₢"
      ]
    },
    "ArrayOfBeamCid": {
      "data": [
        "₢BeamCid₢"
      ]
    },
	"MapOfU8": {
      "data": {
        "a": ₢ValueA₢
      }
    },
	"MapOfString": {
      "data": {
        "a": "₢ValueA₢"
      }
    },
    "MapOfBeamCid": {
      "data": {
        "a": "₢BeamCid₢"
      }
    },    
    "BeamArrayOfString": {
      "data": ["₢ValueA₢"]
    },
    "BeamMapOfString": {
      "data": {
		"a" : "₢ValueA₢"
		}
    },
    "ArrayOfArrayOfString": {
      "data": [
        [
          "₢ValueA₢",
          "₢ValueB₢"
        ]
      ]
    },
    "ArrayOfMapOfString": {
      "data": [
        {
          "a": "₢ValueA₢"
        },
        {
          "a": "₢ValueB₢"
        }
      ]
    },
    "MapOfArrayOfString": {
      "data": {
        "a": [
          "₢ValueA₢",
          "₢ValueB₢"
        ]
      }
    },
    "MapOfMapOfString": {
      "data": {
        "a": {
          "a": "₢ValueA₢"
        }
      }
    },
	"UnrealSoftObjRef":{ 
		"data": "₢SoftObjPath₢"
	},
	"UnrealClass": {
      "data": "₢UnrealClassA₢"
    },
    "UnrealClassArray": {
      "data": [
        "₢UnrealClassA₢",
        "₢UnrealClassB₢"
      ]
    },
    "UnrealClassMap": {
      "data": {
        "a": "₢UnrealClassA₢",
        "b": "₢UnrealClassB₢"
      }
    },
	"TestLink":{
	  "$link": "₢UnrealLinkId₢"	
	}
  }
})");

	FullObject = FullObject.Replace(TEXT("₢Id₢"), *TestId);
	FullObject = FullObject.Replace(TEXT("₢Version₢"), *TestVersion);
	FullObject = FullObject.Replace(TEXT("₢BeamCid₢"), *TestBeamCid);
	FullObject = FullObject.Replace(TEXT("₢StringText₢"), *TestStringText);
	FullObject = FullObject.Replace(TEXT("₢TableText₢"), *TestTableText);
	FullObject = FullObject.Replace(TEXT("₢ValueA₢"), *TestValueA);
	FullObject = FullObject.Replace(TEXT("₢ValueB₢"), *TestValueB);
	FullObject = FullObject.Replace(TEXT("₢SoftObjPath₢"), *TestSoftObjPath);
	FullObject = FullObject.Replace(TEXT("₢UnrealVector₢"), *TestVectorObj);
	FullObject = FullObject.Replace(TEXT("₢UnrealIntVector₢"), *TestIntVectorObj);
	FullObject = FullObject.Replace(TEXT("₢UnrealColor₢"), *TestColorObj);
	FullObject = FullObject.Replace(TEXT("₢UnrealLinearColor₢"), *TestLinearColorObj);
	FullObject = FullObject.Replace(TEXT("₢UnrealGameplayTagA₢"), *TestGameplayTagA);
	FullObject = FullObject.Replace(TEXT("₢UnrealGameplayTagB₢"), *TestGameplayTagB);
	FullObject = FullObject.Replace(TEXT("₢UnrealClassA₢"), *TestUnrealClassA);
	FullObject = FullObject.Replace(TEXT("₢UnrealClassB₢"), *TestUnrealClassB);
	FullObject = FullObject.Replace(TEXT("₢UnrealLinkId₢"), *TestLinkId);

	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢Id₢"), *TestId);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢Version₢"), *TestVersion);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢BeamCid₢"), *TestBeamCid);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢StringText₢"), *TestStringText);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢TableText₢"), *TestTableText);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢ValueA₢"), *TestValueA);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢ValueB₢"), *TestValueB);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢SoftObjPath₢"), *TestSoftObjPath);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealVector₢"), *TestVectorObj);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealIntVector₢"), *TestIntVectorObj);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealColor₢"), *TestColorObj);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealLinearColor₢"), *TestLinearColorObj);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealGameplayTagA₢"), *TestGameplayTagA);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealGameplayTagB₢"), *TestGameplayTagB);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealClassA₢"), *TestUnrealClassA);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealClassB₢"), *TestUnrealClassB);
	WithoutOptionals = WithoutOptionals.Replace(TEXT("₢UnrealLinkId₢"), *TestLinkId);

	Describe("Content Serialization", [=, this]()
	{
		BeforeEach([=, this]()
		{
			ContentObject = NewObject<UMockBeamContentObject>();
			ContentObject->Id = TestId;
			ContentObject->Version = TestVersion;
			ContentObject->Value = TestValueAInt;
			ContentObject->BeamCid = TestBeamCid;

			ContentObject->StringText = FText::FromString(TestStringText);
			ContentObject->StringTextArray = {FText::FromString(TestStringText), FText::FromString(TestStringText)};
			ContentObject->StringTextMap.Add(TEXT("a"), FText::FromString(TestStringText));
			ContentObject->TableText = FText::FromStringTable(FName(TestTableId), TestTableKey);
			ContentObject->TableTextArray = {FText::FromStringTable(FName(TestTableId), TestTableKey), FText::FromStringTable(FName(TestTableId), TestTableKey)};
			ContentObject->TableTextMap.Add(TEXT("a"), FText::FromStringTable(FName(TestTableId), TestTableKey));

			ContentObject->UnrealGameplayTag = FGameplayTag::RequestGameplayTag(FName(TestGameplayTagA), false);
			ContentObject->GameplayTagsArray = {FGameplayTag::RequestGameplayTag(FName(TestGameplayTagA), false), FGameplayTag::RequestGameplayTag(FName(TestGameplayTagB), false)};
			ContentObject->GameplayTagsMap.Add(TEXT("a"), FGameplayTag::RequestGameplayTag(FName(TestGameplayTagA), false));
			ContentObject->GameplayTagsMap.Add(TEXT("b"), FGameplayTag::RequestGameplayTag(FName(TestGameplayTagB), false));

			ContentObject->UnrealVector = FVector::One();
			ContentObject->VectorsArray = {FVector::One(), FVector::One()};
			ContentObject->VectorsMap.Add(TEXT("a"), FVector::One());
			ContentObject->VectorsMap.Add(TEXT("b"), FVector::One());

			ContentObject->UnrealIntVector = FIntVector(1, 1, 1);
			ContentObject->IntVectorsArray = {FIntVector(1, 1, 1), FIntVector(1, 1, 1)};
			ContentObject->IntVectorsMap.Add(TEXT("a"), FIntVector(1, 1, 1));
			ContentObject->IntVectorsMap.Add(TEXT("b"), FIntVector(1, 1, 1));

			ContentObject->UnrealColor = FColor::Black;
			ContentObject->ColorsArray = {FColor::Black, FColor::Black};
			ContentObject->ColorsMap.Add(TEXT("a"), FColor::Black);
			ContentObject->ColorsMap.Add(TEXT("b"), FColor::Black);

			ContentObject->UnrealLinearColor = FLinearColor::Black;
			ContentObject->LinearColorsArray = {FLinearColor::Black, FLinearColor::Black};
			ContentObject->LinearColorsMap.Add(TEXT("a"), FLinearColor::Black);
			ContentObject->LinearColorsMap.Add(TEXT("b"), FLinearColor::Black);

			ContentObject->ArrayOfU8 = TArray{static_cast<uint8>(TestValueAInt), static_cast<uint8>(TestValueBInt)};
			ContentObject->ArrayOfString = TArray{TestValueA, TestValueB};
			ContentObject->ArrayOfBeamCid = TArray{FBeamCid{TestBeamCid}};

			ContentObject->BeamArrayOfString = FArrayOfString(TArray{TestValueA});
			ContentObject->ArrayOfArrayOfString = TArray{FArrayOfString(TArray{TestValueA, TestValueB})};
			ContentObject->ArrayOfMapOfString = TArray{
				FMapOfString(TMap<FString, FString>{{TEXT("a"), TestValueA}}),
				FMapOfString(TMap<FString, FString>{{TEXT("a"), TestValueB}})
			};

			ContentObject->MapOfU8 = TMap<FString, uint8>{{TEXT("a"), static_cast<uint8>(TestValueAInt)}};
			ContentObject->MapOfString = TMap<FString, FString>{{TEXT("a"), TestValueA}};
			ContentObject->MapOfBeamCid = TMap<FString, FBeamCid>{{TEXT("a"), FBeamCid{TestBeamCid}}};

			ContentObject->BeamMapOfString = FMapOfString(TMap<FString, FString>{{TEXT("a"), TestValueA}});
			ContentObject->MapOfArrayOfString = TMap<FString, FArrayOfString>{{TEXT("a"), FArrayOfString(TArray{TestValueA, TestValueB})}};
			ContentObject->MapOfMapOfString = TMap<FString, FMapOfString>{{TEXT("a"), FMapOfString(TMap<FString, FString>{{TEXT("a"), TestValueA}})}};

			ContentObject->UnrealSoftObjRef = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TestSoftObjPath));

			ContentObject->UnrealClass = FSoftClassPath{TestUnrealClassA}.ResolveClass();
			ContentObject->UnrealClassArray = TArray{FSoftClassPath{TestUnrealClassA}.ResolveClass(), FSoftClassPath{TestUnrealClassB}.ResolveClass()};
			ContentObject->UnrealClassMap = TMap<FString, UClass*>{{TEXT("a"), FSoftClassPath{TestUnrealClassA}.ResolveClass()}, {TEXT("b"), FSoftClassPath{TestUnrealClassB}.ResolveClass()}};
		});

		AfterEach([=, this]()
		{
			ContentObject = nullptr;
		});

		It("should serialize ids and version", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("Id serialized correctly", NewObj->Id, TestId);
			TestEqual("Version serialized correctly", NewObj->Version, TestVersion);
			NewObj = nullptr;
		});

		It("should serialize primitives properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("value serialized correctly", NewObj->Value, TestValueAInt);
			NewObj = nullptr;
		});

		It("should serialize FText properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			if (auto Bag = FJsonDataBag(); Bag.FromJson(*Json))
			{
				const auto Props = Bag.GetField(TEXT("properties"))->AsObject();
				TestEqual("String-based FText serialized correctly", Props->GetObjectField(TEXT("StringText"))->GetStringField(TEXT("data")), TestStringText);
				TestEqual("String-based FText serialized correctly", Props->GetObjectField(TEXT("StringTextArray"))->GetArrayField(TEXT("data"))[0]->AsString(), TestStringText);
				TestEqual("String-based FText serialized correctly", Props->GetObjectField(TEXT("StringTextArray"))->GetArrayField(TEXT("data"))[1]->AsString(), TestStringText);
				TestEqual("String-based FText serialized correctly", Props->GetObjectField(TEXT("StringTextMap"))->GetObjectField(TEXT("data"))->GetStringField(TEXT("a")), TestStringText);

				TestEqual("String-based FText serialized correctly", Props->GetObjectField(TEXT("TableText"))->GetStringField(TEXT("data")), TestTableText);
				TestEqual("String-based FText serialized correctly", Props->GetObjectField(TEXT("TableTextArray"))->GetArrayField(TEXT("data"))[0]->AsString(), TestTableText);
				TestEqual("String-based FText serialized correctly", Props->GetObjectField(TEXT("TableTextArray"))->GetArrayField(TEXT("data"))[1]->AsString(), TestTableText);
				TestEqual("String-based FText serialized correctly", Props->GetObjectField(TEXT("TableTextMap"))->GetObjectField(TEXT("data"))->GetStringField(TEXT("a")), TestTableText);
			}
			else
			{
				TestTrue(TEXT("Failed to deserialize"), false);
			}
		});

		It("should serialize semantic types properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("BeamCid serialized correctly", NewObj->BeamCid.AsString, TestBeamCid);
			NewObj = nullptr;
		});

		It("should serialize gameplay tags properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			// If this errors out, make sure you have the expected GameplayTags created here your available ones.
			TestEqual("GameplayTag serialized correctly", NewObj->UnrealGameplayTag.ToString(), TestGameplayTagA);

			TestEqual("GameplayTag serialized correctly", NewObj->GameplayTagsArray[0].ToString(), TestGameplayTagA);
			TestEqual("GameplayTag serialized correctly", NewObj->GameplayTagsArray[1].ToString(), TestGameplayTagB);

			TestEqual("GameplayTag serialized correctly", NewObj->GameplayTagsMap.FindRef(TEXT("a")).ToString(), TestGameplayTagA);
			TestEqual("GameplayTag serialized correctly", NewObj->GameplayTagsMap.FindRef(TEXT("b")).ToString(), TestGameplayTagB);

			NewObj = nullptr;
		});

		It("should serialize Vectors properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			// If this errors out, make sure you have the expected GameplayTags created here your available ones.
			TestEqual("FVector serialized correctly", NewObj->UnrealVector, FVector::One());

			TestEqual("FVector serialized correctly", NewObj->VectorsArray[0], FVector::One());
			TestEqual("FVector serialized correctly", NewObj->VectorsArray[1], FVector::One());

			TestEqual("FVector serialized correctly", NewObj->VectorsMap.FindRef(TEXT("a")), FVector::One());
			TestEqual("FVector serialized correctly", NewObj->VectorsMap.FindRef(TEXT("b")), FVector::One());

			NewObj = nullptr;
		});

		It("should serialize IntVectors properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			// If this errors out, make sure you have the expected GameplayTags created here your available ones.
			TestEqual("FIntVector serialized correctly", NewObj->UnrealIntVector, FIntVector(1, 1, 1));

			TestEqual("FIntVector serialized correctly", NewObj->IntVectorsArray[0], FIntVector(1, 1, 1));
			TestEqual("FIntVector serialized correctly", NewObj->IntVectorsArray[1], FIntVector(1, 1, 1));

			TestEqual("FIntVector serialized correctly", NewObj->IntVectorsMap.FindRef(TEXT("a")), FIntVector(1, 1, 1));
			TestEqual("FIntVector serialized correctly", NewObj->IntVectorsMap.FindRef(TEXT("b")), FIntVector(1, 1, 1));

			NewObj = nullptr;
		});

		It("should serialize colors properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			// If this errors out, make sure you have the expected GameplayTags created here your available ones.
			TestEqual("Color serialized correctly", NewObj->UnrealColor, FColor::Black);

			TestEqual("Color serialized correctly", NewObj->ColorsArray[0], FColor::Black);
			TestEqual("Color serialized correctly", NewObj->ColorsArray[1], FColor::Black);

			TestEqual("Color serialized correctly", NewObj->ColorsMap.FindRef(TEXT("a")), FColor::Black);
			TestEqual("Color serialized correctly", NewObj->ColorsMap.FindRef(TEXT("b")), FColor::Black);

			NewObj = nullptr;
		});

		It("should serialize linear colors properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			// If this errors out, make sure you have the expected GameplayTags created here your available ones.
			TestEqual("LinearColor serialized correctly", NewObj->UnrealLinearColor, FLinearColor::Black);

			TestEqual("LinearColor serialized correctly", NewObj->LinearColorsArray[0], FLinearColor::Black);
			TestEqual("LinearColor serialized correctly", NewObj->LinearColorsArray[1], FLinearColor::Black);

			TestEqual("LinearColor serialized correctly", NewObj->LinearColorsMap.FindRef(TEXT("a")), FLinearColor::Black);
			TestEqual("LinearColor serialized correctly", NewObj->LinearColorsMap.FindRef(TEXT("b")), FLinearColor::Black);

			NewObj = nullptr;
		});

		It("should serialize UClass* properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			// If this errors out, make sure you have the expected GameplayTags created here your available ones.
			TestEqual("Unreal UClass serialized correctly", FSoftClassPath{NewObj->UnrealClass}.ToString(), TestUnrealClassA);

			TestEqual("Unreal UClass serialized correctly", FSoftClassPath{NewObj->UnrealClassArray[0]}.ToString(), TestUnrealClassA);
			TestEqual("Unreal UClass serialized correctly", FSoftClassPath{NewObj->UnrealClassArray[1]}.ToString(), TestUnrealClassB);

			TestEqual("Unreal UClass serialized correctly", FSoftClassPath{NewObj->UnrealClassMap.FindRef(TEXT("a"))}.ToString(), TestUnrealClassA);
			TestEqual("Unreal UClass serialized correctly", FSoftClassPath{NewObj->UnrealClassMap.FindRef(TEXT("b"))}.ToString(), TestUnrealClassB);

			NewObj = nullptr;
		});

		It("should serialize FSoftObjectPtr<> types properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("SoftObjectPtr serialized correctly", NewObj->UnrealSoftObjRef.ToSoftObjectPath().ToString(), TestSoftObjPath);
			NewObj = nullptr;
		});

		It("should serialize TArray<> properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			const auto ExpectedArrayOfU8 = TArray{static_cast<uint8>(TestValueAInt), static_cast<uint8>(TestValueBInt)};
			const auto ExpectedArrayOfString = TArray{TestValueA, TestValueB};

			TestEqual("U8 Array serialized correctly", NewObj->ArrayOfU8, ExpectedArrayOfU8);
			TestEqual("String Array serialized correctly", NewObj->ArrayOfString, ExpectedArrayOfString);
			TestEqual("String Array serialized correctly", NewObj->ArrayOfBeamCid[0], FBeamCid{TestBeamCid});
		});

		It("should serialize TMap<FString,> properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("U8 Array serialized correctly", NewObj->MapOfU8.FindRef(TEXT("a")), TestValueAInt);
			TestEqual("String Array serialized correctly", NewObj->MapOfString.FindRef(TEXT("a")), TestValueA);
			TestEqual("String Array serialized correctly", NewObj->MapOfBeamCid.FindRef(TEXT("a")), FBeamCid{TestBeamCid});
		});

		It("should serialize BeamArrays properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("FArrayOfString deserialized correctly", NewObj->BeamArrayOfString.Values[0], TestValueA);
			TestEqual("TArray<FArrayOfString> deserialized correctly", NewObj->ArrayOfArrayOfString[0].Values[0], TestValueA);
			TestEqual("TArray<FArrayOfString> deserialized correctly", NewObj->ArrayOfArrayOfString[0].Values[1], TestValueB);
			TestEqual("TArray<FMapOfString> deserialized correctly", NewObj->ArrayOfMapOfString[0].Values.FindRef(TEXT("a")), TestValueA);
			TestEqual("TArray<FMapOfString> deserialized correctly", NewObj->ArrayOfMapOfString[1].Values.FindRef(TEXT("a")), TestValueB);
		});

		It("should serialize BeamMaps properly", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("FMapOfString deserialized correctly", NewObj->BeamMapOfString.Values.FindRef(TEXT("a")), TestValueA);
			TestEqual("TMap<FString, FArrayOfString> deserialized correctly", NewObj->MapOfArrayOfString.FindRef("a").Values[0], TestValueA);
			TestEqual("TMap<FString, FArrayOfString> deserialized correctly", NewObj->MapOfArrayOfString.FindRef("a").Values[1], TestValueB);
			TestEqual("TMap<FString, FMapOfString> deserialized correctly", NewObj->MapOfMapOfString.FindRef("a").Values.FindRef("a"), TestValueA);
		});

		It("should serialize BeamOptionals properly", [=, this]()
		{
			ContentObject->BeamOptionalBool = FOptionalBool(false);
			ContentObject->BeamOptionalBeamCid = FOptionalBeamCid(TestBeamCid);
			ContentObject->BeamOptionalArrayOfInt32 = FOptionalArrayOfInt32(TArray{TestValueAInt, TestValueBInt});
			ContentObject->BeamOptionalMapOfInt64 = FOptionalMapOfInt64(TMap<FString, int64>{{TEXT("a"), static_cast<int64>(TestValueAInt)}});
			ContentObject->BeamOptionalArrayOfBeamPid = FOptionalArrayOfBeamPid(TArray{FBeamPid(TestBeamCid)});

			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("Optional of Primitive deserialized correctly", NewObj->BeamOptionalBool.Val, false);
			TestEqual("Optional of semantic type deserialized correctly", NewObj->BeamOptionalBeamCid.Val.AsString, TestBeamCid);

			TestEqual("Optional of TArray<int> deserialized correctly", NewObj->BeamOptionalArrayOfInt32.Val[0], TestValueAInt);
			TestEqual("Optional of TArray<int> deserialized correctly", NewObj->BeamOptionalArrayOfInt32.Val[1], TestValueBInt);

			TestEqual("Optional of TMap<FString, int> deserialized correctly", NewObj->BeamOptionalMapOfInt64.Val.FindRef("a"), TestValueAInt);

			TestEqual("Optional of TArray of Semantic Type deserialized correctly", NewObj->BeamOptionalArrayOfBeamPid.Val[0].AsString, TestBeamCid);
		});

		It("should deserialize BeamOptionals as unset when they are not in the JSON", [=, this]()
		{
			FString Json = FString{};
			ContentObject->ToBasicJson(Json);

			auto NewObj = NewObject<UMockBeamContentObject>();
			NewObj->FromBasicJson(Json);

			TestEqual("Optional of Primitive deserialized correctly", NewObj->BeamOptionalBool.IsSet, false);
			TestEqual("Optional of Primitive deserialized correctly", NewObj->BeamOptionalBeamCid.IsSet, false);
			TestEqual("Optional of Primitive deserialized correctly", NewObj->BeamOptionalArrayOfInt32.IsSet, false);
			TestEqual("Optional of Primitive deserialized correctly", NewObj->BeamOptionalMapOfInt64.IsSet, false);
			TestEqual("Optional of Primitive deserialized correctly", NewObj->BeamOptionalArrayOfBeamPid.IsSet, false);
		});
	});

	Describe("Content Deserialization", [=, this]()
	{
		BeforeEach([=, this]()
		{
			ContentObject = NewObject<UMockBeamContentObject>();
		});

		AfterEach([=, this]()
		{
			ContentObject = nullptr;
		});

		It("should deserialize ids and version properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);

			TestEqual("Id deserialized correctly", ContentObject->Id, TestId);
			TestEqual("Version deserialized correctly", ContentObject->Version, TestVersion);
		});

		It("should deserialize primitives properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("Value deserialized correctly", ContentObject->Value, TestValueAInt);
		});

		It("should deserialize semantic types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("BeamCid deserialized correctly", ContentObject->BeamCid, FBeamCid{TestBeamCid});
		});

		It("should deserialize FText types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);


			TestEqual("String-based FText serialized correctly", ContentObject->StringText.ToString(), TestStringText);
			TestEqual("String-based FText serialized correctly", ContentObject->StringTextArray[0].ToString(), TestStringText);
			TestEqual("String-based FText serialized correctly", ContentObject->StringTextArray[1].ToString(), TestStringText);
			TestEqual("String-based FText serialized correctly", ContentObject->StringTextMap.FindRef(TEXT("a")).ToString(), TestStringText);

			FName TableId;
			FString Key;
			FTextInspector::GetTableIdAndKey(ContentObject->TableText, TableId, Key);
			TestEqual("Table-based FText serialized correctly", TableId.ToString(), TestTableId);
			TestEqual("Table-based FText serialized correctly", Key, TestTableKey);

			FTextInspector::GetTableIdAndKey(ContentObject->TableTextArray[0], TableId, Key);
			TestEqual("Table-based FText serialized correctly", TableId.ToString(), TestTableId);
			TestEqual("Table-based FText serialized correctly", Key, TestTableKey);

			FTextInspector::GetTableIdAndKey(ContentObject->TableTextArray[1], TableId, Key);
			TestEqual("Table-based FText serialized correctly", TableId.ToString(), TestTableId);
			TestEqual("Table-based FText serialized correctly", Key, TestTableKey);

			FTextInspector::GetTableIdAndKey(ContentObject->TableTextMap.FindRef(TEXT("a")), TableId, Key);
			TestEqual("Table-based FText serialized correctly", TableId.ToString(), TestTableId);
			TestEqual("Table-based FText serialized correctly", Key, TestTableKey);
		});

		It("should deserialize gameplay tags types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("GameplayTag deserialized correctly", ContentObject->UnrealGameplayTag.ToString(), TestGameplayTagA);

			TestEqual("GameplayTag deserialized correctly", ContentObject->GameplayTagsArray[0].ToString(), TestGameplayTagA);
			TestEqual("GameplayTag deserialized correctly", ContentObject->GameplayTagsArray[1].ToString(), TestGameplayTagB);

			TestEqual("GameplayTag deserialized correctly", ContentObject->GameplayTagsMap.FindRef(TEXT("a")).ToString(), TestGameplayTagA);
			TestEqual("GameplayTag deserialized correctly", ContentObject->GameplayTagsMap.FindRef(TEXT("b")).ToString(), TestGameplayTagB);
		});

		It("should deserialize FVector types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("FVector deserialized correctly", ContentObject->UnrealVector, FVector::One());

			TestEqual("FVector deserialized correctly", ContentObject->VectorsArray[0], FVector::One());
			TestEqual("FVector deserialized correctly", ContentObject->VectorsArray[1], FVector::One());

			TestEqual("FVector deserialized correctly", ContentObject->VectorsMap.FindRef(TEXT("a")), FVector::One());
			TestEqual("FVector deserialized correctly", ContentObject->VectorsMap.FindRef(TEXT("b")), FVector::One());
		});

		It("should deserialize FIntVector types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("FIntVector deserialized correctly", ContentObject->UnrealIntVector, FIntVector(1, 1, 1));

			TestEqual("FIntVector deserialized correctly", ContentObject->IntVectorsArray[0], FIntVector(1, 1, 1));
			TestEqual("FIntVector deserialized correctly", ContentObject->IntVectorsArray[1], FIntVector(1, 1, 1));

			TestEqual("FIntVector deserialized correctly", ContentObject->IntVectorsMap.FindRef(TEXT("a")), FIntVector(1, 1, 1));
			TestEqual("FIntVector deserialized correctly", ContentObject->IntVectorsMap.FindRef(TEXT("b")), FIntVector(1, 1, 1));
		});

		It("should deserialize color types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("Color deserialized correctly", ContentObject->UnrealColor, FColor::Black);

			TestEqual("Color deserialized correctly", ContentObject->ColorsArray[0], FColor::Black);
			TestEqual("Color deserialized correctly", ContentObject->ColorsArray[1], FColor::Black);

			TestEqual("Color deserialized correctly", ContentObject->ColorsMap.FindRef(TEXT("a")), FColor::Black);
			TestEqual("Color deserialized correctly", ContentObject->ColorsMap.FindRef(TEXT("b")), FColor::Black);
		});

		It("should deserialize linear color types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("Color deserialized correctly", ContentObject->UnrealLinearColor, FLinearColor::Black);

			TestEqual("Color deserialized correctly", ContentObject->LinearColorsArray[0], FLinearColor::Black);
			TestEqual("Color deserialized correctly", ContentObject->LinearColorsArray[1], FLinearColor::Black);

			TestEqual("Color deserialized correctly", ContentObject->LinearColorsMap.FindRef(TEXT("a")), FLinearColor::Black);
			TestEqual("Color deserialized correctly", ContentObject->LinearColorsMap.FindRef(TEXT("b")), FLinearColor::Black);
		});

		It("should deserialize UClass tags types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("GameplayTag deserialized correctly", ContentObject->UnrealClass, FSoftClassPath{TestUnrealClassA}.ResolveClass());

			TestEqual("GameplayTag deserialized correctly", ContentObject->UnrealClassArray[0], FSoftClassPath{TestUnrealClassA}.ResolveClass());
			TestEqual("GameplayTag deserialized correctly", ContentObject->UnrealClassArray[1], FSoftClassPath{TestUnrealClassB}.ResolveClass());

			TestEqual("GameplayTag deserialized correctly", ContentObject->UnrealClassMap.FindRef(TEXT("a")), FSoftClassPath{TestUnrealClassA}.ResolveClass());
			TestEqual("GameplayTag deserialized correctly", ContentObject->UnrealClassMap.FindRef(TEXT("b")), FSoftClassPath{TestUnrealClassB}.ResolveClass());
		});

		It("should deserialize SoftObjectPtr correctly types properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("FSoftObjectPtr deserialized correctly", ContentObject->UnrealSoftObjRef, TSoftObjectPtr<UTexture2D>{FSoftObjectPath(TestSoftObjPath)});
		});

		It("should deserialize TArray<> properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("U8 Array deserialized correctly", ContentObject->ArrayOfU8, TArray{static_cast<uint8>(TestValueAInt), static_cast<uint8>(TestValueBInt)});
			TestEqual("String Array deserialized correctly", ContentObject->ArrayOfString, TArray{TestValueA, TestValueB});
			TestEqual("Semantic Type Array deserialized correctly", ContentObject->ArrayOfBeamCid[0], FBeamCid{TestBeamCid});
		});

		It("should deserialize TMap<FString,> properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);

			TestEqual("U8 Map deserialized correctly", ContentObject->MapOfU8.FindRef(TEXT("a")), TestValueAInt);
			TestEqual("FString Map deserialized correctly", ContentObject->MapOfString.FindRef(TEXT("a")), TestValueA);
			TestEqual("Semantic Type Map deserialized correctly", ContentObject->MapOfBeamCid.FindRef(TEXT("a")), FBeamCid{TestBeamCid});
		});

		It("should deserialize BeamArrays properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("FArrayOfString deserialized correctly", ContentObject->BeamArrayOfString.Values[0], TestValueA);
			TestEqual("TArray<FArrayOfString> deserialized correctly", ContentObject->ArrayOfArrayOfString[0].Values[0], TestValueA);
			TestEqual("TArray<FArrayOfString> deserialized correctly", ContentObject->ArrayOfArrayOfString[0].Values[1], TestValueB);
			TestEqual("TArray<FMapOfString> deserialized correctly", ContentObject->ArrayOfMapOfString[0].Values.FindRef(TEXT("a")), TestValueA);
			TestEqual("TArray<FMapOfString> deserialized correctly", ContentObject->ArrayOfMapOfString[1].Values.FindRef(TEXT("a")), TestValueB);
		});

		It("should deserialize BeamMaps properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("FMapOfString deserialized correctly", ContentObject->BeamMapOfString.Values.FindRef(TEXT("a")), TestValueA);
			TestEqual("TMap<FString, FArrayOfString> deserialized correctly", ContentObject->MapOfArrayOfString.FindRef("a").Values[0], TestValueA);
			TestEqual("TMap<FString, FArrayOfString> deserialized correctly", ContentObject->MapOfArrayOfString.FindRef("a").Values[1], TestValueB);
			TestEqual("TMap<FString, FMapOfString> deserialized correctly", ContentObject->MapOfMapOfString.FindRef("a").Values.FindRef("a"), TestValueA);
		});


		It("should deserialize BeamOptionals properly", [=, this]()
		{
			ContentObject->FromBasicJson(FullObject);
			TestEqual("Optional of Primitive deserialized correctly", ContentObject->BeamOptionalBool.Val, false);
			TestEqual("Optional of semantic type deserialized correctly", ContentObject->BeamOptionalBeamCid.Val.AsString, TestBeamCid);

			TestEqual("Optional of TArray<int> deserialized correctly", ContentObject->BeamOptionalArrayOfInt32.Val[0], TestValueAInt);
			TestEqual("Optional of TArray<int> deserialized correctly", ContentObject->BeamOptionalArrayOfInt32.Val[1], TestValueBInt);

			TestEqual("Optional of TMap<FString, int> deserialized correctly", ContentObject->BeamOptionalMapOfInt64.Val.FindRef("a"), TestValueAInt);

			TestEqual("Optional of TArray of Semantic Type deserialized correctly", ContentObject->BeamOptionalArrayOfBeamPid.Val[0].AsString, TestBeamCid);
		});

		It("should deserialize BeamOptionals as unset when they are not in the JSON", [=, this]()
		{
			ContentObject->FromBasicJson(WithoutOptionals);
			TestEqual("Optional of Primitive deserialized correctly", ContentObject->BeamOptionalBool.IsSet, false);
			TestEqual("Optional of Primitive deserialized correctly", ContentObject->BeamOptionalBeamCid.IsSet, false);
			TestEqual("Optional of Primitive deserialized correctly", ContentObject->BeamOptionalArrayOfInt32.IsSet, false);
			TestEqual("Optional of Primitive deserialized correctly", ContentObject->BeamOptionalMapOfInt64.IsSet, false);
			TestEqual("Optional of Primitive deserialized correctly", ContentObject->BeamOptionalArrayOfBeamPid.IsSet, false);
		});
	});
}
