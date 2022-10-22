#pragma once

#include "CoreMinimal.h"

#include "HttpModule.h"
#include "BeamBackend/BeamRealmHandle.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamRetryConfig.h"

#include "BeamCoreTypes.generated.h"


/**
 * @brief Semantic separation for strings representing each Beamable Request Type (each endpoint). 
 */
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

	/**
	 * @brief Whether or not the last request was successful (true) or failed due to connectivity issues (false).
	 */
	UPROPERTY(BlueprintReadOnly)
	bool IsConnected;

	/**
	 * @brief The time in ticks since the last successful request occurred.
	 */
	UPROPERTY(BlueprintReadOnly)
	int64 LastTimeSinceSuccessfulRequest;
};

/**
 * @brief Wraps around all Request UObjects that we codegen.
 * Enables UBeamBackend to provide guarantees about the lifecycle of every request that goes out while maintaining BP compatibility and keeping compile times low. 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UBeamBaseRequestInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Wraps around all Request UObjects that we codegen.
 * Enables UBeamBackend to provide guarantees about the lifecycle of every request that goes out while maintaining BP compatibility and keeping compile times low. 
 */
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

/**
 * @brief Wraps around all Beamable Serializable types that we codegen and are used as responses.
 * Enables UBeamBackend to provide guarantees about the lifecycle of every response that goes out while maintaining BP compatibility and keeping compile times low. 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UBeamBaseResponseBodyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Wraps around all Beamable Serializable types that we codegen and are used as responses.
 * Enables UBeamBackend to provide guarantees about the lifecycle of every response that goes out while maintaining BP compatibility and keeping compile times low. 
 */
class IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()
};

/**
 * @brief Maps to the response our server sends when a request fails. 
 */
USTRUCT(BlueprintType)
struct FBeamErrorResponse
{
	GENERATED_BODY()

	/**
	 * @brief The HTTP Status Code. 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int64 status;

	/**
	 * @brief Beamable's own Error Code.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString error;

	/**
	 * @brief The Beamable service where the error originated.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString service;

	/**
	 * @brief A more detailed message about the error.
	 */
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

/**
 * @brief Templated wrapper for use in code ONLY WHEN YOU NEED LAMBDAS. ALWAYS PREFER THE BP COMPATIBLE VERSIONS!  
 */
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


/**
 * @brief Handle to an Enqueued Request that needs to be retried.
 */
struct FRequestToRetry
{
	/**
	 * @brief The unique request id.
	 */
	FBeamRequestId RequestId = 0;

	/**
	 * @brief Whether or not the request was made with a blueprint compatible handler. 
	 */
	int32 IsBlueprintCompatible;

	/**
	 * @brief The HTTP status code.
	 */
	int32 ResponseCode;

	/**
	 * @brief The realm the request was targeted to.
	 */
	FBeamRealmHandle RealmHandle;

	/**
	 * @brief The authentication token used in the request, if any.
	 */
	FBeamAuthToken AuthToken;

	friend bool operator==(const FRequestToRetry& Lhs, const FRequestToRetry& RHS)
	{
		return Lhs.RequestId == RHS.RequestId
			&& Lhs.IsBlueprintCompatible == RHS.IsBlueprintCompatible
			&& Lhs.ResponseCode == RHS.ResponseCode
			&& Lhs.RealmHandle == RHS.RealmHandle
			&& Lhs.AuthToken == RHS.AuthToken;
	}

	friend bool operator!=(const FRequestToRetry& Lhs, const FRequestToRetry& RHS)
	{
		return !(Lhs == RHS);
	}
};

/**
 * @brief Data needed to decided when enough time has passed that we should retry again.
 */
struct FProcessingRequestRetry
{
	/**
	 * @brief The handle defining which request we are processing.
	 */
	FRequestToRetry RequestToRetry;

	/**
	 * @brief How long (in seconds) should we wait before trying the request again.
	 */
	float TimeToWait;

	/**
	 * @brief How long (in seconds) have we waited for this retry.
	 */
	float AccumulatedTime;
};
