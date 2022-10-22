#pragma once

#include "CoreMinimal.h"

#include "HttpModule.h"
#include "BeamBackend/BeamRealmHandle.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamRetryConfig.h"

#include "BeamCoreTypes.generated.h"


USTRUCT(BlueprintType)
struct FRequestType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	explicit FRequestType()
	{
	}

	FRequestType(const FString& x) { Name = x; }

	FRequestType& operator=(const FString& x)
	{
		this->Name = x;
		return *this;
	}

	bool operator==(const FRequestType& Other) const
	{
		return Equals(Other);
	}

	bool Equals(const FRequestType& Other) const
	{
		return Name.Equals(Other.Name);
	}

	operator FString() { return Name; }
};

FORCEINLINE uint32 GetTypeHash(const FRequestType& RequestType) { return GetTypeHash(RequestType.Name); }

/**
 * @brief Semantic separation for longs representing a Beamable Request Id.
 * Every request sent out from any of the UBeam***Api subsystems gets one of these.
 */
typedef int64 FBeamRequestId;


/**
 * @brief Shorter name for Unreal's HttpRequest struct.
 */
typedef TSharedRef<IHttpRequest, ESPMode::ThreadSafe> TUnrealRequest;

/**
 * @brief Shorter name for the pointer to Unreal's HttpRequest struct.
 */
typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> TUnrealRequestPtr;

/**
 * @brief Shorter name for unreal's request status.
 */
typedef EHttpRequestStatus::Type TUnrealRequestStatus;

/**
 * @brief Semantic separation for the Functor declaration representing a Beamable Request Processor.
 * Exist to make explicit any assumptions we make about passing parameters to the request processing callback.
 */
typedef TFunction<void (FHttpRequestPtr request, FHttpResponsePtr response, bool success)> FBeamRequestProcessor;

/**
 * @brief Holds data regarding internet connectivity status for Beamable. 
 */
USTRUCT(BlueprintType)
struct FBeamConnectivity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool IsConnected;

	UPROPERTY(BlueprintReadOnly)
	int64 LastTimeSinceSuccessfulRequest;
};

UINTERFACE(MinimalAPI, Blueprintable)
class UBeamBaseRequestInterface : public UInterface
{
	GENERATED_BODY()
};

class IBeamBaseRequestInterface
{
	GENERATED_BODY()

public:
	virtual void BuildVerb(FString& VerbString) const
	{
	}

	virtual void BuildRoute(FString& RouteString) const
	{
	}

	virtual void BuildBody(FString& BodyString) const
	{
	}
};

USTRUCT(BlueprintType)
struct FBeamErrorResponse
{
	GENERATED_BODY()

	/// <summary>
	/// The http status code
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int64 status;

	/// <summary>
	/// The Beamable error code.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString error;

	/// <summary>
	/// The Beamable service where the error originated
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString service;

	/// <summary>
	/// A more detailed message about the error.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString message;
};


enum EBeamFullResponseState
{
	Success,
	Error,
	Cancelled,
	Retrying,
};


template <typename TRequestData, typename TResponseData>
struct FBeamFullResponse
{
	/**
	 * @brief The request data that was sent to Beamable.
	 */
	TRequestData RequestData;

	/**
	 * @brief In case of success, the response body gets placed here.  
	 */
	TResponseData SuccessData;

	/**
	 * @brief In case of error, the response body gets placed here.
	 */
	FBeamErrorResponse ErrorData;

	/**
	 * @brief The internal RequestId. Users can use an API to cancel any request retry by passing this in. 
	 */
	FBeamRequestContext Context;

	/**
	 * @brief Whether or not the Beamable back-end responded successfully to the request. 
	 */
	EBeamFullResponseState State;

	/**
	 * @brief The current attempt number. Starts at 0.
	 */
	int AttemptNumber;
};

DECLARE_DELEGATE_TwoParams(FBeamMakeRequestDelegate, int64 /*ActiveRequestId*/, FBeamConnectivity& /*Connectivity*/);

DECLARE_DELEGATE_TwoParams(FGlobalRequestErrorCodeHandler, const FBeamRequestContext&, const FBeamErrorResponse&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGlobalRequestErrorHandler, const FBeamRequestContext&, RequestContext, const FBeamErrorResponse&, Error);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FGlobalConnectivityChangedCodeHandler, const FBeamRequestContext&, const FRequestType&, const bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGlobalConnectivityChangedHandler, const FBeamRequestContext&, RequestContext, const FRequestType&, FailedRequestType, const bool, bConnected);

template <typename TRequestData, typename TResponseData>
using TBeamFullResponseHandler = TDelegate<void(FBeamFullResponse<TRequestData, TResponseData>)>;

template <typename TRequestData, typename TResponseData>
using TBlueprintRequestSuccessHandler = TBaseDynamicDelegate<FWeakObjectPtr, void, TRequestData, TResponseData>;

template <typename TRequestData>
using TBlueprintRequestErrorHandler = TBaseDynamicDelegate<FWeakObjectPtr, void, TRequestData, FBeamErrorResponse>;

template <typename TRequestData>
using TBlueprintRequestCompleteHandler = TBaseDynamicDelegate<FWeakObjectPtr, void, TRequestData>;


struct FRequestToRetry
{
	FBeamRequestId RequestId = 0;
	int IsBlueprint;
	int ResponseCode;

	FBeamRealmHandle RealmHandle;
	FBeamAuthToken AuthToken;

	friend bool operator==(const FRequestToRetry& Lhs, const FRequestToRetry& RHS)
	{
		return Lhs.RequestId == RHS.RequestId
			&& Lhs.IsBlueprint == RHS.IsBlueprint
			&& Lhs.ResponseCode == RHS.ResponseCode
			&& Lhs.RealmHandle == RHS.RealmHandle
			&& Lhs.AuthToken == RHS.AuthToken;
	}

	friend bool operator!=(const FRequestToRetry& Lhs, const FRequestToRetry& RHS)
	{
		return !(Lhs == RHS);
	}
};

struct FProcessingRequestRetry
{
	FRequestToRetry RequestToRetry;

	float TimeToWait;
	float AccumulatedTime;
};
