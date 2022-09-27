#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"
#include "BeamJsonUtils.h"

#include "BeamBackendTestCallbacks.generated.h"


// Forward declaration of the Automated Testing class so we can make it a friend and make it easier to test internal state.
// Also, mock request types declared for Automated Testing purposes.
class FBeamBackendSpec;

USTRUCT()
struct FBeamMockBody : public FBeamJsonSerializable
{
	GENERATED_BODY()

	int FakeInt;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("fake_int", FakeInt);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FakeInt = Bag->GetIntegerField("fake_int");
	}
};

USTRUCT()
struct FBeamMockGetRequest : public FBeamBaseRequest
{
	GENERATED_BODY()
	virtual void BuildVerb(FString& VerbString) const override { VerbString = TEXT("GET"); }
	virtual void BuildBody(FString& BodyString) const override { BodyString = TEXT(""); }
	virtual void BuildRoute(FString& RouteString) const override { RouteString.Appendf(TEXT("/fake/url")); }
};

USTRUCT()
struct FBeamMockPostRequest : public FBeamBaseRequest
{
	GENERATED_BODY()
	FBeamMockBody Body;

	virtual void BuildVerb(FString& VerbString) const override { VerbString = TEXT("POST"); }

	virtual void BuildBody(FString& BodyString) const override
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
		Body.BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}

	virtual void BuildRoute(FString& RouteString) const override { RouteString.Appendf(TEXT("/fake/url")); }
};

USTRUCT()
struct FBeamMockGetRequestResponse : public FBeamBaseResponse
{
	GENERATED_BODY()

	FBeamMockBody Body;
};


DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMockSuccess, int64, RequestId, FBeamMockGetRequest, Request, FBeamMockGetRequestResponse, Response);

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMockError, int64, RequestId, FBeamMockGetRequest, Request, FBeamErrorResponse, Error);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMockComplete, int64, RequestId, FBeamMockGetRequest, Request);

using FMockFullResponse = FBeamFullResponse<FBeamMockGetRequest, FBeamMockGetRequestResponse>;
DECLARE_DELEGATE_OneParam(FOnMockFullResponse, FMockFullResponse);


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
	
	UFUNCTION()
	void MockSuccessCallback_Expected(int64 RequestId, FBeamMockGetRequest Request, FBeamMockGetRequestResponse Response) const;
	UFUNCTION()
	void MockSuccessCallback_Fail(int64 RequestId, FBeamMockGetRequest Request, FBeamMockGetRequestResponse Response) const;

	UFUNCTION()
	void MockErrorCallback_Expected(int64 RequestId, FBeamMockGetRequest Request, FBeamErrorResponse Response) const;	
	UFUNCTION()
	void MockErrorCallback_Fail(int64 RequestId, FBeamMockGetRequest Request, FBeamErrorResponse Response) const;

	UFUNCTION()
	void MockCompleteCallback_Expected(int64 RequestId, FBeamMockGetRequest Request) const;

	UFUNCTION()
	void MockCompleteCallbackCancelled_Expected(int64 RequestId, FBeamMockGetRequest Request) const;
};
