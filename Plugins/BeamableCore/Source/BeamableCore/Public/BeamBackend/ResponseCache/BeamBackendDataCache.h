#pragma once

#include "BeamBackend/RequestType.h"

#include "BeamBackendDataCache.generated.h"


UENUM()
enum EBeamCacheHierarchyLevel
{
	Global = 0,
	RequestType = 1,
	CallingContext = 2,
	Callsite = 3,
};

USTRUCT(BlueprintType)
struct FBeamCachedRequestCallsite
{
	GENERATED_BODY()

	/**
	 * @brief The type of the request being made at this callsite.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRequestType Type;

	/**
	 * @brief The calling context this request is being made from.
	 */
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	const UObject* CallingContext = nullptr;

	friend bool operator==(const FBeamCachedRequestCallsite& Lhs, const FBeamCachedRequestCallsite& RHS)
	{
		return Lhs.Type == RHS.Type
			&& Lhs.CallingContext == RHS.CallingContext;
	}

	friend bool operator!=(const FBeamCachedRequestCallsite& Lhs, const FBeamCachedRequestCallsite& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamCachedRequestCallsite& InKey)
{
	uint32 KeyHash = 0;
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.Type));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.CallingContext));	
	return KeyHash;
}


USTRUCT()
struct FGlobalCacheKey
{
	GENERATED_BODY()

	FString ReqHeader;
	FString ReqURL;
	FString ReqBody;

	friend bool operator==(const FGlobalCacheKey& Lhs, const FGlobalCacheKey& RHS)
	{
		return Lhs.ReqHeader == RHS.ReqHeader
			&& Lhs.ReqURL == RHS.ReqURL
			&& Lhs.ReqBody == RHS.ReqBody;
	}

	friend bool operator!=(const FGlobalCacheKey& Lhs, const FGlobalCacheKey& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FGlobalCacheKey& InKey)
{
	uint32 KeyHash = 0;
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqHeader));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqURL));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqBody));
	return KeyHash;
}

USTRUCT()
struct FRequestTypeCacheKey
{
	GENERATED_BODY()

	FRequestType Type;
	FString ReqHeader;
	FString ReqURL;
	FString ReqBody;

	friend bool operator==(const FRequestTypeCacheKey& Lhs, const FRequestTypeCacheKey& RHS)
	{
		return Lhs.Type == RHS.Type
			&& Lhs.ReqHeader == RHS.ReqHeader
			&& Lhs.ReqURL == RHS.ReqURL
			&& Lhs.ReqBody == RHS.ReqBody;
	}

	friend bool operator!=(const FRequestTypeCacheKey& Lhs, const FRequestTypeCacheKey& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FRequestTypeCacheKey& InKey)
{
	uint32 KeyHash = 0;
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.Type));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqHeader));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqURL));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqBody));
	return KeyHash;
}

USTRUCT()
struct FCallingContextCacheKey
{
	GENERATED_BODY()

	FString CallingContextName;
	FString ReqHeader;
	FString ReqURL;
	FString ReqBody;

	friend bool operator==(const FCallingContextCacheKey& Lhs, const FCallingContextCacheKey& RHS)
	{
		return Lhs.CallingContextName == RHS.CallingContextName
			&& Lhs.ReqHeader == RHS.ReqHeader
			&& Lhs.ReqURL == RHS.ReqURL
			&& Lhs.ReqBody == RHS.ReqBody;
	}

	friend bool operator!=(const FCallingContextCacheKey& Lhs, const FCallingContextCacheKey& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FCallingContextCacheKey& InKey)
{
	uint32 KeyHash = 0;
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.CallingContextName));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqHeader));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqURL));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqBody));
	return KeyHash;
}


USTRUCT()
struct FCallsiteCacheKey
{
	GENERATED_BODY()

	FRequestType Type;
	FString CallingContextName;
	FString ReqHeader;
	FString ReqURL;
	FString ReqBody;

	friend bool operator==(const FCallsiteCacheKey& Lhs, const FCallsiteCacheKey& RHS)
	{
		return Lhs.Type == RHS.Type
			&& Lhs.CallingContextName == RHS.CallingContextName
			&& Lhs.ReqHeader == RHS.ReqHeader
			&& Lhs.ReqURL == RHS.ReqURL
			&& Lhs.ReqBody == RHS.ReqBody;
	}

	friend bool operator!=(const FCallsiteCacheKey& Lhs, const FCallsiteCacheKey& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FCallsiteCacheKey& InKey)
{
	uint32 KeyHash = 0;
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.Type));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.CallingContextName));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqHeader));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqURL));
	KeyHash = HashCombine(KeyHash, GetTypeHash(InKey.ReqBody));
	return KeyHash;
}


template <typename T>
struct FBeamBackendDataCache
{
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FGlobalCacheKey, T> GlobalCache;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FRequestTypeCacheKey, T> RequestTypeCache;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FCallingContextCacheKey, T> CallingContextCache;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FCallsiteCacheKey, T> CallsiteCache;
};
