#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Enums/BeamGroupType.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Engine/DataTable.h"
#include "Serialization/BeamCsvUtils.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamBackendTestCallbacks.generated.h"


// Forward declaration of the Automated Testing class so we can make it a friend and make it easier to test internal state.
// Also, mock request types declared for Automated Testing purposes.
class FBeamBackendSpec;

UCLASS()
class UBeamMockBody final : public UObject, public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

public:
	int FakeInt;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("fake_int", FakeInt);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FakeInt = Bag->GetIntegerField(TEXT("fake_int"));
	}
};

UCLASS()
class UBeamMockGetRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()

public:
	virtual void BuildVerb(FString& VerbString) const override { VerbString = TEXT("GET"); }
	virtual void BuildBody(FString& BodyString) const override { BodyString = TEXT(""); }
	virtual void BuildRoute(FString& RouteString) const override { RouteString.Appendf(TEXT("/fake/url")); }
};

UCLASS()
class UBeamMockPostRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBeamMockBody* Body;

	virtual void BuildVerb(FString& VerbString) const override { VerbString = TEXT("POST"); }

	virtual void BuildBody(FString& BodyString) const override
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
		Body->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}

	virtual void BuildRoute(FString& RouteString) const override { RouteString.Appendf(TEXT("/fake/url")); }
};

UCLASS()
class UBeamMockGetRequestResponse : public UObject, public FBeamJsonSerializableUStruct, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int FakeInt;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("fake_int", FakeInt);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FakeInt = Bag->GetIntegerField(TEXT("fake_int"));
	}

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override
	{
		OuterOwner = RequestData;
		BeamDeserialize(ResponseContent);
	}
};


DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMockSuccess, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request, UBeamMockGetRequestResponse*, Response);

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMockError, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request, FBeamErrorResponse, Error);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMockComplete, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request);

using FMockFullResponse = FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*>;
DECLARE_DELEGATE_OneParam(FOnMockFullResponse, FMockFullResponse);


USTRUCT(BlueprintType)
struct FBeamMockGetRequestCSVResponseRow : public FTableRowBase
{
	GENERATED_BODY()

	const static FString KeyField;
	const static TArray<FString> HeaderFields;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Field1 = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Field2;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int64 Field3 = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Field4;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamGroupType Field5 = EBeamGroupType::BEAM_guild;
};

UCLASS(BlueprintType)
class UBeamMockGetRequestCSVResponse : public UObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UDataTable* FakeTable;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override
	{
		FakeTable = NewObject<UDataTable>(RequestData);

		// Generate this only if the CSV has no unique value
		UBeamCsvUtils::AddAutoGenKeyField(ResponseContent);
		// Generate this only if the CSV will not contain the header row
		UBeamCsvUtils::AddHeaderRow(ResponseContent, FBeamMockGetRequestCSVResponseRow::HeaderFields);
		// Generate this always.
		UBeamCsvUtils::ParseIntoDataTable(FakeTable,
		                                  FBeamMockGetRequestCSVResponseRow::StaticStruct(),
		                                  FBeamMockGetRequestCSVResponseRow::KeyField,
		                                  ResponseContent);

		UBeamCsvUtils::StoreNameAsColumn<FBeamMockGetRequestCSVResponseRow>(FakeTable, FBeamMockGetRequestCSVResponseRow::KeyField);
	}
};


DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMockCSVSuccess, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request, UBeamMockGetRequestCSVResponse*, Response);

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMockCSVError, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request, FBeamErrorResponse, Error);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMockCSVComplete, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request);

using FMockCSVFullResponse = FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestCSVResponse*>;
DECLARE_DELEGATE_OneParam(FOnMockCSVFullResponse, FMockCSVFullResponse);


UCLASS()
class UBeamBackendTestCallbacks final : public UObject
{
	GENERATED_BODY()

public:
	FBeamBackendSpec* Spec;

	UPROPERTY()
	UBeamBackend* BeamBackend;

	// Forwarded data from the "Fake Request" we made.
	int64 ExpectedReqId;
	int ExpectedSuccessResponse;

	// Data we expect to see in the "FBeamErrorResponse" data struct that got parsed from the request we made.
	int ExpectedErrorFailureCount;
	int64 ExpectedErrorResponseStatus;
	FString ExpectedErrorResponseError;
	FString ExpectedErrorResponseService;
	FString ExpectedErrorResponseMessage;

	// Done callback so that we can run latent tests correctly
	FDoneDelegate DoneDelegateForLatentTests;

	// Used by generate external request id
	TArray<int64> ExternalRequestIds;


	UFUNCTION()
	void MockSuccessCallback_Expected(FBeamRequestContext Context, UBeamMockGetRequest* Request, UBeamMockGetRequestResponse* Response) const;
	UFUNCTION()
	void MockSuccessCallback_Fail(FBeamRequestContext Context, UBeamMockGetRequest* Request, UBeamMockGetRequestResponse* Response) const;

	UFUNCTION()
	void MockErrorCallback_Expected(FBeamRequestContext Context, UBeamMockGetRequest* Request, FBeamErrorResponse Response) const;
	UFUNCTION()
	void MockErrorCallback_Fail(FBeamRequestContext Context, UBeamMockGetRequest* Request, FBeamErrorResponse Response) const;

	UFUNCTION()
	void MockCompleteCallback_Expected(FBeamRequestContext Context, UBeamMockGetRequest* Request) const;

	UFUNCTION()
	void MockCompleteCallbackCancelled_Expected(FBeamRequestContext Context, UBeamMockGetRequest* Request) const;

	UFUNCTION()
	void GenerateExternalRequestIds(TArray<int64>& OutUsingRequestIds) const;
};
