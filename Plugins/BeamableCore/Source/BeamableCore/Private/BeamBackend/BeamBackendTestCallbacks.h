#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamBackendTestCallbacks.generated.h"


// Forward declaration of the Automated Testing class so we can make it a friend and make it easier to test internal state.
// Also, mock request types declared for Automated Testing purposes.
class FBeamBackendSpec;

UCLASS()
class UBeamMockBody final : public UObject, public FBeamJsonSerializable
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
		FakeInt = Bag->GetIntegerField("fake_int");
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
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
		Body->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}

	virtual void BuildRoute(FString& RouteString) const override { RouteString.Appendf(TEXT("/fake/url")); }
};

UCLASS()
class UBeamMockGetRequestResponse : public UObject, public FBeamJsonSerializable
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
		FakeInt = Bag->GetIntegerField("fake_int");
	}
};


DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMockSuccess, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request, UBeamMockGetRequestResponse*, Response);

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMockError, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request, FBeamErrorResponse, Error);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMockComplete, FBeamRequestContext, RequestId, UBeamMockGetRequest*, Request);

using FMockFullResponse = FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*>;
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
};
