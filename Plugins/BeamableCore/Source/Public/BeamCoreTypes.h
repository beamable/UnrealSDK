#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Json/Public/Serialization/JsonWriter.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializerMacros.h"

#include "BeamCoreTypes.generated.h"

//Declare all Beamable Log Categories Here
// TODO: Move to BeamLogging.h
DECLARE_LOG_CATEGORY_EXTERN(LogBeamBackend, Log, All);



/**
 * @brief Semantic separation for strings representing a Beamable User Slot.
 */
USTRUCT(BlueprintType)
struct FUserSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SlotName;

	explicit FUserSlot()
	{
	}

	FUserSlot(const FString& x) { SlotName = x; }

	FUserSlot& operator=(const FString& x)
	{
		this->SlotName = x;
		return *this;
	}

	bool operator==(const FUserSlot& Other) const
	{
		return Equals(Other);
	}
	
	bool Equals(const FUserSlot& Other) const
	{
		return SlotName.Equals(Other.SlotName);
	}

	operator FString() { return SlotName; }
};
FORCEINLINE uint32 GetTypeHash(const FUserSlot& UserSlot) { return GetTypeHash(UserSlot.SlotName); }

USTRUCT(BlueprintType)
struct FRequestType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RequestName;

	explicit FRequestType()
	{
	}

	FRequestType(const FString& x) { RequestName = x; }

	FRequestType& operator=(const FString& x)
	{
		this->RequestName = x;
		return *this;
	}

	bool operator==(const FRequestType& Other) const
	{
		return Equals(Other);
	}
	
	bool Equals(const FRequestType& Other) const
	{
		return RequestName.Equals(Other.RequestName);
	}

	operator FString() { return RequestName; }
};
FORCEINLINE uint32 GetTypeHash(const FRequestType& RequestType) { return GetTypeHash(RequestType.RequestName); }

/**
 * @brief Semantic separation for ints representing an active Beamable User Idx.
 * These are never guaranteed to be the same across sessions.
 */
typedef int FBeamUserIdx;

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
 * @brief Shorter name for the default Unreal Json Writer.
 */
typedef TSharedRef<TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>> TUnrealJsonSerializer;

/**
 * @brief Shorter name for the default Unreal Json Deserializer.
 */
typedef TSharedRef<TJsonReader<TCHAR>> TUnrealJsonDeserializer;

/**
 * @brief Semantic separation for the Functor declaration representing a Beamable Request Processor.
 * Exist to make explicit any assumptions we make about passing parameters to the request processing callback.
 */
typedef TFunction<void (FHttpRequestPtr request, FHttpResponsePtr response, bool success)> FBeamRequestProcessor;


USTRUCT(BlueprintType)
struct FBeamAuthToken
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString AccessToken;
	UPROPERTY(BlueprintReadOnly)
	FString RefreshToken;
	UPROPERTY(BlueprintReadOnly)
	int64 ExpiresIn;
};

USTRUCT(BlueprintType)
struct FBeamRealmHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Cid;

	UPROPERTY(BlueprintReadOnly)
	FString Pid;
};

USTRUCT(BlueprintType)
struct FBeamRealmUser
{
	GENERATED_BODY()

	UPROPERTY()
	FBeamRealmHandle RealmHandle;
	UPROPERTY()
	FBeamAuthToken AuthToken;
};


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
	float LastTimeSinceSuccessfulRequest;

	UPROPERTY(BlueprintReadWrite)
	float IdleTimeForConnectionVerification;
};

/**
 * @brief Holds data defining how a request needs to be sent out. 
 */
USTRUCT(BlueprintType)
struct FBeamRetryConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Timeout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> RetryFalloffValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RetryMaxAttempt = -1;
};

USTRUCT(BlueprintType)
struct FBeamRequestContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FBeamRetryConfig RetryConfiguration;

	UPROPERTY(BlueprintReadWrite)
	FBeamRealmHandle Handle;
};

USTRUCT(BlueprintType)
struct FBeamJsonSerializable
{
	GENERATED_BODY()
	virtual ~FBeamJsonSerializable() = default;

	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const
	{
		Serializer->WriteObjectStart();
		BeamSerializeProperties(Serializer);
		Serializer->WriteObjectEnd();
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
	{
		ensure(false);
	}

	virtual void BeamDeserialize(const FString& JsonString)
	{
		auto Bag = FJsonDataBag{};
		UE_LOG(LogTemp, Display, TEXT("Deserializing Json String=%s"), *JsonString);

		Bag.FromJson(JsonString);
		const auto JsonBag = Bag.JsonObject;
		BeamDeserializeProperties(JsonBag);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
	{
		ensure(false);
	}
};


USTRUCT(BlueprintType)
struct FBeamBaseRequest
{
	GENERATED_BODY()
	virtual ~FBeamBaseRequest() = default;

	FORCEINLINE virtual void BuildVerb(FString& VerbString) const { VerbString = TEXT("GET"); }

	FORCEINLINE virtual void BuildRoute(FString& RouteString) const { RouteString = TEXT(""); }

	FORCEINLINE virtual void BuildBody(FString& BodyString) const
	{
		/* Every generated Request with a body has a UObject Body field that    
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
		Body.BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
		*/
	}
};


USTRUCT(BlueprintType)
struct FBeamBaseResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int ResponseCode;
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
	int64 RequestId;

	/**
	 * @brief Whether or not the Beamable back-end responded successfully to the request. 
	 */
	EBeamFullResponseState State;

	/**
	 * @brief The current attempt number. Starts at 0.
	 */
	int AttemptNumber;
};

DECLARE_DELEGATE_ThreeParams(FBeamMakeRequestDelegate, const FBeamRequestContext& /*RequestContext*/, FBeamConnectivity& /*Connectivity*/, int64 /*ActiveRequestId*/);

DECLARE_DELEGATE_TwoParams(FGlobalRequestErrorCodeHandler, const int64&, const FBeamErrorResponse&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGlobalRequestErrorHandler, const int64&, ActiveRequestId, const FBeamErrorResponse&, Error);

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

	FBeamRealmHandle RealmHandle;
	FBeamAuthToken AuthToken;
};

struct FProcessingRequestRetry
{
	FRequestToRetry RetryHandle;

	float TimeToWait;
	float AccumulatedTime;
};

USTRUCT(BlueprintType)
struct FBeamOptional
{
	GENERATED_BODY()
	virtual ~FBeamOptional() = default;

	UPROPERTY(BlueprintReadOnly)
	bool IsSet = false;

	virtual const void* GetAddr() const
	{
		ensure(false);
		return nullptr;
	}

	virtual bool TryGet(void* OutData, size_t& OutSize) const
	{
		ensure(false);
		return false;
	};

	virtual void Set(const void* Data)
	{
		ensure(false);
	}

	template <typename T>
	static void Set(FBeamOptional* Optional, const T* Data) { Optional->Set(static_cast<const void*>(Data)); }

	template <typename T>
	static void Reset(FBeamOptional* Optional)
	{
		T defaultVal = T{};
		Optional->Set(static_cast<void*>(&defaultVal));
		Optional->IsSet = false;
	}

	template <typename T>
	static const T& GetValue(const FBeamOptional* Optional) { return *static_cast<const T*>(Optional->GetAddr()); }
};
